/* This file is public domain */
#ifndef _JPILS_STANDARD_SPECIALS_H_
#define _JPILS_STANDARD_SPECIALS_H_

#include "jpils-plumming.h"
#include "compile.h"

namespace PILS
{
	/*
	class Identifier
		: public ReallySpecial
	{
	public:
		static const Identifier *get(GUID value);
        int order(const Constant *other) const override;
	private:
		friend class IdentifierLookup;
		Identifier(const Constant *&link, const GUID &value)
			: ReallySpecial(link), value(value)
		{}
		const GUID value;
        size_t unlinkAndGetSize() override;
        void write(Writing &writing) const override;
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
		const ReallySpecial *newSpecial(const Constant *&link);
		void unduplicate();
        bool compare(const ReallySpecial &other) const override;
        size_t hash() const override;
	};
	*/
}
#endif
