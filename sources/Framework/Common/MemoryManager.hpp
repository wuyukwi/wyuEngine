#pragma once

#include <new>
#include "IRuntimeModule.hpp"
#include "Allocator.hpp"

namespace wyuEngine {
    class MemoryManager : public IRuntimeModule
    {
    public:
        template<typename T, typename... Arguments>
        T* New(Arguments... parameters)
        {
            return new (Allocate(sizeof(T))) T(parameters...);
        }

        template<typename T>
        void Delete(T* p)
        {
            p->~T();
            Free(p, sizeof(T));
        }

    public:
        virtual ~MemoryManager() override {}

        virtual int Initialize() override;
        virtual void Finalize() override;
        virtual void Tick() override;

        void* Allocate(size_t size);
        void* Allocate(size_t size, size_t alignment);
        void  Free(void* p, size_t size);
    private:
        static size_t* m_pBlockSizeLookup;
        static Allocator* m_pAllocators;
        static bool       m_bInitialized;

        static Allocator* LookUpAllocator(size_t size);
    };

    extern MemoryManager* g_pMemoryManager;
}
