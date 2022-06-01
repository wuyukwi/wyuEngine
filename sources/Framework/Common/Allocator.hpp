#include <cstddef>
#include <cstdint>

namespace wyuEngine {

    struct BlockHeader {
        // 次のブロック
        BlockHeader* pNext;
    };

    struct PageHeader {
        // 次のページへ
        PageHeader* pNext;
        // 最初のブロックを取得する関数
        BlockHeader* Blocks() {
            return reinterpret_cast<BlockHeader*>(this + 1);
        }
    };
    class Allocator {
    public:
        //　デバッグパターン
        static constexpr uint8_t PATTERN_ALIGN = 0xFC;
        static constexpr uint8_t PATTERN_ALLOC = 0xFD;
        static constexpr uint8_t PATTERN_FREE = 0xFE;

        //　コンストラクタ
        Allocator();
        Allocator(size_t data_size, size_t page_size, size_t alignment);
        //　デストラクタ
        ~Allocator();

        //　allocatorリセットし、新しく構成する
        void Reset(size_t data_size, size_t page_size, size_t alignment);

        // blockの割り当てと解放
        void* Allocate();
        void  Free(void* p);
        void  FreeAll();
    private:
#if defined(_DEBUG)
        // デバッグパターンのページ解放
        void FillFreePage(PageHeader* pPage);

        // デバッグパターンのブロック解放
        void FillFreeBlock(BlockHeader* pBlock);

        //　割り当てられたブロックをデバッグパターンで埋める 
        void FillAllocatedBlock(BlockHeader* pBlock);
#endif

        //　次のブロックのポインターを取得
        BlockHeader* NextBlock(BlockHeader* pBlock) const;

        //　ページリスト 
        PageHeader* m_pPageList;

        //　フリーリスト 
        BlockHeader* m_pFreeList;

        //　サイズ関連データ
        size_t      m_szDataSize;
        size_t      m_szPageSize;
        size_t      m_szAlignmentSize;
        size_t      m_szBlockSize;
        uint32_t    m_nBlocksPerPage;

        // データ統計量
        uint32_t    m_nPages;
        uint32_t    m_nBlocks;
        uint32_t    m_nFreeBlocks;

        //　コピーコンストラクタ無効化にする
        Allocator(const Allocator& clone);
        Allocator& operator=(const Allocator& rhs);
    };
}