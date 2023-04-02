#include <catch2/catch_all.hpp>

#include "Image/Image.h"


TEST_CASE( "Image", "[Image]")
{
    SECTION("Creation")
    {
        Image image0;
        REQUIRE(image0.size() == tools::Vector2I(0, 0));
    }
}