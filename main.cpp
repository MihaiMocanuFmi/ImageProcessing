#include <iostream>

#include "Libs/Image/Image.h"
#include "Libs/Tools/Rectangle.h"
#include "Libs/Processing/Gamma.h"
#include "Libs/Processing/Convolution.h"
#include "Libs/Processing/ContrastBrightness.h"
#include "Libs/Processing/Gamma.h"

int main()
{

    Image image;

    if (image.load("input.ppm"))
    {
        Image verticalImage;
        Convolution convolutionVert(Kernels::VerticalSobelKernel().kernel, Kernels::VerticalSobelKernel::scalingMethod);
        convolutionVert.process(image, verticalImage);

        if(not verticalImage.save("0_vertical.ppm"))
            std::cout << "Error on save";

        Image horizontal;
        Convolution convolutionHoriz(Kernels::HorizontalSobelKernel().kernel, Kernels::HorizontalSobelKernel::scalingMethod);
        convolutionHoriz.process(image, horizontal);

        if(not horizontal.save("1_horizontal.ppm"))
            std::cout << "Error on save";


        Image composition = verticalImage + horizontal;
        if(not composition.save("2_composition.ppm"))
            std::cout << "Error on save";

        Image gaussBlur;
        Convolution convolutionGaussBlur(Kernels::GaussianBlur3x3Kernel().kernel, Kernels::GaussianBlur3x3Kernel::scalingMethod);
        convolutionGaussBlur.process(image, gaussBlur);
        if(not gaussBlur.save("3_gaussBlur.ppm"))
            std::cout << "Error on save";

        Image meanBlur;
        Convolution convolutionMeanBlur(Kernels::MeanBlurKernel().kernel, Kernels::MeanBlurKernel::scalingMethod);
        convolutionMeanBlur.process(image, meanBlur);
        if(not meanBlur.save("4_meanBlur.ppm"))
            std::cout << "Error on save";

        Image identity;
        Convolution convolutionIdentity(Kernels::IdentityKernel().kernel, Kernels::IdentityKernel::scalingMethod);
        convolutionIdentity.process(image, identity);
        if(not identity.save("5_identity.ppm"))
            std::cout << "Error on save";

        Image contrast;
        ContrastBrightness contrastBrightness(1.5, 0.55);
        contrastBrightness.process(image, contrast);
        if(not contrast.save("6_contrast.ppm"))
            std::cout << "Error on save";

        Image gamma;
        Gamma gammaProcess(0.44);
        gammaProcess.process(image, gamma);
        if(not gamma.save("7_gamma.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";


    return 0;
}
