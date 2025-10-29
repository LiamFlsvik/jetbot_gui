#pragma once
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <chrono>

// https://www.boost.org/doc/libs/master/doc/html/boost_asio/tutorial/tutdaytime4.html
//TODO: Handle disconnections.
class TCPClient{
    public:
        TCPClient(std::string ip_address,int port);

        void receive_frame_from_server();

        std::vector<uchar> get_frame();

    private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::endpoint endpoint_;
    
    std::mutex frame_mutex_;
    std::vector<uchar> frame_;
};