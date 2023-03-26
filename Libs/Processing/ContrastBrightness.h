#ifndef CONTRAST_BRIGHTNESS_H
#define CONTRAST_BRIGHTNESS_H

#include "ImageProcessing.h"

class ContrastBrightness : public ImageProcessing
{
private:
    float m_alpha;
    float m_beta;
public:
    ContrastBrightness();
    ///
    /// \param alpha > 0;
    /// \param beta
    ContrastBrightness(float alpha, float beta);

    void process(const Image& src, Image& dst);

    void setAlpha(float alpha);
    float getAlpha() const;

    void setBeta(float beta);
    float getBeta() const;

};


#endif //CONTRAST_BRIGHTNESS_H
