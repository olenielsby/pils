/*
  ==============================================================================

   This file is partially derived from the JUCE library -
   "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_PDFWRITER_JUCEHEADER__
#define __JUCE_PDFWRITER_JUCEHEADER__


#include "hpdf.h"


BEGIN_JUCE_NAMESPACE

#include "src/gui/graphics/contexts/juce_LowLevelGraphicsContext.h"

class JUCE_API  PrintingContext : public LowLevelGraphicsContext
{
public:
	enum Orientation
	{
		Portrait,
		Landscape
	};

	enum PageSize
	{
		PageSize_Letter,	//   8.5 x 11 "         612 x 792
		PageSize_Legal,     //   8.5 x 14 "         612 x 1008
		PageSize_A3,        //   297 x 420 mm    841.89 x 1199.551
		PageSize_A4,        //   210 x 297 mm   595.276 x 841.89
		PageSize_A5,        //   148 x 210 mm   419.528 x 595.276
		PageSize_B4,        //   250 x 353 mm   708.661 x 1000.63
		PageSize_B5,        //   176 x 250 mm   498.898 x 708.661
		PageSize_Executive, //  7.25 x 10.5 "       522 x 756
		PageSize_US4x6,     //     4 x 6 "          288 x 432
		PageSize_US4x8,     //     4 x 8 "          288 x 576
		PageSize_US5x7,     //     5 x 7 "          360 x 504
		PageSize_COMM10     // 4.125 x 9.5 "        297 x 684
	};

	virtual void beginPrinting() = 0;
	virtual void endPrinting() = 0;
	virtual Graphics *beginPage(PageSize pageSize_, Orientation orientation_) = 0;
	virtual void endPage() = 0;

	juce_UseDebuggingNewOperator
};

//==============================================================================
/**
    An implementation of LowLevelGraphicsContext that turns the drawing operations
    into a PDF document.

*/
class JUCE_API  PDFWriter    : public PrintingContext
{
public:
    //==============================================================================
	PDFWriter (OutputStream &out_, int dpi_, const bool isColourPrint_ = true);
	~PDFWriter();

	/* override abstract methods of LowLevelGraphicsContext */

	bool isVectorDevice() const;
	void setOrigin (int x, int y);
    bool clipToRectangle (const Rectangle<int>& r);
    bool clipToRectangleList (const RectangleList& clipRegion);
    void excludeClipRectangle (const Rectangle<int>& r);
    void clipToPath (const Path& path, const AffineTransform& transform);
    void clipToImageAlpha (const Image& sourceImage, const Rectangle<int>& srcClip, const AffineTransform& transform);

    bool clipRegionIntersects (const Rectangle<int>& r);
    const Rectangle<int> getClipBounds() const;
    bool isClipEmpty() const;

    void saveState();
    void restoreState();

    //==============================================================================
    void setFill (const FillType& fillType);
    void setOpacity (float newOpacity);
    void setInterpolationQuality (Graphics::ResamplingQuality quality);

    //==============================================================================
    void fillRect (const Rectangle<int>& r, const bool replaceExistingContents);
    void fillPath (const Path& path, const AffineTransform& transform);

    void drawImage (const Image& sourceImage, const Rectangle<int>& srcClip,
                            const AffineTransform& transform, const bool fillEntireClipAsTiles);

    void drawLine (double x1, double y1, double x2, double y2);
    void drawVerticalLine (const int x, double top, double bottom);
    void drawHorizontalLine (const int y, double left, double right);

    void setFont (const Font& newFont);
    Font getFont();
    void drawGlyph (int glyphNumber, const AffineTransform& transform);

	
	//============= Printing control methods =====================
	void beginPrinting();
	void endPrinting();
	Graphics *beginPage(PageSize pageSize_, Orientation orientation_);
	void endPage();

    juce_UseDebuggingNewOperator

protected:
    //==============================================================================

    OutputStream& out;
  	const int dpi;
	const bool isColourPrint;
	juce::MemoryOutputStream contentBuffer;

	PDFWriter (const PDFWriter& other);
    const PDFWriter& operator= (const PDFWriter&);

	Graphics *currentGraphics;
	juce::Array<int> xref;
	juce::Array<int> pages;

private:
	int outBeginObject();
	void outEndObject();
	void contentOut(float f);
	void contentOut(const Path &path);
	void contentOut(const Rectangle<int> &rect);
};

END_JUCE_NAMESPACE

#endif   // __JUCE_LOWLEVELGRAPHICSPOSTSCRIPTRENDERER_JUCEHEADER__
