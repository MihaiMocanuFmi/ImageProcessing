#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include "tools/RgbColor.h"
#include "tools/Vector2.h"

class ColorMatrix
{
private:
    unsigned int m_globalMaxValue = 0;

    tools::RgbColor *m_matrix = nullptr;
    tools::Vector2U m_size = {0, 0};

public:
    ColorMatrix() = default;
    ColorMatrix(const tools::Vector2U &size, unsigned int maxValue);
    ColorMatrix(const tools::Vector2U &size, const tools::RgbColor &defaultValue);

    ColorMatrix(const ColorMatrix &other);
    ColorMatrix& operator=(const ColorMatrix &other);
    ~ColorMatrix();

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

    ColorMatrix operator+(const ColorMatrix &other);
    ColorMatrix operator-(const ColorMatrix &other);
    ColorMatrix operator*(const ColorMatrix &other);

    friend ColorMatrix operator+(float scalar, const ColorMatrix &colorMatrix);
    friend ColorMatrix operator+(const ColorMatrix &colorMatrix, float scalar);

    friend ColorMatrix operator-(float scalar, const ColorMatrix &colorMatrix);
    friend ColorMatrix operator-(const ColorMatrix &colorMatrix, float scalar);

    friend ColorMatrix operator*(float scalar, const ColorMatrix &colorMatrix);
    friend ColorMatrix operator*(const ColorMatrix &colorMatrix, float scalar);
};


#endif //COLOR_MATRIX_H
