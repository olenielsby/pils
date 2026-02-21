/* This file is public domain */

#include "pils-kernel/pipe.h"
#include "pils-kernel/statement.h"
#include "pilsplug/plughost.h"
#include "jpils-thread.h"
#include "jpils-binding-base.h"
#include "jpils-commander.h"

class JPilsApplication
	: public juce::JUCEApplication, private PILS::PilsCommander
{
public:
	JPilsApplication() {}
	void initialise (const juce::String& commandLine);
	void anotherInstanceStarted (const juce::String &commandLine);
	void shutdown();
	bool moreThanOneInstanceAllowed();
	const juce::String getApplicationName();
	const juce::String getApplicationVersion();
	class WorkerThreadDestruction : public MessageListener
	{
		void handleMessage(const Message &message)
		{
			juce::Thread *thread = (juce::Thread *)message.pointerParameter;
			thread->waitForThreadToExit(-1);
			delete thread;
		}
	} *workerThreadDestruction;
	const char *pilsBootExpression();
};

void JPilsApplication::initialise (const juce::String& commandLine)
{
	commandLineHandler = getCommandLineHandler();
	if (!executeCommandLine(commandLine))
		quit();
	tooltipWindow = new TooltipWindow();
	workerThreadDestruction = new WorkerThreadDestruction();
}

void JPilsApplication::anotherInstanceStarted (const juce::String &commandLine)
{
	executeCommandLine(commandLine);
}

bool JPilsApplication::moreThanOneInstanceAllowed()
{
	return false;
}

const juce::String JPilsApplication::getApplicationName()
{
	return "jucePILS";
}

const juce::String JPilsApplication::getApplicationVersion()
{
	return "unknown version";
}

START_JUCE_APPLICATION (JPilsApplication)

void JPilsApplication::shutdown()
{
	delete tooltipWindow;
	delete workerThreadDestruction;
	PILS::MainThread::singleton->temporaryStrapSticker->clear();
	PILS::MainThread::singleton->where_ = commandLineHandler;
	PILS::MainThread::singleton->releaseReference();
	PILS::Heap::shutdown();
}

void PILS::MainThread::runLevelTouchDown()
{
	PendableThread::runLevelTouchDown();
	if (!JuceComponent::desktopComponentCount)
		juce::JUCEApplication::quit();
}

void PILS::PilsThread::postThreadDestructionMessage(juce::Thread *deadThread)
{
	((JPilsApplication *)JUCEApplication::getInstance())->workerThreadDestruction->postMessage(new juce::Message(0, 0, 0, deadThread));
}
