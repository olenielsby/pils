/* This file is public domain except the molested_CodeEditorComponent which inherits the Juce licensing terms */
#ifdef _WIN32
 #include <windows.h>
#endif

#include "jpils-supplement.h"

// #ifdef _WIN32
//  #include <gl/gl.h>
//  #include <gl/glu.h>
// #elif defined (LINUX)
//  #include <GL/gl.h>
//  #include <GL/glut.h>
//  #undef KeyPress
// #else
//  #include <GLUT/glut.h>
// #endif

namespace juce {

MenuBarComponent *pils__DocumentWindow::getMenuBar(DocumentWindow *documentWindow)
{
	for (int i = 0; i < documentWindow->getNumChildComponents(); i++)
		if (MenuBarComponent *menuBar = dynamic_cast<MenuBarComponent *>(documentWindow->getChildComponent(i)))
			return menuBar;
	return nullptr;
}

void pils__DocumentWindow::setIcon(const Image &imageToUse)
{
	DocumentWindow::setIcon(imageToUse);
#ifdef JUCE_WIN32
	ComponentPeer *peer = getPeer();
	if (peer)
		peer->setIcon(imageToUse);
#endif
}

void pils__DialogWindow::setIcon(const Image &imageToUse)
{
	DocumentWindow::setIcon(imageToUse);
#ifdef JUCE_WIN32
	ComponentPeer *peer = getPeer();
	if (peer)
		peer->setIcon(imageToUse);
#endif
}

pils__TreeView::pils__TreeView(const juce::String &componentName)
	: TreeView(componentName)
{}

pils__TreeView::~pils__TreeView()
{
    TreeViewItem* const root = TreeView::getRootItem();
	TreeView::setRootItem(0);
    delete root;
}

pils__TreeViewItem *pils__TreeView::getRootItem() const throw ()
{
	return static_cast<pils__TreeViewItem *>(TreeView::getRootItem());
}

pils__TreeViewItem *pils__TreeView::newRootItem() throw ()
{
	pils__TreeViewItem *oldRoot = getRootItem();
	pils__TreeViewItem *newRoot = new pils__TreeViewItem();
	TreeView::setRootItem(newRoot);
	delete oldRoot;
	return newRoot;
}

void pils__TreeView::clear() throw ()
{
	pils__TreeViewItem *oldRoot = getRootItem();
	TreeView::setRootItem(nullptr);
	delete oldRoot;
}

Component *pils__TreeView::createItemComponent(pils__TreeViewItem &)
{
	return nullptr;
}

const String pils__TreeView::getDragSourceDescription(pils__TreeViewItem &)
{
    return {};
}

int pils__TreeView::getItemHeight(const pils__TreeViewItem &)
{
	return 20;
}

int pils__TreeView::getItemWidth(const pils__TreeViewItem &)
{
	return -1;
}

const String pils__TreeView::getUniqueName(const pils__TreeViewItem &)
{
//	return String::empty;
    return {};
}

void pils__TreeView::paintItem(pils__TreeViewItem &item, Graphics&, int, int)
{}

void pils__TreeView::itemClicked(pils__TreeViewItem &item, const MouseEvent&)
{}

void pils__TreeView::itemDoubleClicked(pils__TreeViewItem &item, const MouseEvent&)
{
    if (item.mightContainSubItems())
        item.setOpen(!item.isOpen());
}

void pils__TreeView::itemSelectionChanged(pils__TreeViewItem &item, bool)
{}

void pils__TreeView::itemOpennessChanged(pils__TreeViewItem &item, bool)
{}

bool pils__TreeView::mightContainSubItems(pils__TreeViewItem &item)
{
	return item.getNumSubItems() != 0;
}

pils__TreeViewItem::~pils__TreeViewItem()
{
	if (mind) mind->releaseReference();
}

pils__TreeViewItem *pils__TreeViewItem::addSubItem(const int insertPosition)
{
	pils__TreeViewItem *newItem = new pils__TreeViewItem();
	TreeViewItem::addSubItem(newItem, insertPosition);
	return newItem;
}

const PILS::HalfbakedConstant *pils__TreeViewItem::getMind()
{
	if (mind) mind->addReference();
	return mind;
}

void pils__TreeViewItem::setMind(const PILS::HalfbakedConstant *value)
{
	value->addReference();
	if (mind) mind->releaseReference();
	mind = value;
}

pils__TreeViewItem *pils__TreeViewItem::getParentItem() const throw ()
{
	return static_cast<pils__TreeViewItem *>(TreeViewItem::getParentItem());
}

pils__TreeViewItem *pils__TreeViewItem::getSubItem(const int index) const throw ()
{
	return static_cast<pils__TreeViewItem *>(TreeViewItem::getSubItem(index));
}

bool pils__TreeViewItem::mightContainSubItems()
{
    return static_cast<pils__TreeView *>(getOwnerView())->mightContainSubItems(*this);
}

void pils__TreeViewItem::itemOpennessChanged(bool isNowOpen)
{
    static_cast<pils__TreeView *>(getOwnerView())->itemOpennessChanged(*this, isNowOpen);
}

std::unique_ptr<Component> pils__TreeViewItem::createItemComponent()
{
    return std::unique_ptr<Component>(static_cast<pils__TreeView *>(getOwnerView())->createItemComponent(*this));
}

void pils__TreeViewItem::paintItem(Graphics &g, int width, int height)
{
    static_cast<pils__TreeView *>(getOwnerView())->paintItem(*this, g, width, height);
}

void pils__TreeViewItem::itemClicked(const MouseEvent &e)
{
    static_cast<pils__TreeView *>(getOwnerView())->itemClicked(*this, e);
}

void pils__TreeViewItem::itemDoubleClicked(const MouseEvent &e)
{
    static_cast<pils__TreeView *>(getOwnerView())->itemDoubleClicked(*this, e);
}

void pils__TreeViewItem::itemSelectionChanged(bool isNowSelected)
{
    static_cast<pils__TreeView *>(getOwnerView())->itemSelectionChanged(*this, isNowSelected);
}

var pils__TreeViewItem::getDragSourceDescription()
{
    return static_cast<pils__TreeView *>(getOwnerView())->getDragSourceDescription(*this);
}

String pils__TreeViewItem::getUniqueName() const
{
    return static_cast<pils__TreeView *>(getOwnerView())->getUniqueName(*this);
}

int pils__TreeViewItem::getItemHeight() const
{
    return static_cast<pils__TreeView *>(getOwnerView())->getItemHeight(*this);
}

int pils__TreeViewItem::getItemWidth() const
{
    return static_cast<pils__TreeView *>(getOwnerView())->getItemWidth(*this);
}



/*
  ==============================================================================

   This file is a molested version of part of the JUCE library
   - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

   Don't use it for anything except compiling PILS with the proportional-font
   enabled CodeEditorComponent replacement class.

  ==============================================================================
*/

//#include "../../../core/juce_StandardHeader.h"

//BEGIN_JUCE_NAMESPACE

//#include "juce_CodeEditorComponent.h"
//#include "../lookandfeel/juce_LookAndFeel.h"
//#include "../keyboard/juce_TextEditorKeyMapper.h"
//#include "../../../utilities/juce_SystemClipboard.h"


//==============================================================================
class molested__CodeEditorComponent::CodeEditorLine
{
public:
    CodeEditorLine() noexcept
       : highlightColumnStart (0), highlightColumnEnd (0)
    {
    }

    bool update (CodeDocument& document, int lineNum,
                 CodeDocument::Iterator& source,
                 CodeTokeniser* analyser, const int spacesPerTab,
                 const CodeDocument::Position& selectionStart,
                 const CodeDocument::Position& selectionEnd)
    {
        Array <SyntaxToken> newTokens;
        newTokens.ensureStorageAllocated (8);

        if (analyser == nullptr)
        {
            newTokens.add (SyntaxToken (document.getLine (lineNum), -1));
        }
        else if (lineNum < document.getNumLines())
        {
            const CodeDocument::Position pos (document, lineNum);
            createTokens (pos.getPosition(), pos.getLineText(),
                          source, analyser, newTokens);
        }

        replaceTabsWithSpaces (newTokens, spacesPerTab);

        int newHighlightStart = 0;
        int newHighlightEnd = 0;

        if (selectionStart.getLineNumber() <= lineNum && selectionEnd.getLineNumber() >= lineNum)
        {
            const String line (document.getLine (lineNum));

            CodeDocument::Position lineStart (document, lineNum, 0), lineEnd (document, lineNum + 1, 0);
            newHighlightStart = indexToColumn (jmax (0, selectionStart.getPosition() - lineStart.getPosition()),
                                               line, spacesPerTab);
            newHighlightEnd = indexToColumn (jmin (lineEnd.getPosition() - lineStart.getPosition(), selectionEnd.getPosition() - lineStart.getPosition()),
                                             line, spacesPerTab);
        }

        if (newHighlightStart != highlightColumnStart || newHighlightEnd != highlightColumnEnd)
        {
            highlightColumnStart = newHighlightStart;
            highlightColumnEnd = newHighlightEnd;
        }
        else
        {
            if (tokens.size() == newTokens.size())
            {
                bool allTheSame = true;

                for (int i = newTokens.size(); --i >= 0;)
                {
                    if (tokens.getReference(i) != newTokens.getReference(i))
                    {
                        allTheSame = false;
                        break;
                    }
                }

                if (allTheSame)
                    return false;
            }
        }

        tokens.swapWithArray (newTokens);
        return true;
    }

    void draw (molested__CodeEditorComponent& owner, Graphics& g, const Font& font,
               float x, const int y, const int baselineOffset, const int lineHeight,
               const Colour& highlightColour) const
    {
        if (highlightColumnStart < highlightColumnEnd)
        {
            g.setColour (highlightColour);
//beginchange
//remove:
//            g.fillRect (roundToInt (x + highlightColumnStart * owner.getCharWidth()), y,
//                        roundToInt ((highlightColumnEnd - highlightColumnStart) * owner.getCharWidth()), lineHeight);
//insert:
            float xStart = 0;
            float xEnd = 0;
			int col = 0;
			for (int i = 0; i < tokens.size() /*&& col < highlightColumnEnd*/; ++i)
			{
				// Walk through tokens, add widths as needed to xStart, xEnd
                const SyntaxToken & token = tokens.getReference(i);
                if (token.width < 0)
                    token.width = font.getStringWidthFloat (token.text);
				int nextCol = col + token.text.length();

				if (nextCol <= highlightColumnStart)
				{
					xStart += token.width;
				}
				else if (col < highlightColumnStart)
				{
					xStart += font.getStringWidthFloat(token.text.substring(0, highlightColumnStart - col));
				}

				if (nextCol <= highlightColumnEnd)
				{
					xEnd += token.width;
				}
				else if (col < highlightColumnEnd)
				{
					xEnd += font.getStringWidthFloat(token.text.substring(0, highlightColumnEnd - col));
				}
				col = nextCol;
			}
			// Excess marking when a linefeed is included
			if (highlightColumnEnd == col)
			{
				xEnd += owner.getCharWidth();
			}

            g.fillRect (roundToInt (x + xStart), y, roundToInt (xEnd - xStart), lineHeight);
//endchange
        }

        int lastType = std::numeric_limits<int>::min();

        for (int i = 0; i < tokens.size(); ++i)
        {
            const SyntaxToken& token = tokens.getReference(i);

            if (lastType != token.tokenType)
            {
                lastType = token.tokenType;
                g.setColour (owner.getColourForTokenType (lastType));
            }

            g.drawSingleLineText (token.text, roundToInt (x), y + baselineOffset);

            if (i < tokens.size() - 1)
            {
                if (token.width < 0)
                    token.width = font.getStringWidthFloat (token.text);

                x += token.width;
            }
        }
    }

private:
    struct SyntaxToken
    {
        SyntaxToken (const String& text_, const int type) noexcept
            : text (text_), tokenType (type), width (-1.0f)
        {
        }

        bool operator!= (const SyntaxToken& other) const noexcept
        {
            return text != other.text || tokenType != other.tokenType;
        }

        String text;
        int tokenType;
        mutable float width;
    };

    Array <SyntaxToken> tokens;
    int highlightColumnStart, highlightColumnEnd;

    static void createTokens (int startPosition, const String& lineText,
                              CodeDocument::Iterator& source,
                              CodeTokeniser* analyser,
                              Array <SyntaxToken>& newTokens)
    {
        CodeDocument::Iterator lastIterator (source);
        const int lineLength = lineText.length();

        for (;;)
        {
            int tokenType = analyser->readNextToken (source);
            int tokenStart = lastIterator.getPosition();
            int tokenEnd = source.getPosition();

            if (tokenEnd <= tokenStart)
                break;

            tokenEnd -= startPosition;

            if (tokenEnd > 0)
            {
                tokenStart -= startPosition;
                newTokens.add (SyntaxToken (lineText.substring (jmax (0, tokenStart), tokenEnd),
                                            tokenType));

                if (tokenEnd >= lineLength)
                    break;
            }

            lastIterator = source;
        }

        source = lastIterator;
    }

    static void replaceTabsWithSpaces (Array <SyntaxToken>& tokens, const int spacesPerTab)
    {
        int x = 0;
        for (int i = 0; i < tokens.size(); ++i)
        {
            SyntaxToken& t = tokens.getReference(i);

            for (;;)
            {
                int tabPos = t.text.indexOfChar ('\t');
                if (tabPos < 0)
                    break;

                const int spacesNeeded = spacesPerTab - ((tabPos + x) % spacesPerTab);
                t.text = t.text.replaceSection (tabPos, 1, String::repeatedString (" ", spacesNeeded));
            }

            x += t.text.length();
        }
    }

    int indexToColumn (int index, const String& line, int spacesPerTab) const noexcept
    {
        jassert (index <= line.length());

        String::CharPointerType t (line.getCharPointer());
        int col = 0;
        for (int i = 0; i < index; ++i)
        {
            if (t.getAndAdvance() != '\t')
                ++col;
            else
                col += spacesPerTab - (col % spacesPerTab);
        }

        return col;
    }
};

//==============================================================================
molested__CodeEditorComponent::molested__CodeEditorComponent (CodeDocument& document_,
                                          CodeTokeniser* const codeTokeniser_)
    : document (document_),
      firstLineOnScreen (0),
      gutter (5),
      spacesPerTab (4),
      lineHeight (0),
      linesOnScreen (0),
      columnsOnScreen (0),
      scrollbarThickness (16),
      columnToTryToMaintain (-1),
      useSpacesForTabs (false),
      xOffset (0),
      verticalScrollBar (true),
      horizontalScrollBar (false),
      codeTokeniser (codeTokeniser_),
    caret (std::unique_ptr<CaretComponent>(getLookAndFeel().createCaretComponent (this)))
{
    caretPos = CodeDocument::Position (document_, 0);
    caretPos.setPositionMaintained (true);

    selectionStart = CodeDocument::Position (document_, 0, 0);
    selectionStart.setPositionMaintained (true);

    selectionEnd = CodeDocument::Position (document_, 0, 0);
    selectionEnd.setPositionMaintained (true);

    setOpaque (true);
    setMouseCursor (MouseCursor (MouseCursor::IBeamCursor));
    setWantsKeyboardFocus (true);

    addAndMakeVisible (&verticalScrollBar);
    verticalScrollBar.setSingleStepSize (1.0);

    addAndMakeVisible (&horizontalScrollBar);
    horizontalScrollBar.setSingleStepSize (1.0);
    addAndMakeVisible (caret.get());

    Font f (12.0f);
    f.setTypefaceName (Font::getDefaultMonospacedFontName());
    setFont (f);

    resetToDefaultColours();

    verticalScrollBar.addListener (this);
    horizontalScrollBar.addListener (this);
    document.addListener (this);
}

molested__CodeEditorComponent::~molested__CodeEditorComponent()
{
    document.removeListener (this);
}

void molested__CodeEditorComponent::loadContent (const String& newContent)
{
    clearCachedIterators (0);
    document.replaceAllContent (newContent);
    document.clearUndoHistory();
    document.setSavePoint();
    caretPos.setPosition (0);
    selectionStart.setPosition (0);
    selectionEnd.setPosition (0);
    scrollToLine (0);
}

bool molested__CodeEditorComponent::isTextInputActive() const
{
    return true;
}

void molested__CodeEditorComponent::setTemporaryUnderlining (const Array <Range<int> >&)
{
    jassertfalse; // TODO Windows IME not yet supported for this comp..
}

const Rectangle<int> molested__CodeEditorComponent::getCaretRectangle()
{
    return getLocalArea (caret.get(), caret->getLocalBounds());
}

//==============================================================================
void molested__CodeEditorComponent::codeDocumentChanged (const CodeDocument::Position& affectedTextStart,
                                               const CodeDocument::Position& affectedTextEnd)
{
    clearCachedIterators (affectedTextStart.getLineNumber());

    triggerAsyncUpdate();

    updateCaretPosition();
    columnToTryToMaintain = -1;

    if (affectedTextEnd.getPosition() >= selectionStart.getPosition()
         && affectedTextStart.getPosition() <= selectionEnd.getPosition())
        deselectAll();

    if (caretPos.getPosition() > affectedTextEnd.getPosition()
         || caretPos.getPosition() < affectedTextStart.getPosition())
        moveCaretTo (affectedTextStart, false);

    updateScrollBars();
}

void molested__CodeEditorComponent::resized()
{
    linesOnScreen = (getHeight() - scrollbarThickness) / lineHeight;
    columnsOnScreen = (int) ((getWidth() - scrollbarThickness) / charWidth);
    lines.clear();
    rebuildLineTokens();
    updateCaretPosition();

    verticalScrollBar.setBounds (getWidth() - scrollbarThickness, 0, scrollbarThickness, getHeight() - scrollbarThickness);
    horizontalScrollBar.setBounds (gutter, getHeight() - scrollbarThickness, getWidth() - scrollbarThickness - gutter, scrollbarThickness);
    updateScrollBars();
}

void molested__CodeEditorComponent::paint (Graphics& g)
{
    handleUpdateNowIfNeeded();

    g.fillAll (findColour (molested__CodeEditorComponent::backgroundColourId));

    g.reduceClipRegion (gutter, 0, verticalScrollBar.getX() - gutter, horizontalScrollBar.getY());

    g.setFont (font);
    const int baselineOffset = (int) font.getAscent();
    const Colour defaultColour (findColour (molested__CodeEditorComponent::defaultTextColourId));
    const Colour highlightColour (findColour (molested__CodeEditorComponent::highlightColourId));

    const Rectangle<int> clip (g.getClipBounds());
    const int firstLineToDraw = jmax (0, clip.getY() / lineHeight);
    const int lastLineToDraw = jmin (lines.size(), clip.getBottom() / lineHeight + 1);

    for (int j = firstLineToDraw; j < lastLineToDraw; ++j)
    {
        lines.getUnchecked(j)->draw (*this, g, font,
                                     (float) (gutter - xOffset * charWidth),
                                     lineHeight * j, baselineOffset, lineHeight,
                                     highlightColour);
    }
}

void molested__CodeEditorComponent::setScrollbarThickness (const int thickness)
{
    if (scrollbarThickness != thickness)
    {
        scrollbarThickness = thickness;
        resized();
    }
}

void molested__CodeEditorComponent::handleAsyncUpdate()
{
    rebuildLineTokens();
}

void molested__CodeEditorComponent::rebuildLineTokens()
{
    cancelPendingUpdate();

    const int numNeeded = linesOnScreen + 1;

    int minLineToRepaint = numNeeded;
    int maxLineToRepaint = 0;

    if (numNeeded != lines.size())
    {
        lines.clear();

        for (int i = numNeeded; --i >= 0;)
            lines.add (new CodeEditorLine());

        minLineToRepaint = 0;
        maxLineToRepaint = numNeeded;
    }

    jassert (numNeeded == lines.size());

    CodeDocument::Iterator source (document);
    getIteratorForPosition (CodeDocument::Position (document, firstLineOnScreen, 0).getPosition(), source);

    for (int i = 0; i < numNeeded; ++i)
    {
        CodeEditorLine* const line = lines.getUnchecked(i);

        if (line->update (document, firstLineOnScreen + i, source, codeTokeniser, spacesPerTab,
                          selectionStart, selectionEnd))
        {
            minLineToRepaint = jmin (minLineToRepaint, i);
            maxLineToRepaint = jmax (maxLineToRepaint, i);
        }
    }

    if (minLineToRepaint <= maxLineToRepaint)
    {
        repaint (gutter, lineHeight * minLineToRepaint - 1,
                 verticalScrollBar.getX() - gutter,
                 lineHeight * (1 + maxLineToRepaint - minLineToRepaint) + 2);
    }
}

//==============================================================================
void molested__CodeEditorComponent::updateCaretPosition()
{
    caret->setCaretPosition (getCharacterBounds (getCaretPos()));
}

void molested__CodeEditorComponent::moveCaretTo (const CodeDocument::Position& newPos, const bool highlighting)
{
    caretPos = newPos;
    columnToTryToMaintain = -1;

    if (highlighting)
    {
        if (dragType == notDragging)
        {
            if (abs (caretPos.getPosition() - selectionStart.getPosition())
                  < abs (caretPos.getPosition() - selectionEnd.getPosition()))
                dragType = draggingSelectionStart;
            else
                dragType = draggingSelectionEnd;
        }

        if (dragType == draggingSelectionStart)
        {
            selectionStart = caretPos;

            if (selectionEnd.getPosition() < selectionStart.getPosition())
            {
                const CodeDocument::Position temp (selectionStart);
                selectionStart = selectionEnd;
                selectionEnd = temp;

                dragType = draggingSelectionEnd;
            }
        }
        else
        {
            selectionEnd = caretPos;

            if (selectionEnd.getPosition() < selectionStart.getPosition())
            {
                const CodeDocument::Position temp (selectionStart);
                selectionStart = selectionEnd;
                selectionEnd = temp;

                dragType = draggingSelectionStart;
            }
        }

        triggerAsyncUpdate();
    }
    else
    {
        deselectAll();
    }

    updateCaretPosition();
    scrollToKeepCaretOnScreen();
    updateScrollBars();
}

void molested__CodeEditorComponent::deselectAll()
{
    if (selectionStart != selectionEnd)
        triggerAsyncUpdate();

    selectionStart = caretPos;
    selectionEnd = caretPos;
}

void molested__CodeEditorComponent::updateScrollBars()
{
    verticalScrollBar.setRangeLimits (0, jmax (document.getNumLines(), firstLineOnScreen + linesOnScreen));
    verticalScrollBar.setCurrentRange (firstLineOnScreen, linesOnScreen);

    horizontalScrollBar.setRangeLimits (0, jmax ((double) document.getMaximumLineLength(), xOffset + columnsOnScreen));
    horizontalScrollBar.setCurrentRange (xOffset, columnsOnScreen);
}

void molested__CodeEditorComponent::scrollToLineInternal (int newFirstLineOnScreen)
{
    newFirstLineOnScreen = jlimit (0, jmax (0, document.getNumLines() - 1),
                                   newFirstLineOnScreen);

    if (newFirstLineOnScreen != firstLineOnScreen)
    {
        firstLineOnScreen = newFirstLineOnScreen;
        updateCaretPosition();

        updateCachedIterators (firstLineOnScreen);
        triggerAsyncUpdate();
    }
}

void molested__CodeEditorComponent::scrollToColumnInternal (double column)
{
    const double newOffset = jlimit (0.0, document.getMaximumLineLength() + 3.0, column);

    if (xOffset != newOffset)
    {
        xOffset = newOffset;
        updateCaretPosition();
        repaint();
    }
}

void molested__CodeEditorComponent::scrollToLine (int newFirstLineOnScreen)
{
    scrollToLineInternal (newFirstLineOnScreen);
    updateScrollBars();
}

void molested__CodeEditorComponent::scrollToColumn (int newFirstColumnOnScreen)
{
    scrollToColumnInternal (newFirstColumnOnScreen);
    updateScrollBars();
}

void molested__CodeEditorComponent::scrollBy (int deltaLines)
{
    scrollToLine (firstLineOnScreen + deltaLines);
}

void molested__CodeEditorComponent::scrollToKeepCaretOnScreen()
{
    if (caretPos.getLineNumber() < firstLineOnScreen)
        scrollBy (caretPos.getLineNumber() - firstLineOnScreen);
    else if (caretPos.getLineNumber() >= firstLineOnScreen + linesOnScreen)
        scrollBy (caretPos.getLineNumber() - (firstLineOnScreen + linesOnScreen - 1));

//beginchange
//remove:
//    const int column = indexToColumn (caretPos.getLineNumber(), caretPos.getIndexInLine());
//insert:
    const int fixedWidthColumn = indexToColumn (caretPos.getLineNumber(), caretPos.getIndexInLine());
    String textLine = document.getLine(caretPos.getLineNumber());
	for (;;)
	{
		int tabPos = textLine.indexOfChar ('\t');
		if (tabPos < 0)
			break;
		
		const int spacesNeeded = spacesPerTab - (tabPos % spacesPerTab);
		textLine = textLine.replaceSection (tabPos, 1, String::repeatedString (" ", spacesNeeded));
	}
	const int column = roundToInt(font.getStringWidthFloat(textLine.substring(0, fixedWidthColumn)) / charWidth);
//endchange
    if (column >= xOffset + columnsOnScreen - 1)
        scrollToColumn (column + 1 - columnsOnScreen);
    else if (column < xOffset)
        scrollToColumn (column);
}

const Rectangle<int> molested__CodeEditorComponent::getCharacterBounds (const CodeDocument::Position& pos) const
{
//beginchange
//remove:
//    return Rectangle<int> (roundToInt ((gutter - xOffset * charWidth) + indexToColumn (pos.getLineNumber(), pos.getIndexInLine()) * charWidth),
//                           (pos.getLineNumber() - firstLineOnScreen) * lineHeight,
//                           roundToInt (charWidth),
//                           lineHeight);
//insert:
	int col = indexToColumn (pos.getLineNumber(), pos.getIndexInLine());
    String textLine = document.getLine(pos.getLineNumber());
	for (;;)
	{
		int tabPos = textLine.indexOfChar ('\t');
		if (tabPos < 0)
			break;
		
		const int spacesNeeded = spacesPerTab - (tabPos % spacesPerTab);
		textLine = textLine.replaceSection (tabPos, 1, String::repeatedString (" ", spacesNeeded));
	}
	float preWidth = font.getStringWidthFloat(textLine.substring(0, col));
	
	return Rectangle<int> (roundToInt ((gutter - xOffset * charWidth) + preWidth),
                           (pos.getLineNumber() - firstLineOnScreen) * lineHeight,
                           roundToInt (charWidth),
                           lineHeight);
//endchange
}

const CodeDocument::Position molested__CodeEditorComponent::getPositionAt (int x, int y)
{
	const int line = y / lineHeight + firstLineOnScreen;
//beginchange
//remove:
//    const int column = roundToInt ((x - (gutter - xOffset * charWidth)) / charWidth);
//insert:
	String textLine = document.getLine(line);
	// Expand tabs
	for (;;)
	{
		int tabPos = textLine.indexOfChar ('\t');
		if (tabPos < 0)
			break;
		
		const int spacesNeeded = spacesPerTab - (tabPos % spacesPerTab);
		textLine = textLine.replaceSection (tabPos, 1, String::repeatedString (" ", spacesNeeded));
	}
	// Do a binary search for locating best col
	int xBase = roundToInt(x + xOffset - gutter);
	int colLow = 0, colHigh = textLine.length();
	float xLow = 0, xHigh = font.getStringWidthFloat(textLine);
	while (colHigh - colLow >= 2)
	{
		int colMid = (colHigh + colLow) / 2;
		float xMid = font.getStringWidthFloat(textLine.substring(0, colMid));
		if (xBase < xMid)
		{
			colHigh = colMid;
			xHigh = xMid;
		}
		else
		{
			colLow = colMid;
			xLow = xMid;
		}
	}
	const int column = (xBase < (xHigh + xLow) / 2)? colLow : colHigh;
//endchange
    const int index = columnToIndex (line, column);

    return CodeDocument::Position (document, line, index);
}

//==============================================================================
void molested__CodeEditorComponent::insertTextAtCaret (const String& newText)
{
    document.deleteSection (selectionStart, selectionEnd);

    if (newText.isNotEmpty())
        document.insertText (caretPos, newText);

    scrollToKeepCaretOnScreen();
}

void molested__CodeEditorComponent::insertTabAtCaret()
{
    if (CharacterFunctions::isWhitespace (caretPos.getCharacter())
         && caretPos.getLineNumber() == caretPos.movedBy (1).getLineNumber())
    {
        moveCaretTo (document.findWordBreakAfter (caretPos), false);
    }

    if (useSpacesForTabs)
    {
        const int caretCol = indexToColumn (caretPos.getLineNumber(), caretPos.getIndexInLine());
        const int spacesNeeded = spacesPerTab - (caretCol % spacesPerTab);
        insertTextAtCaret (String::repeatedString (" ", spacesNeeded));
    }
    else
    {
        insertTextAtCaret ("\t");
    }
}

void molested__CodeEditorComponent::cut()
{
    insertTextAtCaret ({});
}

bool molested__CodeEditorComponent::copyToClipboard()
{
    newTransaction();

    const String selection (document.getTextBetween (selectionStart, selectionEnd));

    if (selection.isNotEmpty())
        SystemClipboard::copyTextToClipboard (selection);

    return true;
}

bool molested__CodeEditorComponent::cutToClipboard()
{
    copyToClipboard();
    cut();
    newTransaction();
    return true;
}

bool molested__CodeEditorComponent::pasteFromClipboard()
{
    newTransaction();
    const String clip (SystemClipboard::getTextFromClipboard());

    if (clip.isNotEmpty())
        insertTextAtCaret (clip);

    newTransaction();
    return true;
}

bool molested__CodeEditorComponent::moveCaretLeft (const bool moveInWholeWordSteps, const bool selecting)
{
    newTransaction();

    if (moveInWholeWordSteps)
        moveCaretTo (document.findWordBreakBefore (caretPos), selecting);
    else
        moveCaretTo (caretPos.movedBy (-1), selecting);

    return true;
}

bool molested__CodeEditorComponent::moveCaretRight (const bool moveInWholeWordSteps, const bool selecting)
{
    newTransaction();

    if (moveInWholeWordSteps)
        moveCaretTo (document.findWordBreakAfter (caretPos), selecting);
    else
        moveCaretTo (caretPos.movedBy (1), selecting);

    return true;
}

void molested__CodeEditorComponent::moveLineDelta (const int delta, const bool selecting)
{
    CodeDocument::Position pos (caretPos);
    const int newLineNum = pos.getLineNumber() + delta;

    if (columnToTryToMaintain < 0)
        columnToTryToMaintain = indexToColumn (pos.getLineNumber(), pos.getIndexInLine());

    pos.setLineAndIndex (newLineNum, columnToIndex (newLineNum, columnToTryToMaintain));

    const int colToMaintain = columnToTryToMaintain;
    moveCaretTo (pos, selecting);
    columnToTryToMaintain = colToMaintain;
}

bool molested__CodeEditorComponent::moveCaretDown (const bool selecting)
{
    newTransaction();

    if (caretPos.getLineNumber() == document.getNumLines() - 1)
        moveCaretTo (CodeDocument::Position (document, std::numeric_limits<int>::max(), std::numeric_limits<int>::max()), selecting);
    else
        moveLineDelta (1, selecting);

    return true;
}

bool molested__CodeEditorComponent::moveCaretUp (const bool selecting)
{
    newTransaction();

    if (caretPos.getLineNumber() == 0)
        moveCaretTo (CodeDocument::Position (document, 0, 0), selecting);
    else
        moveLineDelta (-1, selecting);

    return true;
}

bool molested__CodeEditorComponent::pageDown (const bool selecting)
{
    newTransaction();
    scrollBy (jlimit (0, linesOnScreen, 1 + document.getNumLines() - firstLineOnScreen - linesOnScreen));
    moveLineDelta (linesOnScreen, selecting);
    return true;
}

bool molested__CodeEditorComponent::pageUp (const bool selecting)
{
    newTransaction();
    scrollBy (-linesOnScreen);
    moveLineDelta (-linesOnScreen, selecting);
    return true;
}

bool molested__CodeEditorComponent::scrollUp()
{
    newTransaction();
    scrollBy (1);

    if (caretPos.getLineNumber() < firstLineOnScreen)
        moveLineDelta (1, false);

    return true;
}

bool molested__CodeEditorComponent::scrollDown()
{
    newTransaction();
    scrollBy (-1);

    if (caretPos.getLineNumber() >= firstLineOnScreen + linesOnScreen)
        moveLineDelta (-1, false);

    return true;
}

bool molested__CodeEditorComponent::moveCaretToTop (const bool selecting)
{
    newTransaction();
    moveCaretTo (CodeDocument::Position (document, 0, 0), selecting);
    return true;
}
namespace molested__CodeEditorHelpers
{
    int findFirstNonWhitespaceChar (const String& line) noexcept
    {
        String::CharPointerType t (line.getCharPointer());
        int i = 0;

        while (! t.isEmpty())
        {
            if (! t.isWhitespace())
                return i;

            ++t;
            ++i;
        }

        return 0;
    }
}

bool molested__CodeEditorComponent::moveCaretToStartOfLine (const bool selecting)
{
    newTransaction();

    int index = molested__CodeEditorHelpers::findFirstNonWhitespaceChar (caretPos.getLineText());

    if (index >= caretPos.getIndexInLine() && caretPos.getIndexInLine() > 0)
        index = 0;

    moveCaretTo (CodeDocument::Position (document, caretPos.getLineNumber(), index), selecting);
    return true;
}

bool molested__CodeEditorComponent::moveCaretToEnd (const bool selecting)
{
    newTransaction();
    moveCaretTo (CodeDocument::Position (document, std::numeric_limits<int>::max(), std::numeric_limits<int>::max()), selecting);
    return true;
}

bool molested__CodeEditorComponent::moveCaretToEndOfLine (const bool selecting)
{
    newTransaction();
    moveCaretTo (CodeDocument::Position (document, caretPos.getLineNumber(), std::numeric_limits<int>::max()), selecting);
    return true;
}

bool molested__CodeEditorComponent::deleteBackwards (const bool moveInWholeWordSteps)
{
    if (moveInWholeWordSteps)
    {
        cut(); // in case something is already highlighted
        moveCaretTo (document.findWordBreakBefore (caretPos), true);
    }
    else
    {
        if (selectionStart == selectionEnd)
            selectionStart.moveBy (-1);
    }

    cut();
    return true;
}

bool molested__CodeEditorComponent::deleteForwards (const bool moveInWholeWordSteps)
{
    if (moveInWholeWordSteps)
    {
        cut(); // in case something is already highlighted
        moveCaretTo (document.findWordBreakAfter (caretPos), true);
    }
    else
    {
        if (selectionStart == selectionEnd)
            selectionEnd.moveBy (1);
        else
            newTransaction();
    }

    cut();
    return true;
}

bool molested__CodeEditorComponent::selectAll()
{
    newTransaction();
    moveCaretTo (CodeDocument::Position (document, std::numeric_limits<int>::max(), std::numeric_limits<int>::max()), false);
    moveCaretTo (CodeDocument::Position (document, 0, 0), true);
    return true;
}

//==============================================================================
bool molested__CodeEditorComponent::undo()
{
    document.undo();
    scrollToKeepCaretOnScreen();
    return true;
}

bool molested__CodeEditorComponent::redo()
{
    document.redo();
    scrollToKeepCaretOnScreen();
    return true;
}

void molested__CodeEditorComponent::newTransaction()
{
    document.newTransaction();
    startTimer (600);
}

void molested__CodeEditorComponent::timerCallback()
{
    newTransaction();
}

//==============================================================================
Range<int> molested__CodeEditorComponent::getHighlightedRegion() const
{
    return Range<int> (selectionStart.getPosition(), selectionEnd.getPosition());
}

void molested__CodeEditorComponent::setHighlightedRegion (const Range<int>& newRange)
{
    moveCaretTo (CodeDocument::Position (document, newRange.getStart()), false);
    moveCaretTo (CodeDocument::Position (document, newRange.getEnd()), true);
}

String molested__CodeEditorComponent::getTextInRange (const Range<int>& range) const
{
    return document.getTextBetween (CodeDocument::Position (document, range.getStart()),
                                    CodeDocument::Position (document, range.getEnd()));
}

//==============================================================================
bool molested__CodeEditorComponent::keyPressed (const KeyPress& key)
{
    if (! TextEditorKeyMapper<molested__CodeEditorComponent>::invokeKeyFunction (*this, key))
    {
        if (key == KeyPress::tabKey || key.getTextCharacter() == '\t')
        {
            insertTabAtCaret();
        }
        else if (key == KeyPress::returnKey)
        {
            newTransaction();
            insertTextAtCaret (document.getNewLineCharacters());
        }
        else if (key.isKeyCode (KeyPress::escapeKey))
        {
            newTransaction();
        }
        else if (key.getTextCharacter() >= ' ')
        {
            insertTextAtCaret (String::charToString (key.getTextCharacter()));
        }
        else
        {
            return false;
        }
    }

    return true;
}

void molested__CodeEditorComponent::mouseDown (const MouseEvent& e)
{
    newTransaction();
    dragType = notDragging;

    if (! e.mods.isPopupMenu())
    {
        beginDragAutoRepeat (100);
        moveCaretTo (getPositionAt (e.x, e.y), e.mods.isShiftDown());
    }
    else
    {
        /*PopupMenu m;
        addPopupMenuItems (m, &e);

        const int result = m.show();

        if (result != 0)
            performPopupMenuAction (result);
        */
    }
}

void molested__CodeEditorComponent::mouseDrag (const MouseEvent& e)
{
    if (! e.mods.isPopupMenu())
        moveCaretTo (getPositionAt (e.x, e.y), true);
}

void molested__CodeEditorComponent::mouseUp (const MouseEvent&)
{
    newTransaction();
    beginDragAutoRepeat (0);
    dragType = notDragging;
}

void molested__CodeEditorComponent::mouseDoubleClick (const MouseEvent& e)
{
    CodeDocument::Position tokenStart (getPositionAt (e.x, e.y));
    CodeDocument::Position tokenEnd (tokenStart);

    if (e.getNumberOfClicks() > 2)
    {
        tokenStart.setLineAndIndex (tokenStart.getLineNumber(), 0);
        tokenEnd.setLineAndIndex (tokenStart.getLineNumber() + 1, 0);
    }
    else
    {
        while (CharacterFunctions::isLetterOrDigit (tokenEnd.getCharacter()))
            tokenEnd.moveBy (1);

        tokenStart = tokenEnd;

        while (tokenStart.getIndexInLine() > 0
                && CharacterFunctions::isLetterOrDigit (tokenStart.movedBy (-1).getCharacter()))
            tokenStart.moveBy (-1);
    }

    moveCaretTo (tokenEnd, false);
    moveCaretTo (tokenStart, true);
}

void molested__CodeEditorComponent::mouseWheelMove (
    const MouseEvent& e,
    const MouseWheelDetails& wheel)
{
    if ((verticalScrollBar.isVisible() && wheel.deltaY != 0.0f)
        || (horizontalScrollBar.isVisible() && wheel.deltaX != 0.0f))
    {
        verticalScrollBar.mouseWheelMove (e, wheel);
        horizontalScrollBar.mouseWheelMove (e, wheel);
    }
    else
    {
        Component::mouseWheelMove (e, wheel);
    }
}
void molested__CodeEditorComponent::scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    if (scrollBarThatHasMoved == &verticalScrollBar)
        scrollToLineInternal ((int) newRangeStart);
    else
        scrollToColumnInternal (newRangeStart);
}

//==============================================================================
void molested__CodeEditorComponent::focusGained (FocusChangeType)
{
    updateCaretPosition();
}

void molested__CodeEditorComponent::focusLost (FocusChangeType)
{
    updateCaretPosition();
}

//==============================================================================
void molested__CodeEditorComponent::setTabSize (const int numSpaces, const bool insertSpaces)
{
    useSpacesForTabs = insertSpaces;

    if (spacesPerTab != numSpaces)
    {
        spacesPerTab = numSpaces;
        triggerAsyncUpdate();
    }
}

int molested__CodeEditorComponent::indexToColumn (int lineNum, int index) const noexcept
{
    String::CharPointerType t (document.getLine (lineNum).getCharPointer());

    int col = 0;
    for (int i = 0; i < index; ++i)
    {
        if (t.isEmpty())
        {
            jassertfalse;
            break;
        }

        if (t.getAndAdvance() != '\t')
            ++col;
        else
            col += getTabSize() - (col % getTabSize());
    }

    return col;
}

int molested__CodeEditorComponent::columnToIndex (int lineNum, int column) const noexcept
{
    String::CharPointerType t (document.getLine (lineNum).getCharPointer());

    int i = 0, col = 0;

    while (! t.isEmpty())
    {
        if (t.getAndAdvance() != '\t')
            ++col;
        else
            col += getTabSize() - (col % getTabSize());

        if (col > column)
            break;

        ++i;
    }

    return i;
}

//==============================================================================
void molested__CodeEditorComponent::setFont (const Font& newFont)
{
    font = newFont;
    charWidth = font.getStringWidthFloat ("0");
    lineHeight = roundToInt (font.getHeight());
    resized();
}

void molested__CodeEditorComponent::resetToDefaultColours()
{
    coloursForTokenCategories.clear();
}

void molested__CodeEditorComponent::setColourForTokenType (const int tokenType, const Colour& colour)
{
    jassert (tokenType < 256);

    while (coloursForTokenCategories.size() < tokenType)
        coloursForTokenCategories.add (Colours::black);

    coloursForTokenCategories.set (tokenType, colour);
    repaint();
}

const Colour molested__CodeEditorComponent::getColourForTokenType (const int tokenType) const
{
    if (! isPositiveAndBelow (tokenType, coloursForTokenCategories.size()))
        return findColour (molested__CodeEditorComponent::defaultTextColourId);

    return coloursForTokenCategories.getReference (tokenType);
}

void molested__CodeEditorComponent::clearCachedIterators (const int firstLineToBeInvalid)
{
    int i;
    for (i = cachedIterators.size(); --i >= 0;)
        if (cachedIterators.getUnchecked (i)->getLine() < firstLineToBeInvalid)
            break;

    cachedIterators.removeRange (jmax (0, i - 1), cachedIterators.size());
}

void molested__CodeEditorComponent::updateCachedIterators (int maxLineNum)
{
    const int maxNumCachedPositions = 5000;
    const int linesBetweenCachedSources = jmax (10, document.getNumLines() / maxNumCachedPositions);

    if (cachedIterators.size() == 0)
        cachedIterators.add (new CodeDocument::Iterator (document));

    if (codeTokeniser == nullptr)
        return;

    for (;;)
    {
        CodeDocument::Iterator* last = cachedIterators.getLast();

        if (last->getLine() >= maxLineNum)
            break;

        CodeDocument::Iterator* t = new CodeDocument::Iterator (*last);
        cachedIterators.add (t);
        const int targetLine = last->getLine() + linesBetweenCachedSources;

        for (;;)
        {
            codeTokeniser->readNextToken (*t);

            if (t->getLine() >= targetLine)
                break;

            if (t->isEOF())
                return;
        }
    }
}

void molested__CodeEditorComponent::getIteratorForPosition (int position, CodeDocument::Iterator& source)
{
    if (codeTokeniser == nullptr)
        return;

    for (int i = cachedIterators.size(); --i >= 0;)
    {
        CodeDocument::Iterator* t = cachedIterators.getUnchecked (i);
        if (t->getPosition() <= position)
        {
            source = *t;
            break;
        }
    }

    while (source.getPosition() < position)
    {
        const CodeDocument::Iterator original (source);
        codeTokeniser->readNextToken (source);

        if (source.getPosition() > position || source.isEOF())
        {
            source = original;
            break;
        }
    }
}

//END_JUCE_NAMESPACE

// END OF MOLESTED JUCE FILE


// Syntax coloring for PILS

PilsCodeTokeniser::PilsCodeTokeniser()
{
}

PilsCodeTokeniser::~PilsCodeTokeniser()
{
}

//==============================================================================
namespace PilsTokeniser
{
    bool isIdentifierStart (const juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetter (c)
                || c == '_' || c == '@' || (unsigned int)c >= 0x80;
    }

    bool isIdentifierBody (const juce_wchar c) noexcept
    {
        return CharacterFunctions::isLetterOrDigit (c)
                || c == '_' || c == '@' || (unsigned int)c >= 0x80;
    }

    int parseIdentifier (CodeDocument::Iterator& source) noexcept
    {
        int tokenLength = 0;
        String::CharPointerType::CharType possibleIdentifier [100];
        String::CharPointerType possible (possibleIdentifier);

        while (isIdentifierBody (source.peekNextChar()))
        {
            const juce_wchar c = source.nextChar();

            if (tokenLength < 20)
                possible.write (c);

            ++tokenLength;
        }

        return PilsCodeTokeniser::tokenType_identifier;
    }

    bool isHexDigit (const juce_wchar c) noexcept
    {
        return (c >= '0' && c <= '9')
                || (c >= 'a' && c <= 'f');
    }

    bool parseHexLiteral (CodeDocument::Iterator& source) noexcept
    {
        if (source.nextChar() != '0')
            return false;

        juce_wchar c = source.nextChar();
        if (c != 'x' && c != 'X')
            return false;

        int numDigits = 0;
        while (isHexDigit (source.peekNextChar()))
        {
            ++numDigits;
            source.skip();
        }

        if (numDigits == 0)
            return false;

        return true;
    }

    bool isDecimalDigit (const juce_wchar c) noexcept
    {
        return c >= '0' && c <= '9';
    }

    bool parseDecimalLiteral (CodeDocument::Iterator& source) noexcept
    {
        int numChars = 0;
        while (isDecimalDigit (source.peekNextChar()))
        {
            ++numChars;
            source.skip();
        }

        if (numChars == 0)
            return false;

        return true;
    }

    bool parseFloatLiteral (CodeDocument::Iterator& source) noexcept
    {
        int numDigits = 0;

        while (isDecimalDigit (source.peekNextChar()))
        {
            source.skip();
            ++numDigits;
        }

        const bool hasPoint = (source.peekNextChar() == '.' || source.peekNextChar() == ',');

        if (hasPoint)
        {
            source.skip();

            while (isDecimalDigit (source.peekNextChar()))
            {
                source.skip();
                ++numDigits;
            }
        }

        if (numDigits == 0)
            return false;

        juce_wchar c = source.peekNextChar();
        const bool hasExponent = (c == 'e' || c == 'E');

        if (hasExponent)
        {
            source.skip();

            c = source.peekNextChar();
            if (c == '+' || c == '-')
                source.skip();

            int numExpDigits = 0;
            while (isDecimalDigit (source.peekNextChar()))
            {
                source.skip();
                ++numExpDigits;
            }

            if (numExpDigits == 0)
                return false;
        }

        if (! (hasExponent || hasPoint))
            return false;

        return true;
    }

    int parseNumber (CodeDocument::Iterator& source)
    {
        const CodeDocument::Iterator original (source);

        if (parseFloatLiteral (source))
            return PilsCodeTokeniser::tokenType_number;

        source = original;

        if (parseHexLiteral (source))
            return PilsCodeTokeniser::tokenType_number;

        source = original;

        if (parseDecimalLiteral (source))
            return PilsCodeTokeniser::tokenType_number;

        source = original;
        source.skip();

        return PilsCodeTokeniser::tokenType_error;
    }

    void skipQuotedString (CodeDocument::Iterator& source) noexcept
    {
        const juce_wchar quote = source.nextChar();

        for (;;)
        {
            const juce_wchar c = source.nextChar();

            if (c == quote || c == 0)
                break;
        }
    }

    void skipComment (CodeDocument::Iterator& source) noexcept
    {
		if (source.nextChar() != '!') return;
		else if (source.peekNextChar() != '!')
        {
			source.skipToEndOfLine();
		}
		else for (bool wasExclamation = false;!source.isEOF();)
		{
			if (source.nextChar() == '!')
			{
				if (wasExclamation) break;
				else wasExclamation = true;
			}
			else
			{
				wasExclamation = false;
			}
		}
	
    }
}

//==============================================================================
int PilsCodeTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    int result = tokenType_error;
    source.skipWhitespace();

    juce_wchar firstChar = source.peekNextChar();

    switch (firstChar)
    {
    case 0:
        source.skip();
        break;

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        result = PilsTokeniser::parseNumber (source);
        break;

    case '.':
    case ',':
    case ';':
    case ':':
        source.skip();
        result = tokenType_punctuation;
        break;

	case '(':
    case ')':
    case '{':
    case '}':
    case '[':
    case ']':
    case '|':
        source.skip();
        result = tokenType_bracket;
        break;

    case '"':
        PilsTokeniser::skipQuotedString (source);
        result = tokenType_string;
        break;

    case '-':
        source.skip();
        result = PilsTokeniser::parseNumber (source);

        if (result == tokenType_error)
        {
            result = tokenType_operator;

            if (source.peekNextChar() == '-')
                source.skip();
            else if (source.peekNextChar() == '=')
                source.skip();
        }
        break;

    case '*':
    case '%':
    case '=':
    case '<':
    case '>':
    case '\\':
    case '/':
    case '?':
    case '~':
    case '&':
    case '^':
    case '#':
    case '+':
    case '$':
        source.skip();
        result = tokenType_operator;
        break;

    case '!':
		PilsTokeniser::skipComment (source);
        result = tokenType_comment;
        break;

	default:
        if (PilsTokeniser::isIdentifierStart (firstChar))
            result = PilsTokeniser::parseIdentifier (source);
        else
            source.skip();

        break;
    }

    return result;
}
// StringArray PilsCodeTokeniser::getTokenTypes()
// {
//     const char* const types[] =
//     {
//         "Error",
//         "Comment",
//         "Identifier",
//         "Number",
//         "String",
//         "Operator",
//         "Bracket",
//         "Punctuation",
//         0
//     };
//     return StringArray (types);
// }
CodeEditorComponent::ColourScheme PilsCodeTokeniser::getDefaultColourScheme()
{
    CodeEditorComponent::ColourScheme scheme;

    scheme.set ("Error",        juce::Colour (0xffcc0000));
    scheme.set ("Comment",      juce::Colour (0xff007700));
    scheme.set ("Identifier",   juce::Colour (0xff000000));
    scheme.set ("Number",       juce::Colour (0xff0000ff));
    scheme.set ("String",       juce::Colour (0xff992200));
    scheme.set ("Operator",     juce::Colour (0xff000000));
    scheme.set ("Bracket",      juce::Colour (0xff000000));
    scheme.set ("Punctuation",  juce::Colour (0xff000000));

    return scheme;
}

} //namespace juce
