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

using BinaryPixel = uint8_t; // 00: black, FF: white
using BinaryLine = std::vector<BinaryPixel>;
using BinaryImg = std::vector<BinaryLine>; // only contains 00 and FF
using BinaryTemplate = BinaryImg;