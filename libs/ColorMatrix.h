#ifndef COLOR_MATRIX_H
#define COLOR_MATRIX_H

#include "tools/RgbColor.h"
#include "tools/Vector2.h"

class ColorMatrix
{
private:
    unsigned int m_globalMaxValue = 0;

    tools::RgbColor **m_matrix = nullptr;
    tools::Vector2U m_size = {0, 0};

public:
    ColorMatrix() = default;
    ColorMatrix(const tools::Vector2U &size, unsigned int maxValue);
    ColorMatrix(const tools::Vector2U &size, const tools::RgbColor &defaultValue);

    ColorMatrix& operator=(const ColorMatrix &other);
    ColorMatrix(const ColorMatrix &other);
    ~ColorMatrix();


    void resize(const tools::Vector2U &newSize);
    void resize(const tools::Vector2U &newSize, const tools::RgbColor &defaultValue);



};


#endif //COLOR_MATRIX_H
