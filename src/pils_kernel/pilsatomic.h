/* This file is public domain */
#pragma once
#include <atomic>
#include <cassert>
#include <cstdio>

namespace PILS {

class Runner;

class Terminator
{
public:
    static bool terminated;
};

template<class T>
class RefcountOrScrap
{
private:
    union
    {
        std::atomic<long> refCount;
        T* scrapLink;
        Runner *deletionRunner;
    };

#ifndef NDEBUG
    enum class ScrapState
    {
        Count,
        Link,
        Deletable
    };
    ScrapState scrapState = ScrapState::Count;
#endif

public:
    RefcountOrScrap() noexcept
    {
        new (&refCount) std::atomic<long>(0);
    }

    ~RefcountOrScrap() noexcept
    {
#ifndef NDEBUG
        assert(Terminator::terminated || scrapState == ScrapState::Deletable && "Not prepared for destruction");
#endif
    }

    std::atomic<long>& count() noexcept
    {
#ifndef NDEBUG
        assert(scrapState == ScrapState::Count);
#endif
        return refCount;
    }

    T*& link() noexcept
    {
#ifndef NDEBUG
        assert(scrapState == ScrapState::Link);
#endif
        return scrapLink;
    }

    void retain() noexcept
    {
        assert(scrapState == ScrapState::Count && "RefcountOrScrap::retaion after becomeScrap()");
        refCount.fetch_add(1, std::memory_order_relaxed);
    }

    bool release() noexcept
    {
        assert(scrapState == ScrapState::Count && "RefcountOrScrap::release after becomeScrap()");
        return refCount.fetch_sub(1, std::memory_order_release) == 0;
    }

    bool isMultipleReferenced(int extraAllowed = 0) const
    {
        assert(scrapState == ScrapState::Count && "RefcountOrScrap::isMultipleReferenced after becomeScrap()");
        return refCount > extraAllowed;
    }

    bool releaseIfMultipleReferenced() noexcept
    {
        assert(scrapState == ScrapState::Count && "RefcountOrScrap::releaseIfMultipleReferenced after becomeScrap()");

        long count = refCount.load(std::memory_order_relaxed);

        while (count > 0) {
            if (refCount.compare_exchange_weak(
                    count,
                    count - 1,
                    std::memory_order_release,
                    std::memory_order_relaxed))
                return true;
        }

        return false;
    }

    static void acquireFence() noexcept
    {
        std::atomic_thread_fence(std::memory_order_acquire);
    }

    void becomeScrap(T* next) noexcept
    {
#ifndef NDEBUG
        assert (scrapState == ScrapState::Count);
        scrapState = ScrapState::Link;
#endif
        refCount.~atomic<long>();
        scrapLink = next;
    }

    void prepareForDeletion(Runner &run) noexcept
    {
#ifndef NDEBUG
        assert(scrapState == ScrapState::Link);
        scrapState = ScrapState::Deletable;
#endif
        deletionRunner = &run;
    }

    Runner &run() noexcept
    {
#ifndef NDEBUG
        assert(scrapState == ScrapState::Deletable);
#endif
        return *deletionRunner;
    }
};

}

class LiveObjectCounter
{
public:
    LiveObjectCounter() noexcept
    {
        ++count;
    }
    ~LiveObjectCounter() noexcept
    {
        --count;
    }
    static void report(const char *prefix)
    {
#ifndef NDEBUG
        std::fprintf(stderr, "%s - object balace: %ld\n", prefix, count.load());
        count.store(0);
#endif
    }
private:
    inline static std::atomic<long> count{0};
};

#ifndef NDEBUG
#define LIVE_OBJECT_COUNT \
private: \
    LiveObjectCounter liveObjectCounter;
#else
#define LIVE_OBJECT_COUNT
#endif
