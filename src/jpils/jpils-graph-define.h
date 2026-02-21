/* This file is public domain */
#ifndef _PLUMMING_JPILS_GRAPH_DEFINE_H_
#define _PLUMMING_JPILS_GRAPH_DEFINE_H_
#include "jpils-thread.h"
#include "jpils-graph.h"

namespace PILS
{
	const PilsString *const PredefinedGraphName::namespace_ = PilsString::get("pils.org/ns/graph");
	const PredefinedGraphNameGraph PredefinedGraphName::graph = "graph";
	const PredefinedGraphName PredefinedGraphName::background = "background";
	const PredefinedGraphName PredefinedGraphName::curve = "curve";
	const PredefinedGraphName PredefinedGraphName::shape = "shape";
	const PredefinedGraphName PredefinedGraphName::at = "at";
	const PredefinedGraphName PredefinedGraphName::scale = "scale";
	const PredefinedGraphName PredefinedGraphName::ink = "ink";
	const PredefinedGraphName PredefinedGraphName::stroke = "stroke";
	const PredefinedGraphName PredefinedGraphName::round = "round";
	const PredefinedGraphName PredefinedGraphName::sharp = "sharp";
	const PredefinedGraphName PredefinedGraphName::font = "font";
	const PredefinedGraphName PredefinedGraphName::linear = "linear";
	const PredefinedGraphName PredefinedGraphName::circular = "circular";
	const PredefinedGraphName PredefinedGraphName::image = "image";
	const PredefinedGraphName PredefinedGraphName::align = "align";
	const PredefinedGraphName PredefinedGraphName::outsize = "outsize";
	const PredefinedGraphName PredefinedGraphName::size = "size";
	const PredefinedGraphName PredefinedGraphName::width = "width";
	const PredefinedGraphName PredefinedGraphName::height = "height";
	const BuiltinClicheGraph BuiltinClicheGraph::singleton;
	const BuiltinClicheCurve BuiltinClicheCurve::singleton;
	const BuiltinClicheShape BuiltinClicheShape::singleton;
	const BuiltinClicheAt BuiltinClicheAt::singleton;
	const BuiltinClicheAlign BuiltinClicheAlign::singleton;
	const BuiltinClicheScale BuiltinClicheScale::singleton;
	const BuiltinClicheBackground BuiltinClicheBackground::singleton;
	const BuiltinClicheInk BuiltinClicheInk::singleton;
	const BuiltinClicheFont BuiltinClicheFont::singleton;
	const FontNamespace FontNamespace::table[] =
	{
		"pils.org/ns/font/normal",
		"pils.org/ns/font/italic",
		"pils.org/ns/font/bold",
		"pils.org/ns/font/bold-italic"
	};
	const BuiltinClicheGradient BuiltinClicheGradient::linear = &PredefinedGraphName::linear;
	const BuiltinClicheGradient BuiltinClicheGradient::circular = &PredefinedGraphName::circular;
	const BuiltinClicheImage BuiltinClicheImage::singleton;
	const BuiltinClicheGraphSize BuiltinClicheGraphSize::singleton;
	const BuiltinClicheGraphOutsize BuiltinClicheGraphOutsize::singleton;
	const BuiltinClicheStroke BuiltinClicheStroke::instance[] =
	{
		BuiltinClicheStroke(&PredefinedGraphName::stroke, &PredefinedGraphName::stroke, juce::PathStrokeType::mitered, juce::PathStrokeType::butt),
		BuiltinClicheStroke(&PredefinedGraphName::stroke, &PredefinedGraphName::round, juce::PathStrokeType::mitered, juce::PathStrokeType::rounded),
		BuiltinClicheStroke(&PredefinedGraphName::stroke, &PredefinedGraphName::sharp, juce::PathStrokeType::mitered, juce::PathStrokeType::square),
		BuiltinClicheStroke(&PredefinedGraphName::round, &PredefinedGraphName::stroke, juce::PathStrokeType::curved, juce::PathStrokeType::butt),
		BuiltinClicheStroke(&PredefinedGraphName::round, &PredefinedGraphName::round, juce::PathStrokeType::curved, juce::PathStrokeType::rounded),
		BuiltinClicheStroke(&PredefinedGraphName::round, &PredefinedGraphName::sharp, juce::PathStrokeType::curved, juce::PathStrokeType::square),
		BuiltinClicheStroke(&PredefinedGraphName::sharp, &PredefinedGraphName::stroke, juce::PathStrokeType::beveled, juce::PathStrokeType::butt),
		BuiltinClicheStroke(&PredefinedGraphName::sharp, &PredefinedGraphName::round, juce::PathStrokeType::beveled, juce::PathStrokeType::rounded),
		BuiltinClicheStroke(&PredefinedGraphName::sharp, &PredefinedGraphName::sharp, juce::PathStrokeType::beveled, juce::PathStrokeType::square)
	};
}
#endif
