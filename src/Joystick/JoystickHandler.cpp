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
        joystick_commands_.left_stick_x =  -add_deadband(joystick_.getAxis(0),0.2); //Inverted
        joystick_commands_.left_stick_y =  -add_deadband(joystick_.getAxis(1),0.2); //Inverted
        joystick_commands_.right_stick_x=  add_deadband(joystick_.getAxis(2),0.2);
        joystick_commands_.right_stick_y = -add_deadband(joystick_.getAxis(3),0.2); //Inverted
    }
}

void JoystickHandler::calculate_motion_command(){
    if(!chinese_controller_){
        motion_commands_.angular_z = joystick_commands_.left_stick_x*scale_angular_;
        motion_commands_.linear_x  = (joystick_commands_.right_trigger-std::abs(joystick_commands_.left_trigger))*scale_linear_;
    } else {
        motion_commands_.angular_z = joystick_commands_.left_stick_x*scale_angular_*5;
        motion_commands_.linear_x  = joystick_commands_.right_stick_y*scale_linear_;
        //debug(); 
        //std::cout << "linear: " << motion_commands_.linear_x << "   angular" << motion_commands_.angular_z << "\n";
    }
}
void JoystickHandler::debug(){
    for(int i= 0; i<10; i++){
        std::cout << "C_" << i << " = " << joystick_.getAxis(i) << "  ";
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

bool JoystickHandler::joystick_changed(){
    float joystick_sum = 0;
    joystick_sum = motion_commands_.angular_z+motion_commands_.linear_x;
    if(joystick_sum != last_joystick_sum_){
        last_joystick_sum_ = joystick_sum;
        return true;
    } else {
        return false;
    }
}

bool JoystickHandler::try_get_motion_command(data::Motion &motion_command){
    std::lock_guard<std::mutex> lock(motion_command_mutex_);
    if(joystick_changed()){
        motion_command = motion_commands_;
        return true;
    } else{
        return false;
    }
}




