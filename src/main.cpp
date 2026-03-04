#include <juce_gui_basics/juce_gui_basics.h>

class MainWindow : public juce::DocumentWindow
{
public:
    MainWindow() : DocumentWindow("Pils",
                                   juce::Colours::lightgrey,
                                   DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new juce::Component(), true);
        centreWithSize(600, 400);
        setVisible(true);
    }

    void closeButtonPressed() override
    {
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

class PilsApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Pils"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new MainWindow());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(PilsApplication)

