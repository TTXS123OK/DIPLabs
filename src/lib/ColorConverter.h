#pragma once

#include <vector>

using PixelData = std::vector<int>; // [ r, g, b ]
using LineData = std::vector<PixelData>;
using RGBImg = std::vector<LineData>;
using YUVImg = std::vector<LineData>;

using GrayPixel = int;
using GrayLine = std::vector<GrayPixel>;
using GrayImg = std::vector<GrayLine>;

YUVImg RGB2YUV(RGBImg& rgb_img);
RGBImg YUV2RGB(YUVImg& yuv_img);
GrayImg reserveGray(RGBImg& rgb_img);
RGBImg changeChannelY(RGBImg& rgb_img);