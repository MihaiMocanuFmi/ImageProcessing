#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageProcessing.h"
#include "../Image/ColorData.h"

typedef void (*ScalingMethod)(ColorData &outColorData);




class Convolution : public ImageProcessing
{
private:


    ColorData m_kernel;
    ScalingMethod scaling;

public:
    Convolution();
    Convolution(const ColorData &kernel, ScalingMethod method);

    virtual void process(const Image& src, Image& dst) = 0;

    ColorData &getKernel();
    const ColorData &getKernel() const;

    ScalingMethod &getScalingMethod();
    const ScalingMethod  &getScalingMethod() const;

};


#endif //CONVOLUTION_H
