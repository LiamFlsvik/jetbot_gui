#pragma once
#include "Server/Server.hpp"
#include "Structs/JetbotData.hpp"
#include "Joystick/JoystickHandler.hpp"
#include "VideoStream/VideoReceiver.hpp"
#include <QObject>
#include <QImage>
#include <mutex>
#include <Structs/GUIData.hpp>

class JetBot : public QObject{
    Q_OBJECT
    public:
        explicit JetBot(unsigned long server_port, unsigned long fpv_port, unsigned long lidar_port, bool chinese_controller, QObject *parent);

        ~JetBot();

        void run();

        void update_gui_display(); //TODO: Take in data


        QImage convert_to_qimage(const cv::Mat &mat);
    public slots:   
        void send_image_fpv(cv::Mat frame);
        void send_image_lidar(cv::Mat frame);
        
    signals:
        void frame_changed_fpv(const QImage frame_);
        void frame_changed_lidar(const QImage frame_);

        void gui_display_data_changed(GUI::DisplayData display_data);
        
    private:
        unsigned long port_;
        std::thread server_thread_;
        std::thread joystick_handler_thread_;
        std::thread update_gui_thread_;
        std::thread jetbot_loop_thread_;
        Server server_;
        data::JetbotData jetbot_data_;

        GUI::DisplayData gui_display_data_;
        GUI::ControlData gui_control_data_;
        std::mutex gui_update_mutex;
        JoystickHandler joystick_handler_;
        VideoReceiver video_receiver_fpv_;
        VideoReceiver video_receiver_lidar_;
        std::atomic<bool> simulator_mode_;
        std::atomic<bool> is_running_{};
        data::Motion motion_command_{};
        

};
