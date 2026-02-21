/* This file is public domain */
#include "jpils-plumming.h"
namespace PILS
{
	class Mutex_implementation : public juce::CriticalSection {};
	void Mutex::Implement::lock(Mutex_implementation &mutex)
	{
		mutex.enter();
	}
	void Mutex::Implement::unlock(Mutex_implementation &mutex)
	{
		mutex.exit();
	}

	Mutex::Mutex()
		: implementation(*new Mutex_implementation)
	{}
	Mutex::~Mutex()
	{
		delete &implementation;
    }

	void *InitialAllocator::allocate(size_t bytes)
	{
		void** block = (void**)malloc(bytes + sizeof(size_t));
		*block = chain;
		chain = block;
		return &block[1];
	}
	void InitialAllocator::free(void *block, size_t size)
	{
		throw "reference underflow";
	}
	void InitialAllocator::shutdown()
	{
		while (chain)
		{
			void* c = chain;
			chain = *(void**)c;
			::free(c);
		}
	}

	class MallocAllocator
		: public Heap::Allocator
	{
	public:
		/* Simple Malloc wrapper
		*/
		void *allocate(size_t bytes)
		{
			return malloc(bytes);
		}

		void free(void *block, size_t size)
		{
			return ::free(block);
		}
		void shutdown() {}
		static MallocAllocator singleton;
	};

	MallocAllocator MallocAllocator::singleton;

	class LeakcheckingAllocator
		: public Heap::Allocator
	{
	public:
		/* Detect memory leaks before destroying initial data */
		/* Note: this allocator is not thread-safe */
		void *allocate(size_t bytes)
		{
			Link *block = (Link *)malloc(bytes + sizeof(Link));
			block->previous = &link;
			block->next = link.next;
			link.next->previous = block;
			link.next = block;
			block->size = bytes;
			return block + 1;
		}

		void free(void *netto, size_t size)
		{
			Link *block = (Link*)netto - 1;
			if (block->size != size)
			{
				throw "inconsistent deallocation";
			}
			block->next->previous = block->previous;
			block->previous->next = block->next;
			::free(block);
		}
		void shutdown()
		{
			while (link.next != &link)
			{
				// const Any *leak = (const Any *)(link.next + 1);
				link.next = link.next->next;
			}
			if (link.previous != &link)
			{
				throw "leak detected";
			}
		}
		static LeakcheckingAllocator singleton;
		LeakcheckingAllocator()
		{
			link.next = &link;
			link.previous = &link;
		}
	private:
		struct Link
		{
			Link *next, *previous;
			size_t size;
		};
		Link link;
	};

	LeakcheckingAllocator LeakcheckingAllocator::singleton;

	void Heap::useStandardAllocator()
	{
#ifdef JUCE_DEBUG
		allocator = &LeakcheckingAllocator::singleton;
#else
		allocator = &MallocAllocator::singleton;
#endif
	}

	void Heap::shutdown()
	{
		allocator->shutdown();
		InitialAllocator::singleton.shutdown();
		delete Plum::cake();
	}
}
