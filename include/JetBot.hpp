#pragma once
#include "Server/Server.hpp"
#include "Structs/JetbotData.hpp"
#include "Joystick/JoystickHandler.hpp"
#include "VideoStream/VideoReceiver.hpp"
#include <QObject>
#include <QImage>
#include <mutex>


class JetBot : public QObject{
    Q_OBJECT
    public:
        explicit JetBot(std::string ip_address, unsigned long port, bool chinese_controller, QObject *parent);

        ~JetBot();

        void run();

        void send_image(cv::Mat frame);
        inline QImage convert_to_qimage(const cv::Mat &mat);
    signals:
        void frame_changed(const QImage frame_);

    private:
        unsigned long port_;
        std::thread server_thread_;
        std::thread joystick_handler_thread_;
        
        Server server_;
        JoystickHandler joystick_handler_;
        VideoReceiver video_receiver_fpv_;

        std::atomic<bool> simulator_mode_;
        std::atomic<bool> is_running_{};
        data::Motion motion_command_{};
        

};
