#include "Joystick/Joystick.hpp"
#include "Joystick/JoystickCommands.hpp"
#include "Structs/ServerData.hpp"
#include <thread>
#include <chrono>
#include <condition_variable>
class JoystickHandler{
    public:
        JoystickHandler(bool chinese_controller);
        
        ~JoystickHandler();
        void run();
        data::Motion get_motion_command();
    private:
        void get_joystick_values();
        void calculate_motion_command();
        inline float add_deadband(float axis, float deadband);
        void debug();

        Joystick joystick_;
        bool chinese_controller_;
        const float scale_linear_{1};
        const float scale_angular_{1};
        JoystickCommands joystick_commands_;
        data::Motion motion_commands_;
        std::mutex motion_command_mutex_;
        std::thread joystick_handler_thread;
        std::atomic<bool> running_;
        std::condition_variable get_joystick_cv;


};