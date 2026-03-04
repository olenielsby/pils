/* This file is public domain */
#include "pipe.h"
#ifndef DEFINE_PILS_PILSSTRING_H
#define DEFINE_PILS_PILSSTRING_H

namespace PILS
{
	class SinkIndex
		: public Sink
	{
	public:
		SinkIndex(const CallWho &what, long index)
			: what(what), index(index), indexInteger(NULL)
		{}
		SinkIndex(const CallWho &what, const Integer *index)
			: what(what), index(index->value), indexInteger(index)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        const Step *pass(Runner &run, const Any *who) override;
	private:
		const CallWho &what;
		long index;
		const Integer *indexInteger;
	};

	class SinkConcatenating
		: public Sink
	{
	public:
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
	protected:
		SinkConcatenating(const CallWho &what)
			: what(what)
		{}
		const CallWho &what;
	};

	class SinkConcatenatingRange
		: public SinkConcatenating
	{
	public:
		SinkConcatenatingRange(const CallWho &what, const Any *anchor, const PILS_CHAR *text, size_t count)
			: SinkConcatenating(what), anchor(anchor), text(text), count(count)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        size_t concatenateCount() override;
        const Step *concatenateBuild(Runner &run, PILS_CHAR *string, PILS_CHAR *at) override;
	private:
		const Any *anchor;
		const PILS_CHAR *text;
		size_t count;
	};

	class SinkConcatenatingString
		: public SinkConcatenating
	{
	public:
		SinkConcatenatingString(const CallWho &what, const PilsString *string)
			: SinkConcatenating(what), string(string)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding) override;
        size_t concatenateCount() override;
        const Step *concatenateBuild(Runner &run, PILS_CHAR *string, PILS_CHAR *at) override;
	private:
		const PilsString *string;
	};

	class RangeExpress
		: public NodeExpressTiny
	{
	public:
		RangeExpress(const BuiltinClicheRange &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class RangeConstant
		: public NodeConstantTiny
	{
	public:
		RangeConstant(const HashedConstant *&link, const BuiltinClicheRange &cliche, const Integer *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const CallWho *callWho(const Any *who) const override;
	};

	class WhoRangeExpress
		: public CallWho
	{
	public:
		WhoRangeExpress(const RangeExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoRangeConstant
		: public CallWho
	{
	public:
		WhoRangeConstant(const RangeConstant *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkRangeOperand
		: public Sink
	{
	public:
		SinkRangeOperand(const WhoRangeExpress &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Any *value) override;
	private:
		const WhoRangeExpress &what;
	};

	class SinkRange
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		SinkRange(const CallWho &what, long range)
			: what(what), range(range)
		{}
		const CallWho &what;
		long range;
	};

	class SinkPlusRange
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkPlusRange(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class SinkPlusSlackRange
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkPlusSlackRange(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        Pipe *connectPipe(Runner &run) override;
	};

	class SinkPlusRangeReverse
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkPlusRangeReverse(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class SinkPlusSlackRangeReverse
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkPlusSlackRangeReverse(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class SinkMinusRange
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkMinusRange(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class SinkMinusSlackRange
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkMinusSlackRange(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        Pipe *connectPipe(Runner &run) override;
	};

	class SinkMinusRangeReverse
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkMinusRangeReverse(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	class SinkMinusSlackRangeReverse
		: public SinkRange
	{
		using SinkRange::pass;
	public:
		SinkMinusSlackRangeReverse(const CallWho &what, long range)
			: SinkRange(what, range)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
	};

	/* Slack ranges ++# and --# are pipeable. */

	class PipeSlackRange
		: public Pipe
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		PipeSlackRange(const CallWho &what, size_t range)
			: what(what),range(range)
		{}
		const CallWho &what;
		size_t range;
        const Step *pipeEnd(Runner &run) override;
	};

	class PipePlusSlackRange
		: public PipeSlackRange
	{
	public:
		PipePlusSlackRange(const CallWho &what, size_t range)
			: PipeSlackRange(what, range)
		{}
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class PipeMinusSlackRange
		: public PipeSlackRange
	{
	public:
		PipeMinusSlackRange(const CallWho &what, size_t range)
			: PipeSlackRange(what, range)
		{}
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
	};

	class WhoSearchString
		: public CallWho
	{
	public:
		WhoSearchString(const SearchString *call, const Any *who)
			: CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeSearchString
		: public WhoSearchString
	{
	public:
		WhoPlusRangeSearchString(const SearchString *call, const Any *who)
			: WhoSearchString(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeReverseSearchString
		: public WhoSearchString
	{
	public:
		WhoPlusRangeReverseSearchString(const SearchString *call, const Any *who)
			: WhoSearchString(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeSearchString
		: public WhoSearchString
	{
	public:
		WhoMinusRangeSearchString(const SearchString *call, const Any *who)
			: WhoSearchString(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeReverseSearchString
		: public WhoSearchString
	{
	public:
		WhoMinusRangeReverseSearchString(const SearchString *call, const Any *who)
			: WhoSearchString(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoSearchListConstant
		: public CallWho
	{
	public:
		WhoSearchListConstant(const SearchListConstant *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeSearchListConstant
		: public WhoSearchListConstant
	{
	public:
		WhoPlusRangeSearchListConstant(const SearchListConstant *call, const Any *who)
			: WhoSearchListConstant(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeReverseSearchListConstant
		: public WhoSearchListConstant
	{
	public:
		WhoPlusRangeReverseSearchListConstant(const SearchListConstant *call, const Any *who)
			: WhoSearchListConstant(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeSearchListConstant
		: public WhoSearchListConstant
	{
	public:
		WhoMinusRangeSearchListConstant(const SearchListConstant *call, const Any *who)
			: WhoSearchListConstant(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeReverseSearchListConstant
		: public WhoSearchListConstant
	{
	public:
		WhoMinusRangeReverseSearchListConstant(const SearchListConstant *call, const Any *who)
			: WhoSearchListConstant(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoSearchExpress
		: public CallWho
	{
	public:
		WhoSearchExpress(const SearchExpress *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeSearchExpress
		: public WhoSearchExpress
	{
	public:
		WhoPlusRangeSearchExpress(const SearchExpress *call, const Any *who)
			: WhoSearchExpress(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoPlusRangeReverseSearchExpress
		: public WhoSearchExpress
	{
	public:
		WhoPlusRangeReverseSearchExpress(const SearchExpress *call, const Any *who)
			: WhoSearchExpress(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeSearchExpress
		: public WhoSearchExpress
	{
	public:
		WhoMinusRangeSearchExpress(const SearchExpress *call, const Any *who)
			: WhoSearchExpress(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class WhoMinusRangeReverseSearchExpress
		: public WhoSearchExpress
	{
	public:
		WhoMinusRangeReverseSearchExpress(const SearchExpress *call, const Any *who)
			: WhoSearchExpress(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkSearch
		: public Sink
	{
	protected:
		const BuiltinClicheSearchAbstract &cliche;
		SinkSearch(const CallWho &what, const BuiltinClicheSearchAbstract &cliche)
			: cliche(cliche), what(what)
		{}
		const CallWho &what;
	};

	class SinkSearchString
		: public SinkSearch
	{
	public:
		SinkSearchString(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const PilsString *string)
			: SinkSearch(what, cliche), string(string)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        Sink *kick(Runner &run) override;
	protected:
		virtual const Step *searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit);
		const PilsString *string;
	};

	class SinkSearchStringPlusRange
		: public SinkSearchString
	{
	public:
		SinkSearchStringPlusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const PilsString *string)
			: SinkSearchString(what, cliche, string)
		{}
	protected:
         const Step *searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit) override;
	};

	class SinkSearchStringPlusRangeReverse
		: public SinkSearchString
	{
	public:
		SinkSearchStringPlusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const PilsString *string)
			: SinkSearchString(what, cliche, string)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit) override;
	};

	class SinkSearchStringMinusRange
		: public SinkSearchString
	{
	public:
		SinkSearchStringMinusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const PilsString *string)
			: SinkSearchString(what, cliche, string)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit) override;
	};

	class SinkSearchStringMinusRangeReverse
		: public SinkSearchString
	{
	public:
		SinkSearchStringMinusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const PilsString *string)
			: SinkSearchString(what, cliche, string)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit) override;
	};

	class SinkSearchListConstant
		: public SinkSearch
	{
	public:
		SinkSearchListConstant(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListConstant *list)
			: SinkSearch(what, cliche), list(list)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        Sink *kick(Runner &run) override;
	protected:
		virtual const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit);
		virtual const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit);
		const ListConstant *list;
	};

	class SinkSearchListConstantPlusRange
		: public SinkSearchListConstant
	{
	public:
		SinkSearchListConstantPlusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListConstant *list)
			: SinkSearchListConstant(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListConstantPlusRangeReverse
		: public SinkSearchListConstant
	{
	public:
		SinkSearchListConstantPlusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListConstant *list)
			: SinkSearchListConstant(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListConstantMinusRange
		: public SinkSearchListConstant
	{
	public:
		SinkSearchListConstantMinusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListConstant *list)
			: SinkSearchListConstant(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListConstantMinusRangeReverse
		: public SinkSearchListConstant
	{
	public:
		SinkSearchListConstantMinusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListConstant *list)
			: SinkSearchListConstant(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListExpress
		: public SinkSearch
	{
	public:
		SinkSearchListExpress(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListExpress *list)
			: SinkSearch(what, cliche), list(list)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        Sink *kick(Runner &run) override;
	protected:
		virtual const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit);
		virtual const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit);
		const ListExpress *list;
	};

	class SinkSearchListExpressPlusRange
		: public SinkSearchListExpress
	{
	public:
		SinkSearchListExpressPlusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListExpress *list)
			: SinkSearchListExpress(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListExpressPlusRangeReverse
		: public SinkSearchListExpress
	{
	public:
		SinkSearchListExpressPlusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListExpress *list)
			: SinkSearchListExpress(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListExpressMinusRange
		: public SinkSearchListExpress
	{
	public:
		SinkSearchListExpressMinusRange(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListExpress *list)
			: SinkSearchListExpress(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchListExpressMinusRangeReverse
		: public SinkSearchListExpress
	{
	public:
		SinkSearchListExpressMinusRangeReverse(const CallWho &what, const BuiltinClicheSearchAbstract &cliche, const ListExpress *list)
			: SinkSearchListExpress(what, cliche, list)
		{}
	protected:
        const Step *searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit) override;
        const Step *searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit) override;
	};

	class SinkSearchOperand
		: public Sink
	{
	public:
		SinkSearchOperand(const CallWho &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;

        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	protected:
		const CallWho &what;
	};

	class SinkSearchPlusRangeOperand
		: public SinkSearchOperand
	{
	public:
		SinkSearchPlusRangeOperand(const CallWho &what)
			: SinkSearchOperand(what)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	};

	class SinkSearchPlusRangeReverseOperand
		: public SinkSearchOperand
	{
	public:
		SinkSearchPlusRangeReverseOperand(const CallWho &what)
			: SinkSearchOperand(what)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	};

	class SinkSearchMinusRangeOperand
		: public SinkSearchOperand
	{
	public:
		SinkSearchMinusRangeOperand(const CallWho &what)
			: SinkSearchOperand(what)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	};

	class SinkSearchMinusRangeReverseOperand
		: public SinkSearchOperand
	{
	public:
		SinkSearchMinusRangeReverseOperand(const CallWho &what)
			: SinkSearchOperand(what)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	};

	class WhoCasing
		: public CallWho
	{
	public:
		WhoCasing(const PropertyCasing *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkCasing
		: public Sink
	{
	public:
		SinkCasing(const WhoCasing &what)
			: what(what)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *who) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
	private:
		const WhoCasing &what;
	};

	class WhoPropertyTraverse
		: public CallWho
	{
	public:
		WhoPropertyTraverse(const PropertyTraverse *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyTraverse
		: SinkProperty
	{
	public:
		SinkPropertyTraverse(const WhoPropertyTraverse &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
	};

	class WhoPropertySinglewise
		: public CallWho
	{
	public:
		WhoPropertySinglewise(const PropertySinglewise *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertySinglewise
		: SinkProperty
	{
	public:
		SinkPropertySinglewise(const WhoPropertySinglewise &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *value) override;
	};

	class WhoPropertyListwise
		: public CallWho
	{
	public:
		WhoPropertyListwise(const PropertyListwise *call, const Any *who)
			:  CallWho(call, who)
		{}
        const Step *step_(Runner &run) const override;
	};

	class SinkPropertyListwise
		: SinkProperty
	{
	public:
		SinkPropertyListwise(const WhoPropertyListwise &what)
			: SinkProperty(what)
		{}
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkStringOperation
		: public Sink
	{
	public:
		SinkStringOperation(const WhoUntypedOperation &what, const PilsString *operand)
			: what(what), operand(operand)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		const WhoUntypedOperation &what;
		const PilsString *operand;
	};

	class SinkSpliceString
		: public SinkStringOperation
	{
	public:
		using SinkStringOperation::pass;
		SinkSpliceString(const WhoUntypedOperation &what, const PilsString *operand)
			: SinkStringOperation(what, operand)
		{}
        const Step *pass(Runner &run, const ListConstant *value) override;
	};

	class SinkSplitString
		: public SinkStringOperation
	{
	public:
		SinkSplitString(const WhoUntypedOperation &what, const PilsString *operand)
			: SinkStringOperation(what, operand)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
	};

	class SinkSplitSize
		: public SinkRange
	{
	public:
		SinkSplitSize(const WhoUntypedOperation &what, long size)
			: SinkRange(what, size)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Any *const *range, size_t count) override;
        const Step *pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count) override;
        Pipe *connectPipe(Runner &run) override;
	};

	class PipesourceSplitEmptySeparator
		: public Pipesource
	{
	public:
		PipesourceSplitEmptySeparator(const PilsString *string)
			: string(string), at(string->value), end(&string->value[string->count->value])
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
	protected:
		const PilsString *const string;
		const PILS_CHAR *at;
		const PILS_CHAR *const end;
	};

	class PipesourceSplit
		: public PipesourceSplitEmptySeparator
	{
	public:
		PipesourceSplit(const PilsString *string, const PilsString *separator)
			: PipesourceSplitEmptySeparator(string), separator(separator)
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
	private:
		const PilsString *separator;
	};

	class PipesourceSplitStringSize
		: public Pipesource
	{
	public:
		PipesourceSplitStringSize(const Any *anchor, const PILS_CHAR *range, size_t count, size_t size)
			: anchor(anchor), range(range), count(count), size(size)
		{}
        Sink *kick(Runner &run) override;
        const Step *step_(Runner &run) const override;
	private:
		const Any *const anchor;
		const PILS_CHAR *range;
		size_t count;
		size_t size;
	};

	class PipeSplitSize
		: public Pipe
	{
	public:
		PipeSplitSize(Pipe &pipe, const WhoUntypedOperation &what)
			: pipe(pipe), what(what)
		{
			at = (const Any **)(this + 1);
		}
        Sink *kick(Runner &run) override;
        const Step *pipeItem(Runner &run, const Any *item) override;
        const Step *pipeBegin(Runner &run) override;
        const Step *pipeEnd(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
	private:
		const Any **begin() {return (const Any **)(this + 1);}
		const Any **end() {return (const Any **)&pipe;}
		const Any **at;
		Pipe &pipe;
		const WhoUntypedOperation &what;
	};

	class SinkReplaceStringPairs
		: public Sink
	{
	public:
		SinkReplaceStringPairs(const WhoUntypedOperation &what, const ListConstant *pairs)
			: what(what), pairs(pairs)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
	private:
		const WhoUntypedOperation &what;
	protected:
		const ListConstant *pairs;
	private:
		class Bag
		{
		public:
			virtual void put(const PILS_CHAR c) = 0;
			virtual void put(const PILS_CHAR *c, size_t count) = 0;
		};

		class CountBag
			: public Bag
		{
		public:
			CountBag() : count(0) {}
            void put(const PILS_CHAR c) override;
            void put(const PILS_CHAR *c, size_t count) override;
			size_t count;
		};

		class TextBag
			: public Bag
		{
		public:
			TextBag(PILS_CHAR *text) : text(text) {}
            void put(const PILS_CHAR c) override;
            void put(const PILS_CHAR *c, size_t count) override;
		private:
			PILS_CHAR *text;
		};

		class Traveller
		{
		public:
			Traveller(const PilsString *original, const ListConstant *pairs)
				: text(original->value),
				  endText(&original->value[original->count->value]),
				  pairs((const PilsString *const *)pairs->element),
				  endPairs((const PilsString *const *)&pairs->element[pairs->count->value])
			{}
            void travel(Bag &bag) const;
		private:
			const PILS_CHAR *text;
			const PILS_CHAR *endText;
			const PilsString *const *pairs;
			const PilsString *const *endPairs;
		};
	};

	class SinkReplaceBeginningStringPairs
		: public SinkReplaceStringPairs
	{
	public:
		SinkReplaceBeginningStringPairs(const WhoUntypedOperation &what, const ListConstant *pairs)
			: SinkReplaceStringPairs(what, pairs)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
	};

	class SinkReplaceEndingStringPairs
		: public SinkReplaceStringPairs
	{
	public:
		SinkReplaceEndingStringPairs(const WhoUntypedOperation &what, const ListConstant *pairs)
			: SinkReplaceStringPairs(what, pairs)
		{}
        const Step *pass(Runner &run, const PilsString *value) override;
	};

	class SinkOrder
		: public Sink
	{
	public:
		SinkOrder(WhoUntypedOperation &what, const Any *who)
			: what(what), who(who)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const ListExpress *list) override;
        const Step *pass(Runner &run, const ListConstant *list) override;
        const Step *pass(Runner &run, const Any *thing) override;
	private:
		WhoUntypedOperation &what;
		const Any *who;
	};
}
#endif
