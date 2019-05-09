#include "spxpch.h"

#include "Spixii/Base/Memory/FreeListAllocator.h"

#include "Spixii/Log.h"

#define Insert(n, _previous)                   \
    {                                          \
        if(_previous)                          \
        {                                      \
            n->previous     = _previous;       \
            n->next         = _previous->next; \
            _previous->next = n;               \
        }                                      \
        else                                   \
        {                                      \
            n->previous = nullptr;             \
            n->next     = m_blockList;         \
            m_blockList = n;                   \
        }                                      \
        if(n->next)                            \
        {                                      \
            n->next->previous = n;             \
        }                                      \
    }

#define Remove(n)                            \
    {                                        \
        if(n->next)                          \
        {                                    \
            n->next->previous = n->previous; \
        }                                    \
        if(n->previous)                      \
        {                                    \
            n->previous->next = n->next;     \
        }                                    \
        else                                 \
        {                                    \
            m_blockList = n->next;           \
        }                                    \
    }

namespace Spixii
{
    FreeListAllocator::FreeListAllocator(uint64 capacity, Allocator *allocator)
        : m_capacity(capacity)
        , m_allocated(0L)
        , m_peakAllocation(0L)
        , m_memoryAddress(nullptr)
        , m_isCleaningNeeded(true)
        , m_backendAllocator(allocator)
    {
        assert(m_capacity && "Allocator capacity cannot be 0");

        if(!m_backendAllocator)  // Need to alloc using malloc
        {
            m_memoryAddress = malloc(m_capacity);
            assert(m_memoryAddress && "Could not allocate the memory needed");
        }
        else
        {
            m_memoryAddress = m_backendAllocator->Allocate(m_capacity, 0);
            assert(m_memoryAddress && "Could not allocate the memory needed");
        }

        Reset();
    }

    FreeListAllocator::FreeListAllocator(void *memoryStart, uint64 capacity)
        : m_capacity(capacity)
        , m_allocated(0L)
        , m_peakAllocation(0L)
        , m_memoryAddress(memoryStart)
        , m_isCleaningNeeded(false)
        , m_backendAllocator(nullptr)
        , m_blockList(nullptr)
    {
        assert(memoryStart && "Invalid memory address");
        Reset();
    }

    FreeListAllocator::~FreeListAllocator()
    {
        assert(m_allocated <= m_capacity && "Memory overrun occurred");
        if(m_isCleaningNeeded)
        {
            if(m_backendAllocator)
            {
                m_backendAllocator->Dealocate(m_memoryAddress);
            }
            else
            {
                free(m_memoryAddress);
            }
        }
    }

    void FreeListAllocator::Reset()
    {
        m_allocated                   = 0L;
        m_peakAllocation              = 0L;
        m_blockList                   = (Node *)m_memoryAddress;
        m_blockList->header.blockSize = m_capacity;
        m_blockList->previous         = nullptr;
        m_blockList->next             = nullptr;
    }

    void *FreeListAllocator::Allocate(uint64 size, uint64 align)
    {
        const uint64 allocationHeaderSize = sizeof(FreeListAllocator::BlockHeader);
        assert("Allocation size must be bigger" && size >= sizeof(FreeListAllocator::Node));
        assert("Alignment must be at least 8" && align >= 8);

        // Search the list for an free block
        uint64 padding      = 0;
        Node * seletedNode  = nullptr;
        Node * previousNode = nullptr;

        Find(size, align, padding, previousNode, seletedNode);

        const uint64 alingmentPadding = padding - allocationHeaderSize;
        const uint64 requiredSize     = size + padding;
        const uint64 remainingMemory  = seletedNode->header.blockSize - requiredSize;

        // Need to create a new block with the remaining memory
        if(remainingMemory > 0)
        {
            Node *newNode             = (Node *)((uint64)seletedNode + requiredSize);
            newNode->header.blockSize = remainingMemory;
            Insert(newNode, seletedNode);
        }
        Remove(seletedNode);

        // Setup the allocated block
        const uint64 headerAddress                = (uint64)seletedNode + alingmentPadding;
        const uint64 dataAdress                   = headerAddress + allocationHeaderSize;
        ((BlockHeader *)headerAddress)->blockSize = requiredSize;
        ((BlockHeader *)headerAddress)->padding   = (uint8)alingmentPadding;

        m_allocated += requiredSize;
        m_peakAllocation = (requiredSize > m_peakAllocation) ? requiredSize : m_peakAllocation;

        SPX_ERROR_CORE("Base address: {0} - total: {1}", (uint64)seletedNode, requiredSize);
        return (void *)dataAdress;
    }

    void FreeListAllocator::Dealocate(void *p)
    {
        // Insert the block in the list sorted by the address
        const uint64       currentAddress = (uint64)p;
        const uint64       headerAddress  = currentAddress - sizeof(BlockHeader);
        const BlockHeader *header         = (BlockHeader *)headerAddress;

        Node *freedNode             = (Node *)(headerAddress - (uint64)header->padding);
        freedNode->header.blockSize = header->blockSize;
        freedNode->next             = nullptr;
        freedNode->previous         = nullptr;

        // Iterate over the list to insert the freed node
        Node *it     = m_blockList;
        Node *itPrev = nullptr;
        while(it != nullptr)
        {
            if(it > p)
            {
                // Insert after itPrev
                Insert(freedNode, itPrev);
                break;
            }
            itPrev = it;
            it     = it->next;
        }

        m_allocated -= freedNode->header.blockSize;

        // Merge contiguous nodes
        Coalescence(freedNode);
    }

    void FreeListAllocator::Coalescence(Node *freed)
    {
        // If both nodes are contiguous, merge then
        if(freed->next)
        {
            SPX_INFO_CORE("{0} & {1} - S{2}", ((uint64)freed + freed->header.blockSize), (uint64)freed->next, (int64)freed->next - ((int64)freed + (int64)freed->header.blockSize));
            if(((uint64)freed + freed->header.blockSize) == (uint64)freed->next)
            {
                SPX_INFO_CORE("\tMerging {0} & {1} - S{2}", (uint64)freed, (uint64)freed->next, (uint64)freed->header.blockSize);
                freed->header.blockSize += freed->next->header.blockSize;
                Remove(freed->next);
            }
        }

        if(freed->previous)
        {
            SPX_INFO_CORE("{0} & {1} - S{2}", ((uint64)freed->previous + freed->previous->header.blockSize), (uint64)freed, (int64)freed - ((int64)freed->previous + freed->previous->header.blockSize));
            if(((uint64)freed->previous + freed->previous->header.blockSize) == (uint64)freed)
            {
                SPX_INFO_CORE("\tMerging {0} & {1} - S{2}", (uint64)freed->previous, (uint64)freed, (uint64)freed->previous->header.blockSize);
                freed->previous->header.blockSize += freed->header.blockSize;
                Remove(freed);
            }
        }
    }

    uint64 FreeListAllocator::AllocatedSize(void *p)
    {
        return uint64();
    }

    void FreeListAllocator::Find(const uint64 size, const uint64 alignment, uint64 &padding, Node *&previousNode, Node *&selectedNode)
    {
        // Iterate the block list to find the fist block that fits
        Node *it     = m_blockList;
        Node *itPrev = nullptr;

        while(it != nullptr)
        {
            padding = Allocator::CalculatePaddingWithHeader((uint64)it, alignment, sizeof(BlockHeader));

            const uint64 requiredSpace = size + padding;
            if(it->header.blockSize >= requiredSpace)
            {
                break;
            }
            itPrev = it;
            it     = it->next;
        }

        previousNode = itPrev;
        selectedNode = it;
    }
}  // namespace Spixii