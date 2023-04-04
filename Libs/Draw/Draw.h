#ifndef DRAW_H
#define DRAW_H

#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"
#include "../Tools/RgbColor.h"
#include "../Image/Image.h"

/// \brief Module responsible for drawing basic shapes on Images
namespace Draw
{
    /// \brief It draws a Circle on the given image
    /// \param img The canvas on which the Circle is drawn
    /// \param center The center of the Circle
    /// \param radius The radius of the Circle
    /// \param color The RgbColor of the Circle
    void drawCircle(Image& img, const tools::Vector2I &center, int radius, const tools::RgbColor &color);

    /// \brief It draws a straight Line on the given image
    /// \param img The canvas on which the Line is drawn
    /// \param p1 One point of the Line
    /// \param p2 Another point of the Line
    /// \param color The RgbColor of the Line
    void drawLine(Image &img, const tools::Vector2I &p1, tools::Vector2I p2, const tools::RgbColor &color);

    /// \brief It draws a Rectangle on the given image
    /// \param img The canvas on which the Rectangle is drawn
    /// \param r The Rectangle to be drawn
    /// \param color The RgbColor of the Rectangle
    void drawRectangle(Image &img, const tools::Rectangle &r, const tools::RgbColor &color);

} // Draw

#endif //DRAW_H
