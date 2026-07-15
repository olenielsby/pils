/* This file is public domain */
#pragma once
#include <memory>
#include "pilsmutex.h"
#include "pilsatomic.h"

#ifdef PILS_CHAR_IS_UTF16
typedef wchar_t PILS_CHAR;
#else
typedef char PILS_CHAR;
#endif

#define _PS(x) x

namespace PILS
{
	class Runner;
	class Sink;

	/* The Step class provides a shared ground for stepping through
	   PILS code.

	   Usually, a Step is an uncounted PILS expression about to be
	   evaluated.
	*/

	class Step
	{
	public:
        virtual ~Step();
		virtual const Step *step_(Runner &run) const = 0;
	protected:
		Step()
		{}
	};

	class Writing;

	enum WriteState
	{
		WRITING_EXPRESSION,
		WRITING_ATTRIBUTE,
		WRITING_ELEMENT,
		WRITING_COMPARAND,
		WRITING_ADDEND,
		WRITING_SEQUEL,
		WRITING_OPERAND,
		WRITING_ARGUMENT,
		WRITING_DOT_ARGUMENT,
		WRITING_NAME,
		WRITING_CONSTANT,
		WRITING_CONSTANT_ATTRIBUTE,
		WRITING_CONSTANT_ELEMENT,
		WRITING_CONSTANT_SHORT_ELEMENT
	};

	enum NameSkin
	{
		NAMESKIN_NONE,
		NAMESKIN_STRING,
		NAMESKIN_NAME,
		NAMESKIN_ASTERISKED,
		NAMESKIN_OPERATOR,
		NAMESKIN_ADDITION,
		NAMESKIN_RELATION,
		NAMESKIN_JOKER
	};

	class Any;
	class Call;
	class CallWho;
	class Escape;
    class Constant;
	class ListConstant;
	class NodeConstant;
	class NodeConstantTiny;
    class PlatformSpecializedNodeConstantTiny;
	class Empty;
	class Express;
	class ListExpress;
	class NodeExpress;
	class Integer;
	class Float;
	class PilsDate;
	class Timestamp;
	class Duration;
	class Cliche;
	class Special;
	class ReallySpecial;
	class SpecialLookup;
	class Slot;
	class ClicheShort;
	class ClicheTiny;
	class Rule;
	class Ruleset;
	class PilsString;
	class Compiling;
	class CompilingBuild;
	class QuickCalling;
	class QuickMatch;
	class WhoAssign;
	class Channel;
	class Language;
	class PilsColor;
    class Closure;

	class Converter
	{
	public:
		virtual bool convert(const Integer &value);
		virtual bool convert(const Float &value);
		virtual bool convert(const PilsDate &value);
		virtual bool convert(const Timestamp &value);
		virtual bool convert(const Duration &value);
		virtual bool convert(const PilsString &value);
		virtual bool convert(const Cliche &value);
        virtual bool convert(const Cliche &cliche, const Any *const *value);
        virtual bool convert(const Any *const *element, size_t count);
        virtual bool convert(const ReallySpecial &special);
		virtual bool convert(const PilsColor &color);
        virtual bool convert(const PlatformSpecializedNodeConstantTiny &node);
        virtual bool convert(const Closure &closure);
        static Converter dummy;
	};

    class PlatformSpecificConverter;

	class InterfaceDesignator;

	class Recognizer;

	class Any
		: public Step
	{
        LIVE_OBJECT_COUNT
    public:
        static void* operator new(size_t baseSize, size_t extra)
        {
            return ::operator new(baseSize + extra);
        }
        static void* operator new(size_t size)
        {
            return ::operator new(size);
        }
        static void operator delete(void* p) noexcept
        {
            ::operator delete(p);
        }
        // DEN VIGTIGE:
        static void operator delete(void* p, size_t) noexcept
        {
            ::operator delete(p);
        }
        bool duplicateReferenceNoChildren() const;
        // virtual bool isMultipleReferenced() const;
	protected:
		Any();
        bool duplicateReference() const;
        bool duplicateReference(bool copying) const;
        virtual void unduplicateChildren() const;
        friend class Writing;
        friend class Runner;
        friend class DeletionQueue;
        mutable RefcountOrScrap<Any> refcount;
    public:
        void unduplicateReference() const;
        inline bool releaseIfMultipleReferenced() const {return refcount.releaseIfMultipleReferenced();}
        void retain() const;
        // void releaseReferenceInsideLock() const; // DEPRECATED
        // void releaseFromScrap(const Any &scrap) const;
        virtual void unlink() {}
        virtual void removeFromHashTable() const = 0;
        // virtual void releaseChildren() const {}
        virtual bool write(Writing &writing, WriteState state, long level, const Constant *dot) const = 0;
        virtual const Any *labeling(Writing &writing) const;
        virtual const Call *callHere() const;
        virtual const CallWho *callWho(const Any *who) const;
        virtual const Escape *escape() const;
        virtual bool isNode(const Any *const *&element, const Cliche *&cliche) const;
        virtual bool isList(const Any *const *&element, const Integer *&count) const;
        virtual bool isList(const Any *const *&element, size_t &count) const;
        virtual bool isNumber(double &number) const;
        bool isNumber(float &number) const;
		virtual const Step *caller(Runner &run, const Any &where_) const = 0;
        virtual const Step *calling(Runner &run, const Constant &call) const;
        virtual const Step *calling(Runner &run, const Integer &call) const;
        virtual const Step *calling(Runner &run, const ListConstant &call) const ;
        virtual const Step *calling(Runner &run, const NodeConstant &call) const;
        virtual const Step *calling(Runner &run, const Empty &call) const;
        virtual const Step *calling(Runner &run, const ListExpress &call) const;
        virtual const Step *calling(Runner &run, const NodeExpress &call) const;
        virtual const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
        virtual const Any *specialCall(Runner &run, const ReallySpecial &special) const;
        virtual const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		virtual const Step *passUncounted(Runner &run) const = 0;
		virtual const Step *passCounted(Runner &run) const = 0;
        virtual const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
        virtual const Constant *as_Constant() const;
        virtual const ClicheShort *as_ClicheShort() const;
        virtual const ClicheTiny *as_ClicheTiny() const;
        virtual const Cliche *as_Cliche() const;
        virtual const NodeConstant *as_NodeConstant() const;
        virtual const NodeConstantTiny *as_NodeConstantTiny() const;
        virtual const Channel *as_Channel() const;
        virtual const ListConstant *as_ListConstant() const;
        virtual const Language *as_Language() const;
        virtual const NodeExpress *as_NodeExpress() const;
        virtual const Rule *as_Rule() const;
        virtual const Ruleset *as_Ruleset() const;
        virtual const Slot *as_Slot() const;
        virtual const Duration *as_Duration() const;
        virtual const Timestamp *as_Timestamp() const;
        virtual const PilsDate *as_PilsDate() const;
        virtual const PilsString *as_String() const;
        virtual const Integer *as_Integer() const;
        virtual void compileRulePattern(Compiling &compiling, const Rule &rule) const;
        virtual void compilePattern(Compiling &compiling) const;
        virtual void compilePattern(Compiling &compiling, size_t offset) const;
        virtual void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
        virtual void compileNodecheckPattern(Compiling &compiling) const;
        virtual void compileAction(Compiling &compiling) const;
		virtual bool compileBuild(CompilingBuild &compiling) const = 0;
		virtual const void *compilePatternIndex() const = 0;
		virtual const void *callingIndex() const = 0;
		virtual const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const = 0;
        virtual const Express *findCatchTag() const;
        virtual const Express *findCatchTag(const Constant &tag) const;
		virtual bool convert(Converter &converter) const = 0;
        virtual bool platformConvert(PlatformSpecificConverter &converter) const {return false;}
        virtual bool recognize(Recognizer &recognizer) const;
        void writeToDebugOutput(int levels) const;
        void writingToDebugOutputNextLevel(int level) const;
    protected:
        void releaseChild(const Any *child) const;
        virtual void writingToDebugOutput(int level) const;
	private:
        Any *destroy(Runner &run);
		friend class Special;
        void disposeRoot(Runner &run);
	};

	class Number;
	class ShortInteger;
	class ClicheLong;
	class ClicheTrailer;
	class NodeConstantShort;
	class NodeConstantLong;
    class Constant;

    class Constant : public Any
	{
	public:
        virtual const ClicheShort *newCliche(const Constant *&link, const Constant *a) const;
        virtual const ClicheLong *newCliche(const Constant *&link, const Constant *const *a, size_t c) const;
        virtual const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const = 0;
        void removeFromHashTable() const override;
        const Call *callHere() const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        void compilePattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        const void *compilePatternIndex() const override;
        const void *callingIndex() const override;
        virtual int order(const Constant *other) const;
        virtual int ordering(double first) const;
        virtual int ordering(const PilsString *first) const;
        virtual int ordering(const ListConstant *first) const;
        virtual int ordering() const;
	public:
        void unlink() override;
        mutable const Constant *hashLink;
        const Constant *as_Constant() const override;
        virtual const Integer *hashLookup(long v) const;
        virtual const PilsString *hashLookup(const PILS_CHAR *text, size_t count) const;
        virtual const Float *hashLookup(double v) const;
        virtual const PilsColor *hashLookupPilsColor(unsigned int v) const;
        virtual const PilsDate *hashLookupPilsDate(long long v) const;
        virtual const Timestamp *hashLookupTimestamp(long long v) const;
        virtual const Duration *hashLookupDuration(long long v) const;
        virtual const ClicheShort *hashLookup(const Constant *h, const Constant *a) const;
        virtual const ClicheLong *hashLookup(const Constant *h, const Constant *const *a, size_t c) const;
        virtual const NodeConstantShort *hashLookup(const ClicheShort &cliche, const Constant *value) const;
        virtual const NodeConstantLong *hashLookup(const ClicheLong &cliche, const Constant *const *value) const;
        virtual const ListConstant *hashLookup(const Constant *const *a, size_t c, bool copying) const;
        virtual const ReallySpecial *hashLookup(SpecialLookup &lookup) const;
        static const Constant *&hashChain(size_t hash);
        const ClicheTiny *clichefy() const;
        const ClicheShort *clichefy(const Constant *attribute) const;
        const ClicheShort *clichefyInsideLock(const Constant *attribute) const;
        const ClicheLong *clichefy(const Constant *const *attribute, size_t count) const;
    protected:
        virtual const ClicheShort *clichefying(const Constant *attribute) const;
        virtual const ClicheTiny *clichefying() const;
        virtual const ClicheLong *clichefying(const Constant *const *attribute, size_t count) const;
        virtual const ClicheTiny *newCliche() const;
        explicit Constant(const Constant *&link);
        Constant();
        void unhash();
        friend class SpecialLookup;
    private:
		friend class Integer;
		static const ShortInteger hashTable[0x10000];
	};

    /* Abstract class for Integer and Float. On unification, floating
       point values will be converted to Integer if possible without
	   loss.
	*/

	class Number
        : public Constant
	{
	public:
        using Constant::isNumber;
		static const Number *get(double v);
        int ordering(const PilsString *first) const override;
        int ordering(const ListConstant *first) const override;
        int ordering() const override;
        bool isNumber(double &number) const override = 0;
	protected:
        explicit Number(const Constant *&link)
            : Constant(link)
		{}
		Number()
		{}
	};

	class Integer
		: public Number
	{
	public:
		long value;
        Integer(const Constant *&link, long v)
			: Number(link), value(v)
		{}
        using Number::ordering;
        const Integer *hashLookup(long v) const override;
        static const Integer *get(long v);
        static const Integer *getInsideLock(long v);
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Step *step_(Runner &run) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run)const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const override;
        bool convert(Converter &converter) const override;
        int order(const Constant *other) const override;
        int ordering(double first) const override;
        const Integer *as_Integer() const override;
        bool isNumber(double &number) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
        bool recognize(Recognizer &recognizer) const override;
	protected:
        explicit Integer(long v)
			: value(v)
		{}
	};

	class ShortInteger
		: public Integer
	{
	public:
		ShortInteger()
			: Integer(initial++)
		{}
        const Integer *hashLookup(long v) const override;
        const PilsString *hashLookup(const PILS_CHAR *text, size_t c) const override;
        const Float *hashLookup(double v) const override;
        const PilsColor *hashLookupPilsColor(unsigned int v) const override;
        const PilsDate *hashLookupPilsDate(long long v) const override;
        const Timestamp *hashLookupTimestamp(long long v) const override;
        const Duration *hashLookupDuration(long long v) const override;
        const ClicheLong *hashLookup(const Constant *h, const Constant *const *a, size_t c) const override;
        const ClicheShort *hashLookup(const Constant *h, const Constant *a) const override;
        const NodeConstantShort *hashLookup(const ClicheShort &cliche, const Constant *value) const override;
        const NodeConstantLong *hashLookup(const ClicheLong &cliche, const Constant *const *value) const override;
        const ListConstant *hashLookup(const Constant *const *a, size_t c, bool copying) const override;
        const ReallySpecial *hashLookup(SpecialLookup &lookup) const override;
	private:
		static long initial;
	};

	class Float
		: public Number
	{
	public:
		double value;
        Float(const Constant *&link, double v)
			: Number(link), value(v)
		{}
        using Number::ordering;
        const Float *hashLookup(double v) const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        int order(const Constant *other) const override;
        int ordering(double first) const override;
        bool isNumber(double &number) const override;
        bool recognize(Recognizer &recognizer) const override;
		struct Split
		{
			long long mantissa;
			long exponent;
            double get() const;
			void put(double value);
			void resetAndReadIntegerDigits(const unsigned char *&at, const unsigned char *end);
			void readFractionDigits(const unsigned char *&at, const unsigned char *end);
			void resetAndReadHexadecimalDigits(const unsigned char *&at, const unsigned char *end);
		};
	};

	/* RGBA color values
	*/

	class PilsColor
        : public Constant
	{
	public:
        PilsColor(const Constant *&link, unsigned int value)
            : Constant(link), value(value)
		{}
		static const PilsColor *get(unsigned int v);
        const PilsColor *hashLookupPilsColor(unsigned int v) const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        bool recognize(Recognizer &recognizer) const override;
		unsigned int value;
	};

	class Timevalue
        : public Constant
	{
	public:
		struct DatepartSplit
		{
			unsigned short year;
			unsigned short month;
			unsigned short day;
		};
		struct ClockpartSplit
		{
			unsigned short hour;
			unsigned short minute;
			unsigned short second;
			unsigned long millisecond;
		};
		struct ZonepartSplit
		{
			bool hasZone;
			long zoneSecond;
		};
        const Step *passUncounted(Runner &run) const override;
        const Step *step_(Runner &run) const override;
		long long value;
	protected:
        Timevalue(const Constant *&link, long long value)
            : Constant(link), value(value)
		{}
	};

	class Timestamp
		: public Timevalue
	{
	public:
        Timestamp(const Constant *&link, long long value)
			: Timevalue(link, value)
		{}
        const Timestamp *as_Timestamp() const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        const Timestamp *hashLookupTimestamp(long long value) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        int order(const Constant *other) const override;
		struct Split : DatepartSplit, ClockpartSplit
		{
			long zoneSecond;
			long long get();
			void put(long long time);
		};
		static const Timestamp *get(long long value);
        static long long stamp;
	};
		
	class Duration
		: public Timevalue
	{
	public:
        Duration(const Constant *&link, long long value)
			: Timevalue(link, value)
		{}
        const Duration *as_Duration() const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        const Duration *hashLookupDuration(long long value) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        int order(const Constant *other) const override;
		struct Split : ClockpartSplit
		{
			long days;
			long long get();
			void put(long long time);
		};
		static const Duration *get(long long value);
	};

	class PilsDate
		: public Timevalue
	{
	public:
        PilsDate(const Constant *&link, long long value)
			: Timevalue(link, value)
		{}
        const PilsDate *as_PilsDate() const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        const PilsDate *hashLookupPilsDate(long long value) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        int order(const Constant *other) const override;
        const Step *passCounted(Runner &run) const override;
		struct Split : DatepartSplit, ClockpartSplit
		{
			long long get();
			long long getTimestampFromLocalTime();
			void put(long long time);
		};
		static const PilsDate *get(long long value);
	};

	/* The CountedConstant is a base for const PilsString and
	   const ListConstant.

	   To facilitate extraction of counts in patterns, the
	   counts are stored as boxed integers.

	   Note: the counts are not included in unduplicateChildren()
	   because the boxing is postponed till creation.
	*/

	class CountedConstant
        : public Constant
	{
	protected:
        CountedConstant(const Constant *&link, size_t c);
	public:
        ~CountedConstant();
        const Integer *const count;
	};

    /* Strings of any length - a limit must be set elsewhere */

    class PilsString
		: public CountedConstant
	{
	public:
		/* Auxillary classes for converting to UTF-32 and UTF-16
		 * When converting to COM BSTR, 2 passes are made: first,
		 * compute the length for allocation, then write the wchars.
		 */
		class UTF32pass
		{
		public:
			bool pass(const PilsString &string);
		private:
			virtual bool put(unsigned long c) = 0;
		};
		class UTF16pass : public UTF32pass
		{
		private:
            bool put(unsigned long c) override;
			virtual bool put(unsigned short c) = 0;
		};
		class UTF16count : public UTF16pass
		{
		public:
			UTF16count() : count(0) {}
			size_t count;
		private:
            bool put(unsigned short c) override;
		};
		class UTF16write : public UTF16pass
		{
		public:
			UTF16write(unsigned short *at) : at(at) {}
		private:
			unsigned short* at;
            bool put(unsigned short c) override;
		};

        PilsString(const Constant *&link, const PILS_CHAR *text, size_t c);
#ifndef NDEBUG
        const std::string bug;
#endif
        const PILS_CHAR value[];
        const PilsString *hashLookup(const PILS_CHAR *text, size_t c) const override;
        static const PilsString *get(const PILS_CHAR *text, size_t count);
		static const PilsString *get(const PILS_CHAR *text);
        static const PilsString *getInsideLock(const PILS_CHAR *text, size_t count);
        static const PilsString *getInsideLock(const PILS_CHAR *text);
        static const PilsString *get(const std::string &text);
#ifndef PILS_CHAR_IS_UTF16
		static const PilsString *get(const wchar_t *text, size_t count);
		static const PilsString *get(const wchar_t *text);
#endif
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        NameSkin nameSkin() const;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const PilsString* as_String() const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const override;
        bool convert(Converter &converter) const override;
        bool less(const PilsString &other) const;
		static const std::locale defaultLocale;
        int order(const Constant *other) const override;
        int ordering(const PilsString *first) const override;
        int ordering(const ListConstant *first) const override;
        int ordering() const override;
        bool recognize(Recognizer &recognizer) const override;
        void writingToDebugOutput(int level) const override;
	protected:
		PilsString(const PILS_CHAR *text, size_t count);
	private:
        static const Constant *&hashChain(const PILS_CHAR *text, size_t count);
	};

	class Cliche
        : public Constant
	{
	public:
		size_t count;
        const Constant *head;
        const Constant *attributes[1];
        ~Cliche();
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        const NodeConstant *nodeConstant(const Constant *const *attributes) const;
		virtual const Any *node(const Any *const *element) const = 0;
        virtual const Any *node(const Constant *const *element) const = 0;
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        const Cliche *as_Cliche() const override;
        const Constant *lookupNonempty(const NodeConstant *node, size_t start, const Constant *key) const;
        const Any *lookupNonempty(const NodeExpress *node, size_t start, const Constant *key) const;
        void writingToDebugOutput(int level) const override;
    protected:
        Cliche(const Constant *&link, const Constant *h, const Constant *const *a, size_t c);
        Cliche(const Constant *h, const Constant *a1, const Constant *a2);
        Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3);
        Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4);
        virtual const NodeConstant *nodifyingConstant(const Constant *const *attributes) const = 0;
	private:
        static const Constant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2);
        static const Constant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3);
        static const Constant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4);
	};

	class ListConstant :
		public CountedConstant
	{
	public:
        const Constant *element[1];
        const ListConstant *as_ListConstant() const override;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        const ListConstant *hashLookup(const Constant *const *a, size_t c, bool copying) const override;
        ListConstant(const Constant *&link, const Constant *const *a, size_t c, bool copying);
        ~ListConstant();
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        static const ListConstant *get(const Constant *const *e, size_t c, bool copying = false);
        bool isList(const Any *const *&element, const Integer *&count) const override;
        const Step *step_(Runner &run) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        int order(const Constant *other) const override;
        int ordering(const ListConstant *first) const override;
        int ordering() const override;
        bool recognize(Recognizer &recognizer) const override;
	protected:
        void unduplicateChildren() const override;
        const void *compilePatternIndex() const override;
        const void *callingIndex() const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
	};

	class Empty :
		public ListConstant
	{
	public:
        using ListConstant::newCliche;
		static const Empty singleton;
        static const Empty *get() {singleton.retain(); return &singleton;}
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        const Call *callHere() const override;
        const ClicheLong *newCliche(const Constant *&link, const Constant *const *a, size_t c) const override;
        const ClicheShort *newCliche(const Constant *&link, const Constant *a) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        void writingToDebugOutput(int level) const override;
	private:
		Empty();
	};

	class NodeExpressShort;

    class ClicheShort
		: public Cliche
	{
	public:
        const ClicheShort *hashLookup(const Constant *h, const Constant *a) const override;
        ClicheShort(const Constant *&link, const Constant *h, const Constant *a)
			: Cliche(link, h, &a, 1)
		{}
        virtual const NodeConstantShort *newNode(const Constant *&link, const Integer *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const Float *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const PilsColor *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const Timestamp *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const Duration *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const PilsDate *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const PilsString *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const Cliche *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const NodeConstant *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const ListConstant *value) const;
        virtual const NodeConstantShort *newNode(const Constant *&link, const Special *value) const;
        static const Constant *&hashChain(const Constant *h, const Constant *a);
        const NodeConstantShort *nodeConstant(const Constant *const *attributes) const;
        virtual const NodeConstantShort *nodeConstant(const Constant *attribute) const;
        const Any *node(const Any *element) const;
        virtual const Any *node(const Constant *element) const;
        virtual const NodeExpressShort *node(const Express *element) const;
        virtual const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
        const Any *node(const Any *const *element) const override;
        const Any *node(const Constant *const *element) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        const ClicheShort* as_ClicheShort() const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const override;
	protected:
        ClicheShort(const Constant *h, const Constant *a)
			: Cliche(hashChain(h, a), h, &a, 1)
		{}
        void unduplicateChildren() const override;
        const NodeConstant *nodifyingConstant(const Constant *const *attributes) const override;
	private:
        static const Constant *&link(const Constant *h, const Constant *a);
	};

	class ClicheTiny
		: public ClicheShort
	{
	public:
		using ClicheShort::node;
        explicit ClicheTiny(const Constant *h);
        const ClicheShort *hashLookup(const Constant *h, const Constant *a) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Integer *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Float *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsDate *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsColor *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Timestamp *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Duration *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const PilsString *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Cliche *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const NodeConstant *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const ListConstant *value) const override;
        const NodeConstantShort *newNode(const Constant *&link, const Special *value) const override;
        const NodeExpressShort *node(const Express *element) const override;
        virtual void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
        const ClicheTiny* as_ClicheTiny() const override;
        virtual const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const;
        virtual const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument, const Any &assignValue) const;
	protected:
        void unduplicateChildren() const override;
	};

	class EmptyClicheShort
		: public ClicheShort
	{
	public:
        EmptyClicheShort(const Constant *&link, const Empty *h, const Constant *a)
			: ClicheShort(link, h, a)
		{}
        const Any *node(const Constant *element) const override;
	private:
		friend class PokerHead;
        EmptyClicheShort(const Empty *h, const Constant *a)
			: ClicheShort(h, a)
		{}
	};

	class PokerHead
		: public EmptyClicheShort
	{
	public:
        using EmptyClicheShort::newCliche;
        const ClicheShort* newCliche(const Constant *&link, const Constant *a) const override;
        const ClicheLong* newCliche(const Constant *&link, const Constant *const *a, size_t c) const override;
		static const PokerHead singleton;
	private:
        explicit PokerHead(const Constant &action)
			: EmptyClicheShort(&Empty::singleton, &action)
		{}
	};

	class PokerClicheShort:
		public ClicheShort
	{
	public:
        PokerClicheShort(const Constant *&link, const Constant *a);
        const Any *node(const Constant *element) const override;
        const NodeExpressShort *node(const Express *element) const override;
	protected:
        explicit PokerClicheShort(const Constant *a)
			: ClicheShort(&PokerHead::singleton, a)
		{}
	};

	/* The const Empty::singleton must always be first in attribute sorting
	   order. Since there is no guarantee that the singleton will be
	   allocated above or belove heap memory, empty list is handled separately
	   when building or sorting cliches.
	*/

	class JumperHead
		: public ClicheTiny
	{
	public:
        using ClicheTiny::newCliche;
        using ClicheTiny::node;
		static const JumperHead singleton;
        const ClicheLong *newCliche(const Constant *&link, const Constant *const *a, size_t c) const override;
        const Any *node(const Constant *element) const override;
        void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const override;
	private:
		JumperHead()
			: ClicheTiny(&Empty::singleton)
		{}
	};

	class JumperCliche0
		: public ClicheTiny
	{
	public:
        const Any *node(const Constant *element) const override;
        const NodeExpressShort *node(const Express *element) const override;
		static const JumperCliche0 singleton;
	protected:
        JumperCliche0(const Constant *head)
			: ClicheTiny(head)
		{}
	private:
		JumperCliche0()
			: ClicheTiny(&JumperHead::singleton)
		{}
	};

	class ClicheLong
		: public Cliche
	{
	protected:
        void unduplicateChildren() const override;
	public:
        const ClicheLong *hashLookup(const Constant *h, const Constant *const *a, size_t c) const override;
        ClicheLong(const Constant *&link, const Constant *h, const Constant *const *a, size_t c);
        virtual const NodeConstantLong *newNodeConstant(const Constant *&link, const Constant *const *value) const;
        virtual const NodeConstantLong *nodeConstant(const Constant *const *attributes) const;
        const Any *node(const Any *const *element) const override;
        const Any *node(const Constant *const *element) const override;
	protected:
        const NodeConstant *nodifyingConstant(const Constant *const *attributes) const override;
        ClicheLong(const Constant *h, const Constant *a1, const Constant *a2)
			: Cliche(h, a1, a2)
		{}
        ClicheLong(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3)
			: Cliche(h, a1, a2, a3)
		{}
        ClicheLong(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4)
			: Cliche(h, a1, a2, a3, a4)
		{}
	};

	class EmptyClicheLong
		: public ClicheLong
	{
	public:
        EmptyClicheLong(const Constant *&link, const Empty *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
        const Any *node(const Constant *const *element) const override;
	protected:
        EmptyClicheLong(const Empty *h, const Constant *a1, const Constant *a2)
			: ClicheLong(h, a1, a2)
		{}
	};

	class ClicheTrailer
		: public ClicheLong
	{
		using ClicheLong::node;
	public:
        ClicheTrailer(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
        const NodeConstantLong *newNodeConstant(const Constant *&link, const Constant *const *value) const override;
        const Any *node(const Any *const *elements) const override;
	protected:
        ClicheTrailer(const Constant *h, const Empty *a1, const Constant *a2)
			: ClicheLong(h, a1, a2)
		{}
        ClicheTrailer(const Constant *h, const Empty *a1, const Constant *a2, const Constant *a3)
			: ClicheLong(h, a1, a2, a3)
		{}
        ClicheTrailer(const Constant *h, const Empty *a1, const Constant *a2, const Constant *a3, const Constant *a4)
			: ClicheLong(h, a1, a2, a3, a4)
		{}
	};

	class PokerClicheLong
		: public ClicheLong
	{
	public:
        PokerClicheLong(const Constant *&link, const Constant *const *a, size_t c);
        const Any *node(const Any *const *element) const override;
        const Any *node(const Constant *const *element) const override;
	protected:
        PokerClicheLong(const Constant *a1, const Constant *a2)
			: ClicheLong(&PokerHead::singleton, a1, a2)
		{}
        PokerClicheLong(const Constant *a1, const Constant *a2, const Constant *a3)
			: ClicheLong(&PokerHead::singleton, a1, a2, a3)
		{}
	};

	class PokerClicheTrailer:
		public ClicheTrailer
	{
	public:
        PokerClicheTrailer(const Constant *&link, const Constant *const *a, size_t c);
        const Any *node(const Any *const *element) const override;
        const Any *node(const Constant *const *element) const override;
	protected:
        PokerClicheTrailer(const Empty *a1, const Constant *a2)
			: ClicheTrailer(&PokerHead::singleton, a1, a2)
		{}
        PokerClicheTrailer(const Empty *a1, const Constant *a2, const Constant *a3)
			: ClicheTrailer(&PokerHead::singleton, a1, a2, a3)
		{}
        PokerClicheTrailer(const Empty *a1, const Constant *a2, const Constant *a3, const Constant *a4)
			: ClicheTrailer(&PokerHead::singleton, a1, a2, a3, a4)
		{}
	};

	class BindCliche:
		public ClicheTrailer
	{
	public:
        BindCliche(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheTrailer(link, h, a, c)
		{}
        const Any *node(const Constant *const *element) const override;
        const Any *node(const Any *const *element) const override;
	};

	class BindCliche1:
		public BindCliche
	{
	public:
        BindCliche1(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	private:
        const Constant *dummy;
	};

	class BindCliche2:
		public BindCliche
	{
	public:
        BindCliche2(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	private:
        const Constant *dummy[2];
	};

	class BindCliche3:
		public BindCliche
	{
	public:
        BindCliche3(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	private:
        const Constant *dummy[3];
	};

	class JumperCliche:
		public BindCliche
	{
	public:
        JumperCliche(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	};

	class JumperCliche1:
		public BindCliche1
	{
	public:
        JumperCliche1(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche1(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	};

	class JumperCliche2:
		public BindCliche2
	{
	public:
        JumperCliche2(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche2(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	};

	class JumperCliche3:
		public BindCliche3
	{
	public:
        JumperCliche3(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche3(link, h, a, c)
		{}
        const Any *node(const Any *const *element) const override;
	};

	class NodeConstant
        : public Constant
	{
	public:
		const Cliche *cliche;
        const Constant *element[1];
        ~NodeConstant();
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        bool isNode(const Any *const *&element, const Cliche *&cliche) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        const NodeConstant *as_NodeConstant() const override;
        const void *compilePatternIndex() const override;
        const void *callingIndex() const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
        bool convert(Converter &converter) const override;
        virtual const Constant *getAttribute(const Constant &name) const;
        void writingToDebugOutput(int level) const override;
	protected:
        NodeConstant(const Constant *&link, const Cliche &cliche);
	};

	class NodeConstantShort
		: public NodeConstant
	{
	public:
        const NodeConstantShort *hashLookup(const ClicheShort &cliche, const Constant *value) const override;
        NodeConstantShort(const Constant *&link, const ClicheShort &cliche, const Constant *value);
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Escape* escape() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	protected:
        void unduplicateChildren() const override;
	};

	class NodeConstantTiny
		: public NodeConstantShort
	{
	public:
        NodeConstantTiny(const Constant *&link, const ClicheTiny &cliche, const Constant *value)
			: NodeConstantShort(link, cliche, value)
		{}
        const NodeConstantTiny *as_NodeConstantTiny() const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
	};

	class NodeConstantLong
		: public NodeConstant
	{
	public:
        const NodeConstantLong *hashLookup(const ClicheLong &cliche, const Constant *const *value) const override;
        NodeConstantLong(const Constant *&link, const ClicheLong &cliche, const Constant *const *value);
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Escape* escape() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	protected:
        void unduplicateChildren() const override;
	};

	class NodeConstantTrailer
		: public NodeConstantLong
	{
	public:
        NodeConstantTrailer(const Constant *&link, const ClicheLong &cliche, const Constant *const *element)
			: NodeConstantLong(link, cliche, element)
		{}
        const Escape *escape() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Constant *getAttribute(const Constant &name) const override;
	};

	class EscapeCliche
		: public ClicheTiny
	{
	public:
        const Any *node(const Constant *element) const override;
        const NodeExpressShort *node(const Express *element) const override;
		static const EscapeCliche singleton;
	private:
		EscapeCliche()
			: ClicheTiny(&PokerHead::singleton)
		{}
	};

	class Express
		: public Any
	{
    public:
        void removeFromHashTable() const override {}
	};

	class TypecheckPropertyCount;
	class BuiltinClicheStrap;

	class Strap
		: public NodeConstantTiny
	{
	public:
        Strap(const Constant *&link, const BuiltinClicheStrap &cliche, const Constant *value);
		class Sticker
		{
		public:
			~Sticker();
            Sticker(Runner &run) : run(run) {} //TODO: make threadsafe and use current thread runner
            void stick(const Strap &strap);
            void clear();
        protected:
            Runner &run;
		private:
			std::set<const Strap*> stuck;
		};
	private:
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        void unstick(Runner &run) const;
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
		mutable size_t stickCount;
		mutable const Any *mind;
        const Any *get() const;
	};

	class Pipesource;

	class Special
        : public Constant
	{
	public:
        const ReallySpecial *hashLookup(SpecialLookup &lookup) const override;
        const Special *unique() const;
        const NodeConstantShort *newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const override;
        const Step *step_(Runner &run) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        bool convert(Converter &converter) const override;
        virtual const Any *specialCalling(Runner &run, const Integer &call) const;
        virtual const Any *specialCalling(Runner &run, const Integer &call, const Any &AssignValue) const;
        virtual const Any *specialCalling(Runner &run, const PilsString &call) const;
        virtual const Any *specialCalling(Runner &run, const PilsString &call, const Any &AssignValue) const;
        virtual const Any *specialCalling(Runner &run, const Constant &nameWhat) const;
        virtual const Any *specialCalling(Runner &run, const Strap &call) const;
        virtual const Any *getWhen() const {return nullptr;}
        virtual const Constant *type() const;
        bool write(Writing &writing, WriteState state, long level, const Constant *dot) const override;
        virtual bool enumerate(Runner &run) const;
        virtual const Any *queryInterface(const InterfaceDesignator &designator) const;
	private:
		virtual void write(Writing &writing) const = 0;
		friend class ReallySpecial;
        explicit Special(const Constant *&link) : Constant(link) {}
        Special() {}
	};

	/* abstract class for looking up wrappers for special values */

	class SpecialLookup
	{
	public:
        virtual const ReallySpecial *newSpecial(const Constant *&link) = 0;
		virtual bool compare(const ReallySpecial &special) const = 0;
        virtual void unduplicate() {};
		virtual size_t hash() const = 0;
		const ReallySpecial *lookup();
		virtual ~SpecialLookup() {}
	};

	class ListExpress
		: public Express
	{
	public:
		const Integer *count;
		const Any *element[1];
        ~ListExpress();
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        bool isList(const Any *const *&element, const Integer *&count) const override;
		ListExpress(const Any *const *element, size_t count);
        const Step *step_(Runner &run) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        const void *compilePatternIndex() const override;
        const void *callingIndex() const override;
        void compilePattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        bool convert(Converter &converter) const override;
        bool recognize(Recognizer &recognizer) const override;
	};

	class NodeExpress
		: public Express
	{
	public:
        ~NodeExpress();
        const Cliche *cliche;
		const Any *element[1];
        bool write (Writing &writing, WriteState state, long level, const Constant *dot) const override;
        const Any *labeling(Writing &writing) const override;
        bool isNode(const Any *const *&element, const Cliche *&cliche) const override;
        const Step *caller(Runner &run, const Any &where_) const override;
        const NodeExpress* as_NodeExpress() const override;
        const void *compilePatternIndex() const override;
        const void *callingIndex() const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
        bool convert(Converter &converter) const override;
        virtual const Any *getAttribute(const Constant &name) const;
        void writingToDebugOutput(int level) const override;
	protected:
		NodeExpress(const Cliche &cliche, const Any *value);
		NodeExpress(const Cliche &cliche, const Any *v1, const Any *v2);
		NodeExpress(const Cliche &cliche, const Any *v1, const Any *v2, const Any *v3);
		NodeExpress(const Cliche &cliche, const Any *const *value);
	};

	class NodeExpressShort
		: public NodeExpress
	{
	public:
		NodeExpressShort(const ClicheShort &cliche, const Any *value)
			: NodeExpress(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
        const CallWho* callWho(const Any *who) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        void compilePattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const override;
        const Escape* escape() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	};

	class PokerShort
		: public NodeExpressShort
	{
	public:
		PokerShort(const PokerClicheShort &cliche, const Any* value)
			: NodeExpressShort(cliche, value)
		{}
        const CallWho* callWho(const Any *who) const override;
        const Step *step_(Runner &run) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class NodeExpressTiny
		: public NodeExpressShort
	{
	public:
		NodeExpressTiny(const ClicheTiny &cliche, const Any *value)
			: NodeExpressShort(cliche, value)
		{}
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
        const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
	};

	class Jumper0
		: public NodeExpressTiny
	{
	public:
		Jumper0(const Any *element)
			: NodeExpressTiny(JumperCliche0::singleton, element)
		{}
        const Express *findCatchTag() const override;
        const Express *findCatchTag(const Constant &tag) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	protected:
		Jumper0(const ClicheTiny &cliche, const Any *element)
			: NodeExpressTiny(cliche, element)
		{}
	};

	class NodeExpressLong
		: public NodeExpress
	{
	public:
		NodeExpressLong(const ClicheLong &cliche, const Any *const *element)
			: NodeExpress(cliche, element)
		{}
		NodeExpressLong(const ClicheLong &cliche, const Any *v1, const Any *v2)
			: NodeExpress(cliche, v1, v2)
		{}
		NodeExpressLong(const ClicheLong &cliche, const Any *v1, const Any *v2, const Any *v3)
			: NodeExpress(cliche, v1, v2, v3)
		{}
        const Step *step_(Runner &run) const override;
        const Step *passUncounted(Runner &run) const override;
        const Step *passCounted(Runner &run) const override;
        void compilePattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
        const QuickCalling *matching(Runner &run, void **stack, const QuickMatch &match) const override;
        const Escape* escape() const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        virtual bool isNameValuePair(const Constant *&name, const Any *&value) const;
	};

	class NodeExpressTrailer
		: public NodeExpressLong
	{
	public:
		NodeExpressTrailer(const ClicheTrailer &cliche, const Any*const * element)
			: NodeExpressLong(cliche, element)
		{}
		NodeExpressTrailer(const ClicheTrailer &cliche, const Any* v1, const Any* v2)
			: NodeExpressLong(cliche, v1, v2)
		{}
		NodeExpressTrailer(const ClicheTrailer &cliche, const Any* v1, const Any* v2, const Any* v3)
			: NodeExpressLong(cliche, v1, v2, v3)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Escape *escape() const override;
        const Any *getAttribute(const Constant &name) const override;
	};

	class PokerLong
		: public NodeExpressLong
	{
	public:
		PokerLong(const PokerClicheLong &cliche, const Any *const *element)
			: NodeExpressLong(cliche, element)
		{}
		PokerLong(const PokerClicheLong &cliche, const Any* v1, const Any* v2)
			: NodeExpressLong(cliche, v1, v2)
		{}
		PokerLong(const PokerClicheLong &cliche, const Any* v1, const Any* v2, const Any* v3)
			: NodeExpressLong(cliche, v1, v2, v3)
		{}
        const Step *step_(Runner &run) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class PokerTrailer
		: public NodeExpressTrailer
	{
	public:
		PokerTrailer(const PokerClicheTrailer &cliche, const Any *const *element)
			: NodeExpressTrailer(cliche, element)
		{}
		PokerTrailer(const PokerClicheTrailer &cliche, const Any* v1, const Any* v2)
			: NodeExpressTrailer(cliche, v1, v2)
		{}
		PokerTrailer(const PokerClicheTrailer &cliche, const Any* v1, const Any* v2, const Any* v3)
			: NodeExpressTrailer(cliche, v1, v2, v3)
		{}
        const Step *step_(Runner &run) const override;
        void compileNodecheckPattern(Compiling &compiling) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class Bind
		: public NodeExpressTrailer
	{
	public:
		Bind(const ClicheTrailer &cliche, const Any *const *element)
			: NodeExpressTrailer(cliche, element)
		{}
        const Step *step_(Runner &run) const override;
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        const Express *findCatchTag() const override;
        const Express *findCatchTag(const Constant &tag) const override;
        bool compileBuild(CompilingBuild &compiling) const override;
	};

	class Bind1
		: public Bind
	{
	public:
        using Bind::calling;
        Bind1(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	private:
		const Any* dummy;
	};

	class Bind2
		: public Bind
	{
	public:
        using Bind::calling;
        Bind2(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	private:
		const Any* dummy[2];
	};

	class Bind3
		: public Bind
	{
	public:
        using Bind::calling;
        Bind3(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
	private:
		const Any* dummy[3];
	};

	class Jumper
		: public Bind
	{
	public:
		Jumper(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
        const Step *calling(Runner &run, const Empty &call) const override;
        const Express *findCatchTag() const override;
	};

	class Jumper1
		: public Bind1
	{
	public:
        using Bind1::calling;
		Jumper1(const ClicheTrailer &cliche, const Any *const *element)
			: Bind1(cliche, element)
		{}
        const Step *calling(Runner &run, const Empty &call) const override;
        const Express *findCatchTag() const override;
	};

	class Jumper2
		: public Bind2
	{
	public:
        using Bind2::calling;
        Jumper2(const ClicheTrailer &cliche, const Any *const *element)
			: Bind2(cliche, element)
		{}
        const Step *calling(Runner &run, const Empty &call) const override;
        const Express *findCatchTag() const override;
	};

	class Jumper3
		: public Bind3
	{
	public:
        using Bind3::calling;
		Jumper3(const ClicheTrailer &cliche, const Any *const *element)
			: Bind3(cliche, element)
		{}
        const Step *calling(Runner &run, const Empty &call) const override;
        const Express *findCatchTag() const override;
	};

	/* Builtin cliches in general */

	class BuiltinClicheTiny
		: public ClicheTiny
	{
	protected:
        BuiltinClicheTiny(const Constant *head)
			: ClicheTiny(head)
		{}
	};

	class BuiltinClicheLong
		: public ClicheLong
	{
	protected:
        BuiltinClicheLong(const Constant *name, const Constant *n1, const Constant *n2)
			: ClicheLong(name, n1, n2)
		{}
        BuiltinClicheLong(const Constant *name, const Constant *n1, const Constant *n2, const Constant *n3)
			: ClicheLong(name, n1, n2, n3)
		{}
	};

	class BuiltinClicheTrailer
		: public ClicheTrailer
	{
	protected:
        BuiltinClicheTrailer(const Constant *name, const Empty *n1, const Constant *n2)
			: ClicheTrailer(name, n1, n2)
		{}
        BuiltinClicheTrailer(const Constant *name, const Empty *n1, const Constant *n2, const Constant *n3)
			: ClicheTrailer(name, n1, n2, n3)
		{}
        BuiltinClicheTrailer(const Constant *name, const Empty *n1, const Constant *n2, const Constant *n3, const Constant *n4)
			: ClicheTrailer(name, n1, n2, n3, n4)
		{}
	};

	class BuiltinPokerClicheLong
		: public PokerClicheLong
	{
	protected:
        BuiltinPokerClicheLong(const Constant *const *name, size_t count);
        BuiltinPokerClicheLong(const Constant *n1, const Constant *n2)
			: PokerClicheLong(n1, n2)
		{}
        BuiltinPokerClicheLong(const Constant *n1, const Constant *n2, const Constant *n3)
			: PokerClicheLong(n1, n2, n3)
		{}
	};

	class BuiltinPokerClicheTrailer
		: public PokerClicheTrailer
	{
	protected:
        BuiltinPokerClicheTrailer(const Constant *const *name, size_t count);
        BuiltinPokerClicheTrailer(const Empty *n1, const Constant *n2)
			: PokerClicheTrailer(n1, n2)
		{}
        BuiltinPokerClicheTrailer(const Empty *n1, const Constant *n2, const Constant *n3)
			: PokerClicheTrailer(n1, n2, n3)
		{}
        BuiltinPokerClicheTrailer(const Empty *n1, const Constant *n2, const Constant *n3, const Constant *n4)
			: PokerClicheTrailer(n1, n2, n3, n4)
		{}
	private:
        const Constant *dummy;
	};

	class BuiltinPokerClicheShort
		: public PokerClicheShort
	{
	protected:
        BuiltinPokerClicheShort(const Constant *name)
			: PokerClicheShort(name)
		{}
	};
}

