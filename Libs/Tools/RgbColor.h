#ifndef RGB_COLOR_H
#define RGB_COLOR_H

#include <vector>
#include <ostream>

namespace tools
{

    class Color
    {
    public:
        int R = 0;
        int G = 0;
        int B = 0;
        Color() = default;
        Color(int r, int g, int b);

        bool operator==(const Color &other) const;
        bool operator!=(const Color &other) const;
    };
    class RgbColor
    {
    private:
         Color m_color;
    public:
        static constexpr int MAX_VALUE = 255;

        RgbColor() = default; // sets color to {0,0,0} and m_maxValue to std::numeric_limits<int>::max();
        RgbColor(Color color, bool override = false);
        RgbColor(int R, int G, int B, bool override = false);


        void setColor(int R, int G, int B, bool override = false);

        void setColor(const Color &color, bool override = false);
        const Color &getColor() const;

        void setColorR(int R, bool override = false);
        int getColorR() const;

        void setColorG(int G, bool override = false);
        int getColorG() const;

        void setColorB(int B, bool override = false);
        int getColorB() const;

        friend std::ostream& operator<<(std::ostream& os, const RgbColor& dt);

        bool operator==(const RgbColor &other) const;
        bool operator!=(const RgbColor &other) const;

        RgbColor add(const RgbColor &other, bool overrideClamp = false) const;
        RgbColor subtract(const RgbColor &other, bool overrideClamp = false) const;
        RgbColor multiply(const RgbColor &other, bool overrideClamp = false) const;

        RgbColor operator+(const RgbColor &other) const;
        RgbColor operator-(const RgbColor &other) const;
        RgbColor operator*(const RgbColor &other) const;

        friend RgbColor add(float scalar, const RgbColor &color, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor(scalar + (float)color.getColorR(), scalar + (float)color.getColorG(),
                              scalar + (float)color.getColorB(), overrideClamp);
            return newColor;
        }
        friend RgbColor subtract(const RgbColor &color, float scalar, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor((float)color.getColorR() - scalar, (float)color.getColorG() - scalar ,
                              (float)color.getColorB() - scalar , overrideClamp);
            return newColor;
        }

        friend RgbColor multiply(float scalar, const RgbColor &color, bool overrideClamp = false)
        {
            //declared inside header because
            //Friend declaration specifying a default argument must be a definition

            RgbColor newColor;

            newColor.setColor(scalar * (float)color.getColorR(), scalar * (float)color.getColorG(),
                              scalar * (float)color.getColorB(), overrideClamp);
            return newColor;
        }

        friend RgbColor operator+(float scalar, const RgbColor &color);
        friend RgbColor operator+(const RgbColor &color, float scalar);

        friend RgbColor operator-(const RgbColor &color, float scalar);

        friend RgbColor operator*(float scalar, const RgbColor &color);
        friend RgbColor operator*(const RgbColor &color, float scalar);
    };

} // Tools

#endif //RGB_COLOR_H
