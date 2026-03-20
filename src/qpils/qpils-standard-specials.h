/* This file is public domain */
#pragma once

#include "qpils-plumming.h"
#include "compile.h"
#include <QUuid>

namespace PILS
{
	class Identifier
		: public ReallySpecial
	{
	public:
        static const Identifier *get(QUuid value);
        int order(const Constant *other) const override;
	private:
		friend class IdentifierLookup;
        Identifier(const HashedConstant *&link, const QUuid &value)
			: ReallySpecial(link), value(value)
		{}
        const QUuid value;
        bool isIdentifier() const override;
        size_t unlinkAndGetSize() override;
        void write(Writing &writing) const override;
	};

	class IdentifierLookup
		: SpecialLookup
	{
	private:
		friend class Identifier;
        IdentifierLookup(QUuid value)
			: value(value)
		{}
        const QUuid value;
        const ReallySpecial *newSpecial(const HashedConstant *&link) override;
        void unduplicate() override;
        bool compare(const ReallySpecial &other) const override;
        size_t hash() const override;
	};
}
