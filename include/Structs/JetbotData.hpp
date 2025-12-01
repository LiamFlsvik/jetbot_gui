#ifndef JETBOT_JETBOTDATA_HPP
#define JETBOT_JETBOTDATA_HPP

#include <nlohmann/json.hpp>

namespace data {
    // Nested structs
    struct ImuData {
        double acc_x = 0.0, acc_y = 0.0, acc_z = 0.0;
        double gyro_x = 0.0, gyro_y = 0.0, gyro_z = 0.0;
    };

    struct EncoderData {
        long left = 0, right = 0;

    };

    struct SensorData {
        ImuData imu;
        EncoderData encoders;
    };


    struct JetbotData {
        SensorData sensorData;
    };

    // Conversion from structs to json using nlohmann
    // EncoderData
    inline void to_json(nlohmann::json &j, const EncoderData &encoderData) {
        j = nlohmann::json{ {"left",    encoderData.left },
                            {"right",   encoderData.right}};
    }

    // ImuData
    inline void to_json(nlohmann::json &j, const ImuData &imuData) {
        j = nlohmann::json{ {"acc_x",   imuData.acc_x },
                            {"acc_y",   imuData.acc_y },
                            {"acc_z",   imuData.acc_z },
                            {"gyro_x",  imuData.gyro_x},
                            {"gyro_y",  imuData.gyro_y},
                            {"gyro_z",  imuData.gyro_z}};
    }

    // SensorData
    inline void to_json(nlohmann::json &j, const SensorData &sensorData) {
        j = nlohmann::json{ {"imu",      sensorData.imu     },
                            {"encoders", sensorData.encoders}};
    }

    // JetbotData
    inline void to_json(nlohmann::json &j, const JetbotData &jetbotData) {
        j = nlohmann::json{ {"Sensordata", jetbotData.sensorData}};
    }

    // Conversion from json to structs using nlohmann
    // ImuData
    inline void from_json(const nlohmann::json &j, ImuData &imuData) {
        j.at("acc_x").get_to(imuData.acc_x);
        j.at("acc_y").get_to(imuData.acc_y);
        j.at("acc_z").get_to(imuData.acc_z);
        j.at("gyro_x").get_to(imuData.gyro_x);
        j.at("gyro_y").get_to(imuData.gyro_y);
        j.at("gyro_z").get_to(imuData.gyro_z);
    }

    // EncoderData
    inline void from_json(const nlohmann::json &j, EncoderData &encoderData) {
        j.at("left").get_to(encoderData.left);
        j.at("right").get_to(encoderData.right);
    }

    // SensorData
    inline void from_json(const nlohmann::json &j, SensorData &sensorData) {
        j.at("imu").get_to(sensorData.imu);
        j.at("encoders").get_to(sensorData.encoders);
    }

    // JetbotData
    inline void from_json(const nlohmann::json &j, JetbotData &jetbotData) {
        j.at("Sensordata").get_to(jetbotData.sensorData);
    }
}





#endif //JETBOT_JETBOTDATA_HPP