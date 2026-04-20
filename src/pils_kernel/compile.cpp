/* This file is public domain */
#include "compile.h"
#include "statement.h"

namespace PILS
{
	void Any::compileRulePattern(Compiling &compiling, const Rule &rule) const
	{
		const void *key = compilePatternIndex();
		compiling.beginRule(key);
		compiling.ruleHead();
		compilePattern(compiling);
		rule.action()->compileAction(compiling);
		compiling.endRule(key);
	}

	void WhoAssignShort::compileRulePattern(Compiling &compiling, const Rule &rule) const
	{
		const Any *assignPattern = ((const NodeExpress*)callAttribute())->element[0];
		const void *key = whoAttribute()->compilePatternIndex();
		compiling.beginAssignRule(key);
		compiling.ruleHead();
		whoAttribute()->compilePattern(compiling);
		compiling.getAssignValue();
		assignPattern->compilePattern(compiling);
		compiling.gotAssignValue();
		rule.action()->compileAction(compiling);
		compiling.endAssignRule(key);
	}

    const void *Constant::compilePatternIndex() const
	{
		return this;
	}

    const void *Constant::callingIndex() const
	{
		return this;
	}

	const void *NodeConstant::compilePatternIndex() const
	{
		return (const char *)cliche + 1;
	}

	const void *NodeConstant::callingIndex() const
	{
		return (const char *)cliche + 1;
	}

	const void *NodeExpress::compilePatternIndex() const
	{
        return (cliche->head != &Empty::singleton)?(const char *)cliche + 1:nullptr;
	}

	const void *NodeExpress::callingIndex() const
	{
		return (const char *)cliche + 1;
	}

	const void *CallWho::compilePatternIndex() const
	{
        return nullptr;
	}

	const void *ListConstant::compilePatternIndex() const
	{
		return (const char *)count + 1;
	}

	const void *ListConstant::callingIndex() const
	{
		return (const char *)count + 1;
	}

	const void *ListExpress::compilePatternIndex() const
	{
		return (const char *)count + 1;
	}

	const void *ListExpress::callingIndex() const
	{
		return (const char *)count + 1;
	}

	const void *Slot::compilePatternIndex() const
	{
        return nullptr;
	}

    void Any::compilePattern(Compiling &compiling) const
	{
		compiling.pattern(*this);
	}

	void Any::compilePattern(Compiling &compiling, size_t offset) const
	{
		compiling.fetch(offset);
		compilePattern(compiling);
		compiling.pop();
	}

    void Constant::compilePattern(Compiling &compiling) const
	{
		compiling.pattern(*this);
	}

	void NodeExpressShort::compilePattern(Compiling &compiling) const
	{
		if (cliche->head == &Empty::singleton)
			compiling.verifyNodeAttributes(*cliche);
		else
			compiling.pattern(*this);
		element[0]->compilePattern(compiling, 0);
	}

	void NodeExpressLong::compilePattern(Compiling &compiling) const
	{
		if (cliche->head == &Empty::singleton)
			compiling.verifyNodeAttributes(*cliche);
		else
			compiling.pattern(*this);
		for (size_t i = 0; i < cliche->count; i++)
			element[i]->compilePattern(compiling, i);
	}

	void ListExpress::compilePattern(Compiling &compiling) const
	{
		compiling.pattern(*this);
		for (size_t i = 0; i < (size_t)count->value; i++)
			element[i]->compilePattern(compiling, i);
	}

	void Slot::compilePattern(Compiling &compiling) const
	{
		compiling.pattern(*this);
	}

	void Slot::compilePattern(Compiling &compiling, size_t offset) const
	{
		compiling.pattern(*this, offset);
	}

	void EmptySlot::compilePattern(Compiling &compiling) const
	{
		// No code generation
	}

	void EmptySlot::compilePattern(Compiling &compiling, size_t offset) const
	{
		// No code generation
	}

	void CallWho::compilePattern(Compiling &compiling) const
	{
		callAttribute()->compileTypecheck(compiling, *this);
	}

	void Any::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		((const NodeExpressLong&)pattern).NodeExpressLong::compilePattern(compiling);
	}

	void NodeConstant::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		const Any *const *whoElement;
		const Cliche *whoCliche;
		if (cliche->head == &Builtin::name.call)
		{
			compiling.fetchThroughCall(*this);
			pattern.whoAttribute()->compilePattern(compiling);
			compiling.pop();
		}
		else if (cliche->head == &Builtin::name.try_)
		{
			compiling.fetchThroughTry(*this);
			pattern.whoAttribute()->compilePattern(compiling);
			compiling.pop();
		}
		else if (cliche->head == &Builtin::name.anyway && pattern.whoAttribute()->isNode(whoElement, whoCliche))
		{
			if (whoCliche == &BuiltinClicheCallWho::singleton && whoElement[0] == &Builtin::name.times && whoElement[1]->isNode(whoElement, whoCliche));
			else compiling.verifyDefaultCliche(*whoCliche);
			for (size_t i = 0; i < whoCliche->count; i++)
			{
                const Any *defaultValue = nullptr;
				for (size_t j = 0; j < cliche->count; j++)
				{
					if (cliche->attributes[j] == whoCliche->attributes[i])
					{
						defaultValue = element[j];
						break;
					}
				}
				if (defaultValue)
					compiling.fetchNodeAttribute(*whoCliche->attributes[i], *defaultValue);
				else
					compiling.fetchNodeAttribute(*whoCliche->attributes[i]);
				whoElement[i]->compilePattern(compiling);
				compiling.pop();
			}
		}
		else ((const NodeExpressLong&)pattern).NodeExpressLong::compilePattern(compiling);
	}

	void BuiltinClicheTrial::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		if (element.as_Constant())
		{
			compiling.fetchThroughTry((NodeConstant &)*pattern.callAttribute());
			pattern.whoAttribute()->compilePattern(compiling);
			compiling.pop();
			return;
		}
		ClicheTiny::compileTinyTypecheck(compiling, pattern, element);
	}

	void BuiltinClicheCalling::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		if (element.as_Constant())
		{
			compiling.fetchThroughCall((NodeConstant &)*pattern.callAttribute());
			pattern.whoAttribute()->compilePattern(compiling);
			compiling.pop();
			return;
		}
		ClicheTiny::compileTinyTypecheck(compiling, pattern, element);
	}

	void BuiltinClicheAnyway::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		const Any *const *whoElement;
		const Cliche *whoCliche;
		const Constant *e = element.as_Constant();
		if (e && pattern.whoAttribute()->isNode(whoElement, whoCliche))
		{
			if (whoCliche == &BuiltinClicheCallWho::singleton && whoElement[0] == &Builtin::name.times && whoElement[1]->isNode(whoElement, whoCliche));
			else compiling.verifyDefaultCliche(*whoCliche);
			for (size_t i = 0; i < whoCliche->count; i++)
			{
                const Any *defaultValue = nullptr;
				if (attributes[0] == whoCliche->attributes[i])
				{
					defaultValue = &element;
				}
				if (defaultValue)
					compiling.fetchNodeAttribute(*whoCliche->attributes[i], *defaultValue);
				else
					compiling.fetchNodeAttribute(*whoCliche->attributes[i]);
				whoElement[i]->compilePattern(compiling);
				compiling.pop();
			}
		}
		else ClicheTiny::compileTinyTypecheck(compiling, pattern, element);
	}

	void TypecheckPlus::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPlus();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPropertyCount::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckCount();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckInteger::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckInteger();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckNumber::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckNumber();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckString::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckString();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckTimestamp::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckTimestamp();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPilsDate::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPilsDate();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckDuration::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckDuration();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPlusString::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPlusString();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPlusPlusString::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPlusPlusString();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckList::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckList();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPlusList::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPlusList();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckPlusPlusList::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckPlusPlusList();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckCliche::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckCliche();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckNode::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		pattern.whoAttribute()->compileNodecheckPattern(compiling);
	}

	void TypecheckPropertyLegs::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckLegs();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckColor::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckColor();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void NodeConstantTiny::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		((ClicheTiny *)cliche)->compileTinyTypecheck(compiling, pattern, *element[0]);
	}

	void NodeExpressTiny::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		((ClicheTiny *)cliche)->compileTinyTypecheck(compiling, pattern, *element[0]);
	}
	
	void ClicheTiny::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		((const NodeExpressLong&)pattern).NodeExpressLong::compilePattern(compiling);
	}

	void BuiltinClicheOperationTimes::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchNodeHead();
		pattern.whoAttribute()->compilePattern(compiling);
		compiling.pop();
		element.compileNodecheckPattern(compiling);
	}

	void BuiltinClicheMakeName::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchClicheShortAttribute();
		element.compilePattern(compiling);
		compiling.pop();
		compiling.fetchClicheName();
		pattern.whoAttribute()->compilePattern(compiling);
		compiling.pop();
	}

	void BuiltinClicheTinyDollar::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchStringCount();
		element.compilePattern(compiling);
		compiling.pop();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void BuiltinClicheConcatenate::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchListCount();
		element.compilePattern(compiling);
		compiling.pop();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void BuiltinClicheCompare::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		class Numeric : public Converter
		{
		public:
			bool convert(const Integer &value) {this->value = value.value; return true;}
			bool convert(const Float &value) {this->value = value.value; return true;}
			double value;
		};
		Numeric numeric;
		const Any *other;
		const BuiltinClicheCompare *cliche;
		if (element.convert(numeric))
		{
			other = pattern.whoAttribute();
			cliche = &opposite();
		}
		else if (pattern.whoAttribute()->convert(numeric))
		{
			other = &element;
			cliche = this;
		}
		else return ClicheTiny::compileTinyTypecheck(compiling, pattern, element);
		compiling.compare(*cliche, numeric.value);
		other->compilePattern(compiling);
	}

	void BuiltinClicheOperationNotEqual::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.notEqual(element);
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void JumperHead::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchNodeHead();
		pattern.whoAttribute()->compilePattern(compiling);
		compiling.pop();
		compiling.verifyNodeAttributes(*this);
		element.compilePattern(compiling, 0);
	}

	void BuiltinClicheFileName::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchFileName();
		element.compilePattern(compiling);
		compiling.pop();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void BuiltinClicheFolderName::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchFolderName();
		element.compilePattern(compiling);
		compiling.pop();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void BuiltinClicheWhen::compileTinyTypecheck(Compiling &compiling, const CallWho &pattern, const Any &element) const
	{
		compiling.fetchWhen();
		element.compilePattern(compiling);
		compiling.pop();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void NodeExpress::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		if (cliche->head == &Empty::singleton)
		{
			compiling.fetchNodeHead();
			pattern.whoAttribute()->compilePattern(compiling);
			compiling.pop();
			compiling.verifyNodeAttributes(*cliche);
			for (size_t offset = 0; offset < cliche->count; offset++)
				element[offset]->compilePattern(compiling, offset);
		}
		else Any::compileTypecheck(compiling, pattern);
	}

	void Integer::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		if (value > 0)
			compiling.fetchListElement(*this);
		else
			compiling.fetchListElementReverse(*this);
		pattern.whoAttribute()->compilePattern(compiling);
		compiling.pop();
	}

	void Any::compileNodecheckPattern(Compiling &compiling) const
	{
		compiling.typecheckNode();
		compilePattern(compiling);
	}

	void PokerShort::compileNodecheckPattern(Compiling &compiling) const
	{
		compiling.typecheckNode();
		compilePattern(compiling);
	}

	void PokerLong::compileNodecheckPattern(Compiling &compiling) const
	{
		compiling.typecheckNode();
		compilePattern(compiling);
	}

	void PokerTrailer::compileNodecheckPattern(Compiling &compiling) const
	{
		compiling.typecheckNode();
		compilePattern(compiling);
	}

	void NodeConstant::compileNodecheckPattern(Compiling &compiling) const
	{
		compiling.fetchNodeHead();
		compiling.pattern(*cliche->head);
		compiling.pop();
		for (size_t i = 0; i < cliche->count; i++)
		{
			compiling.fetchNodeAttribute(*cliche->attributes[i]);
			element[i]->compilePattern(compiling);
			compiling.pop();
		}
	}

	void NodeExpress::compileNodecheckPattern(Compiling &compiling) const
	{
		if (cliche->head != &Empty::singleton)
		{
			compiling.fetchNodeHead();
			compiling.pattern(*cliche->head);
			compiling.pop();
		}
		for (size_t i = 0; i < cliche->count; i++)
		{
			compiling.fetchNodeAttribute(*cliche->attributes[i]);
			element[i]->compilePattern(compiling);
			compiling.pop();
		}
	}

	void TypecheckConstant::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckConstant();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void TypecheckLanguage::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.typecheckLanguage();
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void SearchString::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.check_(*this);
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void SearchListConstant::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.check_(*this);
		pattern.whoAttribute()->compilePattern(compiling);
	}

	void Any::compileAction(Compiling &compiling) const
	{
		compiling.action(*this);
	}

	void Ok::compileAction(Compiling &compiling) const
	{
		compiling.action(*this);
	}

	void OkConstant::compileAction(Compiling &compiling) const
	{
		compiling.action(*this);
	}

	void ImplicitParameterShort::compileAction(Compiling &compiling) const
	{
		const Constant *name = cliche->attributes[0];
		compiling.implicitParameter(*name, ((const ImplicitParameter::ImplicitClicheShort*)cliche)->code);
		element[0]->compileAction(compiling);
	}

	void ImplicitParameterTrailer::compileAction(Compiling &compiling) const
	{
		const Constant *tag = (const Constant*)element[1];
		tag->retain();
		cliche->attributes[1]->retain();
		const ClicheTiny * tagCliche = cliche->attributes[1]->clichefy();
		const Constant *name = tagCliche->node(tag)->as_Constant();
		compiling.implicitParameter(*name, ((const ImplicitParameter::ImplicitClicheTrailer*)cliche)->code);
		tagCliche->unduplicateReference();
		name->unduplicateReference();
		element[0]->compileAction(compiling);
	}

	void RuleCompiler::go(Compiling &compiling)
	{
		for(size_t i = count; i--; compiling.clicheIterator++)
		{
			rules[i]->match()->compileRulePattern(compiling, *rules[i]);
		}
		compiling.done();
	}

	void CompilingPrescan::beginRule(const void *ruleIndex)
	{
		clicheHeadEmptyIfBuildable = &JumperHead::singleton;
        names.insert(names.begin(), Empty::get());
		if (ruleIndex)
		{
			if (!index.count(ruleIndex))
			{
				index.insert(ruleIndex);
			}
		}
		else
		{
			if (index.size())
			{
				endIndex(true);
			}
		}
	}

	void CompilingGenerate::beginRule(const void *ruleIndex)
	{
		resolveChain(unindexedFailChain, (QuickCalling*)code);
		if (ruleIndex)
		{
			if (!indexing)
				indexing = new (allocate(sizeof(QuickIndex))) QuickIndex();
		}
		else
		{
			if (indexing)
				endIndex(true);
		}
        currentFailChain = nullptr;
		currentRule = (const QuickCalling*)code;
		slotSet.resize((*clicheIterator)->count - 1);
		slotAnchor = &(*clicheIterator)->attributes[1];
	}

	void CompilingPrescan::endRule(const void *ruleIndex)
	{
		size_t count = names.size();
		clicheHeadEmptyIfBuildable->retain();
		if (count == 1)
			*clicheIterator = clicheHeadEmptyIfBuildable->clichefy(*names.begin());
		else
			*clicheIterator = clicheHeadEmptyIfBuildable->clichefy(&*names.begin(), count);
		names.clear();
	}

	void CompilingGenerate::endRule(const void *ruleIndex)
	{
		slotSet.clear();
		if (indexing)
		{
			std::pair<std::map<const void*,IndexEntry>::iterator, bool> entry =
				index.insert(std::pair<const void*,IndexEntry>(ruleIndex, IndexEntry(currentRule, currentFailChain)));
			if (!entry.second)
			{
				resolveChain(entry.first->second.failChain, currentRule);
				entry.first->second.failChain = currentFailChain;
			}
		}
		else unindexedFailChain = currentFailChain;
        currentFailChain = nullptr;
	}

	void CompilingPrescan::ruleHead()
	{
		size += sizeof(QuickBeginRule);
	}

	void CompilingGenerate::ruleHead()
	{
		currentRule = new (allocate(sizeof(QuickBeginRule))) QuickBeginRule(**clicheIterator);
	}

	void CompilingPrescan::endIndex(bool more)
	{
		size_t count = index.size();
		if (count)
		{
			size += sizeof(QuickIndex) + count * (sizeof(void*) + sizeof(QuickCalling*)) + sizeof(QuickCalling*);
			index.clear();
		}
	}

	void CompilingGenerate::endIndex(bool more)
	{
		if (indexing)
		{
			size_t count = index.size();
			void **putEntry = (void**)code;
			void **putKey = putEntry + count;
			code = putKey + count + 1;
            const QuickCalling *nextRule = (const QuickCalling*)(more ? code : nullptr);
			for (std::map<const void*, IndexEntry>::iterator get = index.begin(); get != index.end(); get++)
			{
				*(putKey++) = (void*)get->first;
				*(putEntry++) = (void*)get->second.firstEntry;
				resolveChain(get->second.failChain, nextRule);
			}
			*putKey = (void*)nextRule;
			indexing->begin = putEntry;
			indexing->end = putKey;
            indexing = nullptr;
			index.clear();
		}
	}

	void CompilingPrescan::endAssignmentIndex(bool more)
	{
		size_t count = assignmentIndex.size();
		if (count)
		{
			size += sizeof(QuickIndex) + count * (sizeof(void*) + sizeof(QuickCalling*)) + sizeof(QuickCalling*);
			assignmentIndex.clear();
		}
	}

	void CompilingGenerate::endAssignmentIndex(bool more)
	{
		if (assignmentIndexing)
		{
			size_t count = assignmentIndex.size();
			void **putEntry = (void**)code;
			void **putKey = putEntry + count;
			code = putKey + count + 1;
            const QuickCalling *nextRule = (const QuickCalling*)(more ? code : nullptr);
			for (std::map<const void*, IndexEntry>::iterator get = assignmentIndex.begin(); get != assignmentIndex.end(); get++)
			{
				*(putKey++) = (void*)get->first;
				*(putEntry++) = (void*)get->second.firstEntry;
				resolveChain(get->second.failChain, nextRule);
			}
			*putKey = (void*)nextRule;
			assignmentIndexing->begin = putEntry;
			assignmentIndexing->end = putKey;
            assignmentIndexing = nullptr;
			assignmentIndex.clear();
		}
	}

	void *CompilingGenerate::allocate(size_t size)
	{
		char* block = (char*)code;
		code = block + size;
		return block;
	}

	void CompilingPrescan::rulePattern(const Any &p)
	{
		pattern(p);
	}

	void CompilingGenerate::rulePattern(const Any &p)
	{
		pattern(p);
	}

	void CompilingPrescan::beginAssignRule(const void *ruleIndex)
	{
		clicheHeadEmptyIfBuildable = &JumperHead::singleton;
        names.insert(names.begin(), Empty::get());
		assignSize -= size;
		if (ruleIndex)
		{
			if (!assignmentIndex.count(ruleIndex))
			{
				assignmentIndex.insert(ruleIndex);
			}
		}
		else
		{
			if (assignmentIndex.size())
			{
				endAssignmentIndex(true);
			}
		}
	}

	void CompilingGenerate::beginAssignRule(const void *ruleIndex)
	{
		void *temp = code;
		code = assignCode;
		assignCode = temp;
		resolveChain(unindexedAssignmentFailChain, (QuickCalling*)code);
		if (ruleIndex)
		{
			if (!assignmentIndexing)
				assignmentIndexing = new (allocate(sizeof(QuickIndex))) QuickIndex();
		}
		else
		{
			if (assignmentIndexing)
				endAssignmentIndex(true);
		}
		currentRule = (const QuickCalling*)code;
		slotSet.resize((*clicheIterator)->count - 1);
		slotAnchor = &(*clicheIterator)->attributes[0]; //make room for assignValue
	}

	void CompilingPrescan::endAssignRule(const void *index)
	{
		assignSize += size;
		size_t count = names.size();
		clicheHeadEmptyIfBuildable->retain();
		if (count == 1)
			*clicheIterator = clicheHeadEmptyIfBuildable->clichefy(*names.begin());
		else
			*clicheIterator = clicheHeadEmptyIfBuildable->clichefy(&*names.begin(), count);
		names.clear();
	}

	void CompilingGenerate::endAssignRule(const void *ruleIndex)
	{
		slotSet.clear();
		if (assignmentIndexing)
		{
			std::pair<std::map<const void*,IndexEntry>::iterator, bool> entry =
				assignmentIndex.insert(std::pair<const void*,IndexEntry>(ruleIndex, IndexEntry(currentRule, currentFailChain)));
			if (!entry.second)
			{
				resolveChain(entry.first->second.failChain, currentRule);
				entry.first->second.failChain = currentFailChain;
			}
		}
		else unindexedAssignmentFailChain = currentFailChain;
        currentFailChain = nullptr;
		void *temp = code;
		code = assignCode;
		assignCode = temp;
	}

	void CompilingPrescan::getAssignValue()
	{
		size += sizeof(QuickPop);
	}

	void CompilingGenerate::getAssignValue()
	{
		new (allocate(sizeof(QuickPop))) QuickPop();
		slotAnchor++;
	}

	void CompilingPrescan::gotAssignValue()
	{}

	void CompilingGenerate::gotAssignValue()
	{}

	void CompilingPrescan::fetch(size_t offset)
	{
		size += sizeof(QuickFetch);
	}

	void CompilingGenerate::fetch(size_t offset)
	{
		new (allocate(sizeof(QuickFetch))) QuickFetch(offset);
		slotAnchor--;
	}

	void CompilingPrescan::pop()
	{
		size += sizeof(QuickPop);
	}

	void CompilingGenerate::pop()
	{
		slotAnchor++;
		new (allocate(sizeof(QuickPop))) QuickPop();
	}

	void CompilingPrescan::pattern(const Any &p)
	{
		size += sizeof(QuickMatchLiteral);
	}

	void CompilingGenerate::pattern(const Any &p)
	{
		new (allocate(sizeof(QuickMatchLiteral))) QuickMatchLiteral(currentFailChain, p);
	}

	void CompilingPrescan::pattern(const Slot &slot)
	{
		const Constant *name = (const Constant*)slot.element[0];
		std::vector<const Constant*>::iterator at = std::lower_bound(names.begin() + 1, names.end(), name);
		if (at == names.end() || *at != name)
		{
			names.insert(at, name);
			size += sizeof(QuickStore);
			name->retain();
		}
		else size += sizeof(QuickIdentical);
	}

	void CompilingGenerate::pattern(const Slot &p)
	{
		const Constant *name = (const Constant*)p.element[0];
		const Constant *const *begin = (*clicheIterator)->attributes;
		const Constant *const *end = begin + (*clicheIterator)->count;
		begin++;
		const Constant *const *at = std::lower_bound(begin, end, name);
		size_t slotIndex = at - begin;
		size_t slotOffset = (const char*)at - (const char*)slotAnchor;
		if (slotSet[slotIndex])
		{
			new (allocate(sizeof(QuickIdentical)))
			QuickIdentical(currentFailChain, slotOffset);
		}
		else
		{
			new (allocate(sizeof(QuickStore)))
			QuickStore(slotOffset);
			slotSet[slotIndex] = true;
		}
	}

	void CompilingPrescan::pattern(const Slot &p, size_t offset)
	{
		const Constant *name = (const Constant*)p.element[0];
		std::vector<const Constant*>::iterator at = std::lower_bound(names.begin() + 1, names.end(), name);
		if (at == names.end() || *at != name)
		{
			names.insert(at, name);
			size += sizeof(QuickOffsetStore);
			name->retain();
		}
		else size += sizeof(QuickOffsetIdentical);
	}

	void CompilingGenerate::pattern(const Slot &p, size_t offset)
	{
		const Constant *name = (const Constant*)p.element[0];
		const Constant *const *begin = (*clicheIterator)->attributes;
		const Constant *const *end = begin + (*clicheIterator)->count;
		begin++;
		const Constant*const *at = std::lower_bound(begin, end, name);
		size_t slotIndex = at - begin;
		size_t slotOffset = (const char*)at - (const char*)slotAnchor;
		if (slotSet[slotIndex])
		{
			new (allocate(sizeof(QuickOffsetIdentical)))
			QuickOffsetIdentical(currentFailChain, offset, slotOffset);
		}
		else
		{
			new (allocate(sizeof(QuickOffsetStore)))
			QuickOffsetStore(offset, slotOffset);
			slotSet[slotIndex] = true;
		}
	}

	void CompilingPrescan::pattern(const ListExpress &p)
	{
		size += sizeof(QuickMatchListCountOrNodeCliche);
	}

	void CompilingGenerate::pattern(const ListExpress &p)
	{
		new (allocate(sizeof(QuickMatchListCountOrNodeCliche)))
			QuickMatchListCountOrNodeCliche(currentFailChain, *p.count);
	}

	void CompilingPrescan::pattern(const NodeExpress &p)
	{
		size += sizeof(QuickMatchListCountOrNodeCliche);
	}

	void CompilingGenerate::pattern(const NodeExpress &p)
	{
		new (allocate(sizeof(QuickMatchListCountOrNodeCliche)))
			QuickMatchListCountOrNodeCliche(currentFailChain, *p.cliche);
	}

	void CompilingPrescan::typecheckPlus()
	{
		size += sizeof(QuickTestPlus);
	}

	void CompilingGenerate::typecheckPlus()
	{
		new (allocate(sizeof(QuickTestPlus))) QuickTestPlus(currentFailChain);
	}

	void CompilingPrescan::typecheckCount()
	{
		size += sizeof(QuickTestCount);
	}

	void CompilingGenerate::typecheckCount()
	{
		new (allocate(sizeof(QuickTestCount))) QuickTestCount(currentFailChain);
	}

	void CompilingPrescan::typecheckInteger()
	{
		size += sizeof(QuickTestInteger);
	}

	void CompilingGenerate::typecheckInteger()
	{
		new (allocate(sizeof(QuickTestInteger))) QuickTestInteger(currentFailChain);
	}

	void CompilingPrescan::typecheckNumber()
	{
		size += sizeof(QuickTestNumber);
	}

	void CompilingGenerate::typecheckNumber()
	{
		new (allocate(sizeof(QuickTestNumber))) QuickTestNumber(currentFailChain);
	}

	void CompilingPrescan::typecheckString()
	{
		size += sizeof(QuickTestString);
	}

	void CompilingGenerate::typecheckString()
	{
		new (allocate(sizeof(QuickTestString))) QuickTestString(currentFailChain);
	}

	void CompilingPrescan::typecheckTimestamp()
	{
		size += sizeof(QuickTestTimestamp);
	}

	void CompilingGenerate::typecheckTimestamp()
	{
		new (allocate(sizeof(QuickTestTimestamp))) QuickTestTimestamp(currentFailChain);
	}

	void CompilingPrescan::typecheckPilsDate()
	{
		size += sizeof(QuickTestPilsDate);
	}

	void CompilingGenerate::typecheckPilsDate()
	{
		new (allocate(sizeof(QuickTestPilsDate))) QuickTestPilsDate(currentFailChain);
	}

	void CompilingPrescan::typecheckDuration()
	{
		size += sizeof(QuickTestDuration);
	}

	void CompilingGenerate::typecheckDuration()
	{
		new (allocate(sizeof(QuickTestDuration))) QuickTestDuration(currentFailChain);
	}

	void CompilingPrescan::typecheckPlusString()
	{
		size += sizeof(QuickTestPlusString);
	}

	void CompilingGenerate::typecheckPlusString()
	{
		new (allocate(sizeof(QuickTestPlusString))) QuickTestPlusString(currentFailChain);
	}

	void CompilingPrescan::typecheckPlusPlusString()
	{
		size += sizeof(QuickTestPlusPlusString);
	}

	void CompilingGenerate::typecheckPlusPlusString()
	{
		new (allocate(sizeof(QuickTestPlusPlusString))) QuickTestPlusPlusString(currentFailChain);
	}

	void CompilingPrescan::typecheckNode()
	{
		size += sizeof(QuickTestNode);
	}

	void CompilingGenerate::typecheckNode()
	{
		new (allocate(sizeof(QuickTestNode))) QuickTestNode(currentFailChain);
	}

	void CompilingPrescan::typecheckLegs()
	{
		size += sizeof(QuickTestLegs);
	}

	void CompilingGenerate::typecheckLegs()
	{
		new (allocate(sizeof(QuickTestLegs))) QuickTestLegs(currentFailChain);
	}

	void CompilingPrescan::typecheckConstant()
	{
		size += sizeof(QuickTestConstant);
	}

	void CompilingGenerate::typecheckConstant()
	{
		new (allocate(sizeof(QuickTestConstant))) QuickTestConstant(currentFailChain);
	}

	void CompilingPrescan::typecheckLanguage()
	{
		size += sizeof(QuickTestLanguage);
	}

	void CompilingGenerate::typecheckLanguage()
	{
		new (allocate(sizeof(QuickTestLanguage))) QuickTestLanguage(currentFailChain);
	}

	void CompilingPrescan::typecheckColor()
	{
		size += sizeof(QuickTestPilsColor);
	}

	void CompilingGenerate::typecheckColor()
	{
		new (allocate(sizeof(QuickTestPilsColor))) QuickTestPilsColor(currentFailChain);
	}

	void CompilingPrescan::typecheckList()
	{
		size += sizeof(QuickTestList);
	}

	void CompilingGenerate::typecheckList()
	{
		new (allocate(sizeof(QuickTestList))) QuickTestList(currentFailChain);
	}

	void CompilingPrescan::typecheckPlusList()
	{
		size += sizeof(QuickTestPlusList);
	}

	void CompilingGenerate::typecheckPlusList()
	{
		new (allocate(sizeof(QuickTestPlusList))) QuickTestPlusList(currentFailChain);
	}

	void CompilingPrescan::typecheckPlusPlusList()
	{
		size += sizeof(QuickTestPlusPlusList);
	}

	void CompilingGenerate::typecheckPlusPlusList()
	{
		new (allocate(sizeof(QuickTestPlusPlusList))) QuickTestPlusPlusList(currentFailChain);
	}

	void CompilingPrescan::typecheckCliche()
	{
		size += sizeof(QuickTestCliche);
	}

	void CompilingGenerate::typecheckCliche()
	{
		new (allocate(sizeof(QuickTestCliche))) QuickTestCliche(currentFailChain);
	}

	void CompilingPrescan::check_(Converter &check)
	{
		size += sizeof(QuickTestSpecialTypecheck);
	}

	void CompilingGenerate::check_(Converter &check)
	{
		new (allocate(sizeof(QuickTestSpecialTypecheck))) QuickTestSpecialTypecheck(currentFailChain, check);
	}

	void CompilingPrescan::check_(Recognizer &check)
	{
		size += sizeof(QuickTestRecognizerTypecheck);
	}

	void CompilingGenerate::check_(Recognizer &check)
	{
		new (allocate(sizeof(QuickTestRecognizerTypecheck))) QuickTestRecognizerTypecheck(currentFailChain, check);
	}

	void CompilingPrescan::check_(const SearchString &search)
	{
		size += sizeof(QuickTestSearchString);
	}

	void CompilingGenerate::check_(const SearchString &search)
	{
		new (allocate(sizeof(QuickTestSearchString))) QuickTestSearchString(currentFailChain, search);
	}

	void CompilingPrescan::check_(const SearchListConstant &search)
	{
		size += sizeof(QuickTestSearchListConstant);
	}

	void CompilingGenerate::check_(const SearchListConstant &search)
	{
		new (allocate(sizeof(QuickTestSearchListConstant))) QuickTestSearchListConstant(currentFailChain, search);
	}

	void CompilingPrescan::fetchNodeHead()
	{
		size += sizeof(QuickFetchNodeHead);
	}

	void CompilingGenerate::fetchNodeHead()
	{
		new (allocate(sizeof(QuickFetchNodeHead))) QuickFetchNodeHead(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchNodeAttribute(const Constant &name)
	{
		size += sizeof(QuickFetchNodeAttribute);
	}

	void CompilingGenerate::fetchNodeAttribute(const Constant &name)
	{
		new (allocate(sizeof(QuickFetchNodeAttribute))) QuickFetchNodeAttribute(currentFailChain, name);
		slotAnchor--;
	}

	void CompilingPrescan::fetchNodeAttribute(const Constant &name, const Any &defaultValue)
	{
		size += sizeof(QuickFetchNodeAttributeDefault);
	}

	void CompilingGenerate::fetchNodeAttribute(const Constant &name, const Any &defaultValue)
	{
		new (allocate(sizeof(QuickFetchNodeAttributeDefault))) QuickFetchNodeAttributeDefault(currentFailChain, name, defaultValue);
		slotAnchor--;
	}

	void CompilingPrescan::fetchClicheName()
	{
		size += sizeof(QuickFetchClicheName);
	}

	void CompilingGenerate::fetchClicheName()
	{
		new (allocate(sizeof(QuickFetchClicheName))) QuickFetchClicheName(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchClicheShortAttribute()
	{
		size += sizeof(QuickFetchClicheShortAttribute);
	}

	void CompilingGenerate::fetchClicheShortAttribute()
	{
		new (allocate(sizeof(QuickFetchClicheShortAttribute))) QuickFetchClicheShortAttribute(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchStringCount()
	{
		size += sizeof(QuickFetchStringCount);
	}

	void CompilingGenerate::fetchStringCount()
	{
		new (allocate(sizeof(QuickFetchStringCount))) QuickFetchStringCount(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchListCount()
	{
		size += sizeof(QuickFetchListCount);
	}

	void CompilingGenerate::fetchListCount()
	{
		new (allocate(sizeof(QuickFetchListCount))) QuickFetchListCount(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchFileName()
	{
		size += sizeof(QuickFetchFileName);
	}

	void CompilingGenerate::fetchFileName()
	{
		new (allocate(sizeof(QuickFetchFileName))) QuickFetchFileName(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchFolderName()
	{
		size += sizeof(QuickFetchFolderName);
	}

	void CompilingGenerate::fetchFolderName()
	{
		new (allocate(sizeof(QuickFetchFolderName))) QuickFetchFolderName(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchWhen()
	{
		size += sizeof(QuickFetchWhen);
	}

	void CompilingGenerate::fetchWhen()
	{
		new (allocate(sizeof(QuickFetchWhen))) QuickFetchWhen(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::fetchListElement(const Integer &index)
	{
		size += sizeof(QuickFetchListElement);
	}

	void CompilingGenerate::fetchListElement(const Integer &index)
	{
		new (allocate(sizeof(QuickFetchListElement))) QuickFetchListElement(currentFailChain, index);
		slotAnchor--;
	}

	void CompilingPrescan::fetchListElementReverse(const Integer &index)
	{
		size += sizeof(QuickFetchListElementReverse);
	}

	void CompilingGenerate::fetchListElementReverse(const Integer &index)
	{
		new (allocate(sizeof(QuickFetchListElementReverse))) QuickFetchListElementReverse(currentFailChain, index);
		slotAnchor--;
	}

	void CompilingPrescan::verifyNodeAttributes(const Cliche &cliche)
	{
		size += sizeof(QuickVerifyNodeAttributes);
	}

	void CompilingGenerate::verifyNodeAttributes(const Cliche &cliche)
	{
		new (allocate(sizeof(QuickVerifyNodeAttributes))) QuickVerifyNodeAttributes(currentFailChain, cliche);
	}

	void CompilingPrescan::verifyDefaultCliche(const Cliche &cliche)
	{
		size += sizeof(QuickVerifyDefaultCliche);
	}

	void CompilingGenerate::verifyDefaultCliche(const Cliche &cliche)
	{
		new (allocate(sizeof(QuickVerifyDefaultCliche))) QuickVerifyDefaultCliche(currentFailChain, cliche);
	}

	void CompilingPrescan::clicheShortFetchHeadFetchAttribute()
	{
		size += sizeof(QuickClicheShortFetchHeadFetchAttribute);
	}

	void CompilingGenerate::clicheShortFetchHeadFetchAttribute()
	{
		new (allocate(sizeof(QuickClicheShortFetchHeadFetchAttribute))) QuickClicheShortFetchHeadFetchAttribute(currentFailChain);
		slotAnchor--;
		slotAnchor--;
	}

	void CompilingPrescan::fetchThroughCall(const NodeConstant &through)
	{
		size += sizeof(QuickFetchThroughCall);
	}

	void CompilingGenerate::fetchThroughCall(const NodeConstant &through)
	{
		new (allocate(sizeof(QuickFetchThroughCall))) QuickFetchThroughCall(currentFailChain, through);
		slotAnchor--;
	}

	void CompilingPrescan::fetchThroughTry(const NodeConstant &through)
	{
		size += sizeof(QuickFetchThroughTry);
	}

	void CompilingGenerate::fetchThroughTry(const NodeConstant &through)
	{
		new (allocate(sizeof(QuickFetchThroughTry))) QuickFetchThroughTry(currentFailChain, through);
		slotAnchor--;
	}

	void CompilingPrescan::compare(const BuiltinClicheCompare &cliche, double value)
	{
		size += sizeof(QuickCompareDouble);
	}

	void CompilingGenerate::compare(const BuiltinClicheCompare &cliche, double value)
	{
		new (allocate(sizeof(QuickCompareDouble))) QuickCompareDouble(currentFailChain, cliche, value);
	}

	void CompilingPrescan::notEqual(const Any &p)
	{
		size += sizeof(QuickMatchNotEqual);
	}

	void CompilingGenerate::notEqual(const Any &p)
	{
		new (allocate(sizeof(QuickMatchNotEqual))) QuickMatchNotEqual(currentFailChain, p);
	}


	void CompilingPrescan::fetchSpecialType()
	{
		size += sizeof(QuickFetchSpecialType);
	}

	void CompilingGenerate::fetchSpecialType()
	{
		new (allocate(sizeof(QuickFetchSpecialType))) QuickFetchSpecialType(currentFailChain);
		slotAnchor--;
	}

	void CompilingPrescan::queryInterface(const InterfaceDesignator &designator)
	{
		size += sizeof(QuickMatchQueryInterface);
	}

	void CompilingGenerate::queryInterface(const InterfaceDesignator &designator)
	{
		new (allocate(sizeof(QuickMatchQueryInterface))) QuickMatchQueryInterface(currentFailChain, designator);
		slotAnchor--;
	}

	void CompilingPrescan::action(const Any &thing)
	{
		size += sizeof(QuickActionAny);
	}

	void CompilingGenerate::action(const Any &thing)
	{
		new (allocate(sizeof(QuickActionAny)))
			QuickActionAny(**clicheIterator, thing, currentFailChain);
	}

	void CompilingPrescan::action(const Ok &statement)
	{
		if (const Slot *slot = statement.element[0]->as_Slot())
		{
			if (std::binary_search(names.begin() + 1, names.end(), (const Constant *)slot->element[0]))
			{
				size += sizeof(QuickActionOkArgument);
				return;
			}
		}
		size_t backup = size;
		if (statement.element[0]->compileBuild(*this))
		{
			clicheHeadEmptyIfBuildable = &Empty::singleton;
			size += sizeof(QuickBuilt);
		}
		else size = backup + sizeof(QuickActionOk);
	}

	void CompilingGenerate::action(const Ok &statement)
	{
		const Any &tail = *statement.element[0];
		const Cliche &cliche = **clicheIterator;
		if (const Slot *slot = tail.as_Slot())
		{
			const Constant *const *const end = &cliche.attributes[cliche.count];
			const Constant *const *at = std::lower_bound(&cliche.attributes[1], end, (const Constant *)slot->element[0]);
			if (at != end && *at == (const Constant *)slot->element[0])
			{
				new (allocate(sizeof(QuickActionOkArgument))) QuickActionOkArgument((const char *)at - (const char *)end);
				return;
			}
		}
		if (cliche.head == &Empty::singleton)
		{
			statement.element[0]->compileBuild(*this);
			new (allocate(sizeof(QuickBuilt))) QuickBuilt;
		}
		else new (allocate(sizeof(QuickActionOk))) QuickActionOk(**clicheIterator, tail);
	}

	void CompilingPrescan::action(const OkConstant &statement)
	{
		size += sizeof(QuickActionOkConstant);
	}

	void CompilingGenerate::action(const OkConstant &statement)
	{
		new (allocate(sizeof(QuickActionOkConstant)))
			QuickActionOkConstant(*(const Constant*)statement.element[0]);
	}

	void CompilingPrescan::implicitParameter(const Constant &name, const ImplicitParameter::ImplicitCode code)
	{
		std::vector<const Constant*>::iterator at = std::lower_bound(names.begin() + 1, names.end(), &name);
		if (at == names.end() || *at != &name)
		{
			names.insert(at, &name);
			name.retain();
		}
		size += sizeof(QuickImplicitWho);
	}

	void CompilingGenerate::implicitParameter(const Constant &name, const ImplicitParameter::ImplicitCode code)
	{
		const Constant *const *at = std::lower_bound((*clicheIterator)->attributes + 1, (*clicheIterator)->attributes + (*clicheIterator)->count, &name);
		size_t slotOffset = (const char*)at - (const char*)slotAnchor;
		void *d = allocate(sizeof(QuickImplicitWho));
		switch (code)
		{
		case ImplicitParameter::WHO:
			new (d) QuickImplicitWho(slotOffset);
			break;
		case ImplicitParameter::WHERE:
			new (d) QuickImplicitWhere(slotOffset);
			break;
		case ImplicitParameter::WHAT:
			new (d) QuickImplicitWhat(slotOffset);
			break;
		case ImplicitParameter::SELF:
			new (d) QuickImplicitSelf(slotOffset);
			break;
		}
	}

	void CompilingPrescan::done()
	{
		if (index.size())
				endIndex(false);
		if (assignmentIndex.size())
		{
			assignSize -= size;
			endAssignmentIndex(false);
			assignSize += size;
		}
	}

	void CompilingGenerate::done()
	{
		if (indexing)
			endIndex(false);
		if (assignmentIndexing)
		{
			void *temp = code;
			code = assignCode;
			endAssignmentIndex(false);
			assignCode = code;
			code = temp;
		}
        else resolveChain(unindexedFailChain, nullptr);
        resolveChain(unindexedAssignmentFailChain, nullptr);
	}

	void CompilingGenerate::resolveChain(const QuickCalling::Link *&chain, const QuickCalling *target)
	{
		while(chain)
		{
			const QuickCalling::Link *next = chain->next;
			((QuickCalling::Link *&)chain)->target = target;
			chain = next;
		}
	}

	bool CompilingPrescan::quote(const Any &value)
	{
		size += sizeof(QuickBuildQuote);
		return true;
	}

	bool CompilingGenerate::quote(const Any &value)
	{
		new (allocate(sizeof(QuickBuildQuote))) QuickBuildQuote(value);
		slotAnchor--;
		return true;
	}

	bool CompilingPrescan::fetch(const Constant &name)
	{
		if (std::binary_search(names.begin() + 1, names.end(), &name))
		{
			size += sizeof(QuickBuildFetch);
			return true;
		}
		else return false;
	}

	bool CompilingGenerate::fetch(const Constant &name)
	{
		const Constant *const *begin = (*clicheIterator)->attributes;
		const Constant *const *end = begin + (*clicheIterator)->count;
		begin++;
		const Constant *const *at = std::lower_bound(begin, end, &name);
		new (allocate(sizeof(QuickBuildFetch))) QuickBuildFetch((const char*)at - (const char*)(slotAnchor--));
		return true;
	}

	bool CompilingPrescan::build(const ListExpress &list)
	{
		for (long i = 0; i < list.count->value; i++)
			if (!list.element[i]->compileBuild(*this)) return false;
		size += sizeof(QuickBuildList);
		return true;
	}

	bool CompilingGenerate::build(const ListExpress &list)
	{
		for (long i = list.count->value-1; i >= 0; i--)
			list.element[i]->compileBuild(*this);
		new (allocate(sizeof(QuickBuildList))) QuickBuildList(list.count->value);
		slotAnchor += list.count->value-1;
		return true;
	}

	bool CompilingPrescan::build(const NodeExpressShort &node)
	{
		if (!node.element[0]->compileBuild(*this)) return false;
		size += sizeof(QuickBuildNodeShort);
		return true;
	}

	bool CompilingGenerate::build(const NodeExpressShort &node)
	{
		node.element[0]->compileBuild(*this);
		new (allocate(sizeof(QuickBuildNodeShort))) QuickBuildNodeShort(*(const ClicheShort *)node.cliche);
		return true;
	}

	bool CompilingPrescan::build(const NodeExpressLong &node)
	{
		for (size_t i = 0; i < node.cliche->count; i++)
			if (!node.element[i]->compileBuild(*this)) return false;
		size += sizeof(QuickBuildNodeLong);
		return true;
	}

	bool CompilingGenerate::build(const NodeExpressLong &node)
	{
		for (long i = node.cliche->count-1; i >= 0; i--)
			node.element[i]->compileBuild(*this);
		new (allocate(sizeof(QuickBuildNodeLong))) QuickBuildNodeLong(*(const ClicheLong *)node.cliche);
		slotAnchor += node.cliche->count-1;
		return true;
	}

    bool Constant::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.quote(*this);
	}

	bool Quote::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.quote(*element[0]);
	}

	bool Slot::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.fetch(*(const Constant *)element[0]);
	}

	bool NodeExpressShort::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.build(*this);
	}

	bool NodeExpressLong::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.build(*this);
	}

	bool ListExpress::compileBuild(CompilingBuild &compiling) const
	{
		return compiling.build(*this);
	}

    bool PokerShort::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}

	bool PokerLong::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}

	bool PokerTrailer::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}

	bool EmptySlot::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}

	bool Bind::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}

	bool Jumper0::compileBuild(CompilingBuild &compiling) const
	{
		return false;
	}	

	bool Comment::compileBuild(CompilingBuild &compiling) const
	{
		return element[0]->compileBuild(compiling);
	}

	TypecheckingConverterIdentifier TypecheckingConverterIdentifier::singleton;

	void TypecheckIdentifier::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		compiling.check_(TypecheckingConverterIdentifier::singleton);
		pattern.whoAttribute()->compilePattern(compiling);
	}
}
