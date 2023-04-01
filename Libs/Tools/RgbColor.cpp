#include "RgbColor.h"

#include <algorithm>
#include <limits>


namespace tools
{
    /////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

    /////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

    RgbColor::RgbColor()
    {

        setColor(0,0,0);
    }

    RgbColor::RgbColor(int R, int G, int B, bool overrideClamp)
    :overrideClamping(overrideClamp)
    {
        setColor(R, G, B);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColor(int R, int G, int B)
    {
        setColorR(R);
        setColorG(G);
        setColorB(B);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColor(const RgbColor::Color &color)
    {
        setColorR(color.R);
        setColorG(color.G);
        setColorB(color.B);
    }
    const RgbColor::Color &RgbColor::getColor() const
    {
        return m_color;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorR(int R)
    {
        if (not overrideClamping)
            m_color.R = std::clamp<int>(R, 0, MAX_VALUE);
        else
            m_color.R = R;
    }
    int RgbColor::getColorR() const
    {
        return m_color.R;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorG(int G)
    {
        if (not overrideClamping)
            m_color.G = std::clamp<int>(G, 0, MAX_VALUE);
        else
            m_color.G = G;
    }

    int RgbColor::getColorG() const
    {
        return m_color.G;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorB(int B)
    {
        if (not overrideClamping)
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

    RgbColor RgbColor::operator+(const RgbColor &other) const
    {
        RgbColor newColor;

        bool override = this->overrideClamping or other.overrideClamping;
        newColor.overrideClamping = override;

        newColor.setColor(this->getColorR() + other.getColorR(), this->getColorG() + other.getColorG(),
                          this->getColorB() + other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator-(const RgbColor &other) const
    {
        RgbColor newColor;

        bool override = this->overrideClamping or other.overrideClamping;
        newColor.overrideClamping = override;

        newColor.setColor(this->getColorR() - other.getColorR(), this->getColorG() - other.getColorG(),
                          this->getColorB() - other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator*(const RgbColor &other)
    {
        RgbColor newColor;

        bool override = this->overrideClamping or other.overrideClamping;
        newColor.overrideClamping = override;

        newColor.setColor(this->getColorR() * other.getColorR(), this->getColorG() * other.getColorG(),
                          this->getColorB() * other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator+(float scalar, const RgbColor &colorMatrix)
    {
        RgbColor newColor;

        newColor.overrideClamping =  colorMatrix.overrideClamping;

        newColor.setColor(scalar + (float)colorMatrix.getColorR(), scalar + (float)colorMatrix.getColorG(),
                          scalar + (float)colorMatrix.getColorB());
        return newColor;
    }

    RgbColor operator+(const RgbColor &colorMatrix, float scalar)
    {
        return scalar + colorMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator-(const RgbColor &colorMatrix, float scalar)
    {
        RgbColor newColor;

        newColor.overrideClamping =  colorMatrix.overrideClamping;

        newColor.setColor((float)colorMatrix.getColorR() - scalar, (float)colorMatrix.getColorG() - scalar,
                          (float)colorMatrix.getColorB() - scalar);
        return newColor;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator*(float scalar, const RgbColor &colorMatrix)
    {
        RgbColor newColor;

        newColor.overrideClamping =  colorMatrix.overrideClamping;

        newColor.setColor(scalar * (float)colorMatrix.getColorR(), scalar * (float)colorMatrix.getColorG(),
                          scalar * (float)colorMatrix.getColorB());
        return newColor;
    }

    RgbColor operator*(const RgbColor &colorMatrix, float scalar)
    {
        return scalar * colorMatrix;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // Tools