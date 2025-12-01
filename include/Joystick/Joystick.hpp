#ifndef JETBOT_JOYSTICK_HPP
#define JETBOT_JOYSTICK_HPP


#include <GLFW/glfw3.h>
#include <vector>
#include <string>

class Joystick {
public:
    explicit Joystick(int joystickId = GLFW_JOYSTICK_1);

    bool isConnected() const;
    void update(); //

    // Fetches values for one axis (-1.0 til 1.0)
    float getAxis(int axis_id) const;

    // Specific button is pressed (true/false)
    bool isButtonPressed(int button_id) const;

    // Utility functions
    std::string getName() const;
    int getAxisCount() const;
    int getButtonCount() const;

private:
    int findController();

    int joystick_id_;
    bool is_connected_;
    std::string name_;

    std::vector<float> axes_;
    std::vector<unsigned char> buttons_;
};

#endif //JETBOT_JOYSTICK_HPP