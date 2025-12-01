#pragma once
#include <nlohmann/json.hpp>
#include "JetBotMessages.hpp"


class JsonParser{
    public:
    
    std::string serialize(const JetBotMessages::ControlCommand data);

    JetBotMessages::Receive deserialize(std::string json_data);

    bool is_json(std::string &message);
};