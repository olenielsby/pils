/* This file is public domain */
#ifndef DEFINE_PILS_DATAMODEL_H
#define DEFINE_PILS_DATAMODEL_H
#include "pilsmutex.h"

#ifdef PILS_CHAR_IS_UTF16
typedef wchar_t PILS_CHAR;
#else
typedef char PILS_CHAR;
#endif

#define _PS(x) x

namespace PILS
{
	/* The Heap class is a static wrapper for functions dealing with
	   memory management and constant hashing. */

	class Heap
	{
	public:
		static void *allocate(size_t size) {return allocator->allocate(size);}
		static void free(void *block, size_t size) {return allocator->free(block, size);}
		class Allocator
		{
		public:
			virtual void *allocate(size_t size) = 0;
			virtual void free(void *block, size_t size) = 0;
			virtual void shutdown() = 0;
		};
		static void useStandardAllocator();
		static void shutdown();
		static Mutex mutex;
	private:
		static Allocator *allocator;
	};

	class InitialAllocator
		: public Heap::Allocator
	{
	public:
		/* All initial allocations are kept in a chain for deletion on exit.
		   This should prevent memory checkers from reporting them as leaks.
		*/
		void *allocate(size_t bytes);
		void free(void *block, size_t size);
		void shutdown();
		static InitialAllocator singleton;
	private:
		void* chain;
		InitialAllocator(): chain(NULL) {}
	};

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
	class Listener;
	class Language;
	class PilsColor;

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
		virtual bool convert(const Constant &name, const Constant *const *attribute, const Any *const *value, size_t count);
		virtual bool convert(const Any *const *element, size_t count);
		virtual bool convert(const ReallySpecial &special);
		virtual bool convert(const Listener &listener);
		virtual bool convert(const PilsColor &color);
		static Converter dummy;
	};

	class InterfaceDesignator;

	class Recognizer;

	class Any
		: public Step
	{
	public:
		bool duplicateReferenceNoChildren() const;
		virtual bool isMultipleReferenced() const;
	protected:
		Any();
		bool duplicateReference() const;
		bool duplicateReference(bool copying) const;
		virtual void unduplicateChildren() const;
		union
		{
			mutable long referenceCount;
			mutable Any* scrapLink;
		};
	public:
		void unduplicateReference() const;
		void addReference() const;
		void releaseReference() const;
		void releaseReferenceInsideLock() const;
		void releaseFrom(Any &scrap) const;
		virtual size_t unlinkAndGetSize() = 0;
		virtual bool write(Writing &writing, WriteState state, long level, const Constant *dot) const = 0;
		virtual const Any *labeling(Writing &writing) const;
		virtual const Call *callHere() const;
		virtual const CallWho *callWho(const Any *who) const;
		virtual const Escape *escape() const;
		virtual bool isNode(const Any *const *&element, const Cliche *&cliche) const;
		virtual bool isList(const Any *const *&element, const Integer *&count) const;
		bool isList(const Any *const *&element, size_t &count) const;
		virtual bool isNumber(double &number) const;
		bool isNumber(float &number) const;
		virtual const Step *caller(Runner &run, const Any &where_) const = 0;
		virtual const Step *calling(Runner &run, const Constant &call) const;
		virtual const Step *calling(Runner &run, const Integer &call) const;
		virtual const Step *calling(Runner &run, const ListConstant &call) const;
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
		virtual bool recognize(Recognizer &recognizer) const;
	private:
		Any *destroy();
		friend class Special;
		void disposeRoot();
	};

	class Number;
	class ShortInteger;
	class ClicheLong;
	class ClicheTrailer;
	class NodeConstantShort;
	class NodeConstantLong;
	class HashedConstant;

	class Constant
		: public Any
	{
	public:
		const ClicheTiny *newCliche(const HashedConstant *&link) const;
		virtual const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const;
		virtual const ClicheLong *newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
		virtual const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const = 0;
		const Call *callHere() const;
		const ClicheShort *clichefy(const Constant *attribute) const;
		const ClicheTiny *clichefy() const;
		const ClicheLong *clichefy(const Constant *const *attribute, size_t count) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const Constant *as_Constant() const;
		void compilePattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
		const void *compilePatternIndex() const;
		const void *callingIndex() const;
		virtual int order(const Constant *other) const;
		virtual int ordering(double first) const;
		virtual int ordering(const PilsString *first) const;
		virtual int ordering(const ListConstant *first) const;
		virtual int ordering() const;
	private:
		const ClicheShort *clichefying(const Constant *attribute) const;
		virtual const ClicheTiny *clichefying() const;
		const ClicheLong *clichefying(const Constant *const *attribute, size_t count) const;
	};

	/* Hashed constants are uniquely represented */

	class HashedConstant
		: public Constant
	{
	protected:
		using Constant::newCliche;
		virtual const ClicheTiny *newCliche() const;
		HashedConstant(const HashedConstant *&link);
		HashedConstant();
		void unhash();
		friend class SpecialLookup;
		friend class Constant;
	public:
		mutable const HashedConstant *hashLink;
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
		static const HashedConstant *&hashChain(size_t hash);
	private:
		friend class Integer;
		static const ShortInteger hashTable[0x10000];
		virtual const ClicheTiny *clichefying() const;
	};

	/* Abstract class for const Integer and const Float. On unification, floating
	   point values will be converted to const Integer if possible without
	   loss.
	*/

	class Number
		: public HashedConstant
	{
	public:
		using HashedConstant::isNumber;
		static const Number *get(double v);
		int ordering(const PilsString *first) const;
		int ordering(const ListConstant *first) const;
		int ordering() const;
		bool isNumber(double &number) const = 0;
	protected:
		Number(const HashedConstant *&link)
			: HashedConstant(link)
		{}
		Number()
		{}
	};

	class Integer
		: public Number
	{
	public:
		long value;
		Integer(const HashedConstant *&link, long v)
			: Number(link), value(v)
		{}
		const Integer *hashLookup(long v) const;
		size_t unlinkAndGetSize();
		static const Integer *get(long v);
		static const Integer *getInsideLock(long v);
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run)const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		bool convert(Converter &converter) const;
		int order(const Constant *other) const;
		int ordering(double first) const;
		const Integer *as_Integer() const;
		bool isNumber(double &number) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
		bool recognize(Recognizer &recognizer) const;
	protected:
		Integer(long v)
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
		const Integer *hashLookup(long v) const;
		const PilsString *hashLookup(const PILS_CHAR *text, size_t c) const;
		const Float *hashLookup(double v) const;
		const PilsColor *hashLookupPilsColor(unsigned int v) const;
		const PilsDate *hashLookupPilsDate(long long v) const;
		const Timestamp *hashLookupTimestamp(long long v) const;
		const Duration *hashLookupDuration(long long v) const;
		const ClicheLong *hashLookup(const Constant *h, const Constant *const *a, size_t c) const;
		const ClicheShort *hashLookup(const Constant *h, const Constant *a) const;
		const NodeConstantShort *hashLookup(const ClicheShort &cliche, const Constant *value) const;
		const NodeConstantLong *hashLookup(const ClicheLong &cliche, const Constant *const *value) const;
		const ListConstant *hashLookup(const Constant *const *a, size_t c, bool copying) const;
		const ReallySpecial *hashLookup(SpecialLookup &lookup) const;
	private:
		static long initial;
	};

	class Float
		: public Number
	{
	public:
		double value;
		Float(const HashedConstant *&link, double v)
			: Number(link), value(v)
		{}
		const Float *hashLookup(double v) const;
		size_t unlinkAndGetSize();
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		int order(const Constant *other) const;
		int ordering(double first) const;
		bool isNumber(double &number) const;
		bool recognize(Recognizer &recognizer) const;
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
		: public HashedConstant
	{
	public:
		PilsColor(const HashedConstant *&link, unsigned int value)
			: HashedConstant(link), value(value)
		{}
		static const PilsColor *get(unsigned int v);
		const PilsColor *hashLookupPilsColor(unsigned int v) const;
		size_t unlinkAndGetSize();
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		bool recognize(Recognizer &recognizer) const;
		unsigned int value;
	};

	class Timevalue
		: public HashedConstant
	{
	public:
		size_t unlinkAndGetSize();
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
		const Step *passUncounted(Runner &run) const;
		const Step *step_(Runner &run) const;
		long long value;
	protected:
		Timevalue(const HashedConstant *&link, long long value)
			: HashedConstant(link), value(value)
		{}
	};

	class Timestamp
		: public Timevalue
	{
	public:
		Timestamp(const HashedConstant *&link, long long value)
			: Timevalue(link, value)
		{}
		const Timestamp *as_Timestamp() const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const Timestamp *hashLookupTimestamp(long long value) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		int order(const Constant *other) const;
		struct Split : DatepartSplit, ClockpartSplit
		{
			long zoneSecond;
			long long get();
			void put(long long time);
		};
		static const Timestamp *get(long long value);
	private:
		friend class SystemPropertyTimestamp;
		static long long stamp;
	};
		
	class Duration
		: public Timevalue
	{
	public:
		Duration(const HashedConstant *&link, long long value)
			: Timevalue(link, value)
		{}
		const Duration *as_Duration() const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const Duration *hashLookupDuration(long long value) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		int order(const Constant *other) const;
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
		PilsDate(const HashedConstant *&link, long long value)
			: Timevalue(link, value)
		{}
		const PilsDate *as_PilsDate() const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const PilsDate *hashLookupPilsDate(long long value) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		int order(const Constant *other) const;
		const Step *passCounted(Runner &run) const;
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
		: public HashedConstant
	{
	protected:
		CountedConstant(const HashedConstant *&link, size_t c);
	public:
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
			bool put(unsigned long c);
			virtual bool put(unsigned short c) = 0;
		};
		class UTF16count : public UTF16pass
		{
		public:
			UTF16count() : count(0) {}
			size_t count;
		private:
			bool put(unsigned short c);
		};
		class UTF16write : public UTF16pass
		{
		public:
			UTF16write(unsigned short *at) : at(at) {}
		private:
			unsigned short* at;
			bool put(unsigned short c);
		};
		PilsString(const HashedConstant *&link, const PILS_CHAR *text, size_t c);
		const PILS_CHAR value[1];
		const PilsString *hashLookup(const PILS_CHAR *text, size_t c) const;
		size_t unlinkAndGetSize();
		static const PilsString *get(const PILS_CHAR *text, size_t count);
		static const PilsString *get(const PILS_CHAR *text);
#ifndef PILS_CHAR_IS_UTF16
		static const PilsString *get(const wchar_t *text, size_t count);
		static const PilsString *get(const wchar_t *text);
#endif
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		NameSkin nameSkin() const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const PilsString* as_String() const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		bool convert(Converter &converter) const;
		bool less(const PilsString &other) const;
		static const std::locale defaultLocale;
		int order(const Constant *other) const;
		int ordering(const PilsString *first) const;
		int ordering(const ListConstant *first) const;
		int ordering() const;
		bool recognize(Recognizer &recognizer) const;
	protected:
		PilsString(const PILS_CHAR *text, size_t count);
	private:
		static const HashedConstant *&hashChain(const PILS_CHAR *text, size_t count);
	};

	class Cliche
		: public HashedConstant
	{
	public:
		size_t count;
		const Constant *head;
		const Constant *attributes[1];
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		const NodeConstant *nodeConstant(const Constant *const *attributes) const;
		virtual const Any *node(const Any *const *element) const = 0;
		virtual const Any *node(const Constant *const *element) const = 0;
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		const Cliche *as_Cliche() const;
		const Constant *lookupNonempty(const NodeConstant *node, size_t start, const Constant *key) const;
		const Any *lookupNonempty(const NodeExpress *node, size_t start, const Constant *key) const;
	protected:
		Cliche(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c);
		Cliche(const Constant *h, const Constant *a1, const Constant *a2);
		Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3);
		Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4);
		virtual const NodeConstant *nodifyingConstant(const Constant *const *attributes) const = 0;
	private:
		static const HashedConstant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2);
		static const HashedConstant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3);
		static const HashedConstant *&hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4);
	};

	class ListConstant :
		public CountedConstant
	{
	public:
		const Constant *element[1];
		size_t unlinkAndGetSize();
		const ListConstant *as_ListConstant() const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const ListConstant *hashLookup(const Constant *const *a, size_t c, bool copying) const;
		ListConstant(const HashedConstant *&link, const Constant *const *a, size_t c, bool copying);
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		static const ListConstant *get(const Constant *const *e, size_t c, bool copying = false);
		bool isList(const Any *const *&element, const Integer *&count) const;
		const Step *step_(Runner &run) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		int order(const Constant *other) const;
		int ordering(const ListConstant *first) const;
		int ordering() const;
		bool recognize(Recognizer &recognizer) const;
	protected:
		void unduplicateChildren() const;
		const void *compilePatternIndex() const;
		const void *callingIndex() const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
	};

	class Empty :
		public ListConstant
	{
	public:
		static const Empty singleton;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		const Call *callHere() const;
		const ClicheLong *newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
		const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const;
		const Step *caller(Runner &run, const Any &where_) const;
	private:
		Empty();
	};

	class NodeExpressShort;
	class ClicheShort
		: public Cliche
	{
	public:
		const ClicheShort *hashLookup(const Constant *h, const Constant *a) const;
		ClicheShort(const HashedConstant *&link, const Constant *h, const Constant *a)
			: Cliche(link, h, &a, 1)
		{}
		size_t unlinkAndGetSize();
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		virtual const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		static const HashedConstant *&hashChain(const Constant *h, const Constant *a);
		const NodeConstantShort *nodeConstant(const Constant *const *attributes) const;
		virtual const NodeConstantShort *nodeConstant(const Constant *attribute) const;
		const Any *node(const Any *element) const;
		virtual const Any *node(const Constant *element) const;
		virtual const NodeExpressShort *node(const Express *element) const;
		virtual const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		const ClicheShort* as_ClicheShort() const;
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
	protected:
		ClicheShort(const Constant *h, const Constant *a)
			: Cliche(hashChain(h, a), h, &a, 1)
		{}
		void unduplicateChildren() const;
		const NodeConstant *nodifyingConstant(const Constant *const *attributes) const;
	private:
		static const HashedConstant *&link(const Constant *h, const Constant *a);
	};

	class ClicheTiny
		: public ClicheShort
	{
	public:
		using ClicheShort::node;
		ClicheTiny(const HashedConstant *h);
		const ClicheShort *hashLookup(const Constant *h, const Constant *a) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
		virtual void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
		const ClicheTiny* as_ClicheTiny() const;
		virtual const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const;
		virtual const Any *specialOperation(Runner &run, const ReallySpecial &special, const Any &argument, const Any &assignValue) const;
	protected:
		void unduplicateChildren() const;
	};

	class EmptyClicheShort
		: public ClicheShort
	{
	public:
		EmptyClicheShort(const HashedConstant *&link, const Empty *h, const Constant *a)
			: ClicheShort(link, h, a)
		{}
		const Any *node(const Constant *element) const;
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
		const ClicheShort* newCliche(const HashedConstant *&link, const Constant *a) const;
		const ClicheLong* newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
		static const PokerHead singleton;
	private:
		PokerHead(const Constant &action)
			: EmptyClicheShort(&Empty::singleton, &action)
		{}
	};

	class PokerClicheShort:
		public ClicheShort
	{
	public:
		PokerClicheShort(const HashedConstant *&link, const Constant *a);
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	protected:
		PokerClicheShort(const Constant *a)
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
		static const JumperHead singleton;
		const ClicheLong *newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
		const Any *node(const Constant *element) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		JumperHead()
			: ClicheTiny(&Empty::singleton)
		{}
	};

	class JumperCliche0
		: public ClicheTiny
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const JumperCliche0 singleton;
	protected:
		JumperCliche0(const HashedConstant *head)
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
		void unduplicateChildren() const;
	public:
		const ClicheLong *hashLookup(const Constant *h, const Constant *const *a, size_t c) const;
		ClicheLong(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c);
		virtual const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
		size_t unlinkAndGetSize();
		virtual const NodeConstantLong *nodeConstant(const Constant *const *attributes) const;
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
	protected:
		const NodeConstant *nodifyingConstant(const Constant *const *attributes) const;
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
		EmptyClicheLong(const HashedConstant *&link, const Empty *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
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
		ClicheTrailer(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheLong(link, h, a, c)
		{}
		const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
		const Any *node(const Any *const *elements) const;
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
		PokerClicheLong(const HashedConstant *&link, const Constant *const *a, size_t c);
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
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
		PokerClicheTrailer(const HashedConstant *&link, const Constant *const *a, size_t c);
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
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
		BindCliche(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: ClicheTrailer(link, h, a, c)
		{}
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
	};

	class BindCliche1:
		public BindCliche
	{
	public:
		BindCliche1(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	private:
		const Constant *dummy;
	};

	class BindCliche2:
		public BindCliche
	{
	public:
		BindCliche2(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	private:
		const Constant *dummy[2];
	};

	class BindCliche3:
		public BindCliche
	{
	public:
		BindCliche3(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	private:
		const Constant *dummy[3];
	};

	class JumperCliche:
		public BindCliche
	{
	public:
		JumperCliche(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	};

	class JumperCliche1:
		public BindCliche1
	{
	public:
		JumperCliche1(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche1(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	};

	class JumperCliche2:
		public BindCliche2
	{
	public:
		JumperCliche2(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche2(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	};

	class JumperCliche3:
		public BindCliche3
	{
	public:
		JumperCliche3(const HashedConstant *&link, const Constant *h, const Constant *const *a, size_t c)
			: BindCliche3(link, h, a, c)
		{}
		const Any *node(const Any *const *element) const;
	};

	class NodeConstant
		: public HashedConstant
	{
	public:
		const Cliche *cliche;
		const Constant *element[1];
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		bool isNode(const Any *const *&element, const Cliche *&cliche) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const NodeConstant *as_NodeConstant() const;
		const void *compilePatternIndex() const;
		const void *callingIndex() const;
		void compileNodecheckPattern(Compiling &compiling) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
		bool convert(Converter &converter) const;
		virtual const Constant *getAttribute(const Constant &name) const;
	protected:
		NodeConstant(const HashedConstant *&link, const Cliche &cliche);
	};

	class NodeConstantShort
		: public NodeConstant
	{
	public:
		size_t unlinkAndGetSize();
		const NodeConstantShort *hashLookup(const ClicheShort &cliche, const Constant *value) const;
		NodeConstantShort(const HashedConstant *&link, const ClicheShort &cliche, const Constant *value);
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Escape* escape() const;
		virtual const Channel *as_Channel() const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
	protected:
		void unduplicateChildren() const;
	};

	class NodeConstantTiny
		: public NodeConstantShort
	{
	public:
		NodeConstantTiny(const HashedConstant *&link, const ClicheTiny &cliche, const Constant *value)
			: NodeConstantShort(link, cliche, value)
		{}
		const NodeConstantTiny *as_NodeConstantTiny() const;
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
	};

	class NodeConstantLong
		: public NodeConstant
	{
	public:
		size_t unlinkAndGetSize();
		const NodeConstantLong *hashLookup(const ClicheLong &cliche, const Constant *const *value) const;
		NodeConstantLong(const HashedConstant *&link, const ClicheLong &cliche, const Constant *const *value);
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Escape* escape() const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
	protected:
		void unduplicateChildren() const;
	};

	class NodeConstantTrailer
		: public NodeConstantLong
	{
	public:
		NodeConstantTrailer(const HashedConstant *&link, const ClicheLong &cliche, const Constant *const *element)
			: NodeConstantLong(link, cliche, element)
		{}
		const Escape *escape() const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Constant *getAttribute(const Constant &name) const;
	};

	class EscapeCliche
		: public ClicheTiny
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const EscapeCliche singleton;
	private:
		EscapeCliche()
			: ClicheTiny(&PokerHead::singleton)
		{}
	};

	class Express
		: public Any
	{
	};

	class TypecheckPropertyCount;
	class BuiltinClicheStrap;

	class Strap
		: public NodeConstantTiny
	{
	public:
		Strap(const HashedConstant *&link, const BuiltinClicheStrap &cliche, const Constant *value);
		class Sticker
		{
		public:
			~Sticker();
			void stick(const Strap &strap);
			void clear();
			void blast();
		private:
			std::set<const Strap*> stuck;
		};
	private:
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		size_t unlinkAndGetSize();
		void unstick() const;
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		mutable size_t stickCount;
		mutable const Any *mind;
		const Any *get() const;
	};

	class Pipesource;

	class Special
		: public HashedConstant
	{
	public:
		const ReallySpecial *hashLookup(SpecialLookup &lookup) const;
		const Special *unique() const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const Step *step_(Runner &run) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		bool convert(Converter &converter) const;
		virtual const Any *specialCalling(Runner &run, const Integer &call) const;
		virtual const Any *specialCalling(Runner &run, const Integer &call, const Any &AssignValue) const;
		virtual const Any *specialCalling(Runner &run, const PilsString &call) const;
		virtual const Any *specialCalling(Runner &run, const PilsString &call, const Any &AssignValue) const;
		virtual const Any *specialCalling(Runner &run, const Constant &nameWhat) const;
		virtual const Any *specialCalling(Runner &run, const Strap &call) const;
		virtual const Constant *type() const;
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		virtual bool enumerate(Runner &run) const;
		virtual const Any *queryInterface(const InterfaceDesignator &designator) const;
		mutable const Any *when;
	private:
		virtual void write(Writing &writing) const = 0;
		friend class ReallySpecial;
		Special(const HashedConstant *&link) : HashedConstant(link), when(NULL) {}
		Special() : when(NULL) {}
	};

	/* abstract class for looking up wrappers for special values */

	class SpecialLookup
	{
	public:
		virtual const ReallySpecial *newSpecial(const HashedConstant *&link) = 0;
		virtual bool compare(const ReallySpecial &special) const = 0;
		virtual void unduplicate() = 0;
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
		size_t unlinkAndGetSize();
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		bool isList(const Any *const *&element, const Integer *&count) const;
		ListExpress(const Any *const *element, size_t count);
		const Step *step_(Runner &run) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const void *compilePatternIndex() const;
		const void *callingIndex() const;
		void compilePattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		bool recognize(Recognizer &recognizer) const;
	};

	class NodeExpress
		: public Express
	{
	public:
		const Cliche *cliche;
		const Any *element[1];
		bool write (Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Any *labeling(Writing &writing) const;
		bool isNode(const Any *const *&element, const Cliche *&cliche) const;
		const Step *caller(Runner &run, const Any &where_) const;
		const NodeExpress* as_NodeExpress() const;
		const void *compilePatternIndex() const;
		const void *callingIndex() const;
		void compileNodecheckPattern(Compiling &compiling) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
		bool convert(Converter &converter) const;
		virtual const Any *getAttribute(const Constant &name) const;
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
		size_t unlinkAndGetSize();
		const Step *step_(Runner &run) const;
		const CallWho* callWho(const Any *who) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		void compilePattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		const Escape* escape() const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
	};

	class PokerShort
		: public NodeExpressShort
	{
	public:
		PokerShort(const PokerClicheShort &cliche, const Any* value)
			: NodeExpressShort(cliche, value)
		{}
		const CallWho* callWho(const Any *who) const;
		const Step *step_(Runner &run) const;
		void compileNodecheckPattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class NodeExpressTiny
		: public NodeExpressShort
	{
	public:
		NodeExpressTiny(const ClicheTiny &cliche, const Any *value)
			: NodeExpressShort(cliche, value)
		{}
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
	};

	class Jumper0
		: public NodeExpressTiny
	{
	public:
		Jumper0(const Any *element)
			: NodeExpressTiny(JumperCliche0::singleton, element)
		{}
		const Express *findCatchTag() const;
		const Express *findCatchTag(const Constant &tag) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		bool compileBuild(CompilingBuild &compiling) const;
	protected:
		Jumper0(const ClicheTiny &cliche, const Any *element)
			: NodeExpressTiny(cliche, element)
		{}
	};

	class NodeExpressLong
		: public NodeExpress
	{
	public:
		size_t unlinkAndGetSize();
		NodeExpressLong(const ClicheLong &cliche, const Any *const *element)
			: NodeExpress(cliche, element)
		{}
		NodeExpressLong(const ClicheLong &cliche, const Any *v1, const Any *v2)
			: NodeExpress(cliche, v1, v2)
		{}
		NodeExpressLong(const ClicheLong &cliche, const Any *v1, const Any *v2, const Any *v3)
			: NodeExpress(cliche, v1, v2, v3)
		{}
		const Step *step_(Runner &run) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		void compilePattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
		const QuickCalling *matching(Runner &run, void **stack, const QuickMatch &match) const;
		const Escape* escape() const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Escape *escape() const;
		const Any *getAttribute(const Constant &name) const;
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
		const Step *step_(Runner &run) const;
		void compileNodecheckPattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
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
		const Step *step_(Runner &run) const;
		void compileNodecheckPattern(Compiling &compiling) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class Bind
		: public NodeExpressTrailer
	{
	public:
		Bind(const ClicheTrailer &cliche, const Any *const *element)
			: NodeExpressTrailer(cliche, element)
		{}
		const Step *step_(Runner &run) const;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		const Express *findCatchTag() const;
		const Express *findCatchTag(const Constant &tag) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class Bind1
		: public Bind
	{
		using Bind::calling;
	public:
		Bind1(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
	private:
		const Any* dummy;
	};

	class Bind2
		: public Bind
	{
		using Bind::calling;
	public:
		Bind2(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
	private:
		const Any* dummy[2];
	};

	class Bind3
		: public Bind
	{
		using Bind::calling;
	public:
		Bind3(const ClicheTrailer &cliche, const Any *const *element)
			: Bind(cliche, element)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
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
		const Step *calling(Runner &run, const Empty &call) const;
		const Express *findCatchTag() const;
	};

	class Jumper1
		: public Bind1
	{
	public:
		Jumper1(const ClicheTrailer &cliche, const Any *const *element)
			: Bind1(cliche, element)
		{}
		const Step *calling(Runner &run, const Empty &call) const;
		const Express *findCatchTag() const;
	};

	class Jumper2
		: public Bind2
	{
	public:
		Jumper2(const ClicheTrailer &cliche, const Any *const *element)
			: Bind2(cliche, element)
		{}
		const Step *calling(Runner &run, const Empty &call) const;
		const Express *findCatchTag() const;
	};

	class Jumper3
		: public Bind3
	{
	public:
		Jumper3(const ClicheTrailer &cliche, const Any *const *element)
			: Bind3(cliche, element)
		{}
		const Step *calling(Runner &run, const Empty &call) const;
		const Express *findCatchTag() const;
	};

	/* Builtin cliches in general */

	class BuiltinClicheTiny
		: public ClicheTiny
	{
	protected:
		BuiltinClicheTiny(const HashedConstant *head)
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

	/* Template for node constructor maps
	 *
	 * If present, the joker value is stored outside the map
	 * and placed in front when attribute names and values
	 * are extracted.
	 */

	template<class Value> class NodeBuilder
	{
	public:
        typedef std::map<const Constant*, const Value*> map; // Value* won't compile
		bool aim(const Constant *key)
		{
			if (aimed) goto bad;
			if (key == (const Constant *)&Empty::singleton)
			{
				if (joker)
					goto bad;
			}
			else
			{
				if (mapping.count(key))
					goto bad;
			}
			aimed = key;
			return true;
		bad:
			key->releaseReference();
			return false;
		}

		void set(Value* value)
		{
			if (aimed == (const Constant *)&Empty::singleton) joker = value;
			else mapping[aimed] = value;
			aimed = NULL;
		}

		size_t count()
		{
			return mapping.size() + (joker ? 1 : 0);
		}

		const Any *build();

		NodeBuilder(const Constant *head)
			: head(head), aimed(NULL), joker(NULL), alive(true)
		{}

		~NodeBuilder()
		{
			if (aimed) aimed->releaseReference();
			if (alive)
			{
				head->releaseReference();
				if (joker)
				{
					joker->releaseReference();
					Empty::singleton.releaseReference();
				}
				for (typename map::iterator run = mapping.begin();
					run != mapping.end();
					run++)
				{
					run->first->releaseReference();
					run->second->releaseReference();
				}
			}
		}
		const Constant *head;
	private:
		map mapping;
		const Constant *aimed;
		Value* joker;
		bool alive;
	};

	class ClicheBuilder
	{
	public:
		bool add(const Constant *key);
		bool add(const Constant &key);
		const Cliche *build();
		ClicheBuilder(const Constant *head)
			: head(head), joker(false), alive(true)
		{}
		~ClicheBuilder();
	private:
		std::set<const Constant*> setting;
		const Constant *head;
		bool joker;
		bool alive;
	};

	template <class Element, class Result> class ListBuilder
	{
	public:
        typedef std::vector<Element*> vector;
		void add(Element* element)
		{
			listing.insert(listing.end(), element);
		}
		Result *build()
		{
			size_t count = listing.size();
			Element **element = new Element*[count];
			Element **e = element;
			for (typename vector::iterator run = listing.begin(); run != listing.end(); run++)
				*e++ = (Element*)*run;
			Result *list = building(element, count);
			alive = false;
			delete [] element;
			return list;
		}
		ListBuilder() : alive(true)
		{
		}
		~ListBuilder()
		{
			if (alive)
			{
				for (typename vector::iterator run = listing.begin(); run != listing.end(); run++)
				{
					(*run)->releaseReference();
				}
			}
		}

	private:
		static Result* building(Element *const *element, size_t count);
		vector listing;
		bool alive;
	};
}
#endif
