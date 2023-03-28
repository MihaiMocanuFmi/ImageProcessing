#include <iostream>

#include "Libs/Image/Image.h"
#include "Libs/Tools/Rectangle.h"
#include "Libs/Processing/Gamma.h"
#include "Libs/Processing/Convolution.h"
int main()
{
    Image image;

    if (image.load("input.ppm"))
    {
        Image verticalImage;
        Convolution convolutionVert(Kernels::VerticalSobelKernel().kernel, Kernels::VerticalSobelKernel::scalingMethod);
        convolutionVert.process(image, verticalImage);

        if(not verticalImage.save("vertical.ppm"))
            std::cout << "Error on save";

        Image horizontal;
        Convolution convolutionHoriz(Kernels::HorizontalSobelKernel().kernel, Kernels::HorizontalSobelKernel::scalingMethod);
        convolutionHoriz.process(image, horizontal);

        if(not horizontal.save("horizontal.ppm"))
            std::cout << "Error on save";

        Image composition = verticalImage + horizontal;
        if(not composition.save("composition.ppm"))
            std::cout << "Error on save";

    }
    else
        std::cout << "Error on load";


    return 0;
}
