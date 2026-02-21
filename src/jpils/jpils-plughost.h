/* This file is public domain */
#ifndef _JPILS__PLUGHOST_H_
#define _JPILS__PLUGHOST_H_

#include "pilsplug/plughost.h"
#include "jpils-plumming.h"

namespace PILS
{
	class PlugLibrarySpecial
		: public ReallySpecial, private PlugLibrary
	{
	public:
		PlugLibrarySpecial(const HashedConstant *&link, void *handle)
			: ReallySpecial(link), PlugLibrary(handle)
		{}
		size_t unlinkAndGetSize();
		void write(Writing &writing) const;
		const Special *as_Special() const;
		bool specialComparing(const PlugLibraryLookup &lookup) const;
	};

	class PlugObjectSpecial
		: public ReallySpecial, private PlugObject
	{
		friend class PlugTools;
	public:
		PlugObjectSpecial(const HashedConstant *&link, pilsplug::interface::Object *const object, const NodeConstant *types, size_t type, pilsplug::Plug &plug, const Special *handle)
			: ReallySpecial(link), PlugObject(object, types, type, plug, handle)
		{}
		size_t unlinkAndGetSize();
		void write(Writing &writing) const;
		const Special *as_Special() const;
		bool specialComparing(const PlugObjectLookup &lookup) const;
		const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const
		{
			return PlugObject::specialCalling(run, name, arg);
		}
		const Any *specialCalling(Runner &run, const Constant &name) const
		{
			return PlugObject::specialCalling(run, name, Empty::singleton);
		}
		const Any *specialCalling(Runner &run, const Integer &call) const
		{
			return PlugObject::specialCalling(run, call);
		}
		const Any *specialCalling(Runner &run, const PilsString &call) const
		{
			return PlugObject::specialCalling(run, call);
		}
	};
}

#endif
