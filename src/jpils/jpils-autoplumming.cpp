/* This file is public domain */
//#include <src/juce_WithoutMacros.h>
#include "initializers.h"
//#include "pilsplug/initializers.h"
#include "jpils-binding-base.h"
#include "jpils-supplement.h"
#include "jpils-opengl.h"
#include "jpils-graph-define.h"
#include "jpils-autodeclare.h"
#include "jpils-autoplumming.h"

namespace PILS
{
	ClassExtracterMethod method__ClassExtracterMethod("class");
	const Constant *CallbackHelperBase::toPils(const ApplicationCommandTarget::InvocationInfo &arg)
	{
		return JuceClasses::c__ApplicationCommandTarget__InvocationInfo.reference(&arg);
	}

	const Constant *CallbackHelperBase::toPils(const DragAndDropTarget::SourceDetails &arg)
	{
		return JuceClasses::c__DragAndDropTarget__SourceDetails.reference(&arg);
	}

	juce::Graphics *JuceReference::as_Graphics() const
	{
		JuceClassConverter toGraphics(JuceClass::classes.c__Graphics, false);
		if (convert(toGraphics))
			return (juce::Graphics *)toGraphics.value;
		else
			return nullptr;
	}
}
