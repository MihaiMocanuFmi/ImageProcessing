#include <catch2/catch_all.hpp>
#include <catch2/catch_all.hpp>

#include "Processing/Gamma.h"


TEST_CASE("Gamma", "[Gamma]")
{
    SECTION("Creation")
    {
        SECTION("Default")
        {
            Gamma gamma;
            REQUIRE(gamma.getGamma() == 1);
        }

        SECTION("Parameter")
        {
            Gamma gamma(2);
            REQUIRE(gamma.getGamma() == 2);

            Gamma cb2(-2);
            REQUIRE((cb2.getGamma() > 0 and cb2.getGamma() < 0.001));
        }


        SECTION("Process")
        {
            Image src(ColorData({10, 10}, tools::RgbColor(127, 50, 200)));
            Image dst;
            Gamma cb(1);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{127, 50, 200});

            cb = Gamma(0);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{0, 0, 0});

            src = Image(ColorData({10, 10}, tools::RgbColor(255, 128, 64)));
            cb.setGamma(0.44);
            cb.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{255, 53, 11});

        }


    }
}