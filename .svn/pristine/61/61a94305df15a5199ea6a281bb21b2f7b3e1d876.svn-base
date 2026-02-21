/* This file is public domain, except the CodeEditorComponent which is a molested version of the Juce class and inherits its licensing terms.*/
#ifndef _JPILS_SUPPLEMENT_H_
#define _JPILS_SUPPLEMENT_H_

#include "pils-kernel/writing.h"
#include "jpils-thread.h"
#include <juce.h>

/* Additions to juce */

BEGIN_JUCE_NAMESPACE

class mixin__Component : public DragAndDropTarget, public FileDragAndDropTarget
{
public:
	bool isInterestedInDragSource(const SourceDetails& dragSourceDetails) {return false;}
	void itemDropped(const SourceDetails& dragSourceDetails) {}
	bool isInterestedInFileDrag(const StringArray &files) {return false;}
	void filesDropped(const StringArray &files, int, int) {}
};

class mixin__TopLevelWindow : public mixin__Component, public DragAndDropContainer
{
};

class pils__TreeViewItem;
class pils__TreeView
	: public TreeView
{
public:
	pils__TreeView(const String &componentName = String::empty);
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
	pils__TreeViewItem() : mind(NULL) {}
	~pils__TreeViewItem();
	pils__TreeViewItem *getSubItem(const int index) const throw();
	pils__TreeViewItem *getParentItem() const throw ();
    pils__TreeViewItem *addSubItem(const int insertPosition = -1);
	const PILS::Constant *getMind();
	void setMind(const PILS::Constant *value);
private:
	friend class pils__TreeView;
	virtual bool mightContainSubItems();
	virtual const String getUniqueName() const;
	virtual void itemOpennessChanged(bool isNowOpen);
	virtual int getItemWidth() const;
	virtual int getItemHeight() const;
	virtual Component *createItemComponent();
	virtual void paintItem(Graphics &g, int width, int height);
	virtual void itemClicked(const MouseEvent &e);
	virtual void itemDoubleClicked(const MouseEvent &e);
	virtual void itemSelectionChanged(bool isNowSelected);
	virtual const var getDragSourceDescription();
	const PILS::Constant *mind;
};

class pils__MenuBarModel
	: public MenuBarModel
{
protected:
	pils__MenuBarModel()
	{}

public:
	/* dummy implementations of abstract methods */
	const StringArray getMenuBarNames(){return StringArray();}
	const PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName){return PopupMenu();}
	virtual void menuItemSelected(int menuItemID, int topLevelMenuIndex){}
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
		setMenuBar(NULL, 0);
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
		setMenuBar(NULL, 0);
	}

	MenuBarComponent *getMenuBar() {return pils__DocumentWindow::getMenuBar(this);}
	void setIcon(const Image &imageToUse);

	juce_UseDebuggingNewOperator
};

class pils__ListBox
	: public ListBox, public ListBoxModel
{
public:
	pils__ListBox(const String &componentName = String::empty) throw ()
		: ListBox(componentName, NULL)
	{
		setModel(this);
	}
	~pils__ListBox(){
		setModel(NULL);
	}
	/* dummy implementations of abstract methods */
	int getNumRows(){return 0;}
	void paintListBoxItem(int rowNumber, Graphics &g, int width, int height, bool rowIsSelected){}
	juce_UseDebuggingNewOperator
};

class pils__TableListBox
	: public TableListBox, public TableListBoxModel
{
public:
	pils__TableListBox(const String &componentName = String::empty) throw ()
		: TableListBox(componentName, NULL)
	{
		setModel(this);
	}
	~pils__TableListBox()
	{
		setModel(NULL);
	}
	/* dummy implementations of abstract methods */
	int getNumRows(){return 0;}
	void paintRowBackground(Graphics &g, int rowNumber, int width, int height, bool rowIsSelected){}
	void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected){}
 	juce_UseDebuggingNewOperator
};

class pils__TextEditor
	: public TextEditor, public TextEditorListener
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
	void textEditorTextChanged(TextEditor &){}
	void textEditorReturnKeyPressed(TextEditor &){}
	void textEditorEscapeKeyPressed(TextEditor &){}
	void textEditorFocusLost(TextEditor &){}
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
	const PILS::Constant *getData()
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
	const PILS::Constant *getData()
	{
		return PILS::PilsString::get((const PILS_CHAR *)MemoryOutputStream::getData(), getDataSize());
	}
};

class pils__Timer
	: public Timer
{
public:
	pils__Timer() throw () {}
	void timerCallback() {}
};

class pils__FileBrowserListener
	: public FileBrowserListener
{
public:
	pils__FileBrowserListener() throw () {}
	void selectionChanged() {}
	void fileClicked(const File &file, const MouseEvent &e) {}
	void fileDoubleClicked(const File &file) {}
};

class pils__BooleanPropertyComponent
	: public BooleanPropertyComponent
{
public:
	pils__BooleanPropertyComponent(const String &propertyName, const String &buttonTextWhenTrue, const String &buttonTextWhenFalse, bool value = false)
		: BooleanPropertyComponent(propertyName, buttonTextWhenTrue, buttonTextWhenFalse), value(value)
	{}
	void setState (const bool newState) {value = newState;}
	bool getState () const {return value;}
private:
	bool value;
};

class pils__OpenGLComponent
	: public OpenGLComponent
{
public:
	pils__OpenGLComponent() {}
	void newOpenGLContextCreated() {}
	void renderOpenGL() {}
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

    void insertTextAtCaret (const String& textToInsert);
    void insertTabAtCaret();
    const Range<int> getHighlightedRegion() const;
    void setHighlightedRegion (const Range<int>& newRange);
    const String getTextInRange (const Range<int>& range) const;
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
    void resized();
    void paint (Graphics& g);
    bool keyPressed (const KeyPress& key);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent& e);
    void mouseDoubleClick (const MouseEvent& e);
    void mouseWheelMove (const MouseEvent& e, float wheelIncrementX, float wheelIncrementY);
    void focusGained (FocusChangeType cause);
    void focusLost (FocusChangeType cause);
    void timerCallback();
    void scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart);
    void handleAsyncUpdate();
    void codeDocumentChanged (const CodeDocument::Position& affectedTextStart,
                              const CodeDocument::Position& affectedTextEnd);
    bool isTextInputActive() const;
    void setTemporaryUnderlining (const Array <Range<int> >&);

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

    ScopedPointer<CaretComponent> caret;
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
    ~PilsCodeTokeniser();

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
    int readNextToken (CodeDocument::Iterator& source);
    StringArray getTokenTypes();
    const Colour getDefaultColour (int tokenType);

private:
    //==============================================================================
    JUCE_LEAK_DETECTOR (PilsCodeTokeniser);
};


END_JUCE_NAMESPACE
#endif
