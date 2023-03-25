find_package(Catch2 3 REQUIRED)
# These tests can use the Catch2-provided main
add_executable(tests test.cpp
        Draw/test_Draw.cpp
        Image/test_ColorData.cpp Image/test_Image.cpp Image/test_PortablePixMap_Plain.cpp
        Processing/test_ContrastBrightness.cpp Processing/test_Convolution.cpp Processing/test_Gamma.cpp Processing/test_ImageProcessing.cpp
        Tools/test_Rectangle.cpp Tools/test_RgbColor.cpp Tools/test_Vector2.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

# These tests need their own main
#add_executable(custom-main-tests test.cpp test-main.cpp)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

#include(CTest)
#include(Catch)
#catch_discover_tests(tests)