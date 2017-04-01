#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "triangle.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //Register Custom QML-Types
    qmlRegisterType<Triangle>("ChallengeLib",1,0,"MyTriangle");


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
