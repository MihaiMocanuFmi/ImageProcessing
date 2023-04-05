#include <catch2/catch_all.hpp>

#include "Draw/Draw.h"

TEST_CASE("Draw", "[Draw]")
{
    using namespace Draw;
    const tools::RgbColor WHITE = tools::RgbColor(255, 255, 255);
    const tools::RgbColor BLACK = tools::RgbColor(0, 0, 0);

    Image whiteCanvas(ImageData({100, 100}, WHITE));

    SECTION("Circle")
    {
        drawCircle(whiteCanvas, {0, 0}, 99, BLACK);
        REQUIRE(whiteCanvas.at(0, 0) == WHITE);
        REQUIRE(whiteCanvas.at(0, 99) == BLACK);
        REQUIRE(whiteCanvas.at(99, 0) == BLACK);
        REQUIRE(whiteCanvas.at(99.0f/ sqrt(2), 99.0f/ sqrt(2)) == BLACK);
        REQUIRE(whiteCanvas.at(99.0f/ sqrt(2) - 1, 99.0f/ sqrt(2) - 1) == WHITE);


        drawCircle(whiteCanvas, {99, 99}, 99, BLACK);
        REQUIRE(whiteCanvas.at(99 - 0, 99 - 0) == WHITE);
        REQUIRE(whiteCanvas.at(99 - 0, 99 - 99) == BLACK);
        REQUIRE(whiteCanvas.at(99 - 99, 99 - 0) == BLACK);
        REQUIRE(whiteCanvas.at(99 - 99.0f/ sqrt(2) + 1, 99 - 99.0f/ sqrt(2) + 1) == BLACK);
        REQUIRE(whiteCanvas.at(99 - 99.0f/ sqrt(2) - 1, 99 - 99.0f/ sqrt(2) - 1) == WHITE);
    }

    SECTION("Line")
    {
        drawLine(whiteCanvas, {0, 0}, {100, 100}, BLACK);
        REQUIRE(whiteCanvas.at(0, 0) == BLACK);
        REQUIRE(whiteCanvas.at(0, 99) == WHITE);
        REQUIRE(whiteCanvas.at(99, 0) == WHITE);

        for (int i = 1; i < 100; ++i)
        {
            REQUIRE((whiteCanvas.at(i - 1, i) == WHITE));
            REQUIRE((whiteCanvas.at(i, i) == BLACK));
            REQUIRE((whiteCanvas.at(i, i - 1) == WHITE));

        }
    }

    SECTION("Rectangle")
    {
        drawRectangle(whiteCanvas, tools::Rectangle(0, 0, 99, 99), BLACK);
        REQUIRE(whiteCanvas.at(0, 0) == BLACK);
        REQUIRE(whiteCanvas.at(0, 99) == BLACK);
        REQUIRE(whiteCanvas.at(99, 0) == BLACK);

        for (int i = 1; i < 99; ++i)
        {
            REQUIRE((whiteCanvas.at(i, 0) == BLACK));
            REQUIRE((whiteCanvas.at(i, 0) == BLACK));
            REQUIRE((whiteCanvas.at(i, 2) == WHITE));

            REQUIRE((whiteCanvas.at(0, i) == BLACK));
            REQUIRE((whiteCanvas.at(2, i) == WHITE));

            REQUIRE((whiteCanvas.at(i, 99) == BLACK));
            REQUIRE((whiteCanvas.at(i, 97) == WHITE));

            REQUIRE((whiteCanvas.at(99, i) == BLACK));
            REQUIRE((whiteCanvas.at(98, i) == WHITE));

        }
    }
}