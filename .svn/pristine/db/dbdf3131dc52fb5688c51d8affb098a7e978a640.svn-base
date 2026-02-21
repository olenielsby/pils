/* This file is public domain */
#include "pilsread.h"
#include "writing.h"
#include "statement.h"

namespace PILS
{
	const Language *Language::as_Language() const
	{
		return this;
	}

	const long standardExpressWritingLimit = 0x10000;
	const Step *Language::calling(Runner &run, const Constant &call) const
	{
		return run.sink->called(run, call);
	}

	const Step *Language::calling(Runner &run, const NodeConstant &call) const
	{
		if (call.cliche->count == 1 && call.cliche->attributes[0] == &Empty::singleton)
		{
			const Constant *operation = call.cliche->head;
			if (operation == &Builtin::name.read)
			{
				const PilsString *source = call.element[0]->as_String();
				if (source)
				{
					Parsing *parsing = new (run.allocate(sizeof(ParsingNormal))) ParsingNormal(*source, *this);
					new (run.allocate(sizeof(ParseStart))) ParseStart(parsing->at);
					new (run.allocate(sizeof(ParseStart))) ParseStart(parsing->at);
					return parsing;
				}
				/**/
			}
			else if (operation == &Builtin::name.write)
			{
				// Constants are written without lenght checking.
				const PilsString *result;
				{
					WritingString writing(run, this, call.element[0]);
					call.element[0]->write(writing, WRITING_EXPRESSION, -1L, NULL);
					writing.done();
					result = writing.getString();
				}
				return run.sink->pass(run, result);
			}
			else if (operation == &Builtin::name.indent)
			{
				// Constants are written without lenght checking.
				const PilsString *result;
				{
					WritingIndentString writing(run, this, call.element[0]);
					call.element[0]->write(writing, WRITING_EXPRESSION, -1L, NULL);
					writing.done();
					result = writing.getString();
				}
				return run.sink->pass(run, result);
			}
			else if (operation == &Builtin::name.name_)
			{
				const ClicheShort *name = call.element[0]->as_ClicheShort();
				if (name)
				{
					Index::Record record(NULL, NULL);
					nameLookup(name, record);
					if (!record.local)
					{
						record.local = name->attributes[0]->as_String();
					}
					if (record.local)
						return run.sink->pass(run, *record.local);
				}
			}
			else if (operation == &Builtin::name.traceread)
			{
				const PilsString *source = call.element[0]->as_String();
				if (source)
				{
					Parsing *parsing = new (run.allocate(sizeof(ParsingTrace))) ParsingTrace(*source, *this);
					new (run.allocate(sizeof(ParseStart))) ParseStart(parsing->at);
					new (run.allocate(sizeof(ParseStart))) ParseStart(parsing->at);
					return parsing;
				}
			}
			// TODO: other operations.
		}
		return run.sink->called(run, call);
	}

	const Step *Language::calling(Runner &run, const NodeExpress &call) const
	{
		if (call.cliche->count == 1 && call.cliche->attributes[0] == &Empty::singleton)
		{
			const Constant *operation = call.cliche->head;
			if (operation == &Builtin::name.write)
			{
				// Expressions have a default limit of 64K
				long level = -1;
				{
					bool overflow;
					{
						WritingProbe writing(run, this, call.element[0], standardExpressWritingLimit);
						call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
						writing.done();
						overflow = writing.overflow();
					}
					if (overflow)
					{
						overflow = false;
						for (level=1;!overflow;level++)
						{
							WritingProbe writing(run, this, call.element[0], standardExpressWritingLimit);
							call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
							writing.done();
							overflow = writing.overflow();
						}
					}
				}
				const PilsString *result;
				if (--level)
				{
					WritingString writing(run, this, call.element[0]);
					call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
					writing.done();
					result = writing.getString();
				}
				else result = PilsString::get(_PS("..."));
				return run.sink->pass(run, result);
			}
			else if (operation == &Builtin::name.indent)
			{
				// Expressions have a default limit of 64K
				long level = -1;
				{
					bool overflow;
					{
						WritingIndentProbe writing(run, this, call.element[0], standardExpressWritingLimit);
						call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
						writing.done();
						overflow = writing.overflow();
					}
					if (overflow)
					{
						overflow = false;
						for (level=1;!overflow;level++)
						{
							WritingIndentProbe writing(run, this, call.element[0], standardExpressWritingLimit);
							call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
							writing.done();
							overflow = writing.overflow();
						}
					}
				}
				const PilsString *result;
				if (--level)
				{
					WritingIndentString writing(run, this, call.element[0]);
					call.element[0]->write(writing, WRITING_EXPRESSION, level, NULL);
					writing.done();
					result = writing.getString();
				}
				else result = PilsString::get(_PS("..."));
				return run.sink->pass(run, result);
			}
			// TODO: other operations.
		}
		return run.sink->called(run, call);
	}

	bool Language::validateString(const PilsString &string) const
	{
		const PILS_CHAR *at = string.value;
		const PILS_CHAR *end = at + string.count->value;
		return validateString(at, end) == end;
	}

	const PILS_CHAR *Language::validateString(const PILS_CHAR *at, const PILS_CHAR *const end) const
	{
		switch (flags & 7)
		{
		default:
		case 0: //all valid utf-8
			while (at < end)
			{
				unsigned char c = *at;
				if (c < 0x80) at++;
				else if (c < 0xC2 || at + 1 == end || (at[1] & 0xC0) != 0x80) return at;
				else if (c < 0xE0) at += 2;
				else if (c == 0xE0 && (unsigned char)at[1] < 0xA0) return at; // overlong encoding
				else if (c == 0xED && (unsigned char)at[1] >= 0xA0) return at; // utf-16 surrogate
				else if (c == 0xEF && (((unsigned char)at[1] == 0xBB && (unsigned char)at[2] == 0xBF) || ((unsigned char)at[1] == 0xBF && (unsigned char)at[2] == 0xBE)))
					return at; // byte order mark
				else if (at + 2 == end || (at[2] & 0xC0) != 0x80) return at;
				else if (c < 0xF0) at += 3;
				else if (c == 0xF0 && (unsigned char)at[1] < 0x90) return at; // overlong encoding
				else if (at + 3 == end || (at[3] & 0xC0) != 0x80) return at;
				else if (c < 0xF5) at += 4;
				else return at; // out of unicode range
			}
			return at;
		case 1: //all non-control valid utf-8
			while (at < end)
			{
				unsigned char c = *at;
				if (c < 0x20 || c == 0x7F) return at;
				else if (c < 0x80) at++;
				else if (c < 0xC2 || at + 1 == end || (at[1] & 0xC0) != 0x80) return at;
				else if (c < 0xE0) at += 2;
				else if (c == 0xE0 && (unsigned char)at[1] < 0xA0) return at; // overlong encoding
				else if (c == 0xED && (unsigned char)at[1] >= 0xA0) return at; // utf-16 surrogate
				else if (c == 0xEF && (((unsigned char)at[1] == 0xBB && (unsigned char)at[2] == 0xBF) || ((unsigned char)at[1] == 0xBF && (unsigned char)at[2] == 0xBE)))
					return at; // byte order mark
				else if (at + 2 == end || (at[2] & 0xC0) != 0x80) return at;
				else if (c < 0xF0) at += 3;
				else if (c == 0xF0 && (unsigned char)at[1] < 0x90) return at; // overlong encoding
				else if (at + 3 == end || (at[3] & 0xC0) != 0x80) return at;
				else if (c < 0xF5) at += 4;
				else return at; // out of unicode range
			}
			return at;
		case 2: //all ascii
		case 6:
			while (at < end && (*at & 0x80) == 0)
				at++;
			return at;
		case 3: //all non-control ascii
		case 7:
			while (at < end && (unsigned char)*at >= 0x20 && (unsigned char)*at < 0x7F)
				at++;
			return at;
		case 4: //anything
			return end;
		case 5: //any non-control
			while (at < end && *at != 0x7F && (unsigned char)*at >= 0x20)
				at++;
			return at;
		}
	}

	const NodeConstantShort *BuiltinClicheLanguage::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		/* Validate language node whilst creating index for writing */

		//Info about how to write a translated name

		//Collect info on translated names
		Language::Index *index = new Language::Index();

		{
			//Get default names
			const NodeConstant *defaultNames = NULL;
			for (size_t namespaceIndex = 1;; namespaceIndex++)
			{
				if (namespaceIndex == value->cliche->count) goto invalidLanguage;
				if (value->cliche->head != value->cliche->attributes[namespaceIndex]) continue;
				const NodeConstant *names = value->element[namespaceIndex]->as_NodeConstant();
				if (names == NULL) goto invalidLanguage;
				defaultNames = names;
				break;
			}

			//Get default url
			const Constant* defaultUrl = defaultNames->cliche->head;
			if (defaultUrl == &Builtin::name.minus) defaultUrl = NULL;

			//Check the presence of a format control string
			if (value->cliche->attributes[0] != &Empty::singleton
				|| value->element[0]->as_String() == NULL)
				goto invalidLanguage;

			//Walk through namespaces - save default namespace for later
			for (size_t namespaceIndex = 1; namespaceIndex < value->cliche->count; namespaceIndex++)
			{
				//namespace specification must be a node constant
				const NodeConstant *names = value->element[namespaceIndex]->as_NodeConstant();

				//leave default namespace for later
				if (names == defaultNames) continue;

				//namespace prefix must be a string
				const PilsString *prefix = value->cliche->attributes[namespaceIndex]->as_String();
				if (prefix == NULL || names == NULL) goto invalidLanguage;

				// index translations
				for (size_t i = 0; i < names->cliche->count; i++)
				{
					//ignore attributes with non-string names
					const PilsString* local = names->cliche->attributes[i]->as_String();
					if (local == NULL) continue;

					//no translation for empty list
					const Constant* value = names->element[i];
					if (value == &Empty::singleton) continue;

					//don't translate out of the standard namespace
					const ClicheShort *cliche = value->as_ClicheShort();
					if (cliche && cliche->head == defaultUrl && cliche->attributes[0]->as_String())
						continue;
					index->translation[value] = Language::Index::Record(prefix, local);
				}

				// index the namespace prefix if open
				const Constant* url = names->cliche->head;
				if (url != &Builtin::name.minus)
					index->prefix[url] = prefix;
			}

			//Process default namespace
			if (defaultNames == NULL) goto invalidLanguage;
			for (size_t i = 0; i < defaultNames->cliche->count; i++)
			{
				//ignore attributes with non-string names
				const PilsString* local = defaultNames->cliche->attributes[i]->as_String();
				if (local == NULL) continue;

				//no translation for empty list
				const Constant* value = defaultNames->element[i];
				if (value == &Empty::singleton) continue;

				//default namespace uses no prefix
				index->translation[value] = Language::Index::Record((const PilsString*)NULL, local);
			}

			// index the null namespace prefix if open
			if (defaultUrl)
				index->prefix[defaultUrl] = NULL;

			return
				(const NodeConstantShort*)
				new (Heap::allocate(sizeof(Language)))
				Language(link, value, defaultNames, index);
		}

	invalidLanguage:
		/* Create a standard const NodeConstant */
		delete index;
		return
			new (Heap::allocate(sizeof(NodeConstantShort)))
			const NodeConstantShort(link, *this, value);
	}

	size_t Language::unlinkAndGetSize()
	{
		delete index;
		unhash();
		cliche->releaseFrom(*this);
		element[0]->releaseFrom(*this);
		return sizeof(Language);
	}

	NameSkin Language::nameLookup(const ClicheShort *name, Index::Record &record) const
	{
		std::map<const Constant*, Index::Record>::const_iterator foundTranslation = index->translation.find(name);
		if (foundTranslation != index->translation.end())
		{
			record = foundTranslation->second;
		}
		else
		{
			// No translation
			const PilsString *local = name->attributes[0]->as_String();
			if (local == NULL) return NAMESKIN_NONE; // Not a name
			const Constant *url = name->head;
			if (url == &Builtin::name.minus) return NAMESKIN_NONE; // Not a name

			// Lookup namespace prefix
			std::map<const Constant*, const PilsString*>::const_iterator foundPrefix = index->prefix.find(url);
			if (foundPrefix == index->prefix.end()) return NAMESKIN_NONE;
			record = Index::Record(foundPrefix->second, local);
		}
		if (record.prefix && !validateString(*record.prefix)) return NAMESKIN_NONE;
		if (!validateString(*record.local)) return NAMESKIN_STRING;
		return record.local->nameSkin();
	}

	const Step *SinkBug::pass(Runner &run, const Any *value)
	{
		WritingString writing(run, language, value);
		value->write(writing, WRITING_EXPRESSION, 10, NULL);
		const PilsString *string = writing.getString();
		bug(run, *string);
		string->releaseReference();
		run.sink = kick(run);
		return value->passCounted(run);
	}
}
