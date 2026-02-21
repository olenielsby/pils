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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class SinkCall
		: public Sink
	{
	public:
		SinkCall(const Call &what) : what(what) {}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *thing);
		const Call &what;
	};

	class SinkCallStackedBase
		: public Sink
	{
	public:
		Sink *kick(Runner &run);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
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
		const Step *pass(Runner &run, long value);
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsColor &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Special &value);
		const Step *pass(Runner &run, const Integer *value);
		const Step *pass(Runner &run, const Float *value);
		const Step *pass(Runner &run, const PilsColor *value);
		const Step *pass(Runner &run, const PilsDate *value);
		const Step *pass(Runner &run, const Timestamp *value);
		const Step *pass(Runner &run, const Duration *value);
		const Step *pass(Runner &run, const PilsString *value);
		const Step *pass(Runner &run, const Cliche *value);
		const Step *pass(Runner &run, const ListConstant *value);
		const Step *pass(Runner &run, const NodeConstantLong *value);
		const Step *pass(Runner &run, const NodeConstantShort *value);
		const Step *pass(Runner &run, const ListExpress *value);
		const Step *pass(Runner &run, const NodeExpressLong *value);
		const Step *pass(Runner &run, const NodeExpressShort *value);
		const Step *pass(Runner &run, const Special *value);
		const Step *pass(Runner &run, const Any *value); //dummy
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class SinkAroundStacked
		: public SinkThroughStacked
	{
	public:
		SinkAroundStacked(Runner &run, const Any &who)
			: SinkThroughStacked(run, who)
		{}
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
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
		bool convert(Converter &converter) const;
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
	};

	class CallingConstant
		: public UntypedOperationConstant
	{
	public:
		CallingConstant(const HashedConstant *&link, const BuiltinClicheCalling &cliche, const Constant *value)
			: UntypedOperationConstant(link, cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
	};

	class CallingExpress
		: public UntypedOperationExpress
	{
	public:
		CallingExpress(const BuiltinClicheCalling &cliche, const Express *value)
			: UntypedOperationExpress(cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
	};

	class CallingOkConstant
		: public NodeConstantTiny
	{
	public:
		CallingOkConstant(const HashedConstant *&link, const BuiltinClicheCallingOk &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
	};

	class CallingOkExpress
		: public NodeExpressTiny
	{
	public:
		CallingOkExpress(const BuiltinClicheCallingOk &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
	};

	class SinkCallaround
		: public Sink
	{
	public:
		SinkCallaround(const Any &who)
			: who(who)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *tailStep(Runner &run, const Any *thing, const Any *where_);
		const Step *tailStep(Runner &run, const Any *thing);
		Pipe *connectPipe(Runner &run);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
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
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *call);
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
	};

	class WhoTagExpress
		: public NodeExpressTiny
	{
	public:
		WhoTagExpress(const BuiltinClicheWhoTag &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
	};

	class WhoTagConstantTrailer
		: public NodeConstantTrailer
	{
	public:
		WhoTagConstantTrailer(const HashedConstant *&link, const BuiltinClicheWhoTagTrailer &cliche, const Constant *const *value)
			: NodeConstantTrailer(link, cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
		const Step *calling(Runner &run, const Any &call, const Any *assignValue) const;
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
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
	};

	class Recalling
		: public PokerShort
	{
	public:
		Recalling(const BuiltinClicheRecalling &cliche, const Any *value)
			: PokerShort(cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
	};

	class SinkWhoRecall
		: public SinkWhoCalling
	{
	public:
		SinkWhoRecall(const WhoUntypedOperation &what, const Any *who)
			: SinkWhoCalling(what, who)
		{}
		const Step *pass(Runner &run, const Any *value);
	};

	class SinkRecall
		: public SinkTagged
	{
	public:
		SinkRecall(const Any *call, const Recalling *who, SinkTagged *chain)
			: SinkTagged(*who, chain), call(call)
		{}
		Sink *kick(Runner &run);
		const Step *skip(Runner &run);
		const Any *const call;
		std::map<const Constant *, const Any *> map;

		// un-inherit SinkForget
		const Step *pass(Runner &run, double value);
		const Step *pass(Runner &run, const Integer &value);
		const Step *pass(Runner &run, const Float &value);
		const Step *pass(Runner &run, const PilsString &value);
		const Step *pass(Runner &run, const Cliche &value);
		const Step *pass(Runner &run, const ListConstant &value);
		const Step *pass(Runner &run, const NodeConstantLong &value);
		const Step *pass(Runner &run, const NodeConstantShort &value);
		const Step *pass(Runner &run, const ListExpress &value);
		const Step *pass(Runner &run, const NodeExpressLong &value);
		const Step *pass(Runner &run, const NodeExpressShort &value);
		const Step *pass(Runner &run, const Any *value);
		bool needsResult();

	};

	class SinkRecalling
		: public Sink
	{
	public:
		SinkRecalling(SinkRecall &sinkRecall, const Constant &call)
			: sinkRecall(sinkRecall), call(call)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, const Any *value);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
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
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
	};

	class NotExpress
		: public NodeExpressTiny
	{
	public:
		NotExpress(const BuiltinClicheNot &cliche, const Express *value)
			: NodeExpressTiny(cliche, value)
		{}
		const Step *calling(Runner &run, const Constant &call) const;
		const Step *calling(Runner &run, const Integer &call) const;
		const Step *calling(Runner &run, const ListConstant &call) const;
		const Step *calling(Runner &run, const NodeConstant &call) const;
		const Step *calling(Runner &run, const Empty &call) const;
		const Step *calling(Runner &run, const ListExpress &call) const;
		const Step *calling(Runner &run, const NodeExpress &call) const;
	};

	class SinkCallingNot
		: public SinkForget
	{
	public:
		SinkCallingNot(const Any &call)
			: call(call)
		{}
		Sink *kick(Runner &run);
		const Step *pass(Runner &run, long value);
		const Step *called(Runner &run, const Constant &call);
		const Step *called(Runner &run, const Integer &call);
		const Step *called(Runner &run, const ListConstant &call);
		const Step *called(Runner &run, const NodeConstant &call);
		const Step *called(Runner &run, const Empty &call);
		const Step *called(Runner &run, const ListExpress &call);
		const Step *called(Runner &run, const NodeExpress &call);
		const Step *called(Runner &run, const Any &call, const Any *assignValue);
		const Step *error(Runner &run, const Any *error, const Express *what, const Any *who);
	private:
		const Any &call;
	};
}
#endif
