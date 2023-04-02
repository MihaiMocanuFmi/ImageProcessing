#include <catch2/catch_all.hpp>


#include "Tools/Rectangle.h"


TEST_CASE( "Rectangle", "[Rectangle]")
{
    using namespace tools;

    SECTION("Creation")
    {
        Rectangle rectangle0;

        REQUIRE(rectangle0.size == Vector2I{0, 0});
        REQUIRE(rectangle0.upperLeftCorner == Vector2I{0, 0});

        Rectangle rectangle1(Vector2I{5, 7}, Vector2I{100, 300});
        REQUIRE(rectangle1.size == Vector2I{100, 300});
        REQUIRE(rectangle1.upperLeftCorner == Vector2I{5, 7});

        Rectangle rectangle2(5, 7, 100, 300);
        REQUIRE(rectangle2.size == Vector2I{100, 300});
        REQUIRE(rectangle2.upperLeftCorner == Vector2I{5, 7});

        Rectangle rectangle3(Point(1, 2), Point(2, 4));
        REQUIRE(rectangle3.size == Vector2I{1, 2});
        REQUIRE(rectangle3.upperLeftCorner == Vector2I{1, 2});
    }

    SECTION("Corners")
    {
        Rectangle rectangle0;
        REQUIRE(rectangle0.findLowerRight() == Vector2I(0, 0));
        REQUIRE(rectangle0.findLowerLeft() == Vector2I(0, 0));
        REQUIRE(rectangle0.findUpperRight() == Vector2I(0, 0));

        Rectangle rectangle1(Vector2I{0, 0}, Vector2I{1, 1});
        REQUIRE(rectangle1.findLowerRight() == Vector2I(1, 1));
        REQUIRE(rectangle1.findLowerLeft() == Vector2I(0, 1));
        REQUIRE(rectangle1.findUpperRight() == Vector2I(1, 0));

        Rectangle rectangle2(Vector2I{1, 2}, Vector2I{1, 2});
        REQUIRE(rectangle2.findLowerRight() == Vector2I(2, 4));
        REQUIRE(rectangle2.findLowerLeft() == Vector2I(1, 4));
        REQUIRE(rectangle2.findUpperRight() == Vector2I(2, 2));
    }

    SECTION("Static functions")
    {
        Rectangle rectangle0;
        REQUIRE(Rectangle::isContainedInside({0, 0}, rectangle0) == true);
        REQUIRE(Rectangle::isContainedInside({0, 1}, rectangle0) == false);

        Rectangle rectangle1(Vector2I{1, 2}, Vector2I{1, 2});
        REQUIRE(Rectangle::isContainedInside({1, 2}, rectangle1) == true);
        REQUIRE(Rectangle::isContainedInside({1, 1}, rectangle1) == false);

        REQUIRE(Rectangle::isContainedInside(rectangle0, rectangle1) == false);
        REQUIRE(Rectangle::isContainedInside(rectangle1, rectangle0) == false);

        Rectangle rectangle2(Vector2I{1, 1}, Vector2I{10, 20});
        REQUIRE(Rectangle::isContainedInside(rectangle1, rectangle2) == true);
        REQUIRE(Rectangle::isContainedInside(rectangle2, rectangle1) == false);


        Vector2I size = Rectangle::findSize({1, 2}, {2, 4});
        REQUIRE(size == Vector2I{1, 2});

    }

    SECTION("Operators")
    {
        Rectangle rectangle1(0, 1, 2, 3);
        Rectangle rectangle2(0, 1, 2, 3);
        Rectangle rectangle3(100, 101, 202, 203);
        Rectangle rectangle4(100, 101, 2, 3);
        SECTION("Comparison")
        {
            REQUIRE(rectangle1 == rectangle1);
            REQUIRE(rectangle1 == rectangle2);
            REQUIRE(rectangle1 != rectangle3);
            REQUIRE(rectangle3 != rectangle4);
        }

        SECTION("Stream insert/extract")
        {
            std::stringstream strStream;
            strStream << rectangle1;
            REQUIRE(strStream.str() == "((0, 1), (2, 3))");

            Rectangle rectangle;
            strStream.str("0 1 2 3");
            strStream >> rectangle;
            REQUIRE((rectangle.upperLeftCorner == Vector2I(0, 1) and rectangle.size == Vector2I(2, 3)));
        }

        SECTION("Translation")
        {
            Rectangle result = rectangle1 + Vector2I(10, 20);
            REQUIRE(result == Rectangle(10, 21, 2, 3));
            REQUIRE(result == Vector2I(10, 20) + rectangle1);

            result = rectangle4 - Vector2I(100, 100);
            REQUIRE(result == rectangle1);
        }

        SECTION("Intersection")
        {
            Rectangle result = rectangle1 & rectangle2;
            REQUIRE(result == rectangle1);

            Rectangle rectangleLocal1(0, 0, 10, 10);
            Rectangle rectangleLocal2(5, 5, 10, 10);
            result = rectangleLocal1 & rectangleLocal2;
            REQUIRE(result == Rectangle(5, 5, 5, 5));

            Rectangle rectangleLocal3(5, 5, 10, 10);
            Rectangle rectangleLocal4(10, 10, 10, 10);
            result = rectangleLocal3 & rectangleLocal4;
            REQUIRE(result == Rectangle(10, 10, 5, 5));


            Rectangle rectangleLocal5(5, 5, 10, 10);
            Rectangle rectangleLocal6(10, 10, 100, 100);
            result = rectangleLocal5 & rectangleLocal6;
            REQUIRE(result == Rectangle(10, 10, 5, 5));


            Rectangle rectangleLocal7(5, 5, 4, 4);
            Rectangle rectangleLocal8(10, 10, 100, 100);
            result = rectangleLocal7 & rectangleLocal8;
            REQUIRE(result == Rectangle(-1, -1, -1, -1));

            Rectangle rectangleLocal9(0, 0, 5, 5);
            Rectangle rectangleLocal10(0, 4, 5, 5);
            result = rectangleLocal9 & rectangleLocal10;
            REQUIRE(result == Rectangle(0, 4, 5, 1));
        }

    }
}