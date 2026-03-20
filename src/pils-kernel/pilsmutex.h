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
    class Mutex : public QMutex
    {
    public:
        class Lock
        {
            QMutexLocker<QMutex> locker;
        public:
            explicit Lock(Mutex &mutex)
                : locker(&mutex)
            {}
        };
    };
}
