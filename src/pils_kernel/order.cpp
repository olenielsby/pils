/* This file is public domain */
#include "order.h"
namespace PILS
{
    int Constant::order(const Constant *other) const
	{
		return other->ordering();
	}

    int Constant::ordering() const
	{
		return 0;
	}

    int Constant::ordering(double first) const
	{
		return -1; //arbitrary after number
	}

    int Constant::ordering(const PilsString *first) const
	{
		return -1; // arbitrary after string
	}

    int Constant::ordering(const ListConstant *first) const
	{
		return -1; // arbitrary after list constant
	}

	int Number::ordering() const
	{
		return 1; // number before arbitrary
	}

	int Number::ordering(const PilsString *first) const
	{
		return 1; // number before string
	}

	int Number::ordering(const ListConstant *first) const
	{
		return 1; // number before list constant
	}

	int Integer::order(const Constant *other) const
	{
		return other->ordering(value);
	}

	int Integer::ordering(double first) const
	{
		if (first < value) return -1;
		else if (first > value) return 1;
		else return 0;
	}

	int Float::order(const Constant *other) const
	{
		return other->ordering(value);
	}

	int Float::ordering(double first) const
	{
		if (first < value) return -1;
		else if (first > value) return 1;
		else return 0;
	}

	int PilsString::order(const Constant *other) const
	{
		return other->ordering(this);
	}

	int PilsString::ordering() const
	{
		return 1; // string before arbitrary
	}

	int PilsString::ordering(const ListConstant *first) const
	{
		return 1; // string before list constant
	}

	int PilsString::ordering(const PilsString *first) const
	{
		if (this == first) return 0;
		else if (first->less(*this)) return -1;
		else return 1;
	}

	int ListConstant::order(const Constant *other) const
	{
		return other->ordering(this);
	}

	int ListConstant::ordering() const
	{
		return 1; // list constant before arbitrary
	}

	int ListConstant::ordering(const ListConstant *first) const
	{
		size_t count = this->count->value;
		int tie = 0;
		if ((size_t)first->count->value < count) {tie = -1; count = (size_t)first->count->value;}// shorter list comes first
		else if ((size_t)first->count->value > count) tie = 1;
		for (size_t i = 0; i < count; i++)
		{
			int result = first->element[i]->order(element[i]);
			if (result != 0) return result;
		}
		return tie;
	}

	const Step *BuiltinClicheOrder::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeOrder))) PipeOrder(what, value);
		return what.whoAttribute();
	}

	Sink *PipeOrder::kick(Runner &run)
	{
        run.release(keypicker);
        for(Bag::iterator iterator = bag.begin(); iterator != bag.end(); iterator++)
		{
            run.release(iterator->first);
            run.release(iterator->second);
		}
		bag.~vector();
		return this + 1;
	}

	const Step *PipeOrder::pass(Runner &run, const Any *who)
	{
		bag.~vector();
		const Express &what = this->what;
		const Any *argument = BuiltinClicheOrder::singleton.node(keypicker);
		return (run.sink = this + 1)->call(run, what, argument, who);
	}

	const Step *PipeOrder::pipeBegin(Runner &run)
	{
		Pipe *next = this + 1;
		return next->pipeBegin(run);
	}

	const Step *PipeOrder::pipeEnd(Runner &run)
	{
		Comparator comparator;
		sort(bag.begin(), bag.end(), comparator);
		return new (run.allocate(sizeof(PipesourceSorted))) PipesourceSorted((Pipe&)this[1], bag);
	}

	const Step *PipeOrder::pipeItem(Runner &run, const Any *item)
	{
		new (run.allocate(sizeof(SinkOrderKey))) SinkOrderKey(bag, item);
		((Sink &)this[1]).refer(run, what);
		run.calling.who = keypicker;
		return item->caller(run, *keypicker);
	}

	Sink *PipeOrder::PipesourceSorted::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeOrder::PipesourceSorted::step_(Runner &run) const
	{
		if (at == end)
		{
			Pipe &pipe = this->pipe;
			while (run.sink != &pipe) run.sink = run.sink->kick(run);
			return pipe.pipeEnd(run);
		}
		else
		{
			const Any *item = ((PipesourceSorted *)this)->at++->second;
			item->retain();
			return pipe.pipeItem(run, item);
		}
	}

	Sink *PipeOrder::SinkOrderKey::kick(Runner &run)
	{
        run.release(item);
		return this + 1;
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Integer *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Float *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Timestamp *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Duration *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const PilsDate *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const PilsString *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Cliche *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Special *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const ListConstant *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const NodeConstantShort *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const NodeConstantLong *value)
	{
		return pass(run, (const Constant*)value);
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Any *value)
	{
        run.release(value);
        return pass(run, (const Constant*) Empty::get());
	}

	const Step *PipeOrder::SinkOrderKey::pass(Runner &run, const Constant *key)
	{
		bag.push_back(Pair(key, item));
		return (Pipesource*)(run.sink = this + 1);
	}

	bool PipeOrder::Comparator::operator ()(const PipeOrder::Pair &p1, const PipeOrder::Pair &p2) const
	{
		return p1.first->order(p2.first) == -1;
	}
}
