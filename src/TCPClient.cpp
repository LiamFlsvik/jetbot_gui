#include "TCPClient.hpp"


TCPClient::TCPClient(std::string ip_address,int port): io_context_(),
    endpoint_(boost::asio::ip::make_address(ip_address),port),
    socket_(io_context_,boost::asio::ip::tcp::v4())
    {
        boost::system::error_code ec;
        socket_.connect(endpoint_,ec);
        if(ec){
            std::cout << "[TCP Client] error code:" << boost::system::error_code(ec);
            running_=false;
        } else {
            std::cout << "[TCP Client] Active\n";
            running_=true;
        }

    }

    void TCPClient::receive_frame_from_server(){
        boost::system::error_code ec;
        // Read size
        uint32_t frame_size;
        boost::asio::read(socket_,boost::asio::buffer(&frame_size,sizeof(frame_size)),ec);
        if(ec){
            std::cerr << "[TCP Client] Failed to read size of frame:" << ec.message() << "\n";
        }
        std::vector<uchar> frame(frame_size);
        boost::asio::read(socket_,boost::asio::buffer(frame),ec);            
        if(ec){
            std::cout << "[TCP Client] Receive error: " << ec.message() << "\n";
        } else {
            std::unique_lock<std::mutex> lock(frame_mutex_);
            if(!frame.empty()){
                frame_ = opencv_to_qimage(frame);
                emit frameChanged(frame_);
            }
        }
    }
    inline QImage TCPClient::opencv_to_qimage(const std::vector<uchar> &encoded_frame){
             QImage img = QImage::fromData(encoded_frame.data(), encoded_frame.size());
                if (img.isNull()) {
                    std::cout << "Qt failed to decode image data";
                    return QImage();
                }
                return img;
            }

    void TCPClient::run(){
        while(running_){
            receive_frame_from_server();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }
    

