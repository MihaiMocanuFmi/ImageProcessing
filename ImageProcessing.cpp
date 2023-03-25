#include <iostream>

#include "libs/Image.h"
#include "libs/PortablePixMap_Plain.h"
#include "libs/tools/Rectangle.h"

int main()
{
    //TODO: operator overload
    //TODO: matrix [][]?
    Image image;

    if (image.load("input.ppm"))
    {
        Image newImage;

        tools::Rectangle roi({100,100}, {image.size().x - 100, image.size().y - 100});
        image.getROI(newImage, roi);

        if(not newImage.save("output2.ppm"))
            std::cout << "Error on save";


        if(not image.save("output.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";


    return 0;
}
