/* This file is public domain */
#include "pilsatomic.h"
#include "datamodel.h"

namespace PILS
{
    void Any::retain() const
	{
        refcount.retain();
	}

    void Any::release() const
	{
        if(refcount.release())
		{
            Mutex::Lock lock(Mutex::singleMutex);
			((Any*)this)->disposeRoot();
		}
	}

	void Any::releaseReferenceInsideLock() const
	{
        if(refcount.release())
		{
			((Any*)this)->disposeRoot();
		}
	}

	void Any::unduplicateReference() const
	{
        bool gone = refcount.release();
        if(gone)

        {
            writeToDebugOutput(10);
        }
        assert(!gone && "Any::unduplicateReference() underflow");
	}

	/* For use in hash table lookup: ignore doomed constants */

	bool Any::duplicateReference() const
	{
        if (refcount.count()++ >= 0)
		{
			unduplicateChildren();
			return true;
		}
		else
		{
            refcount.count()--;
			return false;
		}
	}

	/* For use with listeners */

	bool Any::duplicateReferenceNoChildren() const
	{
        if (++refcount.count() != 0)
		{
			return true;
		}
		else
		{
            refcount.count()--;
			return false;
		}
	}

    //old method for use inside lock
    void Any::releaseFrom(Any &scrap) const
	{
        if (refcount.release())
		{
            refcount.becomeScrap(scrap.refcount.link());
            scrap.refcount.link() = (Any*)this;
		}
	}

    //new method for use without lock
    void Any::releaseFromScrap(const Any &scrap) const
    {
        if (refcount.release())
        {
            // Unhash before invalidating refcount,
            // or other threads might grab it.
            removeFromHashTable();
            refcount.becomeScrap(scrap.refcount.queue());
            scrap.refcount.queue() = const_cast<Any*>(this);
        }
    }

    bool Any::duplicateReference(bool copying) const
	{
        if (++refcount.count() == 0)
		{
            refcount.count()--;
			return false;
		}
		else
		{
			if (!copying)
				unduplicateChildren();
			return true;
		}
	}
}
