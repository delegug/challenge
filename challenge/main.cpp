#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "triangle.h"
#include <QQmlContext>
#include "linuxcpuinfo.h"
#include <QMessageBox>
#include "cpuinfomodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Register Custom QML-Types
    qmlRegisterType<Triangle>("ChallengeLib",1,0,"MyTriangle");
    qmlRegisterType<qmlCpuInfoItem>("ChallengeLib",1,0,"MyCpuInfoModelItem");
    qmlRegisterType<qmlCpuInfoModelContainer>("ChallengeLib",1,0,"MyCpuInfoModel");
    qmlRegisterUncreatableType<myNamespace>("ChallengeLib",1,0,"MyNamespace","Contains the enum values of the program");

    //Create QML-Engine
    QQmlApplicationEngine engine;
    //Create cpu-info access
    linuxCpuInfo* info=new linuxCpuInfo(&app);
    if (!info->initialize()) {
        //TODO SHOW ERRORMESSAGE
        //QScopedPointer<QMessageBox> msgBox(new QMessageBox(QMessageBox::Critical,"Error",info->trErrorText()));
        //msgBox->exec();
        //return 0;
    }

    //Register Global Content-Propertys fpr QML
    engine.rootContext()->setContextProperty("_myCpuInfo",info);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
