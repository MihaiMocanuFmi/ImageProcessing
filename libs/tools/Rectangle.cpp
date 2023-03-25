//
// Created by mihai on 3/22/23.
//

#include "Rectangle.h"

namespace tools
{
    Rectangle::Rectangle() : upperLeftCorner{-1, -1}, size{0, 0}
    {

    }

    Rectangle::Rectangle(Vector2I aUpperLeftCorner, Vector2I aSize) : upperLeftCorner{aUpperLeftCorner}, size{aSize}
    {

    }

    Rectangle::Rectangle(int x, int y, int width, int height) : upperLeftCorner{x, y}, size{width, height}
    {

    }

    Vector2I Rectangle::findUpperRight() const
    {
        return upperLeftCorner + Vector2I(size.x, 0);
    }

    Vector2I Rectangle::findLowerLeft() const
    {
        return upperLeftCorner + Vector2I(0, size.y);
    }

    Vector2I Rectangle::findLowerRight() const
    {
        return upperLeftCorner + size;
    }

    bool Rectangle::isContainedInside(const Vector2I &dot, const Rectangle &rectangle)
    {
        bool result = rectangle.upperLeftCorner.x <= dot.x;
        result = result and rectangle.upperLeftCorner.y <= dot.y;

        result = result and dot.x <= rectangle.findLowerRight().x;
        result = result and dot.y <= rectangle.findLowerRight().y;

        return result;
    }

    bool Rectangle::isContainedInside(const Rectangle &inner, const Rectangle &outer)
    {
        bool result = isContainedInside(inner.upperLeftCorner, outer);
        result = result and isContainedInside(inner.findLowerRight(), outer);

        return result;
    }
} // tools