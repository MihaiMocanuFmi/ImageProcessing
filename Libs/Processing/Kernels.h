#ifndef KERNELS_H
#define KERNELS_H

#include "../Image/ImageData.h"

/// \brief Module containing Kernels used for convolutions
namespace Kernels
{
/// \brief Function pointer for the scaling method, taking as parameter a reference to ImageData
typedef void (*ScalingMethod)(ImageData &outColorData);

    /// \brief Basic kernel type
    class KernelType
    {
    public:
        /// \brief The kernel used in convolutions
        ImageData kernel = {};

        //ok so virtual doesn't really work out, swapped it to static
        /// \brief Used to scale the values of ImageData to a certain range
        /// \param outColorData The ImageData to be scaled
        static void scalingMethod(ImageData &outColorData);

        /// \brief Default constructor
        KernelType() = default;

        //virtual ~KernelType() = default;
    };

    /// \brief Class representing an Identity kernel, it does not modify the image
    class IdentityKernel final : public KernelType
    {
    public:
        /// \brief Does not modify the ImageData
        /// \param outColorData
        static void scalingMethod(ImageData &outColorData);

        /// \brief Constructor initialising the kernel to the identity.
        /// \note This kernel won't modify the image
        IdentityKernel();

    };

    /// \brief Class representing a Mean Blur kernel, it blurs the the image
    class MeanBlurKernel final : public KernelType
    {
    public:
        /// \brief function that scales the values inside ImageData by 1/9.0f
        /// \param outColorData the ImageData to be scaled
        static void scalingMethod(ImageData &outColorData);

        /// \brief Constructor initialising the kernel to the 3x3 MeanBlur Kernel.
        MeanBlurKernel();

    };

    /// \brief Class representing a Gaussian Blur kernel, it blurs the the image
    class GaussianBlur3x3Kernel final : public KernelType
    {
    public:
        /// \brief function that scales the values inside ImageData by 1/16.0f
        /// \param outImageData the ImageData to be scaled
        static void scalingMethod(ImageData &outImageData);

        /// \brief Constructor initialising the kernel to the 3x3 Gaussian Blur Kernel.
        GaussianBlur3x3Kernel();
    };

    /// \brief Class representing a Horizontal Sobel Kernel, it highlights horizontal lines in the image
    class HorizontalSobelKernel final : public KernelType
    {
    public:
        /// \brief function that converts the range [-4*255, 4*255] to the range [0, 255]).
        /// \param ouImageData the ImageData to be scaled
        static void scalingMethod(ImageData &ouImageData);

        /// \brief Constructor initialising the kernel to the 3x3 Horizontal Sobel Kernel.
        HorizontalSobelKernel();
    };

/// \brief Class representing a Vertical Sobel Kernel, it highlights vertical lines in the image
    class VerticalSobelKernel final : public KernelType
    {
    public:
        /// \brief Function that converts the range [-4*255, 4*255] to the range [0, 255]).
        /// \param outImageData the ImageData to be scaled
        static void scalingMethod(ImageData &outImageData);

        /// \brief Constructor initialising the kernel to the 3x3 Vertical Sobel Kernel.
        VerticalSobelKernel();
    };

}
#endif //KERNELS_H
