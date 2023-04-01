//
// Created by mihai on 3/27/23.
//

#include "Kernels.h"


namespace Kernels
{
    void KernelType::scalingMethod(ColorData &outColorData)
    {
        return;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    IdentityKernel::IdentityKernel()
    {
        tools::Vector2I size(3, 3);
        tools::RgbColor color(0, 0, 0);
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
        tools::Vector2I size(3, 3);
        tools::RgbColor color(1, 1, 1);
        kernel = ColorData(size, color);
    }

    void MeanBlurKernel::scalingMethod(ColorData &outColorData)
    {
        for (int y = 0; y < outColorData.size().y; ++y)
            for (int x = 0; x < outColorData.size().x; ++x)
                outColorData.at(x, y) = (1.0f / 9) * outColorData.at(x, y);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GaussianBlur3x3Kernel::GaussianBlur3x3Kernel()
    {
        tools::Vector2I size(3, 3);
        kernel = ColorData(size);
        kernel.at(0, 0) = kernel.at(2, 0) = kernel.at(0, 2) = kernel.at(2, 2) = tools::RgbColor(1,1,1);
        kernel.at(1, 0) = kernel.at(0, 1) = kernel.at(2, 1) = kernel.at(1, 2) = tools::RgbColor(2,2,2);
        kernel.at(1, 1) = tools::RgbColor(4,4,4);
    }

    void GaussianBlur3x3Kernel::scalingMethod(ColorData &outColorData)
    {
        for (int y = 0; y < outColorData.size().y; ++y)
            for (int x = 0; x < outColorData.size().x; ++x)
                outColorData.at(x, y) = (1.0f / 16) * outColorData.at(x, y);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HorizontalSobelKernel::HorizontalSobelKernel()
    {
        tools::Vector2I size(3, 3);

        kernel = ColorData(size);
        kernel.at(0, 0) = kernel.at(2, 0) = tools::RgbColor(1,1,1, true);
        kernel.at(1, 0) = tools::RgbColor(2,2,2, true);

        kernel.at(0, 1) = kernel.at(1, 1) = kernel.at(2, 1) = tools::RgbColor(0,0,0, true);

        kernel.at(0, 2) = kernel.at(2, 2) = tools::RgbColor(-1,-1,-1, true);
        kernel.at(1, 2) = tools::RgbColor(-2,-2,-2, true);

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
                tools::RgbColor color = (1.0f / 2) * ((1.0f / 4) * outColorData.at(x, y) + outColorData.MAX_VALUE);
                outColorData.at(x, y) = color;
            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    VerticalSobelKernel::VerticalSobelKernel()
    {
        tools::Vector2I size(3, 3);

        kernel = ColorData(size);
        kernel.at(0, 0) = kernel.at(0, 2) = tools::RgbColor(-1,-1,-1, true);
        kernel.at(0, 1) = tools::RgbColor(-2,-2,-2, true);

        kernel.at(1, 0) = kernel.at(1, 1) = kernel.at(1, 2) = tools::RgbColor(0,0,0, true);

        kernel.at(2, 0) = kernel.at(2, 2) = tools::RgbColor(1,1,1, true);
        kernel.at(2, 1) = tools::RgbColor(2,2,2, true);
    }

    void VerticalSobelKernel::scalingMethod(ColorData &outColorData)
    {
        for (int y = 0; y < outColorData.size().y; ++y)
        {
            for (int x = 0; x < outColorData.size().x; ++x)
            {
                /*
                //Considering just for this example that outColorData.globalMaxValue() = 255;
                //making the range from [-4 * 255, 4 * 255] into [-255, 255]
                outColorData.at(x, y) = (1.0f / 4) * outColorData.at(x, y);

                //making the range [0, 2 * 255]
                outColorData.at(x, y) = outColorData.globalMaxValue() + outColorData.at(x, y);

                //making the range [0, 255]
                outColorData.at(x, y) = (1.0f / 2) * outColorData.at(x, y);
                */
                //One line to decrease float approximation errors caused by casts back to int
                tools::RgbColor color = (1.0f / 2) * ((1.0f / 4) * outColorData.at(x, y) + outColorData.MAX_VALUE);
                outColorData.at(x, y) = color;
            }
        }
    }

}