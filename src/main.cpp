#include <QApplication>
#include <QLocalServer>
#include <QLocalSocket>
#include <QDataStream>
#include <QCryptographicHash>
#include <QDir>
#include <QDebug>
#include "qpils/qpils-commander.h"

static QString makeServerName()
{
    QByteArray exe =
        QCoreApplication::applicationFilePath().toUtf8();

    QByteArray hash =
        QCryptographicHash::hash(exe, QCryptographicHash::Sha1);

    return QString("pils-%1").arg(QString(hash.toHex()));
}

static bool sendArgsToRunningInstance(const QString& serverName)
{
    QLocalSocket socket;

    socket.connectToServer(serverName);

    if (!socket.waitForConnected(50))
        return false;

    QDataStream stream(&socket);
    stream << QCoreApplication::arguments();

    socket.flush();
    socket.waitForBytesWritten();

    return true;
}

static std::string qtPathToStd(const QString& path)
{
    QString norm = QDir::fromNativeSeparators(path);
    QByteArray utf8 = norm.toUtf8();
    return std::string(utf8.constData(), utf8.size());
}

static std::vector<std::string> qtArgsToStd(const QStringList& args)
{
    std::vector<std::string> result;
    result.reserve(args.size());

    for (const QString& s : args)
        result.emplace_back(s.toUtf8().constData());

    return result;
}

class CommandLineServer : public QObject
{
public:
    CommandLineServer(const QString& name, PILS::PilsCommander& commander)
        : commander_(commander)
    {
        server_.listen(name);

        connect(&server_, &QLocalServer::newConnection,
                this, &CommandLineServer::handleConnection);
    }

private:
    void handleConnection()
    {
        QLocalSocket* socket = server_.nextPendingConnection();

        socket->waitForReadyRead();

        QDataStream stream(socket);

        QStringList args;
        stream >> args;

        commander_.executeCommandLine(qtArgsToStd(args));

        socket->disconnectFromServer();
    }

    QLocalServer server_;
    PILS::PilsCommander& commander_;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QString serverName = makeServerName();

    if (sendArgsToRunningInstance(serverName))
        return 0;

    QObject::connect(qApp, &QGuiApplication::lastWindowClosed,
                     []()
                     {
                         QCoreApplication::quit();
                     });

    PILS::PilsCommander commander(qtPathToStd(QCoreApplication::applicationFilePath()));

    // kør første commandline
    commander.executeCommandLine(qtArgsToStd(QCoreApplication::arguments()));

    // start IPC server
    CommandLineServer server(serverName, commander);

    int result = app.exec();

#ifdef PILS_DEBUG
    pilsMemoryLeakCheck();
#endif

    return result;
}
