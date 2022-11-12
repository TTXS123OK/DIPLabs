#pragma once

#include "ImgTypes.h"

class GeometricTransformation {
public:
    GeometricTransformation() = delete;

    static RGBImg translation(RGBImg &img, int delta_x, int delta_y);

    static RGBImg rotation(RGBImg &img, double angle);

    static RGBImg scale(RGBImg &img, double ratio);

//    static RGBImg shearOnXAxis(RGBImg &img, double dx);
//
//    static RGBImg shearOnYAxis(RGBImg &img, double dy);
//
//    static RGBImg mirrorByXAxis(RGBImg &img);
//
//    static RGBImg mirrorByYAxis(RGBImg &img);
};