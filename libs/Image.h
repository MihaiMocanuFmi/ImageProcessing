#ifndef IMAGE_H
#define IMAGE_H

#include "tools/Vector2.h"

class Image
{
private:
    tools::Vector2U m_size = {};

public:
    Image() = default;

    Image(unsigned int width, unsigned int height);
    Image(tools::Vector2U size);


};


#endif //IMAGE_H
