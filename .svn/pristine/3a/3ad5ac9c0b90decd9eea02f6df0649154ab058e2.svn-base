/* This file is public domain */
#include "strap.h"

namespace PILS
{
	Strap::Strap(const HashedConstant *&link, const BuiltinClicheStrap &cliche, const Constant *value)
		: NodeConstantTiny(link, cliche, value), stickCount(0), mind(&Empty::singleton)
	{
		Empty::singleton.addReference();
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheStrap::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(Strap))) Strap(link, *this, value);
	}

	size_t Strap::unlinkAndGetSize()
	{
		NodeConstantTiny::unlinkAndGetSize();
		return sizeof(Strap);
	}

	Strap::Sticker::~Sticker()
	{
		for (std::set<const Strap*>::const_iterator i = stuck.begin(); i != stuck.end(); i++)
			(*i)->unstick();
	}

	void Strap::Sticker::clear()
	{
		for (std::set<const Strap*>::const_iterator i = stuck.begin(); i != stuck.end(); i++)
			(*i)->unstick();
		stuck.clear();
	}

	void Strap::Sticker::stick(const Strap &strap)
	{
		Mutex::Lock lock(Heap::mutex);
		if (stuck.insert(&strap).second == true)
		{
			strap.addReference();
			strap.stickCount++;
		}
	}

	void Strap::unstick() const
	{
		const Any *drop = NULL;
		{
			Mutex::Lock lock(Heap::mutex);
			if (!--stickCount)
			{
				drop = mind;
				Empty::singleton.addReference();
				mind = &Empty::singleton;
			}
		}
		if (drop) drop->releaseReference();
		releaseReference();
	}

	const Any *Strap::get() const
	{
		Mutex::Lock lock(Heap::mutex);
		mind->addReference();
		return mind;
	}

	const Any *Special::specialCalling(Runner &run, const Strap &call) const
	{
		return NULL;
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
			const Any *result = NULL;
			{
				Mutex::Lock lock(Heap::mutex);
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
