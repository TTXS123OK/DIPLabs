#pragma once

#include <string>
#include <vector>

#include "Type.h"

// This version of BMPConverter only support part of Bitmap format.
// Reference: https://www.cnblogs.com/xiekeli/archive/2012/05/09/2491191.html

struct BitMapFileHeader {
    uint16_t bfType;        // Fixed value of 0x4d42 to represent Bitmap
    uint32_t bfSize = 0;    // Size of bmp file
    uint16_t bfReservered1 = 0; // Always zero
    uint16_t bfReservered2 = 0; // Always zero
    uint32_t bfOffbits = 0; // Offset to pixel datas
};

struct BitMapInfoHeader {
    uint32_t biSize;         // Sizeof info header
    int32_t biWidth;         // Width of Bitmap
    int32_t biHeight;        // Height of Bitmap
    uint16_t biPlanes;       // Always 1
    uint16_t biBitCount;     // Number of bits per pixel, only support 8 and 24
    uint32_t biCompression;  // Zero for no compression, only support 0
    uint32_t biSizeImage;    // Unsupported
    int32_t biXPelsPerMeter; // Unsupported
    int32_t biYPelsPerMeter; // Unsupported
    uint32_t biClrUsed;      // Unsupported
    uint32_t biClrImportant; // Unsupported
};

struct PaletteItem {
    uint8_t B;
    uint8_t G;
    uint8_t R;
    uint8_t reserved;
};

class BMPImage {
public:
    BitMapFileHeader file_header;
    BitMapInfoHeader info_header;
    std::vector<PaletteItem> color_palette;
    std::vector<uint8_t> pixel_data;


    void load(const std::string& path);
    void save(const std::string& path);

    RGBImg extractRGB();
    GrayImg extractGray();

    void buildFromRGB(RGBImg& rgb_img);
    void buildFromGray(GrayImg& gray_img, int bit_depth);

private:
    void _load(const std::string& path);
    void _save(const std::string& path);
};