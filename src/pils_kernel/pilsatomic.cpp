/* This file is public domain */
#include "pilsatomic.h"
#include "datamodel.h"
#include "datamodel.h"
#include "sink.h"
namespace PILS
{
    void Any::retain() const
	{
        refcount.retain();
	}

    void Any::unduplicateReference() const
	{
        bool gone = refcount.release();
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
