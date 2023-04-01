#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "PortablePixMap_Plain.h"
#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"
#include "ColorData.h"

//this class is more like an ImageManager, I'm keeping the name Image to coincide with the given example
class Image
{
private:
    //Tools::Vector2I m_size = {};

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

    void release();
    bool isEmpty() const;

    const ColorData &data() const;
    const tools::Vector2I &size() const;
    int globalMaxValue() const;

    tools::RgbColor& at(const tools::Vector2I &position);
    tools::RgbColor& at(int x, int y);

    const tools::RgbColor& at(const tools::Vector2I &position) const;
    const tools::RgbColor& at(int x, int y) const;

    tools::RgbColor* row(int y);

    static Image zeros(int width, int height);
    static Image ones(int width, int height);

    friend std::ostream& operator<<(std::ostream& os, const Image& dt);

    Image operator+(const Image &i);
    Image operator-(const Image &i);
    Image operator*(const Image &i);

    friend Image operator+(float scalar, const Image &image);
    friend Image operator+(const Image &image, float scalar);

    friend Image operator-(const Image &image, float scalar);

    friend Image operator*(float scalar, const Image &image);
    friend Image operator*(const Image &image, float scalar);

};



#endif //IMAGE_H
