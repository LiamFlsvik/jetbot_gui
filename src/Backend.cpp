#include "Backend.hpp"
#include <QDebug>

Backend::Backend(QObject* parent) : QObject(parent) {}
Backend::~Backend(){
    
}
void Backend::callMe() {
    qDebug() << "Test";
}


