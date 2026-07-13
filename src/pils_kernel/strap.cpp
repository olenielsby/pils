/* This file is public domain */
#include "strap.h"

namespace PILS
{
	Strap::Strap(const Constant *&link, const BuiltinClicheStrap &cliche, const Constant *value)
    : NodeConstantTiny(link, cliche, value), stickCount(0), mind(Empty::get())
    {}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Integer *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Float *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Duration *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const Special *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const Strap(link, *this, value);
	}

	Strap::Sticker::~Sticker()
	{
        for (auto i = stuck.begin(); i != stuck.end(); i++)
            (*i)->unstick(run);
	}

    void Strap::Sticker::clear()
    {
        for (auto i = stuck.begin(); i != stuck.end(); i++)
            (*i)->unstick(run);
        stuck.clear();
    }

    void Strap::Sticker::stick(const Strap &strap)
	{
        Mutex::Lock lock(Mutex::singleMutex);
		if (stuck.insert(&strap).second == true)
		{
			strap.retain();
			strap.stickCount++;
		}
	}

    void Strap::unstick(Runner &run) const
	{
		const Any *drop = nullptr;
		{
            Mutex::Lock lock(Mutex::singleMutex);
			if (!--stickCount)
			{
				drop = mind;
                mind = Empty::get();
			}
		}
        if (drop) run.release(drop);
        run.release(this);
	}

	const Any *Strap::get() const
	{
        Mutex::Lock lock(Mutex::singleMutex);
		mind->retain();
		return mind;
	}

	const Any *Special::specialCalling(Runner &run, const Strap &call) const
	{
        return nullptr;
	}

	const Any *Strap::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return ((Special&)special).specialCalling(run, *this);
	}

	const Step *Strap::calling(Runner &run, const Constant &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const Integer &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const ListConstant &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const NodeConstant &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const ListExpress &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const NodeExpress &call) const
	{
		const Any *mind = get();
		new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
		return mind->calling(run, call);
	}

	const Step *Strap::calling(Runner &run, const Empty &call) const
	{
		return get()->passCounted(run);
	}

	const Step *Strap::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		if (&call == &Empty::singleton)
		{
			const Any *result = nullptr;
			{
                Mutex::Lock lock(Mutex::singleMutex);
				if (stickCount)
				{
					result = mind;
					mind = assignValue;
				}
				else result = assignValue;
			}
			return result->passCounted(run);
		}
		else
		{
			const Any *mind = get();
			new (run.allocate(sizeof(SinkHold))) SinkHold(mind);
			return mind->calling(run, call, assignValue);
		}
	}

	const Step *SinkHold::called(Runner &run, const Constant &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const Empty &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const NodeConstant &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const ListConstant &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const NodeExpress &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const ListExpress &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const Integer &call)
	{
		return (run.sink = kick(run))->called(run, call);
	}

	const Step *SinkHold::called(Runner &run, const Any &call, const Any *assignValue)
	{
		return (run.sink = kick(run))->called(run, call, assignValue);
	}
}
