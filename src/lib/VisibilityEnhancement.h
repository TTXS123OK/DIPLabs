#pragma once

#include "ImgTypes.h"

struct Histogram {
    int color_num;
    std::vector<double> hist;

    static Histogram buildByGray(GrayImg gray_img);

    static Histogram buildEqual(int color_num);
};

class VisibilityEnhancement {
public:
    VisibilityEnhancement() = delete;

    static RGBImg logarithmicForRGB(RGBImg &rgb_img);

    // TODO: static RGBImg logarithmicForGray(GrayImg &gray_img);

    // TODO: static RGBImg fitHistogramForRGB(RGBImg &rgb_img, Histogram *target_hist);

    static GrayImg fitHistogramForGray(GrayImg &gray_img, Histogram &target_hist);
};