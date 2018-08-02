#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Field.h"

void qmlRegister() {
    qmlRegisterType<Field>("Client.Component", 2, 0, "Field");
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegister();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:src/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
