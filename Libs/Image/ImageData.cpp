#include "ImageData.h"

#include <stdexcept>
#include <iomanip>

/////////////////////////PRIVATE///////////////////////////////////////////////////////////////////////////////////

/////////////////////////PUBLIC////////////////////////////////////////////////////////////////////////////////////

ImageData::ImageData(const tools::Vector2I &size) : m_size{size}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
}



ImageData::ImageData(const tools::Vector2I &size, const tools::RgbColor &defaultValue) : m_size{size}
{
    m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (int y = 0; y < m_size.y; ++y)
        for (int x = 0; x < m_size.x; ++x)
            this->at(x, y) = defaultValue;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageData &ImageData::operator=(const ImageData &other)
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


ImageData::ImageData(const ImageData &other)
{
    this->m_size = other.m_size;

    //TODO: Change this to a memcopy perhaps
    this->m_matrix = new tools::RgbColor[m_size.y * m_size.x];
    for (int y = 0; y < m_size.y; ++y)
        for (int x = 0; x < m_size.x; ++x)
            this->at(x, y) = other.at(x, y);

}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageData::~ImageData()
{
    delete[] m_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ImageData::resize(const tools::Vector2I &newSize)
{
    if(m_size.x * m_size.y < newSize.x * newSize.y)
    {
        tools::RgbColor *newMatrix = new tools::RgbColor[newSize.y * newSize.x];
        for (int y = 0; y < m_size.y; ++y)
            for (int x = 0; x < m_size.x; ++x)
                newMatrix[newSize.x * y + x] = m_matrix[m_size.x * y + x];

        delete[] m_matrix;
        m_size = newSize;
        m_matrix = newMatrix;
    }
}

void ImageData::resize(const tools::Vector2I &newSize, const tools::RgbColor &defaultValue)
{
    delete[] m_matrix;
    m_matrix = new tools::RgbColor[newSize.y * newSize.x];
    for (int i = 0; i < newSize.x * newSize.y; ++i)
        m_matrix[i] = defaultValue;

    m_size = newSize;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool ImageData::getROI(ImageData &roiImageData, tools::Rectangle roiRect)
{
    if (not tools::Rectangle::isContainedInside(roiRect,tools::Rectangle({0, 0},m_size)))
        return false;

    roiImageData = ImageData(roiRect.size);
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
            *(roiImageData.m_matrix + currentElement) = *(this->m_matrix + m_size.x * yInParent + xInParent);

        }
    }
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor& ImageData::at(const tools::Vector2I &position)
{
    return m_matrix[m_size.x * position.y + position.x];
}

tools::RgbColor& ImageData::at(int x, int y)
{
    return at({x, y});
}

const tools::RgbColor& ImageData::at(const tools::Vector2I &position) const
{
    return m_matrix[m_size.x * position.y + position.x];
}

const tools::RgbColor& ImageData::at(int x, int y) const
{
    return at({x, y});
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tools::RgbColor *ImageData::row(int y)
{
    return &(this->at(0,y));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const tools::Vector2I &ImageData::size() const
{
    return m_size;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const ImageData &dt)
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

bool ImageData::operator==(const ImageData &other) const
{
    if (this->m_size != other.m_size)
        return false;

    for (int y = 0; y < other.m_size.y; ++y)
        for (int x = 0; x < other.m_size.x; ++x)
            if (this->at(x, y) != other.at(x, y))
                return false;
    return true;
}

bool ImageData::operator!=(const ImageData &other) const
{
    return not (*this == other);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageData ImageData::operator+(const ImageData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ImageData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x,y) = this->at(x, y) + other.at(x, y);

    return newMatrix;
}

ImageData ImageData::operator-(const ImageData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ImageData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x,y) = this->at(x, y) - other.at(x, y);

    return newMatrix;
}

ImageData ImageData::operator*(const ImageData &other)
{
    if (this->m_size != other.m_size)
        throw std::runtime_error("The matrices aren't of same size");

    ImageData newMatrix(m_size);
    for (int y = 0; y < this->m_size.y; ++y)
        for (int x = 0; x < this->m_size.x; ++x)
            newMatrix.at(x, y) = this->at(x, y) * other.at(x, y);

    return newMatrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageData operator+(float scalar, const ImageData &imageData)
{
    ImageData newMatrix(imageData.m_size);
    for (int y = 0; y < imageData.m_size.y; ++y)
        for (int x = 0; x < imageData.m_size.x; ++x)
            newMatrix.at(x,y) = scalar + imageData.at(x, y);

    return newMatrix;
}

ImageData operator+(const ImageData &imageData, float scalar)
{
    return scalar + imageData;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ImageData operator-(const ImageData &imageData, float scalar)
{
    ImageData newMatrix(imageData.m_size);
    for (int y = 0; y < imageData.m_size.y; ++y)
        for (int x = 0; x < imageData.m_size.x; ++x)
            newMatrix.at(x,y) = imageData.at(x, y) - scalar;

    return newMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ImageData operator*(float scalar, const ImageData &imageData)
{
    ImageData newMatrix(imageData.m_size);
    for (int y = 0; y < imageData.m_size.y; ++y)
        for (int x = 0; x < imageData.m_size.x; ++x)
            newMatrix.at(x,y) = scalar * imageData.at(x, y);

    return newMatrix;
}

ImageData operator*(const ImageData &imageData, float scalar)
{
    return scalar * imageData;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

