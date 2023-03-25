#ifndef PPM_RAW_H
#define PPM_RAW_H

#include <vector>
#include <string>

#include "../Tools/Vector2.h"
#include "../Tools/RgbColor.h"
#include "ColorData.h"


class PortablePixMap_Plain
{
private:
    std::string m_magicNumber;
    tools::Vector2I m_size;
    int m_maxValue;


    /*
     * Will remove all comments, keeps newlines and spaces before the comment
     */
    void m_removeComments(std::string &rPlainFile);
    void m_preProcessPPM(std::string &rPlainFile);

    /*
     * MUST NOT CONTAIN COMMENTS
     * returns true on success, false otherwise
     */
    bool m_findMagicNumber(std::string &rPlainFile, std::string &outMagicNumber);

    /*
     * Given a string it finds the first number in it;
     * It returns through the out* parameters the position in str of the starting digit and the last digit (inclusive)
     */
    bool m_findFirstNumber(const std::string &str, std::size_t startingPos, std::size_t &outStartPos, std::size_t &outEndPos);

    /*
     * MUST NOT CONTAIN COMMENTS
     * returns true on success, false otherwise
     * We assume that the next pair of number represents the size;
     */
    bool m_findSize(std::string &rPlainFile, tools::Vector2I &outSize);

    bool m_findMaxValue(std::string &rPlainFile, int &outMaxValue);

    /*
     * Will search for colors in a string following the P1 format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP1Format(std::string &rPlainFile, ColorData &outColorMatrix);

    /*
     * Will search for colors in a string following the P2format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP2Format(std::string &rPlainFile, ColorData &outColorMatrix);

    /*
     * Will search for colors in a string following the P3 format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP3Format(std::string &rPlainFile, ColorData &outColorMatrix);

    /*
     * Will find the color matrix in the given string file
     */
    bool m_findColors(std::string &rPlainFile, ColorData &outColorMatrix);

    void cacheDataParameters(const ColorData &data);
public:
    static constexpr char PPM_MAGIC_NUMBER[] = "P3";
    static constexpr char PGM_MAGIC_NUMBER[] = "P2";
    static constexpr char PBM_MAGIC_NUMBER[] = "P1";


    PortablePixMap_Plain();

    /* It's backwards compatible with PGM and PBM files,
     * We make the following assumptions after ignoring all comments:
     * 1) The first line that contains a letter will be the letter P followed by one the numbers:
     *      1, 2 or 3.
     * 2) The next pair of two numbers after that will represent the size
     *
     * returns true on success, false otherwise
     *
     */
    bool loadPlain(std::string plainFile, ColorData &outData);

    bool saveToString(std::string &outPlainFile, const ColorData &data);

};


#endif //PPM_RAW_H
