#ifndef PPM_RAW_H
#define PPM_RAW_H

#include <vector>
#include <string>

#include "../Tools/Vector2.h"
#include "../Tools/RgbColor.h"
#include "ColorData.h"

/// \brief  Class responsible for loading and saving .ppm, .pgm and .pbm images
class PortablePixMap_Plain
{
private:
    std::string m_magicNumber = "";
    tools::Vector2I m_size = {0, 0};
    int m_maxValue = 0;


    ///
    /// Will remove all comments, keeps newlines and spaces before the comment
    ///
    void m_removeComments(std::string &rPlainFile);
    void m_preProcessPPM(std::string &rPlainFile);

    ///
    /// MUST NOT CONTAIN COMMENTS
    /// returns true on success, false otherwise
    ///
    bool m_findMagicNumber(const std::string &rPlainFile, std::string &outMagicNumber);

    ///
    /// Given a string it finds the first number in it;
    /// It returns through the out/// parameters the position in str of the starting digit and the last digit (inclusive)
    ///
    bool m_findFirstNumber(const std::string &str, std::size_t startingPos, std::size_t &outStartPos, std::size_t &outEndPos);

    ///
    /// MUST NOT CONTAIN COMMENTS
    /// returns true on success, false otherwise
    /// We assume that the next pair of number represents the size;
    ///
    bool m_findSize(const std::string &rPlainFile, tools::Vector2I &outSize);

    bool m_findMaxValue(const std::string &rPlainFile, int &outMaxValue);

    ///
    /// Will search for colors in a string following the P1 format. The output colorMatrix will be converted into
    /// P3 format
    ///
    bool m_findColorsP1Format(const std::string &rPlainFile, ColorData &outColorMatrix);

    ///
    /// Will search for colors in a string following the P2format. The output colorMatrix will be converted into
    /// P3 format
    ///
    bool m_findColorsP2Format(const std::string &rPlainFile, ColorData &outColorMatrix);

    ///
    /// Will search for colors in a string following the P3 format. The output colorMatrix will be converted into
    /// P3 format
    ///
    bool m_findColorsP3Format(const std::string &rPlainFile, ColorData &outColorMatrix);

    ///
    /// Will find the color matrix in the given string file
    ///
    bool m_findColors(const std::string &rPlainFile, ColorData &outColorMatrix);

    void cacheDataParameters(const ColorData &data);
public:
    /// \brief The Magic Number that represents .ppm files
    static constexpr char PPM_MAGIC_NUMBER[] = "P3";

    /// \brief The Magic Number that represents .pgm files
    static constexpr char PGM_MAGIC_NUMBER[] = "P2";

    /// \brief The Magic Number that represents .pbm files
    static constexpr char PBM_MAGIC_NUMBER[] = "P1";

    /// \brief Default constructor, initialises all members to their zero/null values
    PortablePixMap_Plain() = default;


    /// \brief Given a string, representing the data of an image, it creates a ColorData with the given data.
    /// \param plainFile String containing the image format.
    /// \param outData Output parameter, representing the loaded image.
    /// \return True if it succeeded, false otherwise.
    /// \note It supports loading plain (ASCII) .ppm, .pgm and .pbm images, but they will be converted all to the .ppm
    /// format inside outData.
    bool loadPlain(std::string plainFile, ColorData &outData);

    /// \brief Given the colorData of an image, it saves it to the given string after the standard of the .ppm format.
    /// \param outPlainFile String representing the image in .ppm format which was contained inside ColorData
    /// \param data The ColorData to be saved to string
    /// \return True if it succeeded, false otherwise.
    bool saveToString(std::string &outPlainFile, const ColorData &data);

};


#endif //PPM_RAW_H
