#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Vector2.h"

namespace tools
{

    int m_sortPointsComparisonX(const Vector2I &a, const Vector2I &b);
    int m_sortPointsComparisonY(const Vector2I &a, const Vector2I &b);
    //TODO: change to template;
    class Rectangle
    {
    private:

    public:
        static Vector2I findSize(const Vector2I &upperLeftCorner,  const Vector2I &lowerRightCorner);

        Vector2I upperLeftCorner = {0, 0};
        Vector2I size = {0, 0};

        Rectangle() = default;
        Rectangle(const Vector2I &aUpperLeftCorner, const Vector2I &aSize);
        //Rectangle(const Vector2I &aUpperLeftCorner,  const Vector2I &aLowerRightCorner);

        Rectangle(int x, int y, int width, int height);


        Vector2I findUpperRight() const;
        Vector2I findLowerLeft() const;
        Vector2I findLowerRight() const;

        static bool isContainedInside(const Vector2I &dot, const Rectangle &rectangle);
        static bool isContainedInside(const Rectangle &inner, const Rectangle &outer);

        friend std::ostream &operator<<(std::ostream &left, const Rectangle &right);
        friend std::istream &operator>>(std::istream &left, Rectangle &right);

        friend Rectangle operator+(const Vector2I &left, const Rectangle &right);
        friend Rectangle operator+(const Rectangle &left, const Vector2I &right);

        friend Rectangle operator-(const Rectangle &left, const Vector2I &right);


        //intersection between 2 rectangles, gives a rectangle of size < 0 if intersection would be empty set
        Rectangle operator&(const Rectangle &right);

        //computes union between 2 rectangles, It actually finds the smallest rectangle which covers both
        Rectangle operator|(const Rectangle &right);

    };






} // Tools

#endif //RECTANGLE_H
