#include "Vector3.h"

namespace tools
{

    template<typename T>
    constexpr Vector3<T>::Vector3(T X, T Y, T Z) : x{X}, y{Y}, z{Z}
    {
    }

    template<typename T>
    template<typename U>
    constexpr Vector3<T>::Vector3(const Vector3<U>& vector) : x{static_cast<T>(vector.x)}, y{static_cast<T>(vector.y)}, z{static_cast<T>(vector.z)}
    {
    }

    template <typename T>
    constexpr Vector3<T>& operator+=(Vector3<T>& left, const Vector3<T>& right)
    {
        left.x += right.x;
        left.y += right.y;
        left.z += right.z;

        return left;
    }

    template <typename T>
    constexpr Vector3<T>& operator-=(Vector3<T>& left, const Vector3<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;
        left.z -= right.z;

        return left;
    }


    template <typename T>
    constexpr Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
    {
        return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
    }


    template<typename T>
    constexpr Vector3 <T> operator-(const Vector3<T> &right)
    {
        return Vector3<T>(-right.x, -right.y, -right.z);
    }

    template <typename T>
    constexpr Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
    {
        return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
    }


    template <typename T>
    constexpr Vector3<T> operator*(const Vector3<T>& left, T right)
    {
        return Vector3<T>(left.x * right, left.y * right, left.z * right);
    }


    template <typename T>
    constexpr Vector3<T> operator*(T left, const Vector3<T>& right)
    {
        return Vector3<T>(right.x * left, right.y * left, right.z * left);
    }


    template <typename T>
    constexpr Vector3<T>& operator*=(Vector3<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;
        left.z *= right;

        return left;
    }


    template <typename T>
    constexpr Vector3<T> operator/(const Vector3<T>& left, T right)
    {
        return Vector3<T>(left.x / right, left.y / right, left.z / right);
    }


    template <typename T>
    constexpr Vector3<T>& operator/=(Vector3<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;
        left.z /= right;

        return left;
    }


    template <typename T>
    constexpr bool operator==(const Vector3<T>& left, const Vector3<T>& right)
    {
        return (left.x == right.x) and (left.y == right.y) and (left.y == right.z);
    }


    template <typename T>
    constexpr bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
    {
        return (left.x != right.x) or (left.y != right.y) or (left.z != right.z);
    }

}
template class tools::Vector3<int>;
template class tools::Vector3<unsigned int>;
template class tools::Vector3<long long int>;
template class tools::Vector3<unsigned long long int>;
template class tools::Vector3<float>;
template class tools::Vector3<double>;