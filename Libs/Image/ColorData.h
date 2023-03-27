#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include <ostream>
#include "../Tools/RgbColor.h"
#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"

class ColorData
{
private:
    int m_globalMaxValue = 0; //for now these are useless
    int m_globalMinValue = 0; //for now these are useless

    tools::RgbColor *m_matrix = nullptr;
    tools::Vector2I m_size = {0, 0};

public:
    ColorData() = default;
    ColorData(const tools::Vector2I &size);
    ColorData(const tools::Vector2I &size, int maxValue, int minValue = 0);
    ColorData(const tools::Vector2I &size, const tools::RgbColor &defaultValue);

    ColorData(const ColorData &other);
    ColorData& operator=(const ColorData &other);
    ~ColorData();

    void resize(const tools::Vector2I &newSize);
    void resize(const tools::Vector2I &newSize, const tools::RgbColor &defaultValue);

    bool getROI(ColorData &roiColorData, tools::Rectangle roiRect);

    //TODO: redefine it through an [][] operator overload
    tools::RgbColor& at(const tools::Vector2I &position);
    tools::RgbColor& at(int x, int y);

    const tools::RgbColor& at(const tools::Vector2I &position) const;
    const tools::RgbColor& at(int x, int y) const;

    tools::RgbColor* row(int y);

    const tools::Vector2I& size() const;
    int globalMaxValue() const;
    int globalMinValue() const;

    friend std::ostream& operator<<(std::ostream& os, const ColorData& dt);

    ColorData operator+(const ColorData &other);
    ColorData operator-(const ColorData &other);
    ColorData operator*(const ColorData &other);

    friend ColorData operator+(float scalar, const ColorData &colorMatrix);
    friend ColorData operator+(const ColorData &colorMatrix, float scalar);

    friend ColorData operator-(const ColorData &colorMatrix, float scalar);

    friend ColorData operator*(float scalar, const ColorData &colorMatrix);
    friend ColorData operator*(const ColorData &colorMatrix, float scalar);
};


#endif //COLOR_MATRIX_H
