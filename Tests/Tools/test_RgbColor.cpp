#include <catch2/catch_all.hpp>

#include "../Libs/Tools/RgbColor.h"

using namespace tools;

TEST_CASE( "RgbColor Creation", "[RgbColor]")
{
    RgbColor color0;
    REQUIRE((color0.getColorR() == 0 and color0.getColorG() == 0 and color0.getColorB() == 0));
    REQUIRE(color0.getMaxValue() == std::numeric_limits<int>::max());

    RgbColor color1({255, 127, 63});
    REQUIRE((color1.getColorR() == 255 and color1.getColorG() == 127 and color1.getColorB() == 63));
    REQUIRE(color1.getMaxValue() == std::numeric_limits<int>::max());

    RgbColor color2(255);
    REQUIRE((color2.getColorR() == 0 and color2.getColorG() == 0 and color2.getColorB() == 0));
    REQUIRE(color2.getMaxValue() == 255);

    RgbColor color3(255, {255, 127, 63});
    REQUIRE((color3.getColorR() == 255 and color3.getColorG() == 127 and color3.getColorB() == 63));
    REQUIRE(color3.getMaxValue() == 255);

    RgbColor color4(255, 255, 127, 63);
    REQUIRE((color4.getColorR() == 255 and color4.getColorG() == 127 and color4.getColorB() == 63));
    REQUIRE(color4.getMaxValue() == 255);

    RgbColor implicitConversion(color1);
    REQUIRE((implicitConversion.getColorR() == 255 and implicitConversion.getColorG() == 127
            and implicitConversion.getColorB() == 63));
    REQUIRE(implicitConversion.getMaxValue() == std::numeric_limits<int>::max());

}

TEST_CASE( "RgbColor Setters", "[RgbColor]")
{
    RgbColor color0;
    color0.setMaxValue(125);
    REQUIRE(color0.getMaxValue() == 125);

    color0.setColor({100, 50, 25});
    REQUIRE((color0.getColorR() == 100 and color0.getColorG() == 50 and color0.getColorB() == 25));

    color0.setColor({125, 125, 125});
    REQUIRE((color0.getColorR() == 125 and color0.getColorG() == 125 and color0.getColorB() == 125));

    //checking clamping when smaller
    color0.setColor({-126, -126, -126});
    REQUIRE((color0.getColorR() == 0 and color0.getColorG() == 0 and color0.getColorB() == 0));

    //checking clamping when bigger
    color0.setColor({126, 126, 126});
    REQUIRE((color0.getColorR() == 125 and color0.getColorG() == 125 and color0.getColorB() == 125));

    //setting maxValue to a smaller value should reclamp color values
    color0.setMaxValue(50);
    REQUIRE((color0.getColorR() == 50 and color0.getColorG() == 50 and color0.getColorB() == 50));


    //checking the component overload of setColor
    color0.setColor(40, 40, 40);
    REQUIRE((color0.getColorR() == 40 and color0.getColorG() == 40 and color0.getColorB() == 40));
}

TEST_CASE( "RgbColor Operators", "[RgbColor]")
{
    RgbColor color1(255, {200, 202, 204});
    RgbColor color2(127, {100, 101, 102});
    RgbColor color3(127, {0, 1, 2});

    SECTION( "Addition")
    {
        RgbColor temp = color1 + color2;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        temp = color2 + color3;
        REQUIRE(temp.getMaxValue() == 127);
        REQUIRE((temp.getColorR() == 100 and temp.getColorG() == 102 and temp.getColorB() == 104));
    }

    SECTION( "Scalar addition")
    {
        RgbColor temp = color1 + 25;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 225 and temp.getColorG() == 227 and temp.getColorB() == 229));

        //checking commutativity;
        temp = 25 + color1;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 225 and temp.getColorG() == 227 and temp.getColorB() == 229));

        //checking clamping
        temp = color1 + 100;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        //checking commutativity;
        temp = 100 + color1;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        //checking float behaviour;
        temp = color1 + 25.9;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 225 and temp.getColorG() == 227 and temp.getColorB() == 229));
    }

    SECTION( "Subtract")
    {
        RgbColor temp = color1 - color2;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 100 and temp.getColorG() == 101 and temp.getColorB() == 102));

        temp = color2 - color3;
        REQUIRE(temp.getMaxValue() == 127);
        REQUIRE((temp.getColorR() == 100 and temp.getColorG() == 100 and temp.getColorB() == 100));

        temp = color3 - color2;
        REQUIRE(temp.getMaxValue() == 127);
        REQUIRE((temp.getColorR() == 0 and temp.getColorG() == 0 and temp.getColorB() == 0));
    }

    SECTION( "Scalar Subtract")
    {
        RgbColor temp = color1 - 25;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 200 - 25 and temp.getColorG() == 202 - 25 and temp.getColorB() == 204 - 25));

        //checking clamping
        temp = color1 - 201;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 0 and temp.getColorG() == 1 and temp.getColorB() == 3));

        //checking float behaviour;
        temp = color1 - 0.5;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 199 and temp.getColorG() == 201 and temp.getColorB() == 203));
    }

    SECTION( "Multiply")
    {
        RgbColor temp = color1 * color2;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        temp = color1 * color3;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 0 and temp.getColorG() == 202 and temp.getColorB() == 255));

        temp = color2 * color3;
        REQUIRE(temp.getMaxValue() == 127);
        REQUIRE((temp.getColorR() == 0 and temp.getColorG() == 101 and temp.getColorB() == 127));
    }

    SECTION( "Scalar multiplication")
    {
        RgbColor temp = color1 * 0.5;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 100 and temp.getColorG() == 101 and temp.getColorB() == 102));

        //checking commutativity;
        temp = 0.5 * color1;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 100 and temp.getColorG() == 101 and temp.getColorB() == 102));

        //checking upper clamping
        temp = color1 * 100;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        //checking commutativity;
        temp = 100 * color1;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 255 and temp.getColorG() == 255 and temp.getColorB() == 255));

        //checking lower clamping behaviour;
        temp = color1 * -1;
        REQUIRE(temp.getMaxValue() == 255);
        REQUIRE((temp.getColorR() == 0 and temp.getColorG() == 0 and temp.getColorB() == 0));
    }

    SECTION("ostream")
    {
        std::stringstream strStream;
        strStream << color1;
        REQUIRE( strStream.str() == "(200, 202, 204)");
    }
}

