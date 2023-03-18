#include "Vector2.h"

namespace tools
{

    template<typename T>
    constexpr Vector2<T>::Vector2(T X, T Y) : x{X}, y{Y}
    {
    }

    template<typename T>
    template<typename U>
    constexpr Vector2<T>::Vector2(const Vector2<U>& vector) : x{static_cast<T>(vector.x)}, y{static_cast<T>(vector.y)}
    {
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

}
template class tools::Vector2<int>;
template class tools::Vector2<unsigned int>;
template class tools::Vector2<long long int>;
template class tools::Vector2<unsigned long long int>;
template class tools::Vector2<float>;
template class tools::Vector2<double>;