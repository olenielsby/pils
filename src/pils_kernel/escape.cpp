/* This file is public domain */
#include "escape.h"
namespace PILS
{
	const NodeExpressShort *EscapeCliche::node(const Express *element) const
	{
		return element->escape();
	}

	const Any *EscapeCliche::node(const Constant *element) const
	{
		return element->escape();
	}

	const Escape *Any::escape() const
	{
        return new const Escape(this);
	}

	const Step *Escape::step_(Runner &run) const
	{
		return element[0];
	}

	bool Escape::compileBuild(CompilingBuild &compiling) const
	{
		return element[0]->compileBuild(compiling);
	}

	const Step *Escape::calling(Runner &run, const Constant &call) const
	{
		return Any::calling(run, call);
	}

	const Step *Escape::calling(Runner &run, const Integer &call) const
	{
		return Any::calling(run, call);
	}

	const Step *Escape::calling(Runner &run, const ListConstant &call) const
	{
		return Any::calling(run, call);
	}

	const Step *Escape::calling(Runner &run, const NodeConstant &call) const
	{
		return Any::calling(run, call);
	}

	const Step *Escape::calling(Runner &run, const Empty &call) const
	{
		return Any::calling(run, call);
	}

	void Escape::compilePattern(Compiling &compiling) const
	{
		compiling.pattern(*element[0]);
	}

	const void *Escape::compilePatternIndex() const
	{
		const Cliche *cliche;
		const Any *const *dummy;
		return element[0]->isNode(dummy, cliche)?(const char *)cliche + 1:nullptr;
	}

	const Escape *NodeConstantShort::escape() const
	{
        return new const EscapeNodeConstantShort(this);
	}

	const Step *EscapeNodeConstantShort::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeConstantShort*)element[0])->NodeConstantShort::calling(run, call);
	}

	const Step *EscapeNodeConstantShort::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeConstantShort*)element[0])->NodeConstantShort::calling(run, call);
	}

	const Step *EscapeNodeConstantShort::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeConstantShort*)element[0])->NodeConstantShort::calling(run, call);
	}

	const Step *EscapeNodeConstantShort::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeConstantShort*)element[0])->NodeConstantShort::calling(run, call);
	}

	const Step *EscapeNodeConstantShort::calling(Runner &run, const Empty &call) const
	{
		return ((const NodeConstantShort*)element[0])->NodeConstantShort::calling(run, call);
	}

	void EscapeNodeConstantShort::compileNodecheckPattern(Compiling &compiling) const
	{
		element[0]->compileNodecheckPattern(compiling);
	}

	const Escape *NodeConstantLong::escape() const
	{
        return new const EscapeNodeConstantLong(this);
	}

	const Step *EscapeNodeConstantLong::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeConstantLong*)element[0])->NodeConstantLong::calling(run, call);
	}

	const Step *EscapeNodeConstantLong::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeConstantLong*)element[0])->NodeConstantLong::calling(run, call);
	}

	const Step *EscapeNodeConstantLong::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeConstantLong*)element[0])->NodeConstantLong::calling(run, call);
	}

	const Step *EscapeNodeConstantLong::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeConstantLong*)element[0])->NodeConstantLong::calling(run, call);
	}

	void EscapeNodeConstantLong::compileNodecheckPattern(Compiling &compiling) const
	{
		element[0]->compileNodecheckPattern(compiling);
	}

	const Escape *NodeConstantTrailer::escape() const
	{
        return new const EscapeNodeConstantTrailer(this);
	}

	const Step *EscapeNodeConstantTrailer::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeConstantTrailer*)element[0])->NodeConstantTrailer::calling(run, call);
	}

	const Step *EscapeNodeConstantTrailer::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeConstantTrailer*)element[0])->NodeConstantTrailer::calling(run, call);
	}

	const Step *EscapeNodeConstantTrailer::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeConstantTrailer*)element[0])->NodeConstantTrailer::calling(run, call);
	}

	const Step *EscapeNodeConstantTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeConstantTrailer*)element[0])->NodeConstantTrailer::calling(run, call);
	}

	const Step *EscapeNodeConstantTrailer::calling(Runner &run, const Empty &call) const
	{
		return ((const NodeConstantTrailer*)element[0])->element[0]->passUncounted(run);
	}

	const Escape *NodeExpressShort::escape() const
	{
        return new const EscapeNodeExpressShort(this);
	}

	const Step *EscapeNodeExpressShort::step_(Runner &run) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::step_(run);
	}

	const Step *EscapeNodeExpressShort::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::calling(run, call);
	}

	const Step *EscapeNodeExpressShort::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::calling(run, call);
	}

	const Step *EscapeNodeExpressShort::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::calling(run, call);
	}

	const Step *EscapeNodeExpressShort::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::calling(run, call);
	}

	const Step *EscapeNodeExpressShort::calling(Runner &run, const Empty &call) const
	{
		return ((const NodeExpressShort*)element[0])->NodeExpressShort::calling(run, call);
	}

	void EscapeNodeExpressShort::compilePattern(Compiling &compiling) const
	{
		const NodeExpressShort *node = (const NodeExpressShort*)element[0];
		compiling.pattern(*node);
		node->element[0]->compilePattern(compiling, 0);
	}

	void EscapeNodeExpressShort::compileNodecheckPattern(Compiling &compiling) const
	{
		const NodeExpressShort *node = (const NodeExpressShort*)element[0];
		compiling.fetchNodeHead();
		compiling.pattern(*node->cliche->head);
		compiling.pop();
		compiling.fetchNodeAttribute(*node->cliche->attributes[0]);
		node->element[0]->compilePattern(compiling);
		compiling.pop();
	}

	bool EscapeNodeExpressShort::compileBuild(CompilingBuild &compiling) const
	{
		const NodeExpressShort *node = (const NodeExpressShort*)element[0];
		return compiling.build(*node);
	}

	const Escape *NodeExpressLong::escape() const
	{
        return new const EscapeNodeExpressLong(this);
	}

	const Step *EscapeNodeExpressLong::step_(Runner &run) const
	{
		return ((const NodeExpressLong*)element[0])->NodeExpressLong::step_(run);
	}

	const Step *EscapeNodeExpressLong::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeExpressLong*)element[0])->NodeExpressLong::calling(run, call);
	}

	const Step *EscapeNodeExpressLong::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeExpressLong*)element[0])->NodeExpressLong::calling(run, call);
	}

	const Step *EscapeNodeExpressLong::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeExpressLong*)element[0])->NodeExpressLong::calling(run, call);
	}

	const Step *EscapeNodeExpressLong::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeExpressLong*)element[0])->NodeExpressLong::calling(run, call);
	}

	void EscapeNodeExpressLong::compilePattern(Compiling &compiling) const
	{
		const NodeExpressLong *node = (const NodeExpressLong*)element[0];
		compiling.pattern(*node);
		for (size_t i = 0; i < node->cliche->count; i++)
			node->element[i]->compilePattern(compiling, i);
	}

	void EscapeNodeExpressLong::compileNodecheckPattern(Compiling &compiling) const
	{
		const NodeExpressLong *node = (const NodeExpressLong*)element[0];
		compiling.fetchNodeHead();
		compiling.pattern(*node->cliche->head);
		compiling.pop();
		for (size_t i = 0; i < node->cliche->count; i++)
		{
			compiling.fetchNodeAttribute(*node->cliche->attributes[i]);
			node->element[i]->compilePattern(compiling);
			compiling.pop();
		}
	}

	bool EscapeNodeExpressLong::compileBuild(CompilingBuild &compiling) const
	{
		const NodeExpressLong *node = (const NodeExpressLong*)element[0];
		return compiling.build(*node);
	}

	const Escape *NodeExpressTrailer::escape() const
	{
        return new EscapeNodeExpressTrailer(this);
	}

	const Step *EscapeNodeExpressTrailer::calling(Runner &run, const Constant &call) const
	{
		return ((const NodeExpressTrailer*)element[0])->NodeExpressTrailer::calling(run, call);
	}

	const Step *EscapeNodeExpressTrailer::calling(Runner &run, const Integer &call) const
	{
		return ((const NodeExpressTrailer*)element[0])->NodeExpressTrailer::calling(run, call);
	}

	const Step *EscapeNodeExpressTrailer::calling(Runner &run, const ListConstant &call) const
	{
		return ((const NodeExpressTrailer*)element[0])->NodeExpressTrailer::calling(run, call);
	}

	const Step *EscapeNodeExpressTrailer::calling(Runner &run, const NodeConstant &call) const
	{
		return ((const NodeExpressTrailer*)element[0])->NodeExpressTrailer::calling(run, call);
	}

	const Step *EscapeNodeExpressTrailer::calling(Runner &run, const Empty &call) const
	{
		return ((const NodeExpressTrailer*)element[0])->element[0]->passUncounted(run);
	}





}
