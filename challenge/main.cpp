/** @file main.cpp
* @brief mainfile of the project.
*

* @mainpage
*
*
* @section intro_sec Introduction
*
* @version 1.0.0
* @date 05.04.2017
* @author M. Gugenhan
*
* Challenge is a program which displays the data of the file '/proc/cpuinfo' on a linux machine
* The program has a @ref cpp for reading and preparing the data, a @ref qml for the visualization of the data
*
*
* @page cpp C++ Part
* @brief Description of the C++-Part
*
* The C++-Part contains of two different parts, a part for reading the cpu-information and a part to create a model out of this information.
*
* @section reading Reading the cpu information
* The classes for reading the cpu are @ref cpuInfoBase and @ref linuxCpuInfo. The abstract base class can be derived to add a new cpuInfo for another system, for example windows.
*
* @section model Datamodel of the cpu information
* The dataModel is the interface between the cpu information classes and the qml part. The classes which provide the model are @ref qmlCpuInfoItem, @ref cpuInfoModel and @ref qmlCpuInfoModelContainer
*
*
*
* @page qml Qml Part
* @brief Visualization of the data with Qml
*
* there are following qml files in the program, the main.qml which is the Application Window of the qml application.
* the MyText.qml is a Text-Element for all texts in the application. ProcessorItem.qml displays the data of a processor and
* contains the ProcessorModel.qml, which is the interface to the c++ @ref cpuInfoModel model.
*
* the ProcessorSelector.qml displays the different processors of the system and allows the user to select one, which is displayed in the processorItem.
* there is a global variable '_myCpuInfo' which has a access to the cpuInfoBase-Object of the program.
*
*
*
*/



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


