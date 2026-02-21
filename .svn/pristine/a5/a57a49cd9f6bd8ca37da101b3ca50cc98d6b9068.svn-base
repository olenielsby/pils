/* This file is public domain */
#include "pilsstring.h"
namespace PILS
{
	std::locale const PilsString::defaultLocale/*("")*/;

	const Step *ListConstant::calling(Runner &run, const Integer &call) const
	{
		size_t index = (size_t)call.value - 1;
		if (index < (size_t)count->value) return element[index]->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const Step *ListExpress::calling(Runner &run, const Integer &call) const
	{
		size_t index = (size_t)call.value - 1;
		if (index < (size_t)count->value) return element[index]->passUncounted(run);
		else return run.sink->called(run, call);
	}

	const CallWho* TypecheckPropertyCount::callWho(const Any* who) const
	{
		return new
			(Heap::allocate(sizeof(WhoCount)))
			WhoCount(this, who);
	}

	const Step *WhoCount::step_(Runner &run) const
	{
		new (run.allocate(sizeof(PipeCount))) PipeCount(*this);
		return whoAttribute();
	}

	const Step *Sink::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		const PilsString *string = (const PilsString*)anchor;
		if (&string->value[0] != range || (size_t)string->count->value != count)
		{
			string = PilsString::get(range, count);
			anchor->releaseReference();
		}
		return pass(run, string);
	}

	const Step *Sink::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
			if (!element[i]->as_Constant())
			{
				for (size_t j = 0; j < count; j++) element[j]->addReference();
				const ListExpress *listExpress = new
					(Heap::allocate(sizeof(ListExpress) + (count - 1) * sizeof(Any*)))
					const ListExpress(element, count);
				anchor->releaseReference();
				return pass(run, listExpress);
			}
		}
		const ListConstant *listConstant = ListConstant::get((const Constant* const*)element, count, true);
		anchor->releaseReference();
		return pass(run, listConstant);
	}

	const Step *Sink::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		const ListConstant *listConstant = ListConstant::get(element, count, true);
		anchor->releaseReference();
		return pass(run, listConstant);
	}

	const Step *SinkArgument::pass(Runner &run, long value)
	{
		if (value <= 0) return Sink::pass(run, value);
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkIndex))) SinkIndex(what, value);
		return what.whoAttribute();
	}

	const Step *SinkArgument::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v != value || v <= 0) return Sink::pass(run, value);
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkIndex))) SinkIndex(what, v);
		return what.whoAttribute();
	}

	const Step *SinkArgument::pass(Runner &run, const Integer &value)
	{
		value.addReference();
		if (value.value <= 0) return pass(run, (const Any*)&value);
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkIndex))) SinkIndex(what, &value);
		return what.whoAttribute();
	}

	const Step *SinkArgument::pass(Runner &run, const Integer *value)
	{
		if (value->value <= 0) return pass(run, (const Any*)value);
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkIndex))) SinkIndex(what, value);
		return what.whoAttribute();
	}

	const Step *SinkArgument::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkConcatenatingString))) SinkConcatenatingString(what, value);
		return what.whoAttribute();
	}

	const Step *SinkArgument::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkConcatenatingRange))) SinkConcatenatingRange(what, anchor, range, count);
		return what.whoAttribute();
	}

	Sink *SinkIndex::kick(Runner &run)
	{
		if (indexInteger) indexInteger->releaseReference();
		return this + 1;
	}

	const Step *SinkIndex::pass(Runner &run, const PilsString &value)
	{
		if (index <= value.count->value)
		{
			long result = value.value[index - 1];
			if (indexInteger) indexInteger->releaseReference();
			return (run.sink = this + 1)->pass(run, result);
		}
		else
		{
			value.addReference();
			return pass(run, (const Any*)&value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const ListConstant &value)
	{
		if (index <= value.count->value)
		{
			const Constant &result = *value.element[index - 1];
			if (indexInteger) indexInteger->releaseReference();
			run.sink = this + 1;
			return result.passUncounted(run);
		}
		else
		{
			value.addReference();
			return pass(run, (const Any*)&value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const ListExpress &value)
	{
		if (index <= value.count->value)
		{
			const Any &result = *value.element[index - 1];
			if (indexInteger) indexInteger->releaseReference();
			run.sink = this + 1;
			return result.passUncounted(run);
		}
		else
		{
			value.addReference();
			return pass(run, (const Any*)&value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const PilsString *value)
	{
		if (index <= value->count->value)
		{
			long result = value->value[index - 1];
			value->releaseReference();
			if (indexInteger) indexInteger->releaseReference();
			return (run.sink = this + 1)->pass(run, result);
		}
		else
		{
			return pass(run, (const Any*)value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const ListConstant *value)
	{
		if (index <= value->count->value)
		{
			const Constant *result = value->element[index - 1];
			result->addReference();
			value->releaseReference();
			if (indexInteger) indexInteger->releaseReference();
			run.sink = this + 1;
			return result->passCounted(run);
		}
		else
		{
			return pass(run, (const Any*)value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const ListExpress *value)
	{
		if (index <= value->count->value)
		{
			const Any *result = value->element[index - 1];
			result->addReference();
			value->releaseReference();
			if (indexInteger) indexInteger->releaseReference();
			run.sink = this + 1;
			return result->passCounted(run);
		}
		else
		{
			return pass(run, (const Any*)value);
		}
	}

	const Step *SinkIndex::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		if ((size_t)index > count) return Sink::pass(run, anchor, range, count);
		long result = range[index - 1];
		anchor->releaseReference();
		if (indexInteger) indexInteger->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkIndex::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		if ((size_t)index > count) return Sink::pass(run, anchor, range, count);
		const Constant *result = range[index - 1];
		result->addReference();
		anchor->releaseReference();
		if (indexInteger) indexInteger->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkIndex::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		if ((size_t)index > count) return Sink::pass(run, anchor, range, count);
		const Any* result = range[index - 1];
		result->addReference();
		anchor->releaseReference();
		if (indexInteger) indexInteger->releaseReference();
		run.sink = this + 1;
		return result->passCounted(run);
	}

	const Step *SinkIndex::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const Integer *argument = indexInteger;
		if (!argument) argument = Integer::get(index);
		const CallWho &what = this->what;
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, argument))->pass(run, nodeBuilding);
	}

	const Step *SinkIndex::pass(Runner &run, const Any *who)
	{
		const Integer *call = indexInteger;
		if (!call) call = Integer::get(index);
		const CallWho &what = this->what;
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	size_t Sink::concatenateCount()
	{
		return 0;
	}

	const Step *Sink::concatenateBuild(Runner &run, PILS_CHAR *text, PILS_CHAR *at)
	{
		const PilsString *string = PilsString::get(text, at - text);
		delete text;
		return pass(run, string);
	}

	const Step *SinkConcatenating::pass(Runner &run, const PilsString &string)
	{
		size_t count = concatenateCount() + string.count->value;
		PILS_CHAR *text = new PILS_CHAR[count];
		PILS_CHAR *at = text;
		for (size_t i = 0; i < (size_t)string.count->value; i++)
			*(at++) = string.value[i];
		return concatenateBuild(run, text, at);
	}

	const Step *SinkConcatenating::pass(Runner &run, const PilsString *string)
	{
		size_t count = concatenateCount() + string->count->value;
		PILS_CHAR *text = new PILS_CHAR[count];
		PILS_CHAR *at = text;
		for (size_t i = 0; i < (size_t)string->count->value; i++)
			*(at++) = string->value[i];
		string->releaseReference();
		return concatenateBuild(run, text, at);
	}

	const Step *SinkConcatenating::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t rangeCount)
	{
		size_t count = concatenateCount() + rangeCount;
		PILS_CHAR *text = new PILS_CHAR[count];
		PILS_CHAR *at = text;
		for (size_t i = 0; i < rangeCount; i++)
			*(at++) = range[i];
		anchor->releaseReference();
		return concatenateBuild(run, text, at);
	}

	Sink *SinkConcatenatingString::kick(Runner &run)
	{
		string->releaseReference();
		return this + 1;
	}

	const Step *SinkConcatenatingString::pass(Runner &run, const Any *value)
	{
		const PilsString *string = this->string;
		const CallWho &what = this->what;
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, string))->pass(run, value);
	}

	const Step *SinkConcatenatingString::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const PilsString *string = this->string;
		const CallWho &what = this->what;
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, string))->pass(run, nodeBuilding);
	}

	size_t SinkConcatenatingString::concatenateCount()
	{
		Sink *next = this + 1;
		return next->concatenateCount() + string->count->value;
	}

	const Step *SinkConcatenatingString::concatenateBuild(Runner &run, PILS_CHAR *text, PILS_CHAR *at)
	{
		for (size_t i = 0; i < (size_t)string->count->value; i++)
			*(at++) = string->value[i];
		string->releaseReference();
		return (run.sink = this + 1)->concatenateBuild(run, text, at);
	}

	Sink *SinkConcatenatingRange::kick(Runner &run)
	{
		anchor->releaseReference();
		return this + 1;
	}

	const Step *SinkConcatenatingRange::pass(Runner &run, const Any *value)
	{
		const PilsString *string = PilsString::get(text, count);
		anchor->releaseReference();
		const CallWho &what = this->what;
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, string))->pass(run, value);
	}

	const Step *SinkConcatenatingRange::pass(Runner &run, SinkTaggedNodeBuilding &nodeBuilding)
	{
		const PilsString *string = PilsString::get(text, count);
		anchor->releaseReference();
		const CallWho &what = this->what;
		run.sink = this + 1;
		return (new (run.allocate(sizeof(SinkWho))) SinkWho(what, string))->pass(run, nodeBuilding);
	}

	const Step *SinkConcatenatingRange::concatenateBuild(Runner &run, PILS_CHAR *text, PILS_CHAR *at)
	{
		for (size_t i = 0; i < count; i++)
			*(at++) = this->text[i];
		anchor->releaseReference();
		return (run.sink = this + 1)->concatenateBuild(run, text, at);
	}

	size_t SinkConcatenatingRange::concatenateCount()
	{
		Sink *next = this + 1;
		return next->concatenateCount() + count;
	}

	const NodeConstantShort *BuiltinClicheRange::newNode(const HashedConstant *&link, const Integer *value) const
	{
		if (value->value >= 0)
			return new (Heap::allocate(sizeof(RangeConstant))) RangeConstant(link, *this, value);
		else
			return new (Heap::allocate(sizeof(NodeConstantTiny))) NodeConstantTiny(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheRange::node(const Express *element) const
	{
		return new (Heap::allocate(sizeof(RangeExpress))) RangeExpress(*this, element);
	}

	const CallWho *RangeConstant::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoRangeConstant))) const WhoRangeConstant(this, who);
	}

	const CallWho *RangeExpress::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoRangeExpress))) const WhoRangeExpress(this, who);
	}

	const Step *WhoRangeConstant::step_(Runner &run) const
	{
		RangeConstant *call = (RangeConstant*)callAttribute();
		((BuiltinClicheRange*)call->cliche)->rangeSink(run, ((const Integer*)call->element[0])->value, *this);
		return whoAttribute();
	}

	const Step *WhoRangeExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkRangeOperand))) SinkRangeOperand(*this);
		return ((RangeExpress*)callAttribute())->element[0];
	}

	Sink *SinkRangeOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkRangeOperand::pass(Runner &run, long value)
	{
		if (value >= 0)
		{
			const WhoRangeExpress &what = this->what;
			const RangeExpress *call = (const RangeExpress*)what.callAttribute();
			run.sink = this + 1;
			((BuiltinClicheRange*)call->cliche)->rangeSink(run, value, what);
			return what.whoAttribute();
		}
		else return pass(run, (const Any*)Integer::get(value));
	}

	const Step *SinkRangeOperand::pass(Runner &run, const Integer &value)
	{
		if (value.value >= 0)
		{
			const WhoRangeExpress &what = this->what;
			const RangeExpress *call = (const RangeExpress*)what.callAttribute();
			run.sink = this + 1;
			((BuiltinClicheRange*)call->cliche)->rangeSink(run, value.value, what);
			return what.whoAttribute();
		}
		else
		{
			value.addReference();
			return pass(run, (const Any*)&value);
		}
	}

	const Step *SinkRangeOperand::pass(Runner &run, const Integer *value)
	{
		if (value->value >= 0)
		{
			RangeExpress *call = (RangeExpress*)what.callAttribute();
			const WhoRangeExpress &what = this->what;
			run.sink = this + 1;
			((BuiltinClicheRange*)call->cliche)->rangeSink(run, value->value, what);
			value->releaseReference();
			return what.whoAttribute();
		}
		else return pass(run, (const Any*)value);
	}

	const Step *SinkRangeOperand::pass(Runner &run, double value)
	{
		long v = (long)value;
		if ((double)v == value) return pass(run, v);
		else return pass(run, (const Any*)Number::get(value));
	}

	const Step *SinkRangeOperand::pass(Runner &run, const Any *value)
	{
		const WhoRangeExpress &what = this->what;
		run.sink = this + 1;
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, ((RangeExpress*)what.callAttribute())->cliche->node(&value));
		return what.whoAttribute();
	}

	void BuiltinClichePlusRange::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkPlusRange))) SinkPlusRange(what, range);
	}

	void BuiltinClichePlusSlackRange::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkPlusSlackRange))) SinkPlusSlackRange(what, range);
	}

	void BuiltinClichePlusRangeReverse::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkPlusRangeReverse))) SinkPlusRangeReverse(what, range);
	}

	void BuiltinClichePlusSlackRangeReverse::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkPlusSlackRangeReverse))) SinkPlusSlackRangeReverse(what, range);
	}

	void BuiltinClicheMinusRange::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkMinusRange))) SinkMinusRange(what, range);
	}

	void BuiltinClicheMinusSlackRange::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkMinusSlackRange))) SinkMinusSlackRange(what, range);
	}

	void BuiltinClicheMinusRangeReverse::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkMinusRangeReverse))) SinkMinusRangeReverse(what, range);
	}

	void BuiltinClicheMinusSlackRangeReverse::rangeSink(Runner &run, long range, const CallWho &what) const
	{
		new (run.allocate(sizeof(SinkMinusSlackRangeReverse))) SinkMinusSlackRangeReverse(what, range);
	}

	Sink *SinkRange::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkRange::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		RangeConstant *call = (RangeConstant*)what.callAttribute()->as_NodeConstant();
		if (call)
			call->addReference();
		else
			call = (RangeConstant*)((const ClicheShort*)((RangeExpress*)what.callAttribute())->cliche)->node(Integer::get(range));
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *SinkPlusRange::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[0], range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[0], range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[length - range], range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[length - range], range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[range], length - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->value[length], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->value[range], length - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->value[0], length - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const PilsString *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->value[0], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->value[0], length - range);
	}

	const Step *SinkPlusRange::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[length - range], range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[length - range], range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[range], length - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->element[length], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->element[range], length - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], length - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const ListConstant *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->element[0], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], length - range);
	}

	const Step *SinkPlusRange::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[length - range], range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[length - range], range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[range], length - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->element[length], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->element[range], length - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return pass(run, (const Any*)value);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], length - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const ListExpress *value)
	{
		size_t range = this->range;
		size_t length = value->count->value;
		if (length < range)
			return (run.sink = this + 1)->pass(run, value, &value->element[0], (size_t)0);
		else return (run.sink = this + 1)->pass(run, value, &value->element[0], length - range);
	}

	const Step *SinkPlusRange::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const Any *anchor, const PILS_CHAR *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	const Step *SinkPlusRange::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const Any *anchor, const Constant *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	const Step *SinkPlusRange::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusSlackRange::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, range);
	}

	const Step *SinkPlusRangeReverse::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkPlusSlackRangeReverse::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + count - range, range);
	}

	const Step *SinkMinusRange::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusSlackRange::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element + range, count - range);
	}

	const Step *SinkMinusRangeReverse::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range)
			return Sink::pass(run, anchor, element, count);
		else return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	const Step *SinkMinusSlackRangeReverse::pass(Runner &run, const Any *anchor, const Any *const *element, size_t count)
	{
		size_t range = this->range;
		if (count < range) range = count;
		return (run.sink = this + 1)->pass(run, anchor, element, count - range);
	}

	Pipe *SinkPlusSlackRange::connectPipe(Runner &run)
	{
		const CallWho &what = this->what;
		size_t range = this->range;
		(run.sink = this + 1)->connectPipe(run);
		PipePlusSlackRange *pipe = new (run.allocate(sizeof(PipePlusSlackRange))) PipePlusSlackRange(what, range);
		run.sink = pipe;
		return pipe;
	}

	Pipe *SinkMinusSlackRange::connectPipe(Runner &run)
	{
		const CallWho &what = this->what;
		size_t range = this->range;
		(run.sink = this + 1)->connectPipe(run);
		PipeMinusSlackRange *pipe = new (run.allocate(sizeof(PipeMinusSlackRange))) PipeMinusSlackRange(what, range);
		run.sink = pipe;
		return pipe;
	}

	Sink *PipeSlackRange::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *PipeSlackRange::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		RangeConstant *call = (RangeConstant*)what.callAttribute()->as_NodeConstant();
		if (call)
			call->addReference();
		else
			call = (RangeConstant*)((const ClicheShort*)((RangeExpress*)what.callAttribute())->cliche)->node(Integer::get((long)range));
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *PipeSlackRange::pipeEnd(Runner &run)
	{
		Pipe &next = this[1];
		run.sink = &next;
		return next.pipeEnd(run);
	}

	const Step *PipePlusSlackRange::pipeBegin(Runner &run)
	{
		Pipe &next = this[1];
		if (!range)
		{
			//trash pending pipes, pipe empty range
			for (Sink *sink = run.sink; sink != &next; sink = sink->kick(run));
			run.sink = &next;
			new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(NULL, (size_t)0);
		}
		return next.pipeBegin(run);
	}

	const Step *PipePlusSlackRange::pipeItem(Runner &run, const Any *item)
	{
		Pipe &next = this[1];
		if (range > 1)
		{
			range--;
			return next.pipeItem(run, item);
		}
		else
		{
			// No more items needed - kick pipe
			for (Sink *sink = run.sink; sink != this; sink = sink->kick(run));
			run.sink = this;
			if (range)
			{
				new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(NULL, (size_t)0);
				return next.pipeItem(run, item);
			}
			else
			{
				// Zero items required - this first one is irrelevant
				item->releaseReference();
				return next.pipeEnd(run);
			}
		}
	}

	const Step *PipeMinusSlackRange::pipeBegin(Runner &run)
	{
			Pipe &next = this[1];
			return next.pipeBegin(run);
	}

	const Step *PipeMinusSlackRange::pipeItem(Runner &run, const Any *item)
	{
		if (range)
		{
			// Still counting down - first items are thrashed
			range--;
			item->releaseReference();
			return (Pipesource*)run.sink;
		}
		else
		{
			// Countdown expired - further items are passed
			Pipe &next = this[1];
			return next.pipeItem(run, item);
		}
	}

	const CallWho *SearchName::whoSearch(const SearchString *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSearchString))) const WhoSearchString(call, who);
	}

	const CallWho *SearchName::whoSearch(const SearchListConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSearchListConstant))) const WhoSearchListConstant(call, who);
	}

	const CallWho *SearchName::whoSearch(const SearchExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoSearchExpress))) const WhoSearchExpress(call, who);
	}

	const CallWho *PlusRangeSearchName::whoSearch(const SearchString *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeSearchString))) const WhoPlusRangeSearchString(call, who);
	}

	const CallWho *PlusRangeSearchName::whoSearch(const SearchListConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeSearchListConstant))) const WhoPlusRangeSearchListConstant(call, who);
	}

	const CallWho *PlusRangeSearchName::whoSearch(const SearchExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeSearchExpress))) const WhoPlusRangeSearchExpress(call, who);
	}

	const CallWho *PlusRangeReverseSearchName::whoSearch(const SearchString *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeReverseSearchString))) const WhoPlusRangeReverseSearchString(call, who);
	}

	const CallWho *PlusRangeReverseSearchName::whoSearch(const SearchListConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeReverseSearchListConstant))) const WhoPlusRangeReverseSearchListConstant(call, who);
	}

	const CallWho *PlusRangeReverseSearchName::whoSearch(const SearchExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPlusRangeReverseSearchExpress))) const WhoPlusRangeReverseSearchExpress(call, who);
	}

	const CallWho *MinusRangeSearchName::whoSearch(const SearchString *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeSearchString))) const WhoMinusRangeSearchString(call, who);
	}

	const CallWho *MinusRangeSearchName::whoSearch(const SearchListConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeSearchListConstant))) const WhoMinusRangeSearchListConstant(call, who);
	}

	const CallWho *MinusRangeSearchName::whoSearch(const SearchExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeSearchExpress))) const WhoMinusRangeSearchExpress(call, who);
	}

	const CallWho *MinusRangeReverseSearchName::whoSearch(const SearchString *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeReverseSearchString))) const WhoMinusRangeReverseSearchString(call, who);
	}

	const CallWho *MinusRangeReverseSearchName::whoSearch(const SearchListConstant *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeReverseSearchListConstant))) const WhoMinusRangeReverseSearchListConstant(call, who);
	}

	const CallWho *MinusRangeReverseSearchName::whoSearch(const SearchExpress *call, const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoMinusRangeReverseSearchExpress))) const WhoMinusRangeReverseSearchExpress(call, who);
	}

	const NodeConstantShort *BuiltinClicheSearchAbstract::newNode(const HashedConstant *&link, const PilsString *value) const
	{
		return new (Heap::allocate(sizeof(SearchString))) SearchString(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheSearchAbstract::newNode(const HashedConstant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(SearchListConstant))) SearchListConstant(link, *this, value);
	}

	const NodeExpressShort *BuiltinClicheSearchAbstract::node(const Express *value) const
	{
		return new (Heap::allocate(sizeof(SearchExpress))) SearchExpress(*this, value);
	}

	const CallWho *SearchString::callWho(const Any *who) const
	{
		return ((const SearchNameAbstract*)cliche->head)->whoSearch(this, who);
	}

	const CallWho *SearchListConstant::callWho(const Any *who) const
	{
		return ((const SearchNameAbstract*)cliche->head)->whoSearch(this, who);
	}

	const CallWho *SearchExpress::callWho(const Any *who) const
	{
		return ((const SearchNameAbstract*)cliche->head)->whoSearch(this, who);
	}

	const Step *WhoSearchString::step_(Runner &run) const
	{
		SearchString &call = (SearchString&)*callAttribute();
		const PilsString *string = (const PilsString*)call.element[0];
		string->addReference();
		new (run.allocate(sizeof(SinkSearchString))) SinkSearchString(*this, (BuiltinClicheSearchAbstract&)*call.cliche, string);
		return whoAttribute();
	}

	const Step *WhoPlusRangeSearchString::step_(Runner &run) const
	{
		SearchString &call = (SearchString&)*callAttribute();
		const PilsString *string = (const PilsString*)call.element[0];
		string->addReference();
		new (run.allocate(sizeof(SinkSearchStringPlusRange))) SinkSearchStringPlusRange(*this, (BuiltinClicheSearchAbstract&)*call.cliche, string);
		return whoAttribute();
	}

	const Step *WhoPlusRangeReverseSearchString::step_(Runner &run) const
	{
		SearchString &call = (SearchString&)*callAttribute();
		const PilsString *string = (const PilsString*)call.element[0];
		string->addReference();
		new (run.allocate(sizeof(SinkSearchStringPlusRangeReverse))) SinkSearchStringPlusRangeReverse(*this, (BuiltinClicheSearchAbstract&)*call.cliche, string);
		return whoAttribute();
	}

	const Step *WhoMinusRangeSearchString::step_(Runner &run) const
	{
		SearchString &call = (SearchString&)*callAttribute();
		const PilsString *string = (const PilsString*)call.element[0];
		string->addReference();
		new (run.allocate(sizeof(SinkSearchStringMinusRange))) SinkSearchStringMinusRange(*this, (BuiltinClicheSearchAbstract&)*call.cliche, string);
		return whoAttribute();
	}

	const Step *WhoMinusRangeReverseSearchString::step_(Runner &run) const
	{
		SearchString &call = (SearchString&)*callAttribute();
		const PilsString *string = (const PilsString*)call.element[0];
		string->addReference();
		new (run.allocate(sizeof(SinkSearchStringMinusRangeReverse))) SinkSearchStringMinusRangeReverse(*this, (BuiltinClicheSearchAbstract&)*call.cliche, string);
		return whoAttribute();
	}

	const Step *WhoSearchListConstant::step_(Runner &run) const
	{
		SearchListConstant &call = (SearchListConstant&)*callAttribute();
		const ListConstant *list = (const ListConstant*)call.element[0];
		list->addReference();
		new (run.allocate(sizeof(SinkSearchListConstant))) SinkSearchListConstant(*this, (BuiltinClicheSearchAbstract&)*call.cliche, list);
		return whoAttribute();
	}

	const Step *WhoPlusRangeSearchListConstant::step_(Runner &run) const
	{
		SearchListConstant &call = (SearchListConstant&)*callAttribute();
		const ListConstant *list = (const ListConstant*)call.element[0];
		list->addReference();
		new (run.allocate(sizeof(SinkSearchListConstantPlusRange))) SinkSearchListConstantPlusRange(*this, (BuiltinClicheSearchAbstract&)*call.cliche, list);
		return whoAttribute();
	}

	const Step *WhoPlusRangeReverseSearchListConstant::step_(Runner &run) const
	{
		SearchListConstant &call = (SearchListConstant&)*callAttribute();
		const ListConstant *list = (const ListConstant*)call.element[0];
		list->addReference();
		new (run.allocate(sizeof(SinkSearchListConstantPlusRangeReverse))) SinkSearchListConstantPlusRangeReverse(*this, (BuiltinClicheSearchAbstract&)*call.cliche, list);
		return whoAttribute();
	}

	const Step *WhoMinusRangeSearchListConstant::step_(Runner &run) const
	{
		SearchListConstant &call = (SearchListConstant&)*callAttribute();
		const ListConstant *list = (const ListConstant*)call.element[0];
		list->addReference();
		new (run.allocate(sizeof(SinkSearchListConstantMinusRange))) SinkSearchListConstantMinusRange(*this, (BuiltinClicheSearchAbstract&)*call.cliche, list);
		return whoAttribute();
	}

	const Step *WhoMinusRangeReverseSearchListConstant::step_(Runner &run) const
	{
		SearchListConstant &call = (SearchListConstant&)*callAttribute();
		const ListConstant *list = (const ListConstant*)call.element[0];
		list->addReference();
		new (run.allocate(sizeof(SinkSearchListConstantMinusRangeReverse))) SinkSearchListConstantMinusRangeReverse(*this, (BuiltinClicheSearchAbstract&)*call.cliche, list);
		return whoAttribute();
	}

	const Step *WhoSearchExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSearchOperand))) SinkSearchOperand(*this);
		return ((const NodeExpressShort*)callAttribute())->element[0];
	}

	const Step *WhoPlusRangeSearchExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSearchPlusRangeOperand))) SinkSearchPlusRangeOperand(*this);
		return ((const NodeExpressShort*)callAttribute())->element[0];
	}

	const Step *WhoPlusRangeReverseSearchExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSearchPlusRangeReverseOperand))) SinkSearchPlusRangeReverseOperand(*this);
		return ((const NodeExpressShort*)callAttribute())->element[0];
	}

	const Step *WhoMinusRangeSearchExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSearchMinusRangeOperand))) SinkSearchMinusRangeOperand(*this);
		return ((const NodeExpressShort*)callAttribute())->element[0];
	}

	const Step *WhoMinusRangeReverseSearchExpress::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkSearchMinusRangeReverseOperand))) SinkSearchMinusRangeReverseOperand(*this);
		return ((const NodeExpressShort*)callAttribute())->element[0];
	}

	Sink *SinkSearchOperand::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkSearchOperand::pass(Runner &run, const Any *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		const ClicheShort &cliche = (const ClicheShort&)*((const NodeExpress*)what.callAttribute())->cliche;
		const Any *argument = cliche.node(value);
		new (run.allocate(sizeof(SinkWho))) SinkWho(what, argument);
		return what.whoAttribute();
	}

	const Step *SinkSearchOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchString))) SinkSearchString(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchOperand::pass(Runner &run, const ListConstant *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListConstant))) SinkSearchListConstant(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchOperand::pass(Runner &run, const ListExpress *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListExpress))) SinkSearchListExpress(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchStringPlusRange))) SinkSearchStringPlusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeOperand::pass(Runner &run, const ListConstant *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListConstantPlusRange))) SinkSearchListConstantPlusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeOperand::pass(Runner &run, const ListExpress *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListExpressPlusRange))) SinkSearchListExpressPlusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeReverseOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchStringPlusRangeReverse))) SinkSearchStringPlusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeReverseOperand::pass(Runner &run, const ListConstant *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListConstantPlusRangeReverse))) SinkSearchListConstantPlusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchPlusRangeReverseOperand::pass(Runner &run, const ListExpress *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListExpressPlusRangeReverse))) SinkSearchListExpressPlusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchStringMinusRange))) SinkSearchStringMinusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeOperand::pass(Runner &run, const ListConstant *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListConstantMinusRange))) SinkSearchListConstantMinusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeOperand::pass(Runner &run, const ListExpress *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListExpressMinusRange))) SinkSearchListExpressMinusRange(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeReverseOperand::pass(Runner &run, const PilsString *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchStringMinusRangeReverse))) SinkSearchStringMinusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeReverseOperand::pass(Runner &run, const ListConstant *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListConstantMinusRangeReverse))) SinkSearchListConstantMinusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	const Step *SinkSearchMinusRangeReverseOperand::pass(Runner &run, const ListExpress *value)
	{
		const CallWho &what = this->what;
		run.sink = this + 1;
		BuiltinClicheSearchAbstract &cliche = (BuiltinClicheSearchAbstract&)*((const NodeExpress*)what.callAttribute())->cliche;
		new (run.allocate(sizeof(SinkSearchListExpressMinusRangeReverse))) SinkSearchListExpressMinusRangeReverse(what, cliche, value);
		return what.whoAttribute();
	}

	Sink *SinkSearchString::kick(Runner &run)
	{
		string->releaseReference();
		return this + 1;
	}

	const Step *SinkSearchString::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const NodeConstantShort *call = cliche.nodeConstant(string);
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *SinkSearchString::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		size_t hit = cliche.search(range, count, string->value, string->count->value);
		return this->searched(run, anchor, range, count, hit);
	}

	const Step *SinkSearchString::pass(Runner &run, const PilsString *who)
	{
		size_t hit = cliche.search(who->value, who->count->value, string->value, string->count->value);
		return this->searched(run, who, who->value, who->count->value, hit);
	}

	const Step *SinkSearchString::searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit)
	{
		string->releaseReference();
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, (long)hit);
	}

	const Step *SinkSearchStringPlusRange::searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit)
	{
		string->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, hit);
	}

	const Step *SinkSearchStringPlusRangeReverse::searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit)
	{
		string->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + count - hit, hit);
	}

	const Step *SinkSearchStringMinusRange::searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit)
	{
		string->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + hit, count - hit);
	}

	const Step *SinkSearchStringMinusRangeReverse::searched(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count, size_t hit)
	{
		string->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, count - hit);
	}

	Sink *SinkSearchListConstant::kick(Runner &run)
	{
		list->releaseReference();
		return this + 1;
	}

	const Step *SinkSearchListConstant::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const NodeConstantShort *call = cliche.nodeConstant(list);
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *SinkSearchListConstant::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		size_t hit = cliche.search((const Any *const *)range, count, (const Any *const *)list->element, list->count->value);
		return this->searched(run, anchor, range, count, hit);
	}

	const Step *SinkSearchListConstant::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		size_t hit = cliche.search(range, count, (const Any *const *)list->element, list->count->value);
		return this->searched(run, anchor, range, count, hit);
	}

	const Step *SinkSearchListConstant::pass(Runner &run, const ListConstant *who)
	{
		size_t hit = cliche.search((const Any *const *)who->element, who->count->value, (const Any *const *)list->element, list->count->value);
		return this->searched(run, who, who->element, who->count->value, hit);
	}

	const Step *SinkSearchListConstant::pass(Runner &run, const ListExpress *who)
	{
		size_t hit = cliche.search(who->element, who->count->value, (const Any *const *)list->element, list->count->value);
		return this->searched(run, who, who->element, who->count->value, hit);
	}

	const Step *SinkSearchListConstant::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, (long)hit);
	}

	const Step *SinkSearchListConstant::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, (long)hit);
	}

	const Step *SinkSearchListConstantPlusRange::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, hit);
	}

	const Step *SinkSearchListConstantPlusRange::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, hit);
	}

	const Step *SinkSearchListConstantPlusRangeReverse::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + count - hit, hit);
	}

	const Step *SinkSearchListConstantPlusRangeReverse::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + count - hit, hit);
	}

	const Step *SinkSearchListConstantMinusRange::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + hit, count - hit);
	}

	const Step *SinkSearchListConstantMinusRange::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + hit, count - hit);
	}

	const Step *SinkSearchListConstantMinusRangeReverse::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, count - hit);
	}

	const Step *SinkSearchListConstantMinusRangeReverse::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, count - hit);
	}

	Sink *SinkSearchListExpress::kick(Runner &run)
	{
		list->releaseReference();
		return this + 1;
	}

	const Step *SinkSearchListExpress::pass(Runner &run, const Any *who)
	{
		const CallWho &what = this->what;
		const NodeExpressShort *call = cliche.node(list);
		return (run.sink = this + 1)->call(run, what, call, who);
	}

	const Step *SinkSearchListExpress::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		size_t hit = cliche.search((const Any *const *)range, count, (const Any *const *)list->element, list->count->value);
		return this->searched(run, anchor, range, count, hit);
	}

	const Step *SinkSearchListExpress::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		size_t hit = cliche.search(range, count, (const Any *const *)list->element, list->count->value);
		return this->searched(run, anchor, range, count, hit);
	}

	const Step *SinkSearchListExpress::pass(Runner &run, const ListConstant *who)
	{
		size_t hit = cliche.search((const Any *const *)who->element, who->count->value, (const Any *const *)list->element, list->count->value);
		return this->searched(run, who, who->element, who->count->value, hit);
	}

	const Step *SinkSearchListExpress::pass(Runner &run, const ListExpress *who)
	{
		size_t hit = cliche.search(who->element, who->count->value, (const Any *const *)list->element, list->count->value);
		return this->searched(run, who, who->element, who->count->value, hit);
	}

	const Step *SinkSearchListExpress::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, (long)hit);
	}

	const Step *SinkSearchListExpress::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, (long)hit);
	}

	const Step *SinkSearchListExpressPlusRange::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, hit);
	}

	const Step *SinkSearchListExpressPlusRange::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, hit);
	}

	const Step *SinkSearchListExpressPlusRangeReverse::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + count - hit, hit);
	}

	const Step *SinkSearchListExpressPlusRangeReverse::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + count - hit, hit);
	}

	const Step *SinkSearchListExpressMinusRange::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + hit, count - hit);
	}

	const Step *SinkSearchListExpressMinusRange::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range + hit, count - hit);
	}

	const Step *SinkSearchListExpressMinusRangeReverse::searched(Runner &run, const Any *anchor, const Constant *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, count - hit);
	}

	const Step *SinkSearchListExpressMinusRangeReverse::searched(Runner &run, const Any *anchor, const Any *const *range, size_t count, size_t hit)
	{
		list->releaseReference();
		return (run.sink = this + 1)->pass(run, anchor, range, count - hit);
	}

	size_t BuiltinClicheSearchCount::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			size_t count = 0;
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2)
					{
						count++;
						i += c2;
						if (i + c2 > c1) return count;
						j = 0;
					}
				}
			}
			return count;
		}
		else return c1 + 1;
	}

	size_t BuiltinClicheSearchCount::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			size_t count = 0;
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2)
					{
						count++;
						i += c2;
						if (i + c2 > c1) return count;
						j = 0;
					}
				}
			}
			return count;
		}
		else return c1 + 1;
	}

	size_t BuiltinClicheSearchContains::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2) return i + c2;
				}
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchContains::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2) return i + c2;
				}
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchTill::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2) return i;
				}
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchTill::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[i + j] == s2[j];)
				{
					if (++j == c2) return i;
				}
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchSpread::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			size_t j = 0;
			for (size_t i = 0; i < c1;)
			{
				if (s1[i++] == s2[j] && ++j == c2) return i;
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchSpread::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			size_t j = 0;
			for (size_t i = 0; i < c1;)
			{
				if (s1[i++] == s2[j] && ++j == c2) return i;
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchPrefix::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c1 >= c2)
		{
			for (size_t i = 0; i < c2; i++)
			{
				if (s1[i] != s2[i]) return 0;
			}
			return c2;
		}
		return 0;
	}

	size_t BuiltinClicheSearchPrefix::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c1 >= c2)
		{
			for (size_t i = 0; i < c2; i++)
			{
				if (s1[i] != s2[i]) return 0;
			}
			return c2;
		}
		return 0;
	}

	size_t BuiltinClicheSearchRhyme::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[i] != s2[i]) return i;
		}
	}

	size_t BuiltinClicheSearchRhyme::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[i] != s2[i]) return i;
		}
	}

	size_t BuiltinClicheSearchUnrhyme::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[i] == s2[i]) return i;
		}
	}

	size_t BuiltinClicheSearchUnrhyme::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[i] == s2[i]) return i;
		}
	}

	size_t BuiltinClicheSearchPlus::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0;; j++)
			{
				if (j == c2) return i;
				if (s1[i] == s2[j]) break;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchPlus::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0;; j++)
			{
				if (j == c2) return i;
				if (s1[i] == s2[j]) break;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchMinus::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0; j < c2; j++)
			{
				if (s1[i] == s2[j]) return i;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchMinus::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0; j < c2; j++)
			{
				if (s1[i] == s2[j]) return i;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchContainsReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[c1 - 1 - i - j] == s2[c2 - 1 - j];)
				{
					if (++j == c2) return i + c2;
				}
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchContainsReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[c1 - 1 - i - j] == s2[c2 - 1 - j];)
				{
					if (++j == c2) return i + c2;
				}
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchTillReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[c1 - 1 - i - j] == s2[c2 - 1 - j];)
				{
					if (++j == c2) return i;
				}
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchTillReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			for (size_t i = 0; i + c2 <= c1; i++)
			{
				for (size_t j = 0; s1[c1 - 1 - i - j] == s2[c2 - 1 - j];)
				{
					if (++j == c2) return i;
				}
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchSpreadReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c2)
		{
			size_t j = 0;
			for (size_t i = 0; i < c1;)
			{
				if (s1[c1 - 1 - i++] == s2[c2 - 1 - j] && ++j == c2) return i;
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchSpreadReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c2)
		{
			size_t j = 0;
			for (size_t i = 0; i < c1;)
			{
				if (s1[c1 - 1 - i++] == s2[c2 - 1 - j] && ++j == c2) return i;
			}
		}
		return 0;
	}

	size_t BuiltinClicheSearchPrefixReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		if (c1 >= c2)
		{
			for (size_t i = 0; i < c2; i++)
			{
				if (s1[c1 - 1 - i] != s2[c2 - 1 - i]) return 0;
			}
			return c2;
		}
		return 0;
	}

	size_t BuiltinClicheSearchPrefixReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		if (c1 >= c2)
		{
			for (size_t i = 0; i < c2; i++)
			{
				if (s1[c1 - 1 - i] != s2[c2 - 1 - i]) return 0;
			}
			return c2;
		}
		return 0;
	}

	size_t BuiltinClicheSearchRhymeReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[c1 - 1 - i] != s2[c2 - 1 - i]) return i;
		}
	}

	size_t BuiltinClicheSearchRhymeReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[c1 - 1 - i] != s2[c2 - 1 - i]) return i;
		}
	}

	size_t BuiltinClicheSearchUnrhymeReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[c1 - 1 - i] == s2[c2 - 1 - i]) return i;
		}
	}

	size_t BuiltinClicheSearchUnrhymeReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0;;i++)
		{
			if (i == c1 || i == c2 || s1[c1 - 1 - i] == s2[c2 - 1 - i]) return i;
		}
	}

	size_t BuiltinClicheSearchPlusReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0;; j++)
			{
				if (j == c2) return i;
				if (s1[c1 - 1 - i] == s2[j]) break;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchPlusReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0;; j++)
			{
				if (j == c2) return i;
				if (s1[c1 - 1 - i] == s2[j]) break;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchMinusReverse::search(const PILS_CHAR *s1, size_t c1, const PILS_CHAR *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0; j < c2; j++)
			{
				if (s1[c1 - 1 - i] == s2[j]) return i;
			}
		}
		return c1;
	}

	size_t BuiltinClicheSearchMinusReverse::search(const Any *const *s1, size_t c1, const Any *const *s2, size_t c2) const
	{
		for (size_t i = 0; i < c1; i++)
		{
			for (size_t j = 0; j < c2; j++)
			{
				if (s1[c1 - 1 - i] == s2[j]) return i;
			}
		}
		return c1;
	}

	const CallWho *PropertyCasing::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoCasing))) const WhoCasing(this, who);
	}

	const Step *WhoCasing::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkCasing))) SinkCasing(*this);
		return whoAttribute();
	}

	Sink *SinkCasing::kick(Runner &run)
	{
		return this + 1;
	}

	const Step *SinkCasing::pass(Runner &run, const Any *who)
	{
		const WhoCasing &what = this->what;
		return (run.sink = this + 1)->call(run, what, (PropertyCasing&)*what.callAttribute(), who);
	}

	const Step *SinkCasing::pass(Runner &run, const PilsString *value)
	{
		return pass(run, value, value->value, value->count->value);
	}

	const Step *SinkCasing::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		const PilsString *transformed = ((PropertyCasing*)what.callAttribute())->transform(range, count, PilsString::defaultLocale);
		anchor->releaseReference();
		return (run.sink = this + 1)->pass(run, transformed);
	}

	const CallWho *PropertyTraverse::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyTraverse))) const WhoPropertyTraverse(this, who);
	}

	const Step *WhoPropertyTraverse::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyTraverse))) SinkPropertyTraverse(*this);
		return whoAttribute();
	}

	const CallWho *PropertySinglewise::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertySinglewise))) const WhoPropertySinglewise(this, who);
	}

	const Step *WhoPropertySinglewise::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertySinglewise))) SinkPropertySinglewise(*this);
		return whoAttribute();
	}

	const Step *SinkPropertySinglewise::pass(Runner &run, const ListConstant *value)
	{
		if (value->count->value == 1)
		{
			const Constant *item = value->element[0];
			item->addReference();
			value->releaseReference();
			run.sink = this + 1;
			return item->passCounted(run);
		}
		else return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkPropertySinglewise::pass(Runner &run, const ListExpress *value)
	{
		if (value->count->value == 1)
		{
			const Any *item = value->element[0];
			item->addReference();
			value->releaseReference();
			run.sink = this + 1;
			return item->passCounted(run);
		}
		else return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkPropertySinglewise::pass(Runner &run, const Any *value)
	{
		run.sink = this + 1;
		return value->passCounted(run);
	}

	const CallWho *PropertyListwise::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoPropertyListwise))) const WhoPropertyListwise(this, who);
	}

	const Step *WhoPropertyListwise::step_(Runner &run) const
	{
		new (run.allocate(sizeof(SinkPropertyListwise))) SinkPropertyListwise(*this);
		return whoAttribute();
	}

	const Step *SinkPropertyListwise::pass(Runner &run, const ListConstant *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkPropertyListwise::pass(Runner &run, const ListExpress *value)
	{
		return (run.sink = this + 1)->pass(run, value);
	}

	const Step *SinkPropertyListwise::pass(Runner &run, const Any *value)
	{
		if (value->as_Constant())
			return (run.sink = this + 1)->pass(run, ListConstant::get((const Constant *const *)&value, 1));
		else
			return (run.sink = this + 1)->pass(run, new (Heap::allocate(sizeof(ListExpress))) const ListExpress(&value, 1));
	}

	const Step *SinkPropertyTraverse::pass(Runner &run, const ListConstant *value)
	{
		size_t elementSize = value->count->value;
		if (elementSize == 0) return (run.sink = this + 1)->pass(run, value);
		const Integer *countFirst;
		const Constant *const *e;
		if (!value->element[0]->isList((const Any *const *&)e, countFirst)) return SinkProperty::pass(run, (const Any*)value);
		for (size_t i = 1; i < elementSize; i++)
		{
			const Integer *count;
			if (!value->element[i]->isList((const Any *const *&)e, count)||count != countFirst)
				return SinkProperty::pass(run, (const Any*)value);
		}
		size_t listSize = countFirst->value;
		const Constant **list = new const Constant *[listSize];
		const Constant **element = new const Constant *[elementSize];
		const Constant *const **cursor = new const Constant *const *[elementSize];
		for (size_t i = 0; i < elementSize; i++)
			cursor[i] = &((const ListConstant*)value->element[i])->element[0];
		for (size_t j = 0; j < listSize; j++)
		{
			for (size_t i = 0; i < elementSize; i++)
				element[i] = *cursor[i]++;
			list[j] = ListConstant::get(element, elementSize, true);
		}
		delete cursor;
		delete element;
		const ListConstant *result = ListConstant::get(list, listSize);
		delete list;
		value->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkPropertyTraverse::pass(Runner &run, const ListExpress *value)
	{
		size_t elementSize = value->count->value;
		if (elementSize == 0) return (run.sink = this + 1)->pass(run, value);
		const Integer *countFirst;
		const Any *const *e;
		if (!value->element[0]->isList(e, countFirst)) return SinkProperty::pass(run, (const Any*)value);
		for (size_t i = 1; i < elementSize; i++)
		{
			const Integer *count;
			if (!value->element[i]->isList(e, count)||count != countFirst)
				return SinkProperty::pass(run, (const Any*)value);
		}
		size_t listSize = countFirst->value;
		const Any **list = new const Any *[listSize];
		const Any **element = new const Any *[elementSize];
		const Any *const **cursor = new const Any *const*[elementSize];
		for (size_t i = 0; i < elementSize; i++)
			value->element[i]->isList(cursor[i], countFirst);
		for (size_t j = 0; j < listSize; j++)
		{
			bool express = false;
			for (size_t i = 0; i < elementSize; i++)
			{
				const Any *e = *cursor[i]++;
				element[i] = e;
				e->addReference();
				if (!express && !e->as_Constant()) express = true;
			}
			if (express)
				list[j] = new (Heap::allocate(sizeof(ListExpress) + (elementSize - 1) * sizeof(Any*))) ListExpress(element, elementSize);
			else list[j] = ListConstant::get((const Constant *const *)element, elementSize);
		}
		delete cursor;
		delete element;
		const ListExpress *result = new (Heap::allocate(sizeof(ListExpress) + (listSize - 1) * sizeof(Any*))) ListExpress(list, listSize);
		delete list;
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *BuiltinClicheSplice::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const PilsString *separator = value->as_String();
		if (separator)
		{
			new (run.allocate(sizeof(SinkSpliceString))) SinkSpliceString(what, separator);
			return what.whoAttribute();
		}
		const Any *const *element;
		const Integer *count;
		if (value->isList(element, count))
		{
			run.sink->connectPipe(run);
			new (run.allocate(sizeof(PipeSplice))) PipeSplice(what);
			new (run.allocate(sizeof(PipeListSeparator))) PipeListSeparator(what, value);
			return what.whoAttribute();
		}
		else return BuiltinClicheUntypedOperation::gotOperand(run, what, value);
	}

	Sink *SinkStringOperation::kick(Runner &run)
	{
		operand->releaseReference();
		return this + 1;
	}

	const Step *SinkStringOperation::pass(Runner &run, const Any *who)
	{
		const WhoUntypedOperation &what = this->what;
		const ClicheShort *cliche;
		const Any *const *dummy;
		what.callAttribute()->isNode(dummy, (const Cliche*&)cliche);
		const Any *argument = cliche->node(operand);
		return (run.sink = this + 1)->call(run, what, argument, who);
	}

	const Step *SinkSpliceString::pass(Runner &run, const ListConstant *list)
	{
		if (list == &Empty::singleton)
		{
			list->releaseReference();
			const PilsString *separator = operand;
			return (run.sink = this + 1)->pass(run, separator, separator->value, (size_t)0);
		}
		size_t listCount = list->count->value;
		size_t separatorCount = operand->count->value;
		size_t spliceCount = separatorCount * (listCount - 1); //TODO: overflow detection
		for (size_t i = 0; i < listCount; i++)
		{
			const PilsString *element = list->element[i]->as_String();
			if (!element) return pass(run, (const Any*)list);
			spliceCount += element->count->value; //TODO: overflow detection
		}
		PILS_CHAR *spliceText = new PILS_CHAR[spliceCount];
		PILS_CHAR *splicing = spliceText;
		for (size_t i = 0; i < listCount; i++)
		{
			if (i) for (size_t j = 0; j < separatorCount; j++) *splicing++ = operand->value[j];
			const PilsString *element = list->element[i]->as_String();
			size_t count = element->count->value;
			for (size_t j = 0; j < count; j++) *splicing++ = element->value[j];
		}
		const PilsString *result = PilsString::get(spliceText, spliceCount);
		delete spliceText;
		list->releaseReference();
		operand->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *BuiltinClicheSplit::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Integer *integer;
		if (const PilsString *separator = value->as_String())
		{
			new (run.allocate(sizeof(SinkSplitString))) SinkSplitString(what, separator);
		}
		else if ((integer = value->as_Integer()) && integer->value > 0 && integer->value <= 1000)
		{
			new (run.allocate(sizeof(SinkSplitSize))) SinkSplitSize(what, integer->value);
			integer->releaseReference();
		}
		else
		{
			const ClicheShort *cliche;
			const Any *const *dummy;
			what.callAttribute()->isNode(dummy, (const Cliche*&)cliche);
			const Any *argument = cliche->node(value);
			new (run.allocate(sizeof(SinkWho))) SinkWho(what, argument);
		}
		return what.whoAttribute();
	}

	const Step *SinkSplitString::pass(Runner &run, const PilsString *string)
	{
		const PilsString *separator = operand;
		Pipe *pipe = (run.sink = this + 1)->connectPipe(run);
		if (separator->count->value)
			new (run.allocate(sizeof(PipesourceSplit))) PipesourceSplit(string, separator);
		else
		{
			new (run.allocate(sizeof(PipesourceSplitEmptySeparator))) PipesourceSplitEmptySeparator(string);
			separator->releaseReference();
		}
		return pipe->pipeBegin(run);
	}

	Sink *PipesourceSplitEmptySeparator::kick(Runner &run)
	{
		string->releaseReference();
		return this + 1;
	}

	const Step *PipesourceSplitEmptySeparator::step_(Runner &run) const
	{
		Pipe *pipe = (Pipe*)(this + 1);
		if (at < end) return pipe->pipeItem(run, PilsString::get(((PipesourceSplitEmptySeparator *)this)->at++, 1));
		else
		{
			string->releaseReference();
			run.sink = pipe;
			return pipe->pipeEnd(run);
		}
	}

	Sink *PipesourceSplit::kick(Runner &run)
	{
		string->releaseReference();
		separator->releaseReference();
		return this + 1;
	}

	const Step *PipesourceSplit::step_(Runner &run) const
	{
		Pipe *pipe = (Pipe*)(this + 1);
		if (at)
		{
			size_t separatorCount = separator->count->value;
			const PilsString *item = NULL;
			for (const PILS_CHAR *to = at; !item && to <= end - separatorCount; to++)
			{
				for (size_t i = 0; to[i] == separator->value[i];)
				{
					if (++i == separatorCount)
					{
						item = PilsString::get(at, to - at);
						((PipesourceSplit *)this)->at = to + separatorCount;
						break;
					}
				}
			}
			if (!item)
			{
				item = PilsString::get(at, end - at);
				((PipesourceSplit *)this)->at = NULL;
			}
			return pipe->pipeItem(run, item);
		}
		else
		{
			string->releaseReference();
			separator->releaseReference();
			run.sink = pipe;
			return pipe->pipeEnd(run);
		}
	}

	const Step *SinkSplitSize::pass(Runner &run, const PilsString *value)
	{
		return pass(run, value, value->value, value->count->value);
	}

	const Step *SinkSplitSize::pass(Runner &run, const ListConstant *value)
	{
		return pass(run, value, value->element, value->count->value);
	}

	const Step *SinkSplitSize::pass(Runner &run, const ListExpress *value)
	{
		return pass(run, value, value->element, value->count->value);
	}

	const Step *SinkSplitSize::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		long size = this->range;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		new (run.allocate(sizeof(PipesourceSplitStringSize))) PipesourceSplitStringSize(anchor, range, count, size);
		return pipe.pipeBegin(run);
	}

	const Step *SinkSplitSize::pass(Runner &run, const Any *anchor, const Any *const *range, size_t count)
	{
		Pipe &pipe = *connectPipe(run);
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(range, count);
		return pipe.pipeBegin(run);
	}

	const Step *SinkSplitSize::pass(Runner &run, const Any *anchor, const Constant *const *range, size_t count)
	{
		Pipe &pipe = *connectPipe(run);
		new (run.allocate(sizeof(PipeHold))) PipeHold(anchor);
		new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange((const Any *const *)range, count);
		return pipe.pipeBegin(run);
	}

	Sink *PipesourceSplitStringSize::kick(Runner &run)
	{
		anchor->releaseReference();
		return this + 1;
	}

	const Step *PipesourceSplitStringSize::step_(Runner &run) const
	{
		Pipe &pipe = (Pipe&)this[1];
		if (count)
		{
			if (size > count) ((PipesourceSplitStringSize *)this)->size = count;
			const PilsString *string = PilsString::get(this->range, size);
			((PipesourceSplitStringSize *)this)->count -= size;
			((PipesourceSplitStringSize *)this)->range += size;
			return pipe.pipeItem(run, string);
		}
		else
		{
			anchor->releaseReference();
			run.sink = &pipe;
			return pipe.pipeEnd(run);
		}
	}

	Pipe *SinkSplitSize::connectPipe(Runner &run)
	{
		size_t size = this->range;
		const CallWho &what = this->what;
		Pipe &pipe = *(run.sink = this + 1)->connectPipe(run);
		return new (run.allocate(sizeof(PipeSplitSize) + sizeof(const Any *) * size)) PipeSplitSize(pipe, (WhoUntypedOperation &)what);
	}

	Sink *PipeSplitSize::kick(Runner &run)
	{
		for (const Any **trash = begin(); trash != at; trash++)
			(*trash)->releaseReference();
		return &pipe;
	}

	const Step *PipeSplitSize::pass(Runner &run, const Any *thing)
	{
		const WhoUntypedOperation &what = this->what;
		const Any *const *dummy;
		const ClicheTiny *cliche;
		what.callAttribute()->isNode(dummy, (const Cliche*&)cliche);
		const Any *argument = cliche->nodeConstant(Integer::get((long)(end() - begin())));
		return (run.sink = kick(run))->call(run, what, argument, thing);
	}

	const Step *PipeSplitSize::pipeBegin(Runner &run)
	{
		return pipe.pipeBegin(run);
	}

	const Step *PipeSplitSize::pipeItem(Runner &run, const Any *item)
	{
		*at++ = item;
		if (at == end())
		{
			for (const Any **test = begin();; test++)
			{
				if (test == at)
				{
					item = ListConstant::get((const Constant *const *)begin(), at - begin());
					break;
				}
				if (!(*test)->as_Constant())
				{
					item = new (Heap::allocate(sizeof(ListExpress) + (char*)(at - 1) - (char*)begin())) ListExpress(begin(), at - begin());
					break;
				}
			}
			at = begin();
			return pipe.pipeItem(run, item);
		}
		else return (Pipesource*)run.sink;
	}

	const Step *PipeSplitSize::pipeEnd(Runner &run)
	{
		if (at == begin())
		{
			run.sink = &pipe;
			return pipe.pipeEnd(run);
		}
		else
		{
			const Any *item;
			for (const Any **test = begin();; test++)
			{
				if (test == at)
				{
					item = ListConstant::get((const Constant *const *)begin(), at - begin());
					break;
				}
				if (!(*test)->as_Constant())
				{
					item = new (Heap::allocate(sizeof(ListExpress) + (char*)(at - 1) - (char*)begin())) ListExpress(begin(), at - begin());
					break;
				}
			}
			Pipe &pipe = this->pipe;
			run.sink = &pipe;
			new (run.allocate(sizeof(PipesourceListRange))) PipesourceListRange(NULL, (size_t)0);
			return pipe.pipeItem(run, item);
		}
	}

	const Step *BuiltinClicheReplaceBase::gotOperand(Runner &run, const WhoUntypedOperation &what, const Any *value) const
	{
		const Any *const *element = NULL;
		const Integer *count;
		if (value->isList(element, count) && ((size_t)count->value & (size_t)1) == 0)
		{
			for (const Any *const *const end = element + count->value; element != NULL && element < end;)
			{
				const PilsString *search = (*element++)->as_String();
				const PilsString *replace = (*element++)->as_String();
				if (search == NULL || invalidSearchstringLength(search->count->value) || replace == NULL)
					element = NULL;
			}
		}
		else element = NULL; // odd lengt = misfit;
		if (element)
			pushReplaceSink(run, what, (const ListConstant*)value);
		else
		{
			const ClicheShort *cliche;
			const Any *const *dummy;
			what.callAttribute()->isNode(dummy, (const Cliche*&)cliche);
			const Any *argument = cliche->node(value);
			new (run.allocate(sizeof(SinkWho))) SinkWho(what, argument);
		}
		return what.whoAttribute();
	}

	bool BuiltinClicheReplaceBase::invalidSearchstringLength(size_t i) const
	{
		return false;
	}

	bool BuiltinClicheReplace::invalidSearchstringLength(size_t i) const
	{
		return i == 0;
	}

	void BuiltinClicheReplace::pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const
	{
		new (run.allocate(sizeof(SinkReplaceStringPairs))) SinkReplaceStringPairs(what, value);
	}

	void BuiltinClicheReplaceBeginning::pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const
	{
		new (run.allocate(sizeof(SinkReplaceBeginningStringPairs))) SinkReplaceBeginningStringPairs(what, value);
	}

	void BuiltinClicheReplaceEnding::pushReplaceSink(Runner &run, const WhoUntypedOperation &what, const ListConstant *value) const
	{
		new (run.allocate(sizeof(SinkReplaceEndingStringPairs))) SinkReplaceEndingStringPairs(what, value);
	}

	Sink *SinkReplaceStringPairs::kick(Runner &run)
	{
		pairs->releaseReference();
		return this + 1;
	}

	const Step *SinkReplaceStringPairs::pass(Runner &run, const Any *who)
	{
		const WhoUntypedOperation &what = this->what;
		const ClicheShort *cliche;
		const Any *const *dummy;
		what.callAttribute()->isNode(dummy, (const Cliche*&)cliche);
		const Any *argument = cliche->node(pairs);
		return (run.sink = this + 1)->call(run, what, argument, who);
	}

	const Step *SinkReplaceStringPairs::pass(Runner &run, const PilsString *value)
	{
		Traveller traveller(value, pairs);
		CountBag countBag;
		traveller.travel(countBag);
		PILS_CHAR *text = new PILS_CHAR[countBag.count];
		TextBag bag(text);
		traveller.travel(bag);
		value->releaseReference();
		pairs->releaseReference();
		const PilsString *result = PilsString::get(text, countBag.count);
		delete text;
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkReplaceBeginningStringPairs::pass(Runner &run, const PilsString *original)
	{
		const PilsString *result = NULL;
		for (size_t pair = 0; pair < (size_t)pairs->count->value;)
		{
			const PilsString &first = *(const PilsString *)pairs->element[pair++];
			const PilsString &second = *(const PilsString *)pairs->element[pair++];
			if (first.count->value <= original->count->value)
			{
				size_t i;
				for (i = 0; i < (size_t)first.count->value && original->value[i] == first.value[i]; i++);
				if (i == (size_t)first.count->value)
				{
					PILS_CHAR *text = new PILS_CHAR[original->count->value - first.count->value + second.count->value];
					PILS_CHAR *c = text;
					for (size_t j = 0; j < (size_t)second.count->value; j++) *c++ = second.value[j];
					for (; i < (size_t)original->count->value; i++) *c++ = original->value[i];
					result = PilsString::get(text, c - text);
					delete text;
					break;
				}
			}
		}
		if (result) original->releaseReference(); else result = original;
		pairs->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	const Step *SinkReplaceEndingStringPairs::pass(Runner &run, const PilsString *original)
	{
		const PilsString *result = NULL;
		for (size_t pair = 0; pair < (size_t)pairs->count->value;)
		{
			const PilsString &first = *(const PilsString *)pairs->element[pair++];
			const PilsString &second = *(const PilsString *)pairs->element[pair++];
			if (first.count->value <= original->count->value)
			{
				size_t i;
				for (i = 0; i < (size_t)first.count->value && original->value[original->count->value - first.count->value + i] == first.value[i]; i++);
				if (i == (size_t)first.count->value)
				{
					PILS_CHAR *text = new PILS_CHAR[original->count->value - first.count->value + second.count->value];
					PILS_CHAR *c = text;
					for (size_t j = 0; j < (size_t)original->count->value - i; j++) *c++ = original->value[j];
					for (i = 0; i < (size_t)second.count->value; i++) *c++ = second.value[i];
					result = PilsString::get(text, c - text);
					delete text;
					break;
				}
			}
		}
		if (result) original->releaseReference(); else result = original;
		pairs->releaseReference();
		return (run.sink = this + 1)->pass(run, result);
	}

	void SinkReplaceStringPairs::CountBag::put(const PILS_CHAR c)
	{
		count++;
	}

	void SinkReplaceStringPairs::CountBag::put(const PILS_CHAR *c, size_t count)
	{
		this->count += count;
	}

	void SinkReplaceStringPairs::TextBag::put(const PILS_CHAR c)
	{
		*text++ = c;
	}

	void SinkReplaceStringPairs::TextBag::put(const PILS_CHAR *c, size_t count)
	{
		for (size_t i = 0; i < count; i++)
			*text++ = *c++;
	}

	void SinkReplaceStringPairs::Traveller::travel(SinkReplaceStringPairs::Bag &bag) const
	{
		const PilsString *const *p = pairs;
		for (const PILS_CHAR *at = text; at < endText;)
		{
			if (p == endPairs)
			{
				bag.put(*at++);
				p = pairs;
			}
			else
			{
				const PilsString *search = *p++;
				const PilsString *replace = *p++;
				size_t searchCount = search->count->value;
				if (at + searchCount <= endText)
				{
					for (size_t i = 0; i < searchCount; i++)
					{
						if (search->value[i] != at[i])
						{
							replace = NULL;
							break;
						}
					}
					if (replace)
					{
						size_t replaceCount = replace->count->value;
						at += searchCount;
						bag.put(replace->value, replaceCount);
						p = pairs;
					}
				}
			}
		}
	}

#ifndef PILS_CHAR_IS_UTF16
	const PilsString *PilsString::get(const wchar_t *text, size_t count)
	{
		// UTF16 -> UTF8 conversion
		size_t bcount = count; //one byte per char
		for (size_t i = 0; i < count;)
		{
			unsigned int c = (unsigned int)text[i++];
			if (c < 0x80) continue;
			bcount++;
			if (c < 0x800) continue;
			bcount++;
			// surrogate test
			if ((c & 0xFC00) != 0xD800 || i == count || (text[i] & 0xFC00) != 0xDC00)
				continue;
			bcount++; i++;
		}
		PILS_CHAR *buffer = new PILS_CHAR[bcount];
		PILS_CHAR *w = buffer;
		for (size_t i = 0; i < count;)
		{
			unsigned int c = (unsigned int)text[i++];
			if (c < 0x80)
			{
				*w++ = (PILS_CHAR)c;
			}
			else if (c < 0x800)
			{
				*w++ = (PILS_CHAR)(0xC0 | c >> 6);
				*w++ = (PILS_CHAR)(0x80 | (c & 0x3F));
			}
			else if ((c & 0xFC00) != 0xD800 || i == count || (text[i] & 0xFC00) != 0xDC00)
			{
				*w++ = (PILS_CHAR)(0xE0 | c >> 12);
				*w++ = (PILS_CHAR)(0x80 | (c >> 6 & 0x3F));
				*w++ = (PILS_CHAR)(0x80 | (c & 0x3F));
			}
			else //surrogate
			{
				c += 0x40;
				c <<= 10;
				c |= text[i++] & 0x03FF;
				*w++ = (PILS_CHAR)(0xF0 | (c >> 18 & 0x03));
				*w++ = (PILS_CHAR)(0x80 | (c >> 12 & 0x3F));
				*w++ = (PILS_CHAR)(0x80 | (c >> 6 & 0x3F));
				*w++ = (PILS_CHAR)(0x80 | (c & 0x3F));
			}
		}
		const PilsString *result = PilsString::get((const PILS_CHAR*)buffer, bcount);
		delete buffer;
		return result;
	}
	const PilsString *PilsString::get(const wchar_t *text)
	{
		return get(text, wcslen(text));
	}

	bool PilsString::UTF32pass::pass(const PilsString &string)
	{
		const char *end = &string.value[string.count->value];
		for (const char *at = string.value; at < end;)
		{
			unsigned long c = *at++;
			if (c & 0x80)
			{
				unsigned int tailbytes = 0;
				unsigned long tailmask = 0x40;
				while (c & tailmask)
				{
					tailmask >>= 1;
					tailbytes++;
				}
				if (tailmask == 0||tailbytes == 0)
					return false; // bad multibyte start
				c &= tailmask - 1;
				while (tailbytes--)
				{
					if (at == end || (*at & 0xC0) != 0x80) return false; // bad multibyte tail
					c <<= 6;
					c |= *at++ & 0x3F;
				}
			}
			put(c);
		}
		return true;
	}
#endif
	bool PilsString::UTF16pass::put(unsigned long c)
	{
		if (c >= 0x10000)
			// Try to encode as surrogates
			return (c <= 0x10FFFF && put((unsigned short)(0xD800 - 0x40 + ((c >> 10) & 0x03FF)))) && put((unsigned short)((c & 0x03FF)| 0xDC00));
		//Delete the following line to accept surrogates
		else if (c >= 0xD800 && c < 0xE000) return false;
		else return put((unsigned short)c);
	}

	bool PilsString::UTF16count::put(unsigned short c)
	{
		count++;
		return true;
	}

	bool PilsString::UTF16write::put(unsigned short c)
	{
		*at++ = c;
		return true;
	}

	const CallWho *PropertyCharacterEncoding::callWho(const Any *who) const
	{
		return new (Heap::allocate(sizeof(WhoCharacterEncoding))) WhoCharacterEncoding(this, who);
	}

	const Step *WhoCharacterEncoding::step_(Runner &run) const
	{
		new (run.allocate(sizeof(PipeCharacterEncoder))) PipeCharacterEncoder(*this);
		return whoAttribute();
	}

	Sink *PipeCharacterEncoder::kick(Runner &run)
	{
		string.std::string::~string();
		return this + 1;
	}

	const Step *PipeCharacterEncoder::pass(Runner &run, const PilsString *value)
	{
		return pass(run, value, value->value, value->count->value);
	}

	const Step *PipeCharacterEncoder::pass(Runner &run, const Any *anchor, const PILS_CHAR *range, size_t count)
	{
		const CallWho &what = this->what;
		(run.sink = kick(run))->connectPipe(run);
		return new (run.allocate(sizeof(PipesourceCharacterDecoder))) PipesourceCharacterDecoder(what, anchor, range, range + count);
	}

	Sink *PipesourceCharacterDecoder::kick(Runner &run)
	{
		anchor->releaseReference();
		return this + 1;
	}

	const Step *PipesourceCharacterDecoder::step_(Runner &run) const
	{
		return ((PipesourceCharacterDecoder *)this)->step_(run);
	}

	const Step *PipesourceCharacterDecoder::step_(Runner &run)
	{
		if (at == end) return ((Pipe *)(run.sink = kick(run)))->pipeEnd(run);
		if (state)
		{
			long character = ((PropertyCharacterEncoding *)what.callAttribute())->get(at, end, state);
			if (state) return ((Pipe *)(this + 1))->pipeItem(run, Integer::get(character));
		}
		run.calling.what = &what;
		what.addReference();
		run.where_->addReference();
		return (run.sink = kick(run))->error(run, PilsString::get(at, end - at), &what, run.where_);
	}

	const Step *PipeCharacterEncoder::pipeItem(Runner &run, const Any *item)
	{
		if (item->convert(*this))
		{
			item->releaseReference();
			return (Pipesource*)(run.sink);
		}
		else
		{
			const Express &what = this->what;
			what.addReference();
			for (; run.sink != this + 1; run.sink = run.sink->kick(run));
			run.where_->addReference();
			return run.sink->error(run, item, &what, run.where_);
		}
	}

	const Step *PipeCharacterEncoder::pipeEnd(Runner &run)
	{
		size_t count = string.size();
		const PilsString *string = PilsString::get(count?&this->string[0]:NULL, count);
		return (run.sink = kick(run))->pass(run, string);
	}

	bool PipeCharacterEncoder::convert(const Integer &value)
	{
		return ((PropertyCharacterEncoding *)what.callAttribute())->put(string, value.value, state);
	}

	int PropertyBytes::initialState(const char *&at, const char *end) const
	{
		return 1;
	}

	long PropertyBytes::get(const char *&at, const char *end, int &state) const
	{
		return (unsigned char)*at++;
	}

	bool PropertyBytes::put(std::string &string, long code, int &state) const
	{
		char byte = (char)code;
		string.push_back(byte);
		return true;
	}

	int PropertyUtf_8::initialState(const char *&at, const char *end) const
	{
		return 1;
	}

	long PropertyUtf_8::get(const char *&at, const char *end, int &state) const
	{
		long c = (unsigned char)*at++;
		if (c < 0x80) return c;
		if (c < 0xC0 || c >= 0xF8) {state = 0; return c;}
		if (c < 0xE0 && at < end) return ((c & 0x1F) << 6) + (*at++ & 0x3F);
		if (c < 0xF0 && at + 1 < end)
		{
			c &= 0xF;
			c <<= 6;
			c += *at++ & 0x3F;
			c <<= 6;
			c += *at++ & 0x3F;
			return c;
		}
		if (at + 2 < end)
		{
			c &= 0x7;
			c <<= 6;
			c += *at++ & 0x3F;
			c <<= 6;
			c += *at++ & 0x3F;
			c <<= 6;
			c += *at++ & 0x3F;
			return c;
		}
		return false;
	}

	bool PropertyUtf_8::put(std::string &string, long code, int &state) const
	{
		if (code < 0) return false;
		if (code < 0x80)
		{
			char byte = (char)code;
			string.push_back(byte);
			return true;
		}
		for (int count = 0; count < 4; count++)
		{
			if (code >> (count * 5 + 6)) continue;
			string.push_back((char)((-1 << (7 - count)) + ((code >> count * 6) & 0x3F)));
			while (count--)
				string.push_back((char)(0x80 + ((code >> count * 6) & 0x3F)));
			return true;
		}
		return false;
	}

	int PropertyUtf_16::initialState(const char *&at, const char *end) const
	{
		if (end == at || (end - at) % 2 != 0)
		{
			return 0;
		}
		else if (at[0] == (char)(-1) && at[1] == (char)(-2))
		{
			at += 2;
			return 1;
		}
		else if (at[0] == (char)(-2) && at[1] == (char)(-1))
		{
			at += 2;
			return 2;
		}
		else
		{
			return 0;
		}
	}

	long PropertyUtf_16::get(const char *&at, const char *end, int &state) const
	{
		long c = get16bit(at, end, state);
		if ((c & 0xFC00) != 0xD800)
		{
			return c;
		}
		if (at != end)
		{
			unsigned long d = get16bit(at, end, state) ^ 0xDC00;
			if (d < 0x0400)
			{
				return (c << 10) | d;
			}
		}
		return state = 0;
	}

	bool PropertyUtf_16::put(std::string &string, long code, int &state) const
	{
		if (code < 0 || (code & 0xF800) == 0xD800 || code >= 0x110000)
			return false;
		if (code < 0x10000)
		{
			put16bit(string, code, state);
		}
		else
		{
			code -= 0x10000;
			put16bit(string, (code >> 10) | 0xD800, state);
			put16bit(string, (code & 0x03FF) | 0xDC00, state);
		}
		return true;
	}

	long PropertyUtf_16::get16bit(const char *&at, const char *end, int &state) const
	{
		int c[2];
		switch (state)
		{
		case 1:
			c[0] = (unsigned char)*at++;
			c[1] = (unsigned char)*at++;
			break;
		case 2:
			c[1] = (unsigned char)*at++;
			c[0] = (unsigned char)*at++;
			break;
		case 0:
			return 0;
		}
		return c[0] | (c[1] << 8);
	}

	void PropertyUtf_16::put16bit(std::string &string, long code, int &state) const
	{
		if (state == 0)
		{
			state = 1;
			string.push_back((char)0xFF);
			string.push_back((char)0xFE);
		}
		string.push_back((char)code);
		string.push_back((char)(code >> 8));
	}

	int PropertyUtf_16le::initialState(const char *&at, const char *end) const
	{
		if ((end - at) % 2 != 0)
		{
			return 0;
		}
		return 1;
	}


	long PropertyUtf_16le::get16bit(const char *&at, const char *end, int &state) const
	{
		unsigned char c0 = *at++;
		unsigned char c1 = *at++;
		return (long)c0 | (c1 << 8);
	}

	void PropertyUtf_16le::put16bit(std::string &string, long code, int &state) const
	{
		string.push_back((char)(code & 0xFF));
		string.push_back((char)(code >> 8));
	}

	int PropertyUtf_16be::initialState(const char *&at, const char *end) const
	{
		if ((end - at) % 2 != 0)
		{
			return 0;
		}
		return 2;
	}

	long PropertyUtf_16be::get16bit(const char *&at, const char *end, int &state) const
	{
		unsigned char c0 = *at++;
		unsigned char c1 = *at++;
		return (long)c1 | (c0 << 8);
	}

	void PropertyUtf_16be::put16bit(std::string &string, long code, int &state) const
	{
		string.push_back((char)(code >> 8));
		string.push_back((char)(code & 0xFF));
	}
}
