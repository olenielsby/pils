/* This file is public domain */
#pragma once
#include "qpils_plumming.h"
#include <QDir>
#include <QFileInfo>

namespace PILS
{
	class FileName
		: public ReallySpecial
	{
	public:
        FileName(const Constant *&link, const PilsString *name, bool isFolder)
            :   ReallySpecial(link), name(name), isFolder(isFolder), file(new QFileInfo(QString::fromUtf8(name->value, name->count->value)))
		{}
        const Any *specialCalling(Runner &run, const Constant &name) const override;
        const Any *specialCalling(Runner &run, const Constant &name, const Any &arg) const override;
        bool specialComparing(const FileNameLookup &lookup) const override;
        bool converting(PlatformSpecificConverter &converter) const override;
        void write(Writing & writing) const override;
        ~FileName();
    private:
		const PilsString *name;
        bool isFolder;
        const QFileInfo *const file;
	};

	class FileNameLookup
		: public SpecialLookup
	{
	public:
		FileNameLookup(const PilsString &name)
            : name(name), isFolder(name.count->value > 0 && name.value[name.count->value-1] == '/')
		{}
        const ReallySpecial *newSpecial(const Constant *&link) override;
        bool compare(const ReallySpecial &special) const override;
        void unduplicate() override;
        size_t hash() const override;
		const PilsString &name;
		const bool isFolder;
	};
}
