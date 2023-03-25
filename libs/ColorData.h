#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include <ostream>
#include "tools/RgbColor.h"
#include "tools/Vector2.h"

class ColorData
{
private:
    int m_globalMaxValue = 0;

    tools::RgbColor *m_matrix = nullptr;
    tools::Vector2I m_size = {0, 0};

public:
    ColorData() = default;
    ColorData(const tools::Vector2I &size, int maxValue);
    ColorData(const tools::Vector2I &size, const tools::RgbColor &defaultValue);

    ColorData(const ColorData &other);
    ColorData& operator=(const ColorData &other);
    ~ColorData();

    void resize(const tools::Vector2I &newSize);
    void resize(const tools::Vector2I &newSize, const tools::RgbColor &defaultValue);


    //TODO: redefine it through an [][] operator overload
    /*
    void setAt(const tools::Vector2I &position, const tools::RgbColor &color);
    void setAt(int x, int y, const tools::RgbColor &color);
    */
    tools::RgbColor& at(const tools::Vector2I &position);
    tools::RgbColor& at(int x, int y);

    const tools::RgbColor& at(const tools::Vector2I &position) const;
    const tools::RgbColor& at(int x, int y) const;

    tools::RgbColor* row(int y);

    const tools::Vector2I& size() const;
    int globalMaxValue() const;

    friend std::ostream& operator<<(std::ostream& os, const ColorData& dt);

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
