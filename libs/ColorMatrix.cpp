#include "ColorMatrix.h"



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
    //if (this->m_size != other.m_size) //if the dimension is different we can't copy directly
    if(this->m_size.x * this->m_size.y != other.m_size.x * other.m_size.y)
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


