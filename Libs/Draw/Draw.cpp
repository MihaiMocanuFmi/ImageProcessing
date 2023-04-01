#include "Draw.h"
#include <math.h>

namespace Draw
{
    void drawCircle(Image &img, const tools::Vector2I &center, int radius, const tools::RgbColor &color)
    {
        /*
         * x^2 + y^2 = r^2
         * Fix x = 0 => y = {+r, -r}
         * fix x = 1 => .....
         * ..................
         * fix x = r => y = 0;
         */
        tools::Rectangle imageBoundary({0,0}, img.size() - tools::Vector2I{1, 1});
        //radius/sqrt(2) would represent the quarter point (when y^2 = x^2), to get the rest points we can just mirror
        //We add one just to make sure we do get all;
        for (int x = 0; x <= radius/ sqrt(2) + 1; ++x)
        {
            float y1 = sqrtf(radius * radius - x * x);


            tools::Vector2I point1{(int)x, (int)y1};
            tools::Vector2I point2{-(int)x, (int)y1};
            tools::Vector2I point1Mirrored{(int)y1, (int)x};
            tools::Vector2I point2Mirrored{(int)y1, (int)-x};

            if (tools::Rectangle::isContainedInside(point1 + center, imageBoundary))
                img.at(point1 + center) = color;
            if (tools::Rectangle::isContainedInside(-point1 + center, imageBoundary))
                img.at(-point1 + center) = color;
            if (tools::Rectangle::isContainedInside(point1Mirrored + center, imageBoundary))
                img.at(point1Mirrored + center) = color;
            if (tools::Rectangle::isContainedInside(-point1Mirrored + center, imageBoundary))
                img.at(-point1Mirrored + center) = color;

            if (tools::Rectangle::isContainedInside(point2 + center, imageBoundary))
                img.at(point2 + center) = color;
            if (tools::Rectangle::isContainedInside(-point2 + center, imageBoundary))
                img.at(-point2 + center) = color;
            if (tools::Rectangle::isContainedInside(point2Mirrored + center, imageBoundary))
                img.at(point2Mirrored + center) = color;
            if (tools::Rectangle::isContainedInside(-point2Mirrored + center, imageBoundary))
                img.at(-point2Mirrored + center) = color;



        }
    }

    void drawLine(Image &img, const tools::Vector2I &p1, tools::Vector2I p2, const tools::RgbColor &color)
    {
        tools::Rectangle imageBoundary({0,0}, img.size() - tools::Vector2I{1, 1});
        float norm = sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
        for (int t = 0; t <= norm; ++t)
        {
            //Consider t be in the interval [0, LENGTH_LINE];
            //Let x = p1.x + t * (p2.x - p1.x) / norm;
            //Let y = p1.y + t * (p2.y - p1.y) / norm;
            //If t was in the interval [0, 1] we wouldn't have had to divide by the NORM (same as LENGHT_LINE)
            int x = p1.x + t * (p2.x - p1.x) / norm;
            int y = p1.y + t * (p2.y - p1.y) / norm;
            tools::Vector2I point(x, y);

            if (tools::Rectangle::isContainedInside(point, imageBoundary))
                img.at(point) = color;

        }
    }

    void drawRectangle(Image &img, const tools::Rectangle &r, const tools::RgbColor &color)
    {
        drawLine(img, r.upperLeftCorner, r.findUpperRight(), color);
        drawLine(img, r.upperLeftCorner, r.findLowerLeft(), color);
        drawLine(img, r.findUpperRight(), r.findLowerRight(), color);
        drawLine(img, r.findLowerLeft(), r.findLowerRight(), color);
    }
} // Draw