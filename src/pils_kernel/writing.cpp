/* This file is public domain */
#include "writing.h"
#include "rule.h"

namespace PILS
{
	Writing::Writing(Runner &run, const Language *language, const Any *thing)
        : run(run), language(language), spacing(tight), labelCount(0), level(0), flatLevel(0), lastName(nullptr)
	{
		while (thing) thing = thing->labeling(*this);
	}
	void Writing::write(long long n)
	{
		long long nn = n / 10;
		if (nn) write(nn);
		write((PILS_CHAR)('0' + n % 10));
	}

	void Writing::write(size_t n)
	{
		size_t nn = n / 10;
		if (nn) write(nn);
		write((PILS_CHAR)('0' + n % 10));
	}

	void Writing::write(size_t n, size_t count)
	{
		if (--count) write(n / 10, count);
		write((PILS_CHAR)('0' + n % 10));
	}

	bool Writing::write(const Any *thing, WriteState state, long level, const Constant *dot)
	{
        if(thing->refcount.isMultipleReferenced())
		{
			std::map<const Any *, int>::iterator find = labels.find(thing);
			if (find != labels.end() && find->second)
			{
				spaceElement();
				if (find->second == -1)
				{
					write((long long)(find->second = ++labelCount));
					spacing = tight;
                    return thing->write(*this, WRITING_ARGUMENT, level, nullptr);
				}
				else
				{
					write((long long)find->second);
					write('.');
					spacing = space;
					return false;
				}
			}
		}
		const bool done = thing->write(*this, state, level, dot);
		return done;
	}

	bool Writing::overflow() const
	{
		return false;
	}

	void Writing::spaceElement()
	{
		if (spacing != tight)
			writeSpaceOrBreak();
	}

	void Writing::spaceString()
	{
		if (spacing != tight)
			writeSpaceOrBreak();
	}

	void Writing::spaceRule()
	{
		if (spacing == rule)
			write (" .");
		if (spacing != tight)
			writeSpaceOrBreak();
	}

	void Writing::spaceColon()
	{
		if (spacing != tight && spacing != colon)
			writeSpaceOrBreak();
	}

	void Writing::spaceDot()
	{
		if (spacing != tight && spacing != dot)
			writeSpaceOrBreak();
	}

	void WritingString::write(const PILS_CHAR c)
	{
		buffer.append(&c, 1);
	}

	void WritingString::write(const PILS_CHAR *cc)
	{
		for(PILS_CHAR c = *cc++; c; c = *cc++)
		buffer.append(&c, 1);
	}

	void WritingString::write(const PILS_CHAR *cc, size_t count)
	{
		buffer.append(cc, count);
	}

	void WritingString::writeSpaceOrBreak()
	{
		buffer.append(" ", 1);
	}

	const PilsString *WritingString::getString() const
	{
		return PilsString::get(buffer.data(), buffer.size());
	}

	bool WritingProbe::overflow() const
	{
		return count > limit;
	}

	void WritingProbe::write(const PILS_CHAR c)
	{
		count++;
	}

	void WritingProbe::write(const PILS_CHAR *cc)
	{
		while(*cc++) count++;
	}

	void WritingProbe::write(const PILS_CHAR *cc, size_t count)
	{
		this->count += count;
	}

	void WritingProbe::writeSpaceOrBreak()
	{
		count++;
	}

	void WritingIndentString::writeSpaceOrBreak()
	{
		size_t at = buffer.size();
		buffer.append(" ", 1);
		tap(at, level, flatLevel);
	}

	void WritingIndentString::done()
	{
		if (buffer.size()) buffer.append("\n", 1);
		WritingString::done();
	}

	int WritingIndentString::indenting(size_t at, size_t level)
	{
		buffer.replace(at++, 1, "\n");
		buffer.insert(at, level * indentSpacing, ' ');
		return level * indentSpacing;
	}

	void WritingIndentString::optionalSpace()
	{
		buffer.append(" ", 1);
	}

	void WritingIndentString::optionalSpaceOrBreak()
	{
		writeSpaceOrBreak();
	}

	void WritingIndentProbe::writeSpaceOrBreak()
	{
		tap(count++, level, flatLevel);
	}

	void WritingIndentProbe::done()
	{
		if (count) count++;
		WritingProbe::done();
	}

	int WritingIndentProbe::indenting(size_t at, size_t level)
	{
		count += level * indentSpacing;
		return level * indentSpacing;
	}

	void WritingIndentProbe::optionalSpaceOrBreak()
	{
		writeSpaceOrBreak();
	}

	void WritingIndentProbe::optionalSpace()
	{
		count++;
	}

	void IndentHand::tap(size_t at, size_t indent, size_t flatLevel)
	{
		size_t level = indent+flatLevel;
		// Do indents until line is not too long
		while(!hand.empty() && hand[0].at + maxMeaningfulChars < at)
		{
			breakLevel = hand[0].level;
			int correction = indenting(hand[0].at, hand[0].indent);
			brokeAt = hand[0].at + correction;
			hand.erase(hand.begin());
			for (std::vector<Finger>::iterator i = hand.begin(); i < hand.end(); i++)
			{
				i->at += correction;
			}
			at += correction;
		}
		// Release smaller fingers
		while(!hand.empty() && (hand.end()-1)->level >= level)
		{
			hand.pop_back();
		}
		// Indent or stack
		if (level<breakLevel)
		{
			breakLevel = level;
			brokeAt = at+indenting(at, indent);
		}
		else
		{
			Finger finger = {at, level, indent};
			hand.push_back(finger);
		}
	}

	bool Integer::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceElement();
		if (value < 0)
		{
			writing.write('-');
			writing.write((size_t)(-value));
		}
		else writing.write((size_t)value);
		writing.spacing = Writing::space;
		return false;
	}

	bool Float::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (dot == &Empty::singleton)
		{
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceElement();
		/* TODO: use read-back check
		 * - writing and reading should not change float.
		 */
		Split split;
		split.put(value);
		if (split.mantissa < 0)
		{
			split.mantissa = -split.mantissa;
			if (split.mantissa < 0)
			{
				writing.write("{#}");
				return false;
			}
			writing.write('-');
		}
		if (split.exponent == 0)
		{
			writing.write(split.mantissa);
		}
		else
		{
			PILS_CHAR digitspace[22];
			PILS_CHAR &enddigits = digitspace[20];
			digitspace[20] = '0';
			digitspace[21] = '0';
			PILS_CHAR *digit = &enddigits;
			for (long long m = split.mantissa; m; m /= 10)
			{
				*--digit = (PILS_CHAR)('0' + m % 10);
			}
			long e = (long)(&enddigits - digit + split.exponent - 1);
			if (e >= -3 && e < 6) e = 0;
			while (e % 3) e--;
			long lump = (long)(&enddigits - digit + split.exponent - e);
			while (lump <= 0)
			{
				lump++;
				*--digit = '0';
			}
			writing.write(digit, lump);
			digit += lump;
			lump = (long)(&enddigits - digit);
			if (lump >= 0)
			{
				const PILS_CHAR *decimalPoint = writing.language->element[0]->as_NodeConstant()->element[0]->as_String()->value + 1;
				writing.write(*decimalPoint ? decimalPoint : _PS("."));
				writing.write(digit, lump);
			}
			if (e)
			{
				writing.write('e');
				if (e < 0)
				{
					e = -e;
					writing.write('-');
				}
				writing.write((size_t)e);
			}
		}
		writing.spacing = Writing::space;
		return false;
	}

	bool PilsString::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceString();
		if (count->value == 0)
		{
			writing.write("\"\"");
			writing.spacing = Writing::space;
			return false;
		}
        writing.lastName = nullptr; // avoid confusing name repeaters
		const PILS_CHAR *const end = value + count->value;
		const PILS_CHAR *validating = writing.language->validateString(value, end);
		for (const PILS_CHAR *at = value; at < end;)
		{
			writing.write('"');
			while (at < validating)
			{
				const PILS_CHAR c = *at++;
				writing.write(c);
				if (c == '"') writing.write(c);
			}
			writing.write('"');
			while (at == validating && at < end)
			{
				const PILS_CHAR c = *at++;
				switch (c)
				{
				case (const PILS_CHAR)0:
					writing.write('~');
					break;
				case (const PILS_CHAR)9:
					writing.write('>');
					break;
				case (const PILS_CHAR)10:
					writing.write('=');
					break;
				case (const PILS_CHAR)13:
					if (at < end && *at == (const PILS_CHAR)10)
					{
						writing.write('/');
						at++;
					}
					else writing.write('<');
					break;
				default:
					for (long shift = sizeof(PILS_CHAR) * 8 - 4; shift >= 0; shift -= 4)
						writing.write("0123456789abcdef"[(c >> shift) & 0xF]);
				}
				while (at < end && *at == '"')
				{
					writing.write('"');
					writing.write('"');
					at++;
				}
				validating = writing.language->validateString(at, end);
			}
		}
		writing.spacing = Writing::space;
		return false;
	}

	bool PilsColor::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceElement();
		writing.write('#');
		for (int i = 20; i >= 0; i -= 4)
		{
			char c = (value >> i) & 0xF;
			c += c < 10?'0':'a' - 10;
			writing.write(c);
		}
		unsigned int alpha = value >> 24;
		if (alpha != 0xff)
		{
			for (int i = 4; i >= 0; i -= 4)
			{
				char c = (alpha >> i) & 0xF;
				c += c < 10?'0':'a'-10;
				writing.write(c);
			}
		}
		writing.spacing = Writing::space;
		return false;
	}

	bool Cliche::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else
			writing.spaceElement();
		writing.write('[');
		if (--level)
		{
			writing.flatLevel++;
			writing.optionalSpace();
			writing.level++;
			writing.spacing = Writing::tight;
            writing.write(head, WRITING_CONSTANT, level, nullptr);
			writing.level--;
			writing.optionalSpaceOrBreak();
			for (size_t i = 0; i < count; i++)
			{
				writing.write('|');
				writing.spacing = Writing::tight;
				if (attributes[i] != &Empty::singleton)
				{
					writing.optionalSpace();
					writing.level++;
                    writing.write(attributes[i], WRITING_CONSTANT, level, nullptr);
					writing.level--;
					writing.optionalSpaceOrBreak();
				}
			}
			writing.flatLevel--;
		}
		else writing.write("...");
		writing.write(']');
		writing.spacing = Writing::space;
		return false;
	}

	bool ClicheShort::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoNames()) return Cliche::write(writing, state, level, dot);
		if (writing.overflow()) return false;
		Language::Index::Record record;
		NameSkin skin = writing.language->nameLookup(this, record);
		if (skin == NAMESKIN_NONE)
		{
			Cliche::write(writing, state, level, dot);
			return false;
		}
		writing.spaceElement();
		if (skin != NAMESKIN_STRING && !writing.language->validateString(*record.local))
			skin = NAMESKIN_STRING;
		bool wrap;
		switch (state)
		{
		case WRITING_NAME:
		case WRITING_CONSTANT:
		case WRITING_CONSTANT_ATTRIBUTE:
		case WRITING_CONSTANT_ELEMENT:
		case WRITING_CONSTANT_SHORT_ELEMENT:
			wrap = false;
			break;
		default:
			if (dot == &Empty::singleton)
			{
				wrap = false;
				if (skin != NAMESKIN_NAME && skin != NAMESKIN_ASTERISKED) skin = NAMESKIN_STRING;
			}
			else wrap = true;
		}

		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			writing.write('[');
		}
		if(this == writing.lastName)
			writing.write('\'');
		else
		{
			record.write(writing, skin == NAMESKIN_STRING);
			if (skin == NAMESKIN_ASTERISKED)
				writing.write('\'');
			if (skin == NAMESKIN_STRING||skin == NAMESKIN_NAME||skin ==NAMESKIN_ASTERISKED)
				writing.lastName = this;
		}
		if (wrap) writing.write(']');
		writing.spacing = Writing::space;
		return false;
	}

	void Language::Index::Record::write(Writing &writing, bool stringwise) const
	{
		if (prefix || stringwise)
		{
			if (prefix)	writing.write(prefix->value, prefix->count->value);
			else writing.write('?');
			writing.write(':');
			writing.spacing = Writing::tight;
		}
		if (stringwise)
            local->write(writing, WRITING_CONSTANT, 0, nullptr);
		else
		{
			writing.write(local->value, local->count->value);
			writing.spacing = Writing::space;
		}
	}

	bool NodeConstant::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		writing.spaceElement();
		if (--level == 0)
		{
			writing.write("...");
			return false;
		}

		bool wrap = state != WRITING_CONSTANT;
		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			writing.write('[');
			writing.optionalSpace();
			writing.level++;
		}
		writing.spacing = Writing::tight;

		writing.flatLevel++;

		const Constant *head = cliche->head;
        writing.write(head, WRITING_NAME, level, nullptr);
		writing.write(':');
		writing.spacing = Writing::space;

		// write head-named attribute if exists

		if (writing.language->withNoSugar())
            head = nullptr;
		else if (const Constant *v = getAttribute(*head))
		{
			writing.write('.');
			if (v != head)
			{
				if (v == &Empty::singleton)
				{
					writing.write('?');
				}
				else
				{
					writing.level++;
					writing.writeSpaceOrBreak();
					writing.spacing = Writing::tight;
					WriteState s = (cliche->count == 1 ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                    writing.write(v, s, level, nullptr);
					writing.level--;
				}
			}
		}
        else head = nullptr;

		for (size_t i = cliche->count - 1; i + 1; i--)
		{
			const Constant *name = cliche->attributes[i];
			if (name == head)
			{
                head = nullptr;
			}
			else
			{
				const Constant *v = element[i];
				if (name == &Empty::singleton)
				{
					if (cliche->count > 1)
					{
						writing.write(';');
						writing.spacing	= Writing::space;
					}

					if (v != &Empty::singleton)
					{
						writing.flatLevel--;
                        writing.write(v, WRITING_CONSTANT, level, nullptr);
						writing.flatLevel++;
					}
				}
				else
				{
					writing.writeSpaceOrBreak();
					writing.flatLevel++;
					writing.write('.');
					writing.spacing	= Writing::tight;
                    writing.write(cliche->attributes[i], WRITING_NAME, level, nullptr);

					if (v != name)
					{
						if (v == &Empty::singleton)
						{
							writing.write('?');
							writing.spacing = Writing::space;
						}
						else
						{
							writing.level++;
							WriteState s = (i == 0||(head && i == 1) ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                            writing.write(v, s, level, nullptr);
							writing.level--;
						}
					}
					writing.flatLevel--;
				}
			}
		}

		writing.flatLevel--;

		if (wrap)
		{
			writing.level--;
			writing.optionalSpaceOrBreak();
			writing.write(']');
			writing.spacing = Writing::space;
		}
		return false;
	}

	bool ListConstant::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}
		size_t c = count->value;

		bool shortlist = c != 1 && !writing.language->withNoSugar();
		if (shortlist && state != WRITING_CONSTANT_ELEMENT)
		{
			for (size_t i = 0; i < c; i++)
			{
				const Integer *ec;
				const Any *const *ee;
                if ((element[i]->isList(ee, ec) && ec->value != 1) || element[i]->as_String() != nullptr)
				{
					shortlist = false;
					break;
				}
			}
		}

		bool wrap = true;
		if (!writing.language->withNoSugar())
		switch (state)
		{
		case WRITING_CONSTANT:
		case WRITING_CONSTANT_ATTRIBUTE:
			wrap = false;
			break;
		case WRITING_CONSTANT_ELEMENT:
			wrap = !shortlist;
			break;
		default:
            break;
		}

		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			else writing.spaceElement();
			writing.write('[');
			writing.level++;
			writing.optionalSpace();
		}
		else
		{
			writing.spaceElement();
			writing.flatLevel++;
		}
		writing.spacing = Writing::tight;

		if (shortlist)
		{
			for (size_t i = 0; i < c; i++)
			{
				const Constant *e = element[i];
                writing.write(e, WRITING_CONSTANT_SHORT_ELEMENT, level, nullptr);
			}
		}
		else
		{
			for (size_t i = 0; i < c; i++)
			{
				const Constant *e = element[i];
				if (e != &Empty::singleton)
				{
                    writing.write(e, WRITING_CONSTANT_ELEMENT, level, nullptr);
				}
				if (e == &Empty::singleton || i < c - 1 || c == 1)
				{
					writing.write(',');
					writing.spacing = Writing::space;
				}
			}
		}

		if (wrap)
		{
			writing.optionalSpaceOrBreak();
			writing.write(']');
			writing.level--;
			writing.spacing = Writing::space;
		}
		else writing.flatLevel--;
		return false;
	}

	bool ListExpress::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}

		bool wrap = (state != WRITING_EXPRESSION && state != WRITING_ATTRIBUTE) || writing.language->withNoSugar();
        if (wrap) dot = nullptr;
		size_t c = count->value;

		if (wrap)
		{
			writing.spaceElement();
			writing.write('(');
			writing.spacing = Writing::tight;
			writing.level++;
			writing.optionalSpace();
		}
		else writing.flatLevel++;
		for (size_t i = 0; i < c; i++)
		{
			const Any *e = element[i];
			if (e != &Empty::singleton)
			{
				writing.write(e, WRITING_ELEMENT, level, dot);
			}
			if (e == &Empty::singleton || i < c - 1 || c == 1)
			{
				writing.write(',');
				writing.spacing = Writing::space;
			}
            dot = nullptr;
		}
		if (wrap)
		{
			writing.optionalSpaceOrBreak();
			writing.level--;
			writing.write(')');
			writing.spacing = Writing::space;
		}
		else writing.flatLevel--;
		return false;
	}

	bool Empty::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (!writing.language->withNoSugar())
		{
			switch (state)
			{
			case WRITING_CONSTANT_ELEMENT:
			case WRITING_CONSTANT_SHORT_ELEMENT:
				writing.write('?');
				writing.spacing = Writing::space;
			case WRITING_CONSTANT:
			case WRITING_CONSTANT_ATTRIBUTE:
				return false;
            default:
                break;
			}
		}
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceElement();
		writing.write("[]");
		writing.spacing = Writing::space;
		return false;
	}

	bool NodeExpress::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}
		bool wrap = state != WRITING_EXPRESSION || writing.language->withNoSugar();
		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			writing.spaceElement();
			writing.write('(');
			writing.spacing = Writing::tight;
			writing.optionalSpace();
			writing.level++;
		}

		const Constant *head = cliche->head;
		if (head == &PokerHead::singleton)
		{
            head = nullptr;
			writing.spaceColon();
			writing.write(':');
		}
		else if (head == &Empty::singleton && cliche->attributes[cliche->count - 1] != head)
		{
            head = nullptr;
			writing.spaceColon();
			writing.write(';');
		}
        if (head == nullptr)
		{
			head = cliche->attributes[cliche->count - 1];
			const Any *v = element[cliche->count - 1];
			if (head == &Empty::singleton)
			{
                head = nullptr;
                if (v == &Empty::singleton) v = nullptr;
			}
			else
			{
				writing.spacing = Writing::tight;
                writing.write(head, WRITING_NAME, level, nullptr);
				const Slot *slot = v->as_Slot();
				if (slot && slot->element[0] == head)
                    v = nullptr;
			}
			if (v)
			{
				writing.level++;
				WriteState s = (cliche->count == 1 ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
				writing.write(v, s, level, head);
				writing.level--;
			}
		}
		else
		{
            writing.write(head, WRITING_NAME, level, nullptr);
			writing.write(':');
			writing.spacing = Writing::space;
			if (head == &Empty::singleton || writing.language->withNoSugar())
                head = nullptr;
			else
			// write head-named attribute if exists
			if (const Any* v = getAttribute(*head))
			{
				writing.write('.');
				const Slot *slot = v->as_Slot();
                if (slot == nullptr||slot->element[0] != head)
				{
					writing.spacing = Writing::dot;
					WriteState s = (cliche->count == 1 ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
					writing.level++;
					writing.write(v, s, level, head);
					writing.level--;
				}
			}
            else head = nullptr;
		}

		for (size_t i = cliche->count - 1; i + 1; i--)
		{
			const Constant *name = cliche->attributes[i];
			if (name == head)
			{
                head = nullptr;
			}
			else
			{
				if (name == &Empty::singleton)
				{
                    name = nullptr;
					if (cliche->count > 1)
					{
						writing.write(';');
						writing.spaceElement();
					}
				}
				else
				{
					writing.spaceDot();
					writing.write('.');
					writing.spacing = Writing::tight;
                    writing.write(name, WRITING_NAME, level, nullptr);
				}

				const Any *v = element[i];
				if (name)
				{
					const Slot *slot = v->as_Slot();
					if (slot && slot->element[0] == name && !writing.language->withNoSugar())
                        v = nullptr;
				}
                else if (v == &Empty::singleton && !writing.language->withNoSugar()) v = nullptr;
				if (v)
				{
					WriteState s = (i == 0||(head && i == 1) ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
					if (name) writing.level++;
					writing.write(v, s, level, name);
					if (name) writing.level--;
				}
			}
		}

		if (wrap)
		{
			writing.level--;
			writing.optionalSpace();
			writing.write(')');
			writing.spacing = Writing::space;
		}
		return false;
	}

	bool Escape::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}

		bool wrap = state != WRITING_EXPRESSION || writing.language->withNoSugar();
		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			else
				writing.spaceElement();
			writing.write('(');
			writing.optionalSpace();
			writing.level++;
		}
		else writing.spaceColon();
		writing.write(':');
		writing.spacing = Writing::colon;
        writing.write(element[0], WRITING_EXPRESSION, level, nullptr);
		if (wrap)
		{
			writing.level--;
			writing.optionalSpace();
			writing.write(')');
			writing.spacing = Writing::space;
		}
		return false;
	}

	bool Slot::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoSugar()) return NodeExpress::write(writing, state, level, dot);
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}

		Language::Index::Record record;
		NameSkin skin;
		// Calling a proper name or a node with a proper name
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
			writing.spacing = Writing::tight;
		}
		const ClicheShort *head = element[0]->as_ClicheShort();
        const NodeConstant *node = nullptr;
		const Cliche *cliche;
        if (head == nullptr)
		{
			node = element[0]->as_NodeConstant();
			if (node)
			{
				cliche = node->cliche;
				head = cliche->head->as_ClicheShort();
			}
		}

		if (head
			&& (skin = writing.language->nameLookup(head, record)) != NAMESKIN_NONE)
		{
			writing.spaceElement();
			bool wrap = state == WRITING_ARGUMENT;
			if (wrap)
			{
				writing.write('(');
				writing.optionalSpace();
				writing.level++;
			}
			if (head == writing.lastName)
			{
				writing.write('\'');
			}
			else
			{
				if (skin == NAMESKIN_STRING||skin == NAMESKIN_NAME||skin == NAMESKIN_ASTERISKED)
					writing.lastName = head;
				record.write(writing, skin != NAMESKIN_NAME && skin != NAMESKIN_ASTERISKED);
				if (skin == NAMESKIN_ASTERISKED) writing.write('\'');
			}
			writing.spacing = Writing::space;
			if (node)
			{
				if (cliche->count == 1 && cliche->attributes[0] == &Empty::singleton)
                    writing.write(node->element[0], WRITING_ARGUMENT, level, nullptr);
				else
				{
					writing.writeSpaceOrBreak();
					writing.write('[');
					writing.optionalSpace();
					writing.level++;
					writing.spacing = Writing::tight;
					if (const Constant* v = node->getAttribute(*head))
					{
						writing.write('.');
						if (v == &Empty::singleton)
						{
							writing.write('?');
						}
						else if (v != head)
						{
							writing.spacing = Writing::space;
							WriteState s = (cliche->count == 1 ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                            writing.write(v, s, level, nullptr);
						}
					}
                    else head = nullptr;
					for (size_t i = cliche->count - 1; i + 1; i--)
					{
						const Constant *name = cliche->attributes[i];
						if (name == head)
						{
                            head = nullptr;
						}
						else
						{
							if (name == &Empty::singleton)
							{
								writing.write(';');
								writing.spacing = Writing::space;
							}
							else
							{
								writing.spaceDot();
								writing.write('.');
								writing.spacing = Writing::tight;
                                writing.write(cliche->attributes[i], WRITING_NAME, level, nullptr);
							}

							const Constant *v = node->element[i];
							if (v != name)
							{
								if (v == &Empty::singleton)
								{
									writing.write('?');
								}
								else
								{
									WriteState s = (i == 0||(head && i == 1) ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                                    writing.write(v, s, level, nullptr);
								}
							}
						}
					}
					writing.level--;
					writing.optionalSpace();
					writing.write(']');
				}
			}
			if (wrap)
			{
				writing.level--;
				writing.optionalSpace();
				writing.write(')');
				writing.spacing = Writing::space;
			}
            return node == nullptr && wrap == false;
		}

        return PokerShort::write(writing, state, level, nullptr);
	}

	bool EmptySlot::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoSugar()) return NodeExpress::write(writing, state, level, dot);

		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}

		bool wrap = state == WRITING_ARGUMENT;
		if (wrap) writing.write('(');
		writing.write('?');
		if (wrap) writing.write(')');
		writing.spacing = Writing::space;
		return false;
	}

	bool Call::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoSugar()) return NodeExpress::write(writing, state, level, dot);
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}

		Language::Index::Record record;
		NameSkin skin;
		// Calling a proper name or a node with a proper name
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
			writing.spacing = Writing::tight;
		}
		const NodeExpress *node = element[0]->as_NodeExpress();
        const ClicheShort *head = nullptr;
		const Cliche *cliche;
		if (node)
		{
			cliche = node->cliche;
			head = cliche->head->as_ClicheShort();
		}
		if (head
			&& (skin = writing.language->nameLookup(head, record)) != NAMESKIN_NONE)
		{
			bool wrap = state == WRITING_ARGUMENT;
			writing.spaceElement();
			if (wrap)
			{
				writing.write('(');
				writing.optionalSpace();
				writing.level++;
				writing.spacing = Writing::tight;
			}

			if (head == writing.lastName)
			{
				writing.write('\'');
			}
			else
			{
				if (skin == NAMESKIN_STRING ||skin == NAMESKIN_NAME || skin == NAMESKIN_ASTERISKED)
					writing.lastName = head;
				record.write(writing, skin != NAMESKIN_NAME && skin != NAMESKIN_ASTERISKED);
				if (skin == NAMESKIN_ASTERISKED) writing.write('\'');
			}
			writing.spaceElement();
			if (cliche->count == 1 && cliche->attributes[0] == &Empty::singleton)
                writing.write(node->element[0], WRITING_ARGUMENT, level, nullptr);
			else
			{
				const Slot* slot;
				writing.write('(');
				writing.optionalSpace();
				writing.level++;
				writing.spacing = Writing::tight;
				if (const Any* v = node->getAttribute(*head))
				{
					writing.write('.');
					writing.spacing = Writing::dot;
					
					if (!((slot = v->as_Slot()) && slot->element[0] == head))
					{
						WriteState s = (cliche->count == 1 ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
                        writing.write(v, s, level, nullptr);
					}
				}
                else head = nullptr;
				for (size_t i = cliche->count - 1; i + 1; i--)
				{
					const Constant *name = cliche->attributes[i];
					if (name == head)
					{
                        head = nullptr;
					}
					else
					{
						if (name == &Empty::singleton)
						{
							writing.write(';');
							writing.spacing = Writing::space;
						}
						else
						{
							writing.spaceDot();
							writing.write('.');
							writing.spacing = Writing::tight;
                            writing.write(cliche->attributes[i], WRITING_NAME, level, nullptr);
						}

						const Any *v = node->element[i];
						if (name == &Empty::singleton)
						{
                            name = nullptr;
							if (v == &Empty::singleton)
                                v = nullptr;
						}
						else
						{
							const Slot *slot = v->as_Slot();
							if (slot && slot->element[0] == name)
                                v = nullptr;
						}
						if(v)
						{
							WriteState s = (i == 0||(head && i == 1) ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
							writing.write(v, s, level, name);
						}
					}
				}
				writing.level--;
				writing.optionalSpace();
				writing.write(')');
				writing.spacing = Writing::space;
			}
			if (wrap)
			{
				writing.level--;
				writing.optionalSpace();
				writing.write(')');
				writing.spacing = Writing::space;
			}
			return false;
		}
        else return PokerShort::write(writing, state, level, nullptr);
	}

	bool CallWho::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoSugar()) return NodeExpress::write(writing, state, level, dot);
		if (writing.overflow()) return false;
		if (--level == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}

		// Examine call

        const Any *const *callElement = nullptr;
        const Cliche *callCliche = nullptr;
        const ClicheShort *name = nullptr;
		Language::Index::Record record;
		NameSkin skin = NAMESKIN_NONE;

		if (element[0] == &Empty::singleton) skin = NAMESKIN_JOKER;
		else
		{
			if (element[0]->isNode(callElement, callCliche))
				name = callCliche->head->as_ClicheShort();
			else
				name = element[0]->as_ClicheShort();
		}
		if (name)
			skin = writing.language->nameLookup(name, record);

		// Decide the need for wrapping

		bool wrap;
		bool prefix = false;
		if (skin == NAMESKIN_OPERATOR || skin == NAMESKIN_ADDITION || skin == NAMESKIN_RELATION)
		{
			if (callElement)
			{
				if (callCliche->count != 1 || callCliche->attributes[0] != &Empty::singleton)
				{
					skin = NAMESKIN_NONE;
				}
			}
			else prefix = true;
		}

		switch (state)
		{
		case WRITING_EXPRESSION:
		case WRITING_ATTRIBUTE:
		case WRITING_ELEMENT:
			wrap = false;
			break;
		case WRITING_COMPARAND:
			wrap = (callElement && skin == NAMESKIN_RELATION);
			break;
		case WRITING_ADDEND:
			wrap = (callElement && (skin == NAMESKIN_RELATION || skin == NAMESKIN_ADDITION));
			break;
		case WRITING_SEQUEL:
			wrap = (callElement && (skin == NAMESKIN_RELATION || skin == NAMESKIN_ADDITION));
			break;
		case WRITING_OPERAND:
			wrap = (prefix == false);
			break;
		case WRITING_ARGUMENT:
		case WRITING_DOT_ARGUMENT:
		default:
			wrap = true;
		}

		if (wrap)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			writing.spaceElement();
			writing.write('(');
			writing.optionalSpace();
			writing.level++;
			writing.spacing = Writing::tight;
		}

		bool mustDot;

		// reverse order if call node is operator

		if (prefix)
		{
			writing.spaceElement();
			writing.level++;
			record.write(writing, false);
			writing.spacing = Writing::space;
            mustDot = writing.write(element[1], WRITING_OPERAND, level, nullptr);
			writing.level--;
		}
		else
		{
			// write who attribute

			WriteState s = WRITING_SEQUEL;
			if (callElement) switch (skin)
			{
			case NAMESKIN_RELATION:
				s = WRITING_ELEMENT;
				break;
			case NAMESKIN_ADDITION:
				s = WRITING_COMPARAND;
				break;
            default:
                break;
			}

			mustDot = writing.write(element[1], s, level, dot);

			// dot if needed, prefix and name if present

			switch (skin)
			{
			case NAMESKIN_JOKER:
				writing.flatLevel++;
				mustDot = false;
				break;
			case NAMESKIN_OPERATOR:
			case NAMESKIN_ADDITION:
			case NAMESKIN_RELATION:
				writing.spaceElement();
				writing.flatLevel++;
				record.write(writing, false);
				writing.spacing = Writing::space;
				break;
			case NAMESKIN_STRING:
			case NAMESKIN_NAME:
			case NAMESKIN_ASTERISKED:
				writing.spaceElement();
				writing.flatLevel++;
				if (name == writing.lastName)
				{
					writing.write('\'');
				}
				else
				{
					record.write(writing, skin == NAMESKIN_STRING);
					if (skin == NAMESKIN_ASTERISKED) writing.write('\'');
					writing.lastName = name;
				}
				writing.spacing = Writing::space;

				break;
			default:
				skin = NAMESKIN_NONE;
			case NAMESKIN_NONE:
				writing.flatLevel++;
				break;
			}

			// write whatever form is appropriate

			switch (skin)
			{
			case NAMESKIN_JOKER:
				writing.write('?');
				writing.spacing = Writing::space;
				mustDot = false;
				break;
			case NAMESKIN_OPERATOR:
                mustDot = writing.write(callElement[0], WRITING_OPERAND, level, nullptr);
				break;
			case NAMESKIN_ADDITION:
                mustDot = writing.write(callElement[0], WRITING_ADDEND, level, nullptr);
				break;
			case NAMESKIN_RELATION:
                mustDot = writing.write(callElement[0], WRITING_COMPARAND, level, nullptr);
				break;
			case NAMESKIN_NAME:
			case NAMESKIN_ASTERISKED:
			case NAMESKIN_STRING:
				if (callElement)
				{
					const Constant *head = callCliche->head;
					if (callCliche->count == 1 && callCliche->attributes[0] == &Empty::singleton)
                        mustDot = writing.write(callElement[0], WRITING_ARGUMENT, level, nullptr);
					else if (const NodeConstant *callNodeConstant = element[0]->as_NodeConstant())
					{
						writing.spaceElement();
						writing.write('[');
						writing.optionalSpace();
						writing.level++;
						writing.spacing = Writing::tight;
						if (const Constant *v = callNodeConstant->getAttribute(*head))
						{
							writing.write('.');
							if (v == &Empty::singleton)
							{
								writing.write('?');
								writing.spacing = Writing::space;
							}
							else if  (v != head)
							{
								writing.spacing = Writing::space;
								WriteState s = (callCliche->count == 1 ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                                writing.write(v, s, level, nullptr);
							}
						}
                        else head = nullptr;
						for (size_t i = callCliche->count - 1; i + 1; i--)
						{
							const Constant *name = callCliche->attributes[i];
							if (name == head)
                                head = nullptr;
							else
							{
								if (name == &Empty::singleton)
								{
									writing.write(';');
									writing.spacing = Writing::space;
								}
								else
								{
									writing.spaceDot();
									writing.write('.');
									writing.spacing = Writing::tight;
                                    writing.write(callCliche->attributes[i], WRITING_NAME, level, nullptr);
								}
								const Constant *v = (const Constant *)callElement[i];
								if (v != name)
								{
									if(v == &Empty::singleton)
									{
										writing.write('?');
										writing.spacing = Writing::space;
									}
									else
									{
										WriteState s = (i == 0||(head && i == 1) ? WRITING_CONSTANT : WRITING_CONSTANT_ATTRIBUTE);
                                        writing.write(v, s, level, nullptr);
									}
								}
							}
						}
						writing.level--;
						writing.optionalSpace();
						writing.write(']');
						writing.spacing = Writing::space;
						mustDot = false;
					}
					else
					{
						const NodeExpress *callNodeExpress = element[0]->as_NodeExpress();
						const Slot* slot;
						writing.spaceElement();
						writing.write('(');
						writing.optionalSpace();
						writing.level++;
						writing.spacing = Writing::tight;
						if (const Any *v = callNodeExpress->getAttribute(*head))
						{
							writing.write('.');
							writing.spacing = Writing::dot;
							if (!((slot = v->as_Slot()) && slot->element[0] == head))
							{
								WriteState s = (callCliche->count == 1 ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
                                writing.write(v, s, level, nullptr);
							}
						}
                        else head = nullptr;
						for (size_t i = callCliche->count - 1; i + 1; i--)
						{
							const Constant *name = callCliche->attributes[i];
							if (name == head)
                                head = nullptr;
							else
							{
								if (name == &Empty::singleton)
								{
									writing.write(';');
									writing.spacing = Writing::space;
								}
								else
								{
									writing.spaceDot();
									writing.write('.');
									writing.spacing = Writing::tight;
                                    writing.write(callCliche->attributes[i], WRITING_NAME, level, nullptr);
								}

								const Any *v = callElement[i];
								if (name == &Empty::singleton)
								{
                                    name = nullptr;
									if (v == &Empty::singleton)
                                        v = nullptr;
								}
								else
								{
									const Slot *slot = v->as_Slot();
									if (slot && slot->element[0] == name)
                                        v = nullptr;
								}
								if(v)
								{
									WriteState s = (i == 0||(head && i == 1) ? WRITING_EXPRESSION : WRITING_ATTRIBUTE);
									writing.write(v, s, level, name);
								}
							}
						}
						writing.level--;
						writing.optionalSpace();
						writing.write(')');
						writing.spacing = Writing::space;
						mustDot = false;
					}
				}
				else
				{
					mustDot = true;
				}
				break;
			default:
				if (state == WRITING_EXPRESSION && callCliche && callCliche->attributes[0] != &Builtin::name.call)
				{
                    mustDot = writing.write(element[0], WRITING_EXPRESSION, level, (mustDot ? &Empty::singleton : nullptr));
				}
				else
				{
					if (mustDot)
					{
						writing.spaceDot();
						writing.write('.');
						writing.spacing = Writing::dot;
                        mustDot = writing.write(element[0], WRITING_DOT_ARGUMENT, level, nullptr);
					}
                    else mustDot = writing.write(element[0], WRITING_ARGUMENT, level, nullptr);
				}
			}
			writing.flatLevel--;
		}
		if (wrap)
		{
			writing.level--;
			writing.optionalSpace();
			writing.write(')');
			writing.spacing = Writing::space;
			mustDot = false;
		}
		return mustDot;
	}

	double Float::Split::get() const
	{
		double scale = 1;
		double value = (double)mantissa;
		if (exponent > 0)
		{
			for (long e = 0; e < exponent; e++) scale *= 10;
			value = mantissa * scale;
		}
		else if (exponent < 0)
		{
			for (long e = 0; e > exponent; e--) scale *= 10;
			value = mantissa / scale;
		}
		return value;
	}

	void Float::Split::put(double value)
	{
		mantissa = (long long)value;
		exponent = 0;
		if ((double)mantissa == value) return; /*integral values*/

		/* When splitting a double, be as exact as possible */
		double absValue = value < 0 ? -value : value;
		double scale = 1;
		if (absValue >= 1e18)
		{
			exponent++;
			scale *= 10;
			while (absValue / scale >= 1e18 && exponent < 1000)
			{
				exponent++;
				scale *= 10;
			}
			mantissa = (long long)(absValue / scale);
			/* try to adjust mantissa */
//			if (absValue > (double)mantissa * scale) mantissa++;
//			if (absValue < (double)mantissa * scale) mantissa--;
		}
		else if (absValue < 1e17)
		{
			while (absValue * scale < 1e17 && absValue != (double)mantissa / scale && exponent > -1000)
			{
				scale *= 10;
				exponent--;
				mantissa = (long long)(absValue * scale);
				/* try to adjust mantissa */
//				if (absValue > (double)mantissa / scale) mantissa++;
//				if (absValue < (double)mantissa / scale) mantissa--;
			}
		}
		if (value < 0) mantissa = -mantissa;
	}

	bool Special::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
		}
		else writing.spaceElement();
		writing.write('{');
		writing.spacing = Writing::tight;
		write(writing);
		writing.write('}');
		writing.spacing = Writing::space;
		return false;
	}

	bool Language::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.overflow()) return false;
		if (this == writing.language)
		{
			if (dot == &Empty::singleton)
			{
				writing.spaceDot();
				writing.write('.');
				writing.writeSpaceOrBreak();
			}
			else writing.spaceElement();
			writing.write("{}");
			writing.spacing = Writing::space;
			return false;
		}
		else return NodeConstantShort::write(writing, state, level, dot);
	}

	bool Ruleset::write(Writing &writing, WriteState state, long level, const Constant *dot) const
	{
		if (writing.language->withNoSugar()) return NodeExpress::write(writing, state, level, dot);
		if (level-- == 0)
		{
			writing.spaceElement();
			writing.write("...");
			writing.spacing = Writing::space;
			return false;
		}
		if (dot == &Empty::singleton)
		{
			writing.spaceDot();
			writing.write('.');
			writing.writeSpaceOrBreak();
			writing.spacing = Writing::tight;
		}
		writing.spaceRule();
		writing.spacing = Writing::tight;
		const ListExpress &rulelist = *(ListExpress *)element[0];
		for (size_t i = 0; i < (size_t)rulelist.count->value; i++)
		{
			const Rule *rule = (Rule *)rulelist.element[i];
			writing.spaceElement();
			writing.write('{');
			writing.flatLevel++;
			writing.spacing = Writing::tight;
			writing.level++;
			const Any *match = rule->match();
			if (match != &Empty::singleton)
			{
				writing.optionalSpace();
                writing.write(match, WRITING_EXPRESSION, level, nullptr);
			}
			writing.level--;
			writing.optionalSpaceOrBreak();
			writing.write('|');
			writing.optionalSpace();
			writing.level++;
			writing.spacing = Writing::tight;
			const Any *action = rule->action();
			if (action != &Empty::singleton)
                writing.write(action, WRITING_EXPRESSION, level, nullptr);
			writing.level--;
			writing.optionalSpaceOrBreak();
			writing.flatLevel--;
			writing.write('}');
			writing.spacing = Writing::space;
		}
		writing.spacing = Writing::rule;
		return false;
	}

	bool Writing::labeling(const Any *thing)
	{
        if (thing->refcount.isMultipleReferenced())
		{
			std::pair<std::map<const Any *, int>::iterator, bool> insert = labels.insert(std::pair<const Any *, int>(thing, 0));
			if (!insert.second)
			{
				insert.first->second = -1;
				return false;
			}
		}
		return true;
	}

	const Any *Any::labeling(Writing &writing) const
	{
        return nullptr;
	}

	const Any *PilsString::labeling(Writing &writing) const
	{
		if (count->value > 12)
			writing.labeling(this);
        return nullptr;
	}

	const Any *ListConstant::labeling(Writing &writing) const
	{
		if (writing.labeling(this))
		{
			for (size_t i = count->value - 1; i; i--)
			{
				for (const Any *e = element[i]; e; e = e->labeling(writing));
			}
			return element[0];
		}
        else return nullptr;
	}

	const Any *Empty::labeling(Writing &writing) const
	{
        return nullptr;
	}

	const Any *ListExpress::labeling(Writing &writing) const
	{
		if (writing.labeling(this))
		{
			for (size_t i = count->value - 1; i; i--)
			{
				for (const Any *e = element[i]; e; e = e->labeling(writing));
			}
			return element[0];
		}
        else return nullptr;
	}

	const Any *NodeConstant::labeling(Writing &writing) const
	{
		if (writing.labeling(this))
		{
			const Any *e = cliche->head;
			for (long i = cliche->count - 1; i >= 0; i--)
			{
				while(e) e=e->labeling(writing);
				e = cliche->attributes[i];
				if(e != element[i])
				{
					while(e) e=e->labeling(writing);
					e = element[i];
				}
			}
			return e;
		}
        else return nullptr;
	}

	const Any *NodeExpress::labeling(Writing &writing) const
	{
		if (writing.labeling(this))
		{
			const Any *e = cliche->head;
			for (long i = cliche->count - 1; i >= 0; i--)
			{
				while(e) e=e->labeling(writing);
				e = cliche->attributes[i];
				const NodeExpress *n = element[i]->as_NodeExpress();
                if(n == nullptr || n->cliche != &BuiltinClicheCall::singleton || n->element[0] != e)
				{
					while(e) e=e->labeling(writing);
					e = element[i];
				}
			}
			return e;
		}
        else return nullptr;
	}

	const Any *Cliche::labeling(Writing &writing) const
	{
		if (writing.labeling(this))
		{
			const Any *e = head;
			for (long i = count - 1; i >= 0; i--)
			{
				while(e) e=e->labeling(writing);
				e = attributes[i];
			}
			return e;
		}
        else return nullptr;
	}

	const Any *ClicheShort::labeling(Writing &writing) const
	{
        return nullptr;
	}
}
