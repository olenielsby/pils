/* This file is public domain */
#include "pilsthread.h"
namespace PILS
{
    // const Any *SystemPropertyThread::get(Runner &run) const
    // {
    // 	return run.as_Thread();
    // }

    // const Any *BuiltinClicheThread::node(const Constant *element) const
    // {
    // 	return new (Heap::allocate(sizeof(ThreadPoker))) ThreadPoker(*this, element);
    // }

    // const NodeExpressShort *BuiltinClicheThread::node(const Express *element) const
    // {
    // 	return new (Heap::allocate(sizeof(ThreadPoker))) ThreadPoker(*this, element);
    // }

	const Any *BuiltinClicheLater::node(const Constant *element) const
	{
        return new const LaterPoker(*this, element);
	}

	const NodeExpressShort *BuiltinClicheLater::node(const Express *element) const
	{
        return new const LaterPoker(*this, element);
	}

    // const Step *ThreadPoker::step_(Runner &run) const
    // {
    // 	return run.thread(*element[0]);
    // }

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Integer *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Float *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Duration *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheKnot::newNode(const Constant *&link, const Special *value) const
	{
        return new const KnotConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheKnot::node(const Express *element) const
	{
        return new const KnotExpress(*this, element);
	}

	const Step *KnotConstant::calling(Runner &run, const Constant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const Integer &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const Empty &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const ListConstant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const NodeConstant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const ListExpress &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const NodeExpress &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotConstant::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return run.callingKnot(*element[0], call, assignValue);
	}

	const Step *KnotExpress::calling(Runner &run, const Constant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const Integer &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const Empty &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const ListConstant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const NodeConstant &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const ListExpress &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const NodeExpress &call) const
	{
		return run.callingKnot(*element[0], call);
	}

	const Step *KnotExpress::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		return run.callingKnot(*element[0], call, assignValue);
	}

	const Step *Runner::callingKnot(const Any &who, const Any &call)
	{
		return call.caller(*this, who);
	}

	const Step *Runner::callingKnot(const Any &who, const Any &call, const Any *assignValue)
	{
		return call.calling(*this, call, assignValue);
	}
}
