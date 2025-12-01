# Jetbot GUI
The goal of this project is to create a user interface that is useful when using the Jetbot.

#install packages
conan install . --output-folder=build --build=missing


# configure  
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=build/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release

# build
cmake --build build
