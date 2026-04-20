/* This file is public domain */
#include <QStandardPaths>
#include <QGuiApplication>
#include <QCoreApplication>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>


#include "pipe.h"
#include "statement.h"
#include "qpils_commander.h"

const PILS::PilsString *pils_configuration_get_user_language();

namespace PILS
{
	class ConfigurationBuilder
		: private NodeBuilder<const Constant>
	{
	public:
        void set(const PILS_CHAR *name, QStandardPaths::StandardLocation location)
        {
            QString string = QStandardPaths::writableLocation(location);
            // Qt bruger allerede '/' internt, men vi sikrer det
            string.replace('\\', '/');

            QFileInfo file(string);

            if (file.isDir() && !string.endsWith('/'))
                string += '/';

            aim(PilsString::get(name));
            QByteArray utf8 = string.toUtf8();
            NodeBuilder<const Constant>::set(
                PilsString::get(utf8.constData(), utf8.size()));
        }
		void set(const PILS_CHAR *name, const PILS_CHAR *value)
		{
			aim(PilsString::get(name));
			NodeBuilder<const Constant>::set(PilsString::get(value));
		}
		void set(const PILS_CHAR *name, const PilsString *value)
		{
			aim(PilsString::get(name));
			NodeBuilder<const Constant>::set(value);
		}
		const NodeConstant *build()
		{
			return (const NodeConstant*) NodeBuilder<const Constant>::build();
		}
		ConfigurationBuilder()
			: NodeBuilder<const Constant>(&Builtin::name.minus)
		{
			Builtin::name.minus.retain();
		}
	};
    PilsCommander::PilsCommander(const std::string efn) : exeFileName(efn)
    {
        assert(MainThread::singleton == nullptr);
        MainThread::singleton = new MainThread(QThread::currentThread());
        commandLineHandler = getCommandLineHandler();
    }

    bool PilsCommander::executeCommandLine(const std::vector<std::string> &args)
    {
        Runner &runner = *MainThread::singleton;
        const Any *cmd = nullptr;
        runner.where_ = commandLineHandler;
        commandLineHandler->retain();

        std::vector<const Constant*> arglist;

        for (const std::string &arg : args)
        {
            arglist.push_back(PilsString::get(arg));
        }

        cmd = ListConstant::get(arglist.data(), arglist.size())->callHere();

        {
            // MainThread::RunLevel runlevel;
            runner.run(cmd);
            cmd->release();
            runner.where_->release();
        }

        return QGuiApplication::topLevelWindows().size() != 0;
    }

	void PilsCommander::addNamespace(NodeBuilder<const Constant> &gloss, const char *prefix, const char *identifier)
	{
		gloss.aim(PilsString::get(prefix));
		const ClicheTiny *cliche = PilsString::get(identifier)->clichefy();
        gloss.set(cliche->nodeConstant(Empty::get()));
		cliche->unduplicateReference();
	}

    static std::string executableBaseName(const std::string& path)
    {
        // fjern path
        size_t pos = path.find_last_of('/');
        std::string name = (pos == std::string::npos)
                               ? path
                               : path.substr(pos + 1);

        // fjern extension
        size_t dot = name.find_last_of('.');
        if (dot != std::string::npos)
            name = name.substr(0, dot);

        return name;
    }

    const Any *PilsCommander::getCommandLineHandler()
    {
        const Any *commandLineHandler = nullptr;

        // Heap::useStandardAllocator();

        const Language *language;

        {
            NodeBuilder<const Constant> gloss(PilsString::get(_PS("system")));

            gloss.aim(Empty::get());
            gloss.set(PilsString::get(_PS("\1.")));

            // Add standard namespace
            addNamespace(gloss, "system", "pils.org/ns/sne");
            // addNamespace(gloss, "graph", "pils.org/ns/graph");
            // addNamespace(gloss, "font", "pils.org/ns/font/normal");
            // addNamespace(gloss, "italic", "pils.org/ns/font/italic");
            // addNamespace(gloss, "bold", "pils.org/ns/font/bold");
            // addNamespace(gloss, "bold-italic", "pils.org/ns/font/bold-italic");

            // Add system information namespace
            gloss.aim(PilsString::get(_PS("pils-configuration")));

            ConfigurationBuilder config;

            config.set(_PS("platform"), _PS("qt"));
            config.set(_PS("platform-version"), _PS(QT_VERSION_STR));
            config.set(_PS("application-type"), _PS("desktop"));

#if defined(Q_OS_WIN)
            config.set(_PS("system"), _PS("win32"));
            config.set(_PS("plugtype"), _PS("dll"));
#elif defined(Q_OS_LINUX)
            config.set(_PS("system"), _PS("linux"));
            config.set(_PS("plugtype"), _PS("so"));
#elif defined(Q_OS_MACOS)
            config.set(_PS("system"), _PS("macos"));
            config.set(_PS("plugtype"), _PS("dylib"));
#endif

            config.set(_PS("compile-date"), _PS(__DATE__) _PS(" ") _PS(__TIME__));

#ifdef QT_DEBUG
            config.set(_PS("compile-mode"), _PS("debug"));
#else
            config.set(_PS("compile-mode"), _PS("release"));
#endif

            // executable filename
            config.set(_PS("executable-filename"),
                       PilsString::get(exeFileName));

            // open command
            config.set(_PS("open-command"),
                       PilsString::get(exeFileName));

            // configuration directory
            QString configDir =
                QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

            config.set(_PS("configuration-directory"),
                       PilsString::get(QDir::fromNativeSeparators(configDir)
                                           .toUtf8().toStdString()));

            // documents directory
            QString docsDir =
                QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

            config.set(_PS("documents-directory"),
                       PilsString::get(QDir::fromNativeSeparators(docsDir)
                                           .toUtf8().toStdString()));

            config.set(_PS("language"), pils_configuration_get_user_language());

            // pils filetype (basename of executable)

            config.set(_PS("pils-filetype"), PilsString::get(executableBaseName(exeFileName)));

            gloss.set(config.build());

            language =
                (const Language*)BuiltinClicheLanguage::singleton.nodeConstant(
                    (Constant*)gloss.build());
        }
        assert(MainThread::singleton != nullptr);

        Runner &runner = *MainThread::singleton;
        runner.where_ = Plum::cake();

        const PilsString *teststring = PilsString::get(bootExpression);

        const Any *test =
            BuiltinClicheRead::singleton.node(teststring)->callWho(language);

        try
        {
            runner.run(test);

            test->release();
            test = runner.where_;

            (runner.where_ = PILS::Plum::cake())->retain();

            runner.run(test);

            commandLineHandler = runner.where_;

            test->release();
        }
        catch (const wchar_t *msg)
        {
            qDebug().noquote() << QString::fromWCharArray(msg);
        }

        // MainThread::singleton->doPending();

        return commandLineHandler;
    }

    void SinkBug::bug(Runner &run, const PilsString &bug)
    {
        QString string = QString::fromUtf8(bug.value, bug.count->value);
        qDebug().noquote() << string;
    }
}
