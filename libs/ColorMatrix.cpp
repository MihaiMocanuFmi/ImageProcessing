#include "ColorMatrix.h"

#include <stdexcept>


/////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

/////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

ColorMatrix::ColorMatrix(const tools::Vector2U &size, unsigned int maxValue)
        : m_size{size}, m_globalMaxValue{maxValue}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];

}

ColorMatrix::ColorMatrix(const tools::Vector2U &size, const tools::RgbColor &defaultValue)
        : m_size{size}, m_globalMaxValue{defaultValue.getMaxValue()}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (unsigned int i = 0; i < m_size.y; ++i)
        for (unsigned int j = 0; j < m_size.x; ++j)
            this->getAt({i, j}) = defaultValue;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix &ColorMatrix::operator=(const ColorMatrix &other)
{
    if (this == &other)
        return *this;

    //TODO: Find why this doesnt work
    tools::Vector2U test =  other.m_size + this->m_size;
    if (this->m_size != other.m_size) //if the dimension is different we can't copy directly
    {
        //we first need to free the existing memory;
        delete[] m_matrix;

        //start copying;
        this->m_size = other.m_size;
        this->m_globalMaxValue = other.m_globalMaxValue;

        //allocate new memory and  copy
        m_matrix = new tools::RgbColor[m_size.y * m_size.x];
        for (unsigned int i = 0; i < m_size.y; ++i)
            for (unsigned int j = 0; j < m_size.x; ++j)
                this->setAt({i, j}, other.getAt({i, j}));


    } else
    {
        this->m_globalMaxValue = other.m_globalMaxValue;

        for (unsigned int i = 0; i < m_size.y; ++i)
            for (unsigned int j = 0; j < m_size.x; ++j)
                this->setAt({i, j}, other.getAt({i, j}));
    }

    return *this;
}


ColorMatrix::ColorMatrix(const ColorMatrix &other)
{
    this->m_size = other.m_size;
    this->m_globalMaxValue = other.m_globalMaxValue;

    //TODO: Change this to a memcopy perhaps
    this->m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (unsigned int i = 0; i < m_size.y; ++i)
        for (unsigned int j = 0; j < m_size.x; ++j)
            this->setAt({i, j}, other.getAt({i, j}));

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix::~ColorMatrix()
{
    delete[] m_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorMatrix::setAt(const tools::Vector2U &position, const tools::RgbColor &color)
{
    if (m_size.x > position.x and m_size.y > position.y)
        m_matrix[m_size.y * position.y + position.x] = color;
}

tools::RgbColor &ColorMatrix::getAt(const tools::Vector2U &position)
{
    return m_matrix[m_size.y * position.y + position.x];
}

const tools::RgbColor &ColorMatrix::getAt(const tools::Vector2U &position) const
{
    return m_matrix[m_size.y * position.y + position.x];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix ColorMatrix::operator+(const ColorMatrix &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    unsigned int maxValue = this->m_globalMaxValue + other.m_globalMaxValue;
    ColorMatrix newMatrix(m_size, maxValue);
    for (unsigned int y = 0; y < this->m_size.y; ++y)
        for (unsigned int x = 0; x < this->m_size.x; ++x)
        {
            tools::RgbColor newValue = this->getAt({x,y}) + other.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

ColorMatrix ColorMatrix::operator-(const ColorMatrix &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    unsigned int maxValue = (this->m_globalMaxValue > other.m_globalMaxValue)? this->m_globalMaxValue : other.m_globalMaxValue;
    ColorMatrix newMatrix(m_size, maxValue);
    for (unsigned int y = 0; y < this->m_size.y; ++y)
        for (unsigned int x = 0; x < this->m_size.x; ++x)
        {
            tools::RgbColor newValue = this->getAt({x,y}) - other.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

ColorMatrix ColorMatrix::operator*(const ColorMatrix &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    unsigned int maxValue = this->m_globalMaxValue * other.m_globalMaxValue;
    ColorMatrix newMatrix(m_size, maxValue);
    for (unsigned int y = 0; y < this->m_size.y; ++y)
        for (unsigned int x = 0; x < this->m_size.x; ++x)
        {
            tools::RgbColor newValue = this->getAt({x,y}) + other.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix operator+(float scalar, const ColorMatrix &colorMatrix)
{
    unsigned int maxValue = scalar + (float)colorMatrix.m_globalMaxValue;
    ColorMatrix newMatrix(colorMatrix.m_size, maxValue);
    for (unsigned int y = 0; y < colorMatrix.m_size.y; ++y)
        for (unsigned int x = 0; x < colorMatrix.m_size.x; ++x)
        {
            tools::RgbColor newValue = scalar + colorMatrix.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

ColorMatrix operator+(const ColorMatrix &colorMatrix, float scalar)
{
    return scalar + colorMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix operator-(float scalar, const ColorMatrix &colorMatrix)
{
    unsigned int maxValue = colorMatrix.m_globalMaxValue;
    ColorMatrix newMatrix(colorMatrix.m_size, maxValue);
    for (unsigned int y = 0; y < colorMatrix.m_size.y; ++y)
        for (unsigned int x = 0; x < colorMatrix.m_size.x; ++x)
        {
            tools::RgbColor newValue = scalar - colorMatrix.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

ColorMatrix operator-(const ColorMatrix &colorMatrix, float scalar)
{
    return -scalar + colorMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix operator*(float scalar, const ColorMatrix &colorMatrix)
{
    unsigned int maxValue = scalar * (float)colorMatrix.m_globalMaxValue;
    ColorMatrix newMatrix(colorMatrix.m_size, maxValue);
    for (unsigned int y = 0; y < colorMatrix.m_size.y; ++y)
        for (unsigned int x = 0; x < colorMatrix.m_size.x; ++x)
        {
            tools::RgbColor newValue = scalar * colorMatrix.getAt({x,y});
            newValue.setMaxValue(maxValue);
            newMatrix.setAt({x,y}, newValue);
        }

    return newMatrix;
}

ColorMatrix operator*(const ColorMatrix &colorMatrix, float scalar)
{
    return scalar * colorMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ColorMatrix::resize(const tools::Vector2U &newSize)
{
    if(m_size.x * m_size.y < newSize.x * newSize.y)
    {
        tools::RgbColor *newMatrix = new tools::RgbColor[m_size.y * m_size.x];
        for (int i = 0; i < m_size.x * m_size.y; ++i)
            newMatrix[i] = m_matrix[i];

        delete[] m_matrix;
        m_matrix = newMatrix;
    }

    m_size = newSize;
}

void ColorMatrix::resize(const tools::Vector2U &newSize, const tools::RgbColor &defaultValue)
{
    delete[] m_matrix;
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (int i = 0; i < m_size.x * m_size.y; ++i)
        m_matrix[i] = defaultValue;

    m_size = newSize;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

