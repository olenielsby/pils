/* This file is public domain */
#include "pilsread.h"
#include "escape.h"

namespace PILS
{
	Sink *ParsingNormal::kick(Runner &run)
	{
		if (inversion) inversion->releaseReference();
		this->ParsingNormal::~ParsingNormal();
		return (Sink*)(this + 1);
	}

	Sink *Parse::kick(Runner &run)
	{
		return (Sink*)(this + 1);
	}

	const Step *Parse::step_(Runner &run) const
	{
		throw "bad step";
	}

	const Step *ParsingNormal::done(Runner &run, const Any *value)
	{
		run.sink = kick(run);
		return value->passCounted(run);
	}

	void ParsingNormal::tracing(const Any *, const unsigned char *)
	{}

	const Step *ParsingTrace::done(Runner &run, const Any *value)
	{
		const Any *tracechain = this->tracechain;
		this->tracechain = value;
		run.sink = kick(run);
		return tracechain->passCounted(run);
	}

	Sink *ParsingTrace::kick(Runner &run)
	{
		if (inversion) inversion->releaseReference();
		tracechain->releaseReference();
		this->ParsingTrace::~ParsingTrace();
		return (Sink *)(this + 1);
	}

	void ParsingTrace::tracing(const Any *item, const unsigned char *from)
	{
		const unsigned char *start = (const unsigned char *)source.value;
		item->addReference();
		const Any *legs[4];
		legs[0] = tracechain;
		legs[1] = Integer::get((int)(from - start));
		legs[2] = Integer::get((int)((at==afterSpace?beforeSpace:at) - start));
		legs[3] = item;
		tracechain = BuiltinClicheTraceread::singleton.node(legs);
	}

	const Step *Parsing::step_(Runner &run) const
	{
		Parsing &parsing = const_cast<Parsing &>(*this);
		if (run.stackOverflow())
			return parsing.error(run, Parsing::ERROR_STACK_OVERFLOW);
		if (at < end)
		{
			switch (*at)
			{
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
			case 0x08:
			case 0x09:
			case 0x0A:
			case 0x0B:
			case 0x0C:
			case 0x0D:
			case 0x0E:
			case 0x0F:
			case 0x10:
			case 0x11:
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x1B:
			case 0x1C:
			case 0x1D:
			case 0x1E:
			case 0x1F:
			case ' ':
			case '!':
				parsing.space();
				return ((Parse *)run.sink)->space(run, parsing);
			case '"':
				((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
				if (redirection) return redirection;
				if (const PilsString *string = parsing.string())
				{
					return parsing.constant(run, string);
				}
				else
					return parsing.error(run, ERROR_BAD_STRING);
			case '(':
				((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->beginParenthesis(run, parsing);
			case ')':
				if (inversion)
				{
					const Any *value = inversion;
					parsing.inversion = NULL;
					((Parse *)run.sink)->close(run, parsing, PARSE_CLOSE, value);
				}
				else
				{
					((Parse *)run.sink)->close(run, parsing, PARSE_CLOSE);
				}
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->endParenthesis(run, parsing);
			case ',':
				((Parse *)run.sink)->close(run, parsing, PARSE_ELEMENT);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->comma(run, parsing);
			case '.':
				if (at + 1 < end)
				{
					switch (at[1])
					{
					case '?':
						if (at + 2 == end || at[2] != ':')
							break;
					default:
						((Parse *)run.sink)->close(run, parsing, PARSE_ATTRIBUTE);
						if (redirection) return redirection;
						parsing.at++;
						return ((Parse *)run.sink)->dotAttribute(run, parsing);
					case ':':	
						((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
						if (redirection) return redirection;
						parsing.at++;
						return ((Parse *)run.sink)->dotColonInversion(run, parsing);
					case '(':
						((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
						if (redirection) return redirection;
						parsing.at++;
						return ((Parse *)run.sink)->dotInversion(run, parsing);
					case 0x00:
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
					case 0x08:
					case 0x09:
					case 0x0A:
					case 0x0B:
					case 0x0C:
					case 0x0D:
					case 0x0E:
					case 0x0F:
					case 0x10:
					case 0x11:
					case 0x12:
					case 0x13:
					case 0x14:
					case 0x15:
					case 0x16:
					case 0x17:
					case 0x18:
					case 0x19:
					case 0x1A:
					case 0x1B:
					case 0x1C:
					case 0x1D:
					case 0x1E:
					case 0x1F:
					case ' ':
					case '!':
					case ';':
					case ']':
					case '{':
					case '|':
					case '}':
					case '.':
					case ',':
					case ')':
						break;
					}
				}
				((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->dot(run, parsing);
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
				((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
				if (redirection) return redirection;
				return parsing.number(run);
			case ':':
				((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
				if (redirection) return redirection;
				parsing.at++;
				if (at < end)
				{
					switch (*at)
					{
					case '?':
						if (at + 2 == end || at[2] != ':')
							break;
					default:
						return ((Parse *)run.sink)->colonNode(run, parsing);
					case ':':
						return ((Parse *)run.sink)->colonColon(run, parsing);
					case '(':
					case ')':
					case 0x00:
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
					case 0x08:
					case 0x09:
					case 0x0A:
					case 0x0B:
					case 0x0C:
					case 0x0D:
					case 0x0E:
					case 0x0F:
					case 0x10:
					case 0x11:
					case 0x12:
					case 0x13:
					case 0x14:
					case 0x15:
					case 0x16:
					case 0x17:
					case 0x18:
					case 0x19:
					case 0x1A:
					case 0x1B:
					case 0x1C:
					case 0x1D:
					case 0x1E:
					case 0x1F:
					case ' ':
					case '!':
					case ';':
					case ']':
					case '{':
					case '|':
					case '}':
						break;
					}
				}
				return ((Parse *)run.sink)->colon(run, parsing);
			case ';':
				if (at + 1 < end)
				{
					switch (at[1])
					{
					case '?':
						if (at + 2 == end || at[2] != ':')
							break;
					default:
						((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
						if (redirection) return redirection;
						parsing.at++;
						return ((Parse *)run.sink)->semicolonNode(run, parsing);
					case ':':
						((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
						if (redirection) return redirection;
						parsing.at++;
						parsing.at++;
						Empty::singleton.addReference();
						return ((Parse *)run.sink)->nodehead(run, parsing, &Empty::singleton);
					case '(':
					case ')':
					case 0x00:
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
					case 0x08:
					case 0x09:
					case 0x0A:
					case 0x0B:
					case 0x0C:
					case 0x0D:
					case 0x0E:
					case 0x0F:
					case 0x10:
					case 0x11:
					case 0x12:
					case 0x13:
					case 0x14:
					case 0x15:
					case 0x16:
					case 0x17:
					case 0x18:
					case 0x19:
					case 0x1A:
					case 0x1B:
					case 0x1C:
					case 0x1D:
					case 0x1E:
					case 0x1F:
					case ' ':
					case '!':
					case ';':
					case ']':
					case '{':
					case '|':
					case '}':
						break;
					}
				}
				((Parse *)run.sink)->close(run, parsing, PARSE_ATTRIBUTE);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->semicolon(run, parsing);
			case '[':
				((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->beginSquare(run, parsing);
			case ']':
				((Parse *)run.sink)->close(run, parsing, PARSE_CLOSE);
				if (redirection) return redirection;
				parsing.at++;
				if (at < end && *at == ':')
				{
					parsing.at++;
					return ((Parse *)run.sink)->endSquareNodehead(run, parsing);
				}
				else return ((Parse *)run.sink)->endSquare(run, parsing);
			case '{':
				parsing.at++;
				if (at < end && *at == '}')
				{
					parsing.at++;
					((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
					if (redirection) return redirection;					
					language.addReference();
					parsing.tracing(&language, at-2);
					return ((Parse *)run.sink)->constant(run, parsing, &language);
				}
				else
				{
					return ((Parse *)run.sink)->beginCurl(run, parsing);
				}
			case '|':
				((Parse *)run.sink)->close(run, parsing, PARSE_BAR);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->bar(run, parsing);
			case '}':
				((Parse *)run.sink)->close(run, parsing, PARSE_CLOSE);
				if (redirection) return redirection;
				parsing.at++;
				return ((Parse *)run.sink)->endCurl(run, parsing);
			case '-':
				if (at + 1 < end && at[1] >= '0' && at[1] <= '9')
				{
					((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
					if (redirection) return redirection;
					return parsing.number(run);
				}
				else
				{
					((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
					if (redirection) return redirection;
					return parsing.name(run);
				}
			case '#':
				{
					const unsigned char *cc;
					unsigned int colorValue = 0;
                                        for (cc = at + 1; cc < end && ((*cc >= '0' && *cc <= '9')||(*cc >= 'a' && *cc <= 'f')); cc++)
					{
						colorValue <<= 4;
						colorValue += *cc - (*cc <= '9'?'0':'a'-10);
					}
					unsigned int alpha = 0xff;
					switch (cc - at)
					{
					case 7:
						break;
					case 9:
						alpha &= colorValue;
						colorValue >>= 8;
						break;
					default:
						((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
						if (redirection) return redirection;
						return parsing.name(run);
					}
					colorValue += alpha << 24;
					((Parse *)run.sink)->close(run, parsing, PARSE_RULESET);
					if (redirection) return redirection;
					const PilsColor *color = PilsColor::get(colorValue);
					parsing.at = cc;
					return parsing.constant(run, color);
				}
			case '?':
				((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
				if (redirection) return redirection;
				parsing.at++;
				if (at < end && *at == ':')
				{
					parsing.at++;
					return parsing.questionName(run);
				}
				else return ((Parse *)run.sink)->question(run, parsing);
			default:
				((Parse *)run.sink)->close(run, parsing, PARSE_PHRASE);
				if (redirection) return redirection;
				return parsing.name(run);
			}
		}
		else
		{
			((Parse *)run.sink)->close(run, parsing, PARSE_CLOSE);
			if (redirection) return redirection;
			return ((Parse *)run.sink)->end(run, parsing);
		}
	}

	void Parsing::space()
	{
		beforeSpace = at;
		while (at < end && *at <= '!')
		{
			if(*at++ == '!')
			{
				if (at < end && *at == '!')
				{
					at++;
                                        while (at < end && (*at++ != '!' || (at < end && *at++ != '!')))
					{;}
				}
				else
				{
					while (at < end && *at++ != '\n')
					{;}
				}
			}
		}
		afterSpace = at;
	}

	const PilsString *Parsing::string()
	{
		class Pass
		{
			virtual void write(unsigned char c) = 0;
			virtual void write(unsigned char const *cc, long count) = 0;
		public:
			bool pass(unsigned char const *&at, unsigned char const *end)
			{
				while(at < end && *at == '"')
				{
					unsigned char const *p = ++at;
					while (at < end && *at != '"') at++;
					if (at == end) return false;
					write(p, at++ - p);
					if (at < end && *at == '"')
					{
						write('"');
						continue;
					}
					while (at < end)
					{
						switch(unsigned char c = *at)
						{
						case '"':
							if (at + 1 == end || at[1] != '"') break;
							at += 2;
							write('"');
							continue;
						case 'a':
						case 'b':
						case 'c':
						case 'd':
						case 'e':
						case 'f':
							c -= 'a' - '9' - 1;
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
                                                        if (at + 1 == end || at[1] < '0' || (at[1] > '9' && at[1] < 'a') || at[1] > 'f')
								return NULL;
							c &= 0x0f;
							c <<= 4;
							c += at[1] <= '9'?at[1] - '0':at[1] - ('a' - 10);
							at += 2;
							write(c);
							continue;
						case '<':
							write('\r');
							at++;
							continue;
						case '>':
							write('\t');
							at++;
							continue;
						case '=':
							write('\n');
							at++;
							continue;
						case '/':
							write('\r');
							write('\n');
							at++;
							continue;
						case '~':
						case '*':
							write('\0');
							at++;
							continue;
						case '-':
							at++;
							while (at < end && *at != '"')
							{
								switch (*at++)
								{
								default:
									return false;
								case 0x00:
								case 0x01:
								case 0x02:
								case 0x03:
								case 0x04:
								case 0x05:
								case 0x06:
								case 0x07:
								case 0x08:
								case 0x09:
								case 0x0A:
								case 0x0B:
								case 0x0C:
								case 0x0D:
								case 0x0E:
								case 0x0F:
								case 0x10:
								case 0x11:
								case 0x12:
								case 0x13:
								case 0x14:
								case 0x15:
								case 0x16:
								case 0x17:
								case 0x18:
								case 0x19:
								case 0x1A:
								case 0x1B:
								case 0x1C:
								case 0x1D:
								case 0x1E:
								case 0x1F:
								case ' ':
									continue;
								case '!':
									if (at == end) return false;
									if (*at == '!')
									{
										at++;
                                                                                while (at < end && (*at++ != '!' || (at < end && *at++ != '!')))
										{;}
									}
									else
									{
										while (at < end && *at++ != '\n')
										{;}
									}
								}
							}
							if (at == end) return false;
							break;
						}
						break;
					}
				}
				return true;
			}
		};

		unsigned char const *from = at;

		class Counting : public Pass
		{
			void write(unsigned char c) {count++;}
			void write(unsigned char const *, long count) {this->count += count;}
		public:
			Counting() : count(0) {}
			long count;
		} counting;

		if (!counting.pass(at, end)) return NULL;

		class Building : public Pass
		{
			void write(unsigned char c) {*at++ = c;}
			void write(unsigned char const *cc, long count)
			{
				for (long i = 0; i < count; i++)
					*at++ = cc[i];
			}
			unsigned char *at;
			unsigned char *buffer;
			long count;
		public:
			Building(long count)
                                : buffer(new unsigned char[count]), count(count)
			{
				at = buffer;
			}
			~Building()
			{
				delete [] buffer;
			}
			const PilsString *string()
			{
				return PilsString::get((PILS_CHAR *)buffer, count);
			}
		} building(counting.count);
		building.pass(at = from, end);
		return building.string();
	}

	Parsing::Nametype Parsing::nametype()
	{
		const unsigned char *const from = at;
		while (++at < end)
		{
			switch(*at)
			{
			default:
				continue;
			case 0x00:
			case 0x01:
			case 0x02:
			case 0x03:
			case 0x04:
			case 0x05:
			case 0x06:
			case 0x07:
			case 0x08:
			case 0x09:
			case 0x0A:
			case 0x0B:
			case 0x0C:
			case 0x0D:
			case 0x0E:
			case 0x0F:
			case 0x10:
			case 0x11:
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x19:
			case 0x1A:
			case 0x1B:
			case 0x1C:
			case 0x1D:
			case 0x1E:
			case 0x1F:
			case ' ':
			case '!':
			case '"':
			case '(':
			case ')':
			case ',':
			case ';':
			case '?':
			case '[':
			case ']':
			case '{':
			case '|':
			case '}':
				break;
			case ':':
				if (at + 1 < end)
				{
					switch (at[1])
					{
					default:
						return NAMETYPE_PREFIX;
					case '-':
						{
							if (at + 2 < end && at[2] >= '0' && at[2] <= '9')
								break;
							else return NAMETYPE_PREFIX;
						}
					case 0x00:
					case 0x01:
					case 0x02:
					case 0x03:
					case 0x04:
					case 0x05:
					case 0x06:
					case 0x07:
					case 0x08:
					case 0x09:
					case 0x0A:
					case 0x0B:
					case 0x0C:
					case 0x0D:
					case 0x0E:
					case 0x0F:
					case 0x10:
					case 0x11:
					case 0x12:
					case 0x13:
					case 0x14:
					case 0x15:
					case 0x16:
					case 0x17:
					case 0x18:
					case 0x19:
					case 0x1A:
					case 0x1B:
					case 0x1C:
					case 0x1D:
					case 0x1E:
					case 0x1F:
					case ' ':
					case '!':
					case '(':
					case ')':
					case ',':
					case '[':
					case ']':
					case '{':
					case '|':
					case '}':
					case '.':
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
						break;
					}
				}
				return NAMETYPE_NODEHEAD;
			}
			break;
		}

		switch(at[-1])
		{
		case '\'':
			for (const unsigned char *c = at - 2; c >= from; c--)
			{
				switch (*c)
				{
				case '\'':
					break;
				case '+':
				case '-':
				case '#':
				case '$':
				case '*':
				case '%':
				case '&':
				case '/':
				case '\\':
				case '^':
				case '<':
				case '=':
				case '>':
				case '~':
					return NAMETYPE_ASTERISKED;
				default:
					return NAMETYPE_NAME;
				}
			}
			return NAMETYPE_ASTERISKED;
		case '#':
		case '$':
		case '*':
		case '%':
		case '&':
		case '/':
		case '\\':
		case '^':
			return NAMETYPE_OPERATOR;
		case '+':
		case '-':
			return NAMETYPE_ADDITION;
		case '<':
		case '=':
		case '>':
		case '~':
			return NAMETYPE_RELATION;
		default:
			return NAMETYPE_NAME;
		}
	}

	const Step *Parsing::name(Runner &run)
	{
		unsigned char const *from = at;
		const NodeConstant *nameSelector = language.defaultNamespace;
		Nametype nametype = this->nametype();
		const PilsString *name = NULL;
		const Constant *result = NULL;
		if (nametype == NAMETYPE_PREFIX)
		{
			const PilsString *prefix = PilsString::get((const PILS_CHAR *)from, at - from);
			nameSelector = (const NodeConstant *)language.namespaces->getAttribute(*prefix);
			prefix->releaseReference();
			if (!nameSelector)
				return error(run, ERROR_BAD_PREFIX);
			from = ++at;
			switch (*at)
			{
			default:
				nametype = this->nametype();
				if (nametype == NAMETYPE_PREFIX)
					return error(run, ERROR_MULTIPLE_PREFIX);
				break;
			case '"':
				if ((name = string()))
				{
					if (at < end && *at == ':')
						nametype = NAMETYPE_NODEHEAD;
					else nametype = NAMETYPE_NAME;
					break;
				}
				else return error(run, ERROR_BAD_STRING);
			case '?':
				at++;
				const Constant* namespaceUrl = nameSelector->cliche->head;
				if (namespaceUrl == &Builtin::name.minus)
				{
					return error(run, ERROR_FORBIDDEN_NAME);
				}
				namespaceUrl->addReference();
				return constant(run, namespaceUrl);
			}
		}
		else if (at == from + 1 && *from == '\'')
		{
			result = lastName?lastName:&Empty::singleton;
            name = PilsString::get("-"); //dummy - this string can be unduplicated
		}
		if (!name)
			name = PilsString::get((const PILS_CHAR *)from, at - from - (nametype == NAMETYPE_ASTERISKED));
		if (!result)
			result = nameSelector->getAttribute(*name);

		if (result)
		{
			name->unduplicateReference();
			if (result == &Empty::singleton)
				return error(run, ERROR_FORBIDDEN_NAME);
			result->addReference();
		}
		else
		{
			const Constant* namespaceUrl = nameSelector->cliche->head;
			if (namespaceUrl == &Builtin::name.minus)
			{
				name->releaseReference();
				return error(run, ERROR_UNKNOWN_NAME);
			}
			namespaceUrl->addReference();
			result = namespaceUrl->clichefy(name);
		}
		Parse &parse = *(Parse *)run.sink;
		tracing(result, parse.at);
		switch (nametype)
		{
		case NAMETYPE_OPERATOR:
			return parse.operator_(run, *this, PARSE_ARGUMENT, result);
		case NAMETYPE_ADDITION:
			return parse.operator_(run, *this, PARSE_ADDEND, result);
		case NAMETYPE_RELATION:
			return parse.operator_(run, *this, PARSE_COMPARAND, result);
		case NAMETYPE_NODEHEAD:
			{
				at++;
				lastName = result;
				return parse.nodehead(run, *this, result);
			}
		default:
			lastName = result;
			return parse.name(run, *this, result);
		}
	}

	const Step *Parsing::questionName(Runner &run)
	{
		if (at < end)
		{
			const NodeConstant *nameSelector = language.defaultNamespace;
			const Constant* namespaceUrl = nameSelector->cliche->head;
			switch (*at)
			{
			case '?':
				at++;
				if (namespaceUrl == &Builtin::name.minus)
				{
					return error(run, ERROR_FORBIDDEN_NAME);
				}
				namespaceUrl->addReference();
				return constant(run, namespaceUrl);
			case '"':
				if (const PilsString *name = string())
				{
					const Constant *result = nameSelector->getAttribute(*name);
					if (result)
					{
						name->unduplicateReference();
						if (result == &Empty::singleton)
							return error(run, ERROR_FORBIDDEN_NAME);
						result->addReference();
					}
					else
					{
						const Constant* namespaceUrl = nameSelector->cliche->head;
						if (namespaceUrl == &Builtin::name.minus)
						{
							name->releaseReference();
							return error(run, ERROR_UNKNOWN_NAME);
						}
						namespaceUrl->addReference();
						result = namespaceUrl->clichefy(name);
					}
					Parse &parse = *(Parse *)run.sink;
					if (at < end && *at == ':')
						return constant(run, result);
					tracing(result, parse.at);
					return parse.name(run, *this, result);
				}
				else return error(run, ERROR_BAD_STRING);
			}
		}
		return error(run, ERROR_BAD_PREFIX);
	}

	const Step *Parsing::constant(Runner &run, const Constant *value)
	{
		Parse *parse = (Parse*)run.sink;
		tracing(value, parse->at);
		if (at < end && *at == ':')
		{
			at++;
			return parse->nodehead(run, *this, value);
		}
		else return parse->constant(run, *this, value);
	}

	const Step *Parsing::number(Runner &run)
	{
		if (*at != '-' && at + 4 < end && at[1] >= '0' && at[1] <= '9' && at[2] >= '0' && at[2] <= '9' && at[3] >= '0' && at[3] <= '9' && at[4] == '-')
		{
			if (const Constant *result = date(run))
				return constant(run, result);
			else
				return error(run, ERROR_BAD_DATE);
		}
		bool negative = *at == '-';
		Float::Split split;
		if (negative) at++;
		if (at + 1 < end && at[0] == '0' && at[1] == 'x')
		{
			at += 2;
			split.resetAndReadHexadecimalDigits(at, end);
			goto done;
		}

		split.resetAndReadIntegerDigits(at, end);
		if (at < end)
		{
			switch (*at)
			{
			case ',':
				if (at + 1 < end && at[1] >= '0' && at[1] <= '9')
				{
					at++;
					split.readFractionDigits(at, end);
				}
				break;
			case '.':
				at++;
				if (at < end && *at >= '0' && *at <= '9')
				{
					split.readFractionDigits(at, end);
				}
				else if (!negative) return useLabel(run, (int)split.mantissa);
				break;
			case '"':
			case '[':
			case '(':
			case '{':
				if (!negative) return defineLabel(run, (int)split.mantissa);
				break;
			case 'd':
			case 'h':
			case 'm':
				{
					int done = 0;
					Duration::Split duration;
					duration.days = 0;
					duration.hour = 0;
					duration.minute = 0;
					duration.second = 0;
					duration.millisecond = 0;
					for(;;)
					{
						if (at == end) goto badDuration;
						switch (*at)
						{
						case 'd':
							if (done != 0) goto badDuration;
							duration.days = (int)split.mantissa;
							done = 1;
							break;
						case 'h':
							if (done > 1) goto badDuration;
							duration.hour = (int)split.mantissa;
							done = 2;
							break;
						case 'm':
							if (done > 2) goto badDuration;
							duration.minute = (int)split.mantissa;
							done = 3;
							break;
						case 's':
							if (done > 3) goto badDuration;
							duration.second = (int)split.mantissa;
							done = 4;
							break;
						case '.':
						case ',':
							if (done > 3) goto badDuration;
							at++;
							for (int d = 0; d < 3; d++)
							{
								duration.millisecond *= 10;
								if(at < end && *at >= '0' && *at <= '9')
								{
									duration.millisecond += *at++ - '0';
								}
								else if (d == 0) goto badDuration;
							}
							while (at < end && *at >= '0' && *at <= '9') at++;
							if (at == end || *at != 's') goto badDuration;
							duration.second = (int)split.mantissa;
							done = 4;
							break;
						default:
							goto badDuration;
						}
						at++;
						if (at == end||*at < '0'||*at > '9')
							break;
						split.resetAndReadIntegerDigits(at, end);
					}
					{
						long long milliseconds = (long long)duration.get();
						const Constant *result = Duration::get(negative?-milliseconds:milliseconds);
						return constant(run, result);
					}
				badDuration:
					return error(run, Parsing::ERROR_BAD_DURATION);
				}
			}
		}

		if (at < end && *at == 's')
		{
			while (split.exponent < -3)
			{
				split.exponent++;
				split.mantissa /= 10;
			}
			while (split.exponent > -3)
			{
				split.exponent--;
				split.mantissa *= 10;
			}
			at++;
			const Constant *result = Duration::get(negative?-split.mantissa:split.mantissa);
			return constant(run, result);
		}

		if (at < end)
		{
			switch (*at)
			{
			case 'e':
			case 'E':
				{
					long e = 0;
					at++;
					bool negexp = (at < end && *at == '-' && at++);
					bool empty = true;
					while (at < end && *at >= '0' && *at <= '9')
					{
						if (empty) empty = false;
						else e *= 10;
						e += *at++ - '0';
					}
					if (empty)
						return error(run, Parsing::ERROR_BAD_EXPONENT);
					if (negexp) split.exponent -= e;
					else split.exponent += e;
				}
				break;
			case '%':
				split.exponent -= 2;
				at++;
				break;
			}
		}
	done:
		double value = split.get();
		const Constant *result = Number::get(negative?-value:value);
		return constant(run, result);
	}

	const Constant *Parsing::date(Runner &run)
	{
		Timestamp::Split split;
		split.year = 0;
		split.month = 0;
		split.day = 0;
		split.hour = 0;
		split.minute = 0;
		split.second = 0;
		split.millisecond = 0;
		split.zoneSecond = 0;
		bool hasZone = false;
		for (int i = 0; i < 4; i++)
		{
			split.year *= 10;
			split.year += *at++ - '0';
		}
		at++;
		for (int i = 0; i < 2; i++)
		{
			if (at == end || *at < '0' || *at > '9') return NULL;
			split.month *= 10;
			split.month += *at++ - '0';
		}
		if (at == end || *at++ != '-') return NULL;
		for (int i = 0; i < 2; i++)
		{
			if (at == end || *at < '0' || *at > '9') return NULL;
			split.day *= 10;
			split.day += *at++ - '0';
		}
		int maxday;
		switch (split.month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			maxday = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			maxday = 30;
			break;
		case 2:
			maxday = split.year%4?28:split.year%100?29:split.year%400?28:29;
			break;
		default: return NULL;
		}
		if (split.day < 1 || split.day > maxday) return NULL;
		if (at != end && *at == 'T')
		{
			at++;
			for (int i = 0; i < 2; i++)
			{
				if (at == end || *at < '0' || *at > '9') return NULL;
				split.hour *= 10;
				split.hour += *at++ - '0';
			}
			if (split.hour > 23) return NULL;
			if (at != end && *at == ':')
			{
				at++;
				for (int i = 0; i < 2; i++)
				{
					if (at == end || *at < '0' || *at > '9') return NULL;
					split.minute *= 10;
					split.minute += *at++ - '0';
				}
				if (split.minute >= 60) return NULL;
				if (at != end && *at == ':')
				{
					at++;
					for (int i = 0; i < 2; i++)
					{
						if (at == end || *at < '0' || *at > '9') return NULL;
						split.second *= 10;
						split.second += *at++ - '0';
					}
					if (split.second > 60) return NULL;
					if (at != end && *at == '.')
					{
						at++;
						for (int i = 0; i < 3; i++)
						{
							split.millisecond *= 10;
							if (at != end && *at >= '0' && *at <= '9')
								split.millisecond += *at++ - '0';
							else if (i == 0) return NULL;
						}
					}
				}
			}
		}
		if (at != end)
		{
			bool negativeZone = false;
			switch (*at)
			{
			case 'Z':
				at++;
				hasZone = true;
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
				return NULL;
			case '-':
			case '+':
				negativeZone = *at == '-';
				hasZone = true;
				at++;
				if (at == end || *at < '0' || *at > '9') return NULL;
				split.zoneSecond += 36000 * (*at++ - '0');
				if (at == end || *at < '0' || *at > '9') return NULL;
				split.zoneSecond += 3600 * (*at++ - '0');
				if (at != end && *at == ':')
				{
					at++;
					if (at == end || *at < '0' || *at > '9') return NULL;
					split.zoneSecond += 600 * (*at++ - '0');
					if (at == end || *at < '0' || *at > '9') return NULL;
					split.zoneSecond += 60 * (*at++ - '0');
				}
				if (negativeZone) split.zoneSecond = -split.zoneSecond;
				break;
			}
		}
		long long time = split.get();
		if (hasZone)
			return Timestamp::get(time);
		else return PilsDate::get(time);
	}

	const Step *Parsing::useLabel(Runner &run, int index)
	{
		std::map<int, const Any *>::iterator find = labels.find(index);
		if (const Any *value = find == labels.end() ? NULL : find->second)
		{
			value->addReference();
			((Parse *)run.sink)->close(run, *this, PARSE_PHRASE, value);
			if (redirection) return redirection;
			return this;
		}
		else return error(run, ERROR_UNDEFINED_LABEL);
	}

	const Step *Parsing::defineLabel(Runner &run, int index)
	{
		if (labels.insert(std::pair<int, const Any *>(index, static_cast<const Any *>(NULL))).second)
		{
			new (run.allocate(sizeof(ParseLabel))) ParseLabel(at, index);
			return this;
		}
		else return error(run, ERROR_TWIN_LABEL);
	}

	const Step *Parsing::error(Runner &run, Parsing::ErrorCode code)
	{
		Parse *parse = (Parse *)run.sink;
		const unsigned char *begin = (const unsigned char *)source.value;
		const Constant *legs[3];
		legs[0] = Integer::get(parse->at - begin);
		legs[1] = Integer::get(at - begin);
		legs[2] = Integer::get(code);
		const Any *error = BuiltinClicheSyntaxError::singleton.node(legs);
		for (Kickable *kicking = run.sink; kicking != this; kicking = kicking->kick(run))
		{;}
		run.sink = kick(run);
		run.calling.what->addReference();
		run.calling.who->addReference();
		return run.sink->error(run, error, run.calling.what, run.calling.who);
	}

	void Parsing::redirectError(Runner &run, Parsing::ErrorCode code)
	{
		if (redirection) return;
		class ErrorRedirection : public Step
		{
		public:
			ErrorRedirection(Parsing *parsing, const Any *error)
				: parsing(parsing), error(error)
			{}
			const Step *step_(Runner &run) const
			{
				const Any *error = this->error;
				Parsing *parsing = this->parsing;
				for (Kickable *kicking = (Kickable*)(this + 1); kicking != parsing; kicking = kicking->kick(run))
				{;}
				run.sink = parsing->kick(run);
				run.calling.what->addReference();
				run.calling.who->addReference();
				return run.sink->error(run, error, run.calling.what, run.calling.who);
			}
			Parsing *parsing;
			const Any *const error;
		};
		Parse *parse = (Parse *)run.sink;
		const unsigned char *begin = (const unsigned char *)source.value;
		const Constant *legs[3];
		legs[0] = Integer::get(parse->at - begin);
		legs[1] = Integer::get(at - begin);
		legs[2] = Integer::get(code);
		const Any *error = BuiltinClicheSyntaxError::singleton.node(legs);
		redirection = new (run.allocate(sizeof(ErrorRedirection))) ErrorRedirection(this, error);
	}

	const Step *Parse::space(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		return &parsing;
	}

	const Step *Parse::end(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_END);
	}

	const Step *Parse::bar(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::beginParenthesis(Runner &run, Parsing &parsing)
	{
		new (run.allocate(sizeof(ParseInversionParenthesis))) ParseInversionParenthesis(parsing);
		return &parsing;
	}

	const Step *Parse::endParenthesis(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::beginSquare(Runner &run, Parsing &parsing)
	{
		new (run.allocate(sizeof(ParseSquare))) ParseSquare(parsing.at);
		return &parsing;
	}

	const Step *Parse::endSquare(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::endSquareNodehead(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::beginCurl(Runner &run, Parsing &parsing)
	{
		return (new (run.allocate(sizeof(ParseRuleset))) ParseRuleset(at))->beginCurl(run, parsing);
	}

	const Step *Parse::endCurl(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::comma(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::colon(Runner &run, Parsing &parsing)
	{
		PokerHead::singleton.addReference();
		Empty::singleton.addReference();
		AnyNodeBuilderChain *chain = new AnyNodeBuilderChain(&PokerHead::singleton, at, NULL);
		chain->aim(&Empty::singleton);
		new (run.allocate(sizeof(ParseNodeAttributes))) ParseNodeAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeValue))) ParseAttributeValue(parsing.at, Empty::singleton);
		return &parsing;
	}

	const Step *Parse::colonColon(Runner &run, Parsing &parsing)
	{
		return colon(run, parsing);
	}

	const Step *Parse::colonNode(Runner &run, Parsing &parsing)
	{
		PokerHead::singleton.addReference();
		AnyNodeBuilderChain *chain = new AnyNodeBuilderChain(&PokerHead::singleton, at, NULL);
		new (run.allocate(sizeof(ParseNodeAttributes))) ParseNodeAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *Parse::semicolon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *Parse::semicolonNode(Runner &run, Parsing &parsing)
	{
		Empty::singleton.addReference();
		AnyNodeBuilderChain *chain = new AnyNodeBuilderChain(&Empty::singleton, at, NULL);
		new (run.allocate(sizeof(ParseNodeAttributes))) ParseNodeAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *Parse::dot(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_DOT);
	}

	const Step *Parse::dotAttribute(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_DOT);
	}

	const Step *Parse::dotInversion(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_DOT);
	}

	const Step *Parse::dotColonInversion(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_DOT);
	}

	const Step *Parse::question(Runner &run, Parsing &parsing)
	{
		Empty::singleton.addReference();
		closePhrase(run, parsing, PARSE_PHRASE, &Empty::singleton);
		if (parsing.redirection) return parsing.redirection;
		return &parsing;
	}

	const Step *Parse::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		new (run.allocate(sizeof(ParseSequel))) ParseSequel(parsing.at, constant);
		return &parsing;
	}

	const Step *Parse::nodehead(Runner &run, Parsing &parsing, const Constant *head)
	{
		new (run.allocate(sizeof(ParseNodeStart))) ParseNodeStart(new AnyNodeBuilderChain(head, at, NULL), parsing.at);
		return &parsing;
	}

	const Step *Parse::name(Runner &run, Parsing &parsing, const Constant *name)
	{
		new (run.allocate(sizeof(ParseName))) ParseName(parsing.at, name);
		return &parsing;
	}

	const Step *Parse::operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name)
	{
		new (run.allocate(sizeof(ParsePrefixOperator))) ParsePrefixOperator(parsing.at, name);
		new (run.allocate(sizeof(ParseOperand))) ParseOperand(parsing.at, PARSE_ARGUMENT);
		return &parsing;
	}

	const Step *Parse::attributeName(Runner &run, Parsing &parsing, const Constant *value)
	{
		return parsing.error(run, Parsing::ERROR_BAD_DOT);
	}

	void Parse::closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		value = value->callHere();
		parsing.tracing(value, at);
		close(run, parsing, level, value);
	}

	void Parse::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		switch (level)
		{
		case PARSE_PHRASE:
		case PARSE_ADDEND:
		case PARSE_COMPARAND:
			new (run.allocate(sizeof(ParseSequel))) ParseSequel(parsing.at, value);
			break;
		case PARSE_ELEMENT:
			new (run.allocate(sizeof(ParseList))) ParseList(parsing.at, value);
			break;
		default:
			value->releaseReference();
			parsing.redirectError(run, Parsing::ERROR_NOT_IMPLEMENTED);
		}
	}

	void Parse::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		close(run, parsing, level, (const Any *)value);
	}

	void Parse::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level == PARSE_ELEMENT || level > PARSE_ATTRIBUTE)
		{
			Empty::singleton.addReference();
			close(run, parsing, level, (const Any *)&Empty::singleton);
		}
	}

	Sink *ParseLabel::kick(Runner &run)
	{
		return (Sink *)(this + 1);
	}

	void ParseLabel::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		parsing.labels[index] = value;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		next->close(run, parsing, level, value);
	}

	void ParseLabel::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		parsing.labels[index] = value;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		next->close(run, parsing, level, value);
	}

	const Step *ParseLabel::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		parsing.labels[index] = constant;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		return next->constant(run, parsing, constant);
	}
	const Step *ParseLabel::nodehead(Runner &run, Parsing &parsing, const Constant *head)
	{
		parsing.labels[index] = head;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		return next->nodehead(run, parsing, head);
	}

	Sink *ParseHoldAny::kick(Runner &run)
	{
		hold->releaseReference();
		return (Sink *)(this + 1);
	}

	void ParseStart::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			run.sink = (Sink *)(this + 1);
			new (run.allocate(sizeof(ParseDone))) ParseDone(parsing.at, value);
		}
		else Parse::close(run, parsing, level, value);
	}

	const Step *ParseDone::end(Runner &run, Parsing &parsing)
	{
		const Any *result = hold;
		run.sink = (Sink *)(this + 1);
		while (run.sink != (Sink *)&parsing) run.sink = run.sink->kick(run);
		return parsing.done(run, result);
	}

	const Step *ParseSequel::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		hold = constant->callWho(hold);
		parsing.tracing(hold, this[1].at);
		return &parsing;
	}

	const Step *ParseSequel::dot(Runner &run, Parsing &parsing)
	{
		new (run.allocate(sizeof(ParseOperand))) ParseOperand((at = parsing.at), PARSE_ARGUMENT);
		return &parsing;
	}

	const Step *ParseSequel::operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name)
	{
		if (level == PARSE_ADDEND||level == PARSE_COMPARAND) //if (false)
		{
			const Any *hold = this->hold;
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->close(run, parsing, level, hold);
		}
//		close(run, parsing, level);
		new (run.allocate(sizeof(ParseName))) ParseName(parsing.at, name);
		new (run.allocate(sizeof(ParseOperand))) ParseOperand(parsing.at, level);
		return &parsing;
	}

	void ParseSequel::closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		close(run, parsing, level, value);
	}

	void ParseSequel::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		hold = value->callWho(hold);
		parsing.tracing(hold, this[1].at);
		close(run, parsing, level);
	}

	void ParseSequel::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ARGUMENT)
		{
			const Any *hold = this->hold;
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->close(run, parsing, level, hold);
		}
	}

	const Step *ParseSequel::dotInversion(Runner &run, Parsing &parsing)
	{
		const Any *hold = this->hold;
		run.sink = (Sink *)(this + 1);
		new (run.allocate(sizeof(ParseInversion))) ParseInversion(parsing.at, hold);
		return &parsing;
	}

	const Step *ParseSequel::dotColonInversion(Runner &run, Parsing &parsing)
	{
		const Any *hold = this->hold;
		run.sink = (Sink *)(this + 1);
		new (run.allocate(sizeof(ParseColonInversion))) ParseColonInversion(parsing.at, hold);
		return &parsing;
	}

	const Step *ParseInversion::beginParenthesis(Runner &run, Parsing &parsing)
	{
		const Any *hold = this->hold;
		run.sink = (Sink *)(this + 1);
		new (run.allocate(sizeof(ParseInversionParenthesis))) ParseInversionParenthesis(parsing, hold);
		return &parsing;
	}

	Sink *ParseHideInversionBase::kick(Runner &run)
	{
		if (restore) restore->releaseReference();
		restore = hold;
		return (Sink *)(this + 1);
	}

	void ParseHideInversionBase::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		return ((Parse *)(run.sink = kick(run)))->close(run, parsing, level, value);
	}

	void ParseHideInversion::closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		return ((Parse *)(run.sink = kick(run)))->closePhrase(run, parsing, level, value);
	}

	void ParseInversionParenthesis::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level <= PARSE_ATTRIBUTE) return Parse::close(run, parsing, level, value);
		run.sink = kick(run);
		new (run.allocate(sizeof(ParseEndParenthesis))) ParseEndParenthesis(parsing.at, value);
	}

	const Step *ParseEndParenthesis::endParenthesis(Runner &run, Parsing &parsing)
	{
		const Any *value = hold;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		next->close(run, parsing, PARSE_PHRASE, value);
		if (parsing.redirection) return parsing.redirection;
		return &parsing;
	}

	Sink *ParseOperand::kick(Runner &run)
	{
		return (Sink *)(this + 1);
	}

	void ParseOperand::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level >= PARSE_ARGUMENT)
		{
			parsing.redirectError(run, Parsing::ERROR_MISSING_OPERAND);
		}
	}

	void ParseOperand::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level >= PARSE_ELEMENT || this->level == PARSE_ARGUMENT || /*this->level < PARSE_COMPARAND &&*/ level >= this->level)
		{
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->close(run, parsing, level, value);
		}
		else Parse::close(run, parsing, level, value);
	}

	const Step *ParseOperand::constant(Runner &run, Parsing &parsing, const Constant *value)
	{
		if (level == PARSE_ARGUMENT)
		{
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->close(run, parsing, PARSE_PHRASE, (const Any *)value);
			if (parsing.redirection) return parsing.redirection;
			return &parsing;
		}
		else return Parse::constant(run, parsing, value);
	}

	void ParsePrefixOperator::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		Parse *next = this + 1;
		value = hold->callWho(value);
		parsing.tracing(value, next->at);
		run.sink = (Sink *)next;
		return next->close(run, parsing, level, value);
	}

	Sink *ParseHoldConstant::kick(Runner &run)
	{
		hold->releaseReference();
		return (Sink *)(this + 1);
	}

	const Step *ParseName::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		const ClicheTiny *cliche = hold->clichefy();
		const Any *phrase = cliche->node(constant);
		cliche->unduplicateReference();
		Parse *next = this + 1;
		parsing.tracing(phrase, next->at);
		run.sink = (Sink *)next;
		next->closePhrase(run, parsing, PARSE_PHRASE, phrase);
		return &parsing;
	}

	void ParseName::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level >= PARSE_PHRASE)
		{
			const Any *phrase = hold;
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->closePhrase(run, parsing, level, phrase);
		}
	}

	void ParseName::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		const ClicheTiny *cliche = hold->clichefy();
		value = cliche->node(value);
		cliche->unduplicateReference();
		Parse *next = this + 1;
		parsing.tracing(value, next->at);
		run.sink = (Sink *)next;
		next->closePhrase(run, parsing, level, value);
	}

	const Step *ParseName::beginParenthesis(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = new AnyNodeBuilderChain(hold, this[1].at, NULL);
		run.sink = (Sink *)(this + 1);
		new (run.allocate(sizeof(ParseHideInversion))) ParseHideInversion(this[1].at, parsing, NULL);
		new (run.allocate(sizeof(ParsePhraseStart))) ParsePhraseStart(chain, parsing.at);
		return &parsing;
	}

	const Step *ParseName::beginSquare(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = new AnyNodeBuilderChain(hold, this[1].at, NULL);
		run.sink = (Sink *)(this + 1);
		new (run.allocate(sizeof(ParseHideInversion))) ParseHideInversion(this[1].at, parsing, NULL);
		new (run.allocate(sizeof(ParseConstantPhraseStart))) ParseConstantPhraseStart(chain, parsing.at);
		return &parsing;
	}

	Sink *ParseList::kick(Runner &run)
	{
		builder.~ListBuilder();
		return (Sink *)(this + 1);
	}

	void ParseList::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level < PARSE_ELEMENT)
		{
			return Parse::close(run, parsing, level, value);
		}
		else
		{
			builder.add(value);
			if (level > PARSE_ELEMENT)
			{
				close(run, parsing, level);
			}
		}
	}

	void ParseList::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level < PARSE_ELEMENT)
			return Parse::close(run, parsing, level);
		else if (level == PARSE_ELEMENT)
		{
			Empty::singleton.addReference();
			builder.add(&Empty::singleton);
		}
		else // level >= PARSE_ELEMENT
		{
			const Any *value = builder.build();
			parsing.tracing(value, this[1].at);
			((Parse *)(run.sink = kick(run)))->close(run, parsing, level, value);
		}
	}

	const Step *ParseList::comma(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		return &parsing;
	}

	Sink *ParseNodeBase::kick(Runner &run)
	{
		while (chain)
		{
			AnyNodeBuilderChain *next = chain->next;
			delete chain;
			chain = next;
		}
		return (Sink *)(this + 1);
	}

	const Any *ParseNodeBase::build(Runner &run, Parsing &parsing)
	{
		for (;;)
		{
			const Any *value = chain->build();
			parsing.tracing(value, chain->from);
			AnyNodeBuilderChain *temp = chain;
			chain = chain->next;
			delete temp;
			if (!chain) return value;
			chain->set(value);
		}
	}

	Sink *ParseColonInversion::kick(Runner &run)
	{
		while (chain)
		{
			AnyNodeBuilderChain *next = chain->next;
			delete chain;
			chain = next;
		}
		inner->releaseReference();
		return (Sink *)(this + 1);
	}

	const Step *ParseColonInversion::attributeName(Runner &run, Parsing &parsing, const Constant *name)
	{
		PokerHead::singleton.addReference();
		chain = new AnyNodeBuilderChain(&PokerHead::singleton, at, chain);
		chain->aim(name);
		chain->set(inner);
		const Any *value = build(run, parsing);
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		new (run.allocate(sizeof(ParseSequel))) ParseSequel(parsing.at, value);
		return &parsing;
	}

	void ParseColonInversion::close(Runner &run, Parsing &parsing, ParseLevel level)
	{}

	const Step *ParseColonInversion::colon(Runner &run, Parsing &parsing)
	{
		colonColon(run, parsing);
		chain->set(inner);
		const Any *value = build(run, parsing);
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		new (run.allocate(sizeof(ParseSequel))) ParseSequel(parsing.at, value);
		return &parsing;
	}

	const Step *ParseColonInversion::colonColon(Runner &run, Parsing &parsing)
	{
		PokerHead::singleton.addReference();
		chain = new AnyNodeBuilderChain(&PokerHead::singleton, at, chain);
		at = parsing.at;
		Empty::singleton.addReference();
		chain->aim(&Empty::singleton);
		return &parsing;
	}

	const Step *ParseColonInversion::colonNode(Runner &run, Parsing &parsing)
	{
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	void ParseNodeAttributes::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			const Any *value = build(run, parsing);
			Parse *next = this + 1;
			run.sink = (Sink *)(next);
			next->close(run, parsing, level, value);
		}
	}

	const Step *ParseNodeAttributes::dotAttribute(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(at);
		return &parsing;
	}

	const Step *ParseNodeAttributes::attributeName(Runner &run, Parsing &parsing, const Constant *value)
	{
		if (!chain->aim(value))
			return parsing.error(run, Parsing::ERROR_TWIN_ATTRIBUTE);
		new (run.allocate(sizeof(ParseAttributeValue))) ParseAttributeValue(parsing.at, *value);
		return &parsing;
	}

	const Step *ParseNodeAttributes::semicolon(Runner &run, Parsing &parsing)
	{
		Empty::singleton.addReference();
		at = parsing.at;
		return attributeName(run, parsing, &Empty::singleton);
	}

	void ParseNodeStart::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			Empty::singleton.addReference();
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(&Empty::singleton);
			const Any *value = build(run, parsing);
			Parse *next = this + 1;
			run.sink = (Sink *)(next);
			next->close(run, parsing, level, value);
		}
		else ParseNodeBase::close(run, parsing, level);
	}

	void ParseNodeStart::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level < PARSE_ATTRIBUTE)
		{
			Parse::close(run, parsing, level, value);
		}
		else
		{
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(value);
			if (level > PARSE_ATTRIBUTE)
			{
				value = build(run, parsing);
				Parse *next = this + 1;
				run.sink = (Sink *)(next);
				next->close(run, parsing, level, value);
				
			}
			else
			{
				new (this) ParseNodeAttributes(chain, at);
			}
		}
	}

	const Step *ParseNodeStart::dotAttribute(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseNodeAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *ParseNodeStart::dot(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseNodeAttributes(chain, parsing.at);
		const Constant *head = chain->head;
		head->addReference();
		chain->aim(head);
		new (run.allocate(sizeof(ParseAttributeValue))) ParseAttributeValue(parsing.at, *head);
		return &parsing;
	}

	const Step *ParseNodeStart::semicolon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	void ParsePhraseAttributes::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			AnyNodeBuilderChain *chain = this->chain;
			new (this) ParsePhraseEndParenthesis(chain, parsing.at);
		}
	}

	void ParsePhraseStart::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			Empty::singleton.addReference();
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(&Empty::singleton);
			AnyNodeBuilderChain *chain = this->chain;
			new (this) ParsePhraseEndParenthesis(chain, parsing.at);
		}
		else if (level == PARSE_ELEMENT)
		{
			Empty::singleton.addReference();
			close(run, parsing, level, (const Any *)&Empty::singleton);
		}
	}

	void ParsePhraseStart::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level < PARSE_ATTRIBUTE)
		{
			Parse::close(run, parsing, level, value);
		}
		else
		{
			AnyNodeBuilderChain *chain = this->chain;
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(value);
			if (level > PARSE_ATTRIBUTE)
			{
				AnyNodeBuilderChain *chain = this->chain;
				new (this) ParsePhraseEndParenthesis(chain, parsing.at);
			}
			else
			{
				new (this) ParsePhraseAttributes(chain, parsing.at);
			}
		}
	}

	const Step *ParsePhraseStart::dotAttribute(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParsePhraseAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *ParsePhraseStart::dot(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParsePhraseAttributes(chain, parsing.at);
		const Constant *head = chain->head;
		head->addReference();
		chain->aim(head);
		new (run.allocate(sizeof(ParseAttributeValue))) ParseAttributeValue(parsing.at, *head);
		return &parsing;
	}

	const Step *ParsePhraseStart::semicolon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *ParsePhraseEndParenthesis::endParenthesis(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		Parse *next = this + 1;
		const Any *phrase = build(run, parsing);
		run.sink = (Sink *)next;
		next->closePhrase(run, parsing, PARSE_PHRASE, phrase);
		if (parsing.redirection) return parsing.redirection;
		return &parsing;
	}

	const Step *ParseConstant::question(Runner &run, Parsing &parsing)
	{
		Empty::singleton.addReference();
		return constant(run, parsing, &Empty::singleton);
	}

	const Step *ParseConstant::name(Runner &run, Parsing &parsing, const Constant *name)
	{
		return constant(run, parsing, name);
	}

	const Step *ParseConstant::operator_(Runner &run, Parsing &parsing, ParseLevel level, const Constant *name)
	{
		return constant(run, parsing, name);
	}

	const Step *ParseConstant::relation(Runner &run, Parsing &parsing, const Constant *name)
	{
		return constant(run, parsing, name);
	}

	const Step *ParseConstant::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		close(run, parsing, PARSE_PHRASE, constant);
		if (parsing.redirection) return parsing.redirection;
		return &parsing;
	}

	void ParseConstant::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		switch (level)
		{
		case PARSE_PHRASE:
			new (run.allocate(sizeof(ParseConstantElement))) ParseConstantElement(parsing.at, value);
			break;
		case PARSE_ELEMENT:
			new (run.allocate(sizeof(ParseConstantCommaList))) ParseConstantCommaList(parsing.at, value);
			break;
		default:
			value->releaseReference();
			parsing.redirectError(run, Parsing::ERROR_NOT_IMPLEMENTED);
		}
	}

	void ParseConstant::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (const Constant *constant = value->as_Constant())
			close(run, parsing, level, constant);
		else
		{
			value->releaseReference();
			parsing.redirectError(run, Parsing::ERROR_BAD_CONSTANT);
		}
	}

	void ParseConstant::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level == PARSE_ELEMENT || level > PARSE_ATTRIBUTE)
		{
			Empty::singleton.addReference();
			close(run, parsing, level, &Empty::singleton);
		}
	}


	const Step *ParseConstant::nodehead(Runner &run, Parsing &parsing, const Constant *head)
	{
		new (run.allocate(sizeof(ParseConstantNodeStart))) ParseConstantNodeStart(new AnyNodeBuilderChain(head, at, NULL), parsing.at);
		return &parsing;
	}

	const Step *ParseConstant::colon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_CONSTANT);
	}

	const Step *ParseConstant::colonNode(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_CONSTANT);
	}

	const Step *ParseConstant::semicolonNode(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_BAD_CONSTANT);
	}

	void ParseSquare::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		switch (level)
		{
		default:
			ParseConstant::close(run, parsing, level, value);
			break;
		case PARSE_CLOSE:
			run.sink = (Sink *)(this + 1);
			new (run.allocate(sizeof(ParseEndSquare))) ParseEndSquare(parsing.at, value);
			break;
		case PARSE_BAR:
			new (run.allocate(sizeof(ParseCliche))) ParseCliche(parsing.at, value);
		}
	}

	void ParseSquare::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_BAR)
		{
			run.sink = (Sink *)(this + 1);
			Empty::singleton.addReference();
			new (run.allocate(sizeof(ParseEndSquare))) ParseEndSquare(parsing.at, &Empty::singleton);
		}
		else ParseConstant::close(run, parsing, level);
	}

	const Step *ParseEndSquare::endSquare(Runner &run, Parsing &parsing)
	{
		const Constant *hold = this->hold;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		return next->constant(run, parsing, hold);
	}

	const Step *ParseEndSquare::endSquareNodehead(Runner &run, Parsing &parsing)
	{
		const Constant *hold = this->hold;
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		return next->nodehead(run, parsing, hold);
	}

	const Step *ParseAttributeName::constant(Runner &run, Parsing &parsing, const Constant *constant)
	{
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		return next->attributeName(run, parsing, constant);
	}

	void ParseAttributeName::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		Parse *next = this + 1;
		run.sink = (Sink *)next;
		next->attributeName(run, parsing, value);
	}

	Sink *ParseAttributeValue::kick(Runner &run)
	{
		return (Sink*)(this + 1);
	}

	void ParseAttributeValue::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		if (level >= PARSE_ATTRIBUTE)
		{
			ParseNodeAttributes *next = (ParseNodeAttributes *)(this + 1);
			run.sink = (Sink *)next;
			next->chain->set(value);
			next->close(run, parsing, level);
		}
		else Parse::close(run, parsing, level, value);
	}

	void ParseAttributeValue::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level >= PARSE_ATTRIBUTE)
		{
			name.addReference();
			const Any *value = &name;
			if (&name != &Empty::singleton)
			{
				value = name.callHere();
				parsing.tracing(value, this[1].at);
			}
			close(run, parsing, level, value);
		}
		else Parse::close(run, parsing, level);
	}

	Sink *ParseConstantNodeBase::kick(Runner &run)
	{
		while (chain)
		{
			AnyNodeBuilderChain *next = chain->next;
			delete chain;
			chain = next;
		}
		return (Sink *)(this + 1);
	}

	const Any *ParseConstantNodeBase::build(Runner &run, Parsing &parsing)
	{
		for (;;)
		{
			const Any *value = chain->build();
			parsing.tracing(value, chain->from);
			AnyNodeBuilderChain *temp = chain;
			chain = chain->next;
			delete temp;
			if (!chain) return value;
			chain->set(value);
		}
	}

	void ParseConstantNodeAttributes::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			const Any *value = build(run, parsing);
			if (const Constant *constant = value->as_Constant())
			{
				Parse *next = this + 1;
				run.sink = (Sink *)(next);
				next->close(run, parsing, level, constant);
			}
			else
			{
				value->releaseReference();
				parsing.redirectError(run, Parsing::ERROR_BAD_CONSTANT);
			}
		}
	}

	const Step *ParseConstantNodeAttributes::dotAttribute(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(at);
		return &parsing;
	}

	const Step *ParseConstantNodeAttributes::attributeName(Runner &run, Parsing &parsing, const Constant *value)
	{
		if (!chain->aim(value))
			return parsing.error(run, Parsing::ERROR_TWIN_ATTRIBUTE);
		new (run.allocate(sizeof(ParseConstantAttributeValue))) ParseConstantAttributeValue(parsing.at, *value);
		return &parsing;
	}

	const Step *ParseConstantNodeAttributes::semicolon(Runner &run, Parsing &parsing)
	{
		Empty::singleton.addReference();
		at = parsing.at;
		return attributeName(run, parsing, &Empty::singleton);
	}

	void ParseConstantNodeStart::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			Empty::singleton.addReference();
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(&Empty::singleton);
			const Any *value = build(run, parsing);
			if (const Constant *constant = value->as_Constant())
			{
				Parse *next = this + 1;
				run.sink = (Sink *)(next);
				next->close(run, parsing, level, constant);
			}
			else
			{
				value->releaseReference();
				parsing.redirectError(run, Parsing::ERROR_BAD_CONSTANT);
			}
		}
		else ParseConstantNodeBase::close(run, parsing, level);
	}

	void ParseConstantNodeStart::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		if (level < PARSE_ATTRIBUTE)
		{
			ParseConstant::close(run, parsing, level, value);
		}
		else
		{
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(value);
			if (level > PARSE_ATTRIBUTE)
			{
				const Any *node = build(run, parsing);
				if (const Constant *constant = node->as_Constant())
				{
					Parse *next = this + 1;
					run.sink = (Sink *)(next);
					next->close(run, parsing, level, constant);
				}
				else
				{
					node->releaseReference();
					parsing.redirectError(run, Parsing::ERROR_BAD_CONSTANT);
				}
				
			}
			else
			{
				new (this) ParseConstantNodeAttributes(chain, at);
			}
		}
	}

	const Step *ParseConstantNodeStart::dotAttribute(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseConstantNodeAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *ParseConstantNodeStart::dot(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseConstantNodeAttributes(chain, parsing.at);
		const Constant *head = chain->head;
		head->addReference();
		if (!chain->aim(head))
			return parsing.error(run, Parsing::ERROR_TWIN_ATTRIBUTE);
		new (run.allocate(sizeof(ParseConstantAttributeValue))) ParseConstantAttributeValue(parsing.at, *head);
		return &parsing;
	}

	const Step *ParseConstantNodeStart::semicolon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	void ParseConstantPhraseAttributes::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE)
		{
			AnyNodeBuilderChain *chain = this->chain;
			new (this) ParseConstantPhraseEndSquare(chain, parsing.at);
		}
	}

	void ParseConstantPhraseStart::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_ATTRIBUTE || level == PARSE_ELEMENT)
		{
			Empty::singleton.addReference();
			close(run, parsing, level, &Empty::singleton);
		}
	}

	void ParseConstantPhraseStart::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		if (level < PARSE_ATTRIBUTE)
		{
			ParseConstant::close(run, parsing, level, value);
		}
		else if (level == PARSE_BAR)
		{
			new (run.allocate(sizeof(ParseCliche))) ParseCliche(parsing.at, value);
		}
		else
		{
			AnyNodeBuilderChain *chain = this->chain;
			Empty::singleton.addReference();
			chain->aim(&Empty::singleton);
			chain->set(value);
			if (level > PARSE_ATTRIBUTE)
			{
				AnyNodeBuilderChain *chain = this->chain;
				new (this) ParseConstantPhraseEndSquare(chain, parsing.at);
			}
			else
			{
				new (this) ParseConstantPhraseAttributes(chain, parsing.at);
			}
		}
	}

	const Step *ParseConstantPhraseStart::dotAttribute(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseConstantPhraseAttributes(chain, parsing.at);
		new (run.allocate(sizeof(ParseAttributeName))) ParseAttributeName(parsing.at);
		return &parsing;
	}

	const Step *ParseConstantPhraseStart::dot(Runner &run, Parsing &parsing)
	{
		AnyNodeBuilderChain *chain = this->chain;
		new (this) ParseConstantPhraseAttributes(chain, parsing.at);
		const Constant *head = chain->head;
		head->addReference();
		chain->aim(head);
		new (run.allocate(sizeof(ParseConstantAttributeValue))) ParseConstantAttributeValue(parsing.at, *head);
		return &parsing;
	}

	const Step *ParseConstantPhraseStart::semicolon(Runner &run, Parsing &parsing)
	{
		return parsing.error(run, Parsing::ERROR_UNEXPECTED_CHARACTER);
	}

	const Step *ParseConstantPhraseEndSquare::endSquare(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		Parse *next = this + 1;
		const Any *phrase = build(run, parsing);
		run.sink = (Sink *)next;
		if (phrase->as_Constant())
		{
			next->closePhrase(run, parsing, PARSE_PHRASE, phrase);
			if (parsing.redirection) return parsing.redirection;
			return &parsing;
		}
		else return parsing.error(run, Parsing::ERROR_BAD_CONSTANT);
	}

	Sink *ParseConstantAttributeValue::kick(Runner &run)
	{
		return (Sink*)(this + 1);
	}

	void ParseConstantAttributeValue::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		if (level >= PARSE_ATTRIBUTE)
		{
			ParseConstantNodeAttributes *next = (ParseConstantNodeAttributes *)(this + 1);
			run.sink = (Sink *)next;
			next->chain->set(value);
			next->close(run, parsing, level);
		}
		else ParseConstant::close(run, parsing, level, value);
	}

	void ParseConstantAttributeValue::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level >= PARSE_ATTRIBUTE)
		{
			name.addReference();
			close(run, parsing, level, &name);
		}
		else ParseConstant::close(run, parsing, level);
	}

	Sink *ParseConstantHold::kick(Runner &run)
	{
		hold->releaseReference();
		return (Sink *)(this + 1);
	}

	Sink *ParseConstantList::kick(Runner &run)
	{
		builder.~ListBuilder();
		return (Sink *)(this + 1);
	}

	void ParseConstantCommaList::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		if (level < PARSE_ELEMENT)
		{
			return ParseConstant::close(run, parsing, level, value);
		}
		else
		{
			builder.add(value);
			if (level > PARSE_ELEMENT)
			{
				close(run, parsing, level);
			}
		}
	}

	void ParseConstantCommaList::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level < PARSE_ELEMENT)
			return ParseConstant::close(run, parsing, level);
		else if (level == PARSE_ELEMENT)
		{
			Empty::singleton.addReference();
			builder.add(&Empty::singleton);
		}
		else // level >= PARSE_ELEMENT
		{
			const ListConstant *value = builder.build();
			parsing.tracing(value, this[1].at);
			Parse *next = (Parse *)(run.sink = kick(run));
			next->close(run, parsing, level, value);
		}
	}

	const Step *ParseConstantCommaList::comma(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		return &parsing;
	}

	void ParseConstantElement::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *second)
	{
		const Constant *first = hold;
		run.sink = (Sink *)(this + 1);
		ParseConstantShortList *parse = new (run.allocate(sizeof(ParseConstantShortList))) ParseConstantShortList(parsing.at, first, second);
		parse->close(run, parsing, level);
	}

	void ParseConstantElement::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level >= PARSE_ELEMENT)
		{
			const Constant *value = hold;
			Parse *next = this + 1;
			run.sink = (Sink *)next;
			next->close(run, parsing, level, value);
		}
	}

	void ParseConstantShortList::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		builder.add(value);
		close(run, parsing, level);
	}

	void ParseConstantShortList::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		if (level > PARSE_PHRASE)
		{
			const ListConstant *value = builder.build();
			parsing.tracing(value, this[1].at);
			((Parse *)(run.sink = kick(run)))->close(run, parsing, level, value);
		}
	}

	Sink *ParseCliche::kick(Runner &run)
	{
		builder.~ClicheBuilder();
		return (Sink *)(this + 1);
	}

	const Step *ParseCliche::endSquare(Runner &run, Parsing &parsing)
	{
		const Cliche *value = builder.build();
		parsing.tracing(value, this[1].at);
		((Parse*)(run.sink = kick(run)))->close(run, parsing, PARSE_CLOSE, value);
		if (parsing.redirection) return parsing.redirection;
		return ((Parse*)(run.sink))->endSquare(run, parsing);
	}

	const Step *ParseCliche::endSquareNodehead(Runner &run, Parsing &parsing)
	{
		const Cliche *value = builder.build();
		parsing.tracing(value, this[1].at);
		((Parse*)(run.sink = kick(run)))->close(run, parsing, PARSE_CLOSE, value);
		if (parsing.redirection) return parsing.redirection;
		return ((Parse*)(run.sink))->endSquareNodehead(run, parsing);
	}

	const Step *ParseCliche::bar(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		return &parsing;
	}

	void ParseCliche::close(Runner &run, Parsing &parsing, ParseLevel level, const Constant *value)
	{
		if (level <= PARSE_ATTRIBUTE)
			ParseConstant::close(run, parsing, level, value);
		else if (!builder.add(value))
			parsing.redirectError(run, Parsing::ERROR_TWIN_ATTRIBUTE);
	}

	Sink *ParseRuleset::kick(Runner &run)
	{
		builder.~ListBuilder();
		return (Sink *)(this + 1);
	}

	void ParseRuleset::close(Runner &run, Parsing &parsing, ParseLevel level)
	{
		const ListExpress *rules = (const ListExpress *)builder.build();
		Parse *next = (Parse *)kick(run);
		run.sink = (Sink *)next;
		const Any *ruleset = BuiltinClicheRuleset::singleton.node(rules);
		parsing.tracing(ruleset, next->at);
		next->close(run, parsing, level, ruleset);
	}

	const Step *ParseRulePattern::dot(Runner &run, Parsing &parsing)
	{
		new (this)ParseRuleDotPattern(parsing.at);
		return &parsing;
	}

	const Step *ParseRulePattern::dotAttribute(Runner &run, Parsing &parsing)
	{
		new (this)ParseRuleDotPattern(parsing.at);
		return &parsing;
	}

	void ParseRuleDotPattern::closePhrase(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		return close(run, parsing, level, value);
	}

	void ParseRulePatternBase::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		switch (level)
		{
		case PARSE_CLOSE:
			parsing.redirectError(run, Parsing::ERROR_BAD_RULE);
			break;
		case PARSE_BAR:
			run.sink = (Sink *)(this + 1);
			new (run.allocate(sizeof(ParseRuleAction))) ParseRuleAction(at, value);
			break;
		default:
			Parse::close(run, parsing, level, value);
		}
	}

	void ParseRuleAction::close(Runner &run, Parsing &parsing, ParseLevel level, const Any *value)
	{
		switch (level)
		{
		case PARSE_CLOSE:
			{
				const Any *legs[] = {hold, value};
				value = BuiltinClicheRule::singleton.node(legs);
				new (this) ParseRuleEnd(at, value);
			}
			break;
		case PARSE_BAR:
			parsing.redirectError(run, Parsing::ERROR_BAD_RULE);
			break;
		default:
			Parse::close(run, parsing, level, value);
		}
	}

	const Step *ParseRuleAction::bar(Runner &run, Parsing &parsing)
	{
		at = parsing.at;
		return &parsing;
	}

	const Step *ParseRuleEnd::endCurl(Runner &run, Parsing &parsing)
	{
		ParseRuleset *next = (ParseRuleset *)(this + 1);
		parsing.tracing(hold, next->at);
		next->at = parsing.at;
		next->builder.add(hold);
		run.sink = (Sink *)next;
		return &parsing;
	}

	const Step *ParseRuleset::beginCurl(Runner &run, Parsing &parsing)
	{
		new (run.allocate(sizeof(ParseRulePattern))) ParseRulePattern(parsing.at);
		return &parsing;
	}
}
