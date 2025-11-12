#pragma once
#include <boost/asio.hpp>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <chrono>
#include <QObject>
#include <QImage>

// https://www.boost.org/doc/libs/master/doc/html/boost_asio/tutorial/tutdaytime4.html
//TODO: Handle disconnections.
class TCPClient: public QObject{
    Q_OBJECT
    public:
        TCPClient(std::string ip_address,int port);
    
        void receive_frame_from_server();

        void run();

        inline QImage opencv_to_qimage(const std::vector<uchar> &encoded_frame);

    signals:
        void frameChanged(const QImage frame_);

    private:
        boost::asio::io_context io_context_;
        boost::asio::ip::tcp::socket socket_;
        boost::asio::ip::tcp::endpoint endpoint_;
        std::mutex frame_mutex_;
        QImage frame_;
        std::atomic<bool> running_;
};