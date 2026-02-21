/* This file is public domain */
#ifndef DEFINE_PILS_COMPILE_H
#define DEFINE_PILS_COMPILE_H

#include "quickstep.h"

namespace PILS
{
	class Compiling;

	class Compiler
	{
	public:
		Compiler (const Cliche *&firstCliche)
			: firstCliche(firstCliche)
		{}
		const Cliche *&firstCliche;
		virtual void go(Compiling &compiling) = 0;
	};

	class RuleCompiler
		: public Compiler
	{
	public:
		RuleCompiler (const Rule *const *rules, size_t count, const Cliche *&firstCliche)
			: Compiler(firstCliche), rules(rules), count(count)
		{}
		const Rule *const *rules;
		size_t count;
		void go(Compiling &compiling);
	};

	class CompilingBuild
	{
	public:
		virtual bool quote(const Any &value) = 0;
		virtual bool fetch(const Constant &name) = 0;
		virtual bool build(const ListExpress &list) = 0;
		virtual bool build(const NodeExpressShort &node) = 0;
		virtual bool build(const NodeExpressLong &node) = 0;
	};

	class Compiling : protected CompilingBuild
	{
	public:
        virtual ~Compiling() {}
		virtual void rulePattern(const Any &pattern) = 0;
		virtual void beginRule(const void *index) = 0;
		virtual void ruleHead() = 0;
		virtual void endRule(const void *index) = 0;
		virtual void beginAssignRule(const void *index) = 0;
		virtual void getAssignValue() = 0;
		virtual void gotAssignValue() = 0;
		virtual void endAssignRule(const void *index) = 0;
		virtual void pattern(const Any &pattern) = 0;
		virtual void pattern(const Slot &pattern) = 0;
		virtual void pattern(const Slot &pattern, size_t offset) = 0;
		virtual void pattern(const ListExpress &pattern) = 0;
		virtual void pattern(const NodeExpress &pattern) = 0;
		virtual void typecheckPlus() = 0;
		virtual void typecheckCount() = 0;
		virtual void typecheckInteger() = 0;
		virtual void typecheckNumber() = 0;
		virtual void typecheckString() = 0;
		virtual void typecheckTimestamp() = 0;
		virtual void typecheckPilsDate() = 0;
		virtual void typecheckDuration() = 0;
		virtual void typecheckPlusString() = 0;
		virtual void typecheckPlusPlusString() = 0;
		virtual void typecheckCliche() = 0;
		virtual void typecheckList() = 0;
		virtual void typecheckPlusList() = 0;
		virtual void typecheckPlusPlusList() = 0;
		virtual void typecheckNode() = 0;
		virtual void typecheckLegs() = 0;
		virtual void typecheckConstant() = 0;
		virtual void typecheckLanguage() = 0;
		virtual void typecheckListener() = 0;
		virtual void typecheckColor() = 0;
		virtual void check_(Converter &check_) = 0;
		virtual void check_(Recognizer &check_) = 0;
		virtual void check_(const SearchString &search) = 0;
		virtual void check_(const SearchListConstant &search) = 0;
		virtual void action(const Any &pattern) = 0;
		virtual void action(const Ok &pattern) = 0;
		virtual void action(const OkConstant &pattern) = 0;
		virtual void fetch(size_t offset) = 0;
		virtual void fetchSpecialType() = 0;
		virtual void pop() = 0;
		virtual void fetchNodeHead() = 0;
		virtual void fetchNodeAttribute(const Constant &name) = 0;
		virtual void fetchNodeAttribute(const Constant &name, const Any &defaultValue) = 0;
		virtual void fetchClicheName() = 0;
		virtual void fetchClicheShortAttribute() = 0;
		virtual void fetchStringCount() = 0;
		virtual void fetchListCount() = 0;
		virtual void fetchFileName() = 0;
		virtual void fetchFolderName() = 0;
		virtual void fetchWhen() = 0;
		virtual void fetchListElement(const Integer &index) = 0;
		virtual void fetchListElementReverse(const Integer &index) = 0;
		virtual void verifyNodeAttributes(const Cliche &cliche) = 0;
		virtual void verifyDefaultCliche(const Cliche &cliche) = 0;
		virtual void clicheShortFetchHeadFetchAttribute() = 0;
		virtual void fetchThroughCall(const NodeConstant &through) = 0;
		virtual void fetchThroughTry(const NodeConstant &through) = 0;
		virtual void compare(const BuiltinClicheCompare &compare, double value) = 0;
		virtual void notEqual(const Any &value) = 0;
		virtual void endIndex(bool more) = 0;
		virtual void implicitParameter(const Constant &name, ImplicitParameter::ImplicitCode code) = 0;
		virtual void queryInterface(const InterfaceDesignator &designator) = 0;
		const Cliche **clicheIterator;
		virtual void done() = 0;
	protected:
		Compiling(Compiler &compiler)
			: clicheIterator(&compiler.firstCliche), compiler(compiler)
		{}
		Compiler &compiler;
	};

	class CompilingPrescan
		: Compiling
	{
	public:
		CompilingPrescan(Compiler &compiler, size_t &size, size_t &assignSize)
			: Compiling(compiler), size(size), assignSize(assignSize)
		{
			compiler.go(*this);
		}
		void beginRule(const void *index);
		void ruleHead();
		void endRule(const void *index);
		void beginAssignRule(const void *index);
		void getAssignValue();
		void gotAssignValue();
		void endAssignRule(const void *index);
		void endIndex(bool more);
		void endAssignmentIndex(bool more);
		void rulePattern(const Any &pattern);
		void pattern(const Any &pattern);
		void pattern(const Slot &pattern);
		void pattern(const Slot &pattern, size_t offset);
		void pattern(const ListExpress &pattern);
		void pattern(const NodeExpress &pattern);
		void typecheckPlus();
		void typecheckCount();
		void typecheckInteger();
		void typecheckNumber();
		void typecheckString();
		void typecheckTimestamp();
		void typecheckPilsDate();
		void typecheckDuration();
		void typecheckPlusString();
		void typecheckPlusPlusString();
		void typecheckCliche();
		void typecheckList();
		void typecheckPlusList();
		void typecheckPlusPlusList();
		void typecheckNode();
		void typecheckLegs();
		void typecheckConstant();
		void typecheckLanguage();
		void typecheckListener();
		void typecheckColor();
		void check_(Converter &check_);
		void check_(Recognizer &check_);
		void check_(const SearchString &search);
		void check_(const SearchListConstant &search);
		void fetch(size_t offset);
		void fetchSpecialType();
		void pop();
		void fetchNodeHead();
		void fetchNodeAttribute(const Constant &name);
		void fetchNodeAttribute(const Constant &name, const Any &defaultValue);
		void fetchClicheName();
		void fetchClicheShortAttribute();
		void fetchStringCount();
		void fetchListCount();
		void fetchFileName();
		void fetchFolderName();
		void fetchWhen();
		void fetchListElement(const Integer &index);
		void fetchListElementReverse(const Integer &index);
		void verifyNodeAttributes(const Cliche &cliche);
		void verifyDefaultCliche(const Cliche &cliche);
		void clicheShortFetchHeadFetchAttribute();
		void fetchThroughCall(const NodeConstant &through);
		void fetchThroughTry(const NodeConstant &through);
		void compare(const BuiltinClicheCompare &compare, double value);
		void notEqual(const Any &value);
		void action(const Any &pattern);
		void action(const Ok &pattern);
		void action(const OkConstant &pattern);
		void implicitParameter(const Constant &name, ImplicitParameter::ImplicitCode code);
		void queryInterface(const InterfaceDesignator &designator);
		bool quote(const Any &value);
		bool fetch(const Constant &name);
		bool build(const ListExpress &list);
		bool build(const NodeExpressShort &node);
		bool build(const NodeExpressLong &node);
	protected:
		void done();
	private:
		size_t &size;
		size_t &assignSize;
		std::vector<const Constant*> names;
		std::set<const void*> index;
		std::set<const void*> assignmentIndex;
		const Constant *clicheHeadEmptyIfBuildable;
	};

	class CompilingGenerate
		: Compiling
	{
	public:
		CompilingGenerate(Compiler &compiler, void *code, void *assignCode)
			: Compiling(compiler),
			  code(code),
			  assignCode(assignCode),
			  indexing(NULL),
			  assignmentIndexing(NULL),
			  currentFailChain(NULL),
			  unindexedFailChain(NULL),
			  unindexedAssignmentFailChain(NULL)
		{
			compiler.go(*this);
		}

		void beginRule(const void *index);
		void ruleHead();
		void endRule(const void *index);
		void beginAssignRule(const void *index);
		void getAssignValue();
		void gotAssignValue();
		void endAssignRule(const void *index);
		void endIndex(bool more);
		void endAssignmentIndex(bool more);
		void rulePattern(const Any &pattern);
		void pattern(const Any &pattern);
		void pattern(const Slot &pattern);
		void pattern(const Slot &pattern, size_t offset);
		void pattern(const ListExpress &pattern);
		void pattern(const NodeExpress &pattern);
		void typecheckPlus();
		void typecheckCount();
		void typecheckInteger();
		void typecheckNumber();
		void typecheckString();
		void typecheckTimestamp();
		void typecheckPilsDate();
		void typecheckDuration();
		void typecheckPlusString();
		void typecheckPlusPlusString();
		void typecheckCliche();
		void typecheckList();
		void typecheckPlusList();
		void typecheckPlusPlusList();
		void typecheckNode();
		void typecheckLegs();
		void typecheckConstant();
		void typecheckLanguage();
		void typecheckListener();
		void typecheckColor();
		void check_(Converter &check_);
		void check_(Recognizer &check_);
		void check_(const SearchString &search);
		void check_(const SearchListConstant &search);
		void fetch(size_t offset);
		void fetchSpecialType();
		void pop();
		void fetchNodeHead();
		void fetchNodeAttribute(const Constant &name);
		void fetchNodeAttribute(const Constant &name, const Any &defaultValue);
		void fetchClicheName();
		void fetchClicheShortAttribute();
		void fetchStringCount();
		void fetchListCount();
		void fetchFileName();
		void fetchFolderName();
		void fetchWhen();
		void fetchListElement(const Integer &index);
		void fetchListElementReverse(const Integer &index);
		void verifyNodeAttributes(const Cliche &cliche);
		void verifyDefaultCliche(const Cliche &cliche);
		void clicheShortFetchHeadFetchAttribute();
		void fetchThroughCall(const NodeConstant &through);
		void fetchThroughTry(const NodeConstant &through);
		void compare(const BuiltinClicheCompare &compare, double value);
		void notEqual(const Any &value);
		void action(const Any &pattern);
		void action(const Ok &pattern);
		void action(const OkConstant &pattern);
		void implicitParameter(const Constant &name, ImplicitParameter::ImplicitCode code);
		void queryInterface(const InterfaceDesignator &designator);
		bool quote(const Any &value);
		bool fetch(const Constant &name);
		bool build(const ListExpress &list);
		bool build(const NodeExpressShort &node);
		bool build(const NodeExpressLong &node);
	protected:
		void done();
	private:
		struct IndexEntry
		{
			IndexEntry(const QuickCalling *firstEntry, const QuickCalling::Link *failChain)
				: firstEntry(firstEntry), failChain(failChain)
			{}
			const QuickCalling *firstEntry;
			const QuickCalling::Link *failChain;
		};
		void *code;
		void *assignCode;
		const Constant *const *slotAnchor;
		const QuickCalling *currentRule;
		QuickIndex *indexing;
		QuickIndex *assignmentIndexing;
		const QuickCalling::Link *currentFailChain;
		const QuickCalling::Link *unindexedFailChain;
		const QuickCalling::Link *unindexedAssignmentFailChain;
		std::map<const void*, IndexEntry> index;
		std::map<const void*, IndexEntry> assignmentIndex;
		std::vector<bool> slotSet;
		void *allocate(size_t size);
		static void resolveChain(const QuickCalling::Link *&chain, const QuickCalling *target);
	};

	class TypecheckingConverterSpecial
		: protected Converter
	{
	protected:
		TypecheckingConverterSpecial(){}

	};

	class TypecheckingConverterIdentifier
		: TypecheckingConverterSpecial
	{
	private:
		TypecheckingConverterIdentifier(){}
		friend class TypecheckIdentifier;
		bool convert(const ReallySpecial &special);
		static TypecheckingConverterIdentifier singleton;
	};
}
#endif
