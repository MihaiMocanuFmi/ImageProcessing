#include "RgbColor.h"

#include <algorithm>
#include <limits>

namespace tools
{
    /////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

    /////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

    RgbColor::RgbColor()
    {
        m_maxValue = 0;
        setColor(0,0,0);
    }

    RgbColor::RgbColor(const Color &color) : m_color{color}, m_maxValue{std::numeric_limits<unsigned int>::max()}
    {

    }

    RgbColor::RgbColor(unsigned int maxValue) : m_maxValue{maxValue}
    {
        setColor(0,0,0);
    }

    RgbColor::RgbColor(unsigned int maxValue, unsigned int R, unsigned int G, unsigned int B) : m_maxValue{maxValue}
    {
        setColor(R,G,B);
    }

    RgbColor::RgbColor(unsigned int maxValue, const RgbColor::Color &color) : m_maxValue{maxValue}
    {
        setColor(color);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setMaxValue(unsigned int maxValue)
    {
        m_maxValue = maxValue;
    }

    unsigned int RgbColor::getMaxValue() const
    {
        return m_maxValue;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColor(unsigned int R, unsigned int G, unsigned int B)
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

    void RgbColor::setColorR(unsigned int R)
    {
        m_color.R = std::clamp<unsigned int>(R, 0, m_maxValue);
    }
    unsigned int RgbColor::getColorR() const
    {
        return m_color.R;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorG(unsigned int G)
    {
        m_color.G = std::clamp<unsigned int>(G, 0, m_maxValue);
    }

    unsigned int RgbColor::getColorG() const
    {
        return m_color.G;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void RgbColor::setColorB(unsigned int B)
    {
        m_color.B = std::clamp<unsigned int>(B, 0, m_maxValue);
    }

    unsigned int RgbColor::getColorB() const
    {
        return m_color.B;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator+(const RgbColor &other) const
    {
        unsigned int maxValue = this->m_maxValue + other.m_maxValue;
        unsigned int R = this->getColorR() + other.getColorR();
        unsigned int G = this->getColorG() + other.getColorG();
        unsigned int B = this->getColorB() + other.getColorB();
        return {maxValue, R, G, B};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator-(const RgbColor &other) const
    {
        unsigned int maxValue = (this->m_maxValue > other.m_maxValue)? this->m_maxValue : other.m_maxValue;
        unsigned int R = this->getColorR() - other.getColorR();
        unsigned int G = this->getColorG() - other.getColorG();
        unsigned int B = this->getColorB() - other.getColorB();
        return {maxValue, R, G, B};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor RgbColor::operator*(const RgbColor &other)
    {
        unsigned int maxValue = this->m_maxValue * other.m_maxValue;
        unsigned int R = this->getColorR() * other.getColorR();
        unsigned int G = this->getColorG() * other.getColorG();
        unsigned int B = this->getColorB() * other.getColorB();
        return {maxValue, R, G, B};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator+(float scalar, const RgbColor &colorMatrix)
    {
        unsigned int maxValue = scalar + (float)colorMatrix.m_maxValue;
        unsigned int R = scalar + (float)colorMatrix.getColorR();
        unsigned int G = scalar + (float)colorMatrix.getColorG();
        unsigned int B = scalar + (float)colorMatrix.getColorB();
        return {maxValue, R, G, B};
    }

    RgbColor operator+(const RgbColor &colorMatrix, float scalar)
    {
        return scalar + colorMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator-(float scalar, const RgbColor &colorMatrix)
    {
        unsigned int maxValue = colorMatrix.m_maxValue;
        unsigned int R = scalar - (float)colorMatrix.getColorR();
        unsigned int G = scalar - (float)colorMatrix.getColorG();
        unsigned int B = scalar - (float)colorMatrix.getColorB();
        return {maxValue, R, G, B};
    }

    RgbColor operator-(const RgbColor &colorMatrix, float scalar)
    {
        return -scalar + colorMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    RgbColor operator*(float scalar, const RgbColor &colorMatrix)
    {
        unsigned int maxValue = scalar * (float)colorMatrix.m_maxValue;
        unsigned int R = scalar - (float)colorMatrix.getColorR();
        unsigned int G = scalar - (float)colorMatrix.getColorG();
        unsigned int B = scalar - (float)colorMatrix.getColorB();
        return {maxValue, R, G, B};
    }

    RgbColor operator*(const RgbColor &colorMatrix, float scalar)
    {
        return scalar * colorMatrix;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////


} // tools