/* This file is public domain */
#ifndef _JPILS_FILE_H_
#define _JPILS_FILE_H_
#include "jpils-plumming.h"

namespace PILS
{
	class FileName
		: public ReallySpecial
	{
	public:
		FileName(const HashedConstant *&link, const PilsString *name, bool isFolder)
			:  ReallySpecial(link), file(new juce::File (juce::String::fromUTF8 (name->value, name->count->value - isFolder))), name(name)
		{}
		const Any *specialCalling(Runner &run, const Constant &name) const;
		const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const;
		bool specialComparing(const FileNameLookup &lookup) const;
		bool converting(JuceSpecialConverter &converter) const;
		void write(Writing & writing) const;
		size_t unlinkAndGetSize();
	private:
		friend class FileNameConverter;
		const PilsString *name;
		const juce::File *const file;
	};

	class FileNameLookup
		: public SpecialLookup
	{
	public:
		FileNameLookup(const PilsString &name)
			: name(name), isFolder(name.value[name.count->value-1] == '/')
		{}
		const ReallySpecial *newSpecial(const HashedConstant *&link);
		bool compare(const ReallySpecial &special) const;
		void unduplicate();
		size_t hash() const;
		const PilsString &name;
		const bool isFolder;
	};

	class FileNameConverter
		: public JuceSpecialConverter
	{
	public:
		FileNameConverter()
			: name(NULL)
		{}
		const PilsString *name;
		bool converting(const FileName &argument);
	};

	class PipesourceUnzip
		: public Pipesource
	{
	public:
		PipesourceUnzip(const juce::File &file);
		const Step *pass(Runner &run, const Any *thing);
		const Step *step_(Runner &run) const;
		Sink *kick(Runner &run);
	private:
		juce::ZipFile zipFile;
		int at, count;
	};
}
#endif
