#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <vector>

namespace tools
{

    class RgbColor
    {
    private:
        unsigned int m_maxValue;

        struct m_Color
        {
            unsigned int R;
            unsigned int G;
            unsigned int B;
        }m_color;

    public:
        static constexpr unsigned int EIGHT_BIT = 255;
        RgbColor();
        RgbColor(unsigned int maxValue);
        RgbColor(unsigned int maxValue, unsigned int R, unsigned int G, unsigned int B);

        void setColor(unsigned int R, unsigned int G, unsigned int B);
        void setColorR(unsigned int R);
        void setColorG(unsigned int G);
        void setColorB(unsigned int B);
    };


    typedef std::vector<std::vector<tools::RgbColor>> ColorMatrix;
} // tools

#endif //RGBCOLOR_H
