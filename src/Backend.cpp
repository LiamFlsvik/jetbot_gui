#include "Backend.hpp"
#include <QDebug>


Backend::Backend(QObject* parent) : QObject(parent) {}
Backend::~Backend(){
    
}
void Backend::setMode(bool mode) {
    if (mode != manual_mode_) {
        manual_mode_ = mode;
        qDebug() << "C++: Manual mode set to:" << mode;
        emit modeChanged(mode);
    }
}

void Backend::setIP(std::string ip){
    if(ip_address_ !=ip){
        ip_address_ = ip;
    
        qDebug() << "C++: IP set to:" << ip;
        emit ipChanged();
    }
}

void Backend::setSpeed(float speed){
    speed_ = speed;
    qDebug() << "C++: Speed:" << speed;
    emit speedChanged();
    
}

float Backend::getSpeed(){
    return speed_;
}

QString Backend::getIP() const {
    return QString::fromStdString(ip_address_);
}

