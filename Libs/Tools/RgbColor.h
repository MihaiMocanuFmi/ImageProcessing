#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <vector>
#include <ostream>

namespace tools
{
    /// \brief Simplified color class containing 3 components representing the RGB values
    class Color
    {
    public:
        /// \brief Red component
        int R = 0;
        /// \brief Green component
        int G = 0;
        /// \brief Blue component
        int B = 0;

        /// \brief Default constructor which initialises the RGB values to 0
        Color() = default;

        /// \brief Initialises the 3-tuple to the given values
        /// \param r red component
        /// \param g green component
        /// \param b blue component
        Color(int r, int g, int b);

        /// \brief Overload of binary operator ==
        ///
        /// This operator compares strict equality between two Colors.
        ///
        /// \param other Right operand (a Color)
        /// \return True if \c left is equal to \c right
        bool operator==(const Color &other) const;

        /// \brief Overload of binary operator !=
        ///
        /// This operator compares strict difference between two Colors.
        ///
        /// \param other  Right operand (a Color)
        ///
        /// \return True if \c left is not equal to \c right
        bool operator!=(const Color &other) const;
    };


    /// \brief Specialization of Color class which keeps its values in the range [0, MAX_VALUE=255]
    class RgbColor
    {
    private:
         Color m_color;
    public:
        /// \brief The maximum value that a RGB component can have
        static constexpr int MAX_VALUE = 255;

        /// \brief Default constructor which initialises the RGB values to 0
        RgbColor() = default;

        /// \brief Constructor which converts a simple Color into a \c RgbColor
        /// \param color The \c Color from which you want to generate a \c RgbColor
        /// \param override Option to override clamping, allowing elements outside the default range
        RgbColor(Color color, bool override = false);

        /// \brief Constructor which creates a \c RgbColor given the values of its components
        /// \param R Red component
        /// \param G Green component
        /// \param B Blue component
        /// \param override Option to override clamping, allowing elements outside the default range
        RgbColor(int R, int G, int B, bool override = false);

        /// \brief Setter for color, given its components
        /// \param R Red component
        /// \param G Green component
        /// \param B Blue component
        /// \param override Option to override clamping, allowing elements outside the default range
        void setColor(int R, int G, int B, bool override = false);

        /// \brief Setter for color given a simple \c Color
        /// \param color The \c Color from which you want to get the components' values
        /// \param override Option to override clamping, allowing elements outside the default range
        void setColor(const Color &color, bool override = false);

        /// \brief Getter of Color
        /// \return A const reference Color object
        const Color &getColor() const;

        /// \brief Setter for color, given its red component
        /// \param R Red component
        /// \param override Option to override clamping, allowing elements outside the default range
        void setColorR(int R, bool override = false);

        /// \brief Getter of red component
        /// \return red component
        int getColorR() const;

        /// \brief Setter for color, given its green component
        /// \param G green component
        /// \param override Option to override clamping, allowing elements outside the default range
        void setColorG(int G, bool override = false);

        /// \brief Getter of green component
        /// \return green component
        int getColorG() const;

        /// \brief Setter for color, given its blue component
        /// \param B blue component
        /// \param override Option to override clamping, allowing elements outside the default range
        void setColorB(int B, bool override = false);

        /// \brief Getter of blue component
        /// \return blue component
        int getColorB() const;

        friend std::ostream& operator<<(std::ostream& os, const RgbColor& dt);

        bool operator==(const RgbColor &other) const;
        bool operator!=(const RgbColor &other) const;

        /// \brief Computes the component-wis sum of the current RgbColor with the given RgbColor
        /// \param other The RgbColor to sum with
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the sum
        RgbColor add(const RgbColor &other, bool overrideClamp = false) const;

        /// \brief Computes the component-wis difference between the current RgbColor and the given RgbColor
        /// \param other The RgbColor to be subtracted
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the difference
        RgbColor subtract(const RgbColor &other, bool overrideClamp = false) const;

        /// \brief Computes the component-wis product of the current RgbColor with the given RgbColor
        /// \param other The RgbColor to multiply with
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the product
        RgbColor multiply(const RgbColor &other, bool overrideClamp = false) const;

        RgbColor operator+(const RgbColor &other) const;
        RgbColor operator-(const RgbColor &other) const;
        RgbColor operator*(const RgbColor &other) const;

        /// \brief Computes the component-wis sum between a scalar and an RgbColor
        /// \param scalar the scalar which is added
        /// \param color the RgbColor on which the scalar is added
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the new result after the scalar sum
        friend RgbColor add(float scalar, const RgbColor &color, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor(scalar + (float)color.getColorR(), scalar + (float)color.getColorG(),
                              scalar + (float)color.getColorB(), overrideClamp);
            return newColor;
        }

        /// \brief Subtracts the scalar from the given RgbColor
        /// \param color the RgbColor on which the scalar is subtracted
        /// \param scalar the scalar which is subtracted
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the new result after the scalar difference
        friend RgbColor subtract(const RgbColor &color, float scalar, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor((float)color.getColorR() - scalar, (float)color.getColorG() - scalar ,
                              (float)color.getColorB() - scalar , overrideClamp);
            return newColor;
        }

        /// \brief Computes the component-wise product between a scalar and an RgbColor
        /// \param scalar the scalar which is multiplied
        /// \param color the RgbColor on which the scalar is multiplied
        /// \param overrideClamp Option to override clamping, allowing elements outside the default range
        /// \return A new RgbColor representing the new result after the scalar product
        friend RgbColor multiply(float scalar, const RgbColor &color, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor(scalar * (float)color.getColorR(), scalar * (float)color.getColorG(),
                              scalar * (float)color.getColorB(), overrideClamp);
            return newColor;
        }

        friend RgbColor operator+(float scalar, const RgbColor &color);
        friend RgbColor operator+(const RgbColor &color, float scalar);

        friend RgbColor operator-(const RgbColor &color, float scalar);

        friend RgbColor operator*(float scalar, const RgbColor &color);
        friend RgbColor operator*(const RgbColor &color, float scalar);
    };

} // Tools

#endif //RGB_COLOR_H
