#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <vector>
#include <ostream>

namespace tools
{

    class RgbColor
    {
    private:
        int m_maxValue;

        struct Color
        {
            //They cannot be unsigned because:
            //{10,10,10} - {20, 20, 20} should be {0,0,0}, not maxValue^3 after clamping
            int R;
            int G;
            int B;
        }m_color;

    public:
        static constexpr int EIGHT_BIT = 255;
        RgbColor(); // sets color to {0,0,0} and m_maxValue to std::numeric_limits<int>::max();

        RgbColor(const Color &color);
        RgbColor(int maxValue);
        RgbColor(int maxValue, int R, int G, int B);
        RgbColor(int maxValue, const Color &color);

        void setMaxValue(int maxValue);
        int getMaxValue() const;


        void setColor(int R, int G, int B);

        void setColor(const Color &color);
        const Color &getColor() const;

        void setColorR(int R);
        int getColorR() const;

        void setColorG(int G);
        int getColorG() const;

        void setColorB(int B);
        int getColorB() const;

        friend std::ostream& operator<<(std::ostream& os, const RgbColor& dt);

        RgbColor operator+(const RgbColor &other) const;
        RgbColor operator-(const RgbColor &other) const;
        RgbColor operator*(const RgbColor &other);


        friend RgbColor operator+(float scalar, const RgbColor &color);
        friend RgbColor operator+(const RgbColor &color, float scalar);

        friend RgbColor operator-(const RgbColor &color, float scalar);

        friend RgbColor operator*(float scalar, const RgbColor &color);
        friend RgbColor operator*(const RgbColor &color, float scalar);
    };

} // Tools

#endif //RGB_COLOR_H
