#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "uptime.h"
#include "memory.h"
#include "cpuinfo.h"
#include "kernelversion.h"
#include "timestamp.h"
#include "osinfo.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UpTime>("MyUptime", 1, 0, "UpTime");
    qmlRegisterType<Memory>("MyMemory", 1, 0, "Memory");
    qmlRegisterType<CpuInfo>("MyCpuInfo", 1, 0, "CpuInfo");
    qmlRegisterType<KernelVersion>("MyKernelVersion", 1, 0, "KernelVersion");
    qmlRegisterType<TimeStamp>("MyTimeStamp", 1, 0, "TimeStamp");
    qmlRegisterType<OSInfo>("MyOsInfo", 1, 0, "OsInfo");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
