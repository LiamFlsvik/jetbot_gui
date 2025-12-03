#include "VideoStream/VideoReceiver.hpp"

VideoReceiver::VideoReceiver(unsigned long port, QObject *parent) : QObject(parent), ep(asio::ip::udp::v4(), port), s(ioContext, ep), frameVector(1920*1080*3) {
    if (s.is_open()) std::cout << "socket åpnet" << std::endl;
    qRegisterMetaType<cv::Mat>("cv::Mat"); //https://stackoverflow.com/questions/9646110/how-to-send-a-qt-signal-containing-a-cvmat
    //for (auto &byte : frameVector) byte = 0x00;
}

VideoReceiver::~VideoReceiver() {
    if(t.joinable()) t.join();
}

void VideoReceiver::run() {

    t = std::thread([this] {
        auto time = std::chrono::steady_clock::now();
        auto prevTime = std::chrono::steady_clock::now();
        while(!shouldClose) {
            try {
                //std::cout << "mottar" << std::endl;

                std::vector<uint8_t> payload(4 + pkgSize);
                size_t bytes = s.receive_from(asio::buffer(payload), remoteEndpoint, 0, ec);

                std::uint16_t thisChunkNumber = 0;
                std::uint16_t thisChunkSize = 0;

                if (bytes == 8) {

                    std::memcpy(&numberOfChunks, payload.data(), 4);
                    std::memcpy(&rows,  payload.data() + 4, 2);
                    std::memcpy(&cols,  payload.data() + 6, 2);

                    //std::cout << "size: " << numberOfChunks << "\trows: " << rows << "\tcolumns: " << cols << std::endl;
                    chunksRecieved = 0;
                } else if(bytes>8) {
                        //std::vector<uint8_t> payloadChunk(4+thisChunkSize);


                        //size_t bytes = s.receive_from(asio::buffer(payload), remoteEndpoint, 0, ec);
                        //frameVector.insert(frameVector.end(), payloadChunk.begin(), payloadChunk.end());

                    if(bytes<4 || bytes > pkgSize+4) {
                        std::cout << "for liten eller stor pakke. Størrelse: " << bytes << std::endl;
                        continue;
                    }

                    chunksRecieved += 1;

                    std::memcpy(&thisChunkNumber, payload.data(), 2);
                    std::memcpy(&thisChunkSize, payload.data()+2, 2);

                    //std::cout << "Number: " << thisChunkNumber << "\tChunksize: " << thisChunkSize<< std::endl;

                    std::size_t offset = static_cast<std::size_t>(thisChunkNumber) * pkgSize;
                    //if (offset >= frameVector.size()) continue;
                    //std::size_t canCopy = std::min<std::size_t>(thisChunkSize, frameVector.size() - offset);
                    std::memcpy(frameVector.data()+offset, payload.data()+4, thisChunkSize);

                }

                if(chunksRecieved>=numberOfChunks) {
                    /*
                    std::cout << "[SERVER] Chunks recieved: " << chunksRecieved
                              << "\tThis chunk number: " << thisChunkNumber
                              << "\tTotal Number of chunks: "<< numberOfChunks
                              << "\tChunk size: " << thisChunkSize
                              << "\tRows: " << rows
                              << "\tColumns: " << cols
                              << std::endl;
                    */

                    try {
                        //cv::Mat frame(rows, cols, CV_8UC3, frameVector.data());
                        {
                            //std::unique_lock<std::mutex> lock(frameMutex);
                            frame = cv::imdecode(frameVector, cv::IMREAD_COLOR);
                            emit frame_changed(frame);
                            
                            //frameCV.notify_all();
                        }

                        time = std::chrono::steady_clock::now();

                        auto duration = std::chrono::duration<double>(time - prevTime);
                        //std::cout << "FPS: " << 1/duration.count() << std::endl;

                        //cv::imshow("motatt", frame);
                        prevTime = time;
                        //cv::waitKey(1);
                    } catch(std::exception &e) {
                        std::cout << "[SERVER] OpenCV error: " << e.what() << std::endl;
                    }

                }
            } catch(std::exception &e) {
                std::cout << e.what() << std::endl;
            }

        }
    });

    
}

