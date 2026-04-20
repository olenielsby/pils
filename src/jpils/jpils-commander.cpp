/* This file is public domain */
#include "pipe.h"
#include "statement.h"
//#include "pilsplug/plughost.h"
#include "jpils-thread.h"
#include "jpils-binding-base.h"
#include "jpils-commander.h"

const PILS::PilsString *pils_configuration_get_user_language();

namespace PILS
{
	class ConfigurationBuilder
		: private NodeBuilder<const Constant>
	{
	public:
		void set(const PILS_CHAR *name, ::juce::File::SpecialLocationType specialLocation)
		{
			::juce::File file = juce::File::getSpecialLocation(specialLocation);
			::juce::String string = file.getFullPathName();
			if (!::juce::File::areFileNamesCaseSensitive() && string[0] >= 'a' && string[0] <= 'z')
			{
				::juce::String old = string;
				string = old.substring(0,1).toUpperCase();
				string+=old.substring(1);
			}
            if (::juce::File::getSeparatorChar() == '\\')	string = string.replaceCharacter('\\', '/');
			if (file.isDirectory())	string += '/';
			aim(PilsString::get(name));
			NodeBuilder<const Constant>::set(pils(string));
		}
		void set(const PILS_CHAR *name, const PILS_CHAR *value)
		{
			aim(PilsString::get(name));
			NodeBuilder<const Constant>::set(PilsString::get(value));
		}
		void set(const PILS_CHAR *name, const PilsString *value)
		{
			aim(PilsString::get(name));
			NodeBuilder<const Constant>::set(value);
		}
		const NodeConstant *build()
		{
			return (const NodeConstant*) NodeBuilder<const Constant>::build();
		}
		ConfigurationBuilder()
			: NodeBuilder<const Constant>(&Builtin::name.minus)
		{
			Builtin::name.minus.addReference();
		}
	};

	bool PilsCommander::executeCommandLine(const ::juce::String& commandLine)
	{
		Runner &runner = *MainThread::singleton;
		const Any *cmd = nullptr;
		runner.where_ = commandLineHandler;
		commandLineHandler->addReference();
		//Build PILS argument list
		{
			std::vector<const Constant*> arglist;
			arglist.push_back(pils(::juce::File::getSpecialLocation(::juce::File::currentExecutableFile).getFullPathName()));
			for (const char *cc = commandLine.toUTF8();;)
			{
				switch (*cc)
				{
				case 0:
					break;
				case '\r':
				case '\n':
				case ' ':
				case '\t':
					cc++;
					continue;
				case '"':
					for (const char *c = ++cc;; cc++)
					{
						switch (*cc)
						{
						case '"':
							arglist.push_back(PILS::PilsString::get(c, cc++ - c));
						case 0:
							break;
						default:
							continue;
						}
						break;
					}
					continue;
				default:
					for (const char *c = cc++;; cc++)
					{
						switch (*cc)
						{
						case '"':
						case 0:
						case '\r':
						case '\n':
						case ' ':
						case '\t':
							arglist.push_back(PILS::PilsString::get(c, cc - c));
							break;
						default:
							continue;
						}
						break;
					}
					continue;
				}
				break;
			}
			cmd = ListConstant::get(&arglist[0], arglist.size())->callHere();
		}
		{
			MainThread::RunLevel runlevel;
			runner.run(cmd);
			cmd->releaseReference();
			runner.where_->releaseReference();
		}
		return JuceComponent::desktopComponentCount != 0;
	}

	void PilsCommander::addNamespace(NodeBuilder<const Constant> &gloss, const char *prefix, const char *identifier)
	{
		gloss.aim(PilsString::get(prefix));
		Empty::singleton.addReference();
		const ClicheTiny *cliche = PilsString::get(identifier)->clichefy();
		gloss.set(cliche->nodeConstant(&Empty::singleton));
		cliche->unduplicateReference();
	}

	const Any *PilsCommander::getCommandLineHandler()
	{
		const Any *commandLineHandler = nullptr;
		Heap::useStandardAllocator();
		const Language *language;
		{
			NodeBuilder<const Constant> gloss(PilsString::get(_PS("system")));
			Empty::singleton.addReference();
			gloss.aim(&Empty::singleton);
			gloss.set(PilsString::get(_PS("\1.")));
			// Add standard namespace
			addNamespace(gloss, "system", "pils.org/ns/sne");
			addNamespace(gloss, "graph", "pils.org/ns/graph");
			addNamespace(gloss, "font", "pils.org/ns/font/normal");
			addNamespace(gloss, "italic", "pils.org/ns/font/italic");
			addNamespace(gloss, "bold", "pils.org/ns/font/bold");
			addNamespace(gloss, "bold-italic", "pils.org/ns/font/bold-italic");
			// Add system information namespace
			gloss.aim(PilsString::get(_PS("pils-configuration")));
			ConfigurationBuilder config;
			config.set(_PS("platform"), _PS("juce"));
			config.set(_PS("application-type"), _PS("desktop"));
#ifdef JUCE_WIN32
			config.set(_PS("system"), _PS("win32"));
			config.set(_PS("plugtype"), _PS("dll"));
#elif defined(JUCE_LINUX)
			config.set(_PS("system"), _PS("linux"));
			config.set(_PS("plugtype"), _PS("so"));
#else
			config.set(_PS("system"), _PS("macos"));
			config.set(_PS("plugtype"), _PS("dylib"));
#endif
			config.set(_PS("compile-date"), _PS(__DATE__) _PS(" ") _PS(__TIME__));
#ifdef JUCE_DEBUG
			config.set(_PS("compile-mode"), _PS("debug"));
#else
			config.set(_PS("compile-mode"), _PS("release"));
#endif
			config.set(_PS("executable-filename"), ::juce::File::currentExecutableFile);
			config.set(_PS("open-command"), ::juce::File::getSpecialLocation(File::currentExecutableFile).getFullPathName().toUTF8());
			config.set(_PS("configuration-directory"), ::juce::File::userApplicationDataDirectory);
			config.set(_PS("documents-directory"), ::juce::File::userDocumentsDirectory);
			config.set(_PS("language"), pils_configuration_get_user_language());
			config.set(_PS("pils-filetype"), ::juce::File::getSpecialLocation(File::currentExecutableFile).getFileNameWithoutExtension().toUTF8());
			gloss.set(config.build());
			language = (const Language*)BuiltinClicheLanguage::singleton.nodeConstant((HalfbakedConstant*)gloss.build());
		}
		MainThread::singleton = (MainThread *)PILS::PilsThread::RunLevel::getCurrent();
		Runner &runner = *MainThread::singleton;

		runner.where_ = Plum::cake();
		const PilsString *teststring = PilsString::get(bootExpression);

		const Any *test = BuiltinClicheRead::singleton.node(teststring)->callWho(language);
		try
		{
			runner.run(test);
			test->releaseReference();
			test = runner.where_;
			(runner.where_ = PILS::Plum::cake())->addReference();
			runner.run(test);
			commandLineHandler = runner.where_;
			test->releaseReference();
		}
		catch (const wchar_t *msg)
		{
			::juce::Logger::outputDebugString(msg);
		}
		MainThread::singleton->doPending();
		return commandLineHandler;
	}

	void SinkBug::bug(Runner &run, const PilsString &bug)
	{
		::juce::String string = juce::String::fromUTF8(bug.value, bug.count->value);
		::juce::Logger::outputDebugString(string);
	}
}
