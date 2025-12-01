cmake_minimum_required(VERSION 3.15)
project(user_interface)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_compile_definitions(PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")


find_package(Qt6 6.4 COMPONENTS Quick Qml Widgets REQUIRED)

find_package(Threads REQUIRED)

#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
#find_package(Boost REQUIRED)

find_package(OpenCV REQUIRED)


include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw.git"
        GIT_TAG "3.3.7"
)

FetchContent_Declare(
        boost
        GIT_REPOSITORY https://github.com/boostorg/boost.git
        GIT_TAG boost-1.89.0
)

FetchContent_MakeAvailable(nlohmann_json glfw boost)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(GUI 
    main.cpp
    src/Backend.cpp include/Backend.hpp
    src/VideoProvider.cpp include/VideoProvider.hpp
    src/JetBot.cpp include/JetBot.hpp    
    src/Server/Server.cpp include/Server/Server.hpp
    src/Joystick/Joystick.cpp include/Joystick/Joystick.hpp
    src/Joystick/JoystickHandler.cpp include/Joystick/JoystickHandler.hpp
    src/VideoStream/VideoReceiver.cpp include/VideoStream/VideoReceiver.hpp
    include/Structs/JetbotData.hpp
    include/Structs/ServerData.hpp
    include/Joystick/JoystickCommands.hpp
)

qt_add_resources(GUI "app_images"
    PREFIX "/"
    FILES 
        qml/images/jetbot.jpg
        qml/images/lidar.png
        qml/images/taskbar.png
        qml/images/taskbar_top.png
        qml/images/stack.png
        qml/images/stack2.png    
        qml/images/camera.png 
        qml/images/jetpov.png
        qml/images/battery/battery100.png
        qml/images/pid_menu_down.png
        qml/images/pid_menu_up.png
        qml/images/mode_menu.png
)

qt_add_qml_module(GUI
URI gui_uri
VERSION 1.0
QML_FILES
    qml/Main.qml
    qml/Background.qml
    qml/BottomBar.qml
    qml/DisplayCamera.qml
    qml/TopBar.qml
    qml/Modes.qml
    qml/CustomSwitch.qml
    qml/DisplayMap.qml
    qml/DoubleSpinBox.qml
)

target_include_directories(GUI 
    PRIVATE ${CMAKE_SOURCE_DIR}/include
    PRIVATE ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(GUI PRIVATE Qt6::Quick Qt6::Widgets ${OpenCV_LIBS} Boost::asio nlohmann_json::nlohmann_json Threads::Threads glfw)
