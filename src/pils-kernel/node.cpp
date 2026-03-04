/* This file is public domain */
#include "node.h"
namespace PILS
{
	const CallWho *TypecheckPropertyCliche::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyCliche))) WhoPropertyCliche(this, who);
	}

	const Step *WhoPropertyCliche::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyCliche))) SinkPropertyCliche(*this);
		return whoAttribute();
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeConstantShort &node)
	{
		return (run.sink = this + 1)->pass(run, *node.cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeConstantLong &node)
	{
		return (run.sink = this + 1)->pass(run, *node.cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeExpressShort &node)
	{
		return (run.sink = this + 1)->pass(run, *node.cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeExpressLong &node)
	{
		return (run.sink = this + 1)->pass(run, *node.cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeConstantShort *node)
	{
		const Cliche *cliche = node->cliche;
		cliche->addReference();
		node->releaseReference();
		return (run.sink = this + 1)->pass(run, cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeConstantLong *node)
	{
		const Cliche *cliche = node->cliche;
		cliche->addReference();
		node->releaseReference();
		return (run.sink = this + 1)->pass(run, cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeExpressShort *node)
	{
		const Cliche *cliche = node->cliche;
		cliche->addReference();
		node->releaseReference();
		return (run.sink = this + 1)->pass(run, cliche);
	}

	const Step *SinkPropertyCliche::pass(Runner &run, const NodeExpressLong *node)
	{
		const Cliche *cliche = node->cliche;
		cliche->addReference();
		node->releaseReference();
		return (run.sink = this + 1)->pass(run, cliche);
	}

	const CallWho *PropertyHead::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyHead))) WhoPropertyHead(this, who);
	}

	const Step *WhoPropertyHead::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyHead))) SinkPropertyHead(*this);
		return whoAttribute();
	}

	const CallWho *TypecheckPropertyLegs::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyLegs))) const WhoPropertyLegs(this, who);
	}

	const Step *WhoPropertyLegs::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyLegs))) SinkPropertyLegs(*this);
		return whoAttribute();
	}

	const Step *SinkPropertyHead::pass(Runner &run, const Cliche &cliche)
	{
		run.sink = this + 1;
		return cliche.head->passUncounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeConstantShort &node)
	{
		run.sink = this + 1;
		return node.cliche->head->passUncounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeConstantLong &node)
	{
		run.sink = this + 1;
		return node.cliche->head->passUncounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeExpressShort &node)
	{
		run.sink = this + 1;
		return node.cliche->head->passUncounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeExpressLong &node)
	{
		run.sink = this + 1;
		return node.cliche->head->passUncounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const Cliche *cliche)
	{
		const Constant *head = cliche->head;
		head->addReference();
		cliche->releaseReference();
		run.sink = this + 1;
		return head->passCounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeConstantShort *node)
	{
		const Constant *head = node->cliche->head;
		head->addReference();
		node->releaseReference();
		run.sink = this + 1;
		return head->passCounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeConstantLong *node)
	{
		const Constant *head = node->cliche->head;
		head->addReference();
		node->releaseReference();
		run.sink = this + 1;
		return head->passCounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeExpressShort *node)
	{
		const Constant *head = node->cliche->head;
		head->addReference();
		node->releaseReference();
		run.sink = this + 1;
		return head->passCounted(run);
	}

	const Step *SinkPropertyHead::pass(Runner &run, const NodeExpressLong *node)
	{
		const Constant *head = node->cliche->head;
		head->addReference();
		node->releaseReference();
		run.sink = this + 1;
		return head->passCounted(run);
	}

	const Step *SinkPropertyLegs::pass(Runner &run, const Cliche *cliche)
	{
		return (run.sink = this + 1)->pass(run, cliche, cliche->attributes, cliche->count);
	}

	const Step *BuiltinClicheHeadset::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Constant *name = value->as_Constant();
		if (name)
		{
			new (run.allocate(sizeof(SinkHeadset))) SinkHeadset(what, name);
			return what.whoAttribute();
		}
		else
			return BuiltinClicheUntypedOperation::gotOperand(run, what, value);
	}

	const Step *BuiltinClicheUntypedOperation::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, node(value));
		return what.whoAttribute();
	}

	Sink *SinkHeadset::kick(Runner &run)
	{
		name->releaseReference();
		return this + 1;
	}

	const Step *SinkHeadset::pass(Runner &run, const Cliche *cliche)
	{
		const Cliche *result;
		if (cliche->count == 1) result = name->clichefy(cliche->attributes[0]);
		else result = name->clichefy(cliche->attributes, cliche->count);
		for (size_t i = 0; i < cliche->count; i++) result->attributes[i]->addReference();
		cliche->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkHeadset::pass(Runner &run, const NodeConstantShort *node)
	{
		const Constant *attribute = node->cliche->attributes[0];
		node->element[0]->addReference();
		attribute->addReference();
		const ClicheShort *cliche = name->clichefy(attribute);
		const Any *result = cliche->node(node->element[0]);
		cliche->unduplicateReference();
		node->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkHeadset::pass(Runner &run, const NodeConstantLong *node)
	{
		size_t count = node->cliche->count;
		const ClicheLong *cliche = name->clichefy(node->cliche->attributes, count);
		for (size_t i = 0; i < count; i++) cliche->attributes[i]->addReference();
		for (size_t i = 0; i < count; i++) node->element[i]->addReference();
		const Any *result = cliche->node(node->element);
		cliche->unduplicateReference();
		node->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkHeadset::pass(Runner &run, const NodeExpressShort *node)
	{
		const Constant *attribute = node->cliche->attributes[0];
		attribute->addReference();
		node->element[0]->addReference();
		const ClicheShort *cliche = name->clichefy(attribute);
		const Any *result = cliche->node(node->element[0]);
		cliche->unduplicateReference();
		node->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkHeadset::pass(Runner &run, const NodeExpressLong *node)
	{
		size_t count = node->cliche->count;
		const ClicheLong *cliche = name->clichefy(node->cliche->attributes, count);
		for (size_t i = 0; i < count; i++) cliche->attributes[i]->addReference();
		for (size_t i = 0; i < count; i++) node->element[i]->addReference();
		const Any *result = cliche->node(node->element);
		cliche->unduplicateReference();
		node->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkHeadset::pass(Runner &run, const Any *thing)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *const *dummy;
		BuiltinClicheHeadset *cliche;
		what.callAttribute()->isNode(dummy, (const Cliche*&) cliche);
		const NodeConstantShort *argument = cliche->nodeConstant(name);
		return (run.sink = this + 1)->call(run, what, argument, thing);
	}

	const Step *BuiltinClicheLegs::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		run.sink->connectPipe(run);
		new (run.allocate(sizeof(PipeCounting))) PipeCounting(what, value);
		return what.whoAttribute();
	}

	const Step *PipeCounting::pass(Runner &run, const NodeConstantShort *node)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *who = this->filter;
		Pipe &pipe = *(Pipe *)(run.sink = this + 1);
		new (run.allocate(sizeof(PipesourceLegs))) PipesourceLegs(what, who, node);
		return pipe.pipeBegin(run);
	}

	const Step *PipeCounting::pass(Runner &run, const NodeConstantLong *node)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *who = this->filter;
		Pipe &pipe = *(Pipe *)(run.sink = this + 1);
		new (run.allocate(sizeof(PipesourceLegs))) PipesourceLegs(what, who, node);
		return pipe.pipeBegin(run);
	}

	const Step *PipeCounting::pass(Runner &run, const NodeExpressShort *node)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *who = this->filter;
		Pipe &pipe = *(Pipe *)(run.sink = this + 1);
		new (run.allocate(sizeof(PipesourceLegs))) PipesourceLegs(what, who, node);
		return pipe.pipeBegin(run);
	}

	const Step *PipeCounting::pass(Runner &run, const NodeExpressLong *node)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *who = this->filter;
		Pipe &pipe = *(Pipe *)(run.sink = this + 1);
		new (run.allocate(sizeof(PipesourceLegs))) PipesourceLegs(what, who, node);
		return pipe.pipeBegin(run);
	}

	Sink *PipesourceLegs::kick(Runner &run)
	{
		who->releaseReference();
		node->releaseReference();
		return this + 1;
	}

	const Step *PipesourceLegs::step_(Runner &run) const
	{
		Pipe &pipe = (Pipe&)(this[1]);
		if (name < nameEnd)
		{
			new (run.allocate(sizeof(PipingLegs))) PipingLegs(pipe);
			run.calling.what = &what;
			const Any *assignValue = *((PipesourceLegs *)this)->value++;
			assignValue->addReference();
			return (run.calling.who = who)->calling(run, **((PipesourceLegs *)this)->name++, assignValue);
		}
		else
		{
			run.sink = &pipe;
			who->releaseReference();
			node->releaseReference();
			return pipe.pipeEnd(run);
		}
	}

	const Step *PipingLegs::called(Runner &run, const Any &call, const Any *assignValue)
	{
		assignValue->releaseReference();
		return (Pipesource*)(run.sink = this + 1);
	}

	const Step *BuiltinClicheMerge::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		if (value != &Empty::singleton)
			new (run.allocate(sizeof(SinkMerge))) SinkMerge(what, value);
		return what.whoAttribute();
	}

	Sink *SinkBindMerge::kick(Runner &run)
	{
		operand->releaseReference();
		return this + 1;
	}

	const Step *SinkMerge::pass(Runner &run, const Cliche *a)
	{
		const Cliche *b = operand->as_Cliche();
		if (b == NULL) return pass(run, (const Any*)a);
		size_t count = CountRound(a, b).count;
		if (count == 1)
		{
			if (b->head == &Empty::singleton)
			{
				b->releaseReference();
				b = a;
			}
			else a->releaseReference();
		}
		else
		{
			const Constant **names = new const Constant*[count];
			NameRound(a, b, names);
			const Constant *name = b->head;
			if (name == &Empty::singleton) name = a->head;
			name->addReference();
			a->releaseReference();
			b->releaseReference();
			b = name->clichefy(names, count);
            delete[] names;
		}
		return (run.sink = this + 1)->pass(run, b);
	}

	const Step *SinkMerge::pass(Runner &run, const NodeConstantShort *node)
	{
		return passNode(run, node, *node->cliche, (const Any *const *)node->element);
	}

	const Step *SinkMerge::pass(Runner &run, const NodeConstantLong *node)
	{
		return passNode(run, node, *node->cliche, (const Any *const *)node->element);
	}

	const Step *SinkMerge::pass(Runner &run, const NodeExpressShort *node)
	{
		return passNode(run, node, *node->cliche, node->element);
	}

	const Step *SinkMerge::pass(Runner &run, const NodeExpressLong *node)
	{
		return passNode(run, node, *node->cliche, node->element);
	}

	const Step *SinkMerge::pass(Runner &run, const ListConstant *who)
	{
		if (who == &Empty::singleton)
		{
			Empty::singleton.unduplicateReference();
			const Any *operand = this->operand;
			run.sink = this + 1;
			const Any *const *elements;
			const Integer *count;
			if (operand != &Empty::singleton && operand->isList(elements, count))
			{
				const Constant *name = elements[0]->as_Constant();
				if (name && count->value == 2)
				{
					const Any *value = elements[1];
					name->addReference();
					value->addReference();
					operand->releaseReference();
					Builtin::name.anyway.addReference();
					const ClicheShort &cliche = *Builtin::name.anyway.clichefy(name);
					const Any *result = cliche.node(value);
					cliche.unduplicateReference();
					return result->passCounted(run);
				}
			}
			else return operand->passCounted(run);
		}
		return pass(run, (const Any *)who);
	}

	const Step *SinkMerge::pass(Runner &run, const Any *who)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *argument = what.callAttribute()->as_NodeConstant();
		if (argument)
		{
			argument->addReference();
			operand->unduplicateReference();
		}
		else
			argument = ((BuiltinClicheMerge*)((const UntypedOperationExpress*)what.callAttribute())->cliche)->node(operand);
		return (run.sink = this + 1)->call(run, what, argument, who);
	}

	const Step *SinkMerge::passNode(Runner &run, const Any *node, const Cliche &ca, const Any *const *ea)
	{
		const Cliche *cb;
		const Any *const *eb;
		const Integer *two;
		const Any **scratch;
		const Any *result = NULL;
		if (operand->isNode(eb, cb))
		{
			size_t count = CountRound(&ca, cb).count;
			scratch = new const Any*[count];
			NameRound(&ca, cb, (const Constant**)scratch);
			const Constant *name = cb->head;
			if (name == &Empty::singleton) name = ca.head;
			name->addReference();
			const Cliche *cliche = count == 1?(const Cliche*)name->clichefy((const Constant *)scratch[0]):name->clichefy((const Constant *const *)scratch, count);
			ValueRound(&ca, cb, scratch, ea, eb);
			result = cliche->node(scratch);
			cliche->unduplicateReference();
		}
		else if (operand->isList(eb, two) && two->value == 2 && eb[0]->as_Constant())
		{
			const Constant *const *at;
			if (eb[0] == &Empty::singleton || (eb[0] <= ca.attributes[0] && ca.attributes[0] != &Empty::singleton))
				at = &ca.attributes[0];
			else at = std::lower_bound(&ca.attributes[1], &ca.attributes[ca.count], (const Constant *)eb[0]);
			size_t count;
			if (at == &ca.attributes[ca.count] || *at != eb[0])
			{
				count = ca.count + 1;
				scratch = new const Any *[count];
				size_t i;
				for (i = 0; &ca.attributes[i] < at; i++)
					(scratch[i] = ca.attributes[i])->addReference();
				(scratch[i++] = eb[0])->addReference();
				for (; i < count; i++)
					(scratch[i] = ca.attributes[i - 1])->addReference();
				ca.head->addReference();
				const ClicheLong *cliche = ca.head->clichefy((const Constant *const*)scratch, count);
				for (i = 0; &ca.attributes[i] < at; i++)
					(scratch[i] = ea[i])->addReference();
				(scratch[i++] = eb[1])->addReference();
				for (; i < count; i++)
					(scratch[i] = ea[i - 1])->addReference();
				result = cliche->node(scratch);
				cliche->unduplicateReference();
			}
			else
			{
				count = ca.count;
				scratch = new const Any *[count];
				size_t i;
				for (i = 0; &ca.attributes[i] < at; i++)
					(scratch[i] = ea[i])->addReference();
				(scratch[i++] = eb[1])->addReference();
				for (; i < count; i++)
					(scratch[i] = ea[i])->addReference();
				result = ca.node(scratch);
			}
		}
		if (result)
		{
			delete scratch;
			node->releaseReference();
			operand->releaseReference();
			run.sink = this + 1;
			return result->passCounted(run);
		}
		else return pass(run, node);
	}

	void SinkMerge::Round::round()
	{
		if (*aAttribute == &Empty::singleton)
		{
			if (*bAttribute == &Empty::singleton)
			{
				ab();
				aAttribute++;
				bAttribute++;
			}
			else
			{
				a();
				aAttribute++;
			}
		}
		else if (*bAttribute == &Empty::singleton)
		{
				b();
				bAttribute++;
		}
		while (aAttribute < aEnd && bAttribute < bEnd)
		{
			if (*bAttribute > *aAttribute)
			{
				a();
				aAttribute++;
			}
			else if (*aAttribute > *bAttribute)
			{
				b();
				bAttribute++;
			}
			else
			{
				ab();
				aAttribute++;
				bAttribute++;
			}
		}
		while (aAttribute < aEnd)
		{
			a();
			aAttribute++;
		}
		while (bAttribute < bEnd)
		{
			b();
			bAttribute++;
		}
	}

	void SinkMerge::CountRound::a()
	{
		count++;
	}

	void SinkMerge::CountRound::b()
	{
		count++;
	}

	void SinkMerge::CountRound::ab()
	{
		count++;
	}

	void SinkMerge::NameRound::a()
	{
		const Constant *name = *aAttribute;
		name->addReference();
		*destination++ = name;
	}

	void SinkMerge::NameRound::b()
	{
		const Constant *name = *bAttribute;
		name->addReference();
		*destination++ = name;
	}

	void SinkMerge::NameRound::ab()
	{
		const Constant *name = *aAttribute;
		name->addReference();
		*destination++ = name;
	}

	void SinkMerge::ValueRound::a()
	{
		const Any *value = *aSource++;
		value->addReference();
		*destination++ = value;
	}

	void SinkMerge::ValueRound::b()
	{
		const Any *value = *bSource++;
		value->addReference();
		*destination++ = value;
	}

	void SinkMerge::ValueRound::ab()
	{
		aSource++;
		const Any *value = *bSource++;
		value->addReference();
		*destination++ = value;
	}

	const Step *BuiltinClicheBind::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		new (run.allocate(sizeof(SinkBindMerge))) SinkBindMerge(what, value);
		return what.whoAttribute();
	}

	const Step *SinkBindMerge::pass(Runner &run, const Any *who)
	{
		const Any *const *e;
		const Integer *c;
		if (operand->isList(e, c) && c->value == 2 && e[0] != &Empty::singleton && e[0]->as_Constant())
		{
			Empty::singleton.addReference();
			Empty::singleton.addReference();
			e[0]->addReference();
			e[1]->addReference();
			const Constant *const attributes[2] = {&Empty::singleton, (const Constant*)e[0]};
			const Any *const values[2] = {who, e[1]};
			const ClicheLong *cliche = Empty::singleton.clichefy(attributes, 2);
			const NodeExpressLong *result = (const NodeExpressLong *)cliche->node(values);
			cliche->unduplicateReference();
			operand->releaseReference();
			return (run.sink = this + 1)->pass(run, result);
		}
		else
		{
			const WhoUntypedOperation &what = this->what;
			const Any *argument = what.callAttribute()->as_NodeConstant();
			if (argument)
			{
				argument->addReference();
				operand->unduplicateReference();
			}
			else
				argument = ((BuiltinClicheBind*)((const UntypedOperationExpress*)what.callAttribute())->cliche)->node(operand);
			return (run.sink = this + 1)->call(run, what, argument, who);
		}
	}

	const Step *SinkBindMerge::pass(Runner &run, const NodeExpressLong *who)
	{
		const Any *const *e;
		const Integer *two;
		const Cliche &oldCliche = *who->cliche;
		if (who->cliche->head == &Empty::singleton
			&& who->cliche->attributes[0] == &Empty::singleton
			&& operand->isList(e, two)
			&& two->value == 2
			&& e[0]	!= &Empty::singleton
			&& e[0]->as_Constant())
		{
			const Constant *const *at = std::lower_bound(&oldCliche.attributes[1], &oldCliche.attributes[oldCliche.count], (const Constant *)e[0]);
			size_t count;
			const Any **scratch;
			const NodeExpressLong *result;
			if (at == &oldCliche.attributes[oldCliche.count] || *at != (const Constant *)e[0])
			{
				count = oldCliche.count + 1;
				scratch = new const Any *[count];
				size_t i;
				for (i = 0; &oldCliche.attributes[i] < at; i++)
					(scratch[i] = oldCliche.attributes[i])->addReference();
				(scratch[i++] = e[0])->addReference();
				for (; i < count; i++)
					(scratch[i] = oldCliche.attributes[i - 1])->addReference();
				oldCliche.head->addReference();
				const ClicheLong *newCliche = oldCliche.head->clichefy((const Constant *const*)scratch, count);
				for (i = 0; &oldCliche.attributes[i] < at; i++)
					(scratch[i] = who->element[i])->addReference();
				(scratch[i++] = e[1])->addReference();
				for (; i < count; i++)
					(scratch[i] = who->element[i - 1])->addReference();
				result = (NodeExpressLong *)newCliche->node(scratch);
				newCliche->unduplicateReference();
			}
			else
			{
				count = oldCliche.count;
				scratch = new const Any *[count];
				size_t i;
				for (i = 0; &oldCliche.attributes[i] < at; i++)
					(scratch[i] = who->element[i])->addReference();
				(scratch[i++] = e[1])->addReference();
				for (; i < count; i++)
					(scratch[i] = who->element[i])->addReference();
				result = (NodeExpressLong *)oldCliche.node(scratch);
			}
			delete scratch;
			who->releaseReference();
			operand->releaseReference();
			return (run.sink = this + 1)->pass(run, result);
		}
		else return pass(run, (const Any *)who);
	}

	const Step *BuiltinClicheWithout::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Constant *attribute = value->as_Constant();
		if (attribute)
		{
			new (run.allocate(sizeof(SinkWithout))) SinkWithout(what, attribute);
			return what.whoAttribute();
		}
		else return BuiltinClicheUntypedOperation::gotOperand(run, what, value);
	}

	Sink *SinkUntypedConstantOperation::kick(Runner &run)
	{
		operand->releaseReference();
		return this + 1;
	}

	const Step *SinkUntypedConstantOperation::pass(Runner &run, const Any *who)
	{
		const ClicheShort *cliche;
		const Any *const *e;
		what.callAttribute()->isNode(e, (const Cliche*&) cliche);
		const NodeConstantShort *argument = cliche->nodeConstant(operand);
		const WhoUntypedOperation &what = this->what;
		return (run.sink = this + 1)->call(run, what, argument, who);
	}

	const Step *SinkWithout::pass(Runner &run, const Cliche *cliche)
	{
		const Constant *const *at;
		if (cliche->attributes[0] == operand)
			at = &cliche->attributes[0];
		else
			at = std::lower_bound(cliche->attributes + 1, cliche->attributes + cliche->count, operand);
		if (at != cliche->attributes + cliche->count && *at == operand)
		{
			if (cliche->count == 1) return pass(run, (const Any*)cliche); // cannot remove last attribute
			const Constant **attributeBuffer = new const Constant*[cliche->count - 1];
			const Constant **dest = attributeBuffer;
			for (size_t i = 0; i < cliche->count; i++)
			{
				if (&cliche->attributes[i] != at)
					(*dest++ = cliche->attributes[i])->addReference();
			}
			const Cliche *newCliche = cliche->count > 2 ? (const Cliche*)cliche->head->clichefy(attributeBuffer, cliche->count - 1) : cliche->head->clichefy(*attributeBuffer);
			cliche->head->addReference();
            delete[] attributeBuffer;
			operand->unduplicateReference();
			cliche->releaseReference();
			return (run.sink = this + 1)->pass(run, newCliche);
		}
		else return (run.sink = kick(run))->pass(run, cliche);
	}

	const Step *SinkWithout::pass(Runner &run, const NodeConstantShort *node)
	{
		if (operand == node->cliche->attributes[0])
			return pass(run, (const Any *)node); // cannot remove last attribute
		else return (run.sink = kick(run))->pass(run, node);
	}

	const Step *SinkWithout::pass(Runner &run, const NodeConstantLong *node)
	{
		const Constant *const *at;
		if (node->cliche->attributes[0] == operand)
			at = &node->cliche->attributes[0];
		else
			at = std::lower_bound(node->cliche->attributes + 1, node->cliche->attributes + node->cliche->count, operand);
		if (at != node->cliche->attributes + node->cliche->count && *at == operand)
		{
			const Constant **attributeBuffer = new const Constant*[node->cliche->count - 1];
			const Constant **valueBuffer = new const Constant*[node->cliche->count - 1];
			const Constant **attributeDest = attributeBuffer;
			const Constant **valueDest = valueBuffer;
			for (size_t i = 0; i < node->cliche->count; i++)
			{
				if (&node->cliche->attributes[i] != at)
				{
					(*attributeDest++ = node->cliche->attributes[i])->addReference();
					(*valueDest++ = node->element[i])->addReference();
				}
			}
			const Cliche *newCliche = node->cliche->count > 2 ? (const Cliche*)node->cliche->head->clichefy(attributeBuffer, node->cliche->count - 1) : node->cliche->head->clichefy(*attributeBuffer);
			node->cliche->head->addReference();
			const Any *result = newCliche->node(valueBuffer);
			newCliche->unduplicateReference();
            delete[] valueBuffer;
            delete[] attributeBuffer;
			operand->unduplicateReference();
			node->releaseReference();
			run.sink = this + 1;
			return result->passCounted(run);
		}
		else return (run.sink = kick(run))->pass(run, node);
	}

	const Step *SinkWithout::pass(Runner &run, const NodeExpressShort *node)
	{
		if (operand == node->cliche->attributes[0])
			return pass(run, (const Any *)node);
		else return (run.sink = kick(run))->pass(run, node);
	}

	const Step *SinkWithout::pass(Runner &run, const NodeExpressLong *node)
	{
		const Constant *const *at;
		if (node->cliche->attributes[0] == operand)
			at = &node->cliche->attributes[0];
		else
			at = std::lower_bound(node->cliche->attributes + 1, node->cliche->attributes + node->cliche->count, operand);
		if (at != node->cliche->attributes + node->cliche->count && *at == operand)
		{
			const Constant **attributeBuffer = new const Constant*[node->cliche->count - 1];
			const Any **valueBuffer = new const Any*[node->cliche->count - 1];
			const Constant **attributeDest = attributeBuffer;
			const Any **valueDest = valueBuffer;
			for (size_t i = 0; i < node->cliche->count; i++)
			{
				if (&node->cliche->attributes[i] != at)
				{
					(*attributeDest++ = node->cliche->attributes[i])->addReference();
					(*valueDest++ = node->element[i])->addReference();
				}
			}
			const Cliche *newCliche = node->cliche->count > 2 ? (const Cliche*)node->cliche->head->clichefy(attributeBuffer, node->cliche->count - 1) : node->cliche->head->clichefy(*attributeBuffer);
			node->cliche->head->addReference();
			const Any *result = newCliche->node(valueBuffer);
			newCliche->unduplicateReference();
            delete[] valueBuffer;
            delete[] attributeBuffer;
			operand->unduplicateReference();
			node->releaseReference();
			run.sink = this + 1;
			return result->passCounted(run);
		}
		else return (run.sink = kick(run))->pass(run, node);
	}

	const Step *BuiltinClicheMakeCliche::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Constant *attribute = value->as_Constant();
		if (attribute)
		{
			new (run.allocate(sizeof(SinkMakeCliche))) SinkMakeCliche(what, attribute);
			return what.whoAttribute();
		}
		else return BuiltinClicheUntypedOperation::gotOperand(run, what, value);
	}

	const Step *SinkMakeCliche::pass(Runner &run, const ListConstant *list)
	{
		size_t count = list->count->value;
		if (count)
		{
			ClicheBuilder build(operand);
			for (size_t i = 0; i < count; i++)
				build.add(*list->element[i]);
			list->releaseReference();
			const Cliche *result = build.build();
			return (run.sink = this + 1)->pass(run, result);
		}
		else return pass(run, (const Any *)list);
	}

	const Step *BuiltinClicheMakeName::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Constant *attribute = value->as_Constant();
		if (attribute)
		{
			new (run.allocate(sizeof(SinkMakeName))) SinkMakeName(what, attribute);
			return what.whoAttribute();
		}
		else return BuiltinClicheUntypedOperation::gotOperand(run, what, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Integer *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Float *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const PilsString *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Timestamp *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Duration *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const PilsDate *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Cliche *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const Special *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const NodeConstantShort *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const NodeConstantLong *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::pass(Runner &run, const ListConstant *value)
	{
		return passConstant(run, value);
	}

	const Step *SinkMakeName::passConstant(Runner &run, const Constant *head)
	{
		const ClicheShort *cliche = head->clichefy(operand);
		return (run.sink = this + 1)->pass(run, cliche);
	}
}
