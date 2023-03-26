#include <catch2/catch_all.hpp>


#include "Tools/Rectangle.h"

TEST_CASE( "Rectangle Creation", "[Rectangle]"){
    tools::Rectangle rectangle0;

    REQUIRE(rectangle0.size == tools::Vector2I {0, 0});
    REQUIRE(rectangle0.upperLeftCorner == tools::Vector2I {0, 0});

    tools::Rectangle rectangle1({5, 7}, {100, 300});

    REQUIRE(rectangle1.size == tools::Vector2I {100, 300});
    REQUIRE(rectangle1.upperLeftCorner == tools::Vector2I {5, 7});

    tools::Rectangle rectangle2(5, 7, 100, 300);

    REQUIRE(rectangle2.size == tools::Vector2I {100, 300});
    REQUIRE(rectangle2.upperLeftCorner == tools::Vector2I {5, 7});
}

TEST_CASE( "Corners", "[Rectangle]"){

}