# Jetbot GUI
The goal of this project is to create a graphical user interface (GUI) that is useful when operating the Jetbot, providing an intuitive visual interface for control, monitoring, and configuration of various different parameters. The GUI is designed with a multi-threaded architecture such that visual elements and controls are handled in real-time without hindering operation.

The project was developed in the university course [AIS2203](https://www.ntnu.no/studier/emner/AIS2203#tab=omEmnet) and is part of a larger project.


## Features

* Toggle between operating modes: manual control and autonomy mode.

* Displays Real-Time video (UDP)

* Visualizes LiDAR measurements (UDP), or any other desired map/image.

* Joystick Controller interface



![Image of GUI](readme_images/jetbot_gui.png)

### Stack

* Frontend: Written in QML

* Backend: C++

* Graphical element is drawn in [Inkscape](https://inkscape.org/).

### Prerequisites

* A C++ compiler such as Clang, GCC or MSVC

* C++ 23

* CMake 3.15 or higher

* Qt 6

### Configure and build
#### Linux:

> mkdir build 

> cd build && cmake ..  

> cd .. 

> cmake --build build


#### Code structure

##### Classes

* **Backend** - Connects the main logic to the frontend

* **JetBot** - Responsible for setting up all of the jetbot classes and create signals for 

* JetBot/JoystickHandler/**Joystick** - Scans for Joystick interfaces and updates updates all of the joystick axes

* JetBot/**JoystickHandler** - Transforms the joystick input into motion commands

* JetBot/**VideoReceiver** - Receives a UDP camera stream and sends it to the frontend.

* JetBot/**Server** - Enables communication of json data between the JetBot or Simulator.



