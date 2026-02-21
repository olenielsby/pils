/* This file is public domain */
#ifndef _JPILS_STANDARD_SPECIALS_H_
#define _JPILS_STANDARD_SPECIALS_H_

#include "jpils-plumming.h"
#include "pils-kernel/compile.h"

namespace PILS
{
	/*
	class Identifier
		: public ReallySpecial
	{
	public:
		static const Identifier *get(GUID value);
		int order(const Constant *other) const;
	private:
		friend class IdentifierLookup;
		Identifier(const HashedConstant *&link, const GUID &value)
			: ReallySpecial(link), value(value)
		{}
		const GUID value;
		size_t unlinkAndGetSize();
		void write(Writing &writing) const;
	};

	class IdentifierLookup
		: SpecialLookup
	{
	private:
		friend class Identifier;
		IdentifierLookup(GUID value)
			: value(value)
		{}
		const GUID value;
		const ReallySpecial *newSpecial(const HashedConstant *&link);
		void unduplicate();
		bool compare(const ReallySpecial &other) const;
		size_t hash() const;
	};
	*/
}
#endif
