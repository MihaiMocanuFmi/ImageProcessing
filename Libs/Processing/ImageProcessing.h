#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "../Image/Image.h"

class ImageProcessing
{
private:

public:
    virtual void process(const Image& src, Image& dst) = 0;

    virtual ~ImageProcessing() = default;
};


#endif //IMAGE_PROCESSING_H
