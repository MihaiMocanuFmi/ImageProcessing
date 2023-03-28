#include "RgbColor.h"

#include <algorithm>
#include <limits>


namespace tools
{
    /////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

    /////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

    RgbColor::RgbColor() : m_maxValue{std::numeric_limits<int>::max()}
    {

        setColor(0,0,0);
    }

    RgbColor::RgbColor(int maxValue) : m_maxValue{maxValue}
    {
        setColor(0,0,0);
    }

    RgbColor::RgbColor(int maxValue, int R, int G, int B) : m_maxValue{maxValue}
    {
        setColor(R,G,B);
    }

    RgbColor::RgbColor(int maxValue, const RgbColor::Color &color)
    : m_maxValue{maxValue}
    {
        setColor(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setMaxValue(int maxValue)
    {
        m_maxValue = maxValue;
        this->setColor(this->getColor());
    }

    int RgbColor::getMaxValue() const
    {
        return m_maxValue;
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
        m_color.R = std::clamp<int>(R, 0, m_maxValue);
    }
    int RgbColor::getColorR() const
    {
        return m_color.R;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorG(int G)
    {
        m_color.G = std::clamp<int>(G, 0, m_maxValue);
    }

    int RgbColor::getColorG() const
    {
        return m_color.G;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorB(int B)
    {
        m_color.B = std::clamp<int>(B, 0, m_maxValue);
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
        int maxValue = std::max(this->m_maxValue, other.m_maxValue);

        RgbColor newColor(maxValue);
        newColor.setColor(this->getColorR() + other.getColorR(), this->getColorG() + other.getColorG(),
                          this->getColorB() + other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator-(const RgbColor &other) const
    {
        int maxValue = this->m_maxValue;
        RgbColor newColor(maxValue);
        newColor.setColor(this->getColorR() - other.getColorR(), this->getColorG() - other.getColorG(),
                          this->getColorB() - other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator*(const RgbColor &other)
    {
        int maxValue = std::max(this->m_maxValue, other.m_maxValue);
        RgbColor newColor(maxValue);
        newColor.setColor(this->getColorR() * other.getColorR(), this->getColorG() * other.getColorG(),
                          this->getColorB() * other.getColorB());
        return newColor;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator+(float scalar, const RgbColor &colorMatrix)
    {
        int maxValue = colorMatrix.m_maxValue;
        RgbColor newColor(maxValue);
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
        int maxValue = colorMatrix.m_maxValue;
        RgbColor newColor(maxValue);
        newColor.setColor((float)colorMatrix.getColorR() - scalar, (float)colorMatrix.getColorG() - scalar,
                          (float)colorMatrix.getColorB() - scalar);
        return newColor;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator*(float scalar, const RgbColor &colorMatrix)
    {
        int maxValue = colorMatrix.m_maxValue;
        RgbColor newColor(maxValue);
        newColor.setColor(scalar * (float)colorMatrix.getColorR(), scalar * (float)colorMatrix.getColorG(),
                          scalar * (float)colorMatrix.getColorB());
        return newColor;
    }

    RgbColor operator*(const RgbColor &colorMatrix, float scalar)
    {
        return scalar * colorMatrix;
    }

    RgbColor::RgbColor(int R, int G, int B) : m_maxValue{std::numeric_limits<int>::max()}
    {
        setColor(R, G, B);
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // Tools