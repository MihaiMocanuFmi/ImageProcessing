#include "Image.h"

#include <fstream>
#include <sstream>


///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************



Image::Image(int width, int height) : m_ImageData{{width, height}}
{
}

Image::Image(const ImageData &imageData) : m_ImageData{imageData}
{


}
Image::Image(tools::Vector2I size) : m_ImageData{size}
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::load(const std::string &imagePath)
{
    std::ifstream inputFile(imagePath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    if (not ppm.loadPlain(buffer.str(), m_ImageData))
    {
        inputFile.close();
        return false;
    }

    //m_size = m_ImageData.size();

    inputFile.close();
    return true;
}

bool Image::save(const std::string &imagePath)
{
    std::string imageStr;

    if (not ppm.saveToString(imageStr, m_ImageData))
        return false;


    std::ofstream outputFile(imagePath);
    outputFile << imageStr;

    outputFile.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::getROI(Image &roiImg, tools::Rectangle roiRect)
{
    ImageData colorData;
    if (not m_ImageData.getROI(colorData, roiRect))
        return false;

   roiImg = Image(colorData);
    return true;
}

bool Image::getROI(Image &roiImg, int x, int y, int width, int height)
{
    return getROI(roiImg, tools::Rectangle(x, y, width, height));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Image::release()
{
    ppm = PortablePixMap_Plain();
    m_ImageData = ImageData();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::isEmpty() const
{
    return m_ImageData.size().x <= 0 or m_ImageData.size().y <= 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::Vector2I &Image::size() const
{
    return m_ImageData.size();
}


const ImageData &Image::data() const
{
    return m_ImageData;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor& Image::at(const tools::Vector2I &position)
{
    return m_ImageData.at(position);
}

tools::RgbColor& Image::at(int x, int y)
{
    return m_ImageData.at(x, y);
}

const tools::RgbColor& Image::at(const tools::Vector2I &position) const
{
    return m_ImageData.at(position);
}

const tools::RgbColor& Image::at(int x, int y) const
{
    return m_ImageData.at(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image Image::zeros(int width, int height)
{
    tools::Vector2I size = {width, height};
    tools::RgbColor defaultColor = {0, 0, 0};
    ImageData colorMatrix(size, defaultColor);
    return Image(colorMatrix);
}

Image Image::ones(int width, int height)
{
    tools::Vector2I size = {width, height};
    tools::RgbColor defaultColor = {1, 1, 1};
    ImageData colorMatrix(size, defaultColor);
    return Image(colorMatrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Image &dt)
{
    os << dt.m_ImageData;
    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image Image::operator+(const Image &i)
{

    return Image(this->m_ImageData + i.m_ImageData);
}

Image Image::operator-(const Image &i)
{
    return Image(this->m_ImageData - i.m_ImageData);
}

Image Image::operator*(const Image &i)
{
    return Image(this->m_ImageData * i.m_ImageData);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator+(float scalar, const Image &image)
{
    return Image(scalar + image.m_ImageData);
}

Image operator+(const Image &image, float scalar)
{
    return Image(image.m_ImageData + scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator-(const Image &image, float scalar)
{
    return Image(image.m_ImageData - scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator*(float scalar, const Image &image)
{
    return Image(scalar * image.m_ImageData);
}

Image operator*(const Image &image, float scalar)
{
    return Image(image.m_ImageData * scalar);
}

tools::RgbColor *Image::row(int y)
{
    return m_ImageData.row(y);
}

bool Image::operator==(const Image &other) const
{
    return this->m_ImageData == other.m_ImageData;
}

bool Image::operator!=(const Image &other) const
{
    return not (*this == other);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

