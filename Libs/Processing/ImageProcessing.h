#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "../Image/Image.h"

/// \brief Abstract class used for processing
class ImageProcessing
{
private:

public:
    /// \brief Default Constructor
    ImageProcessing() = default;

    /// \brief Pure virtual method which will take a source image, and create a new modified image
    /// \param src The source image which you want to modify
    /// \param dst Output parameter representing the new modified image
    virtual void process(const Image& src, Image& dst) = 0;

    /// \brief Virtual default destructor
    virtual ~ImageProcessing() = default;
};


#endif //IMAGE_PROCESSING_H
