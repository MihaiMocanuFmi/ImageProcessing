cmake_minimum_required(VERSION 3.24)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/")

add_executable(ImageProcessing
        ImageProcessing.cpp
        libs/PortablePixMap_Plain.cpp libs/PortablePixMap_Plain.h libs/Image.cpp
        libs/tools/RgbColor.cpp libs/tools/RgbColor.h libs/tools/Vector2.cpp)
