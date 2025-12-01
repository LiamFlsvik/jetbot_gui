#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <QObject>
#include "JetBotMessages.hpp"
#include <mutex>

class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString ip READ getIP WRITE setIP NOTIFY ipChanged)
    Q_PROPERTY(float speed READ getSpeed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool manualMode READ getMode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(QString detectionMode READ getDetectionMode WRITE setDetectionMode NOTIFY detectionModeChanged)
public:
    explicit Backend(QObject* parent = nullptr);
    ~Backend();

    QString getIP() const;
    float getSpeed() const;
    bool getMode() const;
    int getBatteryPercentage() const;
    QString getDetectionMode() const;

public slots:
    //To be sent to JetBot
    void setIP(const QString ipAddress);
    void setSpeed(const float speed);
    void setMode(const bool mode);
    void setDetectionMode(const QString detectionMode);
    void updateControlCommands();
    const JetBotMessages::ControlCommand getControlCommands();

    //Received from JetBot

    void updateReceivedData(const JetBotMessages::Receive data);

signals:
    void ipChanged(QString newIP);
    void speedChanged(float newSpeed);
    void modeChanged(bool newMode);
    void detectionModeChanged(QString detectionMode);
private: 
    std::string ip_address_ = "JetBot User Interface"; // IP address set purely for displaying the ip on the GUI (Display only)
    float speed_; // Speed set by the user (for display only)
    bool mode_; // Jetbot mode set by user; Autonomous or manual.
    int battery_percentage_; // Percentage of current battery.
    std::string detection_mode_; //Machine vision type eg face detection, canny edge or something else
    JetBotMessages::Receive received_data_; // Data received from the JetBot
    JetBotMessages::ControlCommand control_command_; // Data to be sent from the JetBot
    JetBotMessages::ControlCommand latest_control_command_;
    std::mutex get_control_commands_mutex;
};

#endif
