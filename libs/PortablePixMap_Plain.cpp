#include "PortablePixMap_Plain.h"

#include <cstring>
#include <array>



///*********************************************************************************************************************
///*****************************************PRIVATE*********************************************************************
///*********************************************************************************************************************



void PortablePixMap_Plain::m_removeComments(std::string &rPlainFile)
{
    int commentStart = rPlainFile.find('#');

    while(commentStart != std::string::npos)
    {
        int commentEnd = rPlainFile.find('\n', commentStart);

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

bool PortablePixMap_Plain::m_findMagicNumber(std::string &rPlainFile, std::string &outMagicNumber)
{
    int positionOfP = rPlainFile.find("P");

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
    if (outMagicNumber != MAGIC_NUMBER and outMagicNumber != PGM_MAGIC_NUMBER and outMagicNumber != PBM_MAGIC_NUMBER)
        return false;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findFirstNumber(const std::string &str, unsigned int startingPos, int &outStartPos,
                                             int &outEndPos)
{
    const char numbers[] = "0123456789";
    int posDigit = str.find_first_of(numbers, startingPos);

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

bool PortablePixMap_Plain::m_findSize(std::string &rPlainFile, tools::Vector2U &outSize)
{
    int posOfMagicNumber = rPlainFile.find(m_magicNumber);

    //if magic number is the last element
    if(posOfMagicNumber + 2 == rPlainFile.size())
        return false;

    int startingPos, endingPos;
    //if it couldn't find a number
    if (not m_findFirstNumber(rPlainFile, posOfMagicNumber + 2, startingPos, endingPos))
        return false;

    std::string firstSizeComponentStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    unsigned int firstSizeComponent = std::stoi(firstSizeComponentStr);

    //if the found number is the last one
    if (endingPos + 1 >= rPlainFile.length())
        return false;

    //if it couldn't find a number
    if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
        return false;

    std::string secondSizeComponentStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    unsigned int secondSizeComponent = std::stoi(secondSizeComponentStr);

    //if the found number is the last one (taking into account that the image's size is non-zero)
    if (firstSizeComponent > 0 and secondSizeComponent > 0 and endingPos + 2 >= rPlainFile.length())
        return false;


    outSize = {firstSizeComponent, secondSizeComponent};
    return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findMaxValue(std::string &rPlainFile, unsigned int &outMaxValue)
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


    int startingPos, endingPos;
    //if there wasn't any number
    if (not m_findFirstNumber(rPlainFile, posNextWhiteSpace, startingPos, endingPos))
        return false;

    std::string maxValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
    unsigned int maxValue = std::stoi(maxValueStr);

    outMaxValue = maxValue;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findColorsP1Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posNextWhiteSpace = posSecondSizeComp + std::to_string(m_size.y).length();


    int startingPos = -1;
    int endingPos = posNextWhiteSpace;

    outColorMatrix.resize(m_size.y);
    for (int y = 0; y < m_size.y; ++y)
    {
        outColorMatrix[y].resize(m_size.x);
        for (int x = 0; x < m_size.x; ++x)
        {
            //if there wasn't any number
            if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                return false;

            std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
            unsigned int colorValue = std::stoi(colorValueStr);

            outColorMatrix[y][x] = {m_maxValue, {colorValue, colorValue, colorValue}};
        }
    }

    return true;
}

bool PortablePixMap_Plain::m_findColorsP2Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posMaxValue =  rPlainFile.find(std::to_string(m_maxValue), posSecondSizeComp + 1);
    int posNextWhiteSpace = posMaxValue + std::to_string(m_maxValue).length();

    int startingPos = -1;
    int endingPos = posNextWhiteSpace;

    outColorMatrix.resize(m_size.y);
    for (int y = 0; y < m_size.y; ++y)
    {
        outColorMatrix[y].resize(m_size.x);
        for (int x = 0; x < m_size.x; ++x)
        {
            //if there wasn't any number
            if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                return false;

            std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
            unsigned int colorValue = std::stoi(colorValueStr);

            outColorMatrix[y][x] = {m_maxValue, {colorValue, colorValue, colorValue}};
        }
    }

    return true;
}

bool PortablePixMap_Plain::m_findColorsP3Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix)
{
    //TODO: Maybe add checking for these searches, even though if the rest of the methods were called, these calls will
    // also be valid
    int magicNumber = rPlainFile.find(m_magicNumber);
    int posFirstSizeComp = rPlainFile.find(std::to_string(m_size.x), magicNumber + 3);
    int posSecondSizeComp = rPlainFile.find(std::to_string(m_size.y), posFirstSizeComp + 2);
    int posMaxValue =  rPlainFile.find(std::to_string(m_maxValue), posSecondSizeComp + 1);
    int posNextWhiteSpace = posMaxValue + std::to_string(m_maxValue).length();

    int startingPos = -1;
    int endingPos = posNextWhiteSpace;

    outColorMatrix.resize(m_size.y);
    for (int y = 0; y < m_size.y; ++y)
    {
        outColorMatrix[y].resize(m_size.x);
        for (int x = 0; x < m_size.x; ++x)
        {
            std::array<unsigned int, 3> colors;
            for (int i = 0; i < 3; ++i)
            {
                //if there wasn't any number
                if (not m_findFirstNumber(rPlainFile, endingPos + 1, startingPos, endingPos))
                    return false;

                std::string colorValueStr = rPlainFile.substr(startingPos, endingPos - startingPos + 1);
                unsigned int colorValue = std::stoi(colorValueStr);

                colors[i] = colorValue;
            }


            outColorMatrix[y][x] = {m_maxValue, {colors[0] , colors[1] , colors[2] }};
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::m_findColors(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix)
{
    if (m_magicNumber == PBM_MAGIC_NUMBER)
        return m_findColorsP1Format(rPlainFile, outColorMatrix);
    else if (m_magicNumber == PGM_MAGIC_NUMBER)
        return m_findColorsP2Format(rPlainFile, outColorMatrix);
    else if (m_magicNumber == MAGIC_NUMBER)
        return m_findColorsP3Format(rPlainFile, outColorMatrix);
    else
        return false;
}



///*********************************************************************************************************************
///*****************************************PUBLIC**********************************************************************
///*********************************************************************************************************************



PortablePixMap_Plain::PortablePixMap_Plain() : m_size{0,0}, m_maxValue{0}
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::loadPlain(std::string plainFile)
{
    m_preProcessPPM(plainFile);

    std::string magicNumber;
    if (not m_findMagicNumber(plainFile, magicNumber))
        return false;

    m_magicNumber = magicNumber;



    tools::Vector2U size;
    if (not m_findSize(plainFile, size))
        return false;

    m_size = size;


    unsigned int maxValue;
    if (not m_findMaxValue(plainFile, maxValue))
        return false;

    m_maxValue = maxValue;

    tools::ColorMatrix colorMatrix;
    if (not m_findColors(plainFile, colorMatrix))
        return false;
    m_colorDataMatrix = colorMatrix;

    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PortablePixMap_Plain::saveToString(std::string &outPlainFile)
{
    try
    {
        outPlainFile = "";
        outPlainFile += m_magicNumber + "\t#Magic Number\n";
        outPlainFile += std::to_string(m_size.x) + " " + std::to_string(m_size.y) + "\t#Size width and height\n";
        outPlainFile += std::to_string(m_maxValue) + "\t#Max color value\n";

        for (int y = 0; y < m_size.y; ++y)
        {
            outPlainFile += "\n";
            for (int x = 0; x < m_size.x; ++x)
            {
                outPlainFile += std::to_string(m_colorDataMatrix[y][x].getColorR());
                outPlainFile += "\t";
                outPlainFile += std::to_string(m_colorDataMatrix[y][x].getColorG());
                outPlainFile += "\t";
                outPlainFile += std::to_string(m_colorDataMatrix[y][x].getColorB());

                outPlainFile += "\t\t\t";
            }

        }

        return true;
    }
    catch (...){
        return false;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const std::string &PortablePixMap_Plain::getMagicNumber() const
{
    return m_magicNumber;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::Vector2U &PortablePixMap_Plain::getSize() const
{
    return m_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int PortablePixMap_Plain::getMaxValue() const
{
    return m_maxValue;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::ColorMatrix &PortablePixMap_Plain::getColorMatrix() const
{
    return m_colorDataMatrix;
}




