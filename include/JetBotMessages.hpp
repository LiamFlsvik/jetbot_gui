#pragma once
#include <string>
#include <vector>

namespace JetBotMessages {
    struct ControlCommand{
        bool armed_or_disarmed;
        bool mode;
        std::string detection_mode;
        float speed;  
        std::vector<double> regulator_gains; //[g,kp.ki,kd,g,kp.ki,kd] distance and yaw gain
    };

    struct Receive{
        std::vector<double> position;
        std::vector<double> velocity;
        std::vector<double> acceleration;
        bool foo;
        std::string voo;
        


    } ;


}