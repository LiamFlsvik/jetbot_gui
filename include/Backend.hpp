#ifndef BACKEND_HPP
#define BACKEND_HPP
#include <QObject>



class Backend : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString ip READ getIP NOTIFY ipChanged)
    Q_PROPERTY(float speed READ getSpeed NOTIFY speedChanged)
public:
    explicit Backend(QObject* parent = nullptr);
    ~Backend();

    QString getIP() const;
    float getSpeed();

public slots:
    void setMode(bool mode);
    void setIP(std::string ip_address);
    void setSpeed(float speed);
    
signals:
    void modeChanged(bool newMode);
    void ipChanged();
    void speedChanged();

private: 
    bool manual_mode_; // Manual control set by user
    std::string ip_address_ = "JetBot User Interface"; // IP address set purely for displaying the ip on the GUI (Display only)
    float speed_; // Speed set by the user (for display only)
    std::string detection_mode_; //Machine vision type eg face detection, canny edge or something else
};

#endif
