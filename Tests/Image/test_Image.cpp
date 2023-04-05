#include <catch2/catch_all.hpp>

#include "Image/Image.h"

/// \brief
/// \test
TEST_CASE( "Image", "[Image]")
{
    SECTION("Creation")
    {
        Image image0;
        REQUIRE(image0.size() == tools::Vector2I(0, 0));

        Image image2(tools::Vector2I {2, 3});

        Image image1(ImageData({10, 11}, tools::RgbColor(255, 300, -200)));
        REQUIRE(image1.size() == tools::Vector2I(10, 11));

        for (int y = 0; y < image1.size().y; ++y)
            for (int x = 0; x < image1.size().x; ++x)
                REQUIRE(image1.at(x, y) == tools::RgbColor(255, 255, 0));

        Image image3 = ImageData(tools::Vector2I{5, 6});
        REQUIRE(image3.size() == tools::Vector2I{5, 6});

        Image image4(2, 3);
        REQUIRE(image4.size() == tools::Vector2I(2, 3));

    }

    SECTION("accessing elements")
    {
        Image image1(100, 100);
        Image image2(ImageData({100, 100}, tools::RgbColor(5, 5, 5)));
        const Image &image3 = image2;
        for (int y = 0; y < 100; ++y)
        {
            for (int x = 0; x < 100; ++x)
            {
                image1.at(x, y) = tools::RgbColor(x, y, (x + y) / 2);
                REQUIRE(image1.at(x, y) == tools::RgbColor(x, y, (x + y) / 2));
                REQUIRE(image1.at({x, y}) == tools::RgbColor(x, y, (x + y) / 2));


                //forcing const reference getter
                image1.at({x, y}) = (2.0f) * image3.at({x, y}) + 4.0f;
                CHECK(image1.at(x, y) == tools::RgbColor(2 * 5 + 4, 2 * 5 + 4, 2 * 5 + 4));
            }

            tools::RgbColor* row = image1.row(y);
            REQUIRE(row == &image1.at(0, y));
        }


    }

    SECTION("load save")
    {
        Image image0;
        bool result = image0.load("");
        REQUIRE_FALSE(result);

        image0 = Image(tools::Vector2I{0,0});
        result = image0.save("Test.ppm");
        REQUIRE(result);

        result = image0.load("Test.ppm");
        REQUIRE(result);
    }

    SECTION("ROI")
    {
        Image imageData1(ImageData({100, 100}, tools::RgbColor(255, 100, 50)));
        tools::Rectangle region(0, 0, 100, 100);
        Image output;
        bool result = imageData1.getROI(output, region);

        REQUIRE(result == true);
        REQUIRE(output.size() == tools::Vector2I {100, 100});
        REQUIRE(output.size() == imageData1.size());

        for (int y = 0; y < output.size().y; ++y)
            for (int x = 0; x < output.size().x; ++x)
                REQUIRE(output.at(x, y) == imageData1.at(x, y));

        output = Image();
        region = tools::Rectangle(1, 0, 100, 100);
        result = imageData1.getROI(output, region);
        REQUIRE(result == false);
        REQUIRE(output.size() == tools::Vector2I {0, 0});

        output = Image();
        region = tools::Rectangle(50, 50, 50, 50);

        for (int y = 50; y < 50 + 50; ++y)
            for (int x = 50; x < 50 + 50; ++x)
                imageData1.at(x, y) = tools::RgbColor(123, 23, 12);

        result = imageData1.getROI(output, region);
        REQUIRE(result == true);
        REQUIRE(output.size() == tools::Vector2I {50, 50});

        for (int y = 0; y < output.size().y; ++y)
            for (int x = 0; x < output.size().x; ++x)
                REQUIRE(output.at(x, y) == tools::RgbColor(123, 23, 12));

        result = imageData1.getROI(output, 50, 50, 50, 50);
        REQUIRE(result == true);
        REQUIRE(output.size() == tools::Vector2I {50, 50});

        for (int y = 0; y < output.size().y; ++y)
            for (int x = 0; x < output.size().x; ++x)
                REQUIRE(output.at(x, y) == tools::RgbColor(123, 23, 12));
    }

    SECTION("Helper methods")
    {
        Image image1(ImageData({10, 11}, tools::RgbColor(255, 300, -200)));

        SECTION("Release")
        {
            REQUIRE(image1.size() == tools::Vector2I(10, 11));
            image1.release();
            REQUIRE(image1.size() == tools::Vector2I(0, 0));
        }

        SECTION("Empty")
        {
            REQUIRE_FALSE(image1.isEmpty());
            image1 = Image();
            REQUIRE(image1.isEmpty());

            image1 = ImageData({0, 1});
            REQUIRE(image1.isEmpty());

            image1 = ImageData({1, 0});
            REQUIRE(image1.isEmpty());

            image1 = ImageData({-1, 0});
            REQUIRE(image1.isEmpty());
        }

        SECTION("Data")
        {
            ImageData data = image1.data();

            REQUIRE(data.size() == tools::Vector2I(10, 11));

            for (int y = 0; y < data.size().y; ++y)
                for (int x = 0; x < data.size().x; ++x)
                    REQUIRE(data.at(x, y) == tools::RgbColor(255, 255, 0));
        }
    }

    SECTION("Static")
    {
        SECTION("Zeros")
        {
            Image image = Image::zeros(5, 6);
            REQUIRE(image.size() == tools::Vector2I{5, 6});

            for (int y = 0; y < image.size().y; ++y)
                for (int x = 0; x  < image.size().x; ++x)
                    REQUIRE(image.at(x, y) == tools::RgbColor(0, 0, 0));
        }

        SECTION("Ones")
        {
            Image image = Image::ones(5, 6);
            REQUIRE(image.size() == tools::Vector2I{5, 6});

            for (int y = 0; y < image.size().y; ++y)
                for (int x = 0; x  < image.size().x; ++x)
                    REQUIRE(image.at(x, y) == tools::RgbColor(1, 1, 1));
        }
    }

    SECTION("Operators")
    {
        SECTION("Stream insertion")
        {
            Image image(2, 2);

            for (int y = 0; y < image.size().y; ++y)
                for (int x = 0; x < image.size().x; ++x)
                    image.at(x, y) = tools::RgbColor(x, y, x + y);

            std::stringstream strStream;
            strStream << image;

            int pos = -1;
            //we ignore whitespaces
            for (int y = 0; y < 2; ++y)
            {
                for (int x = 0; x < 2; ++x)
                {
                    pos = strStream.str().find_first_of("0123456789", pos + 1);
                    REQUIRE(strStream.str().at(pos) == ('0' + x));

                    pos = strStream.str().find_first_of("0123456789", pos + 1);
                    REQUIRE(strStream.str().at(pos) == ('0' + y));

                    pos = strStream.str().find_first_of("0123456789", pos + 1);
                    REQUIRE(strStream.str().at(pos) == ('0' + x + y));
                }
            }

        }

        Image image1(ImageData({4, 4}, tools::RgbColor(200, 100, 0)));
        Image image2(ImageData({4, 4}, tools::RgbColor(100, 150, 200)));

        Image image3(ImageData({5, 5}, tools::RgbColor(100, 150, 200)));
        Image image4(ImageData({2, 8}, tools::RgbColor(100, 150, 200)));

        Image image5(ImageData({2, 8}, tools::RgbColor(100, 150, 200)));
        Image image6(ImageData({4, 4}, tools::RgbColor(255, 250, 200)));

        Image image7(ImageData({4, 4}, tools::RgbColor(2, 1, -2)));

        SECTION("Comparison")
        {
            REQUIRE(image1 == image1);
            REQUIRE(image4 == image5);

            REQUIRE(image1 != image2);
            REQUIRE(image2 != image3);

            REQUIRE(image3 != image4);
        }

        SECTION("Addition")
        {
            Image result = image1 + image2;
            REQUIRE(result == image6);
            REQUIRE(result == image2 + image1);

            REQUIRE_THROWS_AS(image1 + image3, std::runtime_error);
        }

        SECTION("Subtract")
        {
            Image result = image2 - image1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(0, 50, 200)));

            REQUIRE_THROWS_AS(image1 - image3, std::runtime_error);
        }

        SECTION("Multiply")
        {
            Image result = image2 * image7;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(200, 150, 0)));
            REQUIRE(result == image7 * image2);

            REQUIRE_THROWS_AS(image1 * image3, std::runtime_error);
        }

        SECTION("Scalar addition")
        {
            float scalar = 60;
            Image result = scalar + image1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(255, 160, 60)));
            REQUIRE(result == image1 + scalar);

            scalar = -105;
            result = scalar + image4;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(0, 45, 95)));
            REQUIRE(result == image4 + scalar);
        }

        SECTION("Scalar subtraction")
        {
            float scalar = 60;
            Image result = image1 - scalar;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(140, 40, 0)));

            scalar = -60;
            result = image4 - scalar;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(160, 210, 255)));
        }

        SECTION("Scalar multiplication")
        {
            float scalar = 1.0f/2;
            Image result = scalar * image1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(100, 50, 0)));
            REQUIRE(result == image1 * scalar);

            scalar = -100;
            result = scalar * image4;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(0, 0, 0)));
            REQUIRE(result == image4 * scalar);
        }

    }


}