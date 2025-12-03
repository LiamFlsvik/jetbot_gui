#ifndef JETRACERTCP_SERVER_HPP
#define JETRACERTCP_SERVER_HPP

#include <asio.hpp>
#include "Structs/JetbotData.hpp"
#include "Structs/ServerData.hpp"

class Server {
public:

    void connectionHandler(asio::ip::tcp::socket socket);

    void listener(const unsigned long &port);
    void setMotionCommand(data::Motion motion);
    bool tryGetJetbotData(data::JetbotData &data);
    
    std::atomic<bool> shouldStop{false};

    data::JetbotData jetbotData;
    data::ServerData serverData;

    std::mutex jetbotDataMutex;
    std::mutex serverDataMutex;

    std::condition_variable jetbotDataCV;
    std::condition_variable serverDataCV;

    std::atomic<bool> newJetbotData;
    std::atomic<bool> newServerData;
private:

};


#endif //JETRACERTCP_SERVER_HPP