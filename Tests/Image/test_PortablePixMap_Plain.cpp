#include <catch2/catch_all.hpp>

#include "Image/PortablePixMap_Plain.h"

TEST_CASE("PPM", "[PPM]")
{
    SECTION("Load")
    {
        SECTION("PBM normal")
        {
            std::string file = "P1\n"
                               "# This is an example bitmap of the letter \"J\"\n"
                               "6 10\n"
                               "0 0 0 0 1 0\n"
                               "0 0 0 0 1 0\n"
                               "0 0 0 0 1 0\n"
                               "0 0 0 0 1 0\n"
                               "0 0 0 0 1 0\n"
                               "0 0 0 0 1 0\n"
                               "1 0 0 0 1 0\n"
                               "0 1 1 1 0 0\n"
                               "0 0 0 0 0 0\n"
                               "0 0 0 0 0 0";

            PortablePixMap_Plain pbm;
            ColorData data;
            bool result = pbm.loadPlain(file, data);
            REQUIRE(result == true);

            REQUIRE(data.size() == tools::Vector2I{6, 10});
            REQUIRE(data.at(0, 0) == tools::RgbColor(0, 0, 0));
            REQUIRE(data.at(4, 0) == tools::RgbColor(255, 255, 255));
            REQUIRE(data.at(4, 1) == tools::RgbColor(255, 255, 255));
            REQUIRE(data.at(5, 9) == tools::RgbColor(0, 0, 0));
            REQUIRE(data.at(0, 6) == tools::RgbColor(255, 255, 255));

            SECTION("Size too big")
            {
                file = "P1          # \"P3\" means this is a RGB color image in ASCII\n"
                       "30 20          # \"3 2\" is the width and height of the image in pixels\n"
                       "         # \"255\" is the maximum value for each color\n"
                       "# The part above is the header\n"
                       "# The part below is the image data: RGB triplets\n"
                       "255   0   0  # red\n"
                       "  0 255   0  # green\n"
                       "  0   0 255  # blue\n"
                       "255 255   0  # yellow\n"
                       "255 255 255  # white\n"
                       "  0   0   0  # black";

                data = ColorData();
                result = pbm.loadPlain(file, data);
                REQUIRE(result == false);
                REQUIRE(data.size() == tools::Vector2I{0, 0});
            }

        }

            /*SECTION("PBM one-line")
            {
                //It doesnt support one liners

                std::string file = "P1\n"
                                   "# This is an example bitmap of the letter \"J\"\n"
                                   "6 10\n"
                                   "000010000010000010000010000010000010100010011100000000000000";

                PortablePixMap_Plain pbm;
                ColorData data;
                pbm.loadPlain(file, data);

                CHECK(data.size() == tools::Vector2I{6, 10});
                CHECK(data.at(0, 0) == tools::RgbColor(0, 0, 0));
                CHECK(data.at(4, 0) == tools::RgbColor(255, 255, 255));
                CHECK(data.at(4, 1) == tools::RgbColor(255, 255, 255));
                CHECK(data.at(5, 9) == tools::RgbColor(0, 0, 0));
                CHECK(data.at(0, 6) == tools::RgbColor(255, 255, 255));

            }  */



        SECTION("PGM")
        {
            std::string file = "P2\n"
                               "# Shows the word \"FEEP\" (example from Netpbm man page on PGM)\n"
                               "24 7\n"
                               "15\n"
                               "0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0\n"
                               "0  3  3  3  3  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15 15 15 15  0\n"
                               "0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0 15  0\n"
                               "0  3  3  3  0  0  0  7  7  7  0  0  0 11 11 11  0  0  0 15 15 15 15  0\n"
                               "0  3  0  0  0  0  0  7  0  0  0  0  0 11  0  0  0  0  0 15  0  0  0  0\n"
                               "0  3  0  0  0  0  0  7  7  7  7  0  0 11 11 11 11  0  0 15  0  0  0  0\n"
                               "0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0";

            PortablePixMap_Plain pgm;
            ColorData data;
            bool result = pgm.loadPlain(file, data);
            REQUIRE(result == true);

            REQUIRE(data.size() == tools::Vector2I{24, 7});
            REQUIRE(data.at(0, 0) == tools::RgbColor(0, 0, 0));
            REQUIRE(data.at(23, 6) == tools::RgbColor(0, 0, 0));

            REQUIRE(data.at(1, 1) == tools::RgbColor(3 * 255 / 15, 3 * 255 / 15, 3 * 255 / 15));
            REQUIRE(data.at(2, 1) == tools::RgbColor(3 * 255 / 15, 3 * 255 / 15, 3 * 255 / 15));
            REQUIRE(data.at(1, 2) == tools::RgbColor(3 * 255 / 15, 3 * 255 / 15, 3 * 255 / 15));

            REQUIRE(data.at(7, 1) == tools::RgbColor(7 * 255 / 15, 7 * 255 / 15, 7 * 255 / 15));
            REQUIRE(data.at(8, 1) == tools::RgbColor(7 * 255 / 15, 7 * 255 / 15, 7 * 255 / 15));
            REQUIRE(data.at(7, 2) == tools::RgbColor(7 * 255 / 15, 7 * 255 / 15, 7 * 255 / 15));

            SECTION("Size too big")
            {
                file = "P2          # \"P3\" means this is a RGB color image in ASCII\n"
                       "30 20          # \"3 2\" is the width and height of the image in pixels\n"
                       "255          # \"255\" is the maximum value for each color\n"
                       "# The part above is the header\n"
                       "# The part below is the image data: RGB triplets\n"
                       "255   0   0  # red\n"
                       "  0 255   0  # green\n"
                       "  0   0 255  # blue\n"
                       "255 255   0  # yellow\n"
                       "255 255 255  # white\n"
                       "  0   0   0  # black";

                data = ColorData();
                result = pgm.loadPlain(file, data);
                REQUIRE(result == false);
                REQUIRE(data.size() == tools::Vector2I{0, 0});
            }

        }

        SECTION("PPM")
        {
            std::string file = "P3           # \"P3\" means this is a RGB color image in ASCII\n"
                               "3 2          # \"3 2\" is the width and height of the image in pixels\n"
                               "255          # \"255\" is the maximum value for each color\n"
                               "# The part above is the header\n"
                               "# The part below is the image data: RGB triplets\n"
                               "255   0   0  # red\n"
                               "  0 255   0  # green\n"
                               "  0   0 255  # blue\n"
                               "255 255   0  # yellow\n"
                               "255 255 255  # white\n"
                               "  0   0   0  # black";

            PortablePixMap_Plain ppm;
            ColorData data;
            bool result = ppm.loadPlain(file, data);
            REQUIRE(result == true);

            REQUIRE(data.size() == tools::Vector2I{3, 2});
            REQUIRE(data.at(0, 0) == tools::RgbColor(255, 0, 0));
            REQUIRE(data.at(1, 0) == tools::RgbColor(0, 255, 0));
            REQUIRE(data.at(2, 0) == tools::RgbColor(0, 0, 255));
            REQUIRE(data.at(0, 1) == tools::RgbColor(255, 255, 0));
            REQUIRE(data.at(1, 1) == tools::RgbColor(255, 255, 255));
            REQUIRE(data.at(2, 1) == tools::RgbColor(0, 0, 0));

            SECTION("Size too big")
            {
                file = "P3           # \"P3\" means this is a RGB color image in ASCII\n"
                       "30 20          # \"3 2\" is the width and height of the image in pixels\n"
                       "255          # \"255\" is the maximum value for each color\n"
                       "# The part above is the header\n"
                       "# The part below is the image data: RGB triplets\n"
                       "255   0   0  # red\n"
                       "  0 255   0  # green\n"
                       "  0   0 255  # blue\n"
                       "255 255   0  # yellow\n"
                       "255 255 255  # white\n"
                       "  0   0   0  # black";

                data = ColorData();
                result = ppm.loadPlain(file, data);
                REQUIRE(result == false);
                REQUIRE(data.size() == tools::Vector2I{0, 0});
            }
        }

        SECTION("No magic number")
        {
            std::string file = "           # \"P3\" means this is a RGB color image in ASCII\n"
                               "3 2          # \"3 2\" is the width and height of the image in pixels\n"
                               "255          # \"255\" is the maximum value for each color\n"
                               "# The part above is the header\n"
                               "# The part below is the image data: RGB triplets\n"
                               "255   0   0  # red\n"
                               "  0 255   0  # green\n"
                               "  0   0 255  # blue\n"
                               "255 255   0  # yellow\n"
                               "255 255 255  # white\n"
                               "  0   0   0  # black";

            PortablePixMap_Plain ppm;
            ColorData data;
            bool result = ppm.loadPlain(file, data);
            REQUIRE(result == false);
            REQUIRE(data.size() == tools::Vector2I{0, 0});
        }

        SECTION("No maxValue")
        {
            std::string file = "P3         # \"P3\" means this is a RGB color image in ASCII\n"
                               "3 2          # \"3 2\" is the width and height of the image in pixels\n";


            PortablePixMap_Plain ppm;
            ColorData data;
            bool result = ppm.loadPlain(file, data);
            REQUIRE(result == false);
            REQUIRE(data.size() == tools::Vector2I{0, 0});
        }

        SECTION("No size")
        {
            std::string file = "P3         # \"P3\" means this is a RGB color image in ASCII\n"
                               "         # \"3 2\" is the width and height of the image in pixels\n";


            PortablePixMap_Plain ppm;
            ColorData data;
            bool result = ppm.loadPlain(file, data);
            REQUIRE(result == false);
            REQUIRE(data.size() == tools::Vector2I{0, 0});
        }

        SECTION("Wrong magic number")
        {
            std::string file = "P5           # \"P3\" means this is a RGB color image in ASCII\n"
                               "3 2          # \"3 2\" is the width and height of the image in pixels\n"
                               "255          # \"255\" is the maximum value for each color\n"
                               "# The part above is the header\n"
                               "# The part below is the image data: RGB triplets\n"
                               "255   0   0  # red\n"
                               "  0 255   0  # green\n"
                               "  0   0 255  # blue\n"
                               "255 255   0  # yellow\n"
                               "255 255 255  # white\n"
                               "  0   0   0  # black";

            PortablePixMap_Plain ppm;
            ColorData data;
            bool result = ppm.loadPlain(file, data);
            REQUIRE(result == false);
            REQUIRE(data.size() == tools::Vector2I{0, 0});
        }

    }

    SECTION("Save")
    {
        ColorData data({3, 2});
        data.at(0, 0) = tools::RgbColor(255, 0, 0);
        data.at(1, 0) = tools::RgbColor(0, 255, 0);
        data.at(2, 0) = tools::RgbColor(0, 0, 255);
        data.at(0, 1) = tools::RgbColor(255, 255, 0);
        data.at(1, 1) = tools::RgbColor(255, 255, 255);
        data.at(2, 1) = tools::RgbColor(0, 0, 0);

        PortablePixMap_Plain ppm;
        std::string output;
        bool result = ppm.saveToString(output, data);
        REQUIRE(result == true);

        REQUIRE(output == "P3\t"
                          "#Magic Number\n"
                          "3 2\t#Size width and height\n"
                          "255\t#Max color value\n"
                          "\n"
                          "255 0 0 0 255 0 0 0 255 \n"
                          "255 255 0 255 255 255 0 0 0 ");


        data = ColorData({100, 100}, tools::RgbColor(255, 255, 255));
        result = ppm.saveToString(output, data);
        REQUIRE(result == true);
        REQUIRE(output.length() > 100 * 100 * 3);

    }
}