#ifndef JETBOT_SERVERDATA_HPP
#define JETBOT_SERVERDATA_HPP
#include <string>
#include <nlohmann/json.hpp>

namespace data {
    struct Motion {
        std::string command{"stop"};
        double linear_x{0.0};
        double angular_z{0.0};
    };

    struct ServerData {
        Motion motion;
    };

    // Conversion from structs to json using nlohmann
    inline void to_json(nlohmann::json &j, const Motion &motion) {
        j = nlohmann::json{ {"command",     motion.command  },
                            {"linear_x",    motion.linear_x },
                            {"angular_z",   motion.angular_z}};
    }

    inline void to_json(nlohmann::json &j, const ServerData &serverData) {
        j = nlohmann::json{ {"motion", serverData.motion}};
    }

    // Conversion from json to structs using nlohmann
    inline void from_json(const nlohmann::json &j, Motion &motion) {
        j.at("command").get_to(motion.command);
        j.at("linear_x").get_to(motion.linear_x);
        j.at("angular_z").get_to(motion.angular_z);
    }

    inline void from_json(const nlohmann::json &j, ServerData &serverData) {
        j.at("motion").get_to(serverData.motion);
    }
}



#endif //JETBOT_SERVERDATA_HPP