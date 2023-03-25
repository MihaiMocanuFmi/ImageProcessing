#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vector2.h"

namespace tools
{

    class Rectangle
    {
    public:
        Vector2I upperLeftCorner;
        Vector2I size;

        Rectangle();
        Rectangle(Vector2I aUpperLeftCorner,  Vector2I aSize);
        Rectangle(int x, int y, int width, int height);


        Vector2I findUpperRight() const;
        Vector2I findLowerLeft() const;
        Vector2I findLowerRight() const;

        static bool isContainedInside(const Vector2I &dot, const Rectangle &rectangle);
        static bool isContainedInside(const Rectangle &inner, const Rectangle &outer);
    };

} // tools

#endif //RECTANGLE_H
