#include "ColorMatrix.h"



/////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

/////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

ColorMatrix::ColorMatrix(const tools::Vector2U &size, unsigned int maxValue)
                        : m_size{size}, m_globalMaxValue{maxValue}
{
    m_matrix = new tools::RgbColor*[m_size.y];
    for (int i = 0; i < m_size.y; ++i)
        m_matrix[i] = new tools::RgbColor[m_size.x];
}

ColorMatrix::ColorMatrix(const tools::Vector2U &size, const tools::RgbColor &defaultValue)
                        : m_size{size}, m_globalMaxValue{defaultValue.getMaxValue()}
{
    m_matrix = new tools::RgbColor*[m_size.y];
    for (int i = 0; i < m_size.y; ++i)
    {
        m_matrix[i] = new tools::RgbColor[m_size.x];

        for (int j = 0; j < m_size.x; ++j)
            m_matrix[i][j] = defaultValue;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix &ColorMatrix::operator=(const ColorMatrix &other)
{
    if (this != &other)
    {
        if (this->m_size != other.m_size) //if the dimension is different we can't copy directly
        {
            //we first need to free the existing memory;
            if (m_matrix != nullptr)
            {
                for (int i = 0; i < m_size.y; ++i)
                    delete[] m_matrix[i];
                delete[] m_matrix;
            }

            //start copying;
            this->m_size = other.m_size;
            this->m_globalMaxValue = other.m_globalMaxValue;

            //allocate new memory and  copy;
            m_matrix = new tools::RgbColor*[m_size.y];
            for (int i = 0; i < m_size.y; ++i)
            {
                m_matrix[i] = new tools::RgbColor[m_size.x];

                for (int j = 0; j < m_size.x; ++j)
                    m_matrix[i][j] = other.m_matrix[i][j];
            }
        }
        else
        {
            this->m_globalMaxValue = other.m_globalMaxValue;

            for (int i = 0; i < m_size.y; ++i)
                for (int j = 0; j < m_size.x; ++j)
                    m_matrix[i][j] = other.m_matrix[i][j];
        }

    }
}


ColorMatrix::ColorMatrix(const ColorMatrix &other)
{
    this->m_size = other.m_size;
    this->m_globalMaxValue = other.m_globalMaxValue;

    //TODO: Change this to a memcopy perhaps
    this->m_matrix = new tools::RgbColor*[m_size.y];
    for (int i = 0; i < m_size.y; ++i)
    {
        this->m_matrix[i] = new tools::RgbColor[m_size.x];

        for (int j = 0; j < m_size.x; ++j)
            this->m_matrix[i][j] = other.m_matrix[i][j];
    }

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ColorMatrix::~ColorMatrix()
{
    if (m_matrix != nullptr)
    {
        for (int i = 0; i < m_size.y; ++i)
            delete[] m_matrix[i];

        delete[] m_matrix;
    }
}


