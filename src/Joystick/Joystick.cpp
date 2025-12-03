#include "Joystick/Joystick.hpp"
#include "GLFW/glfw3.h"
#include <iostream>
/*
KARTLEGGING AV KONTROLLER ("Pro Controller")
AKSER:
- Venstre Spak Opp/Ned:     Akse 1 (-1.0 for opp, 1.0 for ned)
- Venstre Spak Venstre/Høyre: Akse 0 (-1.0 for venstre, 1.0 for høyre)
- Høyre Spak Opp/Ned:       Akse 3 (-1.0 for opp, 1.0 for ned)
- Høyre Spak Venstre/Høyre: Akse 2 (-1.0 for venstre, 1.0 for høyre)
- L2 Trigger:               Akse 4 Ikke analog 0/1
- R2 Trigger:               Akse 5 Ikke analog 0/1

KNAPPER:
- A:      0
- B:      1
- X:      2
- Y:      3
- L1:     4
- R1:     5
- Select: 6
- Start:  7
*/

Joystick::Joystick(int joystickId) 
    : joystick_id_(joystickId), 
      is_connected_(false), 
      name_("No Joystick") 
{
    joystick_id_ = findController();
    if (joystick_id_ == -1){
        return;
    }
    update();
}

bool Joystick::isConnected() const {
    return is_connected_;
}

int Joystick::findController() {
    int joy_id;
    for (int id = 0; id < 15; ++id) {
        if (glfwJoystickPresent(id)) {
            std::string name = glfwGetJoystickName(id);
            std::cout << "Found potential joystick : " << name << "ID:" << id; "\n";
            if (name.find("Touchpad") != std::string::npos ||
                name.find("ELAN") != std::string::npos ||
                name.find("Razer") != std::string::npos)
            {
                std::cout << "No controllers \n";
                continue;
            }
            std::cout << "Controller found: " << glfwGetJoystickName(id) << "\n";
            return id; 
        }
    }
    return -1;
}

void Joystick::update() {
    // Sjekk om joysticken tilkoblet
    if (!is_connected_ && glfwJoystickPresent(joystick_id_)) {
        is_connected_ = true;
        name_ = glfwGetJoystickName(joystick_id_);
        //std::cout << "[Joystick] INFO: Joystick is connected: " << name_ << std::endl;
    }
    
    if (!is_connected_) {
        return;
    }

    // Sjekk om joysticken har blitt frakoblet
    if (!glfwJoystickPresent(joystick_id_)) {
        is_connected_ = false;
        axes_.clear();
        buttons_.clear();
        name_ = "Ingen joystick";
        //std::cout << "[Joystick] INFO: Joystick disconnected." << std::endl;
        return;
    }

    // hente data for akser
    int axesCount;
    const float* axes_ptr = glfwGetJoystickAxes(joystick_id_, &axesCount);
    if (axes_ptr) {
        axes_.assign(axes_ptr, axes_ptr + axesCount);
    }

    // hente data for knapper
    int buttonsCount;
    const unsigned char* buttons_ptr = glfwGetJoystickButtons(joystick_id_, &buttonsCount);
    if (buttons_ptr) {
        buttons_.assign(buttons_ptr, buttons_ptr + buttonsCount);
    }
}

float Joystick::getAxis(int axis_id) const {
    if (axis_id >= 0 && axis_id < axes_.size()) {
        return axes_[axis_id];
    }
    return 0.0f;
}

bool Joystick::isButtonPressed(int button_id) const {
    if (button_id >= 0 && button_id < buttons_.size()) {
        return buttons_[button_id] == GLFW_PRESS;
    }
    return false;
}

std::string Joystick::getName() const {
    return name_;
}

int Joystick::getAxisCount() const {
    return static_cast<int>(axes_.size());
}

int Joystick::getButtonCount() const {
    return static_cast<int>(buttons_.size());
}