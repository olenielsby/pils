#include <src/juce_WithoutMacros.h>
#include <extras/browser plugins/wrapper/juce_BrowserPluginComponent.h>
#include "nppils-commander.h"

//==============================================================================
/**
    This is our top-level component for our plugin..
*/
class PilsBrowserPlugin
	: public BrowserPluginComponent
	, public ButtonListener
{
public:
    PilsBrowserPlugin()
    {
		PILS::JuceComponent::desktopComponentCount++;
		addAndMakeVisible (textBox = new TextEditor (String::empty));
        textBox->setMultiLine (true);
        textBox->setBounds (8, 8, 300, 300);

        addAndMakeVisible (button = new TextButton ("Send a message to the webpage"));
        button->setBounds (320, 8, 180, 22);
        button->addButtonListener (this);
        button->setEnabled (false);

        ourJavascriptObject = new PilsBrowserObject (this);

        textBox->setText ("Browser version info: " + getBrowserVersion());
	}

    ~PilsBrowserPlugin()
    {
        deleteAllChildren();
		if (!--PILS::JuceComponent::desktopComponentCount)
		{
			PILS::NPPilsCommander::singleton.shutdown();
		}
	}

    const var getJavascriptObject()
    {
        // The browser calls this to get the javascript object that represents our plugin..
        return ourJavascriptObject;
    }

    void paint (Graphics& g)
    {
        g.fillAll (Colours::lightblue);
    }

    void setJavascriptObjectFromBrowser (var callbackObject)
    {
        javascriptObjectFromBrowser = callbackObject;
        
        button->setEnabled (javascriptObjectFromBrowser.isObject());
    }

    void buttonClicked (Button*)
    {
        javascriptObjectFromBrowser.call ("printmessage", "This is a message sent from the plugin...");
    }

    var ourJavascriptObject;
    var javascriptObjectFromBrowser;
    TextEditor* textBox;
    TextButton* button;

    //==============================================================================
    /** This is the javascript object that the browser uses when the webpage accesses
        methods or properties on our plugin object.
    */
    class PilsBrowserObject : public DynamicObject
    {
    public:
        PilsBrowserObject (PilsBrowserPlugin* owner_)
            : owner (owner_)
        {
            // Add a couple of methods to our object..
            setMethod ("printText", (var::MethodFunction) &PilsBrowserObject::printText);
            setMethod ("popUpMessageBox", (var::MethodFunction) &PilsBrowserObject::popUpMessageBox);
            setMethod ("registerCallbackObject", (var::MethodFunction) &PilsBrowserObject::registerCallbackObject);
            setMethod ("pilsCommand", (var::MethodFunction) &PilsBrowserObject::pilsCommand);

            // Add some value properties that the webpage can access
            setProperty ("property1", "testing testing...");
            setProperty ("property2", 12345678.0);
        }

        PilsBrowserObject()
        {
        }

		//==============================================================================
        // These methods are called by javascript in the webpage...

        const var pilsCommand (const var* params, int numParams)
        {
			if (numParams == 1 && PILS::NPPilsCommander::singleton.execute(params[0].toString()))
				return "PILS command was executed.";
			else
				return "Shit happens.";
        }

		const var printText (const var* params, int numParams)
        {
            if (numParams > 0)
                owner->textBox->setText (owner->textBox->getText() + "\n" + params[0].toString());

            return "text was printed ok!";
        }

        const var popUpMessageBox (const var* params, int numParams)
        {
            if (numParams > 0)
                AlertWindow::showMessageBox (AlertWindow::InfoIcon, 
                                             "A message from the webpage", 
                                             params[0].toString(), 
                                             String::empty, owner);
            return var();
        }

        const var registerCallbackObject (const var* params, int numParams)
        {
            if (numParams > 0)
                owner->setJavascriptObjectFromBrowser (params[0]);

            return var();
        }

        //==============================================================================
        PilsBrowserPlugin* owner;
    };
};

BrowserPluginComponent* JUCE_CALLTYPE createBrowserPlugin()
{
    return new PilsBrowserPlugin();
}

void PILS::MainThread::runLevelTouchDown()
{
	PendableThread::runLevelTouchDown();
	if (!JuceComponent::desktopComponentCount)
	{
		PILS::NPPilsCommander::singleton.shutdown();
	}
}

void PILS::PilsThread::postThreadDestructionMessage(juce::Thread *deadThread)
{}

bool PILS::NPPilsCommander::execute(const juce::String &commandLine)
{
	if (!commandLineHandler)
		commandLineHandler = getCommandLineHandler();
	return executeCommandLine(commandLine);
}

PILS::NPPilsCommander::~NPPilsCommander()
{
	Heap::shutdown();
}

void PILS::NPPilsCommander::shutdown()
{
	if (commandLineHandler)
	{
		MainThread::singleton->doPending();
		MainThread::singleton->where_ = commandLineHandler;
		commandLineHandler = NULL;
		MainThread::singleton->releaseReference();
		MainThread::singleton = NULL;
	}
}
