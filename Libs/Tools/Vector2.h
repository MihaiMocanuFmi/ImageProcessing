#ifndef VECTOR2_H
#define VECTOR2_H

#include <ostream>
#include <istream>

//Designed after the structure of SFML's Vector2
//https://github.com/SFML/SFML

namespace tools
{

    template<typename T>
    class Vector2
    {
    public:
        T x = 0;
        T y = 0;

        constexpr Vector2() = default;

        constexpr Vector2(T X, T Y) : x{X}, y{Y}
        {
        }

        template<typename U>
        constexpr explicit Vector2(const Vector2<U>& vector): x{static_cast<T>(vector.x)}, y{static_cast<T>(vector.y)}
        {
        }


    };

    template <typename T>
    std::ostream &operator<<(std::ostream &left, const Vector2<T>& right)
    {
        left << '(' << right.x << ", " << right.y << ')';
        return left;
    }

    template <typename T>
    std::istream &operator>>(std::istream &left, Vector2<T>& right)
    {
        left >> right.x >> right.y;
        return left;
    }


    template <typename T>
    constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    template <typename T>
    constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }


    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }


    template<typename T>
    constexpr Vector2 <T> operator-(const Vector2<T> &right)
    {
        return Vector2<T>(-right.x, -right.y);
    }

    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }


    template <typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x * right, left.y * right);
    }


    template <typename T>
    constexpr Vector2<T> operator*(T left, const Vector2<T>& right)
    {
        return Vector2<T>(right.x * left, right.y * left);
    }


    template <typename T>
    constexpr Vector2<T>& operator*=(Vector2<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;

        return left;
    }


    template <typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x / right, left.y / right);
    }


    template <typename T>
    constexpr Vector2<T>& operator/=(Vector2<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;

        return left;
    }


    template <typename T>
    constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
    {
        return (left.x == right.x) and (left.y == right.y);
    }


    template <typename T>
    constexpr bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
    {
        return (left.x != right.x) or (left.y != right.y);
    }

    typedef Vector2<int>          Vector2I;
    typedef Vector2<unsigned int> Vector2U;
    typedef Vector2<long long int> Vector2LL;
    typedef Vector2<unsigned long long int> Vector2ULL;
    typedef Vector2<float>        Vector2F;
    typedef Vector2<double>        Vector2D;
}


#endif //VECTOR2_H
