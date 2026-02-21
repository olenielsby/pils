/* This file is public domain */
#include <src/juce_WithoutMacros.h>
#include "pils-kernel/initializers.h"
#include "pilsplug/initializers.h"
#include "jpils/jpils-binding-base.h"
#include "jpils/jpils-supplement.h"
#include "jpils/jpils-opengl.h"
#include "jpils/jpils-graph-define.h"
#include "nppils-autodeclare.h"
#include "nppils-autoplumming.h"

namespace PILS
{
	ClassExtracterMethod method__ClassExtracterMethod("class");
	const Constant *CallbackHelperBase::toPils(const ApplicationCommandTarget::InvocationInfo &arg)
	{
		return JuceClasses::c__ApplicationCommandTarget__InvocationInfo.reference(&arg);
	}

	juce::Graphics *JuceReference::as_Graphics() const
	{
		JuceClassConverter toGraphics(JuceClass::classes.c__Graphics, false);
		if (convert(toGraphics))
			return (juce::Graphics *)toGraphics.value;
		else
			return NULL;
	}
}
