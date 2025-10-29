cmake_minimum_required(VERSION 3.15)
project(user_interface)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.4 COMPONENTS Quick Qml REQUIRED)

find_package(OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Boost REQUIRED)

qt_standard_project_setup(REQUIRES 6.4)

qt_add_executable(GUI 
    main.cpp
    src/Backend.cpp include/Backend.hpp
    src/TCPClient.cpp include/TCPClient.hpp
)


qt_add_resources(GUI "app_images"
    PREFIX "/"
    FILES 
        qml/images/jetbot.jpg
        qml/images/lidar.jpeg
        qml/images/taskbar.png
        qml/images/taskbar_top.png
        qml/images/battery100.png
        qml/images/stack.png
        qml/images/stack2.png    
        qml/images/camera.png 
        qml/images/jetpov.png

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
)

target_include_directories(GUI PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(GUI PRIVATE Qt6::Quick ${OpenCV_LIBS} boost::boost)
#set(QT_QML_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/qml" CACHE PATH "Install path for QML" FORCE)
#set(QML_IMPORT_PATH ${CMAKE_BINARY_DIR}/qml CACHE STRING "Extra QML Import Paths" FORCE)