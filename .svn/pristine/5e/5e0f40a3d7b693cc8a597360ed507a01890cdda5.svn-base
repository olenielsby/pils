/* This file is public domain */
#ifndef DEFINE_PILS_WRITING_H
#define DEFINE_PILS_WRITING_H
#include "escape.h"
#include "pilsstring.h"
#include "language.h"
namespace PILS
{
	class Writing
	{
	public:
        virtual ~Writing(){}
		virtual void write(const PILS_CHAR *cc, size_t count) = 0;
		virtual void write(const PILS_CHAR *cc) = 0;
		virtual void write(const PILS_CHAR c) = 0;
		virtual bool overflow() const;
		virtual void writeSpaceOrBreak() = 0;
		virtual void optionalSpace() {};
		virtual void optionalSpaceOrBreak() {};
		virtual void done() {};
		void write(size_t n);
		void write(size_t n, size_t count);
		void write(long long n);
		bool write(const Any *thing, WriteState state, long level, const Constant *dot);
		Runner &run;
		const Language *const language;
		enum Spacing
		{
			tight,
			space,
			colon,
			dot,
			rule
		};
		Spacing spacing;
		void spaceElement();
		void spaceColon();
		void spaceDot();
		void spaceString();
		void spaceRule();
		std::map<const Any *, int> labels;
		int labelCount;
		bool labeling(const Any *thing);
		int level, flatLevel;
		const Constant *lastName;
	protected:
		Writing(Runner &run, const Language *language, const Any *thing);
	};

	class WritingString
		: public Writing
	{
	public:
		WritingString(Runner &run, const Language *language, const Any *thing)
			: Writing(run, language, thing)
		{}
		void write(const PILS_CHAR c);
		void write(const PILS_CHAR *cc);
		void write(const PILS_CHAR *cc, size_t count);
		void writeSpaceOrBreak();
		virtual const PilsString *getString() const;
	protected:
		std::string buffer;
	};

	class WritingProbe
		: public Writing
	{
	public:
		WritingProbe(Runner &run, const Language *language, const Any *thing, size_t limit)
			: Writing(run, language, thing), limit(limit), count(0)
		{}
		void write(const PILS_CHAR c);
		void write(const PILS_CHAR *cc);
		void write(const PILS_CHAR *cc, size_t count);
		void writeSpaceOrBreak();
		bool overflow() const;
		virtual size_t getCount() const {return count;}
	protected:
		size_t limit;
		size_t count;
	};

	class IndentHand
	{
	protected:
		void tap(size_t at, size_t level, size_t flatLevel);
		static const int indentSpacing = 2;
		IndentHand() : breakLevel(0), brokeAt(0) {};
	private:
		struct Finger {size_t at, level, indent;};
		static const size_t maxMeaningfulChars = 20;
		friend class WritingIndentProbe;
		std::vector<Finger> hand;
		size_t breakLevel;
		size_t brokeAt;
		virtual int indenting(size_t at, size_t indent) = 0;
	};

	class WritingIndentString
		: public WritingString, private IndentHand
	{
	public:
		WritingIndentString(Runner &run, const Language *language, const Any *thing)
			: WritingString(run, language, thing)
		{}
		void writeSpaceOrBreak();
		void done();
		int indenting(size_t at, size_t level);
		void optionalSpace();
		void optionalSpaceOrBreak();
	};

	class WritingIndentProbe
		: public WritingProbe, private IndentHand
	{
	public:
		WritingIndentProbe(Runner &run, const Language *language, const Any *thing, size_t limit)
			: WritingProbe(run, language, thing, limit)
		{}
		void writeSpaceOrBreak();
		void done();
		int indenting(size_t at, size_t level);
		void optionalSpace();
		void optionalSpaceOrBreak();
	};
}
#endif
