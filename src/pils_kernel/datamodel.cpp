/* This file is public domain */
#include "datamodel.h"
#include "sink.h"
#include <string.h>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <cstring>

namespace PILS
{
    Step::~Step() = default;

	Any::Any()
	{
    }

	/* For protection against circularity when inserting callbacks in non-aliens */

    void Any::disposeRoot(Runner &run)
    {
        assert(run.deletionQueue == nullptr);
        refcount.becomeScrap(nullptr);
        for (run.deletionQueue = destroy(run); run.deletionQueue; run.deletionQueue = run.deletionQueue->destroy(run));
	}

    Any *Any::destroy(Runner &run)
	{
        unlink();
        Any *link = refcount.link();
        refcount.prepareForDeletion(run);
        delete this;
        return link;
	}

    void Any::releaseChild(const Any *child) const
    {
        refcount.run().release(child); // TODO: queue it instead of recursing
    }
    bool Any::isList(const Any *const *&element, const Integer *&count) const
	{
		return false;
	}

	bool Any::isList(const Any *const *&element, size_t &count) const
	{
		const Integer *c;
		if (isList(element, c))
		{
			count = c->value;
			return true;
		}
		else return false;
	}

	bool Any::isNode(const Any *const *&element, const Cliche *&cliche) const
	{
		return false;
	}

	const ClicheShort *Any::as_ClicheShort() const
	{
        return nullptr;
	}

	const ClicheTiny *Any::as_ClicheTiny() const
	{
        return nullptr;
	}

	const Constant *Any::as_Constant() const
	{
        return nullptr;
	}

	const Integer *Any::as_Integer() const
	{
        return nullptr;
	}

	const NodeConstant *Any::as_NodeConstant() const
	{
        return nullptr;
	}

	const NodeConstantTiny *Any::as_NodeConstantTiny() const
	{
        return nullptr;
	}

    const Channel *Any::as_Channel() const
    {
        return nullptr;
    }

    const ListConstant *Any::as_ListConstant() const
	{
        return nullptr;
	}

	const NodeExpress *Any::as_NodeExpress() const
	{
        return nullptr;
	}

	const Slot *Any::as_Slot() const
	{
        return nullptr;
	}

	const Rule *Any::as_Rule() const
	{
        return nullptr;
	}

	const Ruleset *Any::as_Ruleset() const
	{
        return nullptr;
	}

	const PilsString *Any::as_String() const
	{
        return nullptr;
	}

    void Any::writeToDebugOutput(int levels) const
    {
#ifndef NDEBUG
        writingToDebugOutput(levels);
        std::fputc('\n', stderr);
#endif
    }

    void Any::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        int status = 0;
        const char* mangled = typeid(*this).name();

        std::unique_ptr<char, void(*)(void*)> demangled(
            abi::__cxa_demangle(mangled, nullptr, nullptr, &status),
            std::free);

        if (status == 0 && demangled)
            std::fprintf(stderr, "<%s>", demangled.get());
        else
            std::fprintf(stderr, "<%s>", mangled);
#endif
    }
    void Any::writingToDebugOutputNextLevel(int level) const
    {
        if (level--) writingToDebugOutput(level);
        else std::fputs("...", stderr);
    }

	Constant::Constant(const Constant *&link)
	{
		hashLink = link;
		link = this;
	}

	const Constant *&Constant::hashChain(size_t hash)
	{
		return hashTable[(hash + (hash >> 16)) & 0xFFFF].hashLink;
	}

	Constant::Constant()
	{
		hashLink = this;
	}

    void Constant::removeFromHashTable() const
    {
        if (hashLink == nullptr)
            return;
        Mutex::Lock lock(Mutex::singleMutex);
        assert(this->refcount.count()==-1);
        const Constant **link = &hashLink->hashLink;
        while (*link != this)
            link = &(*link)->hashLink;
        *link = hashLink;
        hashLink = nullptr;
    }

    void Constant::unlink()
    {
        Mutex::Lock lock(Mutex::singleMutex);
        unhash();
    }

    const Constant *Constant::as_Constant() const
	{
		return this;
	}

	const ListConstant *ListConstant::as_ListConstant() const
	{
		return this;
	}

	bool Any::isNumber(double &number) const
	{
		return false;
	}

	bool Any::isNumber(float &number) const
	{
		double buffer;
		if (isNumber(buffer))
		{
			number = (float) buffer;
			return true;
		}
		else return false;
	}

	bool Integer::isNumber(double &number) const
	{
		number = value;
		return true;
	}

	bool Float::isNumber(double &number) const
	{
		number = value;
		return true;
	}

	void Constant::unhash()
	{
		const Constant **link = &hashLink->hashLink;
		while (*link != this)
			link = &(*link)->hashLink;
		*link = hashLink;
        hashLink == nullptr;
	}

	const ClicheShort *Empty::newCliche(const Constant *&link, const Constant *a) const
	{
        return new EmptyClicheShort(link, this, a);
	}

	const ClicheLong *Empty::newCliche(const Constant *&link, const Constant *const *a, size_t c) const
	{
		if (a[0] == &Empty::singleton)
		{
			switch(c)
			{
			case 2:
                return new BindCliche1(link, this, a, c);
			case 3:
                return new BindCliche2(link, this, a, c);
			case 4:
                return new BindCliche3(link, this, a, c);
			default:
                return new ((c - 1) * sizeof(Constant*)) BindCliche(link, this, a, c);
			}
		}
		else
            return new ((c - 1) * sizeof(Constant*)) EmptyClicheLong(link, this, a, c);
	}

	const Any *EmptyClicheShort::node(const Constant *element) const
	{
        return new NodeExpressShort(*this, element);
	}

	const Any *EmptyClicheLong::node(const Any *const *element) const
	{
        return new ((count - 1) * sizeof(Any*))	NodeExpressLong(*this, element);
	}

	const Any *EmptyClicheLong::node(const Constant *const *element) const
	{
        return new ((count - 1) * sizeof(Any*)) NodeExpressLong(*this, (const Any *const *)element);
	}

	const ClicheLong *JumperHead::newCliche(const Constant *&link, const Constant *const *a, size_t c) const
	{
		if (a[0] == &Empty::singleton)
		{
			switch(c)
			{
			case 2:
                return new JumperCliche1(link, this, a, c);
			case 3:
                return new JumperCliche2(link, this, a, c);
			case 4:
                return new JumperCliche3(link, this, a, c);
			default:
                return new ((c - 1) * sizeof(Constant*)) JumperCliche(link, this, a, c);
			}
		}
        else return Constant::newCliche(link, a, c);
	}

	const Any *JumperHead::node(const Constant *element) const
	{
        return new NodeExpressTiny(*this, element);
	}

    const Integer* Integer::as_Integer() const
	{
		return this;
	}

	const Integer *Constant::hashLookup(long v) const
	{ return hashLink->hashLookup(v);}
	const Float *Constant::hashLookup(double v) const
	{ return hashLink->hashLookup(v);}
	const PilsString *Constant::hashLookup(const PILS_CHAR *text, size_t count) const
	{ return hashLink->hashLookup(text, count); }
	const ClicheShort *Constant::hashLookup(const Constant *h, const Constant *a) const
	{ return hashLink->hashLookup(h, a); }
	const ClicheLong *Constant::hashLookup(const Constant *h, const Constant *const *a, size_t c) const
	{ return hashLink->hashLookup(h, a, c); }
	const NodeConstantShort *Constant::hashLookup(const ClicheShort &cliche, const Constant *value) const
	{ return hashLink->hashLookup(cliche, value); }
	const NodeConstantLong *Constant::hashLookup(const ClicheLong &cliche, const Constant *const *value) const
	{ return hashLink->hashLookup(cliche, value); }
	const ListConstant *Constant::hashLookup(const Constant *const *a, size_t c, bool copying) const
	{ return hashLink->hashLookup(a, c, copying); }
	const ReallySpecial *Constant::hashLookup(SpecialLookup &lookup) const
	{ return hashLink->hashLookup(lookup);}
	const PilsColor *Constant::hashLookupPilsColor(unsigned int v) const
	{ return hashLink->hashLookupPilsColor(v);}

	const Integer *Integer::get(long v)
	{
		if ((unsigned long)v < 0x10000)
		{
			const Integer *got = &ShortInteger::hashTable[v];
			got->retain();
			return got;
		}
		else
		{
			const Constant *&link = Constant::hashChain(v);
            Mutex::Lock lock(Mutex::singleMutex);
			return link->hashLookup(v);
		}
	}

	const Integer *Integer::getInsideLock(long v)
	{
		if ((unsigned long)v < 0x10000)
		{
			const Integer *got = &ShortInteger::hashTable[v];
			got->retain();
			return got;
		}
		else
		{
			const Constant *&link = Constant::hashChain(v);
			return link->hashLookup(v);
		}
	}

	const Step *Integer::caller(Runner &run, const Any &where_) const
	{
		return where_.calling(run, *this);
	}

	const Integer *Integer::hashLookup(long v) const
	{
		if (v == value && duplicateReference())	return this;
		else return hashLink->hashLookup(v);
	}

	const Integer *ShortInteger::hashLookup(long v) const
	{
		/* End of hash chain - construct integer */
        return new Integer(((ShortInteger*)this)->hashLink, v);
	}

	const Number *Number::get(double v)
	{
		long truncated = (long)v;
		if (v == (double)truncated)
			return Integer::get(truncated);
        static std::hash<double> hasher;
        const Constant *&link = Constant::hashChain(hasher(v));
        Mutex::Lock lock (Mutex::singleMutex);
		return link->hashLookup(v);
	}

	const Float *ShortInteger::hashLookup(double v) const
	{
		/* End of hash chain - construct float */
        return new Float(hashLink, v);
	}

    const Float *Float::hashLookup(double v) const
	{
		if (v == value && duplicateReference()) return this;
		else return hashLink->hashLookup(v);
	}

	void Float::Split::resetAndReadIntegerDigits(const unsigned char *&at, const unsigned char *end)
	{
		mantissa = 0;
		exponent = 0;
		while (at < end && *at >= '0' && *at <= '9')
		{
			if (mantissa < 100000000000000000LL)
			{
				mantissa *= 10;
				mantissa += *at++ - '0';
			}
			else
			{
				at++;
				exponent++;
			}
		}
	}

	void Float::Split::readFractionDigits(const unsigned char *&at, const unsigned char *end)
	{
		while (at < end && *at >= '0' && *at <= '9')
		{
			if (mantissa < 100000000000000000LL)
			{
				exponent--;
				mantissa *= 10;
				mantissa += *at++ - '0';
			}
		}
	}

	void Float::Split::resetAndReadHexadecimalDigits(const unsigned char *&at, const unsigned char *end)
	{
		mantissa = 0;
		exponent = 0;
		for (; at < end; at++)
		{
			switch (*at)
			{
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
				mantissa <<= 4;
				mantissa += *at - '0';
				continue;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				mantissa <<= 4;
				mantissa += *at - 'a' + 10;
				continue;
			default:
				return;
			}
		}
	}

	CountedConstant::CountedConstant(const Constant *&link, size_t c)
		: Constant(link), count(Integer::getInsideLock((long)c))
	{
	}

	const PilsColor *PilsColor::get(unsigned int v)
	{
		const Constant *&link = Constant::hashChain((long)v);
        Mutex::Lock lock(Mutex::singleMutex);
		return link->hashLookupPilsColor(v);
	}

	const PilsColor *PilsColor::hashLookupPilsColor(unsigned int v) const
	{
		if (v == value && duplicateReference())
			return this;
		else return hashLink->hashLookupPilsColor(v);
	}

	const NodeConstantShort *PilsColor::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{
		return cliche.newNode(link, this);
	}

    const PilsString *PilsString::get(const PILS_CHAR *text)
	{
        return get(text, strlen(text));
    }

    const PilsString *PilsString::getInsideLock(const PILS_CHAR *text)
    {
        return getInsideLock(text, strlen(text));
    }

    const PilsString *PilsString::get(const std::string &text)
    {
        return get(text.data(), text.size());
    }

    const Constant *&PilsString::hashChain(const PILS_CHAR *text, size_t count)
	{
		unsigned long hash = 7913;
		for (size_t index = 0; index < count; index++)
		{
			hash += text[index];
			hash *= 47;
		}
		return Constant::hashChain(hash);
	}

	const PilsString *PilsString::get(const PILS_CHAR *text, size_t count)
	{
		const Constant *&chain = hashChain(text, count);
        Mutex::Lock lock (Mutex::singleMutex);
		return chain->hashLookup(text, count);
	}

    const PilsString *PilsString::getInsideLock(const PILS_CHAR *text, size_t count)
    {
        const Constant *&chain = hashChain(text, count);
        return chain->hashLookup(text, count);
    }

    PilsString::PilsString(const PILS_CHAR *text, size_t count)
        : PilsString(hashChain(text, count), text, count)
    {}

    const PilsString* PilsString::hashLookup(const PILS_CHAR* text, size_t c) const
    {
        if ((size_t)count->value == c &&
            std::memcmp(text, value, c * sizeof(PILS_CHAR)) == 0 &&
            duplicateReference())
        {
            return this;
        }
        return hashLink->hashLookup(text, c);
    }

	const PilsString *ShortInteger::hashLookup(const PILS_CHAR *text, size_t c) const
	{
        return new ((c + 1) * sizeof(PILS_CHAR)) PilsString(hashLink, text, c);
	}

	PilsString::PilsString(const Constant *&link, const PILS_CHAR *text, size_t c)
        : CountedConstant(link, c)
#ifndef NDEBUG
        , bug(text, c)
#endif
    {
        auto* buf = const_cast<PILS_CHAR*>(value);
        memcpy(buf, text, c * sizeof(PILS_CHAR));
        buf[c] = 0;
	}

	const PilsString *PilsString::as_String() const
	{
		return this;
	}

	NameSkin PilsString::nameSkin() const
	{
		//Is this string a valid PILS name/operator/relation?

		size_t c = count->value;
		if (c == 0) return NAMESKIN_STRING; // empty string
		switch (value[0])
		{
		case '0': // nonnegative numbers
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.': // initial full stop
		case '#': // color etc.
			return NAMESKIN_STRING;
		case '-':
			if (c > 1 && value[1] >= '0' && value[1] <= '9')
				return NAMESKIN_STRING; // negative number
			break;
		}

		for (size_t i = 0; i < c; i++)
		{
			// multibyte characters must be well-formed
			if (value[i] & 0x80)
			{
				unsigned int shifter = value[i];
				if ((shifter & 0x40) == 0) return NAMESKIN_STRING;
				for (;shifter & 0x40; shifter <<= 1)
				{
					if (i == c || (value[++i] & 0xC0) != 0x80) return NAMESKIN_STRING;
				}
			}
			// space, punctuation, non-printable characters etc.
			else if (value[i] <= '"') return NAMESKIN_STRING;
			else switch (value[i])
			{
				case '(':
				case ')':
				case ',':
				case ':':
				case ';':
				case '?':
				case '[':
				case ']':
				case '{':
				case '|':
				case '}':
				case 0x7F:
					return NAMESKIN_STRING;
			}
		}

		switch (value[c - 1])
		{
		case '#':
		case '$':
		case '*':
		case '%':
		case '&':
		case '/':
		case '\\':
		case '^':
			return NAMESKIN_OPERATOR;

		case '+':
		case '-':
			return NAMESKIN_ADDITION;

		case '<':
		case '=':
		case '>':
		case '~':
			return NAMESKIN_RELATION;

		case '\'':
			for (int cc = c - 1; cc--;)
			{
				switch (value[cc])
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
					return NAMESKIN_ASTERISKED;
				default:
					return NAMESKIN_NAME;
				}
			}
			return NAMESKIN_ASTERISKED;
		default:
			return NAMESKIN_NAME;
		}
	}

    CountedConstant::~CountedConstant()
    {
        releaseChild(count);
    }

	Cliche::Cliche(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
		: Constant(link), count(c), head(h)
	{
		for (size_t i = 0; i < c; i++)
			attributes[i] = a[i];
	}

	Cliche::Cliche(const Constant *h, const Constant *a1, const Constant *a2)
		: Constant(hashChain(h, a1, a2)), count(2), head(h)
	{
		attributes[0] = a1;
		attributes[1] = a2;
	}

	Cliche::Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3)
		: Constant(hashChain(h, a1, a2, a3)), count(3), head(h)
	{
		attributes[0] = a1;
		attributes[1] = a2;
		attributes[2] = a3;
	}

	Cliche::Cliche(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4)
		: Constant(hashChain(h, a1, a2, a3, a4)), count(4), head(h)
	{
		attributes[0] = a1;
		attributes[1] = a2;
		attributes[2] = a3;
		attributes[3] = a4;
	}

	const Constant *&Cliche::hashChain(const Constant *h, const Constant *a1, const Constant *a2)
	{
		unsigned long hash = (unsigned long)reinterpret_cast<size_t>(h);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a1);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a2);
		return Constant::hashChain(hash);
	}

	const Constant *&Cliche::hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3)
	{
		unsigned long hash = (unsigned long)reinterpret_cast<size_t>(h);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a1);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a2);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a3);
		return Constant::hashChain(hash);
	}

	const Constant *&Cliche::hashChain(const Constant *h, const Constant *a1, const Constant *a2, const Constant *a3, const Constant *a4)
	{
		unsigned long hash = (unsigned long)reinterpret_cast<size_t>(h);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a1);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a2);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a3);
		hash *= 3;
		hash += (unsigned long)reinterpret_cast<size_t>(a4);
		return Constant::hashChain(hash);
	}

	const Cliche *Any::as_Cliche() const
	{
        return nullptr;
	}

	const Cliche *Cliche::as_Cliche() const
	{
		return this;
	}

    const Constant *Cliche::lookupNonempty(const NodeConstant *node, size_t start, const Constant *key) const
	{
		const Constant *const *end = attributes + count;
		const Constant *const *at = std::upper_bound(attributes + start, end, key);
		if (at > attributes && *--at == key)
			return node->element[at - attributes];
        else return nullptr;
	}

	const Any *Cliche::lookupNonempty(const NodeExpress *node, size_t start, const Constant *key) const
	{
		const Constant *const *end = attributes + count;
		const Constant *const *at = std::upper_bound(attributes + start, end, key);
		if (at > attributes && *--at == key)
			return node->element[at - attributes];
        else return nullptr;
	}

    const Constant *NodeConstant::getAttribute(const Constant &name) const
	{
		return cliche->lookupNonempty(this, 0, &name);
	}

	const Constant *NodeConstantTrailer::getAttribute(const Constant &name) const
	{
		if (&name == &Empty::singleton)	return element[0];
		else return cliche->lookupNonempty(this, 1, &name);
	}

	const Any *NodeExpress::getAttribute(const Constant &name) const
	{
		return cliche->lookupNonempty(this, 0, &name);
	}

    void NodeExpress::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        std::fputc('(', stderr);
        cliche->head->writingToDebugOutputNextLevel(level);
        std::fputc(':', stderr);

        for (size_t i = 0; i < cliche->count; ++i)
        {
            std::fputs(" .", stderr);
            cliche->attributes[i]->writingToDebugOutputNextLevel(level);
            std::fputc(' ', stderr);
            element[i]->writingToDebugOutputNextLevel(level);
        }
        std::fputc(')', stderr);
#endif
    }

    void NodeConstant::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        std::fputc('[', stderr);
        cliche->head->writingToDebugOutputNextLevel(level);
        std::fputc(':', stderr);

        for (size_t i = 0; i < cliche->count; ++i)
        {
            std::fputs(" .", stderr);
            cliche->attributes[i]->writingToDebugOutputNextLevel(level);
            std::fputc(' ', stderr);
            element[i]->writingToDebugOutputNextLevel(level);
        }
        std::fputc(']', stderr);
#endif
    }

    void Cliche::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        std::fputc('[', stderr);
        head->writingToDebugOutputNextLevel(level);

        for (size_t i = 0; i < count; ++i)
        {
            std::fputc('|', stderr);
            attributes[i]->writingToDebugOutputNextLevel(level);
        }
        std::fputc(']', stderr);
#endif
    }

    void PilsString::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        size_t max = 100;
        std::fputc('"', stderr);
        for (size_t i = 0; i < count->value && i < max; ++i)
        {
            std::fputc(value[i], stderr);
        }
        std::fputc('"', stderr);
        if (count->value > max)
            std::fputc('+', stderr);
#endif
    }
    void Empty::writingToDebugOutput(int level) const
    {
#ifndef NDEBUG
        std::fputs("[]", stderr);
#endif
    }

    const Any *NodeExpressTrailer::getAttribute(const Constant &name) const
	{
		if (&name == &Empty::singleton)	return element[0];
		else return cliche->lookupNonempty(this, 1, &name);
	}

	const Any *ClicheLong::node(const Any *const *element) const
	{
		for(size_t i = 0; i < count; i++)
		{
            if(element[i]->as_Constant() == nullptr)
			{
                return new ((count - 1) * sizeof(Constant*))
                    const NodeExpressLong((const ClicheLong&)*this, element);
			}
		}
		return node((const Constant *const *)(void *const *)element);
	}

	const Any *ClicheLong::node(const Constant *const *element) const
	{
		return nodeConstant(element);
	}

	const Any *ClicheTrailer::node(const Any *const *element) const
	{
		for(size_t i = 0; i < count; i++)
		{
            if(element[i]->as_Constant() == nullptr)
			{
                return new ((count - 1) * sizeof(Constant*))
                    const NodeExpressTrailer((const ClicheTrailer&)*this, element);
			}
		}
		return ((const ClicheLong*)this)->node((const Constant *const *)(void*const *)element);
	}

	const NodeConstant *Cliche::nodeConstant(const Constant *const *attributes) const
	{
		return nodifyingConstant(attributes);
	}

    const ClicheShort *Constant::clichefy(const Constant *attribute) const
	{
		if (attribute == &Empty::singleton)
		{
			attribute->unduplicateReference();
			return clichefy();
		}
        Mutex::Lock lock (Mutex::singleMutex);
		return clichefying(attribute);
	}

    const ClicheShort *Constant::clichefyInsideLock(const Constant *attribute) const
    {
        assert (attribute != &Empty::singleton);
        return clichefying(attribute);
    }

    const ClicheShort *Constant::clichefying(const Constant *attribute) const
	{
		return ClicheShort::hashChain(this, attribute)->hashLookup(this, attribute);
	}

	const Constant *&ClicheShort::hashChain(const Constant *h, const Constant *a)
	{
		unsigned long hash =
			(unsigned long)reinterpret_cast<size_t>(h) * 3
			+ (unsigned long)reinterpret_cast<size_t>(a);
		return Constant::hashChain(hash);
	}

	const ClicheShort *ClicheShort::hashLookup(const Constant *h, const Constant *a) const
	{
		if (head == h && attributes[0] == a && duplicateReference()) return this;
		else return hashLink->hashLookup(h, a);
	}

    const ClicheShort *Constant::newCliche(const Constant *&link, const Constant *a) const
	{
        return new const ClicheShort(link, this, a);
	}

	const ClicheShort* ClicheShort::as_ClicheShort() const
	{
		return this;
	}

	const Any *ClicheShort::node(const Any *const *element) const
	{
		return node(element[0]);
	}

	const Any *ClicheShort::node(const Constant *const *element) const
	{
		return node(element[0]);
	}

	const Any *ClicheShort::node(const Any *element) const
	{
		const Constant *constant = element->as_Constant();
		if (constant) return node(constant);
		else return node((const Express *)element);
	}

	const Any *ClicheShort::node(const Constant *element) const
	{
		return nodeConstant(element);
	}

	const NodeExpressShort *ClicheShort::node(const Express *element) const
	{
        return new const NodeExpressShort(*this, element);
	}

	const ClicheShort *ShortInteger::hashLookup(const Constant *h, const Constant *a) const
	{
		return h->newCliche(hashLink, a);
	}

	void ClicheShort::unduplicateChildren() const
	{
		head->unduplicateReference();
		attributes[0]->unduplicateReference();
	}

	const NodeConstant *ClicheShort::nodifyingConstant(const Constant *const *attributes) const
	{
		return nodeConstant(attributes[0]);
	}

    const ClicheTiny *Constant::clichefy() const
	{
        Mutex::Lock lock (Mutex::singleMutex);
		return clichefying();
	}

	const ClicheTiny *Constant::clichefying() const
	{
		const ClicheTiny *next = hashLink->as_ClicheTiny();
        if (next != nullptr && next->head == this && next->duplicateReference())
			return next;
		else return newCliche();
	}

	const ClicheTiny *Constant::newCliche() const
	{
        return new const ClicheTiny(this);
	}

	ClicheTiny::ClicheTiny(const Constant *h)
        :  ClicheShort(h->hashLink, h, Empty::get())
    {}

	const ClicheTiny *ClicheTiny::as_ClicheTiny() const
	{
		return this;
	}

	const NodeExpressShort *ClicheTiny::node(const Express *element) const
	{
        return new NodeExpressTiny(*this, element);
	}

	void ClicheTiny::unduplicateChildren() const
	{
		head->unduplicateReference();
	}

	const ClicheShort *ClicheTiny::hashLookup(const Constant *h, const Constant *a) const
	{
		return hashLink->hashLookup(h, a);
	}

    const ClicheLong *Constant::clichefy(const Constant *const *attribute, size_t count) const
	{
        Mutex::Lock lock (Mutex::singleMutex);
		return clichefying(attribute, count);
	}

    const ClicheLong *Constant::clichefying(const Constant *const *attribute, size_t count) const
	{
		unsigned long hash = (unsigned long)reinterpret_cast<size_t>(this);
		for (size_t i = 0; i < count; i++)
		{
			hash *= 3;
			hash += (unsigned long)reinterpret_cast<size_t>(attribute[i]);
		}
		hash += hash >> 16;
		return Constant::hashTable[(unsigned short)(hash & 0xFFFF)].hashLink->hashLookup(this, attribute, count);
	}

	const ClicheLong *ShortInteger::hashLookup(const Constant *h, const Constant *const *a, size_t c) const
	{
		return h->newCliche(hashLink, a, c);
	}

	const ClicheLong *ClicheLong::hashLookup(const Constant *h, const Constant *const *a, size_t c) const
	{
		if (c == count
			&& h == head
            && memcmp(&attributes, a, c * sizeof(Constant*)) == 0
			&& duplicateReference())
			return this;
		else return hashLink->hashLookup(h, a, c);
	}

    const ClicheLong* Constant::newCliche(const Constant*& link, const Constant* const* a, size_t c) const
    {
        size_t extra = (c - 1) * sizeof(Constant*);

        if (a[0] == &Empty::singleton)
            return new (extra) ClicheTrailer(link, this, a, c);
        else
            return new (extra) ClicheLong(link, this, a, c);
    }

    ClicheLong::ClicheLong(const Constant *&link, const Constant *h, const Constant *const *a, size_t c)
		:  Cliche(link, h, a, c)
	{}

	void ClicheLong::unduplicateChildren() const
	{
		head->unduplicateReference();
		for (size_t i = 0; i < count; i++)
			attributes[i]->unduplicateReference();
	}

    Cliche::~Cliche()
	{
        releaseChild(head);
		for (size_t i = 0; i < count; i++)
            releaseChild(attributes[i]);
	}

	const NodeConstant *ClicheLong::nodifyingConstant(const Constant *const *attributes) const
	{
		return nodeConstant(attributes);
	}

	const NodeConstantLong *ClicheLong::nodeConstant(const Constant *const *attributes) const
	{
		unsigned long hash = (unsigned long)reinterpret_cast<size_t>(this);
		for (size_t i = 0; i < count; i++)
		{
			hash *= 5;
			hash += (unsigned long)reinterpret_cast<size_t>(attributes[i]);
		}
		const Constant *&link = Constant::hashChain(hash);
        Mutex::Lock lock (Mutex::singleMutex);
		return link->hashLookup(*this, attributes);
	}

	PokerClicheShort::PokerClicheShort(const Constant *&link, const Constant *a)
		:  ClicheShort(link, &PokerHead::singleton, a)
	{
		PokerHead::singleton.retain();
	}

	const Any *PokerClicheShort::node(const Constant *element) const
	{
        return new const PokerShort(*this, element);
	}

	const NodeExpressShort *PokerClicheShort::node(const Express *element) const
	{
        return new const PokerShort(*this, element);
	}

	PokerClicheLong::PokerClicheLong(const Constant *&link, const Constant *const *a, size_t c)
		:  ClicheLong(link, &PokerHead::singleton, a, c)
	{
		PokerHead::singleton.retain();
	}

	const Any *PokerClicheLong::node(const Constant *const *element) const
	{
		return node((const Any*const *)element);
	}

	const Any *PokerClicheLong::node(const Any *const *element) const
	{
        return new ((count - 1) * sizeof(Any*)) const PokerLong(*this, element);
	}

	PokerClicheTrailer::PokerClicheTrailer(const Constant *&link, const Constant *const *a, size_t c)
		: ClicheTrailer(link, &PokerHead::singleton, a, c)
	{
		PokerHead::singleton.retain();
	}

	const Any *PokerClicheTrailer::node(const Constant *const *element) const
	{
		return node((const Any *const *)element);
	}

	const Any *PokerClicheTrailer::node(const Any *const *element) const
	{
        return new ((count - 1) * sizeof(Any*))
			const PokerTrailer(*this, element);
	}

	const Any* BindCliche::node(const Constant *const *element) const
	{
		return node((const Any*const *)element);
	}

	const Any* BindCliche::node(const Any *const *element) const
	{
        return new ((count - 1) * sizeof(Any*))
			Bind(*this, element);
	}

	const Any* BindCliche1::node(const Any *const *element) const
	{
        return new Bind1(*this, element);
	}

	const Any* BindCliche2::node(const Any *const *element) const
	{
        return new Bind2(*this, element);
	}

	const Any* BindCliche3::node(const Any *const *element) const
	{
        return new Bind3(*this, element);
	}

	const Any* JumperCliche::node(const Any *const *element) const
	{
        return new ((count - 1) * sizeof(Any*)) Jumper(*this, element);
	}

	const Any* JumperCliche1::node(const Any *const *element) const
	{
        return new Jumper1(*this, element);
	}

	const Any* JumperCliche2::node(const Any *const *element) const
	{
        return new Jumper2(*this, element);
	}

	const Any* JumperCliche3::node(const Any *const *element) const
	{
        return new Jumper3(*this, element);
	}

	NodeConstant::NodeConstant(const Constant *&link, const Cliche &c)
		: Constant(link), cliche(&c)
	{
		/* The node cliche is uncounted - most nodes are created
		   from known cliches. */
		c.retain();
	}

	const NodeConstant *NodeConstant::as_NodeConstant() const
	{
		return this;
	}

	bool NodeConstant::isNode(const Any *const *&element, const Cliche *&cliche) const
	{
		element = (const Any *const *)this->element;
		cliche = this->cliche;
		return true;
	}

	const NodeConstantShort *NodeConstantShort::hashLookup(const ClicheShort &c, const Constant* v) const
	{
		if (&c == cliche && v == element[0] && duplicateReference()) return this;
		else return hashLink->hashLookup(c, v);
	}

	const NodeConstantShort *ShortInteger::hashLookup(const ClicheShort &cliche, const Constant *value) const
	{
		return value->newSpecializeNode(hashLink, cliche);
	}

	const NodeConstantShort *Integer::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *Float::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *Timestamp::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *Duration::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *PilsDate::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *PilsString::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *ListConstant::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *Cliche::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *NodeConstant::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }
	const NodeConstantShort *Special::newSpecializeNode(const Constant *&link, const ClicheShort &cliche) const
	{ return cliche.newNode(link, this); }

	const Constant *Special::type() const
	{
        return nullptr;
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Integer *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Float *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Duration *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheShort::newNode(const Constant *&link, const Special *value) const
	{
        return new const NodeConstantShort(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Integer *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Float *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const PilsColor *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Timestamp *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Duration *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const PilsDate *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const PilsString *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Cliche *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const NodeConstant *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const ListConstant *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	const NodeConstantShort *ClicheTiny::newNode(const Constant *&link, const Special *value) const
	{
        return new const NodeConstantTiny(link, *this, value);
	}

	NodeConstantShort::NodeConstantShort(const Constant *&link, const ClicheShort &cliche, const Constant *v)
		: NodeConstant(link, cliche)
	{
		element[0] = v;
	}

	void NodeConstantShort::unduplicateChildren() const
	{
		element[0]->unduplicateReference();
	}

	const NodeConstantShort *ClicheShort::nodeConstant(const Constant *value) const
	{
		size_t hash = reinterpret_cast<size_t>(this) - 5 * reinterpret_cast<size_t>(value);
		const Constant *&link = Constant::hashChain(hash);
        Mutex::Lock lock (Mutex::singleMutex);
		return link->hashLookup(*this, value);
	}

	const NodeConstantTiny *NodeConstantTiny::as_NodeConstantTiny() const
	{
		return this;
	}

	const NodeConstantLong *NodeConstantLong::hashLookup(const ClicheLong &c, const Constant *const *v) const
	{
        if (&c == cliche && memcmp(v, &element, c.count * sizeof(Constant*)) == 0 && duplicateReference())
			return this;
		else return hashLink->hashLookup(c, v);
	}

	const NodeConstantLong *ShortInteger::hashLookup(const ClicheLong &cliche, const Constant *const *value) const
	{
		return cliche.newNodeConstant(hashLink, value);
	}

	const NodeConstantLong *ClicheLong::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
        return new ((count - 1) * sizeof(Constant*)) const NodeConstantLong(link, *this, value);
	}

	const NodeConstantLong *ClicheTrailer::newNodeConstant(const Constant *&link, const Constant *const *value) const
	{
        return new ((count - 1) * sizeof(Constant*)) const NodeConstantTrailer(link, *this, value);
	}

	NodeConstantLong::NodeConstantLong(const Constant *&link, const ClicheLong &cliche, const Constant *const *v)
		: NodeConstant(link, cliche)
	{
		for (size_t i = 0; i < cliche.count; i++)
			element[i] = v[i];
	}

	void NodeConstantLong::unduplicateChildren() const
	{
		size_t count = cliche->count;
		for (size_t i = 0; i < count; i++)
			element[i]->unduplicateReference();
	}

    NodeConstant::~NodeConstant()
	{
		size_t count = cliche->count;
        releaseChild(cliche);
		for (size_t i = 0; i < count; i++)
            releaseChild(element[i]);
	}

    const ListConstant *ListConstant::hashLookup(const Constant *const *a, size_t c, bool copying) const
	{
        if (c == (size_t)count->value && memcmp(a, &element, c * sizeof(Constant*)) == 0 && duplicateReference(copying))
			return this;
		else return hashLink->hashLookup(a, c, copying);
	}

	const ListConstant *ShortInteger::hashLookup(const Constant *const *a, size_t c, bool copying) const
	{
        return new ((c - 1) * sizeof(Constant*)) const ListConstant(hashLink, a, c, copying);
	}

	ListConstant::ListConstant(const Constant *&link, const Constant *const *a, size_t c, bool copying)
		: CountedConstant(link, c)
	{
		if (copying)
			for (size_t i = 0; i < c; i++)
				(element[i] = a[i])->retain();
		else
            memcpy(&element, a, c * sizeof(Constant*));
	}

	const ListConstant* ListConstant::get(const Constant *const *e, size_t c, bool copying)
	{
		if (c)
		{
			unsigned long hash = 7913991;
			for (size_t i = 0; i < c; i++)
			{
				hash += (unsigned long)reinterpret_cast<size_t>(e[i]);
				hash *= 19;
			}
			const Constant *&link = Constant::hashChain(hash);
            Mutex::Lock lock (Mutex::singleMutex);
			return link->hashLookup(e, c, copying);
		}
        else return Empty::get();
	}

	bool ListConstant::isList(const Any *const *&element, const Integer *&count) const
	{
		element = (const Any *const *)this->element;
		count = this->count;
		return true;
	}

	Empty::Empty()
        : ListConstant(Empty::singleton.hashLink, nullptr, 0, false)
	{}

	const ClicheShort* PokerHead::newCliche(const Constant *&link, const Constant *a) const
	{
		return
            new const PokerClicheShort(link, a);
	}

	const ClicheLong* PokerHead::newCliche(const Constant *&link, const Constant *const *a, size_t c) const
	{
        if (a[0] == &Empty::singleton)
            return new ((c - 1) * sizeof(Constant*)) const PokerClicheTrailer(link, a, c);
        else
            return new ((c - 1) * sizeof(Constant*)) const PokerClicheLong(link, a, c);
	}

	bool Any::recognize(Recognizer &recognizer) const
	{
		return false;
	}

	const ReallySpecial *ShortInteger::hashLookup(SpecialLookup &lookup) const
	{
		return lookup.newSpecial(hashLink);
	}

	const ReallySpecial *Special::hashLookup(SpecialLookup &lookup) const
	{
		if (lookup.compare((const ReallySpecial&)*this) && duplicateReference(true))
		{
			lookup.unduplicate();
			return (const ReallySpecial*)this;
		}
		else return hashLink->hashLookup(lookup);
	}

	const ReallySpecial *SpecialLookup::lookup()
	{
		size_t hash = this->hash();
        Mutex::Lock lock (Mutex::singleMutex);
		return Constant::hashTable[(hash + (hash >> 16)) & 0xFFFF].hashLink->hashLookup(*this);
	}

	void ListConstant::unduplicateChildren() const
	{
		size_t c = count->value;
		for (size_t i = 0; i < c; i++)
			element[i]->unduplicateReference();
	}

    ListConstant::~ListConstant()
	{
        size_t c = count->value;
		for (size_t i = 0; i < c; i++)
            releaseChild(element[i]);
	}

    ListExpress::ListExpress(const Any *const *e, size_t c)
		: count(Integer::get((long)c))
	{
		for (size_t i = 0; i < c; i++)
			element[i] = e[i];
	}

    ListExpress::~ListExpress()
	{
		size_t c = count->value;
        releaseChild(count);
		for (size_t i = 0; i < c; i++)
            releaseChild(element[i]);
	}

    bool ListExpress::isList(const Any *const *&element, const Integer *&count) const
	{
		element = this->element;
		count = this->count;
		return true;
	}

	NodeExpress::NodeExpress(const Cliche &cliche, const Any *const *v)
		: cliche(&cliche)
	{
		cliche.retain();
		for (size_t i = 0; i < cliche.count; i++)
			element[i] = v[i];
	}

	NodeExpress::NodeExpress(const Cliche &cliche, const Any *value)
		: cliche(&cliche)
	{
		cliche.retain();
		element[0] = value;
	}

	NodeExpress::NodeExpress(const Cliche &cliche, const Any *v1, const Any *v2)
		: cliche(&cliche)
	{
		cliche.retain();
		element[0] = v1;
		element[1] = v2;
	}

	NodeExpress::NodeExpress(const Cliche &cliche, const Any *v1, const Any *v2, const Any *v3)
		: cliche(&cliche)
	{
		cliche.retain();
		element[0] = v1;
		element[1] = v2;
		element[2] = v3;
	}

	const NodeExpress *NodeExpress::as_NodeExpress() const
	{
		return this;
	}

	bool NodeExpress::isNode(const Any *const *&element, const Cliche *&cliche) const
	{
		element = this->element;
		cliche = this->cliche;
		return true;
	}

	const CallWho *NodeExpressShort::callWho(const Any *who) const
	{
		return ((const ClicheShort*)cliche)->whoOperation(this, who);
	}

    NodeExpress::~NodeExpress()
	{
		size_t c = cliche->count;
        releaseChild(cliche);
		for (size_t i = 0; i < c; i++)
            releaseChild(element[i]);
	}

	bool NodeExpressLong::isNameValuePair(const Constant *&name, const Any *&value) const
	{
		return false;
	}

	ClicheBuilder::~ClicheBuilder()
	{
		if (alive)
		{
            head->unduplicateReference();
			if (joker)
			{
                Empty::singleton.unduplicateReference();
			}
            for (std::set<const Constant*>::iterator r = setting.begin(); r != setting.end(); r++)
			{
                (*r)->unduplicateReference();
			}
		}
	}

	bool ClicheBuilder::add(const Constant *key)
	{
		if (key == &Empty::singleton)
		{
			if (!joker)	return joker = true;
		}
		else
		{
			if (setting.insert(key).second) return true;
		}
        key->unduplicateReference();
		return false;
	}

	bool ClicheBuilder::add(const Constant &key)
	{
		if (&key == &Empty::singleton)
		{
			if (joker) return false;
			else joker = true;
		}
		else
		{
			if (!setting.insert(&key).second) return false;
		}
		key.retain();
		return true;
	}

	const Cliche *ClicheBuilder::build()
	{
		size_t count = setting.size();
		if (joker) count++;
		const Cliche *cliche;
		switch (count)
		{
		case 0:
            return nullptr;
		case 1:
			if (joker)
				cliche = head->clichefy(&Empty::singleton);
			else
			{
                std::set<const Constant*>::iterator r = setting.begin();
                cliche = head->clichefy(*r);
			}
			break;
		default:
			{
				const Constant** attributes = new const Constant*[count];
				const Constant** a = attributes;
				if (joker)
				{
					*a++ = &Empty::singleton;
				}
                for (std::set<const Constant*>::iterator r = setting.begin(); r != setting.end(); r++)
				{
                    *a++ = *r;
				}
				cliche = head->clichefy(attributes, count);
                delete[] attributes;
			}
		}
		alive = false;
		return cliche;
	}

	template <> const ListConstant *ListBuilder<const Constant, const ListConstant>::building(const Constant *const *element, size_t count)
	{
		return ListConstant::get(element, count);
	}

	template <> const Any *ListBuilder<const Any, const Any>::building(const Any *const *element, size_t count)
	{
		for (size_t i = 0; i < count; i++)
		{
            if (element[i]->as_Constant() == nullptr)
			{
                return new ((count - 1) * sizeof(Any*)) const ListExpress(element, count);
			}
		}
		return ListConstant::get((const Constant *const *)(element), count);
	}

	const Any *JumperCliche0::node(const Constant *element) const
	{
        return new Jumper0(element);
	}

	const NodeExpressShort *JumperCliche0::node(const Express *element) const
	{
        return new Jumper0(element);
	}

	void Any::unduplicateChildren() const
	{}

	bool Integer::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool Float::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool Timestamp::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool Duration::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool PilsDate::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool PilsColor::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool PilsString::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool Cliche::convert(Converter &converter) const
	{
		return converter.convert(*this);
	}
	bool Special::convert(Converter &converter) const
	{
		return converter.convert((const ReallySpecial&)*this);
	}
	bool ListConstant::convert(Converter &converter) const
	{
        return converter.convert((const Any* const *)element, count->value);
	}
	bool ListExpress::convert(Converter &converter) const
	{
		return converter.convert(element, count->value);
	}
	bool NodeConstant::convert(Converter &converter) const
	{
        return converter.convert(*cliche, (const Any* const *)element);
	}
	bool NodeExpress::convert(Converter &converter) const
	{
        return converter.convert(*cliche, element);
	}

	bool Converter::convert(const Integer &value)
	{
		return false;
	}
	bool Converter::convert(const Float &value)
	{
		return false;
	}
	bool Converter::convert(const PilsString &value)
	{
		return false;
	}
	bool Converter::convert(const Cliche &value)
	{
		return false;
	}
    bool Converter::convert(const Cliche &name, const Any *const *value)
	{
		return false;
	}
	bool Converter::convert(const Any *const *element, size_t count)
	{
		return false;
	}
	bool Converter::convert(const ReallySpecial &special)
	{
		return false;
	}
	const Any *NodeConstantTiny::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return ((const ClicheTiny*)cliche)->specialOperation(run, special, *element[0]);
	}

	const Any *NodeConstantTiny::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return ((const ClicheTiny*)cliche)->specialOperation(run, special, *element[0], assignValue);
	}

	const Any *NodeExpressTiny::specialCall(Runner &run, const ReallySpecial &special) const
	{
		return ((const ClicheTiny*) cliche)->specialOperation(run, special, *element[0]);
	}

	const Any *NodeExpressTiny::specialCall(Runner &run, const ReallySpecial &special, const Any &assignValue) const
	{
		return ((const ClicheTiny*) cliche)->specialOperation(run, special, *element[0], assignValue);
	}

	const Language *Any::as_Language() const
	{
        return nullptr;
	}

	const Any *Special::queryInterface(const InterfaceDesignator &designator) const
	{
        return nullptr;
	}
}
