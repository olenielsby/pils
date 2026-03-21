/* This file is public domain */
#include "qpils-file.h"
#include "qpils-standard-specials.h"

namespace PILS
{
	const Any *Plumcake::specialCalling(Runner &run, const Constant &name) const
	{
		return NULL;
	}

	const Any *Plumcake::specialCalling(Runner &run, const Constant &name, const Any &arg) const
	{
		if (run.isMainThread() && (&name == &Builtin::name.file || &name == &Builtin::name.folder))
		{
			const PilsString *fileName = arg.as_String();
			if (fileName && fileName->count->value && (fileName->value[fileName->count->value - 1] == '/') == (&name == &Builtin::name.folder))
			{
				return FileNameLookup(*fileName).lookup();
			}
		}
		return NULL;
	}

	bool FileNameLookup::compare(const ReallySpecial &special) const
	{
		return special.specialComparing(*this);
	}

	void FileNameLookup::unduplicate()
	{}

	size_t FileNameLookup::hash() const
	{
		return reinterpret_cast<size_t>(&name);
	}

	const ReallySpecial *FileNameLookup::newSpecial(const HashedConstant *&link)
	{
		name.addReference();
        return new const FileName(link, &name, isFolder);
	}

	void FileName::write(Writing & writing) const
	{
		writing.write(name->value, name->count->value);
	}

	size_t FileName::unlinkAndGetSize()
	{
		unhash();
		if (when) when->releaseFrom(*this);
		name->releaseFrom(*this);
        delete file;
		return sizeof(FileName);
	}

	const Any *FileName::specialCalling(Runner &run, const Constant &method) const
	{
        // this->writeToDebugOutput(5);
        // method.writeToDebugOutput(5);
        // name->writeToDebugOutput(5);
        if (!run.isMainThread()) return nullptr;
        else if (&method == &Builtin::name.name_)
		{
			name->addReference();
			return name;
		}
        else if (name->count->value == 0) return nullptr;
		else if (name->value[name->count->value - 1] == '/') //folder name
        {
            QDir dir(file->absoluteFilePath());

            QStringList results = dir.entryList(
                (&method == &Builtin::name.files ? QDir::Files : QDir::Dirs)
                | QDir::NoDotAndDotDot
                );

            int count = results.size();

            if (!count)
            {
                Empty::singleton.addReference();
                return &Empty::singleton;
            }
            std::vector<const Constant *> items(count);

            for (int i = 0; i < count; ++i)
            {
                QString path =
                    QDir::fromNativeSeparators(dir.absoluteFilePath(results[i]));

                if (&method == &Builtin::name.folders)
                    path += '/';

                QByteArray utf8 = path.toUtf8();

                const PilsString *pilsName =
                    PilsString::get(utf8.constData(), utf8.size());

                items[i] = FileNameLookup(*pilsName).lookup();

                pilsName->unduplicateReference();
            }

            return ListConstant::get(items.data(), items.size());
        }
        else if(
            (&method == &Builtin::name.ok && file->isDir())
            || (&method == &Builtin::name.delete_ && file->isDir() && QDir(file->absoluteFilePath()).removeRecursively())
            || (&method == &Builtin::name.create && !file->isDir() && QDir().mkpath(file->absoluteFilePath()))
            )
        {
            addReference();
            return this;
        }
		else if(&method == &Builtin::name.text)
		{
            QFile f(file->absoluteFilePath());

            if (!f.open(QIODevice::ReadOnly))
                return nullptr;

            QByteArray data = f.readAll();
            return PilsString::get(data.constData(), data.size());
        }
        if (!file->isFile())
            return nullptr;

        if (&method == &Builtin::name.ok)
        {
            addReference();
            return this;
        }
        else if (&method == &Builtin::name.timestamp)
        {
            return pils(file->lastModified());
        }
        else if (&method == &Builtin::name.count_)
        {
            return Number::get((double)file->size());
        }
        else if (&method == &Builtin::name.readable)
        {
            return Integer::get(file->isReadable());
        }
        else if (&method == &Builtin::name.writable)
        {
            return Integer::get(file->isWritable());
        }
        else if (&method == &Builtin::name.delete_)
        {
            return Integer::get(QFile::remove(file->absoluteFilePath()));
        }
		return NULL;
	}

    const Any *FileName::specialCalling(Runner &run, const Constant &method, const Any &arg) const
    {
        if (!run.isMainThread()) return nullptr;
        if (name->count->value == 0 || name->value[name->count->value - 1] == '/') return nullptr;

        QString path = QString::fromUtf8(name->value, name->count->value);
        QFile file(path);

        // Write text string to file
        if (&method == &Builtin::name.text)
        {
            const PilsString *string = arg.as_String();
            if (string)
            {
                QFile f(path);
                if (f.open(QIODevice::WriteOnly))
                {
                    f.write(string->value, string->count->value);
                    f.close();
                    addReference();
                    return this;
                }
            }
        }
        else if (&method == &Builtin::name.move)
        {
            if (!file.exists()) return nullptr;

            if (const PilsString *string = arg.as_String())
            {
                QString newName = QString::fromUtf8(string->value, string->count->value);
                if (file.rename(newName))
                {
                    return FileNameLookup(*string).lookup();
                }
            }
        }
        else if (&method == &Builtin::name.copy)
        {
            if (!file.exists()) return nullptr;

            if (const PilsString *string = arg.as_String())
            {
                QString newName = QString::fromUtf8(string->value, string->count->value);
                if (QFile::copy(path, newName))
                {
                    return FileNameLookup(*string).lookup();
                }
            }
        }
        else if (&method == &Builtin::name.timestamp)
        {
            if (const Timestamp *timestamp = arg.as_Timestamp())
            {
                if (file.exists())
                {
                    QFile f(path);
                    if (f.open(QIODevice::ReadWrite))
                    {
                        f.setFileTime(
                            QDateTime::fromMSecsSinceEpoch(timestamp->value),
                            QFileDevice::FileModificationTime
                            );
                        addReference();
                        return this;
                    }
                }
            }
        }

        return nullptr;
    }
	bool FileName::specialComparing(const FileNameLookup &lookup) const
	{
		return name == &lookup.name;
	}

    bool FileName::converting(QtSpecialConverter &converter) const
	{
		return converter.converting(*this);
	}

	const Any *QuickFetchFileName::specialAttribute(const Special &value) const
	{
		FileNameConverter converter;
        if (value.convert(converter) && converter.name->count != 0 && converter.name->value[converter.name->count->value - 1] != '/')
			return converter.name;
		else return NULL;
	}

	const Any *QuickFetchFolderName::specialAttribute(const Special &value) const
	{
		FileNameConverter converter;
        if (value.convert(converter) && converter.name->count != 0 && converter.name->value[converter.name->count->value - 1] == '/')
			return converter.name;
		else return NULL;
	}

	bool FileNameConverter::converting(const FileName &argument)
	{
		name = argument.name;
		return true;
	}

    // PipesourceUnzip::PipesourceUnzip(const juce::File &file)
    // 	: zipFile(file), at(0)
    // {
    // 	count = zipFile.getNumEntries();
    // }

    // Sink *PipesourceUnzip::kick(Runner &run)
    // {
    // 	zipFile.~ZipFile();
    // 	return this + 1;
    // }

    // const Step *PipesourceUnzip::pass(Runner &run, const PILS::Any *thing)
    // {
    // 	thing->releaseReference();
    // 	return ((Pipe &)this[1]).pipeBegin(run);
    // }

    // const Step *PipesourceUnzip::step_(Runner &run) const
    // {
    // 	PipesourceUnzip *this_ = const_cast<PipesourceUnzip*>(this);
    // 	Pipe &pipe = (Pipe &)this[1];
    // 	if (count == at)
    // 	{
    // 		run.sink = this_->kick(run);
    // 		return pipe.pipeEnd(run);
    // 	}
    // 	else
    // 	{
 //            const juce::ZipFile::ZipEntry *entry = zipFile.getEntry(at);
    // 		const Constant *elements[3];
    // 		elements[0] = pils(entry->filename.replaceCharacter('\\', '/'));
    // 		elements[2] = pils(entry->fileTime);
 //            juce::MemoryBlock data;
 //            juce::InputStream *stream = this_->zipFile.createStreamForEntry(this_->at++);
    // 		stream->readIntoMemoryBlock(data);
    // 		delete stream;
    // 		elements[1] = PilsString::get((char *)data.getData(), data.getSize());
    // 		return pipe.pipeItem(run, ListConstant::get(elements, 3));
    // 	}
    // }
}
