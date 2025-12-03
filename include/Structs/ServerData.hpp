#ifndef JETBOT_SERVERDATA_HPP
#define JETBOT_SERVERDATA_HPP
#include <string>
#include <nlohmann/json.hpp>

namespace data {
    struct Motion {
        bool armed_or_disarmed{true}; // From GUI
        float linear_x{0.0}; //From joystick
        float angular_z{0.0};  //From joystick
        float desired_speed{}; //From GUI in autonomy mode
        std::string detection_mode; // From GUI
        
    };

    struct ServerData {
        Motion motion;
    };

    // Conversion from structs to json using nlohmann
    inline void to_json(nlohmann::json &j, const Motion &motion) {
        j = nlohmann::json{ {"armed_or_disarmed",     motion.armed_or_disarmed  },
                            {"linear_x",    motion.linear_x },
                            {"angular_z",   motion.angular_z},
                            {"desired_speed", motion.desired_speed},
                                {"detection_mode", motion.detection_mode}
                            };
    }

    inline void to_json(nlohmann::json &j, const ServerData &serverData) {
        j = nlohmann::json{ {"motion", serverData.motion}};
    }

    // Conversion from json to structs using nlohmann
    inline void from_json(const nlohmann::json &j, Motion &motion) {
        j.at("armed_or_disarmed").get_to(motion.armed_or_disarmed);
        j.at("linear_x").get_to(motion.linear_x);
        j.at("angular_z").get_to(motion.angular_z);
        j.at("desired_speed").get_to(motion.desired_speed);
        j.at("detection_mode").get_to(motion.detection_mode);
    }

    inline void from_json(const nlohmann::json &j, ServerData &serverData) {
        j.at("motion").get_to(serverData.motion);
    }
}



#endif //JETBOT_SERVERDATA_HPP