/* This file is public domain */
#ifndef _PLUMMING_JPILS_COMMANDER_H_
#define _PLUMMING_JPILS_COMMANDER_H_
#include "jpils-thread.h"

namespace PILS
{
	class PilsCommander
	{
	public:
		PilsCommander() : tooltipWindow(NULL) {}
	protected:
		const Any *getCommandLineHandler();
		bool executeCommandLine(const juce::String &commandLine);
		const Any *commandLineHandler;
		TooltipWindow *tooltipWindow;
		static const char *bootExpression;
	private:
		void addNamespace(NodeBuilder<const Constant> &gloss, const char *prefix, const char *identifier);
	};
}
#endif
