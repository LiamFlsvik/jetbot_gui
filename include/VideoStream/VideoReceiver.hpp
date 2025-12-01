#ifndef VIDEOSTREAM_VIDEORECEIVER_HPP
#define VIDEOSTREAM_VIDEORECEIVER_HPP

#include <opencv2/opencv.hpp>
#include <asio.hpp>
#include <chrono>
#include <iostream>

class VideoReceiver {
public:
    VideoReceiver();
    ~VideoReceiver();

    void run();

    std::size_t pkgSize{1400};

    std::condition_variable frameCV;
    std::mutex frameMutex;
    cv::Mat frame;

    bool shouldClose{false};
    
    cv::Mat getFrame();
    void setFrame(cv::Mat frame);

private:
    cv::Mat frame_;
    asio::io_context ioContext;
    asio::ip::udp::endpoint ep;
    asio::ip::udp::socket s;

    std::thread t;

    asio::ip::udp::endpoint remoteEndpoint;
    std::error_code ec;

    std::vector<std::uint8_t> frameVector;

    std::uint32_t numberOfChunks = 0;
    std::uint16_t rows = 0;
    std::uint16_t cols = 0;

    std::uint16_t chunksRecieved = 0;
    
};


#endif //VIDEOSTREAM_VIDEORECEIVER_HPP