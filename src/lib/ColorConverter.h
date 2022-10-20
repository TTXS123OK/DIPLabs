#pragma once

#include "Type.h"

class ColorConverter {
public:
    static YUVImg RGB2YUV(RGBImg& rgb_img);
    static RGBImg YUV2RGB(YUVImg& yuv_img);
    static GrayImg reserveGray(RGBImg& rgb_img);
    static RGBImg changeChannelY(RGBImg& rgb_img);
};