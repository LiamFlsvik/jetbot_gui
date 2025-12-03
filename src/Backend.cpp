#include "Backend.hpp"
#include <QDebug>

Backend::Backend(QObject* parent) : QObject(parent) {}
Backend::~Backend(){}


GUI::ControlData Backend::getControlData(){
    std::unique_lock<std::mutex> lock(control_data_mutex_);
    //TODO: Remove printstatements
    qDebug() << "Manual mode set to:" << control_data_.manual_mode;
    qDebug() << "Detection mode set to:" << control_data_.detection_mode;
    qDebug() << "Desired speed set to:" << control_data_.desired_speed;

    return control_data_;
    
};

void Backend::setMode(bool mode) {
    bool modified = false;
    {
        std::unique_lock<std::mutex> lock(control_data_mutex_);
        if (control_data_.manual_mode == mode){return;}
        control_data_.manual_mode = mode;
        modified = true;
    }
    if(modified){
        emit controlDataChanged();
    }
}

void Backend::setDetectionMode(const QString detectionMode){
    bool modified = false;
    std::cout << "HEREEEEEEEEEEEEE\n";
    {
        std::unique_lock<std::mutex> lock(control_data_mutex_);
        if(control_data_.detection_mode == detectionMode){return;}
        control_data_.detection_mode = detectionMode;
        modified = true;
    }
    if(modified){
        emit controlDataChanged();
    }
}

void Backend::setIP(const QString ipAddress){
    if(ip_address_ == ipAddress){return;}
    ip_address_ = ipAddress;
    emit ipChanged(ip_address_);
    qDebug() << "C++: IP set to:" << ipAddress;
}

void Backend::setDesiredSpeed(const float speed){
    bool modified = false;
    {
        std::unique_lock<std::mutex> lock(control_data_mutex_);
        if(speed == control_data_.desired_speed){return;}
            control_data_.desired_speed = speed;
            modified=true;
    }
    if(modified){
        emit controlDataChanged();
    }
}

float Backend::getDesiredSpeed() const {
    return desired_speed_;
}

QString Backend::getIP() const {
    std::unique_lock<std::mutex> lock(display_data_mutex_);
    return ip_address_;
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

float Backend::getCurrentSpeed(){
    std::unique_lock<std::mutex> lock(display_data_mutex_);
    return current_speed_;
}

void Backend::setDisplayData(const GUI::DisplayData display_data){
    bool ip_changed = false;
    bool current_speed_changed = false;
    {
        std::unique_lock<std::mutex> lock(display_data_mutex_);
        if(ip_address_!= display_data.ip){
            ip_address_ = display_data.ip;
            ip_changed = true;
        }
        if(current_speed_ != display_data.current_speed){
            current_speed_= display_data.current_speed;
            current_speed_changed = true;
        }
    }

    if(ip_changed){
        emit ipChanged(ip_address_);
    }
    if(current_speed_changed){
        emit currentSpeedChanged(current_speed_);
    }

}








