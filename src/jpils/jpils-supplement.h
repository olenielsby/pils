/* This file is public domain, except the CodeEditorComponent which is a molested version of the Juce class and inherits its licensing terms.*/
#ifndef _JPILS_SUPPLEMENT_H_
#define _JPILS_SUPPLEMENT_H_

#include "writing.h"
#include "jpils-thread.h"
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_formats/juce_audio_formats.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <juce_core/juce_core.h>
#include <juce_cryptography/juce_cryptography.h>

/* Additions to juce */

// BEGIN_JUCE_NAMESPACE
namespace juce
{

class mixin__Component : public DragAndDropTarget, public FileDragAndDropTarget
{
public:
    bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) override {return false;}
    void itemDropped(const SourceDetails& dragSourceDetails) override {}
    bool isInterestedInFileDrag(const StringArray &files) override {return false;}
    void filesDropped(const StringArray &files, int, int) override {}
};

class mixin__TopLevelWindow : public mixin__Component, public DragAndDropContainer
{
};

class pils__TreeViewItem;
class pils__TreeView
	: public TreeView
{
public:
//	pils__TreeView(const String &componentName = String::empty);
    pils__TreeView(const String &componentName = {});
    ~pils__TreeView();
	pils__TreeViewItem *getRootItem() const throw ();
	pils__TreeViewItem *newRootItem() throw ();
	void clear() throw ();
    virtual bool mightContainSubItems(pils__TreeViewItem &item);
    virtual const String getUniqueName(const pils__TreeViewItem &item);
    virtual void itemOpennessChanged(pils__TreeViewItem &item, bool isNowOpen);
    virtual int getItemWidth(const pils__TreeViewItem &item);
    virtual int getItemHeight(const pils__TreeViewItem &item);
    virtual Component *createItemComponent(pils__TreeViewItem &item);
    virtual void paintItem(pils__TreeViewItem &item, Graphics &g, int width, int height);
    virtual void itemClicked(pils__TreeViewItem &item, const MouseEvent &e);
    virtual void itemDoubleClicked(pils__TreeViewItem &item, const MouseEvent &e);
    virtual void itemSelectionChanged(pils__TreeViewItem &item, bool isNowSelected);
    virtual const String getDragSourceDescription(pils__TreeViewItem &item);
};

class pils__TreeViewItem
	: public TreeViewItem
{
public:
	pils__TreeViewItem() : mind(nullptr) {}
	~pils__TreeViewItem();
	pils__TreeViewItem *getSubItem(const int index) const throw();
	pils__TreeViewItem *getParentItem() const throw ();
    pils__TreeViewItem *addSubItem(const int insertPosition = -1);
	const PILS::HalfbakedConstant *getMind();
	void setMind(const PILS::HalfbakedConstant *value);
private:
	friend class pils__TreeView;
    bool mightContainSubItems() override;
    String getUniqueName() const override;
    void itemOpennessChanged(bool isNowOpen) override;
    int getItemWidth() const override;
    int getItemHeight() const override;
    std::unique_ptr<Component> createItemComponent() override;
    void paintItem(Graphics &g, int width, int height) override;
    void itemClicked(const MouseEvent &e) override;
    void itemDoubleClicked(const MouseEvent &e) override;
    void itemSelectionChanged(bool isNowSelected) override;
    var getDragSourceDescription() override;
	const PILS::HalfbakedConstant *mind;
};

class pils__MenuBarModel
	: public MenuBarModel
{
protected:
	pils__MenuBarModel()
	{}

public:
	/* dummy implementations of abstract methods */
    // const StringArray getMenuBarNames(){return StringArray();}
    StringArray getMenuBarNames() override {return {};}

    // const PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName){return P;}
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName) override {return {};}
    virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex) override {}
};

class pils__Component
	: public Component
{
public:
	pils__Component() throw () {}
	pils__Component(const String &componentName) throw () : Component(componentName) {}
	~pils__Component()
	{
		deleteAllChildren();
	}
};

class pils__DocumentWindow
	: public DocumentWindow, public pils__MenuBarModel
{
public:
	pils__DocumentWindow(const String &name, const Colour &backgroundColour, const int requiredButtons) throw ()
		: DocumentWindow(name, backgroundColour, requiredButtons, true)
	{}

	~pils__DocumentWindow()
	{
		setMenuBar(nullptr, 0);
	}

	MenuBarComponent *getMenuBar() {return getMenuBar(this);}
	void setIcon(const Image &imageToUse);

	juce_UseDebuggingNewOperator
private:
	friend class pils__DialogWindow;
	static MenuBarComponent *getMenuBar(DocumentWindow *documentWindow);
};

class pils__DialogWindow
	: public DialogWindow, public pils__MenuBarModel
{
public:
	pils__DialogWindow(const String &name, const Colour &backgroundColour, const bool escapeKeyTriggersCloseButton) throw ()
		: DialogWindow(name, backgroundColour, escapeKeyTriggersCloseButton, true)
	{}

	~pils__DialogWindow()
	{
		setMenuBar(nullptr, 0);
	}

	MenuBarComponent *getMenuBar() {return pils__DocumentWindow::getMenuBar(this);}
	void setIcon(const Image &imageToUse);

	juce_UseDebuggingNewOperator
};

class pils__ListBox
	: public ListBox, public ListBoxModel
{
public:
    pils__ListBox(const String &componentName = {}) throw ()
		: ListBox(componentName, nullptr)
	{
		setModel(this);
	}
	~pils__ListBox(){
		setModel(nullptr);
	}
	/* dummy implementations of abstract methods */
    int getNumRows() override {return 0;}
    void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected) override {}
	juce_UseDebuggingNewOperator
};

class pils__TableListBox
	: public TableListBox, public TableListBoxModel
{
public:
    pils__TableListBox(const String &componentName = {}) throw ()
		: TableListBox(componentName, nullptr)
	{
		setModel(this);
	}
	~pils__TableListBox()
	{
		setModel(nullptr);
	}
	/* dummy implementations of abstract methods */
    int getNumRows() override {return 0;}
    void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected) override {}
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override {}
 	juce_UseDebuggingNewOperator
};

class pils__TextEditor
    : public TextEditor, public TextEditor::Listener
{
public:
	pils__TextEditor()
	{
		this->addListener(this);
	}
	~pils__TextEditor()
	{
		this->removeListener(this);
	}
protected:
    void textEditorTextChanged(TextEditor &) override {}
    void textEditorReturnKeyPressed(TextEditor &) override {}
    void textEditorEscapeKeyPressed(TextEditor &) override {}
    void textEditorFocusLost(TextEditor &) override {}
};

class pils__TabBarButton
	: public TabBarButton
{
public:
	pils__TabBarButton(const String &name, TabbedButtonBar &ownerBar)
		: TabBarButton(name, ownerBar)
	{}
};

class pils__GroupComponent
	: public GroupComponent
{
public:
	pils__GroupComponent(const String &componentName, const String &labelText)
		: GroupComponent(componentName, labelText)
	{}

	~pils__GroupComponent()
	{
		deleteAllChildren();
	}
};

class pils__MemoryBlock
	: public MemoryBlock
{
public:
	pils__MemoryBlock() throw ()
	{}
	pils__MemoryBlock(const int  initialSize, const bool  initialiseToZero = false) throw ()
		: MemoryBlock(initialSize, initialiseToZero)
	{}
	pils__MemoryBlock(const void *const dataToInitialiseFrom, const int sizeInBytes) throw ()
		: MemoryBlock(dataToInitialiseFrom, sizeInBytes)
	{}
	const PILS::HalfbakedConstant *getData()
	{
		return PILS::PilsString::get((const PILS_CHAR *)MemoryBlock::getData(), getSize());
	}
};

class pils__MemoryOutputStream
	: public MemoryOutputStream
{
public:
	pils__MemoryOutputStream(const int initialSize=256) throw ()
		: MemoryOutputStream(initialSize)
	{}
	pils__MemoryOutputStream(MemoryBlock &memoryBlockToWriteTo, bool appendToExistingBlockContent) throw ()
		: MemoryOutputStream(memoryBlockToWriteTo, appendToExistingBlockContent)
	{}
	~pils__MemoryOutputStream() throw () {}
	const PILS::HalfbakedConstant *getData()
	{
		return PILS::PilsString::get((const PILS_CHAR *)MemoryOutputStream::getData(), getDataSize());
	}
};

class pils__Timer
	: public Timer
{
public:
	pils__Timer() throw () {}
    void timerCallback() override {}
};

class pils__FileBrowserListener
	: public FileBrowserListener
{
public:
	pils__FileBrowserListener() throw () {}
    void selectionChanged() override {}
    void fileClicked(const File &file, const MouseEvent &e) override {}
    void fileDoubleClicked(const File &file) override {}
};

class pils__BooleanPropertyComponent
	: public BooleanPropertyComponent
{
public:
	pils__BooleanPropertyComponent(const String &propertyName, const String &buttonTextWhenTrue, const String &buttonTextWhenFalse, bool value = false)
		: BooleanPropertyComponent(propertyName, buttonTextWhenTrue, buttonTextWhenFalse), value(value)
	{}
    void setState (const bool newState) override {value = newState;}
    bool getState () const override {return value;}
private:
	bool value;
};

class Convert
{
public:
	static DrawableComposite *drawableComposite(Drawable *drawable) {return dynamic_cast<DrawableComposite*>(drawable);}
	static DrawableImage *drawableImage(Drawable *drawable) {return dynamic_cast<DrawableImage*>(drawable);}
	static DrawablePath *drawablePath(Drawable *drawable) {return dynamic_cast<DrawablePath*>(drawable);}
	static DrawableText *drawableText(Drawable *drawable) {return dynamic_cast<DrawableText*>(drawable);}
//	static GradientBrush *gradientBrush(Brush *brush) {return dynamic_cast<GradientBrush*>(brush);}
//	static ImageBrush *imageBrush(Brush *brush) {return dynamic_cast<ImageBrush*>(brush);}
//	static SolidColourBrush *solidColourBrush(Brush *brush) {return dynamic_cast<SolidColourBrush*>(brush);}
};

// MOLESTED VERSION OF JUCE code
// Will be removed when/if the JUCE CodeEditorComponent
// gets proportional-spaced-font enabled

class JUCE_API  molested__CodeEditorComponent: public Component,
                                        public TextInputTarget,
                                        public Timer,
                                        public ScrollBar::Listener,
                                        public CodeDocument::Listener,
                                        public AsyncUpdater
{
public:
    molested__CodeEditorComponent (CodeDocument& document,
                         CodeTokeniser* codeTokeniser);
    ~molested__CodeEditorComponent();
    CodeDocument& getDocument() const noexcept          { return document; }
    void loadContent (const String& newContent);
    float getCharWidth() const noexcept                         { return charWidth; }
    int getLineHeight() const noexcept                          { return lineHeight; }
    int getNumLinesOnScreen() const noexcept                    { return linesOnScreen; }
    int getNumColumnsOnScreen() const noexcept                  { return columnsOnScreen; }
    const CodeDocument::Position getCaretPos() const            { return caretPos; }
    const Rectangle<int> getCaretRectangle();
    void moveCaretTo (const CodeDocument::Position& newPos, bool selecting);
    const Rectangle<int> getCharacterBounds (const CodeDocument::Position& pos) const;
    const CodeDocument::Position getPositionAt (int x, int y);
    bool moveCaretLeft (bool moveInWholeWordSteps, bool selecting);
    bool moveCaretRight (bool moveInWholeWordSteps, bool selecting);
    bool moveCaretUp (bool selecting);
    bool moveCaretDown (bool selecting);
    bool scrollDown();
    bool scrollUp();
    bool pageUp (bool selecting);
    bool pageDown (bool selecting);
    bool moveCaretToTop (bool selecting);
    bool moveCaretToStartOfLine (bool selecting);
    bool moveCaretToEnd (bool selecting);
    bool moveCaretToEndOfLine (bool selecting);
    bool deleteBackwards (bool moveInWholeWordSteps);
    bool deleteForwards (bool moveInWholeWordSteps);
    bool copyToClipboard();
    bool cutToClipboard();
    bool pasteFromClipboard();
    bool undo();
    bool redo();

    bool selectAll();
    void deselectAll();

    void scrollToLine (int newFirstLineOnScreen);
    void scrollBy (int deltaLines);
    void scrollToColumn (int newFirstColumnOnScreen);
    void scrollToKeepCaretOnScreen();

    void insertTextAtCaret (const String& textToInsert) override;
    void insertTabAtCaret();
    //    const Range<int> getHighlightedRegion() const override;
    Range<int> getHighlightedRegion() const override;
    void setHighlightedRegion (const Range<int>& newRange) override;
    // const String getTextInRange (const Range<int>& range) const override;
    String getTextInRange (const Range<int>& range) const override;
    void setTabSize (int numSpacesPerTab, bool insertSpacesInsteadOfTabCharacters);
    int getTabSize() const noexcept                     { return spacesPerTab; }
    bool areSpacesInsertedForTabs() const               { return useSpacesForTabs; }
    void setFont (const Font& newFont);
    const Font& getFont() const noexcept                { return font; }
    void resetToDefaultColours();
    void setColourForTokenType (int tokenType, const Colour& colour);
    const Colour getColourForTokenType (int tokenType) const;
    enum ColourIds
    {
        backgroundColourId          = 0x1004500,
        highlightColourId           = 0x1004502,
        defaultTextColourId         = 0x1004503
    };
    void setScrollbarThickness (int thickness);
    int getScrollbarThickness() const noexcept          { return scrollbarThickness; }
    void resized() override;
    void paint (Graphics& g) override;
    bool keyPressed (const KeyPress& key) override;
    void mouseDown (const MouseEvent& e) override;
    void mouseDrag (const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    void mouseDoubleClick (const MouseEvent& e) override;
    void mouseWheelMove (const MouseEvent& e, const MouseWheelDetails& wheel) override;
    void focusGained (FocusChangeType cause) override;
    void focusLost (FocusChangeType cause) override;
    void timerCallback() override;
    void scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart) override;
    void handleAsyncUpdate() override;
    void codeDocumentChanged (const CodeDocument::Position& affectedTextStart,
                              const CodeDocument::Position& affectedTextEnd);
    bool isTextInputActive() const override;
    void setTemporaryUnderlining (const Array <Range<int> >&) override;

private:
    CodeDocument& document;

    Font font;
    int firstLineOnScreen, gutter, spacesPerTab;
    float charWidth;
    int lineHeight, linesOnScreen, columnsOnScreen;
    int scrollbarThickness, columnToTryToMaintain;
    bool useSpacesForTabs;
    double xOffset;

    CodeDocument::Position caretPos;
    CodeDocument::Position selectionStart, selectionEnd;

    std::unique_ptr<CaretComponent> caret;
    ScrollBar verticalScrollBar, horizontalScrollBar;

    enum DragType
    {
        notDragging,
        draggingSelectionStart,
        draggingSelectionEnd
    };

    DragType dragType;
    CodeTokeniser* codeTokeniser;
    Array <Colour> coloursForTokenCategories;

    class CodeEditorLine;
    OwnedArray <CodeEditorLine> lines;
    void rebuildLineTokens();

    OwnedArray <CodeDocument::Iterator> cachedIterators;
    void clearCachedIterators (int firstLineToBeInvalid);
    void updateCachedIterators (int maxLineNum);
    void getIteratorForPosition (int position, CodeDocument::Iterator& result);
    void moveLineDelta (int delta, bool selecting);
    void updateCaretPosition();
    void updateScrollBars();
    void scrollToLineInternal (int line);
    void scrollToColumnInternal (double column);
    void newTransaction();
    void cut();

    int indexToColumn (int line, int index) const noexcept;
    int columnToIndex (int line, int column) const noexcept;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (molested__CodeEditorComponent);
};
// END OF MOLESTED JUCE FILE

class pils__CodeEditorComponent
	: public molested__CodeEditorComponent
{
public:
	pils__CodeEditorComponent(CodeDocument &document, CodeTokeniser *tokeniser)
		: molested__CodeEditorComponent(*new CodeDocument(), tokeniser)
	{
		getDocument().setNewLineCharacters("\n");
	}
	~pils__CodeEditorComponent()
	{
		new PendingDocument(&getDocument());
	}
    void codeDocumentChanged (const CodeDocument::Position& affectedTextStart,
                              const CodeDocument::Position& affectedTextEnd)
	{
		molested__CodeEditorComponent::codeDocumentChanged(affectedTextStart, affectedTextEnd);
		codeDocumentEditorTextChanged();
	}
	virtual void codeDocumentEditorTextChanged() {}
	int getHighlightedRegionStart()
	{
		return getHighlightedRegion().getStart();
	}
	int getHighlightedRegionEnd()
	{
		return getHighlightedRegion().getEnd();
	}
private:
	class PendingDocument: PILS::Pending
	{
	public:
		PendingDocument(CodeDocument *gone_) : Pending(*PILS::MainThread::singleton), gone_(gone_) {}
		~PendingDocument()
		{
			delete gone_;
		}
	private:
		CodeDocument *gone_;
	};
};

class JUCE_API  PilsCodeTokeniser    : public CodeTokeniser
{
public:
    //==============================================================================
    PilsCodeTokeniser();
    ~PilsCodeTokeniser() override;

    //==============================================================================
    enum TokenType
    {
        tokenType_error = 0,
        tokenType_comment,
        tokenType_identifier,
        tokenType_number,
        tokenType_string,
        tokenType_operator,
        tokenType_bracket,
        tokenType_punctuation
    };

    //==============================================================================
    int readNextToken (CodeDocument::Iterator& source) override;
    //StringArray getTokenTypes() override;
    //const Colour getDefaultColour (int tokenType) override;
    CodeEditorComponent::ColourScheme getDefaultColourScheme() override;
private:
    //==============================================================================
    JUCE_LEAK_DETECTOR (PilsCodeTokeniser);
};


} // END_JUCE_NAMESPACE
#endif
