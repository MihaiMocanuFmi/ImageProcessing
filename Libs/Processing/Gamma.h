#ifndef GAMMA_H
#define GAMMA_H

#include "ImageProcessing.h"

class Gamma : public ImageProcessing
{
private:
    float m_gamma;
public:
    Gamma();
    explicit Gamma(float gamma);

    void process(const Image& src, Image& dst);

    ///
    /// \param gamma > 0
    void setGamma(float gamma);
    float getGamma() const;


};


#endif //GAMMA_H
