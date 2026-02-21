/* This file is public domain */
#include "pilsatomic.h"

namespace PILS
{
	void Any::addReference() const
	{
		PILS_INTERLOCKED_INCREMENT(referenceCount);
	}

	void Any::releaseReference() const
	{
		if(PILS_INTERLOCKED_DECREMENT_RETURN(referenceCount) < 0)
		{
			Mutex::Lock lock(Heap::mutex);
			((Any*)this)->disposeRoot();
		}
	}

	void Any::releaseReferenceInsideLock() const
	{
		if(PILS_INTERLOCKED_DECREMENT_RETURN(referenceCount) < 0)
		{
			((Any*)this)->disposeRoot();
		}
	}

	void Any::unduplicateReference() const
	{
		PILS_INTERLOCKED_DECREMENT(referenceCount);
	}

	/* For use in hash table lookup: ignore doomed constants */

	bool Any::duplicateReference() const
	{
		if (PILS_INTERLOCKED_INCREMENT_RETURN(referenceCount) != 0)
		{
			unduplicateChildren();
			return true;
		}
		else
		{
			referenceCount--;
			return false;
		}
	}

	/* For use with listeners */

	bool Any::duplicateReferenceNoChildren() const
	{
		if (PILS_INTERLOCKED_INCREMENT_RETURN(referenceCount) != 0)
		{
			return true;
		}
		else
		{
			referenceCount--;
			return false;
		}
	}

	void Any::releaseFrom(Any &scrap) const
	{
		if (PILS_INTERLOCKED_DECREMENT_RETURN(referenceCount) < 0)
		{
			scrapLink = scrap.scrapLink;
			scrap.scrapLink = (Any*)this;
		}
	}

	bool Any::duplicateReference(bool copying) const
	{
		if (PILS_INTERLOCKED_INCREMENT_RETURN(referenceCount) == 0)
		{
			referenceCount--;
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
