#include <catch2/catch_all.hpp>


#include "Tools/Rectangle.h"

TEST_CASE( "Rectangle Creation", "[Rectangle]")
{
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

TEST_CASE( "Rectangle Corners", "[Rectangle]")
{
    tools::Rectangle rectangle0;
    REQUIRE(rectangle0.findLowerRight() == tools::Vector2I(0,0));
    REQUIRE(rectangle0.findLowerLeft() == tools::Vector2I(0,0));
    REQUIRE(rectangle0.findUpperRight() == tools::Vector2I(0,0));

    tools::Rectangle rectangle1({0, 0}, {1 , 1});
    REQUIRE(rectangle1.findLowerRight() == tools::Vector2I(1,1));
    REQUIRE(rectangle1.findLowerLeft() == tools::Vector2I(0,1));
    REQUIRE(rectangle1.findUpperRight() == tools::Vector2I(1,0));

    tools::Rectangle rectangle2({1, 2}, {1 , 2});
    REQUIRE(rectangle2.findLowerRight() == tools::Vector2I(2,4));
    REQUIRE(rectangle2.findLowerLeft() == tools::Vector2I(1,4));
    REQUIRE(rectangle2.findUpperRight() == tools::Vector2I(2,2));
}

TEST_CASE( "Rectangle static functions", "[Rectangle]")
{
    tools::Rectangle rectangle0;
    REQUIRE(tools::Rectangle::isContainedInside({0, 0}, rectangle0) == true);
    REQUIRE(tools::Rectangle::isContainedInside({0, 1}, rectangle0) == false);

    tools::Rectangle rectangle1({1, 2}, {1 , 2});
    REQUIRE(tools::Rectangle::isContainedInside({1, 2}, rectangle1) == true);
    REQUIRE(tools::Rectangle::isContainedInside({1, 1}, rectangle1) == false);

    REQUIRE(tools::Rectangle::isContainedInside(rectangle0, rectangle1) == false);
    REQUIRE(tools::Rectangle::isContainedInside(rectangle1, rectangle0) == false);

    tools::Rectangle rectangle2({1, 1}, {10 , 20});
    REQUIRE(tools::Rectangle::isContainedInside(rectangle1, rectangle2) == true);
    REQUIRE(tools::Rectangle::isContainedInside(rectangle2, rectangle1) == false);

}