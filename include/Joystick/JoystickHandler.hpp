#include "Joystick/Joystick.hpp"
#include "Joystick/MotionCommands.hpp"
#include "Joystick/JoystickCommands.hpp"
#include <thread>
#include "chrono"
class JoystickHandler{
    public:
        JoystickHandler(bool chinese_controller);
        
        ~JoystickHandler();
        void run();
        MotionCommands get_motion_command();
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
        JoystickCommands joystick_deadband_;
        MotionCommands motion_commands_;
        std::mutex motion_command_mutex_;
        std::thread joystick_handler_thread;
        std::atomic<bool> running_;


};