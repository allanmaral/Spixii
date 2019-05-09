#pragma once

#include "Spixii/Base/Memory/Allocator.h"

namespace Spixii
{
    class FreeListAllocator : public Allocator
    {
        struct BlockHeader
        {
            uint64 blockSize;
            uint8  padding;
        };

        struct Node
        {
            BlockHeader header;
            Node *      previous;
            Node *      next;
        };

    public:
        FreeListAllocator(uint64 capacity, Allocator *allocator);
        FreeListAllocator(void *memoryStart, uint64 capacity);

        virtual ~FreeListAllocator() override;

        void   Reset();
        void * Allocate(uint64 size, uint64 align) override;
        void   Dealocate(void *p) override;
        uint64 AllocatedSize(void *p) override;

    private:
        void Find(const uint64 size, const uint64 alignment, uint64 &padding, Node *&previousNode, Node *&selectedNode);
        void Coalescence(Node* freedNode);

    private:
        uint64     m_capacity;
        uint64     m_allocated;
        uint64     m_peakAllocation;
        void *     m_memoryAddress;
        bool       m_isCleaningNeeded;
        Allocator *m_backendAllocator;
        Node *     m_blockList;
    };

}  // namespace Spixii