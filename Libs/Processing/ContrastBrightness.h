#ifndef CONTRAST_BRIGHTNESS_H
#define CONTRAST_BRIGHTNESS_H

#include "ImageProcessing.h"

/// \brief Class that modified the contrast and brightness of the given image
class ContrastBrightness : public ImageProcessing
{
private:
    ///Represents the contrast and must be greater than 0
    float m_alpha;

    ///Represent the brightness
    float m_beta;
public:
    /// \brief Default constructor which initialises alpha to 1 and beta to 0 in order
    /// to not modify the image
    ContrastBrightness();

    ///  Initialises alpha an beta to the given values
    /// \param alpha Represents the contrast and must be greater than 0
    /// \note If alpha is not greater than one it will be set to 1
    /// \param beta Represent the brightness
    ContrastBrightness(float alpha, float beta);

    /// \brief Modifies the contrast and brightness
    /// \param src The source image which you want to modify
    /// \param dst Output parameter representing the new modified image
    void process(const Image& src, Image& dst) override;


    /// \brief Setter for alpha
    /// \param alpha  Represents the contrast and must be greater than 0
    /// \note If alpha is not greater than one it will be set to 1
    void setAlpha(float alpha);

    /// \brief Getter for alpha
    /// \return Alpha
    float getAlpha() const;

    /// \brief Setter for beta
    /// \param beta Represents the brightness
    void setBeta(float beta);

    /// \brief Getter for beta
    /// \return Beta
    float getBeta() const;

};


#endif //CONTRAST_BRIGHTNESS_H
