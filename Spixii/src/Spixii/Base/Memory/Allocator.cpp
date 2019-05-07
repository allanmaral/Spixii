#pragma once

#include "spxpch.h"

#include <malloc.h>

#include "Spixii/Base/Memory/Allocator.h"

namespace Spixii
{
    // 
    extern char g_buffer[];

    void *MallocAllocator::Allocate(std::size_t size, std::size_t align)
    {
        return _aligned_malloc(align, size);
    }

    void MallocAllocator::Dealocate(void *p)
    {
        _aligned_free(p);
    }

    std::size_t MallocAllocator::AllocatedSize(void *p)
    {
        return 0;
    }
}  // namespace Spixii