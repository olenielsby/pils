/* This file is public domain */
#pragma once
#include "datamodel.h"
#include "sink.h"
#include "qpils_thread.h"
#include <QString>

namespace PILS
{
	class PilsCommander
	{
	public:
        PilsCommander(const std::string efn);
        const std::string exeFileName;
        bool executeCommandLine(const std::vector<std::string> &args);
    private:
		const Any *getCommandLineHandler();
        const Any *commandLineHandler;
		static const char *bootExpression;
		void addNamespace(NodeBuilder<const Constant> &gloss, const char *prefix, const char *identifier);
	};
}
