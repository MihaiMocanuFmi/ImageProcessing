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

        /// \brief Default constructor, initialises coords to (0,0);
        constexpr Vector2() = default;

        /// \brief Initialises given its coords
        /// \param X Horizontal coord axis
        /// \param Y Vertical coord axis
        constexpr Vector2(T X, T Y) : x{X}, y{Y}
        {
        }

        /// \brief Initialises Vector2 given another Vector2
        /// \tparam U Type of given Vector2
        /// \param vector The Vector2 whose values will be (casted and) copied;
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


    /// \relates Vector2
    /// \brief Overload of binary operator +=
    ///
    /// This operator performs a memberwise addition of both vectors,
    /// and assigns the result to \c left.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return Reference to \c left
    template <typename T>
    constexpr Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x += right.x;
        left.y += right.y;

        return left;
    }

    /// \relates Vector2
    /// \brief Overload of binary operator -=
    ///
    /// This operator performs a memberwise subtraction of both vectors,
    /// and assigns the result to \c left.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return Reference to \c left
    template <typename T>
    constexpr Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right)
    {
        left.x -= right.x;
        left.y -= right.y;

        return left;
    }

    /// \relates Vector2
    /// \brief Overload of binary operator +
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return Memberwise addition of both vectors
    template <typename T>
    constexpr Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x + right.x, left.y + right.y);
    }


    /// \relates Vector2
    /// \brief Overload of unary operator -
    ///
    /// \param right Vector to negate
    ///
    /// \return Memberwise opposite of the vector
    template<typename T>
    constexpr Vector2 <T> operator-(const Vector2<T> &right)
    {
        return Vector2<T>(-right.x, -right.y);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator -
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return Memberwise subtraction of both vectors
    template <typename T>
    constexpr Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
    {
        return Vector2<T>(left.x - right.x, left.y - right.y);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator *
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a scalar value)
    ///
    /// \return Memberwise multiplication by \c right
    template <typename T>
    constexpr Vector2<T> operator*(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x * right, left.y * right);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator *
    ///
    /// \param left  Left operand (a scalar value)
    /// \param right Right operand (a vector)
    ///
    /// \return Memberwise multiplication by \c left
    template <typename T>
    constexpr Vector2<T> operator*(T left, const Vector2<T>& right)
    {
        return Vector2<T>(right.x * left, right.y * left);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator *=
    ///
    /// This operator performs a memberwise multiplication by \c right,
    /// and assigns the result to \c left.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a scalar value)
    ///
    /// \return Reference to \c left
    template <typename T>
    constexpr Vector2<T>& operator*=(Vector2<T>& left, T right)
    {
        left.x *= right;
        left.y *= right;

        return left;
    }

    /// \relates Vector2
    /// \brief Overload of binary operator /
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a scalar value)
    ///
    /// \return Memberwise division by \c right
    template <typename T>
    constexpr Vector2<T> operator/(const Vector2<T>& left, T right)
    {
        return Vector2<T>(left.x / right, left.y / right);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator /=
    ///
    /// This operator performs a memberwise division by \c right,
    /// and assigns the result to \c left.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a scalar value)
    ///
    /// \return Reference to \c left
    template <typename T>
    constexpr Vector2<T>& operator/=(Vector2<T>& left, T right)
    {
        left.x /= right;
        left.y /= right;

        return left;
    }

    /// \relates Vector2
    /// \brief Overload of binary operator ==
    ///
    /// This operator compares strict equality between two vectors.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return True if \c left is equal to \c right
    template <typename T>
    constexpr bool operator==(const Vector2<T>& left, const Vector2<T>& right)
    {
        return (left.x == right.x) and (left.y == right.y);
    }

    /// \relates Vector2
    /// \brief Overload of binary operator !=
    ///
    /// This operator compares strict difference between two vectors.
    ///
    /// \param left  Left operand (a vector)
    /// \param right Right operand (a vector)
    ///
    /// \return True if \c left is not equal to \c right
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
