#include "Joystick/JoystickHandler.hpp"
#include "Joystick/Joystick.hpp"
#include <cstdlib>
#include <iostream>

JoystickHandler::JoystickHandler(bool chinese_controller) : joystick_(), chinese_controller_(chinese_controller)
{
    glfwInit();
    if(joystick_.isConnected()){
        std::cout << "[Joystick] : Connected\n";
        running_= true;
    } else {
        std::cout << "[Joystick] : Not connected\n";
    }
    std::cout << "[Joystick] STARTED\n";
}

JoystickHandler::~JoystickHandler(){
    running_ = false;
    glfwTerminate();
    joystick_handler_thread.join();
}


void JoystickHandler::run(){
    joystick_handler_thread = std::thread([this](){
        while(running_){
            {
                std::lock_guard<std::mutex> lock(motion_command_mutex_);
                joystick_.update();
                get_joystick_values();
                calculate_motion_command();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });
}

void JoystickHandler::get_joystick_values(){
    if(!chinese_controller_){
        joystick_commands_.left_stick_x =  add_deadband(joystick_.getAxis(0), 0.09);
        joystick_commands_.left_stick_y =  add_deadband(joystick_.getAxis(1), 0.09);
        joystick_commands_.right_stick_x=  add_deadband(joystick_.getAxis(2), 0.09);
        joystick_commands_.left_trigger=   add_deadband(joystick_.getAxis(3), 0.09);
        joystick_commands_.right_trigger=  add_deadband(joystick_.getAxis(4), 0.09);
    } else {
        joystick_commands_.left_stick_x =  add_deadband(joystick_.getAxis(0),0.2);
        joystick_commands_.left_stick_y =  add_deadband(joystick_.getAxis(1),0.2);
        joystick_commands_.right_stick_x=  add_deadband(joystick_.getAxis(3),0.2);
        joystick_commands_.right_stick_y =  add_deadband(joystick_.getAxis(4),0.2);
    }
}

void JoystickHandler::calculate_motion_command(){
    if(!chinese_controller_){
        motion_commands_.angular_z = joystick_commands_.left_stick_x*scale_angular_;
        motion_commands_.linear_x  = (joystick_commands_.right_trigger-std::abs(joystick_commands_.left_trigger))*scale_linear_;
        //debug(); 
    } else {
        //too lazy to add logic for the shitty chinese controller 
    }
}
void JoystickHandler::debug(){
    std::cout << "[JoystickValues] "
              << "LX: " << joystick_commands_.left_stick_x << "  "
              << "LY: " << joystick_commands_.left_stick_y << "  "
              << "RX: " << joystick_commands_.right_stick_x;

    if (!chinese_controller_) {
        std::cout << "  LT: " << joystick_commands_.left_trigger
                  << "  RT: " << joystick_commands_.right_trigger;
    } else {
        std::cout << "  RY: " << joystick_commands_.right_stick_y;
    }

    std::cout << std::endl;


}

inline float JoystickHandler::add_deadband(float axis, float deadband){
    float abs_axis = std::abs(axis);
    if(abs_axis< deadband){
        return 0;
    }
    if(axis > 0){
        return (abs_axis-deadband)/(1.0-deadband);
    }
    if(axis < 0){
        return -(abs_axis-deadband)/(1.0-deadband);
    }
    return 0.0;
}

MotionCommands JoystickHandler::get_motion_command(){

    std::lock_guard<std::mutex> lock(motion_command_mutex_);
    return motion_commands_;
}


