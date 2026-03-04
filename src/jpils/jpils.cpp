/* This file is public domain */

#include "pipe.h"
#include "statement.h"
#include "plughost.h"
#include "jpils-thread.h"
#include "jpils-binding-base.h"
#include "jpils-commander.h"

class JPilsApplication
	: public juce::JUCEApplication, private PILS::PilsCommander
{
public:
	JPilsApplication() {}
    void initialise (const juce::String& commandLine) override;
    void anotherInstanceStarted (const juce::String &commandLine) override;
    void shutdown() override;
    bool moreThanOneInstanceAllowed() override;
    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;
    /*
	class WorkerThreadDestruction : public MessageListener
	{
		void handleMessage(const Message &message)
		{
			juce::Thread *thread = (juce::Thread *)message.pointerParameter;
			thread->waitForThreadToExit(-1);
			delete thread;
		}
	} *workerThreadDestruction;
    */

    class WorkerThreadDestruction
    {
    public:
        static void destroy(juce::Thread* thread)
        {
            juce::MessageManager::callAsync([thread]
                                            {
                                                thread->waitForThreadToExit(-1);
                                                delete thread;
                                            });
        }
    } // *workerThreadDestruction
        ;

	const char *pilsBootExpression();
};

void JPilsApplication::initialise (const juce::String& commandLine)
{
    DBG("JPilsApplication::initialise called");

	commandLineHandler = getCommandLineHandler();
    if (!executeCommandLine(commandLine)){
        DBG("executeCommandLine returned false");
        quit();
        return;
    }
    DBG("PILS boot succeeded");
	tooltipWindow = new TooltipWindow();
    //workerThreadDestruction = new WorkerThreadDestruction();
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
    //delete workerThreadDestruction;
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
    //JPilsApplication::WorkerThreadDestruction::destroy(thread);
    //((JPilsApplication *)JUCEApplication::getInstance())->workerThreadDestruction->postMessage(new juce::Message(0, 0, 0, deadThread));
}
