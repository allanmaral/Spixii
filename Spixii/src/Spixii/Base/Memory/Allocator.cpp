#pragma once

#include "spxpch.h"

#include <malloc.h>

#include "Spixii/Base/Engine.h"
#include "Spixii/Base/Memory/Allocator.h"
#include "Spixii/Log.h"

namespace Spixii
{
    uint64 Allocator::CalculatePadding(const uint64 baseAddress, const uint64 alignment)
    {
        const uint64 offset = alignment - 1;
        const uint64 alignedAddress = (baseAddress + offset) & ~(offset);
        return alignedAddress - baseAddress;
    }

    uint64 Allocator::CalculatePaddingWithHeader(const uint64 baseAddress, const uint64 alignment, const uint64 headerSize)
    {
        return headerSize + CalculatePadding(baseAddress+headerSize, alignment);
    }
}  // namespace Spixii