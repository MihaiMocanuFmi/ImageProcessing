#include "RgbColor.h"

#include <algorithm>
#include <limits>


namespace tools
{
    /////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

    /////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

    RgbColor::RgbColor(int R, int G, int B, bool override)
    {
        setColor(R, G, B, override);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColor(int R, int G, int B, bool override)
    {
        setColorR(R, override);
        setColorG(G, override);
        setColorB(B, override);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColor(const RgbColor::Color &color, bool override)
    {
        setColorR(color.R, override);
        setColorG(color.G, override);
        setColorB(color.B, override);
    }
    const RgbColor::Color &RgbColor::getColor() const
    {
        return m_color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorR(int R, bool override)
    {
        if (not override)
            m_color.R = std::clamp<int>(R, 0, MAX_VALUE);
        else
            m_color.R = R;
    }
    int RgbColor::getColorR() const
    {
        return m_color.R;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorG(int G, bool override)
    {
        if (not override)
            m_color.G = std::clamp<int>(G, 0, MAX_VALUE);
        else
            m_color.G = G;
    }

    int RgbColor::getColorG() const
    {
        return m_color.G;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorB(int B, bool override)
    {
        if (not override)
            m_color.B = std::clamp<int>(B, 0, MAX_VALUE);
        else
            m_color.B = B;
    }

    int RgbColor::getColorB() const
    {
        return m_color.B;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::ostream &operator<<(std::ostream &os, const RgbColor &dt)
    {
        os << '(' << dt.getColorR() << ", " << dt.getColorG() << ", " << dt.getColorB() << ')';
        return os;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::add(const RgbColor &other, bool overrideClamp) const
    {
        RgbColor newColor;

        newColor.setColor(this->getColorR() + other.getColorR(), this->getColorG() + other.getColorG(),
                          this->getColorB() + other.getColorB(), overrideClamp);
        return newColor;
    }

    RgbColor RgbColor::subtract(const RgbColor &other, bool overrideClamp) const
    {
        RgbColor newColor;

        newColor.setColor(this->getColorR() - other.getColorR(), this->getColorG() - other.getColorG(),
                          this->getColorB() - other.getColorB(), overrideClamp);
        return newColor;
    }

    RgbColor RgbColor::multiply(const RgbColor &other, bool overrideClamp) const
    {
        RgbColor newColor;

        newColor.setColor(this->getColorR() * other.getColorR(), this->getColorG() * other.getColorG(),
                          this->getColorB() * other.getColorB(), overrideClamp);
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    RgbColor RgbColor::operator+(const RgbColor &other) const
    {
        return add(other);
    }

    RgbColor RgbColor::operator-(const RgbColor &other) const
    {
        return subtract(other);
    }

    RgbColor RgbColor::operator*(const RgbColor &other) const
    {
        return multiply(other);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator+(float scalar, const RgbColor &color)
    {
        return add(scalar, color);
    }

    RgbColor operator+(const RgbColor &color, float scalar)
    {
        return add(scalar, color);
    }

    RgbColor operator-(const RgbColor &color, float scalar)
    {
        return subtract(color, scalar);
    }

    RgbColor operator*(float scalar, const RgbColor &color)
    {
        return multiply(scalar, color);
    }

    RgbColor operator*(const RgbColor &color, float scalar)
    {
        return multiply(scalar, color);
    }


} // Tools