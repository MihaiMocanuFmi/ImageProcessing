#include <iostream>
#include <random>

#include "Libs/Image/Image.h"
#include "Libs/Tools/Rectangle.h"
#include "Libs/Processing/Gamma.h"
#include "Libs/Processing/Convolution.h"
#include "Libs/Processing/ContrastBrightness.h"
#include "Libs/Processing/Gamma.h"
#include "Libs/Draw/Draw.h"


/// Main function, contains an example for all abilities
/// \return
int main()
{

    Image image;

    if (image.load("input.ppm"))
    {

        Image verticalImage;
        Convolution convolutionVert(Kernels::VerticalSobelKernel().kernel, Kernels::VerticalSobelKernel::scalingMethod);
        convolutionVert.process(image, verticalImage);

        if(not verticalImage.save("00_vertical.ppm"))
            std::cout << "Error on save";

        Image horizontal;
        Convolution convolutionHoriz(Kernels::HorizontalSobelKernel().kernel, Kernels::HorizontalSobelKernel::scalingMethod);
        convolutionHoriz.process(image, horizontal);

        if(not horizontal.save("01_horizontal.ppm"))
            std::cout << "Error on save";


        Image composition = (1/ 2.0f) * verticalImage + (1/ 2.0f) * horizontal;
        if(not composition.save("02_composition.ppm"))
            std::cout << "Error on save";

        Image gaussBlur;
        Convolution convolutionGaussBlur(Kernels::GaussianBlur3x3Kernel().kernel, Kernels::GaussianBlur3x3Kernel::scalingMethod);
        convolutionGaussBlur.process(image, gaussBlur);
        if(not gaussBlur.save("03_gaussBlur.ppm"))
            std::cout << "Error on save";

        Image meanBlur;
        Convolution convolutionMeanBlur(Kernels::MeanBlurKernel().kernel, Kernels::MeanBlurKernel::scalingMethod);
        convolutionMeanBlur.process(image, meanBlur);
        if(not meanBlur.save("04_meanBlur.ppm"))
            std::cout << "Error on save";

        Image identity;
        Convolution convolutionIdentity(Kernels::IdentityKernel().kernel, Kernels::IdentityKernel::scalingMethod);
        convolutionIdentity.process(image, identity);
        if(not identity.save("05_identity.ppm"))
            std::cout << "Error on save";

        Image contrast;
        ContrastBrightness contrastBrightness(1.5, 0.55);
        contrastBrightness.process(image, contrast);
        if(not contrast.save("06_contrast.ppm"))
            std::cout << "Error on save";

        Image gamma;
        Gamma gammaProcess(0.44);
        gammaProcess.process(image, gamma);
        if(not gamma.save("07_gamma.ppm"))
            std::cout << "Error on save";


        Image circle = image;
        float k = 2;
        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(0, 255); // define the range
        int radius = k * image.size().x/2;
        for (int i = radius; i >= 0; --i)
            Draw::drawCircle(circle, image.size() / 2, i, tools::RgbColor(distr(gen), distr(gen), distr(gen)));

        if(not circle.save("08_circle.ppm"))
            std::cout << "Error on save";


        Image line = image;
        Draw::drawLine(line, {0, 0}, image.size(), tools::RgbColor(0, 0, 0));
        if(not line.save("09_line.ppm"))
            std::cout << "Error on save";

        Image rectangle = image;
        Draw::drawRectangle(rectangle, tools::Rectangle(100,100, 1000, 1000), tools::RgbColor(0, 0, 0));
        if(not rectangle.save("10_rectangle.ppm"))
            std::cout << "Error on save";

    }
    else
        std::cout << "Error on load";


    return 0;
}
