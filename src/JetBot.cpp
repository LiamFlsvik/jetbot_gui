#include "JetBot.hpp"


JetBot::JetBot(std::string ip_address, unsigned long port, bool chinese_controller, QObject *parent = nullptr) 
: QObject(parent), port_(port), server_(), joystick_handler_(chinese_controller)
{
    is_running_ = true;
}

JetBot::~JetBot(){
    if (server_thread_.joinable()){
        server_thread_.join();
    }
   
    is_running_ = false;
}

    void JetBot::run(){
        server_thread_ = std::thread([this] {this->server_.listener(this->port_);}); 
        joystick_handler_.run();
        video_receiver_fpv_.run();

        while(true){
            send_image(video_receiver_fpv_.getFrame());
            server_.setMotionCommand(joystick_handler_.get_motion_command());
        }

    }
    inline QImage JetBot::convert_to_qimage(const cv::Mat &mat){
        QImage img = QImage((uchar*) mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).rgbSwapped();
        if (img.isNull()) {
            //std::cout << "Qt failed to decode image data";
            return QImage();
        }
        return img;
        }
    
    void JetBot::send_image(cv::Mat frame){
        try {
            QImage q_image = convert_to_qimage(frame);
            frame_changed emit(q_image);
        }
        catch(std::exception &e) {
                std::cout << e.what() << std::endl;
            }


    }







