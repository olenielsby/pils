/* This file is public domain */
#ifndef DEFINE_PILS_CALL_H
#define DEFINE_PILS_CALL_H
#include "sink.h"
namespace PILS
{
	class SinkHoldWho
		: public SinkHold
	{
	public:
		SinkHoldWho(const Any *thing)
			: SinkHold(thing)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class SinkCall
		: public Sink
	{
	public:
		SinkCall(const Call &what) : what(what) {}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
		const Call &what;
	};

	class SinkCallStackedBase
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
	protected:
		SinkCallStackedBase(const Any &stacked)
			: stacked(stacked)
		{}
		const Any &stacked;
	};

	class SinkCallStacked
		: public SinkCallStackedBase
	{
	public:
		SinkCallStacked(const Any &stacked)
			: SinkCallStackedBase(stacked)
		{}
        const Step *pass(Runner &run, long value) override;
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const PilsColor &value) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const Cliche &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const NodeConstantLong &value) override;
        const Step *pass(Runner &run, const NodeConstantShort &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const NodeExpressLong &value) override;
        const Step *pass(Runner &run, const NodeExpressShort &value) override;
        const Step *pass(Runner &run, const Special &value) override;
        const Step *pass(Runner &run, const Integer *value) override;
        const Step *pass(Runner &run, const Float *value) override;
        const Step *pass(Runner &run, const PilsColor *value) override;
        const Step *pass(Runner &run, const PilsDate *value) override;
        const Step *pass(Runner &run, const Timestamp *value) override;
        const Step *pass(Runner &run, const Duration *value) override;
        const Step *pass(Runner &run, const PilsString *value) override;
        const Step *pass(Runner &run, const Cliche *value) override;
        const Step *pass(Runner &run, const ListConstant *value) override;
        const Step *pass(Runner &run, const NodeConstantLong *value) override;
        const Step *pass(Runner &run, const NodeConstantShort *value) override;
        const Step *pass(Runner &run, const ListExpress *value) override;
        const Step *pass(Runner &run, const NodeExpressLong *value) override;
        const Step *pass(Runner &run, const NodeExpressShort *value) override;
        const Step *pass(Runner &run, const Special *value) override;
        const Step *pass(Runner &run, const Any *value) override; //dummy
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
	};

	class SinkThroughStacked
		: public SinkCallStacked
	{
	public:
		SinkThroughStacked(Runner &run, const Any &who)
			: SinkCallStacked(*run.calling.who)
		{
			run.calling.who = &who;
		}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class SinkAroundStacked
		: public SinkThroughStacked
	{
	public:
		SinkAroundStacked(Runner &run, const Any &who)
			: SinkThroughStacked(run, who)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class Using
		: public PokerTrailer
	{
	public:
		Using(const Any *base, const Any *use)
			: PokerTrailer(BuiltinClicheUsing::singleton, base, use)
		{}
		Using(const PokerClicheTrailer &cliche, const Any *const *element)
			: PokerTrailer(cliche, element)
		{}
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
        bool convert(Converter &converter) const override;
	protected:
		Using(const Cliche &cliche, const Any *base, const Any *use)
			: PokerTrailer(BuiltinClicheUsing::singleton, base, use)
		{}
	private:
		const Any *dummy;
	};

	class Through
		: public Using
	{
	public:
		Through(const Any *base, const Any *use)
			: Using(BuiltinClicheThrough::singleton, base, use)
		{}
		Through(const BuiltinClicheThrough &cliche, const Any *const *element)
			: Using(cliche, element)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class Around
		: public Using
	{
	public:
		Around(const Any *base, const Any *use)
			: Using(BuiltinClicheAround::singleton, base, use)
		{}
		Around(const BuiltinClicheAround &cliche, const Any *const *element)
			: Using(cliche, element)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class CallingConstant
		: public UntypedOperationConstant
	{
	public:
		CallingConstant(const HashedConstant *&link, const BuiltinClicheCalling &cliche, const Constant *value)
			: UntypedOperationConstant(link, cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class CallingExpress
		: public UntypedOperationExpress
	{
	public:
		CallingExpress(const BuiltinClicheCalling &cliche, const Express *value)
			: UntypedOperationExpress(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class CallingOkConstant
		: public NodeConstantTiny
	{
	public:
		CallingOkConstant(const HashedConstant *&link, const BuiltinClicheCallingOk &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
	};

	class CallingOkExpress
		: public NodeExpressTiny
	{
	public:
		CallingOkExpress(const BuiltinClicheCallingOk &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
	};

	class SinkCallaround
		: public Sink
	{
	public:
		SinkCallaround(const Any &who)
			: who(who)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
	private:
		const Any &who;
	};

	class SinkWhoCalling
		: public Sink
	{
	public:
		SinkWhoCalling(const WhoUntypedOperation &what, const Any *who)
			: what(what), who(who)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
	protected:
		const WhoUntypedOperation &what;
		const Any *who;
	};

	class SinkCalling
		: public Sink
	{
	public:
		SinkCalling(const Any *call, const Any *who)
			: call(call), who(who)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        Pipe *connectPipe(Runner &run) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
	private:
		const Any *call;
		const Any *who;
	};

	class SinkWhoCallingAssign
		: public Sink
	{
	public:
		SinkWhoCallingAssign(const WhoAssign &what,	const Any *who, const Any *assignValue)
			: what(what), who(who), assignValue(assignValue)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *call) override;
	private:
		const WhoAssign &what;
		const Any *who;
		const Any *assignValue;
	};

	class WhoTagConstant
		: public NodeConstantTiny
	{
	public:
		WhoTagConstant(const HashedConstant *&link, const BuiltinClicheWhoTag &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class WhoTagExpress
		: public NodeExpressTiny
	{
	public:
		WhoTagExpress(const BuiltinClicheWhoTag &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	};

	class WhoTagConstantTrailer
		: public NodeConstantTrailer
	{
	public:
		WhoTagConstantTrailer(const HashedConstant *&link, const BuiltinClicheWhoTagTrailer &cliche, const Constant *const *value)
			: NodeConstantTrailer(link, cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	private:
		const Constant *dummy;
	};

	class WhoTagExpressTrailer
		: public NodeExpressTrailer
	{
	public:
		WhoTagExpressTrailer(const BuiltinClicheWhoTagTrailer &cliche, const Any *const *value)
			: NodeExpressTrailer(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
	private:
		const Any *dummy;
	};

	class SinkCallingWhoTag
		: public SinkCallStacked
	{
	public:
		SinkCallingWhoTag(const Any &who)
			: SinkCallStacked(who)
		{}
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
	};

	class Recalling
		: public PokerShort
	{
	public:
		Recalling(const BuiltinClicheRecalling &cliche, const Any *value)
			: PokerShort(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
	};

	class SinkWhoRecall
		: public SinkWhoCalling
	{
	public:
		SinkWhoRecall(const WhoUntypedOperation &what, const Any *who)
			: SinkWhoCalling(what, who)
		{}
        const Step *pass(Runner &run, const Any *value) override;
	};

	class SinkRecall
		: public SinkTagged
	{
	public:
		SinkRecall(const Any *call, const Recalling *who, SinkTagged *chain)
			: SinkTagged(*who, chain), call(call)
		{}
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
		const Any *const call;
		std::map<const Constant *, const Any *> map;

		// un-inherit SinkForget
        const Step *pass(Runner &run, double value) override;
        const Step *pass(Runner &run, const Integer &value) override;
        const Step *pass(Runner &run, const Float &value) override;
        const Step *pass(Runner &run, const PilsString &value) override;
        const Step *pass(Runner &run, const Cliche &value) override;
        const Step *pass(Runner &run, const ListConstant &value) override;
        const Step *pass(Runner &run, const NodeConstantLong &value) override;
        const Step *pass(Runner &run, const NodeConstantShort &value) override;
        const Step *pass(Runner &run, const ListExpress &value) override;
        const Step *pass(Runner &run, const NodeExpressLong &value) override;
        const Step *pass(Runner &run, const NodeExpressShort &value) override;
        const Step *pass(Runner &run, const Any *value) override;
        bool needsResult() override;

	};

	class SinkRecalling
		: public Sink
	{
	public:
		SinkRecalling(SinkRecall &sinkRecall, const Constant &call)
			: sinkRecall(sinkRecall), call(call)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
	private:
		SinkRecall &sinkRecall;
		const Constant &call;
	};

	class NotConstant
		: public NodeConstantTiny
	{
	public:
		NotConstant(const HashedConstant *&link, const BuiltinClicheNot &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
	};

	class NotExpress
		: public NodeExpressTiny
	{
	public:
		NotExpress(const BuiltinClicheNot &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
	};

	class SinkCallingNot
		: public SinkForget
	{
	public:
		SinkCallingNot(const Any &call)
			: call(call)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, long value) override;
        const Step *called(Runner &run, const Constant &call) override;
        const Step *called(Runner &run, const Integer &call) override;
        const Step *called(Runner &run, const ListConstant &call) override;
        const Step *called(Runner &run, const NodeConstant &call) override;
        const Step *called(Runner &run, const Empty &call) override;
        const Step *called(Runner &run, const ListExpress &call) override;
        const Step *called(Runner &run, const NodeExpress &call) override;
        const Step *called(Runner &run, const Any &call, const Any *assignValue) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
	private:
		const Any &call;
	};
}
#endif
