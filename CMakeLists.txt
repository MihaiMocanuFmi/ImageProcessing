cmake_minimum_required(VERSION 3.24)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_subdirectory(Tests)

add_executable(ImageProcessing
        main.cpp
        libs/Image/PortablePixMap_Plain.cpp libs/Image/Image.cpp libs/Image/ColorData.cpp
        libs/Tools/RgbColor.cpp libs/Tools/RgbColor.h libs/Tools/Vector2.cpp libs/Tools/Rectangle.cpp
        libs/Processing/ImageProcessing.cpp libs/Processing/ContrastBrightness.cpp libs/Processing/Gamma.cpp
        libs/Processing/Convolution.cpp
        libs/Draw/Draw.cpp Tests/test.cpp)
