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
    //tools::Vector2I m_size = {};

    PortablePixMap_Plain ppm = {};
    ColorData m_colorData = {};

public:
    Image() = default;

    Image(int width, int height);
    Image(const ColorData &colorData);
    explicit Image(tools::Vector2I size);

    bool load(std::string imagePath);
    bool save(std::string imagePath);


    bool getROI(Image &roiImg, tools::Rectangle roiRect);
    bool getROI(Image &roiImg, int x, int y, int width, int height);

    bool isEmpty() const;
    void release();

    tools::Vector2I size() const;

    tools::RgbColor& at(const tools::Vector2I &position);
    tools::RgbColor& at(int x, int y);

    const tools::RgbColor& at(const tools::Vector2I &position) const;
    const tools::RgbColor& at(int x, int y) const;

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
