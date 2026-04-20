/* This file is public domain */
#include "pipe.h"
#include "statement.h"
//#include "pilsplug/plughost.h"
#include "jpils-thread.h"
#include "jpils-binding-base.h"
#include "jpils-graph.h"

namespace PILS
{
	class ListRecognizer : public Recognizer
	{
        bool recognizing(const Any *const *elements, size_t count) override
		{
			for(size_t i = 0; i < count; i++)
			{
				if (!elements[i]->recognize(*this))
					return false;
			}
			return true;
		}
	};

	class Drawing : public ListRecognizer
	{
	public:
		Drawing(juce::Graphics &graphics)
			: graphics(graphics), transform(&juce::AffineTransform::identity)
		{}
        bool recognizing(const PilsGraph &drawable) override
		{
			return drawable.draw(*this);
		}
        bool recognizing(const juce::Colour &color) override
		{
			graphics.fillAll(color);
			return true;
		}
		juce::Graphics &graphics;
		const juce::AffineTransform *transform;
	};

	class StrokeWalk : public ListRecognizer
	{
	public:
		StrokeWalk() : transform(&juce::AffineTransform::identity) {}
        bool recognizing(const PilsGraph &drawable) override
		{
			return drawable.strokeWalk(*this);
		}
        bool recognizing(const juce::Colour &color) override
		{
			return true;
		}
		const juce::AffineTransform *transform;
		juce::Path path;
	};

	class BrushMaker : public Recognizer
	{
	public:
        bool recognizing(const juce::Colour &color) override
		{
			fillType.setColour(color);
			return true;
		}
        bool recognizing(const PilsColor &color) override
		{
			fillType.setColour(juce::Colour(color.value));
			return true;
		}
        bool recognizing(const juce::ColourGradient &gradient) override
		{
			fillType.setGradient(gradient);
			return true;
		}
		juce::FillType fillType;
	};

	void PredefinedGraphNameGraph::compileTypecheck(Compiling &compiling, const CallWho &pattern) const
	{
		const Recognizer &recognizer = *this;
		compiling.check_(const_cast<Recognizer &>(recognizer));
		pattern.whoAttribute()->compilePattern(compiling);
	}

	const PilsGraph *PilsGraph::cast(const Any *thing)
	{
		class PilsDrawableRecognizer : public Recognizer
		{
		public:
            bool recognizing(const PilsGraph &drawable) override
			{
				value = &drawable;
				return true;
			}
			const PilsGraph *value;
		}
		recognizer;
		if (thing->recognize(recognizer)) return recognizer.value;
		else return nullptr;
	}

	class Bounding : public Box, public ListRecognizer
	{
	public:
        bool recognizing(const PilsGraph &drawable) override
		{
			const Box &box = drawable.box;
			if (!box.isEmpty())
			{
				if (!isEmpty())
				{
					if (x > box.x)
					{
						width += x - box.x;
						x = box.x;
					}
					if (x + width < box.x + box.width) width = box.x - x + box.width;
					if (y > box.y)
					{
						height += y - box.y;
						y = box.y;
					}
					if (y + height < box.y + box.height) height = box.y - y + box.height;
				}
				else
				{
					x = box.x;
					y = box.y;
					width = box.width;
					height = box.height;
				}
			}
			return true;
		}
	};

	const NodeConstantShort *BuiltinClicheGraph::newNode(const Constant *&link, const NodeConstant *value) const
	{
		return new (Heap::allocate(sizeof(GraphNode))) const GraphNode(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheGraph::newNode(const Constant *&link, const ListConstant *value) const
	{
		return new (Heap::allocate(sizeof(GraphNode))) const GraphNode(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheGraph::newNode(const Constant *&link, const Empty *value) const
	{
		return new (Heap::allocate(sizeof(GraphNode))) const GraphNode(link, *this, value);
	}

	const NodeConstantShort *BuiltinClicheGraph::newNode(const Constant *&link, const Constant *value) const
	{
		return new (Heap::allocate(sizeof(GraphNode))) const GraphNode(link, *this, value);
	}

	const Any *GraphNode::specialCall(Runner &run, const ReallySpecial &special) const
	{
		if (juce::Graphics *graphics = special.as_Graphics())
		{
			Drawing drawing(*graphics);
			if (element[0]->recognize(drawing))
			{
				special.addReference();
				return &special;
			}
		}
		return NodeConstantTiny::specialCall(run, special);
	}

	bool PilsGraphTiny::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	const Step *PilsGraphTiny::calling(Runner &run, const Constant &call) const
	{
		if (&call == &PredefinedGraphName::width)
			return run.sink->pass(run, (double)box.width);
		else if (&call == &PredefinedGraphName::height)
			return run.sink->pass(run, (double)box.height);
		else return NodeConstantTiny::calling(run, call);
	}

	const Step *DuploDrawable::calling(Runner &run, const Constant &call) const
	{
		if (&call == &PredefinedGraphName::width)
			return run.sink->pass(run, (double)box.width);
		else if (&call == &PredefinedGraphName::height)
			return run.sink->pass(run, (double)box.height);
		else return NodeConstantTrailer2::calling(run, call);
	}

	const NodeConstantShort *BuiltinClichePathBase::newNode(const Constant *&link, const ListConstant *value) const
	{
		juce::Path path;
		bool first = true;
		for (int i = 0; i < value->count->value; i++)
		{
			float f[6];
			size_t count;
			const Any *const *e;
			if (!value->element[i]->isList(e, count))
				goto bad;
			for (size_t j = 0; j < 6 && j < count; j++)
			{
				if (!e[j]->isNumber(f[j])) goto bad;
			}
			if (first)
			{
				if (count == 2)
				{
					path.startNewSubPath(f[0], f[1]);
					first = false;
				}
				else goto bad;
			}
			else
			{
				switch (count)
				{
				case 0:
					closePath(path);
					first = true;
					break;
				case 2:
					path.lineTo(f[0], f[1]);
					break;
				case 4:
					path.quadraticTo(f[0], f[1], f[2], f[3]);
					break;
				case 6:
					path.cubicTo(f[0], f[1], f[2], f[3], f[4], f[5]);
					break;
				default:
					goto bad;
				}
			}
		}
		if (first) goto bad;
		closePath(path);
		path.setUsingNonZeroWinding(false);
		return new (Heap::allocate(sizeof(PathNode))) const PathNode(link, *this, value, path);
bad:
		return new (Heap::allocate(sizeof(NodeConstantTiny))) const NodeConstantTiny(link, *this, value);
	}

	size_t PathNode::unlinkAndGetSize()
	{
		NodeConstantTiny::unlinkAndGetSize();
		path.~Path();
		return sizeof(PathNode);
	}

	bool PathNode::draw(Drawing &drawing) const
	{
		return ((BuiltinClichePathBase *)cliche)->draw(path, drawing);
	}

	bool PathNode::strokeWalk(StrokeWalk &strokeWalk) const
	{
		strokeWalk.path.addPath(path, *strokeWalk.transform);
		return true;
	}

	void BuiltinClicheShape::closePath(juce::Path &path) const
	{
		path.closeSubPath();
	}

	bool BuiltinClicheShape::draw(const juce::Path &path, Drawing &drawing) const
	{
		drawing.graphics.fillPath(path, *drawing.transform);
		return true;
	}

	void BuiltinClicheCurve::closePath(juce::Path &path) const
	{}

	bool BuiltinClicheCurve::draw(const juce::Path &path, Drawing &drawing) const
	{
		return true;
	}

	bool DuploDrawable::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	size_t DuploDrawable::unlinkAndGetSize()
	{
		NodeConstantTrailer2::unlinkAndGetSize();
		return sizeof(DuploDrawable);
	}

	bool DummyDrawable::draw(Drawing &) const
	{
		return true;
	}

	bool DummyDrawable::strokeWalk(StrokeWalk &) const
	{
		return true;
	}

	bool TransformerNode::draw(Drawing &drawing) const
	{
		const juce::AffineTransform *save = drawing.transform;
		const juce::AffineTransform transform =	this->transform.followedBy(*save);
		drawing.transform = &transform;
		bool ok = element[0]->recognize(drawing);
		drawing.transform = save;
		return ok;
	}

	bool TransformerNode::strokeWalk(StrokeWalk &strokeWalk) const
	{
		const juce::AffineTransform *save = strokeWalk.transform;
		const juce::AffineTransform transform =	this->transform.followedBy(*save);
		strokeWalk.transform = &transform;
		bool ok = element[0]->recognize(strokeWalk);
		strokeWalk.transform = save;
		return ok;
	}

	size_t TransformerNode::unlinkAndGetSize()
	{
		NodeConstantTrailer2::unlinkAndGetSize();
		transform.~AffineTransform();
		return sizeof(TransformerNode);
	}

	const NodeConstantLong *BuiltinClicheAt::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		if (const ListConstant *list = value[1]->as_ListConstant())
		{
			float x;
			float y;
			Bounding bounding;
			if (list->count->value == 2
				&& list->element[0]->isNumber(x)
				&& list->element[1]->isNumber(y)
				&& value[0]->recognize(bounding)
				)
			{
				const juce::AffineTransform translation = AffineTransform::translation(x, y);
				return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, translation, bounding);
			}
		}
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheAlign::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		float rx;
		float ry = 0;
		bool useY = false;
		Bounding bounding;
		if (const ListConstant *list = value[1]->as_ListConstant())
		{
			switch(list->count->value)
			{
			case 1:
				if (!list->element[0]->isNumber(rx)) goto bad;
				break;
			case 2:
				if (!list->element[0]->isNumber(rx)) goto bad;
				if (!list->element[1]->isNumber(ry)) goto bad;
				useY = true;
				break;
			default:
				goto bad;
			}
		}
		else if (value[1]->isNumber(rx))
		{
			ry = rx;
			useY = true;
		}
		else goto bad;
		if (value[0]->recognize(bounding))
		{
			if (bounding.isEmpty())
				return new (Heap::allocate(sizeof(DummyDrawable))) DummyDrawable(link, *this, value, bounding);
			float dx = - rx * bounding.width - bounding.x;
			float dy = useY ? - ry * bounding.height - bounding.y : 0.0f;
			return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, AffineTransform::translation(dx, dy), bounding);
		}
	bad:
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheGraphSize::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		float width;
		float height;
		Bounding bounding;
		if (const ListConstant *list = value[1]->as_ListConstant())
		{
			if (list->count->value != 2 || !list->element[0]->isNumber(width) || !list->element[1]->isNumber(height))
				goto bad;
		}
		else if (value[1]->isNumber(width))
		{
			height = width;
		}
		else goto bad;
		if (height > 0.0f && width > 0.0f && value[0]->recognize(bounding))
		{
			if (bounding.width <= 0.0f || bounding.height <= 0.0f)
				return new (Heap::allocate(sizeof(DummyDrawable))) DummyDrawable(link, *this, value, bounding);
			float scaleX = width / bounding.width;
			float scaleY = height / bounding.height;
			float scale = scaleX < scaleY ? scaleX : scaleY;
			return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, juce::AffineTransform::scale(scale, scale), bounding);
		}
	bad:
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheGraphOutsize::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		float width;
		float height;
		Bounding bounding;
		if (const ListConstant *list = value[1]->as_ListConstant())
		{
			if (list->count->value != 2 || !list->element[0]->isNumber(width) || !list->element[1]->isNumber(height))
				goto bad;
		}
		else if (value[1]->isNumber(width))
		{
			height = width;
		}
		else goto bad;
		if (height > 0.0f && width > 0.0f && value[0]->recognize(bounding))
		{
			if (bounding.width <= 0.0f || bounding.height <= 0.0f)
				return new (Heap::allocate(sizeof(DummyDrawable))) DummyDrawable(link, *this, value, bounding);
			float scaleX = width / bounding.width;
			float scaleY = height / bounding.height;
			float scale = scaleX < scaleY ? scaleY : scaleX;
			return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, juce::AffineTransform::scale(scale, scale), bounding);
		}
	bad:
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheScale::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		Bounding bounding;
		if (value[0]->recognize(bounding))
		{
			float x;
			float y;
			if (const ListConstant *list = value[1]->as_ListConstant())
			{
				if (list->count->value == 2 && list->element[0]->isNumber(x) && list->element[1]->isNumber(y))
				{
					const juce::AffineTransform translation = AffineTransform::scale(x, y);
					return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, translation, bounding);
				}
			}
			else if (value[1]->isNumber(x))
			{
				const juce::AffineTransform translation = AffineTransform::scale(x, x);
				return new (Heap::allocate(sizeof(TransformerNode))) TransformerNode(link, *this, value, translation, bounding);
			}
		}
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const ClicheShort *FontNamespace::newCliche(const Constant *&link, const Constant *a) const
	{
		if (const PilsString *name = a->as_String())
			return new (Heap::allocate(sizeof(FontName))) FontName(link, this, name);
		else return HalfbakedConstant::newCliche(link, a);
	}

	size_t FontName::unlinkAndGetSize()
	{
		ClicheShort::unlinkAndGetSize();
        font.~Font();
		return sizeof(FontName);
	}

	const ClicheShort *FontName::newCliche(const Constant *&link, const Constant *a) const
	{
		float size;
		if (a->isNumber(size))
			return new (Heap::allocate(sizeof(PilsFont))) PilsFont(link, this, (const Number *)a, size);
		else return HalfbakedConstant::newCliche(link, a);
	}

	PilsFont::PilsFont(const Constant *&link, const FontName *head, const Number *number, float size)
		: ClicheShort(link, head, number), font(head->font)
	{
		font.setHeight(size);
	}

	size_t PilsFont::unlinkAndGetSize()
	{
		font.~Font();
		ClicheShort::unlinkAndGetSize();
		return sizeof(PilsFont);
	}

	const juce::Font *PilsFont::cast(const Any *thing)
	{
		class fontRecognizer : public Recognizer
		{
            bool recognizing(const PilsFont &thing) override
			{
				font = &thing.font;
				return true;
			}
		public:
			const juce::Font *font;
		}
		fontRecognizer;
		if (thing->recognize(fontRecognizer))
			return fontRecognizer.font;
		else return nullptr;
	}

	bool PilsFont::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	const NodeConstantLong *BuiltinClicheFont::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		if (const juce::Font *font = PilsFont::cast(value[1]))
		{
			if (const PilsString *text = value[0]->as_String())
			{
				return new (Heap::allocate(sizeof(TextNode))) TextNode(link, *this, value, *font, juce::String::fromUTF8(text->value, text->count->value));
			}
		}
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheInk::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		BrushMaker brush;
		Bounding bounding;
		if (value[1]->recognize(brush) && value[0]->recognize(bounding))
		{
			if (bounding.isEmpty())
				return new (Heap::allocate(sizeof(DummyDrawable))) DummyDrawable(link, *this, value, bounding);
			else return new (Heap::allocate(sizeof(BrushNode))) BrushNode(link, *this, value, brush.fillType, bounding);
		}
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	bool BrushNode::draw(Drawing &drawing) const
	{
		bool ok;
		drawing.graphics.saveState();
		drawing.graphics.setFillType(fillType);
		ok = element[0]->recognize(drawing);
		drawing.graphics.restoreState();
		return ok;
	}

	bool BrushNode::strokeWalk(StrokeWalk &strokeWalk) const
	{
		return element[0]->recognize(strokeWalk);
	}

	size_t BrushNode::unlinkAndGetSize()
	{
		fillType.~FillType();
		NodeConstantLong::unlinkAndGetSize();
		return sizeof(BrushNode);
	}

	bool BackgroundNode::draw(Drawing &drawing) const
	{
		bool ok;
		juce::Graphics &graphics = drawing.graphics;
		graphics.saveState();
		graphics.setFillType(fillType);
		graphics.fillRect(graphics.getClipBounds());
		ok = element[0]->recognize(drawing);
		graphics.restoreState();
		return ok;
	}

	const NodeConstantLong *BuiltinClicheBackground::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		BrushMaker brush;
		Bounding bounding;
		if (value[1]->recognize(brush) && value[0]->recognize(bounding))
			return new (Heap::allocate(sizeof(BackgroundNode))) BackgroundNode(link, *this, value, brush.fillType, bounding);
		return BuiltinClicheDuplo::newNodeConstant(link, value);
	}

	const NodeConstantLong *BuiltinClicheStroke::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		float strokeThickness;
		StrokeWalk strokeWalk;
		if (value[1]->isNumber(strokeThickness) && value[0]->recognize(strokeWalk))
		{
			if (strokeWalk.path.isEmpty())
			{
				Box box(strokeWalk.path);
				return new (Heap::allocate(sizeof(DummyDrawable))) DummyDrawable(link, *this, value, box);
			}
			juce::PathStrokeType strokeType(strokeThickness, jointStyle, endCapStyle);
			strokeType.createStrokedPath(strokeWalk.path, strokeWalk.path);
			return new (Heap::allocate(sizeof(StrokeNode))) StrokeNode(link, *this, value, strokeWalk.path);
		}
		return BuiltinClicheTrailer::newNodeConstant(link, value);
	}

	bool StrokeNode::draw(Drawing &drawing) const
	{
		drawing.graphics.fillPath(path, *drawing.transform);
		return true;
	}

	bool StrokeNode::strokeWalk(StrokeWalk &strokeWalk) const
	{
		strokeWalk.path.addPath(path, *strokeWalk.transform);
		return true;
	}

	size_t StrokeNode::unlinkAndGetSize()
	{
		DuploDrawable::unlinkAndGetSize();
		path.~Path();
		return sizeof(StrokeNode);
	}

	const NodeConstantLong *BuiltinClicheGradient::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
		juce::ColourGradient *gradient = new juce::ColourGradient();
		{
			const ListConstant* list = value[1]->as_ListConstant();
			if (!list) goto bad;
			int count = list->count->value;
			if (count > 4) goto bad;
			float f[4];
			for (int i = 0; i < count; i++)
			{
				if (!list->element[i]->isNumber(f[i])) goto bad;
			}
			switch(count)
			{
			case 4:
				gradient->point1.setX(f[0]);
				gradient->point1.setY(f[1]);
				gradient->point2.setX(f[2]);
				gradient->point2.setY(f[3]);
				break;
			default:
				goto bad;
			}
			if (!(list = value[0]->as_ListConstant())) goto bad;
			count = list->count->value;
			if (count < 2) goto bad;
			class StopRecognizer : public Recognizer
			{
			public:
				class ColorRecognizer : public Recognizer
				{
				public:
					const juce::Colour *color;
                    bool recognizing(const juce::Colour &thing) override
					{
						color = &thing;
						return true;
					}
                    bool recognizing(const PilsColor &thing) override
					{
						color = (const juce::Colour *)&thing.value;
						return true;
					}
				} color;
				double at;
                virtual bool recognizing(const Any *const *elements, size_t count) override
				{
					return
						count == 2
						&& elements[0]->recognize(color)
						&& elements[1]->isNumber(at)
						&& at >= 0
						&& at <= 1.0;
				}
			}
			stop;
			for (int i = 0; i < count; i++)
			{
				if (!list->element[i]->recognize(stop)) goto bad;
				if (i == 0 && stop.at != 0.0 || i == count - 1 && stop.at != 1.0) goto bad;
				gradient->addColour(stop.at, *stop.color.color);
			}
			gradient->isRadial = this == &circular;
			return new (Heap::allocate(sizeof(GradientNode))) GradientNode(link, *this, value, gradient);
		}
	bad:
		delete gradient;
		return BuiltinClicheTrailer::newNodeConstant(link, value);
	}

	bool GradientNode::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*gradient);
	}

	size_t GradientNode::unlinkAndGetSize()
	{
		NodeConstantTrailer::unlinkAndGetSize();
		delete gradient;
		return sizeof(GradientNode);
	}

	const NodeConstantShort *BuiltinClicheImage::newNode(const Constant *&link, const PilsString *value) const
	{
		const juce::Image image = juce::ImageFileFormat::loadFrom(value->value, value->count->value);
		if (image.isValid())
			return new (Heap::allocate(sizeof(ImageNode))) ImageNode(link, *this, value, image, true);
        // else if (const juce::Drawable *drawable = juce::Drawable::createFromImageData(value->value, value->count->value))
        // 	return new (Heap::allocate(sizeof(JuceDrawableNode))) JuceDrawableNode(link, *this, value, drawable, true);
		else return BuiltinClicheTiny::newNode(link, value);
	}

	const NodeConstantShort *BuiltinClicheImage::newNode(const Constant *&link, const Special *value) const
	{
		class ImageNodeBuilder : public Recognizer
		{
		public:
			ImageNodeBuilder(const Constant *&link, const BuiltinClicheImage &cliche, const Special *value)
				: link(link), cliche(cliche), value(value)
			{}
			const NodeConstantTiny *result;
		private:
			const Constant *&link;
			const BuiltinClicheImage &cliche;
			const Special *value;
            bool recognizing(const juce::Image &image) override
			{
				result = new (Heap::allocate(sizeof(ImageNode))) ImageNode(link, cliche, value, image, false);
				return true;
			}
            bool recognizing(const juce::Drawable &drawable) override
			{
				result = new (Heap::allocate(sizeof(JuceDrawableNode))) JuceDrawableNode(link, cliche, value, &drawable, false);
				return true;
			}
		} recognizer(link, *this, value);
		if (value->recognize(recognizer))
			return recognizer.result;
		else return BuiltinClicheTiny::newNode(link, value);
	}

	const NodeConstantShort *BuiltinClicheImage::newNode(const Constant *&link, const ListConstant *value) const
	{
		if (const ImageNode *node = newImageNode(link, value))
			return node;
		else return BuiltinClicheTiny::newNode(link, value);
	}

	const NodeConstantShort *BuiltinClicheImage::newNode(const Constant *&link, const NodeConstant *value) const
	{
		if (const ImageNode *node = newImageNode(link, value))
			return node;
		else return BuiltinClicheTiny::newNode(link, value);
	}

	const ImageNode *BuiltinClicheImage::newImageNode(const Constant *&link, const Constant *value) const
	{
		Bounding bounding;
		if (!value->recognize(bounding) || bounding.isEmpty()) return nullptr;
		juce::Image image(Image::ARGB, (int)bounding.width, (int)bounding.height, true);
		juce::Graphics graphics(image);
		juce::AffineTransform transform = juce::AffineTransform::translation(-bounding.x, -bounding.y);
		Drawing drawing(graphics);
		drawing.transform = &transform;
		value->recognize(drawing);
		return new (Heap::allocate(sizeof(ImageNode))) ImageNode(link, *this, value, image, true, bounding.x, bounding.y);
	}

	bool ImageNode::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(image) || recognizer.recognizing(*this);
	}

	bool ImageNode::draw(Drawing &drawing) const
	{
		drawing.graphics.saveState();
		juce::AffineTransform transform = juce::AffineTransform::translation(x, y).followedBy(*drawing.transform);
		drawing.graphics.drawImageTransformed(image, transform);
		drawing.graphics.restoreState();
		return true;
	}

	bool ImageNode::strokeWalk(StrokeWalk &) const
	{
		return true;
	}

	size_t ImageNode::unlinkAndGetSize()
	{
		image.~Image();
		NodeConstantTiny::unlinkAndGetSize();
		return sizeof(ImageNode);
	}

	bool JuceDrawableNode::recognize(Recognizer &recognizer) const
	{
		return recognizer.recognizing(*this);
	}

	bool JuceDrawableNode::draw(Drawing &drawing) const
	{
		drawing.graphics.saveState();
		drawable->draw(drawing.graphics, 1, *drawing.transform);
		drawing.graphics.restoreState();
		return true;
	}

	bool JuceDrawableNode::strokeWalk(StrokeWalk &) const
	{
		return true;
	}

	size_t JuceDrawableNode::unlinkAndGetSize()
	{
		if (own) delete drawable;
		NodeConstantTiny::unlinkAndGetSize();
		return sizeof(JuceDrawableNode);
	}

	bool TextNode::draw(Drawing &drawing) const
	{
		drawing.graphics.setFont(font);
		const juce::AffineTransform &transform = *drawing.transform;
		if (transform.mat00 == 1 && transform.mat01 == 0 && transform.mat10 == 0 && transform.mat11 == 1)
			drawing.graphics.drawSingleLineText(text, (int)(transform.mat02), (int)(transform.mat12));
		else
            // drawing.graphics.drawTextAsPath(text, transform);
        {
            juce::GlyphArrangement glyphs;
            glyphs.addLineOfText(font, text, 0.0f, 0.0f);

            juce::Path path;
            glyphs.createPath(path);

            drawing.graphics.fillPath(path, transform);
        }
		return true;
	}

	bool TextNode::strokeWalk(StrokeWalk &strokeWalk) const
	{
		juce::GlyphArrangement glyphs;
		glyphs.addLineOfText(font, text, 0.0f, 0.0f);
		juce::Path path;
		glyphs.createPath(path);
		path.applyTransform(*strokeWalk.transform);
		strokeWalk.path.addPath(path);
		return true;
	}

	size_t TextNode::unlinkAndGetSize()
	{
		text.~String();
		DuploDrawable::unlinkAndGetSize();
		return sizeof(TextNode);
	}
}
