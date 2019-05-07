#pragma once

#include <Spixii/Core.h>

namespace Spixii
{
    class Allocator
    {
    public:
        virtual void *Allocate(std::size_t size, std::size_t align) = 0;
        virtual void Dealocate(void *p)                             = 0;
        virtual std::size_t AllocatedSize(void *p)                  = 0;

        //template <class T, class P1>
        //T *makeNew(const P1 &p1) { return new (Allocate(sizeof(T), alignof(T))) T(p1); }

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
    };

    class MallocAllocator : public Allocator
    {
    public:
        void *Allocate(std::size_t size, std::size_t align) override;
        void Dealocate(void *p) override;
        std::size_t AllocatedSize(void *p) override;
    };
}  // namespace Spixii