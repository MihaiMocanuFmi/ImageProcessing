#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include <ostream>
#include "../Tools/RgbColor.h"
#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"

/// \brief Class representing the data of an Image. It manages a matrix of colors.
/// \note In the past it was named ColorData, the old name might still appear in certain places in the code
class ImageData
{
private:

    /// \brief Size of the ImageData. Remember that the image data models a matrix of colors
    tools::Vector2I m_size = {0, 0};

    /// \brief a m_size.x * m_size.y array which is seen as a matrix when accessed outside the class.
    tools::RgbColor *m_matrix = nullptr;

    //tools::RgbColor  m_rescaleColorValue(const tools::RgbColor &color, int wantedMaxValue);
public:
    /// \brief The maximum value that an RgbColor element can have
    static constexpr int MAX_VALUE = tools::RgbColor::MAX_VALUE;

    /// \brief The default constructor, it initialises all values to their zero or null value
    ImageData() = default;

    /// \brief It creates an ImageData with a specified size. The elements inside are not initialised
    /// \param size The size of the ImageData matrix;
    explicit ImageData(const tools::Vector2I &size);

    /// \brief It creates an ImageData with a specified size. All elements inside have the value given by defaultValue;
    /// \param size The size of the ImageData matrix;
    /// \param defaultValue The default value which all elements inside the ImageData will have
    ImageData(const tools::Vector2I &size, const tools::RgbColor &defaultValue);

    /// \brief Copy constructor
    /// \param other ImageData to be copied
    ImageData(const ImageData &other);

    /// \brief Copy assignment operator
    /// \param other ImageData to be copied
    /// \return Copied ImageData
    ImageData& operator=(const ImageData &other);

    /// \brief Destructor
    ~ImageData();

    /// \brief If the newSize is greater than the old size, then it will increase the size of the data and copy the old
    ///     elements.
    /// \note Remark, this method overload won't be able to decrease the size.
    /// \param newSize The wanted newSize, it should be greater than the old one
    void resize(const tools::Vector2I &newSize);

    /// \brief It will modify the size and change all elements inside to have the value of the given \c default value.
    /// \note Remark, this method overload will be able to decrease the size.
    /// \param newSize The wanted newSize
    /// \param defaultValue The value which all elements inside the ImageData will have
    void resize(const tools::Vector2I &newSize, const tools::RgbColor &defaultValue);

    /// \brief Copies the elements inside the given ROI (Region of Interest)
    /// \param roiImageData Output parameter, it returns the copied elements inside the region.
    /// \param roiRect The bounds of the Region of Interest inside the original ImageData
    /// \note roiRect has to be contained inside the ImageData perimeter in order for the function to succeed
    /// \return True if it was successfully able to copy and false otherwise.
    bool getROI(ImageData &roiImageData, tools::Rectangle roiRect);

    /// \brief (Input-Output) Random access method for elements of the ImageData.
    /// \param position The position of the wanted element.
    /// \note The position has to be inside the ImageData. The function does not make any boundary checks. <br>
    ///         The syntax is ImageData.at({x, y}), so by the usual notations it becomes ImageData.at({j, i}), not
    ///     ImageData.at({i, j}) like usual.
    /// \return A reference to the wanted element.
    tools::RgbColor& at(const tools::Vector2I &position);

    /// \brief (Input-Output) Random access method for elements of the ImageData.
    /// \param x The x-coord of the wanted element.
    /// \param y The y-coord of the wanted element.
    /// \note The given coords have to be inside the ImageData. The function does not does not make any boundary checks. <br>
    ///         The syntax is ImageData.at(x, y), so by the usual notations it becomes ImageData.at(j, i), not
    /// ImageData.at(i, j) like usual.
    /// \return A reference to the wanted element.
    tools::RgbColor& at(int x, int y);

    /// \brief (Output) Random access method for elements of the ImageData.
    /// \param position The position of the wanted element.
    /// \note The position has to be inside the ImageData. The function does not make any boundary checks. <br>
    ///         The syntax is ImageData.at({x, y}), so by the usual notations it becomes ImageData.at({j, i}), not
    ///     ImageData.at({i, j}) like usual.
    /// \return A const reference to the wanted element.
    const tools::RgbColor& at(const tools::Vector2I &position) const;

    /// \brief (Output) Random access method for elements of the ImageData.
    /// \param x The x-coord of the wanted element.
    /// \param y The y-coord of the wanted element.
    /// \note The given coords have to be inside the ImageData. The function does not does not make any boundary checks. <br>
    ///         The syntax is ImageData.at(x, y), so by the usual notations it becomes ImageData.at(j, i), not
    /// ImageData.at(i, j) like usual.
    /// \return A const reference to the wanted element.
    const tools::RgbColor& at(int x, int y) const;

    /// \brief Gives a pointer to the first element in the given row.
    /// \param y The wanted row
    /// \note because all elements inside the ImageData are continuous in memory, you can access all elements in that row
    /// through pointer operations. <br>
    ///         It does not perform any boundary checks
    /// \return Pointer to the first elements in the given row.
    tools::RgbColor* row(int y);

    /// \brief Getter for the size of the ImageData
    /// \return Returns the size;
    const tools::Vector2I& size() const;


    friend std::ostream& operator<<(std::ostream& os, const ImageData& dt);

    bool operator==(const ImageData& other) const;
    bool operator!=(const ImageData& other) const;

    ImageData operator+(const ImageData &other);
    ImageData operator-(const ImageData &other);
    ImageData operator*(const ImageData &other);

    friend ImageData operator+(float scalar, const ImageData &imageData);
    friend ImageData operator+(const ImageData &imageData, float scalar);

    friend ImageData operator-(const ImageData &imageData, float scalar);

    friend ImageData operator*(float scalar, const ImageData &imageData);
    friend ImageData operator*(const ImageData &imageData, float scalar);
};


#endif //COLOR_MATRIX_H
