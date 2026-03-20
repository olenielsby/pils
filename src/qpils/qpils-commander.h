/* This file is public domain */
#pragma once
#include "pils-kernel/datamodel.h"
#include "pils-kernel/sink.h"
#include <QString>

namespace PILS
{
	class PilsCommander
	{
	public:
        const std::string exeFileName;
        Runner runner;
        PilsCommander(const std::string efn);
        bool executeCommandLine(const std::vector<std::string> &args);
    private:
		const Any *getCommandLineHandler();
        const Any *commandLineHandler;
		static const char *bootExpression;
		void addNamespace(NodeBuilder<const Constant> &gloss, const char *prefix, const char *identifier);
	};
}
