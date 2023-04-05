#include <catch2/catch_all.hpp>

#include "Processing/Convolution.h"

namespace tests
{
    void __scaleConvolution(ImageData &colorData)
    {
        for (int y = 0; y < colorData.size().y; ++y)
            for (int x = 0; x < colorData.size().x; ++x)
                colorData.at(x, y) = 2.0f * colorData.at(x, y);
    }
}

TEST_CASE("Convolution", "[Convolution]")
{

    SECTION("Creation")
    {
        SECTION("Default")
        {
            Convolution convolution;
            REQUIRE(convolution.getKernel().size() == tools::Vector2I{3, 3});
            for (int y = 0; y < convolution.getKernel().size().y; ++y)
                for (int x = 0; x < convolution.getKernel().size().x; ++x)
                    if (x == 1 and y == 1)
                        REQUIRE(convolution.getKernel().at(x, y) == tools::RgbColor(1, 1, 1));
                    else
                        REQUIRE(convolution.getKernel().at(x, y) == tools::RgbColor(0, 0, 0));

            auto scalingMethodPointer = convolution.getScalingMethod();
            ImageData data({6, 6}, tools::RgbColor(100, 200, 50));
            scalingMethodPointer(data);
            REQUIRE(data.size() == tools::Vector2I{6, 6});

            for (int y = 0; y < convolution.getKernel().size().y; ++y)
                for (int x = 0; x < convolution.getKernel().size().x; ++x)
                    REQUIRE(data.at(x, y) == tools::RgbColor(100, 200, 50));
        }

        SECTION("Parameter")
        {

            Convolution convolution(ImageData({1, 1}, tools::RgbColor(177, 177, 177)),
                                    nullptr);
            REQUIRE(convolution.getKernel().size() == tools::Vector2I {1, 1});
            REQUIRE(convolution.getKernel().at(0, 0) == tools::RgbColor{177, 177, 177});
        }

        SECTION("Getters")
        {
            Convolution convolution(ImageData({1, 1}, tools::RgbColor(177, 177, 177)),
                                    nullptr);
            REQUIRE(convolution.getKernel().size() == tools::Vector2I{1, 1});
            REQUIRE(convolution.getKernel().at(0, 0) == tools::RgbColor{177, 177, 177});

            REQUIRE(convolution.getScalingMethod() == nullptr);
        }

        SECTION("Process")
        {
            Convolution convolution;
            convolution.getScalingMethod() = tests::__scaleConvolution;
            REQUIRE(convolution.getKernel().size() == tools::Vector2I {3, 3});

            Image src(ImageData({10, 10}, tools::RgbColor(127, 50, 200)));
            Image dst;
            convolution.process(src, dst);

            REQUIRE(dst.size() == tools::Vector2I{10, 10});
            for (int y = 0; y < 10; ++y)
                for (int x = 0; x < 10; ++x)
                    REQUIRE(dst.at(x, y) == tools::RgbColor{254, 100, 255});
        }


    }
}