#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <vector>


namespace tools
{

    class RgbColor
    {
    private:
        unsigned int m_maxValue;

        struct Color
        {
            unsigned int R;
            unsigned int G;
            unsigned int B;
        }m_color;

    public:
        static constexpr unsigned int EIGHT_BIT = 255;
        RgbColor(); // sets all values to zero

        RgbColor(const Color &color);
        explicit RgbColor(unsigned int maxValue);
        RgbColor(unsigned int maxValue, unsigned int R, unsigned int G, unsigned int B);
        RgbColor(unsigned int maxValue, const Color &color);

        RgbColor operator+(const RgbColor &other) const;
        RgbColor operator-(const RgbColor &other) const;
        RgbColor operator*(const RgbColor &other);


        friend RgbColor operator+(float scalar, const RgbColor &colorMatrix);
        friend RgbColor operator+(const RgbColor &colorMatrix, float scalar);

        friend RgbColor operator-(float scalar, const RgbColor &colorMatrix);
        friend RgbColor operator-( const RgbColor &colorMatrix, float scalar);

        friend RgbColor operator*(float scalar, const RgbColor &colorMatrix);
        friend RgbColor operator*(const RgbColor &colorMatrix, float scalar);


        void setMaxValue(unsigned int maxValue);
        unsigned int getMaxValue() const;

        void setColor(unsigned int R, unsigned int G, unsigned int B);

        void setColor(const Color &color);
        const Color &getColor() const;

        void setColorR(unsigned int R);
        unsigned int getColorR() const;

        void setColorG(unsigned int G);
        unsigned int getColorG() const;

        void setColorB(unsigned int B);
        unsigned int getColorB() const;
    };


    typedef std::vector<std::vector<tools::RgbColor>> ColorMatrixType;
} // tools

#endif //RGB_COLOR_H
