//
// Created by mihai on 3/22/23.
//

#include "Rectangle.h"
#include <algorithm>

namespace tools
{
    Vector2I Rectangle::findSize(const Vector2I &upperLeftCorner, const Vector2I &lowerRightCorner)
    {
        return upperLeftCorner - lowerRightCorner;
    }

    Rectangle::Rectangle(const Vector2I &aUpperLeftCorner, const Vector2I &aSize)
        : upperLeftCorner{aUpperLeftCorner}, size{aSize}
    {

    }

    Rectangle::Rectangle(const Point &aUpperLeftCorner, const Point &aLowerRightCorner)
        : upperLeftCorner{aUpperLeftCorner}, size{findSize(aUpperLeftCorner, aLowerRightCorner)}
    {

    }

    Rectangle::Rectangle(int x, int y, int width, int height)
        : upperLeftCorner{x, y}, size{width, height}
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

    std::ostream &operator<<(std::ostream &left, const Rectangle &right)
    {
        left << '(' << right.upperLeftCorner << ", " << right.size << ')';
        return left;
    }

    std::istream &operator>>(std::istream &left, Rectangle &right)
    {
        left >> right.upperLeftCorner >> right.size;
        return left;
    }

    Rectangle operator+(const Vector2I &left, const Rectangle &right)
    {
        return Rectangle(right.upperLeftCorner + left, right.size);
    }

    Rectangle operator+(const Rectangle &left, const Vector2I &right)
    {
        return right + left;
    }

    Rectangle operator-(const Rectangle &left, const Vector2I &right)
    {
        return left + (-right);
    }


    int m_sortPointsComparisonX(const Vector2I &a, const Vector2I &b)
    {
        if (a.x <  b.x) return -1;
        if ( a.x == b.x ) return 0;
        if ( a.x >  b.x ) return 1;
        return 0;
    }
    int m_sortPointsComparisonY(const Vector2I &a, const Vector2I &b)
    {
        if (a.y <  b.y) return -1;
        if ( a.y == b.y ) return 0;
        if ( a.y >  b.y ) return 1;
        return 0;
    }

    Rectangle Rectangle::operator&(const Rectangle &right)
    {
        Vector2I centerLeft = this->upperLeftCorner + this->size/2;
        Vector2I centerRight = right.upperLeftCorner + right.size/2;
        Vector2I centerCombined = (centerLeft + centerRight)/2;

        Vector2I coords[4] = {this->upperLeftCorner, this->findLowerRight(),right.upperLeftCorner,
                               this->findLowerRight()};
        std::sort(coords, coords + 4, m_sortPointsComparisonX);

        //After sorting, the intersection point will be given by a point that doesn't represent a boundary
        //for the other points. In other words, a point inside the boundary
        //we take the point [1], but we could also take [2]
        Vector2I intersectionPoint(coords[1]);

        if (isContainedInside(intersectionPoint, right))
        {
            Vector2I halfDistance = intersectionPoint - centerCombined;
            //absolute value
            if (halfDistance.x < 0)
                halfDistance.x *= -1;
            if (halfDistance.y < 0)
                halfDistance.y *= -1;

            Vector2I size = halfDistance * 2;

            return Rectangle(centerCombined - halfDistance, size);
        }
        else
            return Rectangle(centerCombined, {-1, -1});

    }

    Rectangle Rectangle::operator|(const Rectangle &right)
    {
        Vector2I coords[4] = {this->upperLeftCorner, this->findLowerRight(),right.upperLeftCorner,
                              this->findLowerRight()};
        std::sort(coords, coords + 4, m_sortPointsComparisonX);

        Vector2I upperLeftCorner;
        upperLeftCorner.x = coords[0].x;
        Vector2I size;
        size.x = coords[3].x - upperLeftCorner.x;

        std::sort(coords, coords + 4, m_sortPointsComparisonY);
        upperLeftCorner.y = coords[0].y;
        size.y = coords[3].y - upperLeftCorner.y;

        return Rectangle(upperLeftCorner, size);
    }


} // Tools