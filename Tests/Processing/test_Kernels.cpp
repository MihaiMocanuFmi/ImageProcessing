#include <catch2/catch_all.hpp>

#include "Processing/Kernels.h"

TEST_CASE("Kernels", "[Kernels]")
{
    using namespace Kernels;
    ColorData data0({3, 3}, tools::RgbColor(0, 0, 0));
    ColorData data1({3, 3}, tools::RgbColor(1, 1, 1));
    ColorData data255({3, 3}, tools::RgbColor(255, 255, 255));


    SECTION("Basic Type")
    {
        SECTION("Method")
        {
            ColorData copy = data0;
            KernelType::scalingMethod(copy);
            REQUIRE(copy == data0);

            copy = data1;
            KernelType::scalingMethod(copy);
            REQUIRE(copy == data1);

            copy = data255;
            KernelType::scalingMethod(copy);
            REQUIRE(copy == data255);
        }
    }

    SECTION("MeanBlur Type")
    {
        SECTION("Kernel")
        {
            ColorData kernel = MeanBlurKernel().kernel;
            REQUIRE(kernel.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < kernel.size().y; ++y)
                for (int x = 0; x < kernel.size().x; ++x)
                    REQUIRE(kernel.at(x, y) == tools::RgbColor(1, 1, 1));
        }
        SECTION("Method")
        {
            //divide by 9
            MeanBlurKernel::scalingMethod(data0);
            REQUIRE(data0.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data0.size().y; ++y)
                for (int x = 0; x < data0.size().x; ++x)
                    REQUIRE(data0.at(x, y) == tools::RgbColor(0, 0, 0));

            MeanBlurKernel::scalingMethod(data1);
            REQUIRE(data1.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data1.size().y; ++y)
                for (int x = 0; x < data1.size().x; ++x)
                    REQUIRE(data1.at(x, y) == tools::RgbColor(0, 0, 0));

            MeanBlurKernel::scalingMethod(data255);
            REQUIRE(data255.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data255.size().y; ++y)
                for (int x = 0; x < data255.size().x; ++x)
                    REQUIRE(data255.at(x, y) == tools::RgbColor(255/9, 255/9, 255/9));
        }
    }


    SECTION("GaussianBlur Type")
    {
        SECTION("Kernel")
        {
            ColorData kernel = GaussianBlur3x3Kernel().kernel;
            REQUIRE(kernel.size() == tools::Vector2I{3, 3});

            REQUIRE(kernel.at(0, 0) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(1, 0) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(2, 0) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(0, 1) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(1, 1) == tools::RgbColor(4, 4, 4));
            REQUIRE(kernel.at(2, 1) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(0, 2) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(1, 2) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(2, 2) == tools::RgbColor(1, 1, 1));
        }
        SECTION("Method")
        {
            //divide by 16
            GaussianBlur3x3Kernel::scalingMethod(data0);
            REQUIRE(data0.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data0.size().y; ++y)
                for (int x = 0; x < data0.size().x; ++x)
                    REQUIRE(data0.at(x, y) == tools::RgbColor(0, 0, 0));

            GaussianBlur3x3Kernel::scalingMethod(data1);
            REQUIRE(data1.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data1.size().y; ++y)
                for (int x = 0; x < data1.size().x; ++x)
                    REQUIRE(data1.at(x, y) == tools::RgbColor(0, 0, 0));

            GaussianBlur3x3Kernel::scalingMethod(data255);
            REQUIRE(data255.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data255.size().y; ++y)
                for (int x = 0; x < data255.size().x; ++x)
                    REQUIRE(data255.at(x, y) == tools::RgbColor(255/16, 255/16, 255/16));
        }
    }

    SECTION("HorizontalSobel Type")
    {
        SECTION("Kernel")
        {
            ColorData kernel = HorizontalSobelKernel().kernel;
            REQUIRE(kernel.size() == tools::Vector2I{3, 3});

            REQUIRE(kernel.at(0, 0) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(1, 0) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(2, 0) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(0, 1) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(1, 1) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(2, 1) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(0, 2) == tools::RgbColor(-1, -1, -1, true));
            REQUIRE(kernel.at(1, 2) == tools::RgbColor(-2, -2, -2, true));
            REQUIRE(kernel.at(2, 2) == tools::RgbColor(-1, -1, -1, true));
        }
        SECTION("Method")
        {
            HorizontalSobelKernel::scalingMethod(data0);
            REQUIRE(data0.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data0.size().y; ++y)
                for (int x = 0; x < data0.size().x; ++x)
                    REQUIRE(data0.at(x, y) == tools::RgbColor(127, 127, 127));

            HorizontalSobelKernel::scalingMethod(data1);
            REQUIRE(data1.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data1.size().y; ++y)
                for (int x = 0; x < data1.size().x; ++x)
                    REQUIRE(data1.at(x, y) == tools::RgbColor(127, 127, 127));

            HorizontalSobelKernel::scalingMethod(data255);
            REQUIRE(data255.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data255.size().y; ++y)
                for (int x = 0; x < data255.size().x; ++x)
                    REQUIRE(data255.at(x, y) == tools::RgbColor(159, 159, 159));
            //(255 + 4 * 255) / 8 = 159;
        }
    }

    SECTION("VerticalSobel Type")
    {
        SECTION("Kernel")
        {
            ColorData kernel = VerticalSobelKernel().kernel;
            REQUIRE(kernel.size() == tools::Vector2I{3, 3});

            REQUIRE(kernel.at(0, 0) == tools::RgbColor(-1, -1, -1, true));
            REQUIRE(kernel.at(1, 0) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(2, 0) == tools::RgbColor(1, 1, 1));
            REQUIRE(kernel.at(0, 1) == tools::RgbColor(-2, -2, -2, true));
            REQUIRE(kernel.at(1, 1) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(2, 1) == tools::RgbColor(2, 2, 2));
            REQUIRE(kernel.at(0, 2) == tools::RgbColor(-1, -1, -1, true));
            REQUIRE(kernel.at(1, 2) == tools::RgbColor(0, 0, 0));
            REQUIRE(kernel.at(2, 2) == tools::RgbColor(1, 1, 1));
        }
        SECTION("Method")
        {
            VerticalSobelKernel::scalingMethod(data0);
            REQUIRE(data0.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data0.size().y; ++y)
                for (int x = 0; x < data0.size().x; ++x)
                    REQUIRE(data0.at(x, y) == tools::RgbColor(127, 127, 127));

            VerticalSobelKernel::scalingMethod(data1);
            REQUIRE(data1.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data1.size().y; ++y)
                for (int x = 0; x < data1.size().x; ++x)
                    REQUIRE(data1.at(x, y) == tools::RgbColor(127, 127, 127));

            VerticalSobelKernel::scalingMethod(data255);
            REQUIRE(data255.size() == tools::Vector2I{3, 3});
            for (int y = 0; y < data255.size().y; ++y)
                for (int x = 0; x < data255.size().x; ++x)
                    REQUIRE(data255.at(x, y) == tools::RgbColor(159, 159, 159));
            //(255 + 4 * 255) / 8 = 159;
        }
    }
}