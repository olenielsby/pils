/* This file is public domain */
#ifndef DEFINE_PILS_LANGUAGE_H
#define DEFINE_PILS_LANGUAGE_H
#include "datamodel.h"
namespace PILS
{
	class Language
		: public NodeConstantTiny
	{
	public:
		class Index
		{
		public:
			struct Record
			{
				const PilsString *prefix;
				const PilsString *local;
				Record(const PilsString* prefix, const PilsString* local)
					: prefix(prefix), local(local)
				{}
				Record()
				{}
                void write(Writing &writing, bool stringwise) const;
			};
			std::map<const Constant*, Record> translation;
			std::map<const Constant*, const PilsString*> prefix;
		};
        NameSkin nameLookup(const ClicheShort* name, Index::Record &record) const;
        const Any *read(const PilsString *text) const;
		Language(const HashedConstant *&link, const NodeConstant *value, const NodeConstant *defaultNamespace, Index *index)
			: NodeConstantTiny(link, BuiltinClicheLanguage::singleton, value),
			  index(index),
			  namespaces(value),
			  defaultNamespace(defaultNamespace),
			  flags(value->element[0]->as_String()->value[0])
		{}

        size_t unlinkAndGetSize() override;
		Index *index; /* Fast name lookup when writing */
		const NodeConstant *namespaces;
		const NodeConstant *defaultNamespace;
		const unsigned char flags;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Language *as_Language() const override;
        bool write(Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const PILS_CHAR *validateString(const PILS_CHAR *at, const PILS_CHAR *const end) const;
        bool validateString(const PilsString &string) const;
		bool withNoNames() const {return (flags & 0x10) != 0;}
		bool withNoSugar() const {return (flags & 0x20) != 0;}
	};
}
#endif
