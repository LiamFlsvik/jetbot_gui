#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <Backend.hpp>
#include <cstring>
#include <qobject.h>
#include <QThread>
#include <string>
#include "TCPClient.hpp"
#include "VideoProvider.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc,argv);
    QQmlApplicationEngine engine;   
 
    TCPClient tcp_client("127.0.0.1",8080);
    VideoProvider video_provider;
    QThread tcp_client_thread;

    tcp_client.moveToThread(&tcp_client_thread);

    QObject::connect(&tcp_client_thread,&QThread::started, &tcp_client, &TCPClient::run);

    QObject::connect(&tcp_client,&TCPClient::frameChanged,&video_provider,&VideoProvider::updateFrame);
    engine.addImageProvider("videoprovider", &video_provider);

    Backend backend;
    engine.rootContext()->setContextProperty("backend",&backend);
    
    engine.load(QUrl(QStringLiteral("qrc:/gui_uri/qml/Main.qml")));
    QQmlContext *rootContext = engine.rootContext();
    tcp_client_thread.start();

    return app.exec();
    
}


