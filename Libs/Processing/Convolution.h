#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include "ImageProcessing.h"
#include "Kernels.h"

#include "../Image/ImageData.h"





/// \brief Class that applies a given convolution to the image
class Convolution : public ImageProcessing
{
private:
    /// \brief The kernel which will be applied to the image
    ImageData m_kernel;

    /// \brief Function pointer to the scaling method
    Kernels::ScalingMethod m_scaling;

    /// \brief Used to apply the multiplication operation between a given Image and it's kernel at a specific spot
    /// \param imageData The ImageData on which you want to apply the multiplication
    /// \param position The position where you want to apply the multiplication
    /// \return A RgbColor representing the result
    tools::RgbColor m_multiplyWithKernel(const ImageData& imageData, tools::Vector2I position);
public:
    /// \brief Default constructor initialising the convolution kernel and scaling method to the identiy convolution
    Convolution();

    /// \brief Constructor initialising the convolution kernel and scaling method to the given parameters
    /// \param kernel The kernel you want to be used in the convolution
    /// \param method The scaling method to re-normalize the color ranges
    Convolution(const ImageData &kernel, Kernels::ScalingMethod method);

    /// \brief Applies the convolution that was given before to the image
    /// \param src The source image which you want to modify
    /// \param dst Output parameter representing the new modified image
    void process(const Image& src, Image& dst) override;

    /// \brief (Input-Output) Getter for kernel
    /// \return Reference to Kernel
    ImageData &getKernel();

    /// \brief (Output) Getter for kernel
    /// \return Const reference to Kernel
    const ImageData &getKernel() const;

    /// \brief (Input-Output) Getter for the scaling method
    /// \return Reference to the function pointer
    Kernels::ScalingMethod &getScalingMethod();

    /// \brief (Input-Output) Getter for the scaling method
    /// \return Const reference to the function pointer
    const Kernels::ScalingMethod  &getScalingMethod() const;

};


#endif //CONVOLUTION_H
