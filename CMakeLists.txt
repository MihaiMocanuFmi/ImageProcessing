cmake_minimum_required(VERSION 3.24)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_executable(ImageProcessing
        ImageProcessing.cpp
        libs/PortablePixMap_Plain.cpp libs/Image.cpp
        libs/tools/RgbColor.cpp libs/tools/RgbColor.h libs/tools/Vector2.cpp libs/tools/Rectangle.cpp
        libs/ColorData.cpp libs/ColorData.h)
