#include "RgbColor.h"

#include <algorithm>

namespace tools
{
    /////////////////////////PRIVATE////////////////////////////////////////////

    /////////////////////////PUBLIC/////////////////////////////////////////////
    RgbColor::RgbColor()
    {
        m_maxValue = EIGHT_BIT;
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

    void RgbColor::setColor(unsigned int R, unsigned int G, unsigned int B)
    {
        setColorR(R);
        setColorG(G);
        setColorB(B);
    }

    void RgbColor::setColorR(unsigned int R)
    {
        m_color.R = std::clamp<unsigned int>(R, 0, m_maxValue);
    }

    void RgbColor::setColorG(unsigned int G)
    {
        m_color.G = std::clamp<unsigned int>(G, 0, m_maxValue);
    }

    void RgbColor::setColorB(unsigned int B)
    {
        m_color.B = std::clamp<unsigned int>(B, 0, m_maxValue);
    }

} // tools