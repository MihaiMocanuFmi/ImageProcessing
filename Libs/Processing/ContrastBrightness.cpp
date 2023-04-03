#include "ContrastBrightness.h"

ContrastBrightness::ContrastBrightness() : m_alpha(1), m_beta(0)
{

}

ContrastBrightness::ContrastBrightness(float alpha, float beta)
{
    setAlpha(alpha);
    setBeta(beta);
}

void ContrastBrightness::process(const Image &src, Image &dst)
{
    //F(x,y) = α⋅I(x,y) + β
    //Let I(x,y) be a R^3 vector, where R, G, B represents the vector basis.
    //Therefore we can consider I(x, y) to have the following representation (r, g, b);
    //It follows that (r', g', b') = (a*r + β, a*g + β, a*b + β);
    dst = Image(src.size());
    for (int y = 0; y < src.size().y; ++y)
        for (int x = 0; x < src.size().x; ++x)
            dst.at(x, y) = m_alpha * src.at(x, y) + m_beta;

}

void ContrastBrightness::setAlpha(float alpha)
{
    if (alpha <= 0)
        alpha = 0.000000000001;


    m_alpha = alpha;
}

float ContrastBrightness::getAlpha() const
{
    return m_alpha;
}

void ContrastBrightness::setBeta(float beta)
{
    m_beta = beta;
}

float ContrastBrightness::getBeta() const
{
    return m_beta;
}


