/* This file is public domain */
#ifndef DEFINE_PILS_PILSTHREAD_H
#define DEFINE_PILS_PILSTHREAD_H

#include "sink.h"
namespace PILS
{
    // class ThreadPoker
    // 	: public PokerShort
    // {
    // public:
    // 	ThreadPoker(const BuiltinClicheThread &cliche, const Any *value)
    // 		: PokerShort(cliche, value)
    // 	{}
    // const Step *step_(Runner &run) const override;
    // };

	class LaterPoker
		: public PokerShort
	{
	public:
		LaterPoker(const BuiltinClicheLater &cliche, const Any *value)
			: PokerShort(cliche, value)
		{}
        const Step *step_(Runner &run) const override;
	};

	class KnotConstant
		: public NodeConstantTiny
	{
	public:
		KnotConstant(const HashedConstant *&link, const BuiltinClicheKnot &cliche, const Constant *value)
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

	class KnotExpress
		: public NodeExpressTiny
	{
	public:
		KnotExpress(const BuiltinClicheKnot &cliche, const Express *value)
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

	class KnotStepResult
		: Step
	{
	public:
		KnotStepResult(const Any *result)
			: result(result)
		{}
	private:
        const Step *step_(Runner &run) const override
		{
			const Any *result = this->result;
			run.sink = (Sink *)(this + 1);
			return result->passCounted(run);
		}
		const Any *result;
	};

	class KnotStepCalled
		: protected Step
	{
	public:
		KnotStepCalled(const Any &call) : call(call) {}
	protected:
		const Any &call;
	private:
        const Step *step_(Runner &run) const override
		{
			const Any &call = this->call;
			run.sink = (Sink *)(this + 1);
			return call.caller(run, Empty::singleton);
		}
	};

	class KnotStepAssignCalled : KnotStepCalled
	{
	public:
		KnotStepAssignCalled(const Any &call, const Any *assignValue)
			: KnotStepCalled(call), assignValue(assignValue)
		{}
	private:
        const Step *step_(Runner &run) const override
		{
			const Any &call = this->call;
			const Any *assignValue = this->assignValue;
			run.sink = (Sink *)(this + 1);
			return run.sink->called(run, call, assignValue);
		}
		const Any *assignValue;
	};
}

#endif
