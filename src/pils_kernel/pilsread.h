/* This file is public domain */
#ifndef DEFINE_PILS_PILSREAD_H
#define DEFINE_PILS_PILSREAD_H
#include "pipe.h"

#ifdef PILS_CHAR_IS_UTF16
	typedef	std::wstring stringbuf;
#else
	typedef std::string stringbuf;
#endif

#include "pilsstring.h"
#include "language.h"

namespace PILS
{
	enum ParseLevel
	{
		PARSE_RULESET,
		PARSE_PHRASE,
		PARSE_ARGUMENT,
		PARSE_ADDEND,
		PARSE_COMPARAND,
		PARSE_ELEMENT,
		PARSE_ATTRIBUTE,
		PARSE_BAR,
		PARSE_CLOSE
	};

	class Parse;

	class Parsing
		: public Kickable
	{
	public:
        const Step *step_(Runner &run) const override;
		virtual const Step *done(Runner &run, const Any *item) = 0;
		virtual void tracing(const Any *item, const unsigned char *from) = 0;
		const unsigned char *at;
		const unsigned char *end;
		const unsigned char *beforeSpace;
		const unsigned char *afterSpace;
		const PilsString &source;
		const Language &language;
		const Step *redirection;
		const Any *inversion;
		const Constant *lastName;
		enum ErrorCode
		{
			ERROR_NOT_IMPLEMENTED,
			ERROR_STACK_OVERFLOW,
			ERROR_UNEXPECTED_END,
			ERROR_UNEXPECTED_CHARACTER,
			ERROR_BAD_STRING,
			ERROR_BAD_DATE,
			ERROR_BAD_DURATION,
			ERROR_BAD_EXPONENT,
			ERROR_BAD_PREFIX,
			ERROR_FORBIDDEN_NAME,
			ERROR_UNKNOWN_NAME,
			ERROR_MULTIPLE_PREFIX,
			ERROR_TWIN_ATTRIBUTE,
			ERROR_BAD_DOT,
			ERROR_MISSING_OPERAND,
			ERROR_BAD_CONSTANT,
			ERROR_BAD_RULE,
			ERROR_UNDEFINED_LABEL,
			ERROR_TWIN_LABEL
		};
		enum Nametype
		{
			NAMETYPE_NAME,
			NAMETYPE_OPERATOR,
			NAMETYPE_ADDITION,
			NAMETYPE_RELATION,
			NAMETYPE_ASTERISKED,
			NAMETYPE_PREFIX,
			NAMETYPE_NODEHEAD
		};
		const Step *error(Runner &run, ErrorCode code);
		void redirectError(Runner &run, ErrorCode code);
	protected:
		Parsing(const PilsString &source, const Language &language)
			: at((const unsigned char *)source.value)
			, end((const unsigned char *)(source.value+source.count->value))
			, afterSpace(nullptr)
			, source(source)
			, language(language)
			, redirection(nullptr)
			, inversion(nullptr)
			, lastName(nullptr)
		{}
	private:
		const PilsString *string();
		const Constant *date(Runner &run);
		const Step *number(Runner &run);
		const Step *name(Runner &run);
		const Step *questionName(Runner &run);
		const Step *constant(Runner &run, const Constant *value);
		const Step *defineLabel(Runner &run, int index);
		const Step *useLabel(Runner &run, int index);
		Nametype nametype();
		void space();
		friend class ParseLabel;
		std::map<int, const Any *> labels;
	};

	class ParsingNormal
		: public Parsing
	{
	public:
		ParsingNormal(const PilsString &source, const Language &language)
			: Parsing(source, language)
		{}
		Sink *kick(Runner &run);
		const Step *done(Runner &run, const Any *item);
		void tracing(const Any *item, const unsigned char *from);
	};

	class ParsingTrace
		: public ParsingNormal
	{
	public:
		ParsingTrace(const PilsString &source, const Language &language)
            : ParsingNormal(source, language), tracechain(Empty::get())
        {}
		Sink *kick(Runner &run);
	private:
		const Any *tracechain;
		void tracing(const Any *item, const unsigned char *from);
		const Step *done(Runner &run, const Any *item);
	};

	class Parse
		: public Kickable
	{
	public:
        Sink *kick(Runner &run) override;
		virtual const Step *space(Runner &run, Parsing &parsing);
		virtual const Step *end(Runner &run, Parsing &parsing);
		virtual const Step *beginParenthesis(Runner &run, Parsing &parsing);
		virtual const Step *endParenthesis(Runner &run, Parsing &parsing);
		virtual const Step *beginSquare(Runner &run, Parsing &parsing);
		virtual const Step *endSquare(Runner &run, Parsing &parsing);
		virtual const Step *endSquareNodehead(Runner &run, Parsing &parsing);
		virtual const Step *beginCurl(Runner &run, Parsing &parsing);
		virtual const Step *endCurl(Runner &run, Parsing &parsing);
		virtual const Step *bar(Runner &run, Parsing &parsing);
		virtual const Step *comma(Runner &run, Parsing &parsing);
		virtual const Step *colon(Runner &run, Parsing &parsing);
		virtual const Step *colonNode(Runner &run, Parsing &parsing);
		virtual const Step *colonColon(Runner &run, Parsing &parsing);
		virtual const Step *semicolon(Runner &run, Parsing &parsing);
		virtual const Step *semicolonNode(Runner &run, Parsing &parsing);
		virtual const Step *dot(Runner &run, Parsing &parsing);
		virtual const Step *dotAttribute(Runner &run, Parsing &parsing);
		virtual const Step *dotInversion(Runner &run, Parsing &parsing);
		virtual const Step *dotColonInversion(Runner &run, Parsing &parsing);
		virtual const Step *question(Runner &run, Parsing &parsing);
		virtual const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		virtual const Step *name(Runner &run, Parsing &parsing, const Constant *name);
		virtual const Step *operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name);
		virtual const Step *nodehead(Runner &run, Parsing &parsing, const Constant *head);
		virtual void close(Runner &run, Parsing &parsing, ParseLevel level);
		virtual void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		virtual void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		virtual void closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		virtual const Step *attributeName(Runner &run, Parsing &parsing, const Constant *value);
		const unsigned char *at;
		class AnyNodeBuilderChain : public NodeBuilder<const Any>
		{
		public:
            AnyNodeBuilderChain(Runner &run, const Constant *head, const unsigned char *from, AnyNodeBuilderChain *next)
                : NodeBuilder<const Any>(run, head), next(next), from(from)
			{}
			AnyNodeBuilderChain *const next;
			const unsigned char *const from;
		};
		class ConstantNodeBuilderChain : public NodeBuilder<const Constant>
		{
		public:
            ConstantNodeBuilderChain(Runner &run, const Constant *head, const unsigned char *from, ConstantNodeBuilderChain *next)
                : NodeBuilder<const Constant>(run, head), next(next), from(from)
			{}
			ConstantNodeBuilderChain *const next;
			const unsigned char *const from;
		};
	protected:
		Parse(const unsigned char *at)
			: at(at)
		{}
	private:
        const Step *step_(Runner &run) const override; //dummy
	};

	class ParseStart
		: public Parse
	{
	public:
		ParseStart(const unsigned char *at)
			: Parse(at)
		{}
		virtual void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseHoldAny
		: public Parse
	{
	public:
		ParseHoldAny(const unsigned char *at, const Any *hold)
			: Parse(at), hold(hold), to(at)
		{}
		Sink *kick(Runner &run);
		const Any *hold;
		const unsigned char *to;
	};

	class ParseDone
		: public ParseHoldAny
	{
	public:
		ParseDone(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		virtual const Step *end(Runner &run, Parsing &parsing);
	};

	class ParseSequel
		: public ParseHoldAny
	{
	public:
		ParseSequel(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		void closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *dotInversion(Runner &run, Parsing &parsing);
		const Step *dotColonInversion(Runner &run, Parsing &parsing);
		const Step *operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name);
		const Step *relation(Runner &run, Parsing &parsing, const Constant *name);
	};

	class ParseInversion
		: public ParseHoldAny
	{
	public:
		ParseInversion(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		const Step *beginParenthesis(Runner &run, Parsing &parsing);
	};

	class ParseHideInversionBase
		: public ParseHoldAny
	{
	protected:
		ParseHideInversionBase(const unsigned char *at, Parsing &parsing, const Any *inversion)
			: ParseHoldAny(at, parsing.inversion), restore(parsing.inversion)
		{
			parsing.inversion = inversion;
		}
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		const Any *&restore;
	};

	class ParseHideInversion
		: public ParseHideInversionBase
	{
	public:
		ParseHideInversion(const unsigned char *at, Parsing &parsing, const Any *inversion)
			: ParseHideInversionBase(at, parsing, inversion)
		{}
		void closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseInversionParenthesis
		: public ParseHideInversionBase
	{
	public:
		ParseInversionParenthesis(Parsing &parsing, const Any *inversion = nullptr)
			: ParseHideInversionBase(parsing.at, parsing, inversion)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseEndParenthesis
		: public ParseHoldAny
	{
	public:
		ParseEndParenthesis(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		virtual const Step *endParenthesis(Runner &run, Parsing &parsing);
	};

	class ParseOperand
		: public Parse
	{
	public:
		ParseOperand(const unsigned char *at, ParseLevel level)
			: Parse(at), level(level)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		Sink *kick(Runner &run);
		ParseLevel level;
	};

	class ParseHoldConstant
		: public Parse
	{
	public:
		ParseHoldConstant(const unsigned char *at, const Constant *hold)
			: Parse(at), hold(hold)
		{}
		Sink *kick(Runner &run);
		const Constant *hold;
	};

	class ParseName
		: public ParseHoldConstant
	{
	public:
		ParseName(const unsigned char *at, const Constant *hold)
			: ParseHoldConstant(at, hold)
		{}
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		const Step *beginParenthesis(Runner &run, Parsing &parsing);
		const Step *beginSquare(Runner &run, Parsing &parsing);
	};

	class ParsePrefixOperator
		: public ParseHoldConstant
	{
	public:
		ParsePrefixOperator(const unsigned char *at, const Constant *name)
			: ParseHoldConstant(at, name)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseList
		: public Parse
	{
	public:
        ParseList(Runner &run, const unsigned char *at, const Any *element)
            : Parse(at), builder(run)
		{
			builder.add(element);
		}
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *comma(Runner &run, Parsing &parsing);
	private:
		ListBuilder<const Any, const Any> builder;
	};

	class ParseNodeBase
		: public Parse
	{
	public:
		Sink *kick(Runner &run);
		AnyNodeBuilderChain *chain;
	protected:
		ParseNodeBase(AnyNodeBuilderChain *chain, const unsigned char *at) : Parse(at), chain(chain) {}
		const Any *build(Runner &run, Parsing &parsing);
	};

	class ParseColonInversion
		: public ParseNodeBase
	{
	public:
		ParseColonInversion(const unsigned char *at, const Any *inner)
			: ParseNodeBase(nullptr, at), inner(inner)
		{}
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *attributeName(Runner &run, Parsing &parsing, const Constant *value);
		const Step *colon(Runner &run, Parsing &parsing);
		const Step *colonNode(Runner &run, Parsing &parsing);
		const Step *colonColon(Runner &run, Parsing &parsing);
		const Any *inner;
	};

	class ParseNodeAttributes
		: public ParseNodeBase
	{
	public:
		ParseNodeAttributes(AnyNodeBuilderChain *chain, const unsigned char *at) : ParseNodeBase(chain, at) {}
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		const Step *attributeName(Runner &run, Parsing &parsing, const Constant *value);
	};

	class ParseNodeStart
		: public ParseNodeAttributes
	{
	public:
		ParseNodeStart(AnyNodeBuilderChain *chain, const unsigned char *at) : ParseNodeAttributes(chain, at) {}
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParsePhraseAttributes
		: public ParseNodeAttributes
	{
	public:
		ParsePhraseAttributes(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParseNodeAttributes(chain, at)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level);
	};

	class ParsePhraseStart
		: public ParsePhraseAttributes
	{
	public:
		ParsePhraseStart(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParsePhraseAttributes(chain, at)
		{}
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParsePhraseEndParenthesis
		: public ParseNodeBase
	{
	public:
		ParsePhraseEndParenthesis(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParseNodeBase(chain, at)
		{}
		const Step *endParenthesis(Runner &run, Parsing &parsing);
	};

	class ParseRuleset
		: public Parse
	{
	public:
        ParseRuleset(Runner &run, const unsigned char *at)
            : Parse(at), builder(run)
		{}
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *beginCurl(Runner &run, Parsing &parsing);
	private:
		friend class ParseRuleEnd;
		ListBuilder<const Any, const Any> builder;
	};

	class ParseRulePatternBase
		: public Parse
	{
	public:
		ParseRulePatternBase(const unsigned char *at)
			: Parse(at)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseRulePattern
		: public ParseRulePatternBase
	{
	public:
		ParseRulePattern(const unsigned char *at)
			: ParseRulePatternBase(at)
		{}
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *dotAttribute(Runner &run, Parsing &parsing);
	};

	class ParseRuleDotPattern
		: public ParseRulePatternBase
	{
	public:
		ParseRuleDotPattern(const unsigned char *at)
			: ParseRulePatternBase(at)
		{}
		void closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseRuleAction
		: public ParseHoldAny
	{
	public:
		ParseRuleAction(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		const Step *bar(Runner &run, Parsing &parsing);
	};

	class ParseRuleEnd
		: public ParseHoldAny
	{
	public:
		ParseRuleEnd(const unsigned char *at, const Any *hold)
			: ParseHoldAny(at, hold)
		{}
		const Step *endCurl(Runner &run, Parsing &parsing);
	};

	class ParseConstant
		: public Parse
	{
	public:
		ParseConstant(const unsigned char *at) : Parse(at) {}
		using Parse::close;
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *nodehead(Runner &run, Parsing &parsing, const Constant *head);
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		const Step *question(Runner &run, Parsing &parsing);
		const Step *name(Runner &run, Parsing &parsing, const Constant *name);
		const Step *operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name);
		const Step *relation(Runner &run, Parsing &parsing, const Constant *name);
		const Step *colon(Runner &run, Parsing &parsing);
		const Step *colonNode(Runner &run, Parsing &parsing);
		const Step *semicolonNode(Runner &run, Parsing &parsing);
	};

	class ParseSquare
		: public ParseConstant
	{
	public:
		ParseSquare(const unsigned char *at) : ParseConstant(at) {}
		using ParseConstant::close;
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	};

	class ParseConstantHold
		: public ParseConstant
	{
	public:
		ParseConstantHold(const unsigned char *at, const Constant *hold)
			: ParseConstant(at), hold(hold)
		{}
		Sink *kick(Runner &run);
		const Constant *hold;
	};

	class ParseEndSquare
		: public ParseConstantHold
	{
	public:
		ParseEndSquare(const unsigned char *at, const Constant *hold)
			: ParseConstantHold(at, hold)
		{}
		const Step *endSquare(Runner &run, Parsing &parsing);
		const Step *endSquareNodehead(Runner &run, Parsing &parsing);
	};

	class ParseAttributeName
		: public ParseConstant
	{
	public:
		ParseAttributeName(const unsigned char *at) : ParseConstant(at) {}
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	};

	class ParseAttributeValue
		: public Parse
	{
	public:
		ParseAttributeValue(const unsigned char *at, const Constant &name)
			: Parse(at), name(name)
		{}
		const Constant &name;
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
	};

	class ParseConstantNodeBase
		: public ParseConstant
	{
	public:
		Sink *kick(Runner &run);
		AnyNodeBuilderChain *chain;
	protected:
		ParseConstantNodeBase(AnyNodeBuilderChain *chain, const unsigned char *at) : ParseConstant(at), chain(chain) {}
		const Any *build(Runner &run, Parsing &parsing);
	};

	class ParseConstantNodeAttributes
		: public ParseConstantNodeBase
	{
	public:
		ParseConstantNodeAttributes(AnyNodeBuilderChain *chain, const unsigned char *at) : ParseConstantNodeBase(chain, at) {}
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		const Step *attributeName(Runner &run, Parsing &parsing, const Constant *value);
	};

	class ParseConstantNodeStart
		: public ParseConstantNodeAttributes
	{
	public:
		ParseConstantNodeStart(AnyNodeBuilderChain *chain, const unsigned char *at) : ParseConstantNodeAttributes(chain, at) {}
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	};

	class ParseConstantPhraseAttributes
		: public ParseConstantNodeAttributes
	{
	public:
		ParseConstantPhraseAttributes(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParseConstantNodeAttributes(chain, at)
		{}
		void close(Runner &run, Parsing &parsing, ParseLevel level);
	};

	class ParseConstantPhraseStart
		: public ParseConstantPhraseAttributes
	{
	public:
		ParseConstantPhraseStart(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParseConstantPhraseAttributes(chain, at)
		{}
		const Step *dotAttribute(Runner &run, Parsing &parsing);
		const Step *dot(Runner &run, Parsing &parsing);
		const Step *semicolon(Runner &run, Parsing &parsing);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	};

	class ParseConstantPhraseEndSquare
		: public ParseConstantNodeBase
	{
	public:
		ParseConstantPhraseEndSquare(AnyNodeBuilderChain *chain, const unsigned char *at)
			: ParseConstantNodeBase(chain, at)
		{}
		const Step *endSquare(Runner &run, Parsing &parsing);
	};

	class ParseConstantAttributeValue
		: public ParseConstant
	{
	public:
		ParseConstantAttributeValue(const unsigned char *at, const Constant &name)
			: ParseConstant(at), name(name)
		{}
		const Constant &name;
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	};

	class ParseConstantElement
		: public ParseConstantHold
	{
	public:
		ParseConstantElement(const unsigned char *at, const Constant *hold) : ParseConstantHold(at, hold) {}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
	};

	class ParseConstantList
		: public ParseConstant
	{
	public:
        ParseConstantList(Runner &run, const unsigned char *at)
            : ParseConstant(at), builder(run)
		{}
		Sink *kick(Runner &run);
	protected:
		ListBuilder<const Constant, const ListConstant> builder;
	};

	class ParseConstantCommaList
		: public ParseConstantList
	{
	public:
        ParseConstantCommaList(Runner &run, const unsigned char *at, const Constant *element)
            : ParseConstantList(run, at)
		{
			builder.add(element);
		}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
		const Step *comma(Runner &run, Parsing &parsing);
	};

	class ParseConstantShortList
		: public ParseConstantList
	{
	public:
        ParseConstantShortList(Runner &run, const unsigned char *at, const Constant *first, const Constant *second)
            : ParseConstantList(run, at)
		{
			builder.add(first);
			builder.add(second);
		}
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level);
	};

	class ParseCliche
		: public ParseConstant
	{
	public:
		ParseCliche(const unsigned char *at, const Constant *head)
			: ParseConstant(at), builder(head)
		{}
		Sink *kick(Runner &run);
		const Step *endSquare(Runner &run, Parsing &parsing);
		const Step *endSquareNodehead(Runner &run, Parsing &parsing);
		const Step *bar(Runner &run, Parsing &parsing);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
	private:
		ClicheBuilder builder;
	};

	class ParseLabel
		: public Parse
	{
	public:
		ParseLabel(const unsigned char *at, int index)
			: Parse(at), index(index)
		{}
		Sink *kick(Runner &run);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value);
		void close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value);
		const Step *constant(Runner &run, Parsing &parsing, const Constant *constant);
		const Step *nodehead(Runner &run, Parsing &parsing, const Constant *head);
	private:
		int index;
	};
}
#endif
