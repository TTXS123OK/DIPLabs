#pragma once

#include "ImgTypes.h"

class ColorConverter {
public:
    ColorConverter() = delete;

    static YUVImg RGB2YUV(RGBImg &rgb_img);

    static RGBImg YUV2RGB(YUVImg &yuv_img);

    static BinaryImg Gray2Binary(GrayImg &gray_img);

    static GrayImg reserveGray(RGBImg &rgb_img);

    static RGBImg changeChannelY(RGBImg &rgb_img);
};