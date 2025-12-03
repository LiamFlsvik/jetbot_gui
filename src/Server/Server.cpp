#include "../include/Server/Server.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <thread>

void Server::listener(const unsigned long &port) {
    asio::io_context ioContext;
    //asio::ip::tcp::endpoint serverCredentials(asio::ip::make_address(ipAddress), port);
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), static_cast<unsigned short>(port));

    asio::ip::tcp::acceptor globalAcceptor(ioContext, endpoint);

    std::vector<std::thread> threadPool;
    
    while(!shouldStop.load()){
        asio::ip::tcp::socket socket(ioContext);

        std::cout << "Waiting for connection..." << std::endl;

        try {
            globalAcceptor.accept(socket);
        } catch(std::system_error &e) {
            continue;
        }

        threadPool.emplace_back(std::thread([this, s = std::move(socket)]() mutable {
            asio::ip::tcp::endpoint remoteEndpoint = s.remote_endpoint();
            std::cout << "New connection from: "    << remoteEndpoint.address().to_string();
            std::cout << ":"                        << remoteEndpoint.port() << std::endl;
            Server::connectionHandler(std::move(s));
        }));
    }
    for (auto &t : threadPool) {
        if (t.joinable()) t.join();
    }
}

void Server::connectionHandler(asio::ip::tcp::socket socket) {
    std::mutex receivedMsgMutex;
    std::condition_variable receivedMsgCV;
    std::vector<std::uint8_t> receivedMsg;
    // Read Json

    std::thread readThread([this, &socket, &receivedMsg, &receivedMsgMutex, &receivedMsgCV] {
        while(!shouldStop.load() && socket.is_open()) {
            try {
                std::uint32_t sizeOfMsg;

                asio::read(socket, asio::buffer(&sizeOfMsg, 4));

                {
                    std::unique_lock<std::mutex> lock(receivedMsgMutex);
                    receivedMsg.resize(sizeOfMsg);
                    asio::read(socket, asio::buffer(receivedMsg.data(), sizeOfMsg));
                    receivedMsgCV.notify_all();
                }

            } catch(std::system_error &e) {
                std::cout << "[Server] Boost system error on read" << e.what() << std::endl;

                socket.close();
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            } catch(nlohmann::json_abi_v3_12_0::detail::out_of_range &e) {
                std::this_thread::sleep_for(std::chrono::seconds(5));
                continue;
            }
        }
    });

    std::thread readHandler([this, &socket,  &receivedMsg, &receivedMsgMutex, &receivedMsgCV] {
        while(!shouldStop.load()) {
            try {
                nlohmann::json jsonData;
                {
                    std::unique_lock<std::mutex> lock(receivedMsgMutex);
                    receivedMsgCV.wait(lock, [&] {return shouldStop.load() || !socket.is_open() || !receivedMsg.empty();});

                    if (shouldStop.load() || !socket.is_open()) {
                        return;
                    }
                    if (receivedMsg.empty()) {
                        continue;
                    }
                    jsonData = nlohmann::json::from_msgpack(receivedMsg);
                    receivedMsg.clear();
                }

                {
                    std::unique_lock<std::mutex> lock(jetbotDataMutex);
                    jetbotData = jsonData.get<data::JetbotData>();
                    jetbotDataCV.notify_all();
                    newJetbotData = true;
                }

            } catch (const nlohmann::json::parse_error &pe) {
                std::cout << "[Server] Parse-fail on read: " << pe.what() << std::endl;
            }

            //std::cout << "Received: \"" << jsonObj.dump(-1) << "\"" << std::endl;
        }
    });

    // Send Json
    std::vector<std::uint8_t> msgToSend;
    std::mutex msgToSendMutex;
    std::condition_variable msgToSendCV;
    std::thread writeThread([this, &socket, &msgToSend, &msgToSendMutex, &msgToSendCV] {
        while(!shouldStop.load() && socket.is_open()){
            try {
                nlohmann::json jsonData;
                {
                    std::unique_lock<std::mutex> lock(serverDataMutex);
                    serverDataCV.wait(lock, [&] {return shouldStop.load() || !socket.is_open() || newServerData.load();});

                    if (shouldStop.load() || !socket.is_open()) {
                        return;
                    }
                    if (!newServerData.load()) {
                        continue;
                    }

                    jsonData = serverData;
                    newServerData = false;
                }

                std::vector<std::uint8_t> tempMsgPck = nlohmann::json::to_msgpack(jsonData);
                {
                    std::unique_lock<std::mutex> lock(msgToSendMutex);
                    msgToSend = std::move(tempMsgPck);
                    msgToSendCV.notify_all();
                }
                std::cout << "sending: " << jsonData.dump(4) << std::endl;
            } catch (const nlohmann::json::parse_error &pe) {
                std::cout << "[Server] Parse-fail on write: " << pe.what() << std::endl;
            }
        }
    });

    std::thread senderThread([this, &socket, &msgToSend, &msgToSendMutex, &msgToSendCV] {
        while(!shouldStop.load() && socket.is_open()){
            try {
                std::vector<uint8_t> tempMsgPck;
                {
                    std::unique_lock<std::mutex> lock(msgToSendMutex);
                    msgToSendCV.wait(lock, [&] {return shouldStop.load() || !socket.is_open() || !msgToSend.empty();});
                    if (shouldStop.load() || !socket.is_open()) {
                        return;
                    }
                    if (msgToSend.empty()) {
                        continue;
                    }
                    tempMsgPck = msgToSend;
                    msgToSend.clear();
                }

                uint32_t sizeOfMsg = tempMsgPck.size();

                std::vector<std::uint8_t> header(4);
                std::memcpy(header.data(), &sizeOfMsg, 4);

                std::vector<uint8_t> package;
                package.insert(package.end(), header.begin(), header.end());
                package.insert(package.end(), tempMsgPck.begin(), tempMsgPck.end());

                asio::write(socket, asio::buffer(package));
            } catch(const std::system_error &e) {
                std::cout << "[Server] Boost system error on write" << e.what() << std::endl;

                socket.close();
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    });

    msgToSendCV.notify_all();
    receivedMsgCV.notify_all();

    if (readThread.joinable())      readThread.join();
    if (writeThread.joinable())     writeThread.join();
    if (readHandler.joinable())     readHandler.join();
    if (senderThread.joinable())    senderThread.join();
}

void Server::setMotionCommand(data::Motion motion){
    std::unique_lock<std::mutex> lock(serverDataMutex);
    serverData.motion = motion;
    if(!newServerData.load()){
        serverDataCV.notify_all();
        newServerData = true;
    }
}

bool Server::tryGetJetbotData(data::JetbotData &data){
    std::unique_lock<std::mutex> lock(jetbotDataMutex);
    if (newJetbotData){
        data = jetbotData;
        newJetbotData=false;
        return true;
    }
    return false;
}


