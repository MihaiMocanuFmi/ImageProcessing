//
// Created by mihai on 3/27/23.
//

#include "Kernels.h"


IdentityKernel::IdentityKernel()
{
    tools::Vector2I size(3,3);
    tools::RgbColor color({0,0,0});
    kernel = ColorData(size, color);
    kernel.at(1, 1).setColor(1, 1, 1);

}

void IdentityKernel::scalingMethod(ColorData &outColorData)
{
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MeanBlurKernel::MeanBlurKernel()
{
    tools::Vector2I size(3,3);
    tools::RgbColor color({0,0,0});
    kernel = ColorData(size, color);
}

void MeanBlurKernel::scalingMethod(ColorData &outColorData)
{
    for (int y = 0; y < outColorData.size().y; ++y)
        for (int x = 0; x < outColorData.size().x; ++x)
            outColorData.at(x, y) = (1.0f/9) * outColorData.at(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GaussianBlur3x3Kernel::GaussianBlur3x3Kernel()
{
    tools::Vector2I size(3,3);
    kernel = ColorData(size);
    kernel.at(0, 0) = kernel.at(2, 2) = kernel.at(0, 2) = kernel.at(2, 2) = 1;
    kernel.at(1, 0) = kernel.at(0, 1) = kernel.at(2, 1) = kernel.at(1, 2) = 2;
    kernel.at(1, 1) = 4;
}

void GaussianBlur3x3Kernel::scalingMethod(ColorData &outColorData)
{
    for (int y = 0; y < outColorData.size().y; ++y)
        for (int x = 0; x < outColorData.size().x; ++x)
            outColorData.at(x, y) = (1.0f/16) * outColorData.at(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

HorizontalSobelKernel::HorizontalSobelKernel()
{
    tools::Vector2I size(3,3);
    kernel = ColorData(size);
    kernel.at(0, 0) = kernel.at(2, 0) = 1;
    kernel.at(1, 0) = 2;

    kernel.at(0, 1) = kernel.at(1, 1) = kernel.at(2, 1) = 0;

    kernel.at(0, 2) = kernel.at(2, 2) = -1;
    kernel.at(1, 2) = -2;

}


void HorizontalSobelKernel::scalingMethod(ColorData &outColorData)
{
    for (int y = 0; y < outColorData.size().y; ++y)
    {
        for (int x = 0; x < outColorData.size().x; ++x)
        {
            /*
            //Considering just for this example that outColorData.globalMaxValue() = 255;
            //making the range [-255, 255]
            outColorData.at(x, y) = (1.0f / 4) * outColorData.at(x, y);

            //making the range [0, 2 * 255]
            outColorData.at(x, y) = outColorData.globalMaxValue() + outColorData.at(x, y);

            //making the range [0, 255]
            outColorData.at(x, y) = (1.0f / 2) * outColorData.at(x, y);
            */
            //One line to decrease float approximation errors caused by casts back to int
            outColorData.at(x, y) = (1.0f/2) * ( (1.0f / 4) * outColorData.at(x, y) + outColorData.globalMaxValue() );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


VerticalSobelKernel::VerticalSobelKernel()
{
    tools::Vector2I size(3,3);
    kernel = ColorData(size);
    kernel.at(2, 0) = kernel.at(2, 2) = 1;
    kernel.at(2, 1) = 2;

    kernel.at(1, 0) = kernel.at(1, 1) = kernel.at(1, 2) = 0;

    kernel.at(0, 0) = kernel.at(0, 2) = -1;
    kernel.at(0, 1) = -2;
}

void VerticalSobelKernel::scalingMethod(ColorData &outColorData)
{
    for (int y = 0; y < outColorData.size().y; ++y)
    {
        for (int x = 0; x < outColorData.size().x; ++x)
        {
            //making the range [-255, 255]
            outColorData.at(x, y) = (1.0f / 4) * outColorData.at(x, y);

            //making the range [0, 2 * 255]
            outColorData.at(x, y) = outColorData.globalMaxValue() + outColorData.at(x, y);

            //making the range [0, 255]
            outColorData.at(x, y) = (1.0f / 2) * outColorData.at(x, y);
            */
            //One line to decrease float approximation errors caused by casts back to int
            outColorData.at(x, y) = (1.0f/2) * ( (1.0f / 4) * outColorData.at(x, y) + outColorData.globalMaxValue() );
        }
    }
}
