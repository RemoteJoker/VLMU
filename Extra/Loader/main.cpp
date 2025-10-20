#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "loadservice.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    // 创建登陆器服务
    LoadService g_load_service;
    QQmlApplicationEngine g_engine;
    g_engine.rootContext()->setContextProperty("g_load_service", &g_load_service);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&g_engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    g_engine.load(url);
    return app.exec();
}
