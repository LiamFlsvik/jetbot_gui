#include "Backend.hpp"
#include <QDebug>
#include <qcontainerfwd.h>

Backend::Backend(QObject* parent) : QObject(parent) {}
Backend::~Backend(){}

void Backend::setMode(bool mode) {
    if (mode == mode_){return;}
    mode_ = mode;
    emit modeChanged(mode);
    qDebug() << "C++: Manual mode set to:" << mode;
}

void Backend::setIP(const QString ipAddress){
    if(ip_address_ == ipAddress.toStdString()){return;}
    ip_address_ = ipAddress.toStdString();
    emit ipChanged(QString::fromStdString(ip_address_));
    qDebug() << "C++: IP set to:" << ipAddress;
}

void Backend::setSpeed(const float speed){
    if(speed == speed_){return;}
    speed_ = speed;
    qDebug() << "C++: Speed:" << speed;
    emit speedChanged(speed_);
}

void Backend::setDetectionMode(const QString detectionMode){
    if(detection_mode_ == detectionMode.toStdString()){return;}
    detection_mode_ = detectionMode.toStdString();
    emit detectionModeChanged(QString::fromStdString(detection_mode_));
    qDebug() << "C++: D set to:" << QString::fromStdString(detection_mode_);
}

void Backend::updateReceivedData(const JetBotMessages::Receive data){
    if(!data.position.empty()){
        //data
    }
}


float Backend::getSpeed() const {
    return speed_;
}

QString Backend::getIP() const {
    return QString::fromStdString(ip_address_);
}

bool Backend::getMode() const{
    return mode_;
}

int Backend::getBatteryPercentage() const{
    return battery_percentage_;
}

QString Backend::getDetectionMode() const{
    return QString::fromStdString(detection_mode_);
}

void Backend::updateControlCommands(){
    std::lock_guard<std::mutex> lock(get_control_commands_mutex);

}

const JetBotMessages::ControlCommand Backend::getControlCommands(){
    std::lock_guard<std::mutex> lock(get_control_commands_mutex);
    return control_command_;

}




