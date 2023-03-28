#include "Convolution.h"

using namespace Kernels;

tools::RgbColor Convolution::m_multiplyWithKernel(const ColorData &colorData, tools::Vector2I position)
{
    tools::RgbColor result;
    //we don't want any boundaries for pixel values
    result.setColor(0, 0, 0);

    for (int y = 0; y < m_kernel.size().y; ++y)
    {
        for (int x = 0; x < m_kernel.size().x; ++x)
        {
            tools::Vector2I indexInColorData = position + tools::Vector2I(x - 1, y - 1);

            //If we get outside the bounds of the ColorDataMatrix, then we consider the nearest pixel inside the matrix
            if(indexInColorData.x <= -1)
                indexInColorData.x = 0;
            else if(indexInColorData.x >= colorData.size().x)
                indexInColorData.x = colorData.size().x - 1;

            if(indexInColorData.y <= -1)
                indexInColorData.y = 0;
            else if(indexInColorData.y >= colorData.size().y)
                indexInColorData.y = colorData.size().y - 1;

            result = result + m_kernel.at(x, y) * colorData.at(indexInColorData);
        }

    }

    return result;
}

/////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

/////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

Convolution::Convolution()
{
    m_kernel = IdentityKernel().kernel;
    m_scaling = IdentityKernel::scalingMethod;
}

Convolution::Convolution(const ColorData &kernel, ScalingMethod method) : m_kernel{kernel}, m_scaling{method}
{

}

void Convolution::process(const Image &src, Image &dst)
{
    //dst = Image(src.size(), src.globalMaxValue());

    //we dont want any bounds for now;

    ColorData buffer(src.size(), src.globalMaxValue());

    for (int y = 0; y < src.size().y; ++y)
        for (int x = 0; x < src.size().x; ++x)
        {
            tools::RgbColor result = m_multiplyWithKernel( src.data(), {x, y});
            buffer.at(x, y) = result;
        }

    m_scaling(buffer);
    dst = Image(buffer);
}

ColorData &Convolution::getKernel()
{
    return m_kernel;
}

const ColorData &Convolution::getKernel() const
{
    return m_kernel;
}

ScalingMethod &Convolution::getScalingMethod()
{
    return m_scaling;
}

const ScalingMethod &Convolution::getScalingMethod() const
{
    return m_scaling;
}

