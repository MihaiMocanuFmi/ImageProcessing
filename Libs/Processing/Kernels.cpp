//
// Created by mihai on 3/27/23.
//

#include "Kernels.h"


namespace Kernels
{
    void KernelType::scalingMethod(ImageData &outColorData)
    {
        return;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    IdentityKernel::IdentityKernel()
    {
        tools::Vector2I size(3, 3);
        tools::RgbColor color(0, 0, 0);
        kernel = ImageData(size, color);
        kernel.at(1, 1).setColor(1, 1, 1);

    }

    void IdentityKernel::scalingMethod(ImageData &outColorData)
    {
        return;
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MeanBlurKernel::MeanBlurKernel()
    {
        tools::Vector2I size(3, 3);
        tools::RgbColor color(1, 1, 1);
        kernel = ImageData(size, color);
    }

    void MeanBlurKernel::scalingMethod(ImageData &outColorData)
    {
        for (int y = 0; y < outColorData.size().y; ++y)
            for (int x = 0; x < outColorData.size().x; ++x)
                outColorData.at(x, y) = (1.0f / 9) * outColorData.at(x, y);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    GaussianBlur3x3Kernel::GaussianBlur3x3Kernel()
    {
        tools::Vector2I size(3, 3);
        kernel = ImageData(size);
        kernel.at(0, 0) = kernel.at(2, 0) = kernel.at(0, 2) = kernel.at(2, 2) = tools::RgbColor(1,1,1);
        kernel.at(1, 0) = kernel.at(0, 1) = kernel.at(2, 1) = kernel.at(1, 2) = tools::RgbColor(2,2,2);
        kernel.at(1, 1) = tools::RgbColor(4,4,4);
    }

    void GaussianBlur3x3Kernel::scalingMethod(ImageData &outImageData)
    {
        for (int y = 0; y < outImageData.size().y; ++y)
            for (int x = 0; x < outImageData.size().x; ++x)
                outImageData.at(x, y) = (1.0f / 16) * outImageData.at(x, y);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    HorizontalSobelKernel::HorizontalSobelKernel()
    {
        tools::Vector2I size(3, 3);

        kernel = ImageData(size);
        kernel.at(0, 0) = kernel.at(2, 0) = tools::RgbColor(1,1,1, true);
        kernel.at(1, 0) = tools::RgbColor(2,2,2, true);

        kernel.at(0, 1) = kernel.at(1, 1) = kernel.at(2, 1) = tools::RgbColor(0,0,0, true);

        kernel.at(0, 2) = kernel.at(2, 2) = tools::RgbColor(-1,-1,-1, true);
        kernel.at(1, 2) = tools::RgbColor(-2,-2,-2, true);

    }


    void HorizontalSobelKernel::scalingMethod(ImageData &ouImageData)
    {
        for (int y = 0; y < ouImageData.size().y; ++y)
        {
            for (int x = 0; x < ouImageData.size().x; ++x)
            {
                /*
                //Considering just for this example that ouImageData.globalMaxValue() = 255;
                //making the range from [-4 * 255, 4 * 255] into [-255, 255]
                //then we make the range [0, 2 * 255]
                //followed by making the range [0, 255]
                */
                //One line to decrease float approximation errors caused by casts back to int
                float R = (1.0f / 2) * ((1.0f / 4) * ouImageData.at(x, y).getColorR() + ouImageData.MAX_VALUE);
                float G = (1.0f / 2) * ((1.0f / 4) * ouImageData.at(x, y).getColorG() + ouImageData.MAX_VALUE);
                float B = (1.0f / 2) * ((1.0f / 4) * ouImageData.at(x, y).getColorB() + ouImageData.MAX_VALUE);
                ouImageData.at(x, y) = tools::RgbColor(R, G, B);
            }
        }
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    VerticalSobelKernel::VerticalSobelKernel()
    {
        tools::Vector2I size(3, 3);

        kernel = ImageData(size);
        kernel.at(0, 0) = kernel.at(0, 2) = tools::RgbColor(-1,-1,-1, true);
        kernel.at(0, 1) = tools::RgbColor(-2,-2,-2, true);

        kernel.at(1, 0) = kernel.at(1, 1) = kernel.at(1, 2) = tools::RgbColor(0,0,0, true);

        kernel.at(2, 0) = kernel.at(2, 2) = tools::RgbColor(1,1,1, true);
        kernel.at(2, 1) = tools::RgbColor(2,2,2, true);
    }

    void VerticalSobelKernel::scalingMethod(ImageData &outImageData)
    {
        for (int y = 0; y < outImageData.size().y; ++y)
        {
            for (int x = 0; x < outImageData.size().x; ++x)
            {
                /*
                //Considering just for this example that outImageData.globalMaxValue() = 255;
                //making the range from [-4 * 255, 4 * 255] into [-255, 255]
                //then we make the range [0, 2 * 255]
                //followed by making the range [0, 255]
                */
                //One line to decrease float approximation errors caused by casts back to int
                float R = (1.0f / 2) * ((1.0f / 4) * outImageData.at(x, y).getColorR() + outImageData.MAX_VALUE);
                float G = (1.0f / 2) * ((1.0f / 4) * outImageData.at(x, y).getColorG() + outImageData.MAX_VALUE);
                float B = (1.0f / 2) * ((1.0f / 4) * outImageData.at(x, y).getColorB() + outImageData.MAX_VALUE);
                outImageData.at(x, y) = tools::RgbColor(R, G, B);
            }
        }
    }

}