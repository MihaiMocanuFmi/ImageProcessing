#include "ColorData.h"

#include <stdexcept>
#include <iomanip>
#include <limits>

/*
tools::RgbColor ColorData::m_rescaleColorValue(const tools::RgbColor &color, int wantedMaxValue)
{
    int actualMaxValue = color.getMaxValue();
    tools::RgbColor scaledColor(wantedMaxValue);
    float R =  ((float)color.getColorR() / actualMaxValue) * wantedMaxValue;
    float G =  ((float)color.getColorG() / actualMaxValue) * wantedMaxValue;
    float B =  ((float)color.getColorB() / actualMaxValue) * wantedMaxValue;
    scaledColor.setColor(R, G, B);
    scaledColor.setMaxValue(wantedMaxValue);
    return scaledColor;
}
*/

/////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

/////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

ColorData::ColorData(const tools::Vector2I &size) : m_size{size}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
}



ColorData::ColorData(const tools::Vector2I &size, const tools::RgbColor &defaultValue) :  m_size{size}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (int y = 0; y < m_size.y; ++y)
        for (int x = 0; x < m_size.x; ++x)
            this->at(x, y) = defaultValue;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorData &ColorData::operator=(const ColorData &other)
{
    if (this == &other)
        return *this;

    //if the dimension is different we can't copy directly. However if the dimension is different,
    //but it has the same area, we can skip directly to copying
    if (this->m_size.x * this->m_size.y != other.m_size.x * other.m_size.y)
    {
        //we first need to free the existing memory;
        delete[] m_matrix;

        //start copying;
        this->m_size = other.m_size;

        //allocate new memory
        m_matrix = new tools::RgbColor[m_size.y * m_size.x];

    }
    this->m_size = other.m_size;
    for (int y = 0; y < m_size.y; ++y)
        for (int x = 0; x < m_size.x; ++x)
            this->at(x, y) = other.at(x, y);

    return *this;
}


ColorData::ColorData(const ColorData &other)
{
    this->m_size = other.m_size;

    //TODO: Change this to a memcopy perhaps
    this->m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (int y = 0; y < m_size.y; ++y)
        for (int x = 0; x < m_size.x; ++x)
            this->at(x, y) = other.at(x, y);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorData::~ColorData()
{
    delete[] m_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorData::resize(const tools::Vector2I &newSize)
{
    if(m_size.x * m_size.y < newSize.x * newSize.y)
    {
        tools::RgbColor *newMatrix = new tools::RgbColor[newSize.y * newSize.x];
        for (int i = 0; i < m_size.x * m_size.y; ++i)
            newMatrix[i] = m_matrix[i];

        delete[] m_matrix;
        m_matrix = newMatrix;
    }

    m_size = newSize;
}

void ColorData::resize(const tools::Vector2I &newSize, const tools::RgbColor &defaultValue)
{
    delete[] m_matrix;
    m_matrix = new tools::RgbColor[newSize.y * newSize.x];
    for (int i = 0; i < newSize.x * newSize.y; ++i)
        m_matrix[i] = defaultValue;

    m_size = newSize;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool ColorData::getROI(ColorData &roiColorData, tools::Rectangle roiRect)
{
    if (not tools::Rectangle::isContainedInside(roiRect,tools::Rectangle({0, 0},
                                                                                    m_size)))
        return false;

    roiColorData = ColorData(roiRect.size);
    for (int y = 0; y < roiRect.size.y; ++y)
    {
        for (int x = 0; x < roiRect.size.x; ++x)
        {
            /*
             * >> You should use only pointer arithmetic for this (so don’t use the indexing operator []);
             * (I dont understand why yet, but here it is)
             */
            int currentElement = y * roiRect.size.x + x;
            int xInParent = roiRect.upperLeftCorner.x + x;
            int yInParent = roiRect.upperLeftCorner.y + y;
            *(roiColorData.m_matrix + currentElement) = *(this->m_matrix + m_size.x * yInParent  + xInParent);

        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor& ColorData::at(const tools::Vector2I &position)
{
    return m_matrix[m_size.x * position.y + position.x];
}

tools::RgbColor& ColorData::at(int x, int y)
{
    return at({x, y});
}

const tools::RgbColor& ColorData::at(const tools::Vector2I &position) const
{
    return m_matrix[m_size.x * position.y + position.x];
}

const tools::RgbColor& ColorData::at(int x, int y) const
{
    return at({x, y});
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor *ColorData::row(int y)
{
    return &(this->at(0,y));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::Vector2I &ColorData::size() const
{
    return m_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const ColorData &dt)
{
    const int emptySize = std::string("(, , )").length();
    const int maxSize = emptySize + 3 * std::to_string(dt.MAX_VALUE).length();
    const int finalGroupSize = maxSize + 3;
    for (int y = 0; y < dt.m_size.y; ++y)
    {
        for (int x = 0; x < dt.m_size.x; ++x)
        {
            int groupSize = emptySize + std::to_string(dt.at(x,y).getColorR()).length();
            groupSize += std::to_string(dt.at(x,y).getColorG()).length();
            groupSize += std::to_string(dt.at(x,y).getColorB()).length();
            os << dt.at(x,y) << std::setw(finalGroupSize - groupSize);
        }
        os << '\n';
    }
    return os;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorData ColorData::operator+(const ColorData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ColorData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x,y) = this->at(x, y) + other.at(x, y);

    return newMatrix;
}

ColorData ColorData::operator-(const ColorData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ColorData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x,y) = this->at(x, y) - other.at(x, y);

    return newMatrix;
}

ColorData ColorData::operator*(const ColorData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ColorData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x, y) = this->at(x, y) * other.at(x, y);

    return newMatrix;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorData operator+(float scalar, const ColorData &colorMatrix)
{
    ColorData newMatrix(colorMatrix.m_size);
    for (int y = 0; y < colorMatrix.m_size.y; ++y)
        for (int x = 0; x < colorMatrix.m_size.x; ++x)
            newMatrix.at(x,y) =  scalar + colorMatrix.at(x, y);

    return newMatrix;
}

ColorData operator+(const ColorData &colorMatrix, float scalar)
{
    return scalar + colorMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ColorData operator-(const ColorData &colorMatrix, float scalar)
{
    ColorData newMatrix(colorMatrix.m_size);
    for (int y = 0; y < colorMatrix.m_size.y; ++y)
        for (int x = 0; x < colorMatrix.m_size.x; ++x)
            newMatrix.at(x,y) = colorMatrix.at(x, y) - scalar;

    return newMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorData operator*(float scalar, const ColorData &colorMatrix)
{
    ColorData newMatrix(colorMatrix.m_size);
    for (int y = 0; y < colorMatrix.m_size.y; ++y)
        for (int x = 0; x < colorMatrix.m_size.x; ++x)
            newMatrix.at(x,y) =  scalar * colorMatrix.at(x, y);

    return newMatrix;
}

ColorData operator*(const ColorData &colorMatrix, float scalar)
{
    return scalar * colorMatrix;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

