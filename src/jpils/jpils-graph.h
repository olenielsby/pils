/* This file is public domain */
#ifndef _PLUMMING_JPILS_GRAPH_H_
#define _PLUMMING_JPILS_GRAPH_H_
#include "jpils-thread.h"

namespace PILS
{
	class PredefinedGraphNameGraph;
	class PredefinedGraphName : public PredefinedName
	{
	public:
		static const PilsString *const namespace_;
		static const PredefinedGraphNameGraph graph;
		static const PredefinedGraphName background;
		static const PredefinedGraphName curve;
		static const PredefinedGraphName shape;
		static const PredefinedGraphName at;
		static const PredefinedGraphName scale;
		static const PredefinedGraphName gradient;
		static const PredefinedGraphName linear;
		static const PredefinedGraphName circular;
		static const PredefinedGraphName ink;
		static const PredefinedGraphName stroke;
		static const PredefinedGraphName round;
		static const PredefinedGraphName sharp;
		static const PredefinedGraphName font;
		static const PredefinedGraphName image;
		static const PredefinedGraphName align;
		static const PredefinedGraphName size;
		static const PredefinedGraphName outsize;
		static const PredefinedGraphName width;
		static const PredefinedGraphName height;
	protected:
		PredefinedGraphName(const PILS_CHAR *name)
			: PredefinedName(namespace_, name)
		{}
	};

	class PredefinedGraphNameGraph : public PredefinedGraphName, public Recognizer
	{
	private:
		friend class PredefinedGraphName;
		PredefinedGraphNameGraph(const PILS_CHAR *name)
			: PredefinedGraphName(name)
		{}
        void compileTypecheck(Compiling &compiling, const CallWho &pattern) const override;
        bool recognizing(const PilsGraph &thing) override {return true;}
	};

	class PredefinedGraphNameColor : public PredefinedGraphName
	{
	private:
		friend class PredefinedGraphName;
		PredefinedGraphNameColor(const PILS_CHAR *name)
			: PredefinedGraphName(name)
		{}
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
	};

	class FontNamespace : public PilsString
	{
	public:
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
		bool isBold() const {return ((this - table) & 2) != 0;}
		bool isItalic() const {return ((this - table) & 1) != 0;}
	private:
		static const FontNamespace table[4];
		FontNamespace(const PILS_CHAR *text)
			: PilsString(text, strlen(text))
		{}
		char slack[30];
	};

	class FontName : public ClicheShort
	{
	public:
		FontName(const HashedConstant *&link, const FontNamespace *head, const PilsString *name)
			: ClicheShort(link, head, name), font(juce::String::fromUTF8(name->value, name->count->value), 0, 0)
		{
			font.setBold(head->isBold());
			font.setItalic(head->isItalic());
		}
        const ClicheShort *newCliche(const HashedConstant *&link, const Constant *a) const override;
        size_t unlinkAndGetSize() override;
		juce::Font font;
	};

	class PilsFont : public ClicheShort
	{
	public:
		PilsFont(const HashedConstant *&link, const FontName *head, const Number *value, float size);
        bool recognize(Recognizer &recognizer) const override;
        size_t unlinkAndGetSize() override;
		static const juce::Font *cast(const Any *thing);
		juce::Font font;
	};

	class Drawing;
	class Bounding;
	class StrokeWalk;
	class Box
	{
	public:
		float x, y, width, height;
		Box(const juce::Path &path)
		{
			Rectangle<float> bounds = path.getBounds();
			x = bounds.getX();
			y = bounds.getY();
			width = bounds.getWidth();
			height = bounds.getHeight();
		}
		Box(const juce::String &text, const juce::Font &font)
			: x(0), y(-font.getAscent()), width(font.getStringWidthFloat(text)), height(font.getHeight())
		{}
		Box(const juce::Image &image, float x, float y)
			: x(x), y(y), width((float)image.getWidth()), height((float)image.getHeight())
		{}
		Box(const juce::Drawable &drawable)
		{
			const Rectangle<float> bounds = drawable.getDrawableBounds();
			x = bounds.getX();
			y = bounds.getY();
			width = bounds.getWidth();
			height = bounds.getHeight();
		}
		bool isEmpty() const {return width == -1.0f;}
		Box applyTransform(const juce::AffineTransform &transform) const
		{
			Box box(*this);
			transform.transformPoint(box.x, box.y);
			float box_width = box.width;
			box.width = box.width * transform.mat00 + box.height * transform.mat01;
			box.height = box_width * transform.mat10 + box.height * transform.mat11;
			return box;
		}
	protected:
		Box() : x(0.0f), y(0.0f), width(-1.0f), height(-1.0f) {}
	};

	class PilsGraph
	{
	public:
		static const PilsGraph *cast(const Any *thing);
		virtual bool draw(Drawing &drawing) const = 0;
		virtual bool strokeWalk(StrokeWalk &strokeWalk) const = 0;
		const Box box;
	protected:
		PilsGraph(const Box box) : box(box) {}
	private:
		virtual const Step *calling(Runner &run, const Constant &call) const = 0;
	};

	class BuiltinClicheGraph : public BuiltinClicheTiny
	{
	public:
		static const BuiltinClicheGraph singleton;
        const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const override;
        const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const override;
        const NodeConstantShort *newNode(const HashedConstant *&link, const Empty *value) const;
        const NodeConstantShort *newNode(const HashedConstant *&link, const Constant *value) const;
	private:
		BuiltinClicheGraph()
			: BuiltinClicheTiny(&PredefinedGraphName::graph)
		{}
	};

	class GraphNode : public NodeConstantTiny
	{
	public:
		GraphNode(const HashedConstant *&link, const BuiltinClicheGraph &cliche, const Constant *value)
			: NodeConstantTiny(link, cliche, value)
		{}
        const Any *specialCall(Runner &run, const ReallySpecial &special) const override;
	};

	class BuiltinClichePathBase : public BuiltinClicheTiny
	{
	public:
        const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const override;
		virtual bool draw(const juce::Path &path, Drawing &drawing) const = 0;
	protected:
		virtual void closePath(juce::Path &path) const = 0;
		BuiltinClichePathBase(const ClicheShort *name)
			: BuiltinClicheTiny(name)
		{}
	};

	class BuiltinClicheCurve : public BuiltinClichePathBase
	{
	public:
		static const BuiltinClicheCurve singleton;
	private:
        void closePath(juce::Path &path) const override;
        bool draw(const juce::Path &path, Drawing &drawing) const override;
		BuiltinClicheCurve()
			: BuiltinClichePathBase(&PredefinedGraphName::curve)
		{}
	};

	class BuiltinClicheShape : public BuiltinClichePathBase
	{
	public:
		static const BuiltinClicheShape singleton;
	private:
        void closePath(juce::Path &path) const override;
        bool draw(const juce::Path &path, Drawing &drawing) const override;
		BuiltinClicheShape()
			: BuiltinClichePathBase(&PredefinedGraphName::shape)
		{}
	};

	class PilsGraphTiny : public NodeConstantTiny, public PilsGraph
	{
	public:
		PilsGraphTiny(const HashedConstant *&link, const BuiltinClicheTiny &cliche, const Constant *value, Box box)
			: NodeConstantTiny(link, cliche, value), PilsGraph(box)
		{}
        bool recognize(Recognizer &recognizer) const override;
        virtual size_t unlinkAndGetSize() override = 0;
        const Step *calling(Runner &run, const Constant &call) const override;
	};

	class PathNode : public PilsGraphTiny
	{
	public:
		PathNode(const HashedConstant *&link, const BuiltinClichePathBase &cliche, const Constant *value, const juce::Path path)
			: PilsGraphTiny(link, cliche, value, path), path(path)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
        size_t unlinkAndGetSize() override;
		const juce::Path path;
	};

	class BuiltinClicheDuplo
		: public BuiltinClicheTrailer
	{
	protected:
		BuiltinClicheDuplo(const Constant *name)
			: BuiltinClicheTrailer(name, &Empty::singleton, name)
		{}
	private:
		void *dummy;
	};

	class BuiltinClicheStroke
		: public BuiltinClicheTrailer
	{
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheStroke(const Constant *head, const Constant *attribute, juce::PathStrokeType::JointStyle jointStyle, juce::PathStrokeType::EndCapStyle endCapStyle)
			: BuiltinClicheTrailer(head, &Empty::singleton, attribute), jointStyle(jointStyle), endCapStyle(endCapStyle)
		{}
		void *dummy;
		const juce::PathStrokeType::JointStyle jointStyle;
		const juce::PathStrokeType::EndCapStyle endCapStyle;
		static const BuiltinClicheStroke instance[];
	};

	class NodeConstantTrailer2 : public NodeConstantTrailer
	{
	protected:
		NodeConstantTrailer2(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value)
			: NodeConstantTrailer(link, cliche, value)
		{}
	private:
		void *dummy;
	};

	class DuploDrawable : public NodeConstantTrailer2, public PilsGraph
	{
	protected:
		DuploDrawable(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, const Box box)
			: NodeConstantTrailer2(link, cliche, value), PilsGraph(box)
		{}
        size_t unlinkAndGetSize() override;
	private:
        const Step *calling(Runner &run, const Constant &call) const override;
        bool recognize(Recognizer &recognizer) const override;
		void *dummy;
	};

	class DummyDrawable : public DuploDrawable
	{
	public:
		DummyDrawable(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, const Box box)
			: DuploDrawable(link, cliche, value, box)
		{}
	private:
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
	};

	class BuiltinClicheBackground : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheBackground singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheBackground()
			: BuiltinClicheDuplo(&PredefinedGraphName::background)
		{}
	};

	class TransformerNode : public DuploDrawable
	{
	public:
		TransformerNode(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, const juce::AffineTransform &transform, const Box box)
			: DuploDrawable(link, cliche, value, box.applyTransform(transform)), transform(transform)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
        bool bounding(Bounding &bounding) const;
		const juce::AffineTransform transform;
        size_t unlinkAndGetSize() override;
	};

	class BuiltinClicheAt : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheAt singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheAt()
			: BuiltinClicheDuplo(&PredefinedGraphName::at)
		{}
	};

	class BuiltinClicheScale : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheScale singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheScale()
			: BuiltinClicheDuplo(&PredefinedGraphName::scale)
		{}
	};

	class BuiltinClicheAlign : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheAlign singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheAlign()
			: BuiltinClicheDuplo(&PredefinedGraphName::align)
		{}
	};

	class BuiltinClicheGraphSize : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheGraphSize singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheGraphSize()
			: BuiltinClicheDuplo(&PredefinedGraphName::size)
		{}
	};

	class BuiltinClicheGraphOutsize : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheGraphOutsize singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheGraphOutsize()
			: BuiltinClicheDuplo(&PredefinedGraphName::outsize)
		{}
	};

	class BuiltinClicheInk : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheInk singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheInk()
			: BuiltinClicheDuplo(&PredefinedGraphName::ink)
		{}
	};

	class BuiltinClicheFont : public BuiltinClicheDuplo
	{
	private:
		static const BuiltinClicheFont singleton;
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		BuiltinClicheFont()
			: BuiltinClicheDuplo(&PredefinedGraphName::font)
		{}
	};

	class BuiltinClicheGradient : public BuiltinClicheDuplo
	{
	private:
        const NodeConstantLong *newNodeConstant(const HashedConstant *&link, const Constant *const *value) const override;
		static const BuiltinClicheGradient linear;
		static const BuiltinClicheGradient circular;
		BuiltinClicheGradient(const PredefinedGraphName *name)
			: BuiltinClicheDuplo(name)
		{}
	};

	class GradientNode : public NodeConstantTrailer
	{
	public:
		GradientNode(const HashedConstant *&link, const BuiltinClicheGradient &cliche, const Constant *const *value, const juce::ColourGradient *gradient)
			: NodeConstantTrailer(link, cliche, value), gradient(gradient)
		{}
        bool recognize(Recognizer &recognizer) const override;
        size_t unlinkAndGetSize() override;
	private:
		const Constant *dummy;
		const juce::ColourGradient *gradient;
	};

	class BrushNode : public DuploDrawable
	{
	public:
		BrushNode(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, FillType &fillType, const Box box)
			: DuploDrawable(link, cliche, value, box), fillType(fillType)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
        size_t unlinkAndGetSize() override;
	protected:
		FillType fillType;
	};

	class BackgroundNode : public BrushNode
	{
	public:
		BackgroundNode(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, FillType &fillType, const Box box)
			: BrushNode(link, cliche, value, fillType, box)
		{}
        bool draw(Drawing &drawing) const override;
	};

	class StrokeNode : public DuploDrawable
	{
	public:
		StrokeNode(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, const juce::Path path)
			: DuploDrawable(link, cliche, value, path), path(path)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
		const juce::Path path;
        size_t unlinkAndGetSize() override;
	};

	class TextNode : public DuploDrawable
	{
	public:
		TextNode(const HashedConstant *&link, const ClicheTrailer &cliche, const Constant *const *value, const juce::Font &font, const juce::String &text)
			: DuploDrawable(link, cliche, value, Box(text, font)), font(font), text(text)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
		const juce::Font &font;
		const juce::String text;
        size_t unlinkAndGetSize() override;
	};

	class ImageNode;
	class BuiltinClicheImage : public BuiltinClicheTiny
	{
	private:
		BuiltinClicheImage()
			: BuiltinClicheTiny(&PredefinedGraphName::image)
		{}
		static const BuiltinClicheImage singleton;
        const NodeConstantShort *newNode(const HashedConstant *&link, const PilsString *value) const override;
        const NodeConstantShort *newNode(const HashedConstant *&link, const Special *value) const override;
        const NodeConstantShort *newNode(const HashedConstant *&link, const NodeConstant *value) const override;
        const NodeConstantShort *newNode(const HashedConstant *&link, const ListConstant *value) const override;
        const ImageNode *newImageNode(const HashedConstant *&link, const Constant *value) const;
	};

	class ImageNode : public PilsGraphTiny
	{
	public:
		ImageNode(const HashedConstant *&link, const BuiltinClicheImage &cliche, const Constant *value, const juce::Image &image, bool own, float x = 0.0f, float y = 0.0f)
			: PilsGraphTiny(link, cliche, value, Box(image, x, y)), image(image), own(own), x(x), y(y)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
        bool recognize(Recognizer &recognizer) const override;
        size_t unlinkAndGetSize() override;
		const juce::Image image;
		const bool own;
		const float x, y;
	};

	class JuceDrawableNode : public PilsGraphTiny
	{
	public:
		JuceDrawableNode(const HashedConstant *&link, const BuiltinClicheImage &cliche, const Constant *value, const juce::Drawable *drawable, bool own)
			: PilsGraphTiny(link, cliche, value, Box(*drawable)), drawable(drawable), own(own)
		{}
        bool draw(Drawing &drawing) const override;
        bool strokeWalk(StrokeWalk &strokeWalk) const override;
        bool recognize(Recognizer &recognizer) const override;
		const juce::Drawable *const drawable;
		const bool own;
        size_t unlinkAndGetSize() override;
	};
}
#endif
