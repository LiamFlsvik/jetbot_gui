#include "JetBot.hpp"
#include <cmath>


JetBot::JetBot(unsigned long server_port, unsigned long fpv_port, unsigned long lidar_port, bool chinese_controller, QObject *parent = nullptr) 
: QObject(parent), port_(server_port), server_(), joystick_handler_(chinese_controller), video_receiver_fpv_(fpv_port), video_receiver_lidar_(lidar_port)
{
    is_running_ = true;
    QObject::connect(&video_receiver_fpv_,&VideoReceiver::frame_changed,this,&JetBot::send_image_fpv);
    QObject::connect(&video_receiver_lidar_,&VideoReceiver::frame_changed,this,&JetBot::send_image_lidar);
}

JetBot::~JetBot(){
    is_running_ = false;

    if (jetbot_loop_thread_.joinable()){
        jetbot_loop_thread_.join();
    }
    if (server_thread_.joinable()){
        server_thread_.join();
    }
    if (update_gui_thread_.joinable()){
        update_gui_thread_.join();
    }
    
}

    void JetBot::run(){
        server_thread_ = std::thread([this] {this->server_.listener(this->port_);}); 
        joystick_handler_.run();
        video_receiver_fpv_.run();
        //video_receiver_lidar_.run();

        //Update for joystick and gui commands:
        jetbot_loop_thread_ = std::thread([this] {
            while(is_running_){
                if(joystick_handler_.try_get_motion_command(motion_command_)){
                    server_.setMotionCommand(motion_command_);
                }
                if(update_gui_control_data_){
                    server_.setMotionCommand(motion_command_);
                    update_gui_control_data_=false;
                }
            }
        });

        //Timer based update for GUI data:
        update_gui_thread_ = std::thread([this] {
            while(is_running_){
                {
                    std::unique_lock<std::mutex> lock(gui_update_mutex);
                    
                    if (server_.tryGetJetbotData(jetbot_data_)){
                        update_gui_display(jetbot_data_); 
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        });
    }

    void JetBot::gui_control_data_set(GUI::ControlData control_data){
        std::unique_lock<std::mutex> lock(gui_update_mutex);
        std::cout << "on gui control data set\n\r";
        if (!update_gui_control_data_){
            gui_control_data_ = control_data;
            motion_command_.armed_or_disarmed = true;
            motion_command_.manual_mode = control_data.manual_mode;
            motion_command_.desired_speed = control_data.desired_speed;
            motion_command_.armed_or_disarmed = control_data.armed_or_disarmed;
            motion_command_.detection_mode = control_data.detection_mode.toStdString();
        } 
        update_gui_control_data_ = true; //flag to allow the thread update_gui_thread_ to update the control data
    }

    void JetBot::update_gui_display(data::JetbotData jetbot_data){
        //Currently only "dummy data" to test the GUI
        gui_display_data_.ip = QString::fromStdString("JetbotIP");
        gui_display_data_.current_speed =std::sqrt(std::pow(jetbot_data.sensorData.imu.acc_x,2)+std::pow(jetbot_data.sensorData.imu.acc_y,2)+std::pow(jetbot_data.sensorData.imu.acc_z,2));
        gui_display_data_.battery_percentage = 100;
        emit gui_display_data_changed(gui_display_data_);
    }
    
    QImage JetBot::convert_to_qimage(const cv::Mat &mat){
        QImage img = QImage((uchar*) mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
        if (img.isNull()) {
            //std::cout << "Qt failed to decode image data";
            return QImage();
        }
        return img;
    }
    
    void JetBot::send_image_fpv(cv::Mat frame){
        try {
            QImage q_image = convert_to_qimage(frame);
            emit frame_changed_fpv(q_image);
        }
        catch(std::exception &e) {
                std::cout << e.what() << std::endl;
        }
    }

    void JetBot::send_image_lidar(cv::Mat frame){
        try {
            QImage q_image = convert_to_qimage(frame);
            emit frame_changed_lidar(q_image);
        }
        catch(std::exception &e) {
                std::cout << e.what() << std::endl;
            }
    }







