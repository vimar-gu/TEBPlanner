#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QWaitCondition>
#include "Interaction.h"
#include "Field.h"
#include "World.h"

void qmlRegister() {
    qmlRegisterType<Interaction>("Client.Component", 2, 0, "Interaction");
    qmlRegisterType<Field>("Client.Component", 2, 0, "Field");
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegister();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:src/qml/main.qml")));

    return app.exec();
}
