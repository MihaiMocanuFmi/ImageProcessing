#ifndef PPM_RAW_H
#define PPM_RAW_H

#include <vector>
#include <string>

#include "tools/Vector2.h"
#include "tools/RgbColor.h"

class PortablePixMap_Plain
{
private:

    tools::Vector2U m_size;
    unsigned int m_maxValue;

    std::vector<tools::RgbColor> m_colorData;
public:
    static constexpr char MAGIC_NUMBER[] = "P3";
    static constexpr char EXTENSION[] = ".ppm";

    PortablePixMap_Plain() = default;
    PortablePixMap_Plain(tools::Vector2U size, unsigned int maxValue);

    void loadPlain(const std::string &plainFile);
    void loadJustColor(tools::Vector2U size, unsigned int maxValue, std::vector<tools::RgbColor> colorData);
};


#endif //PPM_RAW_H
