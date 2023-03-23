#ifndef VECTOR2_H
#define VECTOR2_H

//Designed after the structure of SFML's Vector2
//https://github.com/SFML/SFML

namespace tools
{

    template<typename T>
    class Vector2
    {
    public:
        T x;
        T y;

        Vector2() = default;

        Vector2(T X, T Y);

        template<typename U>
        explicit Vector2(const Vector2<U>& vector);


    };


    template<typename T>
    Vector2<T> &operator+=(Vector2<T> &left, const Vector2<T> &right);

    template<typename T>
    Vector2<T> &operator-=(Vector2<T> &left, const Vector2<T> &right);

    template<typename T>
    Vector2<T> operator+(const Vector2<T> &left, const Vector2<T> &right);

    template<typename T>
    Vector2<T> operator-(const Vector2<T> &right);

    template<typename T>
    Vector2<T> operator-(const Vector2<T> &left, const Vector2<T> &right);

    template<typename T>
    Vector2<T> operator*(const Vector2<T> &left, T right);

    template<typename T>
    Vector2<T> operator*(T left, const Vector2<T> &right);

    template<typename T>
    Vector2<T> &operator*=(Vector2<T> &left, T right);

    template<typename T>
    Vector2<T> operator/(const Vector2<T> &left, T right);

    template<typename T>
    Vector2<T> &operator/=(Vector2<T> &left, T right);

    //TODO: why dont these 2 work
    template<typename T>
    bool operator==(const Vector2<T> &left, const Vector2<T> &right);

    template<typename T>
    bool operator!=(const Vector2<T> &left, const Vector2<T> &right);


    typedef Vector2<int>          Vector2I;
    typedef Vector2<unsigned int> Vector2U;
    typedef Vector2<long long int> Vector2LL;
    typedef Vector2<unsigned long long int> Vector2ULL;
    typedef Vector2<float>        Vector2F;
    typedef Vector2<double>        Vector2D;
}


#endif //VECTOR2_H
