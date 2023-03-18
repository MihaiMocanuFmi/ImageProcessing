#ifndef PPM_RAW_H
#define PPM_RAW_H

#include <vector>
#include <string>

#include "tools/Vector2.h"
#include "tools/RgbColor.h"

class PortablePixMap_Plain
{
private:
    std::string m_magicNumber;
    tools::Vector2U m_size;
    unsigned int m_maxValue;

    tools::ColorMatrix m_colorDataMatrix;

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
    bool m_findFirstNumber(const std::string &str, unsigned int startingPos, int &outStartPos, int &outEndPos);

    /*
     * MUST NOT CONTAIN COMMENTS
     * returns true on success, false otherwise
     * We assume that the next pair of number represents the size;
     */
    bool m_findSize(std::string &rPlainFile, tools::Vector2U &outSize);

    bool m_findMaxValue(std::string &rPlainFile, unsigned int &outMaxValue);

    /*
     * Will search for colors in a string following the P1 format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP1Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix);

    /*
     * Will search for colors in a string following the P2format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP2Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix);

    /*
     * Will search for colors in a string following the P3 format. The output colorMatrix will be converted into
     * P3 format
     */
    bool m_findColorsP3Format(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix);

    /*
     * Will find the color matrix in the given string file
     */
    bool m_findColors(std::string &rPlainFile, tools::ColorMatrix &outColorMatrix);
public:
    static constexpr char MAGIC_NUMBER[] = "P3";
    static constexpr char PGM_MAGIC_NUMBER[] = "P2";
    static constexpr char PBM_MAGIC_NUMBER[] = "P1";

    static constexpr char EXTENSION[] = ".ppm";

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
    bool loadPlain(std::string plainFile);

    bool saveToString(std::string &outPlainFile);

    const std::string &getMagicNumber() const;
    const tools::Vector2U &getSize() const;
    unsigned int getMaxValue() const;

    const tools::ColorMatrix &getColorMatrix() const;

};


#endif //PPM_RAW_H
