#ifndef POINT_H
#define POINT_H

#include "Vector2.h"

namespace tools
{

    class Point : public Vector2I
    {
    private:

    public:
        /// \brief Default constructor
        ///
        ///     Initializes a 2D point with coords (0, 0)
        Point() = default;

        /// \brief Initializes a 2D point given a Vector2I
        /// \param pos Position of point
        Point(Vector2I pos);

        /// \brief Initializes a 2D point given its coords
        /// \param x Horizontal coord axis
        /// \param y Vertical coord axis
        Point(int x, int y);
    };

} // tools

#endif //POINT_H
