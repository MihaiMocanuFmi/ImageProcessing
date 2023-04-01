#ifndef DRAW_H
#define DRAW_H

#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"
#include "../Tools/RgbColor.h"
#include "../Image/Image.h"

namespace Draw
{
    void drawCircle(Image& img, const tools::Vector2I &center, int radius, const tools::RgbColor &color);
    void drawLine(Image &img, const tools::Vector2I &p1, tools::Vector2I p2, const tools::RgbColor &color);
    void drawRectangle(Image &img, const tools::Rectangle &r, const tools::RgbColor &color);

} // Draw

#endif //DRAW_H
