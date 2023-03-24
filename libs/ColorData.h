#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include "tools/RgbColor.h"
#include "tools/Vector2.h"

class ColorData
{
private:
    unsigned int m_globalMaxValue = 0;

    tools::RgbColor *m_matrix = nullptr;
    tools::Vector2U m_size = {0, 0};

public:
    ColorData() = default;
    ColorData(const tools::Vector2U &size, unsigned int maxValue);
    ColorData(const tools::Vector2U &size, const tools::RgbColor &defaultValue);

    ColorData(const ColorData &other);
    ColorData& operator=(const ColorData &other);
    ~ColorData();

    void resize(const tools::Vector2U &newSize);
    void resize(const tools::Vector2U &newSize, const tools::RgbColor &defaultValue);


    //TODO: redefine it through an [][] operator overload
    void setAt(const tools::Vector2U &position, const tools::RgbColor &color);
    void setAt(unsigned int x, unsigned int y, const tools::RgbColor &color);

    tools::RgbColor& getAt(const tools::Vector2U &position);
    tools::RgbColor& getAt(unsigned int x, unsigned int y);

    const tools::RgbColor& getAt(const tools::Vector2U &position) const;
    const tools::RgbColor& getAt(unsigned int x, unsigned int y) const;

    const tools::Vector2U& getSize();

    ColorData operator+(const ColorData &other);
    ColorData operator-(const ColorData &other);
    ColorData operator*(const ColorData &other);

    friend ColorData operator+(float scalar, const ColorData &colorMatrix);
    friend ColorData operator+(const ColorData &colorMatrix, float scalar);

    friend ColorData operator-(float scalar, const ColorData &colorMatrix);
    friend ColorData operator-(const ColorData &colorMatrix, float scalar);

    friend ColorData operator*(float scalar, const ColorData &colorMatrix);
    friend ColorData operator*(const ColorData &colorMatrix, float scalar);
};


#endif //COLOR_MATRIX_H
