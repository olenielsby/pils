/* This file is public domain */

#include "pils-kernel/pipe.h"
#include "pils-kernel/statement.h"
#include "pilsplug/plughost.h"
#include "jpils/jpils-thread.h"
#include "jpils/jpils-binding-base.h"
#include "jpils/jpils-commander.h"

namespace PILS
{
	class NPPilsCommander : public PilsCommander
	{
	public:
		static NPPilsCommander singleton;
		~NPPilsCommander();
		bool execute(const juce::String &commandLine);
		void shutdown();
	};
}
