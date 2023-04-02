#include <catch2/catch_all.hpp>

#include "../Libs/Tools/RgbColor.h"



TEST_CASE( "Color", "[Color]")
{
    using namespace tools;
    SECTION("Creation")
    {
        Color color;
        REQUIRE((color.R == 0 and color.G == 0 and color.B == 0));

        color = Color(100, 500, -100);
        REQUIRE((color.R == 100 and color.G == 500 and color.B == -100));
    }

    SECTION("Operators")
    {
        Color color1(100, 200, 300);
        Color color2(100, 200, 300);
        Color color3(1, 2, 3);

        REQUIRE((color1 == color2));
        REQUIRE((color1 != color3));
    }
}

TEST_CASE("RgbColor", "[Color]")
{
    using namespace tools;
    SECTION("Creation")
    {
        RgbColor color0;
        REQUIRE((color0.getColorR() == 0 and color0.getColorG() == 0 and color0.getColorB() == 0));
        REQUIRE(color0.MAX_VALUE == 255);

        RgbColor color1(255, 127, 63);
        REQUIRE((color1.getColorR() == 255 and color1.getColorG() == 127 and color1.getColorB() == 63));

        RgbColor color2(400, 500, -100);
        REQUIRE((color2.getColorR() == 255 and color2.getColorG() == 255 and color2.getColorB() == 0));

        RgbColor color3(400, 500, -100, true);
        REQUIRE((color3.getColorR() == 400 and color3.getColorG() == 500 and color3.getColorB() == -100));

        REQUIRE(color3.getColor() == Color(400, 500, -100));

        RgbColor color4(Color(400, 500, -100), true);
        REQUIRE((color4.getColorR() == 400 and color4.getColorG() == 500 and color4.getColorB() == -100));

        RgbColor color5(Color(255, 127, 63));
        REQUIRE((color5.getColorR() == 255 and color5.getColorG() == 127 and color5.getColorB() == 63));

    }

    SECTION("Setters")
    {
        RgbColor color0;

        color0.setColor(100, 50, 25);
        REQUIRE((color0.getColorR() == 100 and color0.getColorG() == 50 and color0.getColorB() == 25));

        color0.setColor({125, 125, 125});
        REQUIRE((color0.getColorR() == 125 and color0.getColorG() == 125 and color0.getColorB() == 125));

        //checking clamping
        color0.setColor(400, 500, -100);
        REQUIRE((color0.getColorR() == 255 and color0.getColorG() == 255 and color0.getColorB() == 0));

        //checking clamping override
        color0.setColor(400, 500, -100, true);
        REQUIRE((color0.getColorR() == 400 and color0.getColorG() == 500 and color0.getColorB() == -100));


    }

    SECTION("Operators")
    {
        RgbColor color1(200, 202, 204);
        RgbColor color2(100, 101, 102);
        RgbColor color3(0, 1, 2);
        RgbColor color4(-100, -101, -402, true);

        SECTION("Comparison")
        {
            RgbColor colorTemp(100, 101, 102);
            REQUIRE((color2 == colorTemp));

            REQUIRE((color1 == color1));

            REQUIRE((color1 != color2));

        }

        SECTION("Addition")
        {
            RgbColor result = color1 + color2;
            REQUIRE(result.getColor() == Color(255, 255, 255));
            result = color2 + color1;
            REQUIRE(result.getColor() == Color(255, 255, 255));

            result = color1.add(color2, true);
            REQUIRE(result.getColor() == Color(300, 303, 306));

            result = color2.add(color1, true);
            REQUIRE(result.getColor() == Color(300, 303, 306));

            result = color1 + color3;
            REQUIRE(result.getColor() == Color(200, 203, 206));

            result = color1 + color4;
            REQUIRE(result.getColor() == Color(100, 101, 0));

            result = color3 + color4;
            REQUIRE(result.getColor() == Color(0, 0, 0));
        }

        SECTION("Scalar addition")
        {
            float scalar = 40;
            RgbColor result = color1 + scalar;
            REQUIRE(result == RgbColor(240, 242, 244));
            REQUIRE((color1 + scalar == scalar + color1));

            scalar = 100;
            result = color1 + scalar;
            REQUIRE(result == RgbColor(255, 255, 255));
            REQUIRE((color1 + scalar == scalar + color1));

            result = add(scalar, color1, true);
            REQUIRE(result == RgbColor(300, 302, 304, true));

            scalar = -100;
            result = color1 + scalar;
            REQUIRE(result == RgbColor(100, 102, 104));
            REQUIRE((color1 + scalar == scalar + color1));

            scalar = -300;
            result = color1 + scalar;
            REQUIRE(result == RgbColor(0, 0, 0));
            REQUIRE((color1 + scalar == scalar + color1));
        }

        SECTION("Subtract")
        {
            RgbColor result = color1 - color2;
            REQUIRE((result == RgbColor(100, 101, 102)));


            result = color2 - color1;
            REQUIRE((result == RgbColor(0, 0, 0)));

            result = color2.subtract(color1, true);
            REQUIRE((result == RgbColor(-100, -101, -102, true)));
        }

        SECTION("Scalar Subtract")
        {
            float scalar = 100;
            RgbColor result = color1 - scalar;
            REQUIRE(result == RgbColor(100, 102, 104));

            scalar = 300;
            result = color1 - scalar;
            REQUIRE(result == RgbColor(0, 0, 0));

            result = subtract(color1, scalar, true);
            REQUIRE(result == RgbColor(-100, -98, -96, true));

            scalar = -100;
            result = color1 - scalar;
            REQUIRE(result == RgbColor(255, 255, 255));

            scalar = -40;
            result = color1 - scalar;
            REQUIRE(result == RgbColor(240, 242, 244));
        }

        SECTION("Multiply")
        {
            RgbColor result = color1 * color3;
            REQUIRE(result == RgbColor(0, 202, 255));
            result = color3 * color1;
            REQUIRE(result == RgbColor(0, 202, 255));

            result = color1 * color4;
            REQUIRE(result == RgbColor(0, 0, 0));

            result = color1.multiply(color4, true);
            REQUIRE(result == RgbColor(200 * (-100), 202 * -(101), 204 * (-402), true));
        }

        SECTION("Scalar multiplication")
        {
            float scalar = 1.0f / 2;
            RgbColor result = color1 * scalar;
            REQUIRE(result == RgbColor(100, 101, 102));
            REQUIRE((color1 * scalar == scalar * color1));

            scalar = 100;
            result = color1 * scalar;
            REQUIRE(result == RgbColor(255, 255, 255));
            REQUIRE((color1 * scalar == scalar + color1));

            result = multiply(scalar, color1, true);
            REQUIRE(result == RgbColor(20000, 20200, 20400, true));

            scalar = -100;
            result = color1 * scalar;
            REQUIRE(result == RgbColor(0, 0, 0));
            REQUIRE((color1 * scalar == scalar * color1));

            scalar = 2;
            result = color3 * scalar;
            REQUIRE(result == RgbColor(0, 2, 4));
            REQUIRE((color3 * scalar == scalar * color3));

        }

        SECTION("Stream insertion")
        {
            std::stringstream strStream;
            strStream << color1;
            REQUIRE(strStream.str() == "(200, 202, 204)");
        }

    }
}
