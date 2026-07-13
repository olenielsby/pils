/* This file is public domain */
#pragma once
#include <map>
#include <set>
#include <vector>
#include <new>
#include <algorithm>
#include <list>
#include <locale>

#include <QMutex>
#include <QMutexLocker>

namespace PILS
{
#ifdef NDEBUG
    class Mutex : public QMutex
    {
    public:
        static Mutex singleMutex;
        class Lock
        {
            QMutexLocker<QMutex> locker;
        public:
            explicit Lock(Mutex &mutex)
                : locker(&mutex)
            {}
        };
    };
#else
    class Mutex
    {
    public:
        static Mutex singleMutex;
        bool locked = false;
        class Lock
        {
            Mutex &mutex;
        public:
            explicit Lock(Mutex &mutex)
                : mutex(mutex)
            {
                assert(!mutex.locked);
                mutex.locked = true;
            }
            ~Lock()
            {
                assert(mutex.locked);
                mutex.locked = false;
            }
        };
    };
#endif
}
