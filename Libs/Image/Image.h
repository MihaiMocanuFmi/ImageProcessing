#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "PortablePixMap_Plain.h"
#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"
#include "ColorData.h"

///\brief Class representing an Image. It manages the ColorData and also loading/saving
class Image
{
private:
    //Tools::Vector2I m_size = {};

    PortablePixMap_Plain ppm = {};
    ColorData m_colorData = {};

public:
    /// \brief Creates an Image having all elements ones: RgbColor(1, 1, 1)
    /// \param width The width of the image
    /// \param height The height of the Image
    /// \return A new Image containing only ones
    static Image zeros(int width, int height);

    /// \brief Creates an Image having all elements zeros: RgbColor(0, 0, 0)
    /// \param width The width of the image
    /// \param height The height of the Image
    /// \return A new Image containing only ones
    static Image ones(int width, int height);

    /// \brief The default constructor, it initialises all values to their zero or null value
    Image() = default;

    /// \brief It creates an Image with a specified size. The element inside colorData are not initialised
    /// \param width The width of the image (.x)
    /// \param height The height of the image (.y)
    /// \note The size of the Image coincides with the size of the ColorData contained.
    Image(int width, int height);

    /// \brief It creates an Image with a specified size. The element inside colorData are not initialised
    /// \param size The size of the Image;
    /// \note The size of the Image coincides with the size of the ColorData contained.
    explicit Image(tools::Vector2I size);

    /// \brief It creates an Image knowing its ColorData
    /// \param colorData The ColorData of the image
    /// \note The size of the ColorData will coincide with the size of the Image.
    Image(const ColorData &colorData);


    /// \brief Loads into Image.data() the image found at the given path
    /// \param imagePath the (relative) path to the image file
    /// \note The path is relative to the executable location
    /// \return True if it succeeded, false otherwise.
    bool load(const std::string &imagePath);

    /// \brief Saves the Image.data() in the file at the given path.
    /// \param imagePath the (relative) path to the image file
    /// \note The path is relative to the executable location.
    /// <br>    If the image file does not exist, then it will be created.
    /// \return True if it succeeded, false otherwise.
    bool save(const std::string &imagePath);

    /// \brief Copies the elements inside the given ROI (Region of Interest)
    /// \param roiImg Output parameter, it returns the copied elements inside the region.
    /// \param roiRect The bounds of the Region of Interest inside the original Image
    /// \note roiRect has to be contained inside the Image perimeter in order for the function to succeed
    /// \return True if it was successfully able to copy and false otherwise.
    bool getROI(Image &roiImg, tools::Rectangle roiRect);
    /// \brief Copies the elements inside the given ROI (Region of Interest)
    /// \param roiImg Output parameter, it returns the copied elements inside the region.
    /// \param x The x coord of the upper left corner of the Region of Interest inside the original Image.
    /// \param y The y coord of the upper left corner of the Region of Interest inside the original Image.
    /// \param width The width of the Region of Interest inside the original Image.
    /// \param height The width of the Region of Interest inside the original Image.
    /// \note The ROI has to be contained inside the Image perimeter in order for the function to succeed
    /// \return True if it was successfully able to copy and false otherwise.
    bool getROI(Image &roiImg, int x, int y, int width, int height);

    /// \brief It releases the Image.data().
    void release();

    /// \brief Checks if the Image.data() is empty. This is equivalent to the size of the Image being zero
    /// \return True if it's empty, false otherwise.
    bool isEmpty() const;

    /// \brief Getter for data.
    /// \return Const reference to the data;
    const ColorData &data() const;

    /// \brief Getter for size
    /// \return Const reference to the size;
    const tools::Vector2I &size() const;

    /// \brief (Input-Output) Random access method for elements of the Image.
    /// \param position The position of the wanted element.
    /// \note The position has to be inside the Image. The function does not make any boundary checks. <br>
    ///         The syntax is Image.at({x, y}), so by the usual notations it becomes Image.at({j, i}), not
    ///     Image.at({i, j}) like usual.
    /// \return A reference to the wanted element.
    tools::RgbColor& at(const tools::Vector2I &position);

    /// \brief (Input-Output) Random access method for elements of the Image.
    /// \param x The x-coord of the wanted element.
    /// \param y The y-coord of the wanted element.
    /// \note The given coords have to be inside the Image. The function does not does not make any boundary checks. <br>
    ///         The syntax is Image.at(x, y), so by the usual notations it becomes Image.at(j, i), not
    ///     Image.at(i, j) like usual.
    /// \return A reference to the wanted element.
    tools::RgbColor& at(int x, int y);

    /// \brief (Output) Random access method for elements of the Image.
    /// \param position The position of the wanted element.
    /// \note The position has to be inside the Image. The function does not make any boundary checks. <br>
    ///         The syntax is Image.at({x, y}), so by the usual notations it becomes Image.at({j, i}), not
    ///     Image.at({i, j}) like usual.
    /// \return A const reference to the wanted element.
    const tools::RgbColor& at(const tools::Vector2I &position) const;

    /// \brief (Output) Random access method for elements of the Image.
    /// \param x The x-coord of the wanted element.
    /// \param y The y-coord of the wanted element.
    /// \note The given coords have to be inside the Image. The function does not does not make any boundary checks. <br>
    ///         The syntax is Image.at(x, y), so by the usual notations it becomes Image.at(j, i), not
    /// Image.at(i, j) like usual.
    /// \return A const reference to the wanted element.
    const tools::RgbColor& at(int x, int y) const;

    /// \brief Gives a pointer to the first element in the given row.
    /// \param y The wanted row
    /// \note because all elements inside the Image are continuous in memory, you can access all elements in that row
    /// through pointer operations. <br>
    ///         It does not perform any boundary checks
    /// \return Pointer to the first elements in the given row.
    tools::RgbColor* row(int y);

    bool operator==(const Image &other) const;
    bool operator!=(const Image &other) const;

    friend std::ostream& operator<<(std::ostream& os, const Image& dt);

    Image operator+(const Image &i);
    Image operator-(const Image &i);
    Image operator*(const Image &i);

    friend Image operator+(float scalar, const Image &image);
    friend Image operator+(const Image &image, float scalar);

    friend Image operator-(const Image &image, float scalar);

    friend Image operator*(float scalar, const Image &image);
    friend Image operator*(const Image &image, float scalar);

};



#endif //IMAGE_H
