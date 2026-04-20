/* This file is public domain */
#pragma once
#include "call.h"
namespace PILS
{
	class QuickActionAny;

	class Catch
		: public SinkTagged
	{
	public:
		const Any &getImplicitParameter(ImplicitParameter::ImplicitCode code);
		Sink *kickOff(Runner &run)
		{
			for (Sink *sink = run.sink; sink != this; sink = sink->kick(run));
			return run.sink = kick(run);
		}
	protected:
		const QuickActionAny &action;
	public:
		const Any &where_;
		const Express &what;
		const Any &who;
		Sink *trial;
	protected:
		const NodeExpress &closure;
		Catch(Runner &run, const QuickActionAny &action, const NodeExpress *where_);
	};

	class CatchConstant
		: public Catch
	{
	public:
        using Catch::pass;
		CatchConstant(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const Constant &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const Constant &call;
	};

	class CatchListConstant
		: public Catch
	{
	public:
        using Catch::pass;
		CatchListConstant(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const ListConstant &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const ListConstant &call;
	};

	class CatchNodeConstant
		: public Catch
	{
	public:
        using Catch::pass;
		CatchNodeConstant(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const NodeConstant &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const NodeConstant &call;
	};

	class CatchEmpty
		: public Catch
	{
	public:
        using Catch::pass;
		CatchEmpty(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const Empty &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const Empty &call;
	};

	class CatchListExpress
		: public Catch
	{
	public:
        using Catch::pass;
		CatchListExpress(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const ListExpress &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const ListExpress &call;
	};

	class CatchNodeExpress
		: public Catch
	{
	public:
        using Catch::pass;
        CatchNodeExpress(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const NodeExpress &call)
			: Catch(run, action, where_), call(call)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const NodeExpress &call;
	};

	class CatchAssign
		: public Catch
	{
	public:
        using Catch::pass;
        CatchAssign(Runner &run, const QuickActionAny &action, const NodeExpress *where_, const Any &call, const Any *assignValue)
			: Catch(run, action, where_), call(call), assignValue(assignValue)
		{}
        const Step *pass(Runner &run, long dummy) override;
        Sink *kick(Runner &run) override;
        const Step *skip(Runner &run) override;
	private:
		const Any &call;
		const Any *assignValue;
	};

	class Closure
		: public PokerLong
	{
	public:
		Closure(const Any *const *element)
			: PokerLong(BuiltinClicheClosure::singleton, element)
		{}
		Closure(const Any *where_, const Ruleset *ruleset)
            : PokerLong(BuiltinClicheClosure::singleton, where_, (const Any*) ruleset)
		{}
        const Step *calling(Runner &run, const Constant &call) const override;
        const Step *calling(Runner &run, const Integer &call) const override;
        const Step *calling(Runner &run, const ListConstant &call) const override;
        const Step *calling(Runner &run, const NodeConstant &call) const override;
        const Step *calling(Runner &run, const Empty &call) const override;
        const Step *calling(Runner &run, const ListExpress &call) const override;
        const Step *calling(Runner &run, const NodeExpress &call) const override;
        const Step *calling(Runner &run, const Any &call, const Any *assignValue) const override;
        bool convert(Converter &converter) const override;
        const Ruleset *ruleset;
	};

	class CatchyShort
		: public PokerShort
	{
	public:
		virtual const Step *catching(Runner &run, Catch &catching) const = 0;
	protected:
		CatchyShort(const BuiltinPokerClicheShort &cliche, const Any *value)
			: PokerShort(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
	};

	class CatchyTrailer
		: public PokerTrailer
	{
	public:
		virtual const Step *catching(Runner &run, Catch &catching) const = 0;
	protected:
		CatchyTrailer(const BuiltinPokerClicheTrailer &cliche, const Any *const *value)
			: PokerTrailer(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
	};

	class CatchyTagTrailer
		: public CatchyTrailer
	{
	protected:
		CatchyTagTrailer(const BuiltinPokerClicheTrailer &cliche, const Any *const *value)
			: CatchyTrailer(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
	private:
		const Any *dummy;
	};

	class Ok
		: public CatchyShort
	{
	public:
		Ok(const BuiltinClicheOk &cliche, const Any *value)
			: CatchyShort(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
        void compileAction(Compiling &compiling) const override;
	};

	class OkTrailer
		: public CatchyTagTrailer
	{
	public:
		OkTrailer(const BuiltinClicheOkTrailer &cliche, const Any *const *value)
			: CatchyTagTrailer(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class OkConstant
		: public Ok
	{
	public:
		OkConstant(const BuiltinClicheOk &cliche, const Constant *value)
			: Ok(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
        void compileAction(Compiling &compiling) const override;
	};

	class Possibly
		: public CatchyShort
	{
	public:
		Possibly(const BuiltinClichePossibly &cliche, const Any *value)
			: CatchyShort(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class PossiblyTrailer
		: public CatchyTagTrailer
	{
	public:
		PossiblyTrailer(const BuiltinClichePossiblyTrailer &cliche, const Any *const *value)
			: CatchyTagTrailer(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class SinkPossiblying
		: public Sink
	{
	public:
		SinkPossiblying(Catch &catching, Sink *stackTrial)
			: catching(catching), stackTrial(catching.trial)
		{
			catching.trial = stackTrial;
		}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        void refer(Runner &run, const Express &what) override;
	protected:
		SinkPossiblying(Catch &catching)
			: catching(catching), stackTrial(catching.trial)
		{}
		Catch &catching;
		Sink *stackTrial;
	};

	class Try
		: public CatchyShort
	{
	public:
		Try(const BuiltinClicheTry &cliche, const Any *value)
			: CatchyShort(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class TryTrailer
		: public CatchyTagTrailer
	{
	public:
		TryTrailer(const BuiltinClicheTryTrailer &cliche, const Any *const *value)
			: CatchyTagTrailer(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class SinkTrying
		: public SinkPossiblying
	{
	public:
		SinkTrying(Catch &catching, Sink *stackTrial)
			: SinkPossiblying(catching, stackTrial)
		{}
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
        const Step *call(Runner &run, const Express &what, const Any *call) override;
        const Step *call(Runner &run, const Express &what, const Any *call , const Any *who) override;
        const Step *call(Runner &run, const Express &what, const Any &call) override;
        const Step *call(Runner &run, const Express &what, const Any &call , const Any *who) override;
        const Step *callaround(Runner &run, const Express &what, const Any *call, const Any *who) override;
        const Step *assignCall(Runner &run, const Express &what, const Any *call, const Any *assignValue) override;
        const Step *assignCall(Runner &run, const Express &what, const Any *call , const Any *who, const Any *assignValue) override;
        const Step *assignCallaround(Runner &run, const Express &what, const Any *call, const Any *who, const Any *assignValue) override;
	protected:
		SinkTrying(Catch &catching)
			: SinkPossiblying(catching)
		{}
	};

	class SinkTryReferringUncounted
		: public SinkWhereaboutUncounted
	{
	public:
		SinkTryReferringUncounted(const Any *where_, Catch &catching)
			: SinkWhereaboutUncounted(where_), catching(catching)
		{}
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *thing) override;
        const Step *tailStep(Runner &run, const Any *thing) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
        Pipe *connectPipe(Runner &run) override;
        bool needsResult() override;
	private:
		Catch &catching;
	};

	class SinkTryCalling
		: public Sink
	{
	public:
        Sink *kick(Runner &run) override;
        const Step *pass(Runner &run, const Any *value) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
        const Step *error(Runner &run, const Any *error, const Express *what, const Any *who) override;
        const Step *miss(Runner &run) override;
		SinkTryCalling(const Any *where_, const Any *call)
			: where_(where_), call(call)
		{}
	protected:
		const Any *where_;
		const Any *call;
	};

	class SinkTryCallingAround
		: public SinkTryCalling
	{
	public:
        Sink *kick(Runner &run) override;
		SinkTryCallingAround(const Any *where_, const Any *call, const Any *who)
			: SinkTryCalling(where_, call), who(who)
		{}
        const Step *miss(Runner &run) override;
	protected:
		const Any *who;
	};

	class SinkTryCallingWho
		: public SinkTryCallingAround
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
        const Step *called(Runner &run, PassingMind *mind, const Any *call, const Express *what);
		SinkTryCallingWho(const Any *where_, const Any *call, const Any *who)
			: SinkTryCallingAround(where_, call, who)
		{}
	};

	class Need
		: public CatchyShort
	{
	public:
		Need(const BuiltinClicheNeed &cliche, const Any *value)
			: CatchyShort(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class NeedTrailer
		: public CatchyTagTrailer
	{
	public:
		NeedTrailer(const BuiltinClicheNeedTrailer &cliche, const Any *const *value)
			: CatchyTagTrailer(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class SinkNeeding
		: public SinkTrying
	{
	public:
		SinkNeeding(Catch &catching)
			: SinkTrying(catching)
		{}
        const Step *pass(Runner &run, const Any *value) override;
        //const Step *called(Runner &run, const Empty &call) override;
        const Step *miss(Runner &run) override;
        const Step *tailStep(Runner &run, const Any *thing, const Any *where_) override;
	};

	class Error
		: public CatchyShort
	{
	public:
		Error(const Any *value)
			: CatchyShort(BuiltinClicheError::singleton, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class ErrorTrailer
		: public CatchyTagTrailer
	{
	public:
		ErrorTrailer(const BuiltinClicheErrorTrailer &cliche, const Any *const *value)
			: CatchyTagTrailer(cliche, value)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
	};

	class ImplicitParameterShort
		: public CatchyShort
	{
	public:
		ImplicitParameterShort(const ImplicitParameter::ImplicitClicheShort &cliche, const Any *element)
			: CatchyShort(cliche, element)
		{}
        const Step *catching(Runner &run, Catch &catching) const override;
        void compileAction(Compiling &compiling) const override;
	};

	class ImplicitParameterTrailer
		: public CatchyTrailer
	{
	public:
		ImplicitParameterTrailer(const ImplicitParameter::ImplicitClicheTrailer &cliche, const Any *const *element)
			: CatchyTrailer(cliche, element)
		{}
	private:
		const Any *dummy;
	public:
        const Step *catching(Runner &run, Catch &catching) const override;
        void compileAction(Compiling &compiling) const override;
	};

	class Tag
		: public PokerTrailer
	{
	public:
		Tag(const BuiltinPokerClicheTrailer &cliche, const Any *const *value)
			: PokerTrailer(cliche, value)
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
	private:
		const Constant *tag;
	};
}
