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
        void go(Compiling &compiling) override;
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
        void beginRule(const void *index) override;
        void ruleHead() override;
        void endRule(const void *index) override;
        void beginAssignRule(const void *index) override;
        void getAssignValue() override;
        void gotAssignValue() override;
        void endAssignRule(const void *index) override;
        void endIndex(bool more) override;
        void endAssignmentIndex(bool more);
        void rulePattern(const Any &pattern) override;
        void pattern(const Any &pattern) override;
        void pattern(const Slot &pattern) override;
        void pattern(const Slot &pattern, size_t offset) override;
        void pattern(const ListExpress &pattern) override;
        void pattern(const NodeExpress &pattern) override;
        void typecheckPlus() override;
        void typecheckCount() override;
        void typecheckInteger() override;
        void typecheckNumber() override;
        void typecheckString() override;
        void typecheckTimestamp() override;
        void typecheckPilsDate() override;
        void typecheckDuration() override;
        void typecheckPlusString() override;
        void typecheckPlusPlusString() override;
        void typecheckCliche() override;
        void typecheckList() override;
        void typecheckPlusList() override;
        void typecheckPlusPlusList() override;
        void typecheckNode() override;
        void typecheckLegs() override;
        void typecheckConstant() override;
        void typecheckLanguage() override;
        void typecheckListener() override;
        void typecheckColor() override;
        void check_(Converter &check_) override;
        void check_(Recognizer &check_) override;
        void check_(const SearchString &search) override;
        void check_(const SearchListConstant &search) override;
        void fetch(size_t offset) override;
        void fetchSpecialType() override;
        void pop() override;
        void fetchNodeHead() override;
        void fetchNodeAttribute(const Constant &name) override;
        void fetchNodeAttribute(const Constant &name, const Any &defaultValue) override;
        void fetchClicheName() override;
        void fetchClicheShortAttribute() override;
        void fetchStringCount() override;
        void fetchListCount() override;
        void fetchFileName() override;
        void fetchFolderName() override;
        void fetchWhen() override;
        void fetchListElement(const Integer &index) override;
        void fetchListElementReverse(const Integer &index) override;
        void verifyNodeAttributes(const Cliche &cliche) override;
        void verifyDefaultCliche(const Cliche &cliche) override;
        void clicheShortFetchHeadFetchAttribute() override;
        void fetchThroughCall(const NodeConstant &through) override;
        void fetchThroughTry(const NodeConstant &through) override;
        void compare(const BuiltinClicheCompare &compare, double value) override;
        void notEqual(const Any &value) override;
        void action(const Any &pattern) override;
        void action(const Ok &pattern) override;
        void action(const OkConstant &pattern) override;
        void implicitParameter(const Constant &name, ImplicitParameter::ImplicitCode code) override;
        void queryInterface(const InterfaceDesignator &designator) override;
        bool quote(const Any &value) override;
        bool fetch(const Constant &name) override;
        bool build(const ListExpress &list) override;
        bool build(const NodeExpressShort &node) override;
        bool build(const NodeExpressLong &node) override;
	protected:
        void done() override;
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

        void beginRule(const void *index) override;
        void ruleHead() override;
        void endRule(const void *index) override;
        void beginAssignRule(const void *index) override;
        void getAssignValue() override;
        void gotAssignValue() override;
        void endAssignRule(const void *index) override;
        void endIndex(bool more) override;
        void endAssignmentIndex(bool more);
        void rulePattern(const Any &pattern) override;
        void pattern(const Any &pattern) override;
        void pattern(const Slot &pattern) override;
        void pattern(const Slot &pattern, size_t offset) override;
        void pattern(const ListExpress &pattern) override;
        void pattern(const NodeExpress &pattern) override;
        void typecheckPlus() override;
        void typecheckCount() override;
        void typecheckInteger() override;
        void typecheckNumber() override;
        void typecheckString() override;
        void typecheckTimestamp() override;
        void typecheckPilsDate() override;
        void typecheckDuration() override;
        void typecheckPlusString() override;
        void typecheckPlusPlusString() override;
        void typecheckCliche() override;
        void typecheckList() override;
        void typecheckPlusList() override;
        void typecheckPlusPlusList() override;
        void typecheckNode() override;
        void typecheckLegs() override;
        void typecheckConstant() override;
        void typecheckLanguage() override;
        void typecheckListener() override;
        void typecheckColor() override;
        void check_(Converter &check_) override;
        void check_(Recognizer &check_) override;
        void check_(const SearchString &search) override;
        void check_(const SearchListConstant &search) override;
        void fetch(size_t offset) override;
        void fetchSpecialType() override;
        void pop() override;
        void fetchNodeHead() override;
        void fetchNodeAttribute(const Constant &name) override;
        void fetchNodeAttribute(const Constant &name, const Any &defaultValue) override;
        void fetchClicheName() override;
        void fetchClicheShortAttribute() override;
        void fetchStringCount() override;
        void fetchListCount() override;
        void fetchFileName() override;
        void fetchFolderName() override;
        void fetchWhen() override;
        void fetchListElement(const Integer &index) override;
        void fetchListElementReverse(const Integer &index) override;
        void verifyNodeAttributes(const Cliche &cliche) override;
        void verifyDefaultCliche(const Cliche &cliche) override;
        void clicheShortFetchHeadFetchAttribute() override;
        void fetchThroughCall(const NodeConstant &through) override;
        void fetchThroughTry(const NodeConstant &through) override;
        void compare(const BuiltinClicheCompare &compare, double value) override;
        void notEqual(const Any &value) override;
        void action(const Any &pattern) override;
        void action(const Ok &pattern) override;
        void action(const OkConstant &pattern) override;
        void implicitParameter(const Constant &name, ImplicitParameter::ImplicitCode code) override;
        void queryInterface(const InterfaceDesignator &designator) override;
        bool quote(const Any &value) override;
        bool fetch(const Constant &name) override;
        bool build(const ListExpress &list) override;
        bool build(const NodeExpressShort &node) override;
        bool build(const NodeExpressLong &node) override;
	protected:
        void done() override;
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
        bool convert(const ReallySpecial &special) override;
		static TypecheckingConverterIdentifier singleton;
	};
}
#endif
