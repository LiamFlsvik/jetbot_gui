#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <qtmetamacros.h>
#pragma once
#include <QObject>
#include <chrono>
#include <mutex>
#include "Structs/GUIData.hpp"
#include <thread>
#include <iostream>
class Backend : public QObject {
    Q_OBJECT
    // For display
    Q_PROPERTY(QString ip READ getIP WRITE setIP NOTIFY ipChanged)
    Q_PROPERTY(float currentSpeed READ getCurrentSpeed NOTIFY currentSpeedChanged)
    
    //For control
    //Q_PROPERTY(float simulatorMode READ getSimulatorMode WRITE setSimulatorMode NOTIFY simulatorModeChanged)
    Q_PROPERTY(float arm READ getArmMode WRITE setArmMode NOTIFY armChanged)
    Q_PROPERTY(float desiredSpeed READ getDesiredSpeed WRITE setDesiredSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool manualMode READ getMode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QString detectionMode READ getDetectionMode WRITE setDetectionMode NOTIFY detectionModeChanged)
public:
    explicit Backend(QObject* parent = nullptr);
    ~Backend();

    QString getIP() const;
    float getDesiredSpeed() const;
    bool getMode() const;
    int getBatteryPercentage() const;
    QString getDetectionMode() const;
    float getCurrentSpeed();
    bool getArmMode() const;
    GUI::ControlData getControlData();
    //bool getSimulatorMode() const;
public slots:
    //To be sent to JetBot
    void setMode(const bool mode);
    void setDetectionMode(const QString detectionMode);
    void setDesiredSpeed(const float speed);
    void setArmMode(const bool arm_mode);
    //Received from JetBot
    void setIP(const QString ipAddress);
    void setDisplayData(const GUI::DisplayData display_data);
    //void setSimulatorMode(const bool simulator_mode);

signals:
    //void simulatorModeChanged(bool simulator_mode);
    void armChanged(bool arm_mode);
    void currentSpeedChanged(float current_speed_);
    void ipChanged(QString newIP);
    void speedChanged(float newSpeed);
    void modeChanged(bool newMode);
    void detectionModeChanged(QString detectionMode);
    void controlDataChanged(GUI::ControlData controlData);
private: 
    QString ip_address_ = "JetBot User Interface"; // IP address set purely for displaying the ip on the GUI (Display only)
    float desired_speed_; 
    bool arm_;
    float current_speed_; // Jetbot Speed (for display only)
    bool mode_; // Jetbot mode set by user; Autonomous or manual.
    int battery_percentage_; // Percentage of current battery.
    std::string detection_mode_; //Machine vision type eg face detection, canny edge or something else
    mutable std::mutex display_data_mutex_;
    GUI::DisplayData gui_display_data_;

    GUI::ControlData control_data_;

    mutable std::thread control_data_update_thread_;
    std::mutex control_data_mutex_;
    
    


};

#endif
