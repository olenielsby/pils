/* This file is public domain */
#include "channel.h"

namespace PILS
{
	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Integer *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Float *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Duration *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const Channel(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheChannel::newNode(const Constant *&link, const Special *value) const
	{
        return new const Channel(link, *this, value);
	}

	const Channel *Channel::as_Channel() const
	{
		return this;
	}

    Listener::Listener(const Any *ear, const Channel *channel)
        : PokerTrailer(BuiltinClicheListener::singleton, ear, channel),
        next(channel->listening),
        previous(&channel->listening)
	{
        Mutex::Lock lock(Mutex::singleMutex);
        channel->listening = this;
        if (next)
            next->previous = &next;
	}

    void Listener::unlink()
    {
        *previous = next;
        if (next)
            next->previous = previous;
        PokerTrailer::unlink();
	}

	const Step *Channel::calling(Runner &run, const Constant &call) const
	{
		{
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            Mutex::Lock lock(Mutex::singleMutex);
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
            return (run.sink = this + 1)->pass(run, new Listener(ear, channel));
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
        run.release(ear);
		return this + 1;
	}
}
