#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "PortablePixMap_Plain.h"
#include "tools/Vector2.h"
#include "tools/Rectangle.h"
#include "ColorData.h"

class Image
{
private:
    //tools::Vector2U m_size = {};

    PortablePixMap_Plain ppm = {};
    ColorData m_colorData = {};

public:
    Image() = default;

    Image(unsigned int width, unsigned int height);
    Image(const ColorData &colorData);
    explicit Image(tools::Vector2U size);

    bool load(std::string imagePath);
    bool save(std::string imagePath);


    bool getROI(Image &roiImg, tools::Rectangle roiRect);
    bool getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);


    Image operator+(const Image &i);
    Image operator-(const Image &i);
    Image operator*(const Image &i);

    friend Image operator+(float scalar, const Image &image);
    friend Image operator+(const Image &image, float scalar);

    friend Image operator-(float scalar, const Image &image);
    friend Image operator-(const Image &image, float scalar);

    friend Image operator*(float scalar, const Image &image);
    friend Image operator*(const Image &image, float scalar);

};



#endif //IMAGE_H
