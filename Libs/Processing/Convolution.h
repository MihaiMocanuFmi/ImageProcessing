#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageProcessing.h"
#include "Kernels.h"

#include "../Image/ColorData.h"

typedef void (*ScalingMethod)(ColorData &outColorData);




class Convolution : public ImageProcessing
{
private:
    ColorData m_kernel;
    ScalingMethod m_scaling;

    tools::RgbColor m_multiplyWithKernel(const ColorData& colorData, tools::Vector2I position);
public:
    Convolution();
    Convolution(const ColorData &kernel, ScalingMethod method);

    void process(const Image& src, Image& dst);

    ColorData &getKernel();
    const ColorData &getKernel() const;

    ScalingMethod &getScalingMethod();
    const ScalingMethod  &getScalingMethod() const;

};


#endif //CONVOLUTION_H
