#pragma once

#include "ImgTypes.h"

class Convolution {
public:
    Convolution() = delete;

    static RGBImg meanFiltering(RGBImg &img);

    static RGBImg LaplacianEnhance(RGBImg &img);

    static RGBImg bilateralFiltering(RGBImg &img, int window_size, double sigma_d, double sigma_r);
};