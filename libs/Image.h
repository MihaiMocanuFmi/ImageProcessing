#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "PortablePixMap_Plain.h"
#include "tools/Vector2.h"


class Image
{
private:
    tools::Vector2U m_size = {};

    PortablePixMap_Plain ppm = {};

public:
    Image() = default;

    Image(unsigned int width, unsigned int height);
    Image(tools::Vector2U size);

    bool load(std::string imagePath);
    bool save(std::string imagePath);


};


#endif //IMAGE_H
