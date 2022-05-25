#include "Allocator.hpp"
#include <cassert>
#include <cstring>

#ifndef ALIGN
#define ALIGN(x, a)         (((x) + ((a) - 1)) & ~((a) - 1))
#endif

using namespace ENGINE;

ENGINE::Allocator::Allocator()
    : m_pPageList(nullptr), m_pFreeList(nullptr), m_szDataSize(0), m_szPageSize(0),
    m_szAlignmentSize(0), m_szBlockSize(0), m_nBlocksPerPage(0),
    m_nPages(0), m_nBlocks(0), m_nFreeBlocks(0)
{
}

ENGINE::Allocator::Allocator(size_t data_size, size_t page_size, size_t alignment)
    : m_pPageList(nullptr), m_pFreeList(nullptr)
{
    Reset(data_size, page_size, alignment);
}

ENGINE::Allocator::~Allocator()
{
    FreeAll();
}

void ENGINE::Allocator::Reset(size_t data_size, size_t page_size, size_t alignment)
{
    FreeAll();

    m_szDataSize = data_size;
    m_szPageSize = page_size;

    size_t minimal_size = (sizeof(BlockHeader) > m_szDataSize) ? sizeof(BlockHeader) : m_szDataSize;

    // この魔法は、alignmentが2^ nの場合にのみ機能します。これは、ほとんどのCPU / GPUでもalignmentが2 ^ nである必要があるためですが、
    // それでもassertを使用してそれを保証します。
#if defined(_DEBUG)
    assert(alignment > 0 && ((alignment & (alignment - 1))) == 0);
#endif
    // d/aの結果は0じゃない場合はsize増やす
    m_szBlockSize = ALIGN(minimal_size, alignment);

    m_szAlignmentSize = m_szBlockSize - minimal_size;

    m_nBlocksPerPage = (m_szPageSize - sizeof(PageHeader)) / m_szBlockSize;
}

void* ENGINE::Allocator::Allocate()
{
    if (!m_pFreeList) {
        // 新しいページを作成する
        PageHeader* pNewPage = reinterpret_cast<PageHeader*>(new uint8_t[m_szPageSize]);
        ++m_nPages;
        m_nBlocks += m_nBlocksPerPage;
        m_nFreeBlocks += m_nBlocksPerPage;

#if defined(_DEBUG)
        FillFreePage(pNewPage);
#endif

        if (m_pPageList) {
            pNewPage->pNext = m_pPageList;
        }

        m_pPageList = pNewPage;

        BlockHeader* pBlock = pNewPage->Blocks();
        // ページ内の各ブロックをリンクする
        for (uint32_t i = 0; i < m_nBlocksPerPage - 1; i++) {
            pBlock->pNext = NextBlock(pBlock);
            pBlock = NextBlock(pBlock);
        }
        pBlock->pNext = nullptr;

        m_pFreeList = pNewPage->Blocks();
    }

    BlockHeader* freeBlock = m_pFreeList;
    m_pFreeList = m_pFreeList->pNext;
    --m_nFreeBlocks;

#if defined(_DEBUG)
    FillAllocatedBlock(freeBlock);
#endif

    return reinterpret_cast<void*>(freeBlock);
}

void ENGINE::Allocator::Free(void* p)
{
    BlockHeader* block = reinterpret_cast<BlockHeader*>(p);

#if defined(_DEBUG)
    FillFreeBlock(block);
#endif

    block->pNext = m_pFreeList;
    m_pFreeList = block;
    ++m_nFreeBlocks;
}

void ENGINE::Allocator::FreeAll()
{
    PageHeader* pPage = m_pPageList;
    while (pPage) {
        PageHeader* _p = pPage;
        pPage = pPage->pNext;

        delete[] reinterpret_cast<uint8_t*>(_p);
    }

    m_pPageList = nullptr;
    m_pFreeList = nullptr;

    m_nPages = 0;
    m_nBlocks = 0;
    m_nFreeBlocks = 0;
}

#if defined(_DEBUG)
void ENGINE::Allocator::FillFreePage(PageHeader* pPage)
{
    // page header
    pPage->pNext = nullptr;

    // blocks
    BlockHeader* pBlock = pPage->Blocks();
    for (uint32_t i = 0; i < m_nBlocksPerPage; i++)
    {
        FillFreeBlock(pBlock);
        pBlock = NextBlock(pBlock);
    }
}

void ENGINE::Allocator::FillFreeBlock(BlockHeader* pBlock)
{
    // block header + data
    std::memset(pBlock, PATTERN_FREE, m_szBlockSize - m_szAlignmentSize);

    // alignment
    std::memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
        PATTERN_ALIGN, m_szAlignmentSize);
}

void ENGINE::Allocator::FillAllocatedBlock(BlockHeader* pBlock)
{
    // block header + data
    std::memset(pBlock, PATTERN_ALLOC, m_szBlockSize - m_szAlignmentSize);

    // alignment
    std::memset(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize - m_szAlignmentSize,
        PATTERN_ALIGN, m_szAlignmentSize);
}
#endif
ENGINE::BlockHeader* ENGINE::Allocator::NextBlock(BlockHeader* pBlock) const
{
    return reinterpret_cast<BlockHeader*>(reinterpret_cast<uint8_t*>(pBlock) + m_szBlockSize);
}