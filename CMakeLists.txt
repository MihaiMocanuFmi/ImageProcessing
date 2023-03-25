cmake_minimum_required(VERSION 3.24)
project(ImageProcessing)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/builds")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

add_subdirectory(Tests)

add_executable(ImageProcessing
        main.cpp
        Libs/Image/PortablePixMap_Plain.cpp Libs/Image/Image.cpp Libs/Image/ColorData.cpp
        Libs/Tools/RgbColor.cpp Libs/Tools/RgbColor.h Libs/Tools/Vector2.cpp Libs/Tools/Rectangle.cpp
        Libs/Processing/ImageProcessing.cpp Libs/Processing/ContrastBrightness.cpp Libs/Processing/Gamma.cpp
        Libs/Processing/Convolution.cpp
        Libs/Draw/Draw.cpp)
