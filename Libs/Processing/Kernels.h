#ifndef KERNELS_H
#define KERNELS_H

#include "../Image/ColorData.h"

/// \brief Module containing all used Kernels
namespace Kernels
{
    class KernelType
    {
    public:
        ColorData kernel = {};
        //ok so virtual doesn't really work out, swapped it to static
        static void scalingMethod(ColorData &outColorData);

        KernelType() = default;

        //virtual ~KernelType() = default;
    };

    class IdentityKernel final : public KernelType
    {
    public:
        static void scalingMethod(ColorData &outColorData);

        IdentityKernel();

    };

    class MeanBlurKernel final : public KernelType
    {
    public:
        /// function that multiplies the convolution result by 1/9.0)
        /// \param outColorData
        static void scalingMethod(ColorData &outColorData);

        MeanBlurKernel();

    };

    class GaussianBlur3x3Kernel final : public KernelType
    {
    public:
        /// function that multiplies the convolution result by 1/16.0)
        /// \param outColorData
        static void scalingMethod(ColorData &outColorData);

        GaussianBlur3x3Kernel();
    };


    class HorizontalSobelKernel final : public KernelType
    {
    public:
        /// function that converts the range [-4*255, 4*255] to the range [0, 255]).
        /// \param outColorData
        static void scalingMethod(ColorData &outColorData);


        HorizontalSobelKernel();
    };

    class VerticalSobelKernel final : public KernelType
    {
    public:
        /// function that converts the range [-4*255, 4*255] to the range [0, 255]). (considering globalMaxValue = 255)
        /// \param outColorData
        static void scalingMethod(ColorData &outColorData);

        VerticalSobelKernel();
    };

}
#endif //KERNELS_H
