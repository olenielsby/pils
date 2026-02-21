/*
  ==============================================================================

   This file is partly derived from the JUCE library
   - "Jules' Utility Class Extensions"
   Copyright 2004-9 by Raw Material Software Ltd.
*/

#include <src/juce_WithoutMacros.h>

#include "juce_PDFWriter.h"

BEGIN_JUCE_NAMESPACE

#include "src/gui/graphics/contexts/juce_EdgeTable.h"
#include "src/gui/graphics/imaging/juce_Image.h"
#include "src/gui/graphics/colour/juce_PixelFormats.h"
#include "src/gui/graphics/geometry/juce_PathStrokeType.h"
#include "src/gui/graphics/geometry/juce_Rectangle.h"
#include "src/containers/juce_SparseSet.h"

#if JUCE_MSVC
  #pragma warning (disable: 4996) // deprecated sprintf warning
#endif


// this will throw an assertion if you try to draw something that's not
// possible in PDF
#define WARN_ABOUT_NON_PDF_OPERATIONS 0


//==============================================================================
#if defined (JUCE_DEBUG) && WARN_ABOUT_NON_PDF_OPERATIONS
 #define notPossibleInPDFAssert jassertfalse
#else
 #define notPossibleInPDFAssert
#endif

//==============================================================================
PDFWriter::PDFWriter (OutputStream &out_, const int dpi_, const bool isColourPrint_)
    : dpi (dpi_),
	  isColourPrint(isColourPrint_),
	  out(out_)
{
}

PDFWriter::~PDFWriter()
{
	delete currentGraphics;
}

void PDFWriter::beginPrinting()
{
	if(out.getPosition())
	{
		jassertfalse
	}
	if(xref.size())
	{
		jassertfalse
	}
	out << "%PDF-1.4\n";
	xref.add(0);
}

void PDFWriter::endPrinting()
{
	int pageFirst = xref.size();
	int pageParent = pageFirst + pages.size();
	for (int p = 0; p < pages.size(); p++)
	{
		outBeginObject();
		out << "<</Type /Page /Parent "
			<< pageParent
			<< " 0 R /MediaBox [0 0 612 792] /Contents "
			<< pages[p]
			<< " 0 R >>";
		outEndObject();
	}
	outBeginObject();
	out << "<</Type /Pages /Kids [";
	for (int p = pageFirst; p < pageParent; p++)
	{
		out << p << " 0 R ";
	}
	out << "] /Count " << pages.size() << ">>";
	outEndObject();

	//TODO: write pages, Root and Info

	int startxref=(int)out.getPosition();
	out << "xref\n0 " << xref.size() << "\n0000000000 65535 f \n";
	for (int i = 1; i < xref.size(); i++){
		int j = xref[i];
		for (int k=1000000000;k;k/=10){
			out.writeByte('0'+j/k%10);
		}
		out << " 00000 n \n";
  	}
	out << "trailer\n<< /Size " << xref.size()
		<< " /Root " << (xref.size() - 1)
		<< " 0 R /Info " << (xref.size() - 2)
		<< " 0 R\n>>\n"
		<< "startxref\n" << startxref
		<< "%%EOF\n";
}

Graphics *PDFWriter::beginPage(PageSize pageSize, Orientation orientation)
{
	if(currentGraphics)
	{
		jassertfalse // missing endPage()
	}
	return currentGraphics = new Graphics(this);
}

void PDFWriter::endPage()
{
	if (!currentGraphics)
	{
		jassertfalse // missing beginPage()
	}
	delete currentGraphics;
	currentGraphics = NULL;

	pages.add(outBeginObject());
	int size=(int)contentBuffer.getDataSize();
	out << "<</Length " << size << ">>\nstream\n";
	out.write(contentBuffer.getData(), size);
	out << "\nendstream\n";
	outEndObject();
}

//==============================================================================

bool PDFWriter::isVectorDevice() const
{
	return true;
}

void PDFWriter::setOrigin (int x, int y)
{
}

bool PDFWriter::clipRegionIntersects (const juce::Rectangle<int> &r)
{
	// Dummy
	return true;
}

bool PDFWriter::isClipEmpty () const
{
	// Dummy
	return false;
}

const Rectangle<int> PDFWriter::getClipBounds() const
{
	// Dummy
    return Rectangle<int>(-500000000, -500000000, 1000000000, 1000000000);
}

int PDFWriter::outBeginObject()
{
	int i=xref.size();
	xref.add((int)out.getPosition());
	out << i << " 0 obj\n";
	return i;
}

void PDFWriter::outEndObject()
{
	out << "endobj\n";
}

void PDFWriter::contentOut(const Rectangle<int> &rect)
{
	contentBuffer
		<< rect.getX() << " "
		<< rect.getY() << " "
		<< rect.getWidth() << " "
		<< rect.getHeight()	<< " re ";
}

void PDFWriter::contentOut(float f)
{
	//TODO: no exponential notation
	contentBuffer << f << " ";
}

void PDFWriter::contentOut(const juce::Path &path)
{
	for (Path::Iterator i(path); i.next();)
	{
		switch(i.elementType)
		{
		case Path::Iterator::startNewSubPath:
			contentOut(i.x1);
			contentOut(i.y1);
			contentBuffer << "m ";
			break;
		case Path::Iterator::closePath:
			contentBuffer << "h ";
			break;
		case Path::Iterator::lineTo:
			contentOut(i.x1);
			contentOut(i.y1);
			contentBuffer << "l ";
			break;
		case Path::Iterator::quadraticTo:
			// Quadratic is emulated by cubic
			contentOut(i.x1);
			contentOut(i.y1);
			contentOut(i.x1);
			contentOut(i.y1);
			contentOut(i.x2);
			contentOut(i.y2);
			contentBuffer << "c ";
			break;
		case Path::Iterator::cubicTo:
			contentOut(i.x1);
			contentOut(i.y1);
			contentOut(i.x2);
			contentOut(i.y2);
			contentOut(i.x3);
			contentOut(i.y3);
			contentBuffer << "c ";
			break;
		}
	}
}

bool PDFWriter::clipToRectangle (const Rectangle<int>& r)
{
	contentOut(r);
	contentBuffer << "W n ";
	return true;
}

bool PDFWriter::clipToRectangleList (const RectangleList& clipRegion)
{
	if(!clipRegion.isEmpty())
	{
		for (int i=0; i<clipRegion.getNumRectangles(); i++)
		{
			contentOut(clipRegion.getRectangle(i));
		}
		contentBuffer << "W n ";
	}
	return true;
}

void PDFWriter::excludeClipRectangle (const Rectangle<int>& r)
{
	// Not implemented
}

void PDFWriter::clipToPath (const Path& path, const AffineTransform& transform)
{
	Path p(path);
	p.applyTransform(transform);
	contentOut(p);
	contentBuffer << "W n "; 
}

void PDFWriter::clipToImageAlpha (const Image& sourceImage, const Rectangle<int>& srcClip, const AffineTransform& transform)
{
	// Not implemented
}

void PDFWriter::fillRect(const juce::Rectangle<int> &r, const bool replaceExistingContents)
{
	contentOut(r);
	contentBuffer << "f ";
}

void PDFWriter::fillPath(const Path &path, const AffineTransform &transform)
{
	Path p(path);
	p.applyTransform(transform);
	contentOut(p);
	contentBuffer << "f ";
}

void PDFWriter::setFill (const FillType& fillType)
{
}

void PDFWriter::setOpacity (float opacity)
{
}

void PDFWriter::setInterpolationQuality (Graphics::ResamplingQuality quality)
{
}

void PDFWriter::drawImage (const Image& sourceImage, const Rectangle<int>& srcClip,
							const AffineTransform& transform, const bool fillEntireClipAsTiles)
{
    const int w = jmin (sourceImage.getWidth(), srcClip.getRight());
    const int h = jmin (sourceImage.getHeight(), srcClip.getBottom());

	/*
    writeClip();

    out << "gsave ";
    writeTransform (transform.translated ((float) stateStack.getLast()->xOffset, (float) stateStack.getLast()->yOffset)
                             .scaled (1.0f, -1.0f));

    RectangleList imageClip;
    sourceImage.createSolidAreaMask (imageClip, 0.5f);
    imageClip.clipTo (srcClip);

    out << "newpath ";
    int itemsOnLine = 0;

    for (RectangleList::Iterator i (imageClip); i.next();)
    {
        if (++itemsOnLine == 6)
        {
            out << '\n';
            itemsOnLine = 0;
        }

        const Rectangle& r = *i.getRectangle();

        out << r.getX() << ' ' << r.getY() << ' ' << r.getWidth() << ' ' << r.getHeight() << " pr ";
    }

    out << " clip newpath\n";

    out << w << ' ' << h << " scale\n";
    out << w << ' ' << h << " 8 [" << w << " 0 0 -" << h << ' ' << (int) 0 << ' ' << h << " ]\n";

    writeImage (sourceImage, srcClip.getX(), srcClip.getY(), srcClip.getWidth(), srcClip.getHeight());

    out << "false 3 colorimage grestore\n";
    needToClip = true;
	*/
}

void PDFWriter::setFont (const Font& newFont)
{
}

Font PDFWriter::getFont()
{
	// Dummy
	return NULL;
}

void PDFWriter::drawGlyph (int glyphNumber, const AffineTransform& transform)
{
}

//==============================================================================

void PDFWriter::saveState()
{
}

void PDFWriter::restoreState()
{
}

//==============================================================================
void PDFWriter::drawLine (double x1, double y1, double x2, double y2)
{
    Path p;
    p.startNewSubPath((float)x1, (float)y1);
	p.lineTo((float) x2, (float) y2);
	contentOut(p);
	contentBuffer << "S ";
}

void PDFWriter::drawVerticalLine(const int x, double top, double bottom)
{
    drawLine (x, top, x, bottom);
}

void PDFWriter::drawHorizontalLine (const int y, double left, double right)
{
    drawLine (left, y, right, y);
}

END_JUCE_NAMESPACE
