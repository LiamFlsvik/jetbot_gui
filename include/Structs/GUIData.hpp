#pragma once

#ifndef GUIDATA_HPP
#define GUIDATA_HPP

#include <QMetaType>

namespace GUI{
    struct DisplayData{
        QString ip;
        float current_speed;
        int battery_percentage;
    };

    struct ControlData{
        bool armed_or_disarmed;
        bool manual_mode;
        float desired_speed;
        float yaw_gain, yaw_kp, yaw_ki, yaw_kd;
        float lin_gain, lin_kp, lin_ki, lin_kd;
        QString detection_mode;
        bool simulator_mode;
    };
}
// to use the type with qt
Q_DECLARE_METATYPE(GUI::DisplayData)
Q_DECLARE_METATYPE(GUI::ControlData)


#endif