#pragma once

#include <vector>
#include <cstdint>

using PixelData = std::vector<uint8_t>; // [ r, g, b ]
using LineData = std::vector<PixelData>;
using RGBImg = std::vector<LineData>;
using YUVImg = std::vector<LineData>;

using GrayPixel = uint8_t; // 00: black, FF: white
using GrayLine = std::vector<GrayPixel>;
using GrayImg = std::vector<GrayLine>;