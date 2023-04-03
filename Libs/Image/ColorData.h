#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include <ostream>
#include "../Tools/RgbColor.h"
#include "../Tools/Vector2.h"
#include "../Tools/Rectangle.h"

class ColorData
{
private:


    tools::Vector2I m_size = {0, 0};
    tools::RgbColor *m_matrix = nullptr;

    //tools::RgbColor  m_rescaleColorValue(const tools::RgbColor &color, int wantedMaxValue);
public:
    static constexpr int MAX_VALUE = tools::RgbColor::MAX_VALUE;

    ColorData() = default;
    explicit ColorData(const tools::Vector2I &size);
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


    friend std::ostream& operator<<(std::ostream& os, const ColorData& dt);

    bool operator==(const ColorData& other) const;
    bool operator!=(const ColorData& other) const;

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
