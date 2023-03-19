#include <iostream>

#include "libs/Image.h"
#include "libs/PortablePixMap_Plain.h"

int main()
{
    /*
    PortablePixMap_Plain ppm;

    std::string imageStr = "P21           # P3 means this is a RGB color image in ASCII\n"
                           "3 2          # 3 2 is the width and height of the image in pixels\n"
                           "255          # 255 is the maximum value for each color\n"
                           "# The part above is the header\n"
                           "# The part below is the image data: RGB triplets\n"
                           "255   0   0  # red\n"
                           "0 255   0  # green\n"
                           "0   0 255  # blue\n"
                           "255 255   0  # yellow\n"
                           "255 255 255  # white\n"
                           "0   0   0  # black";

    std::cout << "#############################Original################################\n\n"
              << imageStr << "\n\n"
              << "#############################Original#############################\n\n";

    ppm.loadPlain(imageStr);

    std::string convertedImageStr;
    ppm.saveToString(convertedImageStr);
    std::cout << "#############################Conversion1################################\n\n"
              << convertedImageStr << "\n\n"
              << "#############################End-Conversion1#############################\n\n";

    PortablePixMap_Plain ppm2;
    ppm2.loadPlain(convertedImageStr);

    std::string convertedImageStr2;
    ppm.saveToString(convertedImageStr2);

    std::cout << "#############################Conversion2################################\n\n"
              << convertedImageStr2 << "\n\n"
              << "#############################End-Conversion2#############################\n\n";

    */
    Image image;

    if (image.load("input.ppm"))
    {
        if(not image.save("output.ppm"))
            std::cout << "Error on save";
    }
    else
        std::cout << "Error on load";

    /*
    for (int i = 0; i < 100; ++i)
    {
        image.load("output.ppm");

        image.save("output.ppm");

        std::cout << (i + 1) << "/100" << '\n';
    }
     */
    return 0;
}
