/* This file is public domain */
#ifndef _PILS_INITIALIZERS_H_
#define _PILS_INITIALIZERS_H_
#include "numeric.h"

namespace PILS
{
    Mutex Mutex::singleMutex;
	long ShortInteger::initial = 0;
	const ShortInteger HashedConstant::hashTable[0x10000];
	const Empty Empty::singleton;
	const JumperHead JumperHead::singleton;
	const PilsString *const Namespace::standard = PilsString::get("pils.org/ns/sne");
	Converter Converter::dummy;
	const Builtin Builtin::name;

	double abs(double n);
	double round(double n);
	double truncate(double n);

	Builtin::Builtin()
		:
		start(_PS("start")),
		end(_PS("end")),
		error(_PS("error")),
		call(_PS("call")),
		recall(_PS("recall")),
		who(_PS("who")),
		when(_PS("when")),
		rule(_PS("rule")),
		tag(_PS("tag")),
		name_(_PS("name")),
		value(_PS("value")),
		match(_PS("match")),
		action(_PS("action")),
		if_(_PS("if")),
		else_(_PS("else")),
		and_(_PS("and")),
		or_(_PS("or")),
		anyway(_PS("anyway")),
		not_(_PS("not")),
		count_(_PS("count")),
		counts(_PS("counts")),
		stack(_PS("stack")),
		read(_PS("read")),
		parse(_PS("parse")),
		write(_PS("write")),
		traceread(_PS("traceread")),
		indent(_PS("indent")),
		where_(_PS("where")),
		useline(_PS("===")),
		what(_PS("what")),
		self(_PS("self")),
		ruleset(_PS("ruleset")),
		year(_PS("year")),
		month(_PS("month")),
		weekday(_PS("weekday")),
		day(_PS("day")),
		hour(_PS("hour")),
		minute(_PS("minute")),
		second(_PS("second")),
		millisecond(_PS("millisecond")),
		language(_PS("language")),
		plus(_PS("+")),
		minus(_PS("-")),
		times(_PS("*")),
		divide(_PS("/")),
		integerDivide(_PS("\\")),
		modulo(_PS("%")),
		round_("round", round),
		truncate_("truncate", truncate),
		abs_("abs", abs),
		equal(_PS("=")),
		notEqual(_PS("<>")),
		less(_PS("<")),
		lessEqual(_PS("<=")),
		greater(_PS(">")),
		greaterEqual(_PS(">=")),
		doubleSlash(_PS("//")),
		ok(_PS("ok")),
		try_(_PS("try")),
		possibly(_PS("possibly")),
		need(_PS("need")),
		up(_PS("up")),
		down(_PS("down")),
		each(_PS("each")),
		every(_PS("every")),
		while_(_PS("while")),
		except(_PS("except")),
		find(_PS("find")),
		fold(_PS("fold")),
		first(_PS("first")),
		repeat(_PS("repeat")),
		again(_PS("again")),
		list(_PS("list")),
		groups(_PS("groups")),
		firsts(_PS("firsts")),
		lasts(_PS("lasts")),
		singles(_PS("singles")),
		folds(_PS("folds")),
		exit(_PS("exit")),
		mind(_PS("mind")),
		cliche(_PS("cliche")),
		identifier(_PS("identifier")),
		time(_PS("time")),
		duration(_PS("duration")),
		dating(_PS("dating")),
		hash(_PS("#")),
		ampersand(_PS("&")),
		plusAmpersand(_PS("+&")),
		plusPlusAmpersand(_PS("++&")),
		dollar(_PS("$")),
		plusDollar(_PS("+$")),
		plusPlusDollar(_PS("++$")),
		listen(_PS("listen")),
		head(_PS("head")),
		legs(_PS("legs")),
		operatorEval(_PS("---")),
		quote(_PS("quote")),
		use(_PS("use")),
		using_(_PS("using")),
		but(_PS("+++")),
		through(_PS("through")),
		around(_PS("around")),
		combine(_PS("->")),
		plusRange(_PS("+#")),
		plusSlackRange(_PS("++#")),
		plusRangeReverse(_PS("<+#")),
		plusSlackRangeReverse(_PS("<++#")),
		minusRange(_PS("-#")),
		minusSlackRange(_PS("--#")),
		minusRangeReverse(_PS("<-#")),
		minusSlackRangeReverse(_PS("<--#")),
		building(_PS("building")),
		searchContains(_PS("=*")),
		searchContainsReverse(_PS("<=*")),
		searchTill(_PS("^*")),
		searchTillReverse(_PS("<^*")),
		searchSpread(_PS("~*")),
		searchSpreadReverse(_PS("<~*")),
		searchPrefix(_PS("$*")),
		searchPrefixReverse(_PS("<$*")),
		searchRhyme(_PS("#*")),
		searchRhymeReverse(_PS("<#*")),
		searchUnrhyme(_PS("%*")),
		searchUnrhymeReverse(_PS("<%*")),
		searchPlus(_PS("+*")),
		searchPlusReverse(_PS("<+*")),
		searchMinus(_PS("-*")),
		searchMinusReverse(_PS("<-*")),
		plusRangeSearchContains(_PS("+#=*")),
		plusRangeSearchContainsReverse(_PS("<+#=*")),
		plusRangeSearchTill(_PS("+#^*")),
		plusRangeSearchTillReverse(_PS("<+#^*")),
		plusRangeSearchSpread(_PS("+#~*")),
		plusRangeSearchSpreadReverse(_PS("<+#~*")),
		plusRangeSearchPrefix(_PS("+#$*")),
		plusRangeSearchPrefixReverse(_PS("<+#$*")),
		plusRangeSearchRhyme(_PS("+##*")),
		plusRangeSearchRhymeReverse(_PS("<+##*")),
		plusRangeSearchUnrhyme(_PS("+#%*")),
		plusRangeSearchUnrhymeReverse(_PS("<+#%*")),
		plusRangeSearchPlus(_PS("+#+*")),
		plusRangeSearchPlusReverse(_PS("<+#+*")),
		plusRangeSearchMinus(_PS("+#-*")),
		plusRangeSearchMinusReverse(_PS("<+#-*")),
		minusRangeSearchContains(_PS("-#=*")),
		minusRangeSearchContainsReverse(_PS("<-#=*")),
		minusRangeSearchTill(_PS("-#^*")),
		minusRangeSearchTillReverse(_PS("<-#^*")),
		minusRangeSearchSpread(_PS("-#~*")),
		minusRangeSearchSpreadReverse(_PS("<-#~*")),
		minusRangeSearchPrefix(_PS("-#$*")),
		minusRangeSearchPrefixReverse(_PS("<-#$*")),
		minusRangeSearchRhyme(_PS("-##*")),
		minusRangeSearchRhymeReverse(_PS("<-##*")),
		minusRangeSearchUnrhyme(_PS("-#%*")),
		minusRangeSearchUnrhymeReverse(_PS("<-#%*")),
		minusRangeSearchPlus(_PS("-#+*")),
		minusRangeSearchPlusReverse(_PS("<-#+*")),
		minusRangeSearchMinus(_PS("-#-*")),
		minusRangeSearchMinusReverse(_PS("<-#-*")),
		reverse(_PS("reverse")),
		lower(_PS("lower")),
		upper(_PS("upper")),
		order(_PS("order")),
		title(_PS("title")),
		bytes(_PS("bytes")),
		utf_8(_PS("utf-8")),
		utf_16(_PS("utf-16")),
		utf_16le(_PS("utf-16le")),
		utf_16be(_PS("utf-16be")),
		traverse(_PS("traverse")),
		listwise(_PS("listwise")),
		distinct(_PS("distinct")),
		singlewise(_PS("singlewise")),
		min_(_PS("smallest")),
		max_(_PS("largest")),
		sum_(_PS("sum")),
		transformOperator(_PS("**=**")),
		new_(_PS("new")),
		now(_PS("now")),
		timestamp(_PS("timestamp")),
		gmt(_PS("gmt")),
		localtime(_PS("localtime")),
		splice(_PS("splice")),
		split(_PS("split")),
		replace(_PS("*=*")),
		replaceBeginning(_PS("$*=*")),
		replaceEnding(_PS("<$*=*")),
		merge(_PS("merge")),
		bind(_PS("bind")),
		without(_PS("without")),
		text(_PS("text")),
		file(_PS("file")),
		files(_PS("files")),
		folder(_PS("folder")),
		folders(_PS("folders")),
		readable(_PS("readable")),
		writable(_PS("writable")),
		copy(_PS("copy")),
		move(_PS("move")),
		create(_PS("create")),
		delete_(_PS("delete")),
		zip(_PS("zip")),
		channel(_PS("channel")),
		strap(_PS("strap")),
		plumcake(_PS("plumcake")),
        buglog(_PS("bug")),
        // thread(_PS("thread")),
		knot(_PS("knot")),
		later(_PS("later")),
		hexadecimal(_PS("hexadecimal")),
		color(_PS("color")),
		stackOverflow(_PS("stack-overflow"))
	{}

	const FloatProperty FloatProperty::properties[] =
	{
		FloatProperty("sin", sin),
		FloatProperty("cos", cos),
		FloatProperty("tan", tan),
		FloatProperty("asin", asin),
		FloatProperty("acos", acos),
		FloatProperty("atan", atan),
		FloatProperty("sqrt", sqrt),
		FloatProperty("log", log),
		FloatProperty("exp", exp)
	};

	const PokerHead PokerHead::singleton(Builtin::name.action);
	const EscapeCliche EscapeCliche::singleton;
	const BuiltinClicheLanguage BuiltinClicheLanguage::singleton;
	const BuiltinClicheRead BuiltinClicheRead::singleton;
	const BuiltinClicheSyntaxError BuiltinClicheSyntaxError::singleton;
	const BuiltinClicheTraceread BuiltinClicheTraceread::singleton;
	const BuiltinClicheEval BuiltinClicheEval::singleton;
	const BuiltinClicheQuote BuiltinClicheQuote::singleton;
	const BuiltinClicheCall BuiltinClicheCall::singleton;
	const BuiltinClicheCallWho BuiltinClicheCallWho::singleton;
	const BuiltinClicheWhoTag BuiltinClicheWhoTag::singleton;
	const BuiltinClicheWhoTagTrailer BuiltinClicheWhoTagTrailer::singleton;
	const BuiltinClicheRule BuiltinClicheRule::singleton;
	const BuiltinClicheNameValue BuiltinClicheNameValue::singleton;
	const BuiltinClicheTag BuiltinClicheTag::singleton;
	const BuiltinClicheRuleset BuiltinClicheRuleset::singleton;
	const BuiltinClicheMakeCliche BuiltinClicheMakeCliche::singleton;
	const BuiltinClicheMakeName BuiltinClicheMakeName::singleton;
	const BuiltinClicheComment BuiltinClicheComment::singleton;
	const BuiltinClicheCombine BuiltinClicheCombine::singleton;
	const BuiltinClicheCombined BuiltinClicheCombined::singleton;
	const BuiltinClicheRecall BuiltinClicheRecall::singleton;
	const BuiltinClicheRecalling BuiltinClicheRecalling::singleton;
	const BuiltinClicheUse BuiltinClicheUse::singleton;
	const BuiltinClicheUsing BuiltinClicheUsing::singleton;
	const BuiltinClicheThroughOperation BuiltinClicheThroughOperation::singleton;
	const BuiltinClicheAroundOperation BuiltinClicheAroundOperation::singleton;
	const BuiltinClicheThrough BuiltinClicheThrough::singleton;
	const BuiltinClicheAround BuiltinClicheAround::singleton;
	const BuiltinClicheCalling BuiltinClicheCalling::singleton;
	const BuiltinClicheCallingOk BuiltinClicheCallingOk::singleton;
	const BuiltinClicheUseline BuiltinClicheUseline::singleton;
	const BuiltinClicheConcatenate BuiltinClicheConcatenate::singleton;
	const BuiltinClicheOperationPlus BuiltinClicheOperationPlus::singleton;
	const BuiltinClicheOperationMinus BuiltinClicheOperationMinus::singleton;
	const BuiltinClicheOperationTimes BuiltinClicheOperationTimes::singleton;
	const BuiltinClicheOperationDivide BuiltinClicheOperationDivide::singleton;
	const BuiltinClicheOperationIntegerDivide BuiltinClicheOperationIntegerDivide::singleton;
	const BuiltinClicheOperationModulo BuiltinClicheOperationModulo::singleton;
	const BuiltinClicheOperationEqual BuiltinClicheOperationEqual::singleton;
	const BuiltinClicheOperationNotEqual BuiltinClicheOperationNotEqual::singleton;
	const BuiltinClicheOperationLess BuiltinClicheOperationLess::singleton;
	const BuiltinClicheOperationLessEqual BuiltinClicheOperationLessEqual::singleton;
	const BuiltinClicheOperationGreater BuiltinClicheOperationGreater::singleton;
	const BuiltinClicheOperationGreaterEqual BuiltinClicheOperationGreaterEqual::singleton;
	const BuiltinClicheTinyDollar BuiltinClicheTinyDollar::singleton;
	const BuiltinClicheAssign BuiltinClicheAssign::singleton;
	const BuiltinClicheAssignContinue BuiltinClicheAssignContinue::singleton;
	const BuiltinClicheClosure BuiltinClicheClosure::singleton;
	const BuiltinClicheOk BuiltinClicheOk::singleton;
	const BuiltinClicheOkTrailer BuiltinClicheOkTrailer::singleton;
	const JumperCliche0 JumperCliche0::singleton;
	const BuiltinClicheTry BuiltinClicheTry::singleton;
	const BuiltinClicheTryTrailer BuiltinClicheTryTrailer::singleton;
	const BuiltinClichePossibly BuiltinClichePossibly::singleton;
	const BuiltinClichePossiblyTrailer BuiltinClichePossiblyTrailer::singleton;
	const BuiltinClicheNeed BuiltinClicheNeed::singleton;
	const BuiltinClicheNeedTrailer BuiltinClicheNeedTrailer::singleton;
	const BuiltinClicheEach BuiltinClicheEach::singleton;
	const BuiltinClicheEvery BuiltinClicheEvery::singleton;
	const BuiltinClicheWhile BuiltinClicheWhile::singleton;
	const BuiltinClicheExcept BuiltinClicheExcept::singleton;
	const BuiltinClicheFind BuiltinClicheFind::singleton;
	const BuiltinClicheFold BuiltinClicheFold::singleton;
	const BuiltinClicheFirst BuiltinClicheFirst::singleton;
	const BuiltinClicheMin BuiltinClicheMin::singleton;
	const BuiltinClicheMax BuiltinClicheMax::singleton;
	const BuiltinClicheSum BuiltinClicheSum::singleton;
	const BuiltinClicheRepeat BuiltinClicheRepeat::singleton;
	const BuiltinClicheAgain BuiltinClicheAgain::singleton;
	const BuiltinClicheTrial BuiltinClicheTrial::singleton;
	const BuiltinClicheTransform BuiltinClicheTransform::singleton;
	const BuiltinClicheBut BuiltinClicheBut::singleton;
	const BuiltinClicheIf BuiltinClicheIf::singleton;
	const BuiltinClicheIfElse BuiltinClicheIfElse::singleton;
	const BuiltinClicheOr BuiltinClicheOr::singleton;
	const BuiltinClicheAnd BuiltinClicheAnd::singleton;
	const BuiltinClicheAnyway BuiltinClicheAnyway::singleton;
	const BuiltinClicheNot BuiltinClicheNot::singleton;
	const BuiltinClichePlusRange BuiltinClichePlusRange::singleton;
	const BuiltinClichePlusSlackRange BuiltinClichePlusSlackRange::singleton;
	const BuiltinClichePlusRangeReverse BuiltinClichePlusRangeReverse::singleton;
	const BuiltinClichePlusSlackRangeReverse BuiltinClichePlusSlackRangeReverse::singleton;
	const BuiltinClicheMinusRange BuiltinClicheMinusRange::singleton;
	const BuiltinClicheMinusSlackRange BuiltinClicheMinusSlackRange::singleton;
	const BuiltinClicheMinusRangeReverse BuiltinClicheMinusRangeReverse::singleton;
	const BuiltinClicheMinusSlackRangeReverse BuiltinClicheMinusSlackRangeReverse::singleton;
	const BuiltinClicheBuilding BuiltinClicheBuilding::singleton;
	const BuiltinClicheBuilderShort BuiltinClicheBuilderShort::listBuilder(&Builtin::name.list);
	const BuiltinClicheBuilderShort BuiltinClicheBuilderShort::exitBuilder(&Builtin::name.exit);
	const BuiltinClicheBuilderTrailer BuiltinClicheBuilderTrailer::listBuilder(&Builtin::name.list);
	const BuiltinClicheBuilderTrailer BuiltinClicheBuilderTrailer::exitBuilder(&Builtin::name.exit);
	const BuiltinClicheGroups BuiltinClicheGroups::singleton;
	const BuiltinClicheFirsts BuiltinClicheFirsts::singleton;
	const BuiltinClicheLasts BuiltinClicheLasts::singleton;
	const BuiltinClicheSingles BuiltinClicheSingles::singleton;
	const BuiltinClicheFolds BuiltinClicheFolds::singleton;
	const BuiltinClicheDistinct BuiltinClicheDistinct::singleton;
	const BuiltinClicheHeadset BuiltinClicheHeadset::singleton;
	const BuiltinClicheLegs BuiltinClicheLegs::singleton;
	const BuiltinClicheMerge BuiltinClicheMerge::singleton;
	const BuiltinClicheBind BuiltinClicheBind::singleton;
	const BuiltinClicheWithout BuiltinClicheWithout::singleton;
	const BuiltinClicheChannel BuiltinClicheChannel::singleton;
	const BuiltinClicheStrap BuiltinClicheStrap::singleton;
	const BuiltinClicheListen BuiltinClicheListen::singleton;
    // const BuiltinClicheThread BuiltinClicheThread::singleton;
	const BuiltinClicheKnot BuiltinClicheKnot::singleton;
	const BuiltinClicheLater BuiltinClicheLater::singleton;

	const ImplicitParameter ImplicitParameter::who(Builtin::name.who, ImplicitParameter::WHO);
	const ImplicitParameter ImplicitParameter::where_(Builtin::name.where_, ImplicitParameter::WHERE);
	const ImplicitParameter ImplicitParameter::what(Builtin::name.what, ImplicitParameter::WHAT);
	const ImplicitParameter ImplicitParameter::self(Builtin::name.self, ImplicitParameter::SELF);

	const BuiltinClicheError BuiltinClicheError::singleton;
	const BuiltinClicheErrorTrailer BuiltinClicheErrorTrailer::singleton;

	Plum Plum::singleton;

	BuiltinClicheSearchCount const BuiltinClicheSearchCount::plain(&Builtin::name.count_);

	BuiltinClicheSearchContains const BuiltinClicheSearchContains::plain(&Builtin::name.searchContains);
	BuiltinClicheSearchContains const BuiltinClicheSearchContains::plusRange(&Builtin::name.plusRangeSearchContains);
	BuiltinClicheSearchContains const BuiltinClicheSearchContains::minusRange(&Builtin::name.minusRangeSearchContains);
	BuiltinClicheSearchContainsReverse const BuiltinClicheSearchContainsReverse::plain(&Builtin::name.searchContainsReverse);
	BuiltinClicheSearchContainsReverse const BuiltinClicheSearchContainsReverse::plusRange(&Builtin::name.plusRangeSearchContainsReverse);
	BuiltinClicheSearchContainsReverse const BuiltinClicheSearchContainsReverse::minusRange(&Builtin::name.minusRangeSearchContainsReverse);

	BuiltinClicheSearchTill const BuiltinClicheSearchTill::plain(&Builtin::name.searchTill);
	BuiltinClicheSearchTill const BuiltinClicheSearchTill::plusRange(&Builtin::name.plusRangeSearchTill);
	BuiltinClicheSearchTill const BuiltinClicheSearchTill::minusRange(&Builtin::name.minusRangeSearchTill);
	BuiltinClicheSearchTillReverse const BuiltinClicheSearchTillReverse::plain(&Builtin::name.searchTillReverse);
	BuiltinClicheSearchTillReverse const BuiltinClicheSearchTillReverse::plusRange(&Builtin::name.plusRangeSearchTillReverse);
	BuiltinClicheSearchTillReverse const BuiltinClicheSearchTillReverse::minusRange(&Builtin::name.minusRangeSearchTillReverse);

	BuiltinClicheSearchSpread const BuiltinClicheSearchSpread::plain(&Builtin::name.searchSpread);
	BuiltinClicheSearchSpread const BuiltinClicheSearchSpread::plusRange(&Builtin::name.plusRangeSearchSpread);
	BuiltinClicheSearchSpread const BuiltinClicheSearchSpread::minusRange(&Builtin::name.minusRangeSearchSpread);
	BuiltinClicheSearchSpreadReverse const BuiltinClicheSearchSpreadReverse::plain(&Builtin::name.searchSpreadReverse);
	BuiltinClicheSearchSpreadReverse const BuiltinClicheSearchSpreadReverse::plusRange(&Builtin::name.plusRangeSearchSpreadReverse);
	BuiltinClicheSearchSpreadReverse const BuiltinClicheSearchSpreadReverse::minusRange(&Builtin::name.minusRangeSearchSpreadReverse);

	BuiltinClicheSearchPrefix const BuiltinClicheSearchPrefix::plain(&Builtin::name.searchPrefix);
	BuiltinClicheSearchPrefix const BuiltinClicheSearchPrefix::plusRange(&Builtin::name.plusRangeSearchPrefix);
	BuiltinClicheSearchPrefix const BuiltinClicheSearchPrefix::minusRange(&Builtin::name.minusRangeSearchPrefix);
	BuiltinClicheSearchPrefixReverse const BuiltinClicheSearchPrefixReverse::plain(&Builtin::name.searchPrefixReverse);
	BuiltinClicheSearchPrefixReverse const BuiltinClicheSearchPrefixReverse::plusRange(&Builtin::name.plusRangeSearchPrefixReverse);
	BuiltinClicheSearchPrefixReverse const BuiltinClicheSearchPrefixReverse::minusRange(&Builtin::name.minusRangeSearchPrefixReverse);

	BuiltinClicheSearchRhyme const BuiltinClicheSearchRhyme::plain(&Builtin::name.searchRhyme);
	BuiltinClicheSearchRhyme const BuiltinClicheSearchRhyme::plusRange(&Builtin::name.plusRangeSearchRhyme);
	BuiltinClicheSearchRhyme const BuiltinClicheSearchRhyme::minusRange(&Builtin::name.minusRangeSearchRhyme);
	BuiltinClicheSearchRhymeReverse const BuiltinClicheSearchRhymeReverse::plain(&Builtin::name.searchRhymeReverse);
	BuiltinClicheSearchRhymeReverse const BuiltinClicheSearchRhymeReverse::plusRange(&Builtin::name.plusRangeSearchRhymeReverse);
	BuiltinClicheSearchRhymeReverse const BuiltinClicheSearchRhymeReverse::minusRange(&Builtin::name.minusRangeSearchRhymeReverse);

	BuiltinClicheSearchUnrhyme const BuiltinClicheSearchUnrhyme::plain(&Builtin::name.searchUnrhyme);
	BuiltinClicheSearchUnrhyme const BuiltinClicheSearchUnrhyme::plusRange(&Builtin::name.plusRangeSearchUnrhyme);
	BuiltinClicheSearchUnrhyme const BuiltinClicheSearchUnrhyme::minusRange(&Builtin::name.minusRangeSearchUnrhyme);
	BuiltinClicheSearchUnrhymeReverse const BuiltinClicheSearchUnrhymeReverse::plain(&Builtin::name.searchUnrhymeReverse);
	BuiltinClicheSearchUnrhymeReverse const BuiltinClicheSearchUnrhymeReverse::plusRange(&Builtin::name.plusRangeSearchUnrhymeReverse);
	BuiltinClicheSearchUnrhymeReverse const BuiltinClicheSearchUnrhymeReverse::minusRange(&Builtin::name.minusRangeSearchUnrhymeReverse);

	BuiltinClicheSearchPlus const BuiltinClicheSearchPlus::plain(&Builtin::name.searchPlus);
	BuiltinClicheSearchPlus const BuiltinClicheSearchPlus::plusRange(&Builtin::name.plusRangeSearchPlus);
	BuiltinClicheSearchPlus const BuiltinClicheSearchPlus::minusRange(&Builtin::name.minusRangeSearchPlus);
	BuiltinClicheSearchPlusReverse const BuiltinClicheSearchPlusReverse::plain(&Builtin::name.searchPlusReverse);
	BuiltinClicheSearchPlusReverse const BuiltinClicheSearchPlusReverse::plusRange(&Builtin::name.plusRangeSearchPlusReverse);
	BuiltinClicheSearchPlusReverse const BuiltinClicheSearchPlusReverse::minusRange(&Builtin::name.minusRangeSearchPlusReverse);

	BuiltinClicheSearchMinus const BuiltinClicheSearchMinus::plain(&Builtin::name.searchMinus);
	BuiltinClicheSearchMinus const BuiltinClicheSearchMinus::plusRange(&Builtin::name.plusRangeSearchMinus);
	BuiltinClicheSearchMinus const BuiltinClicheSearchMinus::minusRange(&Builtin::name.minusRangeSearchMinus);
	BuiltinClicheSearchMinusReverse const BuiltinClicheSearchMinusReverse::plain(&Builtin::name.searchMinusReverse);
	BuiltinClicheSearchMinusReverse const BuiltinClicheSearchMinusReverse::plusRange(&Builtin::name.plusRangeSearchMinusReverse);
	BuiltinClicheSearchMinusReverse const BuiltinClicheSearchMinusReverse::minusRange(&Builtin::name.minusRangeSearchMinusReverse);

	BuiltinClicheRound const BuiltinClicheRound::singleton;
	BuiltinClicheTruncate const BuiltinClicheTruncate::singleton;

	BuiltinClicheOperationUpDown const BuiltinClicheOperationUpDown::up(&Builtin::name.up, false);
	BuiltinClicheOperationUpDown const BuiltinClicheOperationUpDown::down(&Builtin::name.down, true);

	BuiltinClicheSplice const BuiltinClicheSplice::singleton;
	BuiltinClicheSplit const BuiltinClicheSplit::singleton;
	BuiltinClicheOrder const BuiltinClicheOrder::singleton;
	BuiltinClicheReplace const BuiltinClicheReplace::singleton;
	BuiltinClicheReplaceBeginning const BuiltinClicheReplaceBeginning::singleton;
	BuiltinClicheReplaceEnding const BuiltinClicheReplaceEnding::singleton;
	BuiltinClicheBug const BuiltinClicheBug::singleton;
	BuiltinClicheFileName const BuiltinClicheFileName::singleton;
	BuiltinClicheFolderName const BuiltinClicheFolderName::singleton;
	BuiltinClicheWhen const BuiltinClicheWhen::singleton;

	long long Timestamp::stamp;
}
#endif
