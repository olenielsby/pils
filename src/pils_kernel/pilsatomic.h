/* This file is public domain */
#pragma once
#include <atomic>
#include <cassert>

namespace PILS {

class Terminator
{
public:
    static bool terminated;
};

template<class T>
class RefcountOrScrap
{
public:
    union
    {
        std::atomic<long> refCount;
        T* scrapLink;
    };

#ifndef NDEBUG
    bool isScrap = false;
#endif

    RefcountOrScrap() noexcept
    {
        new (&refCount) std::atomic<long>(0);
    }

    ~RefcountOrScrap() noexcept
    {
        assert(Terminator::terminated || isScrap && "RefcountOrScrap destroyed before becomeScrap()");
    }

    void retain() noexcept
    {
        assert(!isScrap && "RefcountOrScrap::retaion after becomeScrap()");
        refCount.fetch_add(1, std::memory_order_relaxed);
    }

    bool release() noexcept
    {
        assert(!isScrap && "RefcountOrScrap::release after becomeScrap()");
        return refCount.fetch_sub(1, std::memory_order_release) == 0;
    }
    bool isMultipleReferenced(int extraAllowed = 0) const
    {
        assert(!isScrap && "RefcountOrScrap::isMultipleReferenced after becomeScrap()");
        return refCount > extraAllowed;
    }

    static void acquireFence() noexcept
    {
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void becomeScrap(T* next) noexcept
    {
#ifndef NDEBUG
        isScrap = true;
#endif
        refCount.~atomic<long>();
        scrapLink = next;
    }

    T* nextScrap() const noexcept
    {
        return scrapLink;
    }
};

}