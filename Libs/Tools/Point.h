#ifndef POINT_H
#define POINT_H

#include "Vector2.h"

namespace tools
{

    class Point : public Vector2I
    {
    private:

    public:
        Point() = default;
        Point(Vector2I pos);
        Point(int x, int y);
    };

} // tools

#endif //POINT_H
