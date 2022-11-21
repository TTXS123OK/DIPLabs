#pragma once

#include "ImgTypes.h"

class Convolution {
public:
    Convolution() = delete;

    static RGBImg meanFiltering(RGBImg &img);

    static RGBImg LaplacianEnhance(RGBImg &img);
};