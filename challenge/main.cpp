#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "linuxcpuinfo.h"
#include <QMessageBox>
#include "cpuinfomodel.h"
#include "logfile.h"

/// Message Handler
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context)
    //write debug/warning/critical/fatal message in logfile
    QScopedPointer<logfile> log(new logfile("log"));
    switch (type) {
    case QtDebugMsg:
        log->writeLogFile(QString("Debug: %1").arg(msg));
        break;
    case QtInfoMsg:
        log->writeLogFile(QString("Info: %1").arg(msg));
        break;
    case QtWarningMsg:
        log->writeLogFile(QString("Warning: %1").arg(msg));
        break;
    case QtCriticalMsg:
        log->writeLogFile(QString("Critical: %1").arg(msg));
        break;
    case QtFatalMsg:
        log->writeLogFile(QString("Critical: %1").arg(msg));
        abort();
    }
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //Install Message Handler
    qInstallMessageHandler(myMessageOutput);
    //Install Translator for Locale Language
    QTranslator translator;
    if (translator.load(QLocale(), QLatin1String("challenge"), QLatin1String("_"),
                        QString(QDir::currentPath() + QDir::separator() + "translations"))) {
        app.installTranslator(&translator);
    }

    //Register Custom QML-Types
    qmlRegisterType<qmlCpuInfoItem>("ChallengeLib",1,0,"MyCpuInfoModelItem");
    qmlRegisterType<qmlCpuInfoModelContainer>("ChallengeLib",1,0,"MyCpuInfoModel");
    qmlRegisterUncreatableType<myNamespace>("ChallengeLib",1,0,"MyNamespace","Contains the enum values of the program");

    //Create QML-Engine
    QQmlApplicationEngine engine;
    //Create cpu-info access
    linuxCpuInfo* info=new linuxCpuInfo(&app);
    if (!info->initialize()) {
        //TODO SHOW ERRORMESSAGE IN QML (NOT WIDGET BASED)
        //QScopedPointer<QMessageBox> msgBox(new QMessageBox(QMessageBox::Critical,"Error",info->trErrorText()));
        //msgBox->exec();
        //return 0;
    }

    //Register Global Content-Propertys fpr QML
    engine.rootContext()->setContextProperty("_myCpuInfo",info);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}


