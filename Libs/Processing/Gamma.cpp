#include "Gamma.h"

#include <cmath>

Gamma::Gamma() : m_gamma(1)
{

}

Gamma::Gamma(float gamma)
{
    setGamma(gamma);
}

void Gamma::process(const Image &src, Image &dst)
{
    /*
     * R = pow(r', Gamma)
     * G = pow(g', Gamma)
     * B = pow(b', Gamma)
     * where R, G, B are in the interval [0, 1], therefore r' = r/maxValue;
     */
    dst = Image(src.size());
    for (int y = 0; y < src.size().y; ++y)
        for (int x = 0; x < src.size().x; ++x)
        {
            double r = src.at(x, y).getColorR();
            double g = src.at(x, y).getColorG();
            double b = src.at(x, y).getColorB();

            //we convert r so that it is in the interval [0, 1]
            r = r / src.data().MAX_VALUE;
            g = g / src.data().MAX_VALUE;
            b = b / src.data().MAX_VALUE;

            //we raise every component to the power of gamma (they are still in [0, 1])
            double R = std::pow(r, 1/m_gamma);
            double G = std::pow(g, 1/m_gamma); //perhaps 1/gamma
            double B = std::pow(b, 1/m_gamma);

            //we convert it back to the original range of [0, src.globalMaxValue()];
            R *= src.data().MAX_VALUE;
            G *= src.data().MAX_VALUE;
            B *= src.data().MAX_VALUE;

            dst.at(x, y) = tools::RgbColor(R, G, B);

        }
}

void Gamma::setGamma(float gamma)
{
    if(gamma <= 0)
        gamma = 0.0001;
    m_gamma = gamma;
}

float Gamma::getGamma() const
{
    return m_gamma;
}
