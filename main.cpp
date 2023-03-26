#include <iostream>

#include "Libs/Image/Image.h"
#include "Libs/Tools/Rectangle.h"
#include "Libs/Processing/Gamma.h"
int main()
{
    //TODO: operator overload
    //TODO: matrix [][]?
    Image image;

    if (image.load("input.ppm"))
    {
        Image newImage;
        Gamma Gamma(0.44);
        Gamma.process(image, newImage);

        if(not newImage.save("output2.ppm"))
            std::cout << "Error on save";


        if(not image.save("output.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";


    return 0;
}
