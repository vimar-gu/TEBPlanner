#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include <QWaitCondition>
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

    QObject* root = engine.rootObjects().first();
    QObject* obs1 = root->findChild<QObject*>("obs1");
    if (obs1) {
        QVariant returnVar;
        QMetaObject::invokeMethod(obs1, "x", Q_RETURN_ARG(QVariant, returnVar));
        qDebug() << returnVar.toString().toLocal8Bit().data() << endl;
    }

    return app.exec();
}
