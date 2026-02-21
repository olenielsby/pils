/* This file is public domain */
#ifndef DEFINE_PILS_QUICKSTEP_H
#define DEFINE_PILS_QUICKSTEP_H
#include "catchy.h"
namespace PILS
{
	class QuickStep
	{
	};

	class QuickCalling
		: QuickStep
	{
	public:
		virtual const QuickCalling *quickCalling(Runner &run, const Any &call, const void *key) const = 0;
		virtual const QuickCalling *quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const;
		struct Link
		{
			union
			{
				const Link *next;
				const QuickCalling *target;
			};
			Link(const Link *&link)
			{
				next = link;
				link = this;
			}
		};
	};

	class QuickBeginRule
		: public QuickCalling
	{
	public:
		QuickBeginRule(const Cliche &cliche)
			: variableCount(cliche.count - 1)
		{}
		const QuickCalling *quickCalling(Runner &run, const Any &call, const void *key) const;
		const QuickCalling *quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const;
	private:
		size_t variableCount;
	};

	class QuickMatch
		: public QuickStep
	{
	public:
		virtual const QuickCalling *match(Runner &run, void **stack, const Integer &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Float &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Duration &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Special &value) const = 0;
		virtual const QuickCalling *match(Runner &run, void **stack, const Listener &value) const = 0;
	};

	class QuickFail
		: public QuickMatch
	{
	public:
		QuickFail(const QuickCalling::Link *&fail)
			: fail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	protected:
		const QuickCalling::Link fail;
	};

	class QuickTestPlus
		: QuickFail
	{
	public:
		QuickTestPlus(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
	};

	class QuickTestCount
		: QuickFail
	{
	public:
		QuickTestCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
	};

	class QuickTestInteger
		: QuickFail
	{
	public:
		QuickTestInteger(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
	};

	class QuickTestNumber
		: QuickFail
	{
	public:
		QuickTestNumber(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
	};

	class QuickTestString
		: QuickFail
	{
	public:
		QuickTestString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
	};

	class QuickTestTimestamp
		: QuickFail
	{
	public:
		QuickTestTimestamp(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
	};

	class QuickTestPilsColor
		: QuickFail
	{
	public:
		QuickTestPilsColor(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
	};

	class QuickTestPilsDate
		: QuickFail
	{
	public:
		QuickTestPilsDate(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
	};

	class QuickTestDuration
		: QuickFail
	{
	public:
		QuickTestDuration(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
	};

	class QuickTestPlusString
		: QuickFail
	{
	public:
		QuickTestPlusString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
	};

	class QuickTestPlusPlusString
		: QuickFail
	{
	public:
		QuickTestPlusPlusString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
	};

	class QuickTestList
		: QuickFail
	{
	public:
		QuickTestList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
	};

	class QuickTestPlusList
		: QuickFail
	{
	public:
		QuickTestPlusList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
	};

	class QuickTestPlusPlusList
		: QuickFail
	{
	public:
		QuickTestPlusPlusList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
	};

	class QuickTestCliche
		: QuickFail
	{
	public:
		QuickTestCliche(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
	};

	class QuickTestNode
		: protected QuickFail
	{
	public:
		QuickTestNode(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	};

	class QuickTestLegs
		: QuickTestNode
	{
	public:
		QuickTestLegs(const QuickCalling::Link *&fail)
			: QuickTestNode(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
	};

	class QuickTestConstant
		: QuickFail
	{
	public:
		QuickTestConstant(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	};

	class QuickTestLanguage
		: QuickFail
	{
	public:
		QuickTestLanguage(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
	};

	class QuickTestListener
		: QuickFail
	{
	public:
		QuickTestListener(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	};

	class QuickTestSpecialTypecheck
		: QuickFail
	{
	public:
		QuickTestSpecialTypecheck(const QuickCalling::Link *&fail, Converter &check_)
			: QuickFail(fail), check_(check_)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
	private:
		Converter &check_;
	};
		
	class QuickTestRecognizerTypecheck
		: QuickFail
	{
	public:
		QuickTestRecognizerTypecheck(const QuickCalling::Link *&fail, Recognizer &check_)
			: QuickFail(fail), check_(check_)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		Recognizer &check_;
	};

	class QuickTestSearchString
		: QuickFail
	{
	public:
		QuickTestSearchString(const QuickCalling::Link *&fail, const SearchString &search)
			: QuickFail(fail), search(search)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
	private:
		const SearchString &search;
	};

	class QuickTestSearchListConstant
		: QuickFail
	{
	public:
		QuickTestSearchListConstant(const QuickCalling::Link *&fail, const SearchListConstant &search)
			: QuickFail(fail), search(search)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
	private:
		const SearchListConstant &search;
	};

	class QuickFetch
		: public QuickMatch
	{
	public:
		QuickFetch(size_t offset)
			: offset(offset)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	private:
		size_t offset;
	};

	class QuickPop
		: public QuickMatch
	{
	public:
		QuickPop(){}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	};

	class QuickFetchNodeHead
		: public QuickFail
	{
	public:
		QuickFetchNodeHead(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	};

	class QuickFetchNodeAttribute
		: public QuickFail
	{
	public:
		QuickFetchNodeAttribute(const QuickCalling::Link *&fail, const Constant &name)
			: QuickFail(fail), name(name)
		{}
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		const Constant &name;
	};

	class QuickFetchClicheShortAttribute
		: public QuickFail
	{
	public:
		QuickFetchClicheShortAttribute(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
	};

	class QuickFetchClicheName
		: public QuickFail
	{
	public:
		QuickFetchClicheName(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
	};

	class QuickFetchStringCount
		: public QuickFail
	{
	public:
		QuickFetchStringCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
	};

	class QuickFetchListCount
		: public QuickFail
	{
	public:
		QuickFetchListCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
	};

	class QuickFetchSpecialAttribute
		: public QuickFail
	{
	public:
		QuickFetchSpecialAttribute(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		virtual const Any *specialAttribute(const Special &value) const = 0;
	};

	class QuickFetchFileName
		: public QuickFetchSpecialAttribute
	{
	public:
		QuickFetchFileName(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
		const Any *specialAttribute(const Special &value) const;
	};

	class QuickFetchFolderName
		: public QuickFetchSpecialAttribute
	{
	public:
		QuickFetchFolderName(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
		const Any *specialAttribute(const Special &value) const;
	};

	class QuickFetchWhen
		: QuickFetchSpecialAttribute
	{
	public:
		QuickFetchWhen(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
		const Any *specialAttribute(const Special &value) const;
	};

	class QuickFetchListElement
		: public QuickFail
	{
	public:
		QuickFetchListElement(const QuickCalling::Link *&fail, const Integer &index)
			: QuickFail(fail), index(index.value - 1)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
	private:
		const size_t index;
	};

	class QuickFetchListElementReverse
		: public QuickFail
	{
	public:
		QuickFetchListElementReverse(const QuickCalling::Link *&fail, const Integer &index)
			: QuickFail(fail), index(-index.value)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
	private:
		const size_t index;
	};

	class QuickVerifyNodeAttributes
		: public QuickFail
	{
	public:
		QuickVerifyNodeAttributes(const QuickCalling::Link *&fail, const Cliche &cliche)
			: QuickFail(fail), cliche(cliche)
		{}
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		const Cliche &cliche;
	};

	class QuickVerifyDefaultCliche
		: public QuickFail
	{
	public:
		QuickVerifyDefaultCliche(const QuickCalling::Link *&fail, const Cliche &cliche)
			: QuickFail(fail), cliche(cliche)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		const Cliche &cliche;
	};

	class QuickFetchNodeAttributeDefault
		: public QuickFail
	{
	public:
		QuickFetchNodeAttributeDefault(const QuickCalling::Link *&fail, const Constant &name, const Any &defaultValue)
			: QuickFail(fail), name(name), defaultValue(defaultValue)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		const Constant &name;
		const Any &defaultValue;
	};

	class QuickClicheShortFetchHeadFetchAttribute
		: public QuickFail
	{
	public:
		QuickClicheShortFetchHeadFetchAttribute(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
	private:
	};

	class QuickFetchThrough
		: public QuickFail
	{
	public:
		QuickFetchThrough(const QuickCalling::Link *&fail, const NodeConstant &through)
			: QuickFail(fail), through(through)
		{}
	protected:
		const QuickCalling *matching(Runner &run, void **stack, const Constant &value, const Constant *result) const;
	private:
		const NodeConstant &through;
	};

	class QuickFetchThroughCall
		: public QuickFetchThrough
	{
	public:
		QuickFetchThroughCall(const QuickCalling::Link *&fail, const NodeConstant &through)
			: QuickFetchThrough(fail, through)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	};

	class QuickFetchThroughTry
		: public QuickFetchThrough
	{
	public:
		QuickFetchThroughTry(const QuickCalling::Link *&fail, const NodeConstant &through)
			: QuickFetchThrough(fail, through)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	};

	class QuickMatchListCountOrNodeCliche
		: public QuickFail
	{
	public:
		QuickMatchListCountOrNodeCliche(const QuickCalling::Link *&fail, const Constant &key)
			: QuickFail(fail), key(key)
		{}
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
	private:
		const Constant &key;
	};

	class QuickFetchSpecialType
		: public QuickFail
	{
	public:
		QuickFetchSpecialType(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
	};

	class QuickIndex
		: public QuickCalling
	{
	public:
		const void *const *begin;
		const void *const *end;
		const QuickCalling *quickCalling(Runner &run, const Any &call, const void *key) const;
		const QuickCalling *quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const;
	};

	class QuickStore
		: QuickMatch
	{
	public:
		QuickStore(size_t slotOffset)
			: slotOffset(slotOffset)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	private:
		size_t slotOffset;
	};

	class QuickIdentical
		: QuickFail
	{
	public:
		QuickIdentical(const QuickCalling::Link *&fail, size_t slotOffset)
			: QuickFail(fail), slotOffset(slotOffset)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	private:
		size_t slotOffset;
	};

	class QuickMatchLiteral
		: protected QuickMatch
	{
	public:
		QuickMatchLiteral(const QuickCalling::Link *&failChain, const Any &thing)
			: failChain(failChain), thing(thing)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	protected:
		const QuickCalling::Link failChain;
		const Any &thing;
	};

	class QuickMatchNotEqual
		: QuickMatchLiteral
	{
	public:
		QuickMatchNotEqual(const QuickCalling::Link *&failChain, const Any &thing)
			: QuickMatchLiteral(failChain, thing)

		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	};

	class QuickCompareDouble
		: QuickFail
	{
	public:
		QuickCompareDouble(const QuickCalling::Link *&failChain, const BuiltinClicheCompare &compare, double value)
			: QuickFail(failChain), compare(compare), value(value)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
	private:
		const BuiltinClicheCompare &compare;
		double value;
	};

	class QuickOffsetStore
		: QuickMatch
	{
	public:
		QuickOffsetStore(size_t offset, size_t slotOffset)
			: offset(offset), slotOffset(slotOffset)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	private:
		size_t offset;
		size_t slotOffset;
	};

	class QuickOffsetIdentical
		: QuickFail
	{
	public:
		QuickOffsetIdentical(const QuickCalling::Link *&fail, size_t offset, size_t slotOffset)
			: QuickFail(fail), offset(offset), slotOffset(slotOffset)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	private:
		size_t offset;
		size_t slotOffset;
	};

	class QuickAction
		: QuickMatch
	{
	public:
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
		virtual void action(Runner &run) const = 0;
	};

	class QuickBuild
		: QuickMatch
	{
	public:
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
		virtual const QuickCalling *build(Runner &run, void **stack) const = 0;
	};

	class QuickBuildFetch
		: QuickBuild
	{
	public:
		QuickBuildFetch(size_t offset) : offset(offset) {}
		const QuickCalling *build(Runner &run, void **stack) const;
	private:
		size_t offset;
	};

	class QuickBuildQuote
		: QuickBuild
	{
	public:
		QuickBuildQuote(const Any &value) : value(value) {}
		const QuickCalling *build(Runner &run, void **stack) const;
	private:
		const Any &value;
	};

	class QuickBuildList
		: QuickBuild
	{
	public:
		QuickBuildList(size_t count) : count(count) {}
		const QuickCalling *build(Runner &run, void **stack) const;
	private:
		size_t count;
	};

	class QuickBuildNodeShort
		: QuickBuild
	{
	public:
		QuickBuildNodeShort(const ClicheShort &cliche) : cliche(cliche) {}
		const QuickCalling *build(Runner &run, void **stack) const;
	private:
		const ClicheShort &cliche;
	};

	class QuickBuildNodeLong
		: QuickBuild
	{
	public:
		QuickBuildNodeLong(const ClicheLong &cliche) : cliche(cliche) {}
		const QuickCalling *build(Runner &run, void **stack) const;
	private:
		const ClicheLong &cliche;
	};

	class QuickImplicit
		: public QuickMatch
	{
	public:
		const QuickCalling *match(Runner &run, void **stack, const Integer &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Float &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Duration &value) const;
		const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const;
		const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
		const QuickCalling *match(Runner &run, void **stack, const Listener &value) const;
	protected:
		QuickImplicit(size_t slotOffset)
			: slotOffset(slotOffset)
		{}
		virtual const Any &fetch(Runner &run) const = 0;
		size_t slotOffset;
	};

	class QuickImplicitWho
		: public QuickImplicit
	{
	public:
		QuickImplicitWho(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
		const Any &fetch(Runner &run) const;
	};

	class QuickImplicitWhere
		: public QuickImplicit
	{
	public:
		QuickImplicitWhere(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
		const Any &fetch(Runner &run) const;
	};

	class QuickImplicitWhat
		: public QuickImplicit
	{
	public:
		QuickImplicitWhat(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
		const Any &fetch(Runner &run) const;
	};

	class QuickImplicitSelf
		: public QuickImplicit
	{
	public:
		QuickImplicitSelf(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
		const Any &fetch(Runner &run) const;
	};

	class QuickActionAny
		: QuickAction
	{
	public:
		QuickActionAny(const Cliche &cliche, const Any &thing, const QuickCalling::Link *&fail)
			: cliche(cliche), thing(thing), fail(fail)
		{}
		void action(Runner &run) const;
		const Cliche &cliche;
		const Any &thing;
		const QuickCalling::Link fail;
	};

	class QuickActionOk
		: QuickAction
	{
	public:
		QuickActionOk(const Cliche &cliche, const Any &thing)
			: cliche(cliche), thing(thing)
		{}
		void action(Runner &run) const;
		const Cliche &cliche;
		const Any &thing;
	};

	class QuickActionOkArgument
		: QuickAction
	{
	public:
		QuickActionOkArgument(const size_t offset)
			: offset(offset)
		{}
		void action(Runner &run) const;
	private:
		const size_t offset;
	};

	class QuickActionOkConstant
		: QuickAction
	{
	public:
		QuickActionOkConstant(const Constant &constant)
			: constant(constant)
		{}
		void action(Runner &run) const;
	private:
		const Constant &constant;
	};

	class QuickBuilt
		: QuickBuild
	{
	public:
		const QuickCalling *build(Runner &run, void **stack) const;
	};

	class SinkCompiled
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
	};

	class SinkCompiledStep
		: public SinkCompiled
	{
	public:
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class SinkCompiledOkValue
		: public SinkCompiledStep
	{
	public:
		SinkCompiledOkValue(const Any *value)
			: value(value)
		{}
		const Step *step_(Runner &run) const;
	private:
		const Any *value;
	};

	class SinkCompiledOk
		: public SinkCompiled
	{
	public:
		SinkCompiledOk(const Any *thing, const Any *whereabout)
			: thing(thing), whereabout(whereabout)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	private:
		const Any *thing;
		const Any *whereabout;
	};

	class SinkCompiledAny
		: public SinkCompiled
	{
	public:
		SinkCompiledAny(const QuickActionAny &action, const NodeExpress *where_)
			: action(action), where_(where_)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		Sink *kick(Runner &run);
		const QuickActionAny &action;
		const NodeExpress *where_;
	};

	class QuickMatchQueryInterface
		: public QuickFail
	{
	public:
		QuickMatchQueryInterface(const QuickCalling::Link *&fail, const InterfaceDesignator &designator)
			: QuickFail(fail), designator(designator)
		{}
		const QuickCalling *match(Runner &run, void **stack, const Special &value) const;
	private:
		const InterfaceDesignator &designator;
	};
}
#endif
