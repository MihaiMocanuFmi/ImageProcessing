//
// Created by mihai on 4/2/23.
//

#include "Point.h"

namespace tools
{
    Point::Point(int x, int y) : Vector2(x, y)
    {

    }

    Point::Point(Vector2I pos) : Vector2(pos)
    {

    }
} // tools