#pragma once

#include <Spixii/Core.h>

namespace Spixii
{
    class Allocator
    {
    public:
        virtual void * Allocate(uint64 size, uint64 align) = 0;
        virtual void   Dealocate(void *p)                  = 0;
        virtual uint64 AllocatedSize(void *p)              = 0;

        virtual ~Allocator() = default;

        template <class T, typename... Args>
        T *makeNew(const Args &... args) { return new(Allocate(sizeof(T), alignof(T))) T(args...); }

        template <class T>
        void makeDelete(T *p)
        {
            if(p)
            {
                p->~T();
                Dealocate(p);
            }
        }

    protected:
        static uint64 CalculatePadding(const uint64 baseAddress, const uint64 alignment);
        static uint64 CalculatePaddingWithHeader(const uint64 baseAddress, const uint64 alignment, const uint64 headerSize);
    };
}  // namespace Spixii