/* This file is public domain */
#ifndef DEFINE_PILS_BUILTIN_H
#define DEFINE_PILS_BUILTIN_H
#include "datamodel.h"
namespace PILS
{
	class Namespace
	{
	public:
		static const PilsString *const standard;
	};

	/* Predefined names are statically allocated, to make their ordering
	   independent of the Heap and its allocation policy. */

	class PredefinedName
		: public ClicheShort
	{
	protected:
		friend class Builtin;
		PredefinedName(const PILS_CHAR *name)
			: ClicheShort(Namespace::standard, PilsString::get(name))
		{}
		PredefinedName(const PilsString *namespace_, const PILS_CHAR *name)
			: ClicheShort(namespace_, PilsString::get(name))
		{}
		PredefinedName(const HashedConstant *&link, const PilsString *namespace_, const PilsString *name)
			: ClicheShort(link, namespace_, name)
		{}
	};

	class PredefinedNameCall
		: public PredefinedName
	{
	public:
		const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const;
		const ClicheLong *newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
		virtual const CallWho *callWho(const NodeConstant *call, const Any *who) const;
		virtual const CallWho *callWho(const NodeExpress *call, const Any *who) const;
	protected:
		friend class Builtin;
		PredefinedNameCall(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PredefinedNameTry
		: public PredefinedNameCall
	{
	public:
		const CallWho *callWho(const NodeConstant *call, const Any *who) const;
		const CallWho *callWho(const NodeExpress *call, const Any *who) const;
	private:
		friend class Builtin;
		PredefinedNameTry(const PILS_CHAR *name)
			: PredefinedNameCall(name)
		{}
	};

	class PropertyMinus
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyMinus(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyIncrementRange
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	protected:
		friend class Builtin;
		PropertyIncrementRange(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyDecrementRange
		: public PropertyIncrementRange
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyDecrementRange(const PILS_CHAR *name)
			: PropertyIncrementRange(name)
		{}
	};

	class PropertyReverse
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyReverse(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyCasing
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
		virtual const PilsString *transform(const PILS_CHAR* source, size_t count, const std::locale &locale) const = 0;
	protected:
		PropertyCasing(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyCasingUpper
		: public PropertyCasing
	{
	private:
		const PilsString *transform(const PILS_CHAR* source, size_t count, const std::locale &locale) const;
		friend class Builtin;
		PropertyCasingUpper(const PILS_CHAR *name)
			: PropertyCasing(name)
		{}
	};

	class PropertyCasingLower
		: public PropertyCasing
	{
	private:
		const PilsString *transform(const PILS_CHAR* source, size_t count, const std::locale &locale) const;
		friend class Builtin;
		PropertyCasingLower(const PILS_CHAR *name)
			: PropertyCasing(name)
		{}
	};

	class PropertyCasingTitle
		: public PropertyCasing
	{
	public:
		const PilsString *transform(const PILS_CHAR* source, size_t count, const std::locale &locale) const;
	private:
		friend class Builtin;
		PropertyCasingTitle(const PILS_CHAR *name)
			: PropertyCasing(name)
		{}
	};

	class PropertyTraverse
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyTraverse(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertySplice
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertySplice(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertySinglewise
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertySinglewise(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyListwise
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyListwise(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyDistinct
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyDistinct(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyHexadecimal
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyHexadecimal(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyCounts
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyCounts(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPlus
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPlus(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckInteger
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckInteger(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckNumber
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckNumber(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckIdentifier
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckIdentifier(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckTimestamp
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckTimestamp(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckDuration
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckDuration(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPilsDate
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPilsDate(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckCliche
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	protected:
		friend class Builtin;
		TypecheckCliche(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPropertyCliche
		: public TypecheckCliche
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		TypecheckPropertyCliche(const PILS_CHAR *name)
			: TypecheckCliche(name)
		{}
	};

	class TypecheckString
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckString(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPlusString
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPlusString(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPlusPlusString
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPlusPlusString(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckList
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckList(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPlusList
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPlusList(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPlusPlusList
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPlusPlusList(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckNode
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckNode(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckConstant
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckConstant(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckListen
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckListen(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckColor
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckColor(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyHead
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyHead(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class TypecheckPropertyLegs
		: public PredefinedName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		TypecheckPropertyLegs(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class SystemProperty
		: public PredefinedName
	{
	public:
		const Any *specialCall(Runner &run, const ReallySpecial &special) const;
		const Any *specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const;
		virtual const Any *get(Runner &run) const;
		virtual const Any *set(const Any &assignvalue) const;
	protected:
		SystemProperty(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
		SystemProperty(const PilsString *namespace_, const PILS_CHAR *name)
			: PredefinedName(namespace_, name)
		{}
		SystemProperty(const HashedConstant *&link, const PilsString *namespace_, const PilsString *name)
			: PredefinedName(link, namespace_, name)
		{}
		friend class Plumcake;
	};

	class TypecheckLanguage
		: public SystemProperty
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		TypecheckLanguage(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class SystemPropertyNew
		: public SystemProperty
	{
	public:
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		SystemPropertyNew(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class SystemPropertyNow
		: public SystemProperty
	{
	public:
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		SystemPropertyNow(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class SystemPropertyTimestamp
		: public SystemProperty
	{
	public:
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		SystemPropertyTimestamp(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class SystemPropertyThread
		: public SystemProperty
	{
	public:
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		SystemPropertyThread(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class SystemPropertyPlumcake
		: public SystemProperty
	{
	public:
		const Any *get(Runner &run) const;
	private:
		friend class Builtin;
		SystemPropertyPlumcake(const PILS_CHAR *name)
			: SystemProperty(name)
		{}
	};

	class OperatorEval
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		OperatorEval(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class AggregateCallWho;

	class PredefinedAggregateFunctionName
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
		virtual void pushAggregatePipe(Runner &run, const AggregateCallWho &what) const = 0;
	protected:
		PredefinedAggregateFunctionName(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PredefinedNameSum
		: public PredefinedAggregateFunctionName
	{
	public:
		void pushAggregatePipe(Runner &run, const AggregateCallWho &what) const;
	private:
		friend class Builtin;
		PredefinedNameSum(const PILS_CHAR *name)
			: PredefinedAggregateFunctionName(name)
		{}
	};

	class PredefinedNameMin
		: public PredefinedAggregateFunctionName
	{
	public:
		void pushAggregatePipe(Runner &run, const AggregateCallWho &what) const;
	private:
		friend class Builtin;
		PredefinedNameMin(const PILS_CHAR *name)
			: PredefinedAggregateFunctionName(name)
		{}
	};
	class PredefinedNameMax
		: public PredefinedAggregateFunctionName
	{
	public:
		void pushAggregatePipe(Runner &run, const AggregateCallWho &what) const;
	private:
		friend class Builtin;
		PredefinedNameMax(const PILS_CHAR *name)
			: PredefinedAggregateFunctionName(name)
		{}
	};

	class SearchString;
	class SearchListConstant;
	class SearchExpress;

	class SearchNameAbstract
		: public PredefinedName
	{
	public:
		virtual const CallWho *whoSearch(const SearchString *value, const Any *who) const = 0;
		virtual const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const = 0;
		virtual const CallWho *whoSearch(const SearchExpress *value, const Any *who) const = 0;
	protected:
		SearchNameAbstract(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class SearchName
		: public SearchNameAbstract
	{
	public:
		SearchName(const PILS_CHAR *name)
			: SearchNameAbstract(name)
		{}
		const CallWho *whoSearch(const SearchString *value, const Any *who) const;
		const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const;
		const CallWho *whoSearch(const SearchExpress *value, const Any *who) const;
	};

	class TypecheckPropertyCount
		: public SearchName
	{
	public:
		void compileTypecheck(Compiling &compiling, const CallWho &what) const;
	private:
		friend class Builtin;
		TypecheckPropertyCount(const PILS_CHAR *name)
			: SearchName(name)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class PlusRangeSearchName
		: public SearchNameAbstract
	{
	public:
		PlusRangeSearchName(const PILS_CHAR *name)
			: SearchNameAbstract(name)
		{}
		const CallWho *whoSearch(const SearchString *value, const Any *who) const;
		const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const;
		const CallWho *whoSearch(const SearchExpress *value, const Any *who) const;
	};

	class PlusRangeReverseSearchName
		: public SearchNameAbstract
	{
	public:
		PlusRangeReverseSearchName(const PILS_CHAR *name)
			: SearchNameAbstract(name)
		{}
		const CallWho *whoSearch(const SearchString *value, const Any *who) const;
		const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const;
		const CallWho *whoSearch(const SearchExpress *value, const Any *who) const;
	};

	class MinusRangeSearchName
		: public SearchNameAbstract
	{
	public:
		MinusRangeSearchName(const PILS_CHAR *name)
			: SearchNameAbstract(name)
		{}
		const CallWho *whoSearch(const SearchString *value, const Any *who) const;
		const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const;
		const CallWho *whoSearch(const SearchExpress *value, const Any *who) const;
	};

	class MinusRangeReverseSearchName
		: public SearchNameAbstract
	{
	public:
		MinusRangeReverseSearchName(const PILS_CHAR *name)
			: SearchNameAbstract(name)
		{}
		const CallWho *whoSearch(const SearchString *value, const Any *who) const;
		const CallWho *whoSearch(const SearchListConstant *value, const Any *who) const;
		const CallWho *whoSearch(const SearchExpress *value, const Any *who) const;
	};

	class PredefinedNameOk
		: public PredefinedName
	{
	public:
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
	private:
		friend class Builtin;
		PredefinedNameOk(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PredefinedNameSplit
		: public PredefinedName
	{
	public:
		const ClicheLong *newCliche(const HashedConstant *&link, const Constant *const *a, size_t c) const;
	private:
		friend class Builtin;
		PredefinedNameSplit(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyCharacterEncoding
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
		virtual int initialState(const char* &at, const char* end) const = 0;
		virtual long get(const char* &at, const char* end, int &state) const = 0;
		virtual bool put(std::string &string, long code, int &state) const = 0;
	protected:
		PropertyCharacterEncoding(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyBytes
		: public PropertyCharacterEncoding
	{
	public:
		int initialState(const char* &at, const char* end) const;
		long get(const char* &at, const char* end, int &state) const;
		bool put(std::string &string, long code, int &state) const;
	private:
		friend class Builtin;
		PropertyBytes(const PILS_CHAR *name)
			: PropertyCharacterEncoding(name)
		{}
	};

	class PropertyUtf_8
		: public PropertyCharacterEncoding
	{
		int initialState(const char* &at, const char* end) const;
		long get(const char* &at, const char* end, int &state) const;
		bool put(std::string &string, long code, int &state) const;
	private:
		friend class Builtin;
		PropertyUtf_8(const PILS_CHAR *name)
			: PropertyCharacterEncoding(name)
		{}
	};

	class PropertyUtf_16
		: public PropertyCharacterEncoding
	{
		int initialState(const char* &at, const char* end) const;
		long get(const char* &at, const char* end, int &state) const;
		bool put(std::string &string, long code, int &state) const;
		virtual long get16bit(const char* &at, const char* end, int &state) const;
		virtual void put16bit(std::string &string, long code, int &state) const;
	protected:
		friend class Builtin;
		PropertyUtf_16(const PILS_CHAR *name)
			: PropertyCharacterEncoding(name)
		{}
	};

	class PropertyUtf_16le
		: public PropertyUtf_16
	{
		int initialState(const char* &at, const char* end) const;
		long get16bit(const char* &at, const char* end, int &state) const;
		void put16bit(std::string &string, long code, int &state) const;
	private:
		friend class Builtin;
		PropertyUtf_16le(const PILS_CHAR *name)
			: PropertyUtf_16(name)
		{}
	};

	class PropertyUtf_16be
		: public PropertyUtf_16
	{
		int initialState(const char* &at, const char* end) const;
		long get16bit(const char* &at, const char* end, int &state) const;
		void put16bit(std::string &string, long code, int &state) const;
	private:
		friend class Builtin;
		PropertyUtf_16be(const PILS_CHAR *name)
			: PropertyUtf_16(name)
		{}
	};

	class Building;
	class BuilderName
		: public PredefinedName
	{
	public:
		virtual const Step *building(Runner &run, const Any &step_, const Constant &head) const = 0;
	protected:
		BuilderName(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class BuilderNameList
		: public BuilderName
	{
	public:
		const Step *building(Runner &run, const Any &step_, const Constant &head) const;
	private:
		friend class Builtin;
		BuilderNameList(const PILS_CHAR *name)
			: BuilderName(name)
		{}
	};

	class BuilderNameExit
		: public BuilderName
	{
	public:
		const Step *building(Runner &run, const Any &step_, const Constant &head) const;
	private:
		friend class Builtin;
		BuilderNameExit(const PILS_CHAR *name)
			: BuilderName(name)
		{}
	};

	class FloatProperty
		: public PredefinedName
	{
	public:
		const CallWho* callWho(const Any *who) const;
		double (*function)(double);
	private:
		friend class Builtin;
		FloatProperty(const PILS_CHAR *name, double (*function)(double));
		static const FloatProperty properties[];
	};

	class PropertyLocalTime
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyLocalTime(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class PropertyGreenwichMeanTime
		: public PredefinedName
	{
	public:
		const CallWho *callWho(const Any *who) const;
	private:
		friend class Builtin;
		PropertyGreenwichMeanTime(const PILS_CHAR *name)
			: PredefinedName(name)
		{}
	};

	class Builtin
	{
	public:
		static const Builtin name;
		const PredefinedName start;
		const PredefinedName end;
		const PredefinedName error;
		const PredefinedNameCall call;
		const PredefinedName recall;
		const PredefinedName who;
		const PredefinedName when;
		const PredefinedName rule;
		const PredefinedName tag;
		const PredefinedName name_;
		const PredefinedName value;
		const PredefinedName match;
		const PredefinedName action;
		const PredefinedName if_;
		const PredefinedName else_;
		const PredefinedName and_;
		const PredefinedName or_;
		const PredefinedName anyway;
		const PredefinedName not_;
		const TypecheckPropertyCount count_;
		const PropertyCounts counts;
		const PredefinedName stack;
		const PredefinedName read;
		const PredefinedName parse; //temporary
		const PredefinedName write;
		const PredefinedName traceread;
		const PredefinedName indent;
		const PredefinedName where_;
		const PredefinedName useline;
		const PredefinedName what;
		const PredefinedName self;
		const PredefinedName ruleset;
		const PredefinedName year;
		const PredefinedName month;
		const PredefinedName weekday;
		const PredefinedName day;
		const PredefinedName hour;
		const PredefinedName minute;
		const PredefinedName second;
		const PredefinedName millisecond;
		const TypecheckLanguage language;
		const TypecheckPlus plus;
		const PropertyMinus minus;
		const TypecheckNode times;
		const TypecheckCliche divide;
		const PredefinedName integerDivide;
		const TypecheckInteger modulo;
		const FloatProperty round_;
		const FloatProperty truncate_;
		const FloatProperty abs_;
		const TypecheckConstant equal;
		const PredefinedName notEqual;
		const PredefinedName less;
		const PredefinedName lessEqual;
		const PredefinedName greater;
		const PredefinedName greaterEqual;
		const PredefinedName doubleSlash;
		const PredefinedNameOk ok;
		const PredefinedNameTry try_;
		const PredefinedName possibly;
		const PredefinedName need;
		const PropertyIncrementRange up;
		const PropertyDecrementRange down;
		const PredefinedName each;
		const PredefinedName every;
		const PredefinedName while_;
		const PredefinedName except;
		const PredefinedName find;
		const PredefinedName fold;
		const PredefinedName first;
		const PredefinedName repeat;
		const PredefinedName again;
		const BuilderNameList list;
		const PredefinedName groups;
		const PredefinedName firsts;
		const PredefinedName lasts;
		const PredefinedName singles;
		const PredefinedName folds;
		const BuilderNameExit exit;
		const PredefinedName mind;
		const TypecheckPropertyCliche cliche;
		const TypecheckIdentifier identifier;
		const TypecheckTimestamp time;
		const TypecheckDuration duration;
		const TypecheckPilsDate dating;
		const TypecheckNumber hash;
		const TypecheckList ampersand;
		const TypecheckPlusList plusAmpersand;
		const TypecheckPlusPlusList plusPlusAmpersand;
		const TypecheckString dollar;
		const TypecheckPlusString plusDollar;
		const TypecheckPlusPlusString plusPlusDollar;
		const TypecheckListen listen;
		const PropertyHead head;
		const TypecheckPropertyLegs legs;
		const OperatorEval operatorEval;
		const PredefinedName quote;
		const PredefinedName use;
		const PredefinedName using_;
		const PredefinedName but;
		const PredefinedName through;
		const PredefinedName around;
		const PredefinedName combine;
		const PredefinedName plusRange;
		const PredefinedName plusSlackRange;
		const PredefinedName plusRangeReverse;
		const PredefinedName plusSlackRangeReverse;
		const PredefinedName minusRange;
		const PredefinedName minusSlackRange;
		const PredefinedName minusRangeReverse;
		const PredefinedName minusSlackRangeReverse;
		const PredefinedName building;
		const SearchName searchContains;
		const SearchName searchContainsReverse;
		const SearchName searchTill;
		const SearchName searchTillReverse;
		const SearchName searchSpread;
		const SearchName searchSpreadReverse;
		const SearchName searchPrefix;
		const SearchName searchPrefixReverse;
		const SearchName searchRhyme;
		const SearchName searchRhymeReverse;
		const SearchName searchUnrhyme;
		const SearchName searchUnrhymeReverse;
		const SearchName searchPlus;
		const SearchName searchPlusReverse;
		const SearchName searchMinus;
		const SearchName searchMinusReverse;
		const PlusRangeSearchName plusRangeSearchContains;
		const PlusRangeReverseSearchName plusRangeSearchContainsReverse;
		const PlusRangeSearchName plusRangeSearchTill;
		const PlusRangeReverseSearchName plusRangeSearchTillReverse;
		const PlusRangeSearchName plusRangeSearchSpread;
		const PlusRangeReverseSearchName plusRangeSearchSpreadReverse;
		const PlusRangeSearchName plusRangeSearchPrefix;
		const PlusRangeReverseSearchName plusRangeSearchPrefixReverse;
		const PlusRangeSearchName plusRangeSearchRhyme;
		const PlusRangeReverseSearchName plusRangeSearchRhymeReverse;
		const PlusRangeSearchName plusRangeSearchUnrhyme;
		const PlusRangeReverseSearchName plusRangeSearchUnrhymeReverse;
		const PlusRangeSearchName plusRangeSearchPlus;
		const PlusRangeReverseSearchName plusRangeSearchPlusReverse;
		const PlusRangeSearchName plusRangeSearchMinus;
		const PlusRangeReverseSearchName plusRangeSearchMinusReverse;
		const MinusRangeSearchName minusRangeSearchContains;
		const MinusRangeReverseSearchName minusRangeSearchContainsReverse;
		const MinusRangeSearchName minusRangeSearchTill;
		const MinusRangeReverseSearchName minusRangeSearchTillReverse;
		const MinusRangeSearchName minusRangeSearchSpread;
		const MinusRangeReverseSearchName minusRangeSearchSpreadReverse;
		const MinusRangeSearchName minusRangeSearchPrefix;
		const MinusRangeReverseSearchName minusRangeSearchPrefixReverse;
		const MinusRangeSearchName minusRangeSearchRhyme;
		const MinusRangeReverseSearchName minusRangeSearchRhymeReverse;
		const MinusRangeSearchName minusRangeSearchUnrhyme;
		const MinusRangeReverseSearchName minusRangeSearchUnrhymeReverse;
		const MinusRangeSearchName minusRangeSearchPlus;
		const MinusRangeReverseSearchName minusRangeSearchPlusReverse;
		const MinusRangeSearchName minusRangeSearchMinus;
		const MinusRangeReverseSearchName minusRangeSearchMinusReverse;
		const PropertyReverse reverse;
		const PropertyCasingLower lower;
		const PropertyCasingUpper upper;
		const PredefinedName order;
		const PropertyCasingTitle title;
		const PropertyBytes bytes;
		const PropertyUtf_8 utf_8;
		const PropertyUtf_16 utf_16;
		const PropertyUtf_16le utf_16le;
		const PropertyUtf_16be utf_16be;
		const PropertyTraverse traverse;
		const PropertyListwise listwise;
		const PropertyDistinct distinct;
		const PropertySinglewise singlewise;
		const PredefinedNameMin min_;
		const PredefinedNameMax max_;
		const PredefinedNameSum sum_;
		const PredefinedName transformOperator;
		const SystemPropertyNew new_;
		const SystemPropertyNow now;
		const SystemPropertyTimestamp timestamp;
		const PropertyGreenwichMeanTime gmt;
		const PropertyLocalTime localtime;
		const PropertySplice splice;
		const PredefinedNameSplit split;
		const PredefinedName replace;
		const PredefinedName replaceBeginning;
		const PredefinedName replaceEnding;
		const PredefinedName merge;
		const PredefinedName bind;
		const PredefinedName without;
		const PredefinedName text;
		const PredefinedName file;
		const PredefinedName files;
		const PredefinedName folder;
		const PredefinedName folders;
		const PredefinedName readable;
		const PredefinedName writable;
		const PredefinedName copy;
		const PredefinedName move;
		const PredefinedName create;
		const PredefinedName delete_;
		const PredefinedName zip;
		const PredefinedName channel;
		const PredefinedName strap;
		const SystemPropertyPlumcake plumcake;
		const PredefinedName bug;
		const SystemPropertyThread thread;
		const PredefinedName knot;
		const PredefinedName later;
		const PropertyHexadecimal hexadecimal;
		const TypecheckColor color;
		const PredefinedName stackOverflow;
	private:
		Builtin();
	};

	/* Cliches */

	class BuiltinClicheLanguage
		: public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheLanguage singleton;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
	private:
		BuiltinClicheLanguage()
			: BuiltinClicheTiny(&Builtin::name.language)
		{}
	};

	class BuiltinClicheRead
		: public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheRead singleton;
	private:
		BuiltinClicheRead()
			: BuiltinClicheTiny(&Builtin::name.read)
		{}
	};

	class BuiltinClicheTraceread
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheTraceread singleton;
	private:
		BuiltinClicheTraceread()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.start, &Builtin::name.end, &Builtin::name.traceread)
		{}
		const Constant *dummy[3];
	};

	class BuiltinClicheEval
		: public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheEval singleton;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheEval()
			: BuiltinClicheTiny(&Builtin::name.operatorEval)
		{}
	};

	class BuiltinClicheCall
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheCall singleton;
	private:
		BuiltinClicheCall()
			: BuiltinPokerClicheShort(&Builtin::name.call)
		{}
	};

	class BuiltinClicheCallWho
		: public BuiltinPokerClicheLong
	{
	public:
		const Any *node(const Any *const *element) const;
		static const BuiltinClicheCallWho singleton;
	private:
		BuiltinClicheCallWho()
			: BuiltinPokerClicheLong(&Builtin::name.call, &Builtin::name.who)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheRule
		: public EmptyClicheLong
	{
	public:
		static const BuiltinClicheRule singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheRule()
			: EmptyClicheLong(&Empty::singleton, &Builtin::name.match, &Builtin::name.action)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheNameValue
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheNameValue singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheNameValue()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.name_)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheTag
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheTag singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheTag()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.tag)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheRuleset
		: public BuiltinPokerClicheShort
	{
	public:
		static const BuiltinClicheRuleset singleton;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheRuleset()
			: BuiltinPokerClicheShort(&Builtin::name.ruleset)
		{}
	};

	class BuiltinClicheQuote
		: public BuiltinPokerClicheShort
	{
	public:
		static const BuiltinClicheQuote singleton;
		const NodeExpressShort *node(const Express *element) const;
		const Any *node(const Constant *element) const;
	private:
		BuiltinClicheQuote()
			: BuiltinPokerClicheShort(&Builtin::name.quote)
		{}
	};

	class BuiltinClicheClosure
		: public BuiltinPokerClicheLong
	{
	public:
		static const BuiltinClicheClosure singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheClosure()
			: BuiltinPokerClicheLong(&Builtin::name.where_, &Builtin::name.ruleset)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheComment
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
	private:
		static const BuiltinClicheComment singleton;
		BuiltinClicheComment()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.minus)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheUse
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheUse singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheUse()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.use)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheUsing
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheUsing singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheUsing()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.using_)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheThrough
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheThrough singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheThrough()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.through)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheAround
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheAround singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheAround()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.through)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheUseline
		: public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheUseline singleton;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheUseline()
			: BuiltinClicheTiny(&Builtin::name.useline)
		{}
	};

	class BuiltinClicheConcatenate
		: public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheConcatenate singleton;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		BuiltinClicheConcatenate()
			: BuiltinClicheTiny(&Builtin::name.ampersand)
		{}
	};

	class BuiltinClicheFileName
		: public BuiltinClicheTiny
	{
	public:
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		static const BuiltinClicheFileName singleton;
		BuiltinClicheFileName()
			: BuiltinClicheTiny(&Builtin::name.file)
		{}
	};

	class BuiltinClicheFolderName
		: public BuiltinClicheTiny
	{
	public:
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		static const BuiltinClicheFolderName singleton;
		BuiltinClicheFolderName()
			: BuiltinClicheTiny(&Builtin::name.folder)
		{}
	};

	class BuiltinClicheWhen
		: public BuiltinClicheTiny
	{
	public:
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
		const Any* specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const;
	private:
		static const BuiltinClicheWhen singleton;
		BuiltinClicheWhen()
			: BuiltinClicheTiny(&Builtin::name.when)
		{}
	};

	class ImplicitParameter
	{
	public:
		enum ImplicitCode {WHO, WHERE, WHAT, SELF};

		class ImplicitClicheShort
			: public BuiltinPokerClicheShort
		{
		public:
			const Any *node(const Constant *element) const;
			const NodeExpressShort *node(const Express *element) const;
			ImplicitCode code;
		private:
			friend class ImplicitParameter;
			ImplicitClicheShort(const PredefinedName *name, ImplicitCode code)
				: BuiltinPokerClicheShort(name), code(code)
			{}
		};

		class ImplicitClicheTrailer
			: public BuiltinPokerClicheTrailer
		{
		public:
			const Any *node(const Any *const *element) const;
			const Any *node(const Constant *const *element) const;
		private:
			const Constant *dummy;
			friend class ImplicitParameter;
			ImplicitClicheTrailer(const PredefinedName *name, ImplicitCode code)
				: BuiltinPokerClicheTrailer(&Empty::singleton, name), code(code)
			{}
		public:
			ImplicitCode code;
		};

	private:
		ImplicitParameter(const PredefinedName &name, ImplicitCode code)
			: clicheShort(&name, code), clicheTrailer(&name, code)
		{}
		ImplicitClicheShort clicheShort;
		ImplicitClicheTrailer clicheTrailer;
		static const ImplicitParameter who;
		static const ImplicitParameter where_;
		static const ImplicitParameter what;
		static const ImplicitParameter self;
	};

	class BuiltinClicheWhoTag
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheWhoTag()
			: BuiltinClicheTiny(&Builtin::name.who)
		{}
		static const BuiltinClicheWhoTag singleton;
	};

	class BuiltinClicheWhoTagTrailer
		: public BuiltinClicheTrailer
	{
	public:
		const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const;
		const Any *node(const Any *const *elements) const;
	private:
		BuiltinClicheWhoTagTrailer()
			: BuiltinClicheTrailer(&Builtin::name.who, &Empty::singleton, &Builtin::name.who)
		{}
		const Constant *dummy;
		static const BuiltinClicheWhoTagTrailer singleton;
	};

	class BuiltinClicheSyntaxError
		: public BuiltinClicheLong
	{
	public:
		static const BuiltinClicheSyntaxError singleton;
	private:
		BuiltinClicheSyntaxError()
			: BuiltinClicheLong(&Builtin::name.error, &Builtin::name.start, &Builtin::name.end, &Builtin::name.error)
		{}
		const Constant *dummy[2];
	};

	class BuiltinClicheOperationPlus
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationPlus singleton;
		const Any* specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const;
	private:
		BuiltinClicheOperationPlus()
			: BuiltinClicheTiny(&Builtin::name.plus)
		{}
	};

	class BuiltinClicheOperationMinus
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationMinus singleton;
		const Any* specialOperation(Runner &run, const ReallySpecial &special, const Any &argument) const;
	private:
		BuiltinClicheOperationMinus()
			: BuiltinClicheTiny(&Builtin::name.minus)
		{}
	};

	class BuiltinClicheOperationTimes
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
		static const BuiltinClicheOperationTimes singleton;
	private:
		BuiltinClicheOperationTimes()
			: BuiltinClicheTiny(&Builtin::name.times)
		{}
	};

	class BuiltinClicheOperationDivide
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationDivide singleton;
	private:
		BuiltinClicheOperationDivide()
			: BuiltinClicheTiny(&Builtin::name.divide)
		{}
	};

	class BuiltinClicheOperationIntegerDivide
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationIntegerDivide singleton;
	private:
		BuiltinClicheOperationIntegerDivide()
			: BuiltinClicheTiny(&Builtin::name.integerDivide)
		{}
	};

	class BuiltinClicheOperationModulo
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationModulo singleton;
	private:
		BuiltinClicheOperationModulo()
			: BuiltinClicheTiny(&Builtin::name.modulo)
		{}
	};

	class BuiltinClicheOperationEqual
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationEqual singleton;
	private:
		BuiltinClicheOperationEqual()
			: BuiltinClicheTiny(&Builtin::name.equal)
		{}
	};

	class BuiltinClicheOperationNotEqual
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
		static const BuiltinClicheOperationNotEqual singleton;
	private:
		BuiltinClicheOperationNotEqual()
			: BuiltinClicheTiny(&Builtin::name.notEqual)
		{}
	};

	class BuiltinClicheCompare
		: public BuiltinClicheTiny
	{
	public:
		virtual const BuiltinClicheCompare &opposite() const = 0;
		virtual bool compare(double a, double b) const = 0;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	protected:
		BuiltinClicheCompare(const PredefinedName *name)
			: BuiltinClicheTiny(name)
		{}
	};

	class BuiltinClicheOperationLess
		: public BuiltinClicheCompare
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationLess singleton;
		const BuiltinClicheCompare &opposite() const;
		bool compare(double a, double b) const;
	private:
		BuiltinClicheOperationLess()
			: BuiltinClicheCompare(&Builtin::name.less)
		{}
	};

	class BuiltinClicheOperationLessEqual
		: public BuiltinClicheCompare
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationLessEqual singleton;
		const BuiltinClicheCompare &opposite() const;
		bool compare(double a, double b) const;
	private:
		BuiltinClicheOperationLessEqual()
			: BuiltinClicheCompare(&Builtin::name.lessEqual)
		{}
	};

	class BuiltinClicheOperationGreater
		: public BuiltinClicheCompare
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationGreater singleton;
		const BuiltinClicheCompare &opposite() const;
		bool compare(double a, double b) const;
	private:
		BuiltinClicheOperationGreater()
			: BuiltinClicheCompare(&Builtin::name.greater)
		{}
	};

	class BuiltinClicheOperationGreaterEqual
		: public BuiltinClicheCompare
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		static const BuiltinClicheOperationGreaterEqual singleton;
		const BuiltinClicheCompare &opposite() const;
		bool compare(double a, double b) const;
	private:
		BuiltinClicheOperationGreaterEqual()
			: BuiltinClicheCompare(&Builtin::name.greaterEqual)
		{}
	};

	class BuiltinClicheOperationUpDown
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const CallWho *whoOperation(const NodeExpressShort *operation, const Any *who) const;
		bool downwards;
	private:
		static const BuiltinClicheOperationUpDown up;
		static const BuiltinClicheOperationUpDown down;
		BuiltinClicheOperationUpDown(const HashedConstant *name, bool downwards)
			: BuiltinClicheTiny(name), downwards(downwards)
		{}
	};

	class BuiltinClicheTinyDollar
		: public BuiltinClicheTiny
	{
	public:
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		static const BuiltinClicheTinyDollar singleton;
		BuiltinClicheTinyDollar()
			: BuiltinClicheTiny(&Builtin::name.dollar)
		{}
	};

	class BuiltinClicheAssign
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheAssign singleton;
	private:
		BuiltinClicheAssign()
			: BuiltinPokerClicheShort(&Builtin::name.equal)
		{}
	};

	class BuiltinClicheAssignContinue
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheAssignContinue()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.equal)
		{}
		static const BuiltinClicheAssignContinue singleton;
		const Constant *dummy;
	};

	class BuiltinClicheOk
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheOk()
			: BuiltinPokerClicheShort(&Builtin::name.ok)
		{}
		static const BuiltinClicheOk singleton;
	};

	class BuiltinClicheOkTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
		static const BuiltinClicheOkTrailer singleton;
	private:
		BuiltinClicheOkTrailer()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.ok)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheError
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheError singleton;
	private:
		BuiltinClicheError()
			: BuiltinPokerClicheShort(&Builtin::name.error)
		{}
	};

	class BuiltinClicheErrorTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
		static const BuiltinClicheErrorTrailer singleton;
	private:
		BuiltinClicheErrorTrailer()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.error)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheTry
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheTry()
			: BuiltinPokerClicheShort(&Builtin::name.try_)
		{}
		static const BuiltinClicheTry singleton;
	};

	class BuiltinClicheTryTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheTryTrailer()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.try_)
		{}
		static const BuiltinClicheTryTrailer singleton;
		const Constant *dummy;
	};

	class BuiltinClichePossibly
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClichePossibly()
			: BuiltinPokerClicheShort(&Builtin::name.possibly)
		{}
		static const BuiltinClichePossibly singleton;
	};

	class BuiltinClichePossiblyTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClichePossiblyTrailer()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.possibly)
		{}
		static const BuiltinClichePossiblyTrailer singleton;
		const Constant *dummy;
	};

	class BuiltinClicheNeed
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheNeed()
			: BuiltinPokerClicheShort(&Builtin::name.need)
		{}
		static const BuiltinClicheNeed singleton;
	};

	class BuiltinClicheNeedTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Constant *const *element) const;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheNeedTrailer()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.need)
		{}
		static const BuiltinClicheNeedTrailer singleton;
		const Constant *dummy;
	};

	class BuiltinClicheIf
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheIf()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.if_)
		{}
		static const BuiltinClicheIf singleton;
		const Constant *dummy;
	};

	class BuiltinClicheIfElse
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheIfElse()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.if_, &Builtin::name.else_)
		{}
		static const BuiltinClicheIfElse singleton;
		const Constant *dummy[2];
	};

	class BuiltinClicheOr
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheOr()
			: BuiltinClicheTiny(&Builtin::name.or_)
		{}
		static const BuiltinClicheOr singleton;
	};

	class BuiltinClicheAnd
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheAnd()
			: BuiltinClicheTiny(&Builtin::name.and_)
		{}
		static const BuiltinClicheAnd singleton;
	};

	class BuiltinClicheAnyway
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		BuiltinClicheAnyway()
			: BuiltinClicheTiny(&Builtin::name.anyway)
		{}
		static const BuiltinClicheAnyway singleton;
	};

	class BuiltinClicheNot
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheNot()
			: BuiltinClicheTiny(&Builtin::name.not_)
		{}
		static const BuiltinClicheNot singleton;
	};

	class Call
		: public PokerShort
	{
	public:
		Call(const Any *call)
			: PokerShort(BuiltinClicheCall::singleton, call)
		{}
		const Any* callAttribute() const;
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
	};

	class Slot
		: public Call
	{
	public:
		Slot(const Constant *name)
			: Call(name)
		{}
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		const Slot* as_Slot() const;
		void compilePattern(Compiling &compiling) const;
		void compilePattern(Compiling &compiling, size_t offset) const;
		bool compileBuild(CompilingBuild &compiling) const;
		const void *compilePatternIndex() const;
		const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
	};

	class EmptySlot
		: public Slot
	{
	public:
		EmptySlot()
			: Slot(&Empty::singleton)
		{}
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		void compilePattern(Compiling &compiling) const;
		void compilePattern(Compiling &compiling, size_t offset) const;
		bool compileBuild(CompilingBuild &compiling) const;
	};

	class CallWho
		: public PokerLong
	{
	public:
		CallWho(const Any *call, const Any *who)
			: PokerLong(BuiltinClicheCallWho::singleton, call, who)
		{}
		const Any* callAttribute() const;
		const Any* whoAttribute() const;
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *step_(Runner &run) const;
		void compilePattern(Compiling &compiling) const;
		const void *compilePatternIndex() const;
		const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
	private:
		const Any* dummy[1];
	};

	class WhoAssign
		: public CallWho
	{
	private:
		friend class WhoAssignShort;
		friend class WhoAssignContinue;
		WhoAssign(const Express *call, const Any *who)
			: CallWho(call, who)
		{}
	};

	class WhoAssignShort
		: public WhoAssign
	{
	public:
		WhoAssignShort(const PokerShort *call, const Any *who)
			: WhoAssign(call, who)
		{}
		void compileRulePattern(Compiling &compiling, const Rule &rule) const;
	};

	class WhoAssignContinue
		: public WhoAssign
	{
	public:
		WhoAssignContinue(const PokerTrailer *call, const Any *who)
			: WhoAssign(call, who)
		{}
	};

	class Rule
		: public NodeExpressLong
	{
	public:
		Rule(const Any* const *element)
			: NodeExpressLong(BuiltinClicheRule::singleton, element)
		{}
		Rule(const Any *match, const Any *action)
			: NodeExpressLong(BuiltinClicheRule::singleton, match, action)
		{}
		const Any *match() const;
		const Any *action() const;
		const Rule* as_Rule() const;
	private:
		const Any* dummy;
	};

	class NameValue
		: public NodeExpressTrailer
	{
	public:
		NameValue(const Any* const *element)
			: NodeExpressTrailer(BuiltinClicheNameValue::singleton, element)
		{}
//		NameValue(const Any *value, const Any *name)
//			: NodeExpressTrailer(BuiltinClicheNameValue::singleton, value, name)
//		{}
		bool isNameValuePair(const Constant *&name, const Any *&value) const;
	private:
		const Any* dummy;
	};

	class WhoExpressOperation
		: public CallWho
	{
	public:
		WhoExpressOperation(const NodeExpressShort *call, const Any *who)
			:  CallWho(call, who)
		{}
		const Step *step_(Runner &run) const;
		virtual const Step *pass(Runner &run, long value);
		virtual const Step *pass(Runner &run, double value);
		virtual const Step *pass(Runner &run, const Integer &value);
		virtual const Step *pass(Runner &run, const Float &value);
		virtual const Step *pass(Runner &run, const PilsString &value);
		virtual const Step *pass(Runner &run, const Cliche &value);
		virtual const Step *pass(Runner &run, const ListConstant &value);
		virtual const Step *pass(Runner &run, const NodeConstantLong &value);
		virtual const Step *pass(Runner &run, const NodeConstantShort &value);
		virtual const Step *pass(Runner &run, const ListExpress &value);
		virtual const Step *pass(Runner &run, const NodeExpressLong &value);
		virtual const Step *pass(Runner &run, const NodeExpressShort &value);
		virtual const Step *pass(Runner &run, const Special &value);
		virtual const Step *pass(Runner &run, const Integer *value);
		virtual const Step *pass(Runner &run, const Float *value);
		virtual const Step *pass(Runner &run, const PilsDate *value);
		virtual const Step *pass(Runner &run, const Timestamp *value);
		virtual const Step *pass(Runner &run, const Duration *value);
		virtual const Step *pass(Runner &run, const PilsString *value);
		virtual const Step *pass(Runner &run, const Cliche *value);
		virtual const Step *pass(Runner &run, const ListConstant *value);
		virtual const Step *pass(Runner &run, const NodeConstantLong *value);
		virtual const Step *pass(Runner &run, const NodeConstantShort *value);
		virtual const Step *pass(Runner &run, const ListExpress *value);
		virtual const Step *pass(Runner &run, const NodeExpressLong *value);
		virtual const Step *pass(Runner &run, const NodeExpressShort *value);
		virtual const Step *pass(Runner &run, const Special *value);
	};

	class BuiltinClicheChannel
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		static const BuiltinClicheChannel singleton;
	private:
		BuiltinClicheChannel()
			: BuiltinClicheTiny(&Builtin::name.channel)
		{}
	};

	class Channel;
	class Listener
		: public Constant
	{
	private:
		const Step *step_(Runner &run) const;
		bool write(Writing &writing, WriteState state, long level, const Constant *dot) const;
		const Step *passUncounted(Runner &run) const;
		const Step *passCounted(Runner &run) const;
		const NodeConstantShort *newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const;
		const QuickCalling *matching(Runner &run, void** stack, const QuickMatch &match) const;
		bool convert(Converter &converter) const;
		friend class Channel;
		Listener(const Channel *channel, const Any *ear);
		const Channel *const channel;
	public:
		const Any *const ear;
		Listener *next;
	private:
		Listener **previous;
		size_t unlinkAndGetSize();
	};

	class Channel
		: public NodeConstantTiny
	{
	public:
		Channel(const HashedConstant *&link, const BuiltinClicheChannel &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value), listening(NULL)
		{}
		const Channel *as_Channel() const;
		const Listener *listen(const Any *ear) const;
	private:
		friend class Listener;
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
		size_t unlinkAndGetSize();
		mutable Listener *listening;
	};

	class BuiltinClicheStrap
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
	private:
		BuiltinClicheStrap()
			: BuiltinClicheTiny(&Builtin::name.strap)
		{}
		static const BuiltinClicheStrap singleton;
	};

	class WhoUntypedOperation;

	class BuiltinClicheUntypedOperation
		: public BuiltinClicheTiny
	{
	public:
		using BuiltinClicheTiny::node;
		virtual const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const = 0;
		virtual const Step *gotOperand(Runner &run, const WhoAssign &what, const Any *value, const Any *assignValue) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	protected:
		BuiltinClicheUntypedOperation(const HashedConstant *name)
			: BuiltinClicheTiny(name)
		{}
	};

	class UntypedOperationConstant
		: public NodeConstantTiny
	{
	public:
		UntypedOperationConstant(const HashedConstant *&link, const BuiltinClicheUntypedOperation &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class UntypedOperationExpress
		: public NodeExpressTiny
	{
	public:
		UntypedOperationExpress(const BuiltinClicheUntypedOperation &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
	};

	class WhoUntypedOperation
		: public CallWho
	{
	protected:
		WhoUntypedOperation(const Any *call, const Any *who)
			:  CallWho(call, who)
		{}
	};

	class WhoUntypedOperationConstant
		: public WhoUntypedOperation
	{
	public:
		WhoUntypedOperationConstant(const UntypedOperationConstant *call, const Any *who)
			: WhoUntypedOperation(call, who)
		{}
		const Step *step_(Runner &run) const;
		const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
	};

	class WhoUntypedOperationExpress
		: public WhoUntypedOperation
	{
	public:
		WhoUntypedOperationExpress(const UntypedOperationExpress *call, const Any *who)
			: WhoUntypedOperation(call, who)
		{}
		const Step *step_(Runner &run) const;
		const Step *assign(Runner &run, const Any *assignValue, const WhoAssign &what) const;
	};

	class BuiltinClicheMakeCliche
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheMakeCliche()
			: BuiltinClicheUntypedOperation(&Builtin::name.cliche)
		{}
		static const BuiltinClicheMakeCliche singleton;
	};

	class BuiltinClicheMakeName
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		BuiltinClicheMakeName()
			: BuiltinClicheUntypedOperation(&Builtin::name.doubleSlash)
		{}
		static const BuiltinClicheMakeName singleton;
	};

	class BuiltinClicheCombine
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheCombine()
			: BuiltinClicheUntypedOperation(&Builtin::name.combine)
		{}
		static const BuiltinClicheCombine singleton;
	};

	class BuiltinClicheCombined
		: public BuiltinPokerClicheTrailer
	{
	public:
		static const BuiltinClicheCombined singleton;
		const Any *node(const Any *const *element) const;
	private:
		BuiltinClicheCombined()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.combine)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheRecall
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheRecall()
			: BuiltinClicheUntypedOperation(&Builtin::name.recall)
		{}
		static const BuiltinClicheRecall singleton;
	};

	class BuiltinClicheRecalling
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheRecalling singleton;
	private:
		BuiltinClicheRecalling()
			: BuiltinPokerClicheShort(&Builtin::name.recall)
		{}
	};

	class BuiltinClicheListen
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheListen()
			: BuiltinClicheUntypedOperation(&Builtin::name.listen)
		{}
		static const BuiltinClicheListen singleton;
	};

	class BuiltinClicheCalling
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		const Step *gotOperand(Runner &run, const WhoAssign &what, const Any *value, const Any *assignValue) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		BuiltinClicheCalling()
			: BuiltinClicheUntypedOperation(&Builtin::name.call)
		{}
		static const BuiltinClicheCalling singleton;
	};

	class BuiltinClicheCallingOk
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheCallingOk singleton;
	private:
		BuiltinClicheCallingOk()
			: BuiltinClicheTiny(&Builtin::name.ok)
		{}
	};

	class BuiltinClicheEach
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheEach()
			: BuiltinClicheUntypedOperation(&Builtin::name.each)
		{}
		static const BuiltinClicheEach singleton;
	};

	class BuiltinClicheEvery
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheEvery()
			: BuiltinClicheUntypedOperation(&Builtin::name.every)
		{}
		static const BuiltinClicheEvery singleton;
	};

	class BuiltinClicheWhile
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheWhile()
			: BuiltinClicheUntypedOperation(&Builtin::name.while_)
		{}
		static const BuiltinClicheWhile singleton;
	};

	class BuiltinClicheExcept
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheExcept()
			: BuiltinClicheUntypedOperation(&Builtin::name.except)
		{}
		static const BuiltinClicheExcept singleton;
	};

	class BuiltinClicheFind
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheFind()
			: BuiltinClicheUntypedOperation(&Builtin::name.find)
		{}
		static const BuiltinClicheFind singleton;
	};

	class BuiltinClicheFold
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheFold()
			: BuiltinClicheUntypedOperation(&Builtin::name.fold)
		{}
		static const BuiltinClicheFold singleton;
	};

	class BuiltinClicheFirst
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheFirst()
			: BuiltinClicheUntypedOperation(&Builtin::name.first)
		{}
		static const BuiltinClicheFirst singleton;
	};

	class BuiltinClicheMin
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheMin()
			: BuiltinClicheUntypedOperation(&Builtin::name.min_)
		{}
		static const BuiltinClicheMin singleton;
	};

	class BuiltinClicheMax
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheMax()
			: BuiltinClicheUntypedOperation(&Builtin::name.max_)
		{}
		static const BuiltinClicheMax singleton;
	};

	class BuiltinClicheSum
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheSum()
			: BuiltinClicheUntypedOperation(&Builtin::name.sum_)
		{}
		static const BuiltinClicheSum singleton;
	};

	class BuiltinClicheRepeat
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheRepeat()
			: BuiltinClicheUntypedOperation(&Builtin::name.repeat)
		{}
		static const BuiltinClicheRepeat singleton;
	};

	class BuiltinClicheAgain
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheAgain()
			: BuiltinClicheUntypedOperation(&Builtin::name.again)
		{}
		static const BuiltinClicheAgain singleton;
	};

	class BuiltinClicheTrial
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		void compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const;
	private:
		BuiltinClicheTrial()
			: BuiltinClicheUntypedOperation(&Builtin::name.try_)
		{}
		static const BuiltinClicheTrial singleton;
	};

	class BuiltinClicheTransform
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheTransform()
			: BuiltinClicheUntypedOperation(&Builtin::name.transformOperator)
		{}
		static const BuiltinClicheTransform singleton;
	};

	class BuiltinClicheBut
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheBut()
			: BuiltinClicheUntypedOperation(&Builtin::name.but)
		{}
		static const BuiltinClicheBut singleton;
	};

	class BuiltinClicheThroughOperation
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheThroughOperation()
			: BuiltinClicheUntypedOperation(&Builtin::name.through)
		{}
		static const BuiltinClicheThroughOperation singleton;
	};

	class BuiltinClicheAroundOperation
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheAroundOperation()
			: BuiltinClicheUntypedOperation(&Builtin::name.around)
		{}
		static const BuiltinClicheAroundOperation singleton;
	};

	class BuiltinClicheHeadset
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheHeadset()
			: BuiltinClicheUntypedOperation(&Builtin::name.head)
		{}
		static const BuiltinClicheHeadset singleton;
	};

	class BuiltinClicheLegs
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheLegs()
			: BuiltinClicheUntypedOperation(&Builtin::name.legs)
		{}
		static const BuiltinClicheLegs singleton;
	};

	class BuiltinClicheMerge
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheMerge()
			: BuiltinClicheUntypedOperation(&Builtin::name.merge)
		{}
		static const BuiltinClicheMerge singleton;
	};

	class BuiltinClicheBind
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheBind()
			: BuiltinClicheUntypedOperation(&Builtin::name.bind)
		{}
		static const BuiltinClicheBind singleton;
	};

	class BuiltinClicheWithout
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheWithout()
			: BuiltinClicheUntypedOperation(&Builtin::name.without)
		{}
		friend class SinkWithout;
		static const BuiltinClicheWithout singleton;
	};

	class BuiltinClicheSplit
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheSplit()
			: BuiltinClicheUntypedOperation(&Builtin::name.split)
		{}
		static const BuiltinClicheSplit singleton;
	};

	class BuiltinClicheSplice
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheSplice()
			: BuiltinClicheUntypedOperation(&Builtin::name.splice)
		{}
		friend class PipeListSeparator;
		static const BuiltinClicheSplice singleton;
	};

	class BuiltinClicheOrder
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheOrder()
			: BuiltinClicheUntypedOperation(&Builtin::name.order)
		{}
		friend class PipeOrder;
		static const BuiltinClicheOrder singleton;
	};

	class BuiltinClicheReplaceBase
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	protected:
		virtual void pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const = 0;
		virtual bool invalidSearchstringLength(size_t length) const;
		BuiltinClicheReplaceBase(const HashedConstant *name)
			: BuiltinClicheUntypedOperation(name)
		{}
	};

	class BuiltinClicheReplace
		: public BuiltinClicheReplaceBase
	{
	private:
		void pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const;
		bool invalidSearchstringLength(size_t length) const;
		BuiltinClicheReplace()
			: BuiltinClicheReplaceBase(&Builtin::name.replace)
		{}
		static const BuiltinClicheReplace singleton;
	};

	class BuiltinClicheReplaceBeginning
		: public BuiltinClicheReplaceBase
	{
	private:
		void pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const;
		BuiltinClicheReplaceBeginning()
			: BuiltinClicheReplaceBase(&Builtin::name.replaceBeginning)
		{}
		static const BuiltinClicheReplaceBeginning singleton;
	};

	class BuiltinClicheReplaceEnding
		: public BuiltinClicheReplaceBase
	{
	public:
		void pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const;
		BuiltinClicheReplaceEnding()
			: BuiltinClicheReplaceBase(&Builtin::name.replaceEnding)
		{}
		static const BuiltinClicheReplaceEnding singleton;
	};

	class BuiltinClicheRange
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeExpressShort *node(const Express *element) const;
		virtual void rangeSink(Runner &run, long range, const CallWho &what) const = 0;
	protected:
		BuiltinClicheRange(const HashedConstant *name)
			: BuiltinClicheTiny(name)
		{}
	};

	class BuiltinClichePlusRange
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClichePlusRange singleton;
		BuiltinClichePlusRange()
			: BuiltinClicheRange(&Builtin::name.plusRange)
		{}
	};

	class BuiltinClichePlusSlackRange
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClichePlusSlackRange singleton;
		BuiltinClichePlusSlackRange()
			: BuiltinClicheRange(&Builtin::name.plusSlackRange)
		{}
	};

	class BuiltinClichePlusRangeReverse
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClichePlusRangeReverse singleton;
		BuiltinClichePlusRangeReverse()
			: BuiltinClicheRange(&Builtin::name.plusRangeReverse)
		{}
	};

	class BuiltinClichePlusSlackRangeReverse
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClichePlusSlackRangeReverse singleton;
		BuiltinClichePlusSlackRangeReverse()
			: BuiltinClicheRange(&Builtin::name.plusSlackRangeReverse)
		{}
	};

	class BuiltinClicheMinusRange
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClicheMinusRange singleton;
		BuiltinClicheMinusRange()
			: BuiltinClicheRange(&Builtin::name.minusRange)
		{}
	};

	class BuiltinClicheMinusSlackRange
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClicheMinusSlackRange singleton;
		BuiltinClicheMinusSlackRange()
			: BuiltinClicheRange(&Builtin::name.minusSlackRange)
		{}
	};

	class BuiltinClicheMinusRangeReverse
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClicheMinusRangeReverse singleton;
		BuiltinClicheMinusRangeReverse()
			: BuiltinClicheRange(&Builtin::name.minusRangeReverse)
		{}
	};

	class BuiltinClicheMinusSlackRangeReverse
		: public BuiltinClicheRange
	{
	public:
		void rangeSink(Runner &run, long range, const CallWho &what) const;
	private:
		static const BuiltinClicheMinusSlackRangeReverse singleton;
		BuiltinClicheMinusSlackRangeReverse()
			: BuiltinClicheRange(&Builtin::name.minusSlackRangeReverse)
		{}
	};

	class BuiltinClicheBuilderShort
		: public BuiltinPokerClicheShort
	{
	public:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheBuilderShort(const BuilderName *name)
			: BuiltinPokerClicheShort(name)
		{}
		static const BuiltinClicheBuilderShort listBuilder;
		static const BuiltinClicheBuilderShort nodeBuilder;
		static const BuiltinClicheBuilderShort mindBuilder;
		static const BuiltinClicheBuilderShort exitBuilder;
	};

	class BuiltinClicheBuilderTrailer
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
		const Any *node(const Constant *const *element) const;
	private:
		BuiltinClicheBuilderTrailer(const BuilderName *name)
			: BuiltinPokerClicheTrailer(&Empty::singleton, name)
		{}
		static const BuiltinClicheBuilderTrailer listBuilder;
		static const BuiltinClicheBuilderTrailer nodeBuilder;
		static const BuiltinClicheBuilderTrailer mindBuilder;
		static const BuiltinClicheBuilderTrailer exitBuilder;
		const BuilderName *builderName;
	};

	class BuiltinClicheBuilding
		: public BuiltinPokerClicheTrailer
	{
	public:
		const Any *node(const Any *const *element) const;
		static const BuiltinClicheBuilding singleton;
	private:
		BuiltinClicheBuilding()
			: BuiltinPokerClicheTrailer(&Empty::singleton, &Builtin::name.building)
		{}
		const Constant *dummy;
	};

	class BuiltinClicheGroups
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheGroups singleton;
	private:
		BuiltinClicheGroups()
			: BuiltinClicheUntypedOperation(&Builtin::name.groups)
		{}
	};

	class BuiltinClicheFirsts
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheFirsts singleton;
	private:
		BuiltinClicheFirsts()
			: BuiltinClicheUntypedOperation(&Builtin::name.firsts)
		{}
	};

	class BuiltinClicheSingles
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheSingles singleton;
	private:
		BuiltinClicheSingles()
			: BuiltinClicheUntypedOperation(&Builtin::name.singles)
		{}
	};

	class BuiltinClicheLasts
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheLasts singleton;
	private:
		BuiltinClicheLasts()
			: BuiltinClicheUntypedOperation(&Builtin::name.lasts)
		{}
	};

	class BuiltinClicheFolds
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheFolds singleton;
	private:
		BuiltinClicheFolds()
			: BuiltinClicheUntypedOperation(&Builtin::name.folds)
		{}
	};

	class BuiltinClicheDistinct
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
		static const BuiltinClicheDistinct singleton;
	private:
		BuiltinClicheDistinct()
			: BuiltinClicheUntypedOperation(&Builtin::name.distinct)
		{}
	};

	class BuiltinClicheSearchAbstract
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeExpressShort *node(const Express *element) const;
		virtual size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const = 0;
		virtual size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const = 0;
	protected:
		BuiltinClicheSearchAbstract(const SearchNameAbstract *head)
			: BuiltinClicheTiny(head)
		{}
	};

	class BuiltinClicheSearchCount
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchCount(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchCount plain;
	};

	class BuiltinClicheSearchContains
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchContains(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
		static const BuiltinClicheSearchContains plain;
		static const BuiltinClicheSearchContains plusRange;
		static const BuiltinClicheSearchContains minusRange;
	};

	class BuiltinClicheSearchContainsReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchContainsReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchContainsReverse plain;
		static const BuiltinClicheSearchContainsReverse plusRange;
		static const BuiltinClicheSearchContainsReverse minusRange;
	};

	class BuiltinClicheSearchTill
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchTill(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
		static const BuiltinClicheSearchTill plain;
		static const BuiltinClicheSearchTill plusRange;
		static const BuiltinClicheSearchTill minusRange;
	};

	class BuiltinClicheSearchTillReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchTillReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchTillReverse plain;
		static const BuiltinClicheSearchTillReverse plusRange;
		static const BuiltinClicheSearchTillReverse minusRange;
	};

	class BuiltinClicheSearchSpread
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchSpread(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchSpread plain;
		static const BuiltinClicheSearchSpread plusRange;
		static const BuiltinClicheSearchSpread minusRange;
	};

	class BuiltinClicheSearchSpreadReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchSpreadReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchSpreadReverse plain;
		static const BuiltinClicheSearchSpreadReverse plusRange;
		static const BuiltinClicheSearchSpreadReverse minusRange;
	};

	class BuiltinClicheSearchPrefix
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchPrefix(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchPrefix plain;
		static const BuiltinClicheSearchPrefix plusRange;
		static const BuiltinClicheSearchPrefix minusRange;
	};

	class BuiltinClicheSearchPrefixReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchPrefixReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchPrefixReverse plain;
		static const BuiltinClicheSearchPrefixReverse plusRange;
		static const BuiltinClicheSearchPrefixReverse minusRange;
	};

	class BuiltinClicheSearchRhyme
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchRhyme(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchRhyme plain;
		static const BuiltinClicheSearchRhyme plusRange;
		static const BuiltinClicheSearchRhyme minusRange;
	};

	class BuiltinClicheSearchRhymeReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchRhymeReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchRhymeReverse plain;
		static const BuiltinClicheSearchRhymeReverse plusRange;
		static const BuiltinClicheSearchRhymeReverse minusRange;
	};

	class BuiltinClicheSearchUnrhyme
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchUnrhyme(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchUnrhyme plain;
		static const BuiltinClicheSearchUnrhyme plusRange;
		static const BuiltinClicheSearchUnrhyme minusRange;
	};

	class BuiltinClicheSearchUnrhymeReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchUnrhymeReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchUnrhymeReverse plain;
		static const BuiltinClicheSearchUnrhymeReverse plusRange;
		static const BuiltinClicheSearchUnrhymeReverse minusRange;
	};

	class BuiltinClicheSearchPlus
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchPlus(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchPlus plain;
		static const BuiltinClicheSearchPlus plusRange;
		static const BuiltinClicheSearchPlus minusRange;
	};

	class BuiltinClicheSearchPlusReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchPlusReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchPlusReverse plain;
		static const BuiltinClicheSearchPlusReverse plusRange;
		static const BuiltinClicheSearchPlusReverse minusRange;
	};

	class BuiltinClicheSearchMinus
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchMinus(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchMinus plain;
		static const BuiltinClicheSearchMinus plusRange;
		static const BuiltinClicheSearchMinus minusRange;
	};

	class BuiltinClicheSearchMinusReverse
		: public BuiltinClicheSearchAbstract
	{
	public:
		BuiltinClicheSearchMinusReverse(const SearchNameAbstract *head)
			: BuiltinClicheSearchAbstract(head)
		{}
		size_t search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const;
		size_t search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const;
	private:
		static const BuiltinClicheSearchMinusReverse plain;
		static const BuiltinClicheSearchMinusReverse plusRange;
		static const BuiltinClicheSearchMinusReverse minusRange;
	};

	class SearchString
		: public NodeConstantTiny
	{
	public:
		SearchString(const HashedConstant *&link, const BuiltinClicheSearchAbstract &cliche, const PilsString *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
	};

	class SearchListConstant
		: public NodeConstantTiny
	{
	public:
		SearchListConstant(const HashedConstant *&link, const BuiltinClicheSearchAbstract &cliche, const ListConstant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const CallWho *callWho(const Any *who) const;
		void compileTypecheck(Compiling &compiling, const CallWho &pattern) const;
	};

	class SearchExpress
		: public NodeExpressTiny
	{
	public:
		const CallWho *callWho(const Any *who) const;
		SearchExpress(const BuiltinClicheSearchAbstract &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
	};

	class BuiltinClicheRound
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheRound()
			: BuiltinClicheUntypedOperation(&Builtin::name.round_)
		{}
		static const BuiltinClicheRound singleton;
	};

	class BuiltinClicheTruncate
		: public BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheTruncate()
			: BuiltinClicheUntypedOperation(&Builtin::name.truncate_)
		{}
		static const BuiltinClicheTruncate singleton;
	};

	/* Register special objects for COM automation etc.
	 * Body wil be defined in the Plumming project.
	 */

	class Plum
	{
	public:
		static const Special *cake();
	private:
		Plum();
		const Special &plumcake;
		static Plum singleton;
	};

	/* Debugging output
	 */

	class BuiltinClicheBug
		: BuiltinClicheUntypedOperation
	{
	public:
		const Step *gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const;
	private:
		BuiltinClicheBug()
			: BuiltinClicheUntypedOperation(&Builtin::name.bug)
		{}
		static const BuiltinClicheBug singleton;
	};

	/* Threading
	 */

	class BuiltinClicheThread
		: public BuiltinPokerClicheShort
	{
	private:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheThread singleton;
		BuiltinClicheThread()
			: BuiltinPokerClicheShort(&Builtin::name.thread)
		{}
	};

	class BuiltinClicheKnot
		: public BuiltinClicheTiny
	{
	public:
		const NodeConstantShort *newNode(const HashedConstant *&link, const Integer *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Float *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsColor *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsDate *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Timestamp *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Duration *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Cliche *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const;
		const NodeConstantShort *newNode(const HashedConstant *&link, const Listener *value) const;
		const NodeExpressShort *node(const Express *element) const;
	private:
		BuiltinClicheKnot()
			: BuiltinClicheTiny(&Builtin::name.knot)
		{}
		static const BuiltinClicheKnot singleton;
	};

	class BuiltinClicheLater
		: public BuiltinPokerClicheShort
	{
	private:
		const Any *node(const Constant *element) const;
		const NodeExpressShort *node(const Express *element) const;
		static const BuiltinClicheLater singleton;
		BuiltinClicheLater()
			: BuiltinPokerClicheShort(&Builtin::name.later)
		{}
	};
}
#endif
