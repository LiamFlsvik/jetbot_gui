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
            //std::this_thread::sleep_for(std::chrono::milliseconds(33));
        }

    }
    inline QImage JetBot::convert_to_qimage(const std::vector<uchar> &encoded_frame){
        QImage img = QImage::fromData(encoded_frame.data(), encoded_frame.size());
            if (img.isNull()) {
                std::cout << "Qt failed to decode image data";
                return QImage();
            }
            return img;
        }
    
    void JetBot::send_image(std::vector<uchar> frame){
        try {
            QImage q_image = convert_to_qimage(frame);
            frame_changed emit(q_image);
        }
        catch(std::exception &e) {
                std::cout << e.what() << std::endl;
            }


    }







