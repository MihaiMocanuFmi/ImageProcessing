#include "Image.h"

#include <fstream>
#include <sstream>


///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************



Image::Image(unsigned int width, unsigned int height) : m_size({width, height})
{
}

Image::Image(tools::Vector2U size) : m_size(size)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Image::load(std::string imagePath)
{
    std::ifstream inputFile("imagePath");
    std::stringstream buffer;
    buffer << inputFile.rdbuf();

    if (not ppm.loadPlain(buffer.str()))
        return false;

    inputFile.close();
    return true;
}
bool Image::save(std::string imagePath)
{
    std::string imageStr;

    if (not ppm.saveToString(imageStr))
        return false;

    std::ofstream outputFile("imagePath");
    outputFile << imageStr;

    outputFile.close();
    return true;
}