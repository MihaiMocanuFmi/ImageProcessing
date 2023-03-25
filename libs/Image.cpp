#include "Image.h"

#include <fstream>
#include <sstream>


///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************



Image::Image(int width, int height) : m_colorData{{width, height}, 0}
{
}

Image::Image(const ColorData &colorData) : m_colorData{colorData}
{


}
Image::Image(tools::Vector2I size) : m_colorData{size, 0}
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


void Image::release()
{
    m_colorData = ColorData();
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

Image operator-(float scalar, const Image &image)
{
    return Image(scalar - image.m_colorData);
}

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

