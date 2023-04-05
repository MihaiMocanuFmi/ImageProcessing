#include <catch2/catch_all.hpp>

#include "Image/ImageData.h"


TEST_CASE( "ImageData", "[ImageData]")
{
    SECTION("Creation")
    {
        REQUIRE(ImageData::MAX_VALUE == 255);

        ImageData colorData0;
        REQUIRE(colorData0.size() == tools::Vector2I(0, 0));

        ImageData colorData1({1, 2});
        REQUIRE(colorData1.size() == tools::Vector2I(1, 2));

        ImageData colorData2({2, 2}, tools::RgbColor(255, 100, 50));
        REQUIRE(colorData2.size() == tools::Vector2I(2, 2));

        for (int y = 0; y < colorData2.size().y; ++y)
            for (int x = 0; x < colorData2.size().x; ++x)
                REQUIRE(colorData2.at(x, y) == tools::RgbColor(255, 100, 50));

        colorData0 = colorData2;
        REQUIRE(colorData0.size() == tools::Vector2I(2, 2));
        for (int y = 0; y < colorData0.size().y; ++y)
            for (int x = 0; x < colorData0.size().x; ++x)
                REQUIRE(colorData0.at(x, y) == tools::RgbColor(255, 100, 50));

        ImageData colorData3 = colorData2;
        REQUIRE(colorData3.size() == tools::Vector2I(2, 2));
        for (int y = 0; y < colorData3.size().y; ++y)
            for (int x = 0; x < colorData3.size().x; ++x)
                REQUIRE(colorData3.at(x, y) == tools::RgbColor(255, 100, 50));

        colorData3 = colorData3;
        colorData3 = colorData1;

    }

    SECTION("accessing elements")
    {
        ImageData colorData1({100, 100});

        for (int y = 0; y < 100; ++y)
        {
            for (int x = 0; x < 100; ++x)
            {
                colorData1.at(x, y) = tools::RgbColor(x, y, (x + y)/2);
                REQUIRE(colorData1.at(x, y) == tools::RgbColor(x, y, (x + y)/2));
            }

            tools::RgbColor* row = colorData1.row(y);
            REQUIRE(row == &colorData1.at(0, y));
        }
    }

    SECTION("Resize")
    {
        ImageData colorData2({2, 2}, tools::RgbColor(255, 100, 50));

        //resize with a smaller size shouldn't change the data
        colorData2.resize({1,1});
        REQUIRE(colorData2.size() == tools::Vector2I {2, 2});
        for (int y = 0; y < colorData2.size().y; ++y)
            for (int x = 0; x < colorData2.size().x; ++x)
                REQUIRE(colorData2.at(x, y) == tools::RgbColor(255, 100, 50));

        //resize with a smaller size but a given default element will change the data
        colorData2.resize({1,2}, tools::RgbColor(100, 100, 100));
        REQUIRE(colorData2.size() == tools::Vector2I {1, 2});
        for (int y = 0; y < colorData2.size().y; ++y)
            for (int x = 0; x < colorData2.size().x; ++x)
                REQUIRE(colorData2.at(x, y) == tools::RgbColor(100, 100, 100));


        colorData2.resize({10,10});
        REQUIRE(colorData2.size() == tools::Vector2I {10, 10});
        for (int y = 0; y < 2; ++y)
            for (int x = 0; x < 1; ++x)
                REQUIRE(colorData2.at(x, y) == tools::RgbColor(100, 100, 100));
    }

    SECTION("ROI")
    {
        ImageData colorData1({100, 100}, tools::RgbColor(255, 100, 50));
        tools::Rectangle region(0, 0, 100, 100);
        ImageData output;
        bool result = colorData1.getROI(output, region);

        REQUIRE(result == true);
        REQUIRE(output.size() == tools::Vector2I {100, 100});
        REQUIRE(output.size() == colorData1.size());

        for (int y = 0; y < output.size().y; ++y)
            for (int x = 0; x < output.size().x; ++x)
                REQUIRE(output.at(x, y) == colorData1.at(x, y));

        output = ImageData();
        region = tools::Rectangle(1, 0, 100, 100);
        result = colorData1.getROI(output, region);
        REQUIRE(result == false);
        REQUIRE(output.size() == tools::Vector2I {0, 0});

        output = ImageData();
        region = tools::Rectangle(50, 50, 50, 50);

        for (int y = 50; y < 50 + 50; ++y)
            for (int x = 50; x < 50 + 50; ++x)
                colorData1.at(x, y) = tools::RgbColor(123, 23, 12);

        result = colorData1.getROI(output, region);
        REQUIRE(result == true);
        REQUIRE(output.size() == tools::Vector2I {50, 50});

        for (int y = 0; y < output.size().y; ++y)
            for (int x = 0; x < output.size().x; ++x)
                REQUIRE(output.at(x, y) == tools::RgbColor(123, 23, 12));
    }
    
    SECTION("Operators")
    {
        SECTION("Stream insertion")
        {
            ImageData colorData1({2, 2});

            for (int y = 0; y < colorData1.size().y; ++y)
                for (int x = 0; x < colorData1.size().x; ++x)
                    colorData1.at(x, y) = tools::RgbColor(x, y, x + y);

            std::stringstream strStream;
            strStream << colorData1;

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

        ImageData colorData1({4, 4}, tools::RgbColor(200, 100, 0));
        ImageData colorData2({4, 4}, tools::RgbColor(100, 150, 200));

        ImageData colorData3({5, 5}, tools::RgbColor(100, 150, 200));
        ImageData colorData4({2, 8}, tools::RgbColor(100, 150, 200));

        ImageData colorData5({2, 8}, tools::RgbColor(100, 150, 200));
        ImageData colorData6({4, 4}, tools::RgbColor(255, 250, 200));

        ImageData colorData7({4, 4}, tools::RgbColor(2, 1, -2));

        SECTION("Comparison")
        {
            REQUIRE(colorData1 == colorData1);
            REQUIRE(colorData4 == colorData5);

            REQUIRE(colorData1 != colorData2);
            REQUIRE(colorData2 != colorData3);

            REQUIRE(colorData3 != colorData4);
        }

        SECTION("Addition")
        {
            ImageData result = colorData1 + colorData2;
            REQUIRE(result == colorData6);
            REQUIRE(result == colorData2 + colorData1);

            REQUIRE_THROWS_AS(colorData1 + colorData3, std::runtime_error);
        }

        SECTION("Subtract")
        {
            ImageData result = colorData2 - colorData1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(0, 50, 200)));

            REQUIRE_THROWS_AS(colorData1 - colorData3, std::runtime_error);
        }

        SECTION("Multiply")
        {
            ImageData result = colorData2 * colorData7;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(200, 150, 0)));
            REQUIRE(result == colorData7 * colorData2);

            REQUIRE_THROWS_AS(colorData1 * colorData3, std::runtime_error);
        }

        SECTION("Scalar addition")
        {
            float scalar = 60;
            ImageData result = scalar + colorData1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(255, 160, 60)));
            REQUIRE(result == colorData1 + scalar);

            scalar = -105;
            result = scalar + colorData4;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(0, 45, 95)));
            REQUIRE(result == colorData4 + scalar);
        }

        SECTION("Scalar subtraction")
        {
            float scalar = 60;
            ImageData result = colorData1 - scalar;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(140, 40, 0)));

            scalar = -60;
            result = colorData4 - scalar;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(160, 210, 255)));
        }

        SECTION("Scalar multiplication")
        {
            float scalar = 1.0f/2;
            ImageData result = scalar * colorData1;
            REQUIRE(result == ImageData({4, 4}, tools::RgbColor(100, 50, 0)));
            REQUIRE(result == colorData1 * scalar);

            scalar = -100;
            result = scalar * colorData4;
            REQUIRE(result == ImageData({2, 8}, tools::RgbColor(0, 0, 0)));
            REQUIRE(result == colorData4 * scalar);
        }

    }


}