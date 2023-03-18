#include <iostream>

#include "libs/Image.h"
#include "libs/PortablePixMap_Plain.h"

int main()
{
    PortablePixMap_Plain ppm;

    std::string imageStr = "P3           # P3 means this is a RGB color image in ASCII\n"
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
    ppm.loadPlain(imageStr);
    return 0;
}
