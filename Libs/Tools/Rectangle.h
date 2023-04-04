#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vector2.h"
#include "Point.h"

namespace tools
{
    /// \brief Class representing a rectangular in the 2D space
    class Rectangle
    {
    private:

    public:
        /// \brief Computes the size of a rectangle given its upper left and lower right corners
        /// \param upperLeftCorner  The upper left corner of the rectangle
        /// \param lowerRightCorner The lower right corner of the rectangle
        /// \return The signed difference between the two. It can have negative components if the order imposed isn't
        /// respected
        static Vector2I findSize(const Vector2I &upperLeftCorner,  const Vector2I &lowerRightCorner);

        /// \brief Checks if the given dot is inside the given rectangle
        /// \param dot The dot which is checked if it's inside the rectangle
        /// \param rectangle The rectangle which might contain the dot
        /// \return True if the dot is inside the rectangle, false otherwise
        static bool isContainedInside(const Vector2I &dot, const Rectangle &rectangle);

        /// \brief Checks if the first given rectangle is fully inside the second one
        /// \param inner The rectangle which might be contained
        /// \param outer The rectangle which might contain
        /// \return True if the inner rectangle is fully contained inside the outer one, or false otherwise
        static bool isContainedInside(const Rectangle &inner, const Rectangle &outer);

        /// \brief Represents the coords of the Upper Left Corner of the Rectangle
        Vector2I upperLeftCorner = {0, 0};

        /// \brief Represents the width (size.x) and height (size.y) of the Rectangle.
        Vector2I size = {0, 0};

        /// \brief Default constructor, initialises all member to their zero values
        Rectangle() = default;

        /// \brief Creates a rectangle given its upper left corner and size
        /// \param aUpperLeftCorner The upper left corner of the rectangle
        /// \param aSize The size of the rectangle
        Rectangle(const Vector2I &aUpperLeftCorner, const Vector2I &aSize);

        /// \brief Creates a rectangle given its upper left corner and lower left corner. The order imposed must be kept
        /// \param aUpperLeftCorner The upper left corner of the rectangle
        /// \param aLowerRightCorner The lower right corner of the rectangle
        Rectangle(const Point &aUpperLeftCorner,  const Point &aLowerRightCorner);

        /// \brief Creates a rectangle given the components of its upper left corner and size
        /// \param x X coord of the upper left corner
        /// \param y Y coord of the upper left corner
        /// \param width Width of the rectangle
        /// \param height Height of the rectangle
        Rectangle(int x, int y, int width, int height);

        /// \brief Finds the coords of the upper right corner of the current rectangle
        /// \return Vector2 representing the coords of the upper right corner
        Vector2I findUpperRight() const;

        /// \brief Finds the coords of the lower left corner of the current rectangle
        /// \return Vector2 representing the coords of the lower left corner
        Vector2I findLowerLeft() const;

        /// \brief Finds the coords of the lower right corner of the current rectangle
        /// \return Vector2 representing the coords of the lower right corner
        Vector2I findLowerRight() const;


        bool operator==(const Rectangle &right) const;
        bool operator!=(const Rectangle &right) const;

        friend std::ostream &operator<<(std::ostream &left, const Rectangle &right);
        friend std::istream &operator>>(std::istream &left, Rectangle &right);

        friend Rectangle operator+(const Vector2I &left, const Rectangle &right);
        friend Rectangle operator+(const Rectangle &left, const Vector2I &right);

        friend Rectangle operator-(const Rectangle &left, const Vector2I &right);



        /// \brief Computes the intersection between 2 rectangles, gives a rectangle of norm smaller than 0 if
        /// the intersection would be the empty set
        /// \param right The rectangle to be intersected with the current one.
        /// \return A new rectangle representing the intersection region. If the two rectangles are disjoint, it returns
        /// a rectangle with its upper left corner at (-1, -1) and size(-1, -1)
        Rectangle operator&(const Rectangle &right) const;

        /// \brief Computes a "union" between 2 rectangles. It actually finds the smallest rectangle which covers both.
        /// \param right The rectangle to be reunited with the current one.
        /// \return A new rectangle representing the union region. It represents the smallest rectangle which covers
        /// both given rectangles.
        Rectangle operator|(const Rectangle &right) const;

    };






} // Tools

#endif //RECTANGLE_H
