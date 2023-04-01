#include "Image.h"

#include <fstream>
#include <sstream>
#include <limits>


///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************



Image::Image(int width, int height) : m_colorData{{width, height}}
{
}

Image::Image(const ColorData &colorData) : m_colorData{colorData}
{


}
Image::Image(tools::Vector2I size) : m_colorData{size}
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::load(std::string imagePath)
{
    std::ifstream inputFile(imagePath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    if (not ppm.loadPlain(buffer.str(), m_colorData))
    {
        inputFile.close();
        return false;
    }

    //m_size = m_colorData.size();

    inputFile.close();
    return true;
}

bool Image::save(std::string imagePath)
{
    std::string imageStr;

    if (not ppm.saveToString(imageStr, m_colorData))
        return false;


    std::ofstream outputFile(imagePath);
    outputFile << imageStr;

    outputFile.close();
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::getROI(Image &roiImg, tools::Rectangle roiRect)
{
    ColorData colorData;
    if (not m_colorData.getROI(colorData, roiRect))
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
    m_colorData = ColorData();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::isEmpty() const
{
    return m_colorData.size().x > 0 and m_colorData.size().y > 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::Vector2I &Image::size() const
{
    return m_colorData.size();
}


const ColorData &Image::data() const
{
    return m_colorData;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor &Image::at(const tools::Vector2I &position)
{
    return m_colorData.at(position);
}

tools::RgbColor &Image::at(int x, int y)
{
    return m_colorData.at(x, y);
}

const tools::RgbColor &Image::at(const tools::Vector2I &position) const
{
    return m_colorData.at(position);
}

const tools::RgbColor &Image::at(int x, int y) const
{
    return m_colorData.at(x, y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image Image::zeros(int width, int height)
{
    tools::Vector2I size = {width, height};
    tools::RgbColor defaultColor = {0, 0, 0, 0};
    ColorData colorMatrix(size, defaultColor);
    return Image(colorMatrix);
}

Image Image::ones(int width, int height)
{
    tools::Vector2I size = {width, height};
    tools::RgbColor defaultColor = {1, 1, 1, 1};
    ColorData colorMatrix(size, defaultColor);
    return Image(colorMatrix);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Image &dt)
{
    os << dt.m_colorData;
    return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image Image::operator+(const Image &i)
{

    return Image(this->m_colorData + i.m_colorData);
}

Image Image::operator-(const Image &i)
{
    return Image(this->m_colorData - i.m_colorData);
}

Image Image::operator*(const Image &i)
{
    return Image(this->m_colorData * i.m_colorData);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator+(float scalar, const Image &image)
{
    return Image(scalar + image.m_colorData);
}

Image operator+(const Image &image, float scalar)
{
    return Image( image.m_colorData + scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator-(const Image &image, float scalar)
{
    return Image( image.m_colorData - scalar);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Image operator*(float scalar, const Image &image)
{
    return Image(scalar * image.m_colorData);
}

Image operator*(const Image &image, float scalar)
{
    return Image( image.m_colorData * scalar);
}

tools::RgbColor *Image::row(int y)
{
    return m_colorData.row(y);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

