/* This file is public domain */
#include "concatenate.h"
namespace PILS
{
	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Integer *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Float *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const PilsColor *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Timestamp *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Duration *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const PilsDate *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Cliche *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Special *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const Listener *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheConcatenate::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(ConcatenateConstant))) ConcatenateConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheConcatenate::node(const Express *element) const
	{
		return new (Heap::allocate(sizeof(ConcatenateExpress))) ConcatenateExpress(*this, element);
	}

	const CallWho *ConcatenateConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoConcatenateConstant))) WhoConcatenateConstant(this, who);
	}

	const CallWho *ConcatenateExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoConcatenateExpress))) WhoConcatenateExpress(this, who);
	}

	const Step *WhoConcatenateConstant::step_(Runner &run) const
	{
		run.sink->connectPipe(run);
		const Any *value = ((const ConcatenateConstant *)callAttribute())->element[0];
		new (run.allocate(sizeof(PipeConcatenate))) PipeConcatenate(*value);
		return whoAttribute();
	}

	const Step *WhoConcatenateExpress::step_(Runner &run) const
	{
		run.sink->connectPipe(run);
		const Any *value = ((const ConcatenateExpress *)callAttribute())->element[0];
		new (run.allocate(sizeof(PipeConcatenate))) PipeConcatenate(*value);
		return whoAttribute();
	}

	Sink *PipeConcatenate::kick(Runner &run)
	{
		return this + 1;
	}
	
	const Step *PipeConcatenate::pass(Runner &run, const Any *value)
	{
		PipeHold &hold = *new (run.allocate(sizeof(PipeHold))) PipeHold(value);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(&hold.hold, 1);
		return pipeBegin(run);
	}

	const Step *PipeConcatenate::pipeBegin(Runner &run)
	{
		if (who)
			return ((Pipe*)(this + 1))->pipeBegin(run);
		else return (Pipesource *)run.sink;
	}

	const Step *PipeConcatenate::pipeItem(Runner &run, const Any *item)
	{
		return ((Pipe*)(this + 1))->pipeItem(run, item);
	}

	const Step *PipeConcatenate::pipeEnd(Runner &run)
	{
		if (who)
		{
			run.sink = this;
			const Step *step_ = who;
			who = NULL;
			return step_;
		}
		else return ((Pipe *)(run.sink = this + 1))->pipeEnd(run);
	}
}
