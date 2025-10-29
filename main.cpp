#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>


int main(int argc, char *argv[])
{   
    QGuiApplication app(argc,argv);
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/gui_uri/qml/Main.qml")));
    QQmlContext *rootContext = engine.rootContext();

    return app.exec();
}


