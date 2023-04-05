#include "Convolution.h"

using namespace Kernels;

tools::RgbColor Convolution::m_multiplyWithKernel(const ImageData &imageData, tools::Vector2I position)
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
            else if(indexInColorData.x >= imageData.size().x)
                indexInColorData.x = imageData.size().x - 1;

            if(indexInColorData.y <= -1)
                indexInColorData.y = 0;
            else if(indexInColorData.y >= imageData.size().y)
                indexInColorData.y = imageData.size().y - 1;

            float R = result.getColorR() + m_kernel.at(x, y).getColorR() * imageData.at(indexInColorData).getColorR();
            float G = result.getColorG() + m_kernel.at(x, y).getColorG() * imageData.at(indexInColorData).getColorG();
            float B = result.getColorB() + m_kernel.at(x, y).getColorB() * imageData.at(indexInColorData).getColorB();
            result = tools::RgbColor(R, G, B, true);
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

Convolution::Convolution(const ImageData &kernel, ScalingMethod method) : m_kernel{kernel}, m_scaling{method}
{

}

void Convolution::process(const Image &src, Image &dst)
{
    //dst = Image(src.size(), src.globalMaxValue());

    //we dont want any bounds for now;

    ImageData buffer(src.size());

    for (int y = 0; y < src.size().y; ++y)
        for (int x = 0; x < src.size().x; ++x)
            buffer.at(x, y) =  m_multiplyWithKernel(src.data(), {x, y});;


    m_scaling(buffer);
    dst = Image(buffer);
}

ImageData &Convolution::getKernel()
{
    return m_kernel;
}

const ImageData &Convolution::getKernel() const
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

