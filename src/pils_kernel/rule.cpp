/* This file is public domain */
#include "statement.h"
#include "rule.h"
namespace PILS

{
	const Any* Rule::match() const
	{
		return element[0];
	}

	const Any* Rule::action() const
	{
		return element[1];
	}

	const Any *BuiltinClicheRule::node(const Any *const *element) const
	{
        return new const Rule(element);
	}

	const Rule *Rule::as_Rule() const
	{
		return this;
	}

    const NodeExpressShort* BuiltinClicheRuleset::node(const Express* element) const
    {
        const Any* const* rules;
        const Integer* count;

        if (!element->isList(rules, count))
            return PokerClicheShort::node(element);

        size_t n = (size_t)count->value;

        for (size_t i = 0; i < n; ++i)
        {
            if (rules[i]->as_Rule() == nullptr)
                return PokerClicheShort::node(element);
        }

        return new Ruleset(element, (const Rule* const*)rules, n);
    }

	const Ruleset *Ruleset::as_Ruleset() const
	{
		return this;
	}

	const Any *BuiltinClicheClosure::node(const Any *const *element) const
	{
		if (element[1]->as_Ruleset())
            return new const Closure(element);
        return BuiltinPokerClicheLong::node(element);
	}

	const Step *Ruleset::step_(Runner &run) const
	{
		retain();
		run.where_->retain();
        const Closure *closure = new const Closure(run.where_, this);
		return run.sink->pass(run, closure);
	}

	const Step *WhoUselineRuleset::step_(Runner &run) const
	{
		const Ruleset *ruleset = (const Ruleset *)((const NodeExpress*)callAttribute())->element[0];
		ruleset->retain();
		run.where_->retain();
		run.where_->retain();
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
        const Closure *closure = new const Closure(run.where_, ruleset);
        run.where_ = new const Using(run.where_, closure);
		return whoAttribute();
	}

	const Step *UseRuleset::step_(Runner &run) const
	{
		const Ruleset *ruleset = (Ruleset *)element[1];
		ruleset->retain();
		run.where_->retain();
		run.where_->retain();
		new (run.allocate(sizeof(SinkWhereabout))) SinkWhereabout(run.where_);
        const Closure *closure = new const Closure(run.where_, ruleset);
        run.where_ = new const Using(run.where_, closure);
		return element[0];
	}

    Ruleset::~Ruleset()
	{
		compiled.releaseFrom(*this);
    }

	Ruleset::Compilation::Compilation(const Rule *const *rules, size_t count)
		: assigning(nullptr), count(count), size(0)
	{
		cliche = new const Cliche *[count];
		RuleCompiler compiler(rules, count, *cliche);
		size_t assignSize = 0;
		CompilingPrescan(compiler, size, assignSize);
		calling = (const QuickCalling*)new char[size];
		if (assignSize) assigning = (QuickCalling*)((char*)calling + size - assignSize);
		if (assigning == calling) calling = nullptr;
		CompilingGenerate(compiler, (void*)calling, (void*)assigning);
	}

	void Ruleset::Compilation::releaseFrom(Ruleset &ruleset)
	{
		for (size_t i = 0; i < this->count; i++)
            Runner::main().release(cliche[i]); // TODO: get proper Runner
		delete [] cliche;
		delete [] (const char*)(calling?calling:assigning);
	}

	const Step *Closure::calling(Runner &run, const Constant &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = &call;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const Integer &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = &call;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const Empty &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		//const void *key = (void*)&call;
		const void *key = (const char*)call.count + 1;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const ListConstant &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = (const char*)call.count + 1;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const NodeConstant &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = (const char*)call.cliche + 1;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const ListExpress &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = (const char*)call.count + 1;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const NodeExpress &call) const
	{
		if (run.stackOverflow()) return run.callingStackOverflow();
		const void *key = (const char*)call.cliche + 1;
		run.calling.closure = this;
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.calling;
			code;
			code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *Closure::calling(Runner &run, const Any &call, const Any *assignValue) const
	{
		if (run.stackOverflow())
		{
            run.release(assignValue);
			return run.callingStackOverflow();
		}
		run.calling.closure = this;
		const void *key = call.callingIndex();
		for (const QuickCalling *code = ((Ruleset*)element[1])->compiled.assigning;
			code;
			code = code->quickCalling(run, call, *assignValue, key));
		return run.sink->called(run, call, assignValue);
	}

    bool Closure::convert(Converter &converter) const
    {
        return converter.convert(*this);
    }

    bool Converter::convert(const Closure &closure)
    {
        return false;
    }

    const Step *CatchConstant::pass(Runner &run, long dummy)
	{
		const Constant &call = this->call;
		const void *key = &call;
		run.sinkTagChain = chain;
        run.release(run.where_);
		run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchListConstant::pass(Runner &run, long dummy)
	{
		const ListConstant &call = this->call;
		const void *key = (const char*)call.count + 1;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchNodeConstant::pass(Runner &run, long dummy)
	{
		const NodeConstant &call = this->call;
		const void *key = (const char*)call.cliche + 1;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchEmpty::pass(Runner &run, long dummy)
	{
		const Empty &call = this->call;
		const void *key = (const char*)call.count + 1;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchListExpress::pass(Runner &run, long dummy)
	{
		const ListExpress &call = this->call;
		const void *key = (const char*)call.count + 1;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchNodeExpress::pass(Runner &run, long dummy)
	{
		const NodeExpress &call = this->call;
		const void *key = (const char*)call.cliche + 1;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		for (;code;code = code->quickCalling(run, call, key));
		return run.sink->called(run, call);
	}

	const Step *CatchAssign::pass(Runner &run, long dummy)
	{
		const Any &call = this->call;
		const Any *assignValue = this->assignValue;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		const QuickCalling *code = action.fail.target;
		run.sink = this + 1;
		const void *key = call.callingIndex();
		for (;code;code = code->quickCalling(run, call, *assignValue, key));
		return run.sink->called(run, call, assignValue);
	}

	const Step *CatchConstant::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const Constant &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchListConstant::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const ListConstant &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchNodeConstant::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const NodeConstant &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchEmpty::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const Empty &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchListExpress::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const ListExpress &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchNodeExpress::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const NodeExpress &call = this->call;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call);
	}

	const Step *CatchAssign::skip(Runner &run)
	{
		while (run.sink != this) run.sink = run.sink->kick(run);
		const Any &call = this->call;
		const Any *assignValue = this->assignValue;
		run.sinkTagChain = chain;
        run.release(run.where_);
        run.where_ = &where_;
		run.calling.closure = &closure;
		run.calling.who = &who;
		run.calling.what = &what;
		run.sink = this + 1;
		return run.sink->called(run, call, assignValue);
	}

	bool Ruleset::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.build(*this);
	}
}
