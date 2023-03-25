#include <iostream>

#include "libs/Image.h"
#include "libs/PortablePixMap_Plain.h"

int main()
{
    //TODO: operator overload
    //TODO: matrix [][]?
    Image image;

    if (image.load("input.ppm"))
    {
        std::cout << image;
        if(not image.save("output.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";


    return 0;
}
