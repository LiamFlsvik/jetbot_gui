#include "JetBot.hpp"
#include "VideoStream/VideoReceiver.hpp"


JetBot::JetBot(unsigned long server_port, unsigned long fpv_port, unsigned long lidar_port, bool chinese_controller, QObject *parent = nullptr) 
: QObject(parent), port_(server_port), server_(), joystick_handler_(chinese_controller), video_receiver_fpv_(fpv_port), video_receiver_lidar_(lidar_port)
{
    is_running_ = true;
    QObject::connect(&video_receiver_fpv_,&VideoReceiver::frame_changed,this,&JetBot::send_image_fpv);
    QObject::connect(&video_receiver_lidar_,&VideoReceiver::frame_changed,this,&JetBot::send_image_lidar);
}

JetBot::~JetBot(){
    if (jetbot_loop_thread_.joinable()){
        update_gui_thread_.join();
    }
    if (server_thread_.joinable()){
        server_thread_.join();
    }
    if (update_gui_thread_.joinable()){
        update_gui_thread_.join();
    }
    
    is_running_ = false;
}

    void JetBot::run(){
        server_thread_ = std::thread([this] {this->server_.listener(this->port_);}); 
        joystick_handler_.run();
        video_receiver_fpv_.run();
        //video_receiver_lidar_.run();

        jetbot_loop_thread_ = std::thread([this] {
            while(is_running_){
                server_.setMotionCommand(joystick_handler_.get_motion_command());
            }
        });

        //Timer based update for GUI data:
        update_gui_thread_ = std::thread([this] {
            while(is_running_){
                {
                    std::unique_lock<std::mutex> lock(gui_update_mutex);
                    if (server_.tryGetJetbotData(jetbot_data_)){
                        //update_gui_display(); for testing
                    } 
                    
                    update_gui_display(); //for testing
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        });
    }

    void JetBot::update_gui_display(){
        //Currently only "dummy data" to test the GUI
        gui_display_data_.ip = QString::fromStdString("JetbotIP");
        if(gui_display_data_.current_speed > 2){gui_display_data_.current_speed = 0;}
        gui_display_data_.current_speed += 0.01;
        gui_display_data_.battery_percentage = 100;
        gui_display_data_changed(gui_display_data_);
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







