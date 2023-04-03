#include "PortablePixMap_Plain.h"

#include <cstring>
#include <array>



///*********************************************************************************************************************
///*****************************************PRIVATE*********************************************************************
///*********************************************************************************************************************



void PortablePixMap_Plain::m_removeComments(std::string &rPlainFile)
{
    std::size_t commentStart = rPlainFile.find('#');

    while(commentStart != std::string::npos)
    {
        std::size_t commentEnd = rPlainFile.find('\n', commentStart);

        //if the found comment is actually the last part of the string
        if(commentEnd == std::string::npos)
            commentEnd = rPlainFile.length();

        rPlainFile.erase(commentStart, commentEnd - commentStart);

        commentStart = rPlainFile.find('#', commentStart);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PortablePixMap_Plain::m_preProcessPPM(std::string &rPlainFile)
{
    m_removeComments(rPlainFile);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findMagicNumber(const std::string &rPlainFile, std::string &outMagicNumber)
{
    std::size_t positionOfP = rPlainFile.find('P');

    //if there's no P
    if (positionOfP == std::string::npos)
        return false;

    //if P is the last element it's invalid. We should have P + _digit_ + whitespace
    if(positionOfP + 3 >= rPlainFile.size())
        return false;

    //if there's no digit after P
    char digitAfter = rPlainFile[positionOfP + 1];
    if (not isdigit(digitAfter))
        return false;

    char whiteSpace = rPlainFile[positionOfP + 2];
    //if there's no whitespace (newline) just after the digit
    if (not std::isspace(whiteSpace))
        return false;

    outMagicNumber = std::string(1, rPlainFile[positionOfP]) + std::string(1, digitAfter);

    //if the magic number doesn't represent a format understood by PPM
    if (outMagicNumber != PPM_MAGIC_NUMBER and outMagicNumber != PGM_MAGIC_NUMBER and outMagicNumber != PBM_MAGIC_NUMBER)
        return false;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findFirstNumber(const std::string &str, std::size_t startingPos, std::size_t &outStartPos,
                                             std::size_t &outEndPos)
{
    const char numbers[] = "0123456789";
    std::size_t posDigit = str.find_first_of(numbers, startingPos);

    //if there's no digit in str
    if (posDigit == std::string::npos)
        return false;

    outStartPos = posDigit;
    while(posDigit < str.length() and isdigit(str[posDigit]))
        posDigit++;

    outEndPos = posDigit - 1;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findSize(const std::string &rPlainFile, tools::Vector2I &outSize)
{
    std::size_t posOfMagicNumber = rPlainFile.find(m_magicNumber);

    //if magic number is the last element
    if(posOfMagicNumber + 2 == rPlainFile.size())
        return false;

    std::size_t startingPos, endingPos;
    //if it couldn't find a number
    if (not m_findFirstNumber(rPlainFile, posOfMagicNumber + 2, startingPos, endingPos))
        return false;

    std::string firstSizeComponentStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    int firstSizeComponent = std::stoi(firstSizeComponentStr);

    //if the found number is the last one
    if (endingPos + 1 >= rPlainFile.length())
        return false;

    //if it couldn't find a number
    if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
        return false;

    std::string secondSizeComponentStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    int secondSizeComponent = std::stoi(secondSizeComponentStr);

    //if the found number is the last one (taking into account that the image's size is non-zero)
    if (firstSizeComponent > 0 and secondSizeComponent > 0 and endingPos + 2 >= rPlainFile.length())
        return false;


    outSize = {firstSizeComponent, secondSizeComponent};
    return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findMaxValue(const std::string &rPlainFile, int &outMaxValue)
{
    if (m_magicNumber == PBM_MAGIC_NUMBER)
    {
        outMaxValue = 1;
        return true;
    }

    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);

    int posNextWhiteSpace = posSecondSizeComp + std::to_string(m_size.y).length();


    std::size_t startingPos, endingPos;
    //if there wasn't any number
    if (not m_findFirstNumber(rPlainFile, posNextWhiteSpace, startingPos, endingPos))
        return false;

    std::string maxValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    int maxValue = std::stoi(maxValueStr);

    outMaxValue = maxValue;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findColorsP1Format(const std::string &rPlainFile, ColorData &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posNextWhiteSpace = posSecondSizeComp + std::to_string(m_size.y).length();


    std::size_t startingPos;
    std::size_t endingPos = posNextWhiteSpace;

    outColorMatrix = ColorData(m_size);
    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            //if there wasn't any number
            if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                return false;

            std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
            int colorValue = std::stoi(colorValueStr);
            //scaling it to[0, tools::RgbColor::MAX_VALUE]
            colorValue = ((float)colorValue / m_maxValue) * tools::RgbColor::MAX_VALUE;

            outColorMatrix.at(x,y) = tools::RgbColor(colorValue, colorValue, colorValue);
        }
    }

    m_magicNumber = PPM_MAGIC_NUMBER;
    return true;
}

bool PortablePixMap_Plain::m_findColorsP2Format(const std::string &rPlainFile, ColorData &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posMaxValue =  rPlainFile.find(std::to_string(m_maxValue), posSecondSizeComp + 1);
    int posNextWhiteSpace = posMaxValue + std::to_string(m_maxValue).length();

    std::size_t startingPos;
    std::size_t endingPos = posNextWhiteSpace;

    outColorMatrix = ColorData(m_size);
    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            //if there wasn't any number
            if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                return false;

            std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
            int colorValue = std::stoi(colorValueStr);
            //scaling it to [0, tools::RgbColor::MAX_VALUE]
            colorValue = ((float)colorValue / m_maxValue) * tools::RgbColor::MAX_VALUE;

            outColorMatrix.at(x,y) = tools::RgbColor(colorValue, colorValue, colorValue);

        }
    }

    m_magicNumber = PPM_MAGIC_NUMBER;
    return true;
}

bool PortablePixMap_Plain::m_findColorsP3Format(const std::string &rPlainFile, ColorData &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posMaxValue =  rPlainFile.find(std::to_string(m_maxValue), posSecondSizeComp + 1);
    int posNextWhiteSpace = posMaxValue + std::to_string(m_maxValue).length();

    std::size_t startingPos;
    std::size_t endingPos = posNextWhiteSpace;


    outColorMatrix = ColorData(m_size);
    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            std::array<int, 3> colors;
            for (int i = 0; i < 3; ++i)
            {
                //if there wasn't any number
                if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                    return false;

                std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
                int colorValue = std::stoi(colorValueStr);
                //scaling it to[0, tools::RgbColor::MAX_VALUE]
                colorValue = ((float)colorValue / m_maxValue) * tools::RgbColor::MAX_VALUE;

                colors[i] = colorValue;
            }


            outColorMatrix.at(x, y) = tools::RgbColor(colors[0] , colors[1] , colors[2]);
        }
    }


    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findColors(const std::string &rPlainFile, ColorData &outColorMatrix)
{
    if (m_magicNumber == PBM_MAGIC_NUMBER)
        return m_findColorsP1Format(rPlainFile, outColorMatrix);
    else if (m_magicNumber == PGM_MAGIC_NUMBER)
        return m_findColorsP2Format(rPlainFile, outColorMatrix);
    else if (m_magicNumber == PPM_MAGIC_NUMBER)
        return m_findColorsP3Format(rPlainFile, outColorMatrix);
    else
        return false;
}


void PortablePixMap_Plain::cacheDataParameters(const ColorData &data)
{
    //We assume it's a PPM, (it has color after all)
    m_magicNumber = PPM_MAGIC_NUMBER;
    m_size = data.size();
    m_maxValue = data.MAX_VALUE;
}

/*
 * TODO: Cache the position in the file of all important values during loading (Magic Number, Size, Max Value, Color start)
 */


///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::loadPlain(std::string plainFile, ColorData &outData)
{
    m_preProcessPPM(plainFile);

    std::string magicNumber;
    if (not m_findMagicNumber(plainFile, magicNumber))
        return false;

    m_magicNumber = magicNumber;



    tools::Vector2I size;
    if (not m_findSize(plainFile, size))
        return false;

    m_size = size;


    int maxValue;
    if (not m_findMaxValue(plainFile, maxValue))
        return false;

    m_maxValue = maxValue;

    ColorData colorMatrix;
    if (not m_findColors(plainFile, colorMatrix))
        return false;

    outData = colorMatrix;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::saveToString(std::string &outPlainFile, const ColorData &data)
{
    cacheDataParameters(data);

    int sizeMaxValue = std::to_string(m_maxValue).length();
    constexpr int MAX_LINE_LENGTH = 70;


    try
    {
        outPlainFile = "";
        outPlainFile += m_magicNumber + "\t#Magic Number\n";
        outPlainFile += std::to_string(m_size.x) + " " + std::to_string(m_size.y) + "\t#Size width and height\n";
        outPlainFile += std::to_string(m_maxValue) + "\t#Max color value\n";

        for (int y = 0; y < m_size.y; ++y)
        {
            outPlainFile += "\n";

            int lineLength = 0;
            for (int x = 0; x < m_size.x; ++x)
            {

                //PPM introduces a line length limit of 70 characters
                const int currentLineLength = sizeMaxValue * 3 + 3;
                if (lineLength + currentLineLength >= MAX_LINE_LENGTH)
                {
                    outPlainFile += "\n";
                    lineLength = 0;
                }

                outPlainFile += std::to_string(data.at({x, y}).getColorR());
                outPlainFile += " ";
                outPlainFile += std::to_string(data.at({x, y}).getColorG());
                outPlainFile += " ";
                outPlainFile += std::to_string(data.at({x, y}).getColorB());

                outPlainFile += " ";

                lineLength += currentLineLength;
            }

        }

        return true;
    }
    catch (...){
        return false;
    }
}





