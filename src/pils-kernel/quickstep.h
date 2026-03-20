/* This file is public domain */
#pragma once
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
        const QuickCalling *quickCalling(Runner &run, const Any &call, const void *key) const override;
        const QuickCalling *quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
	};

	class QuickTestCount
		: QuickFail
	{
	public:
		QuickTestCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
	};

	class QuickTestInteger
		: QuickFail
	{
	public:
		QuickTestInteger(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
	};

    class QuickTestNumber
		: QuickFail
	{
	public:
		QuickTestNumber(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
	};

	class QuickTestString
		: QuickFail
	{
	public:
		QuickTestString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
	};

	class QuickTestTimestamp
		: QuickFail
	{
	public:
		QuickTestTimestamp(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
	};

	class QuickTestPilsColor
		: QuickFail
	{
	public:
		QuickTestPilsColor(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
	};

	class QuickTestPilsDate
		: QuickFail
	{
	public:
		QuickTestPilsDate(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
	};

	class QuickTestDuration
		: QuickFail
	{
	public:
		QuickTestDuration(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
	};

	class QuickTestPlusString
		: QuickFail
	{
	public:
		QuickTestPlusString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
	};

	class QuickTestPlusPlusString
		: QuickFail
	{
	public:
		QuickTestPlusPlusString(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
	};

	class QuickTestList
		: QuickFail
	{
	public:
		QuickTestList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
	};

	class QuickTestPlusList
		: QuickFail
	{
	public:
		QuickTestPlusList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
	};

	class QuickTestPlusPlusList
		: QuickFail
	{
	public:
		QuickTestPlusPlusList(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
	};

	class QuickTestCliche
		: QuickFail
	{
	public:
		QuickTestCliche(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
	};

	class QuickTestNode
		: protected QuickFail
	{
	public:
		QuickTestNode(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
	};

	class QuickTestLegs
		: QuickTestNode
	{
	public:
		QuickTestLegs(const QuickCalling::Link *&fail)
			: QuickTestNode(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
	};

	class QuickTestConstant
		: QuickFail
	{
	public:
		QuickTestConstant(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	};

	class QuickTestLanguage
		: QuickFail
	{
	public:
		QuickTestLanguage(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
	};

	class QuickTestListener
		: QuickFail
	{
	public:
		QuickTestListener(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	};

	class QuickTestSpecialTypecheck
		: QuickFail
	{
	public:
		QuickTestSpecialTypecheck(const QuickCalling::Link *&fail, Converter &check_)
			: QuickFail(fail), check_(check_)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	private:
		size_t offset;
	};

	class QuickPop
		: public QuickMatch
	{
	public:
		QuickPop(){}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	};

	class QuickFetchNodeHead
		: public QuickFail
	{
	public:
		QuickFetchNodeHead(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
	};

	class QuickFetchNodeAttribute
		: public QuickFail
	{
	public:
		QuickFetchNodeAttribute(const QuickCalling::Link *&fail, const Constant &name)
			: QuickFail(fail), name(name)
		{}
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
	};

	class QuickFetchClicheName
		: public QuickFail
	{
	public:
		QuickFetchClicheName(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
	};

	class QuickFetchStringCount
		: public QuickFail
	{
	public:
		QuickFetchStringCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
	};

	class QuickFetchListCount
		: public QuickFail
	{
	public:
		QuickFetchListCount(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
	};

	class QuickFetchSpecialAttribute
		: public QuickFail
	{
	public:
		QuickFetchSpecialAttribute(const QuickCalling::Link *&fail)
			: QuickFail(fail)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
		virtual const Any *specialAttribute(const Special &value) const = 0;
	};

	class QuickFetchFileName
		: public QuickFetchSpecialAttribute
	{
	public:
		QuickFetchFileName(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
        const Any *specialAttribute(const Special &value) const override;
	};

	class QuickFetchFolderName
		: public QuickFetchSpecialAttribute
	{
	public:
		QuickFetchFolderName(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
        const Any *specialAttribute(const Special &value) const override;
	};

	class QuickFetchWhen
		: QuickFetchSpecialAttribute
	{
	public:
		QuickFetchWhen(const QuickCalling::Link *&fail)
			: QuickFetchSpecialAttribute(fail)
		{}
        const Any *specialAttribute(const Special &value) const override;
	};

	class QuickFetchListElement
		: public QuickFail
	{
	public:
		QuickFetchListElement(const QuickCalling::Link *&fail, const Integer &index)
			: QuickFail(fail), index(index.value - 1)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	};

	class QuickFetchThroughTry
		: public QuickFetchThrough
	{
	public:
		QuickFetchThroughTry(const QuickCalling::Link *&fail, const NodeConstant &through)
			: QuickFetchThrough(fail, through)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
	};

	class QuickMatchListCountOrNodeCliche
		: public QuickFail
	{
	public:
		QuickMatchListCountOrNodeCliche(const QuickCalling::Link *&fail, const Constant &key)
			: QuickFail(fail), key(key)
		{}
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
	};

	class QuickIndex
		: public QuickCalling
	{
	public:
		const void *const *begin;
		const void *const *end;
        const QuickCalling *quickCalling(Runner &run, const Any &call, const void *key) const override;
        const QuickCalling *quickCalling(Runner &run, const Any &call, const Any &assignValue, const void *key) const override;
	};

	class QuickStore
		: QuickMatch
	{
	public:
		QuickStore(size_t slotOffset)
			: slotOffset(slotOffset)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
	};

	class QuickCompareDouble
		: QuickFail
	{
	public:
		QuickCompareDouble(const QuickCalling::Link *&failChain, const BuiltinClicheCompare &compare, double value)
			: QuickFail(failChain), compare(compare), value(value)
		{}
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
    private:
		size_t offset;
		size_t slotOffset;
	};

	class QuickAction
		: QuickMatch
	{
	public:
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
        virtual void action(Runner &run) const = 0;
	};

	class QuickBuild
		: QuickMatch
	{
	public:
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
		virtual const QuickCalling *build(Runner &run, void **stack) const = 0;
	};

	class QuickBuildFetch
		: QuickBuild
	{
	public:
		QuickBuildFetch(size_t offset) : offset(offset) {}
        const QuickCalling *build(Runner &run, void **stack) const override;
	private:
		size_t offset;
	};

	class QuickBuildQuote
		: QuickBuild
	{
	public:
		QuickBuildQuote(const Any &value) : value(value) {}
        const QuickCalling *build(Runner &run, void **stack) const override;
	private:
		const Any &value;
	};

	class QuickBuildList
		: QuickBuild
	{
	public:
		QuickBuildList(size_t count) : count(count) {}
        const QuickCalling *build(Runner &run, void **stack) const override;
	private:
		size_t count;
	};

	class QuickBuildNodeShort
		: QuickBuild
	{
	public:
		QuickBuildNodeShort(const ClicheShort &cliche) : cliche(cliche) {}
        const QuickCalling *build(Runner &run, void **stack) const override;
	private:
		const ClicheShort &cliche;
	};

	class QuickBuildNodeLong
		: QuickBuild
	{
	public:
		QuickBuildNodeLong(const ClicheLong &cliche) : cliche(cliche) {}
        const QuickCalling *build(Runner &run, void **stack) const override;
	private:
		const ClicheLong &cliche;
	};

	class QuickImplicit
		: public QuickMatch
	{
	public:
        const QuickCalling *match(Runner &run, void **stack, const Integer &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Float &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsColor &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsDate &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Timestamp &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Duration &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const PilsString &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Cliche &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListConstant &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeConstantShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const ListExpress &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressLong &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const NodeExpressShort &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
        const QuickCalling *match(Runner &run, void **stack, const Listener &value) const override;
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
        const Any &fetch(Runner &run) const override;
	};

	class QuickImplicitWhere
		: public QuickImplicit
	{
	public:
		QuickImplicitWhere(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
        const Any &fetch(Runner &run) const override;
	};

	class QuickImplicitWhat
		: public QuickImplicit
	{
	public:
		QuickImplicitWhat(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
        const Any &fetch(Runner &run) const override;
	};

	class QuickImplicitSelf
		: public QuickImplicit
	{
	public:
		QuickImplicitSelf(size_t slotOffset)
			: QuickImplicit(slotOffset)
		{}
	protected:
        const Any &fetch(Runner &run) const override;
	};

	class QuickActionAny
		: QuickAction
	{
	public:
		QuickActionAny(const Cliche &cliche, const Any &thing, const QuickCalling::Link *&fail)
			: cliche(cliche), thing(thing), fail(fail)
		{}
        void action(Runner &run) const override;
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
        void action(Runner &run) const override;
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
        void action(Runner &run) const override;
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
        void action(Runner &run) const override;
	private:
		const Constant &constant;
	};

	class QuickBuilt
		: QuickBuild
	{
	public:
        const QuickCalling *build(Runner &run, void **stack) const override;
	};

	class SinkCompiled
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
	};

	class SinkCompiledStep
		: public SinkCompiled
	{
	public:
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class SinkCompiledOkValue
		: public SinkCompiledStep
	{
	public:
		SinkCompiledOkValue(const Any *value)
			: value(value)
		{}
        const Step *step_(Runner &run) const override;
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
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
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
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        Sink *kick(Runner &run) override;
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
        const QuickCalling *match(Runner &run, void **stack, const Special &value) const override;
	private:
		const InterfaceDesignator &designator;
	};
}
