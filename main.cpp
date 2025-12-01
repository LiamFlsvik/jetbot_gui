#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Backend.hpp>
#include <cstring>
#include <qobject.h>
#include <QThread>
#include <string>
#include "include/JetBot.hpp"

#include "VideoProvider.hpp"

int main(int argc, char *argv[])
{   
    glfwInit();
    QGuiApplication app(argc,argv);
    QQmlApplicationEngine engine;   
    JetBot jetbot("10.22.140.237",8080,false,nullptr);
    QThread jetbot_thread;
    jetbot.moveToThread(&jetbot_thread);

    QObject::connect(&jetbot_thread, &QThread::started, &jetbot,&JetBot::run);

    jetbot_thread.start();

    VideoProvider video_provider;

    QObject::connect(&jetbot,&JetBot::frame_changed,&video_provider,&VideoProvider::updateFrame);
    engine.addImageProvider("videoprovider", &video_provider);

    Backend backend;
    engine.rootContext()->setContextProperty("backend",&backend);
    
    engine.load(QUrl(QStringLiteral("qrc:/gui_uri/qml/Main.qml")));
    QQmlContext *rootContext = engine.rootContext();
    //tcp_client_thread.start();



    return app.exec();
    
}


