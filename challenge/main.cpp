#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "triangle.h"
#include <QQmlContext>
#include "linuxcpuinfo.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Register Custom QML-Types
    qmlRegisterType<Triangle>("ChallengeLib",1,0,"MyTriangle");

    //Create QML-Engine
    QQmlApplicationEngine engine;
    //Create cpu-info access
    linuxCpuInfo* info=new linuxCpuInfo(&app);
    info->initialize();

    //Register Global Content-Propertys fpr QML
    engine.rootContext()->setContextProperty("_myCpuInfo",info);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
