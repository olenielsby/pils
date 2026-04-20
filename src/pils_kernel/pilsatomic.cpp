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
        if (refcount.refCount++ >= 0)
		{
			unduplicateChildren();
			return true;
		}
		else
		{
            refcount.refCount--;
			return false;
		}
	}

	/* For use with listeners */

	bool Any::duplicateReferenceNoChildren() const
	{
        if (++refcount.refCount != 0)
		{
			return true;
		}
		else
		{
            refcount.refCount--;
			return false;
		}
	}

	void Any::releaseFrom(Any &scrap) const
	{
        if (refcount.release())
		{
            refcount.becomeScrap(scrap.refcount.scrapLink);
            scrap.refcount.scrapLink = (Any*)this;
		}
	}

	bool Any::duplicateReference(bool copying) const
	{
        if (++refcount.refCount == 0)
		{
            refcount.refCount--;
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
