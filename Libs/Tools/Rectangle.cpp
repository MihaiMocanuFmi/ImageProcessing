//
// Created by mihai on 3/22/23.
//

#include "Rectangle.h"
#include <algorithm>

namespace tools
{
    Vector2I Rectangle::findSize(const Vector2I &upperLeftCorner, const Vector2I &lowerRightCorner)
    {
        return lowerRightCorner - upperLeftCorner;
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

    bool Rectangle::operator==(const Rectangle &right) const
    {
        return this->upperLeftCorner == right.upperLeftCorner and this->size == right.size;
    }

    bool Rectangle::operator!=(const Rectangle &right) const
    {
        return not(*this == right);
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


    bool m_sortPointsComparisonX(const Vector2I &a, const Vector2I &b)
    {
        return (a.x <  b.x);

    }
    bool m_sortPointsComparisonY(const Vector2I &a, const Vector2I &b)
    {
        return (a.y <  b.y);
    }


    Rectangle Rectangle::operator&(const Rectangle &right) const
    {
        Vector2F centerLeft = Vector2F(this->upperLeftCorner) + Vector2F(this->size)/2.0f;
        Vector2F centerRight =  Vector2F(right.upperLeftCorner) +  Vector2F(right.size)/2.0f;
        Vector2F centerCombined = (centerLeft + centerRight)/2.0f;

        Vector2I coords[4] = {this->upperLeftCorner, this->findLowerRight(),right.upperLeftCorner,
                               right.findLowerRight()};
        std::sort(coords, coords + 4, m_sortPointsComparisonX);

        //After sorting, the intersection point will be given by a point that doesn't represent a boundary
        //for the other points. In other words, a point inside the boundary
        //we take the point [1], but we could also take [2]
        Vector2I intersectionPoint(coords[1]);

        if (isContainedInside(intersectionPoint, right))
        {
            Vector2F halfDistance = Vector2F(intersectionPoint) - centerCombined;
            //absolute value
            if (halfDistance.x < 0)
                halfDistance.x *= -1;
            if (halfDistance.y < 0)
                halfDistance.y *= -1;

            Vector2I size = Vector2I(halfDistance * 2.0f);
            Vector2I upperLeft = Vector2I(centerCombined - halfDistance);
            return Rectangle(upperLeft, size);
        }
        else
            return Rectangle(Vector2I(centerCombined), {-1, -1});

    }

    Rectangle Rectangle::operator|(const Rectangle &right) const
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