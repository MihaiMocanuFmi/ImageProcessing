#ifndef VECTOR3_H
#define VECTOR3_H

//Designed after the structure of SFML's Vector3
//https://github.com/SFML/SFML

namespace tools
{

    template<typename T>
    class Vector3
    {
    public:
        T x;
        T y;
        T z;

        constexpr Vector3() = default;

        constexpr Vector3(T X, T Y, T Z);

        template<typename U>
        constexpr explicit Vector3(const Vector3<U>& vector);


    };


    template<typename T>
    constexpr Vector3<T> &operator+=(Vector3<T> &left, const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> &operator-=(Vector3<T> &left, const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> operator+(const Vector3<T> &left, const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> operator-(const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> operator-(const Vector3<T> &left, const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> operator*(const Vector3<T> &left, T right);

    template<typename T>
    constexpr Vector3<T> operator*(T left, const Vector3<T> &right);

    template<typename T>
    constexpr Vector3<T> &operator*=(Vector3<T> &left, T right);

    template<typename T>
    constexpr Vector3<T> operator/(const Vector3<T> &left, T right);

    template<typename T>
    constexpr Vector3<T> &operator/=(Vector3<T> &left, T right);

    template<typename T>
    constexpr bool operator==(const Vector3<T> &left, const Vector3<T> &right);

    template<typename T>
    constexpr bool operator!=(const Vector3<T> &left, const Vector3<T> &right);


    typedef Vector3<int>          Vector3I;
    typedef Vector3<unsigned int> Vector3U;
    typedef Vector3<long long int> Vector3LL;
    typedef Vector3<unsigned long long int> Vector3ULL;
    typedef Vector3<float>        Vector3F;
    typedef Vector3<double>        Vector3D;
}
#endif //VECTOR3_H
