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
        Image newImage;
        Convolution convolution(Kernels::GaussianBlur3x3Kernel().kernel,Kernels::GaussianBlur3x3Kernel::scalingMethod);
        convolution.process(image, newImage);

        if(not newImage.save("output2.ppm"))
            std::cout << "Error on save";


        if(not image.save("output.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";


    return 0;
}
