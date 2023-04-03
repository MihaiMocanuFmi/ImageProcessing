#include <catch2/catch_all.hpp>

#include "Processing/ContrastBrightness.h"


TEST_CASE("Contrast and Brightness", "[ContrastBrightness]")
{
    SECTION("Creation")
    {
        SECTION("Default")
        {
            ContrastBrightness cb;
            REQUIRE(cb.getAlpha() == 1);
            REQUIRE(cb.getBeta() == 0);
        }

        SECTION("Parameter")
        {
            ContrastBrightness cb(10, 20);
            REQUIRE(cb.getAlpha() == 10);
            REQUIRE(cb.getBeta() == 20);

            ContrastBrightness cb2(0, -20);
            REQUIRE((cb2.getAlpha() > 0 and cb2.getAlpha() < 0.001));
            REQUIRE(cb2.getBeta() == -20);
        }


        SECTION("Process")
        {
            Image src(ColorData({10, 10}, tools::RgbColor(127, 50, 200)));
            Image dst;
            ContrastBrightness cb(1, 0);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{127, 50, 200});

            cb = ContrastBrightness(1, 60);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{127 + 60, 50 + 60, 200 + 60});

            cb = ContrastBrightness(2, 60);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{2 * 127 + 60, 2 * 50 + 60, 2 * 200 + 60});

        }


    }
}