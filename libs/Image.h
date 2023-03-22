#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "PortablePixMap_Plain.h"
#include "tools/Vector2.h"
#include "tools/Rectangle.h";


class Image
{
private:
    tools::Vector2U m_size = {};

    PortablePixMap_Plain ppm = {};

public:
    Image() = default;

    Image(unsigned int width, unsigned int height);
    explicit Image(tools::Vector2U size);

    bool load(std::string imagePath);
    bool save(std::string imagePath);

    Image operator+(const Image &i);
    Image operator-(const Image &i);
    Image operator*(const Image &i);
    friend Image operator*(float scalar, const Image &image);

    bool getROI(Image &roiImg, tools::Rectangle roiRect);
    bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);


};



#endif //IMAGE_H
