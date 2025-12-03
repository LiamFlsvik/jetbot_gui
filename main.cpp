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

    JetBot jetbot(2468,44444,44445,true,nullptr);
    
    VideoProvider video_provider;
    QThread jetbot_thread;
    Backend backend;

    jetbot.moveToThread(&jetbot_thread);
    jetbot_thread.start();

    QObject::connect(&jetbot_thread, &QThread::started, &jetbot,&JetBot::run);
    QObject::connect(&jetbot,&JetBot::gui_display_data_changed,&backend,&Backend::setDisplayData);
    
    QObject::connect(&jetbot,&JetBot::frame_changed_fpv,&video_provider,&VideoProvider::updateFrame);
    engine.addImageProvider("videoprovider", &video_provider);

    engine.rootContext()->setContextProperty("backend",&backend);
    
    engine.load(QUrl(QStringLiteral("qrc:/gui_uri/qml/Main.qml")));
    QQmlContext *rootContext = engine.rootContext();
    //tcp_client_thread.start();



    return app.exec();
    
}


