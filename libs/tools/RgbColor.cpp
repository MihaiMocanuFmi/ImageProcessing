#include "RgbColor.h"

#include <algorithm>

namespace tools
{
    /////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

    /////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

    RgbColor::RgbColor()
    {
        m_maxValue = 0;
        setColor(0,0,0);
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





} // tools