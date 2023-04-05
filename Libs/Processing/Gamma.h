#ifndef GAMMA_H
#define GAMMA_H

#include "ImageProcessing.h"

/// \brief Class representing a gamma correction process
class Gamma : public ImageProcessing
{
private:
    float m_gamma;
public:
    /// \brief Default constructor, it sets the gamma to 1
    /// \note A gamma of 1 won't modify the image
    Gamma();

    /// \brief It initialises the gamma, for the gamma correction process
    /// \param gamma The gamma should be > 0
    /// \note if gamma is <= 0, it will be changed to 1 in order no to modify the image
    explicit Gamma(float gamma);

    /// \brief Applies the gamma correction process
    /// \param src The source image which you want to modify
    /// \param dst Output parameter representing the new modified image
    void process(const Image& src, Image& dst);

    /// \brief Setter for gamma
    /// \param The given gamma should be greater than 0
    /// \note If gamma is <= 0, it is set to 1 in order to not modify the image
    void setGamma(float gamma);

    /// \brief Getter for gamma
    /// \return gamma
    float getGamma() const;


};


#endif //GAMMA_H
