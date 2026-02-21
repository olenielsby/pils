/* This file is public domain */
#include "channel.h"

namespace PILS
{
	const NodeConstantShort *ClicheShort::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return
			new (Heap::allocate(sizeof(NodeConstantShort)))
			const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return
			new (Heap::allocate(sizeof(NodeConstantTiny)))
			const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheUntypedOperation::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return
			new (Heap::allocate(sizeof(UntypedOperationConstant)))
			const UntypedOperationConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Float *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Special *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return
			new (Heap::allocate(sizeof(Channel)))
			const Channel(link, *this, value);
	}

	const Channel *Channel::as_Channel() const
	{
		return this;
	}

	size_t Channel::unlinkAndGetSize()
	{
		unhash();
		cliche->releaseFrom(*this);
		element[0]->releaseFrom(*this);
		return sizeof(Channel);
	}

	Listener::Listener(const Channel *channel, const Any *ear)
		: channel(channel), ear(ear), next(channel->listening), previous(&channel->listening)
	{
		channel->listening = this;
		if (next)
			next->previous = &next;
	}

	size_t Listener::unlinkAndGetSize()
	{
		*previous = next;
		if (next) next->previous = previous;
		ear->releaseFrom(*this);
		channel->releaseFrom(*this);
		return sizeof(Listener);
	}

	const Step *Channel::calling(Runner &run, const Constant &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<Constant>))) SinkChanneling<Constant>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const Integer &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<Integer>))) SinkChanneling<Integer>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const ListConstant &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<ListConstant>))) SinkChanneling<ListConstant>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const NodeConstant &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<NodeConstant>))) SinkChanneling<NodeConstant>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const Empty &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<Empty>))) SinkChanneling<Empty>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const ListExpress &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<ListExpress>))) SinkChanneling<ListExpress>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const NodeExpress &call) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
					return new (run.allocate(sizeof(SinkChanneling<NodeExpress>))) SinkChanneling<NodeExpress>(first, *run.calling.who, call);
			}
		}
		return run.sink->called(run, call);
	}

	const Step *Channel::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		{
			Mutex::Lock lock(Heap::mutex);
			for (Listener *first = listening; first; first = first->next)
			{
				if (first->duplicateReferenceNoChildren())
				{
					return new (run.allocate(sizeof(SinkChannelingAssign))) SinkChannelingAssign(first, *run.calling.who, call, *assignValue);
				}
			}
		}
		return run.sink->called(run, call, assignValue);
	}

	const Step *BuiltinClicheListen::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkListen))) SinkListen(what, value);
		return what.whoAttribute();
	}

	const Step *SinkListen::pass(Runner &run, const NodeConstantShort *thing)
	{
		const Channel *channel = thing->as_Channel();
		if (channel)
		{
			return (run.sink = this + 1)->pass(run, channel->listen(ear));
		}
		else return pass(run, (const Any*)thing);
	}

	const Step *SinkListen::pass(Runner &run, const Any *thing)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *const *dummy;
		const BuiltinClicheListen *cliche;
		what.callAttribute()->isNode(dummy, (const Cliche*&) cliche);
		const Any *argument = cliche->node(ear);
		return (run.sink = this + 1)->call(run, what, argument, thing);
	}

	Sink *SinkListen::kick(Runner &run)
	{
		ear->releaseReference();
		return this + 1;
	}

	const Listener *Channel::listen(const Any *ear) const
	{
		Mutex::Lock lock(Heap::mutex);
		return new (Heap::allocate(sizeof(Listener))) Listener(this, ear);
	}

	const Step *Listener::step_(Runner &run) const
	{
		addReference();
		return run.sink->pass(run, this);
	}

	const Step *Listener::passUncounted(Runner &run) const
	{
		addReference();
		return run.sink->pass(run, this);
	}
	const Step *Listener::passCounted(Runner &run) const
	{
		return run.sink->pass(run, this);
	}
	const NodeConstantShort *Listener::newSpecializeNode(const HashedConstant *&link, const ClicheShort &cliche) const
	{
		return cliche.newNode(link, this);
	}
	bool Listener::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
}
