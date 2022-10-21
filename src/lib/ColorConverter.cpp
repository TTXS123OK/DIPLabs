#include "ColorConverter.h"

YUVImg ColorConverter::RGB2YUV(RGBImg &rgb_img) {
    int height = rgb_img.size();
    int width = rgb_img[0].size();

    YUVImg yuv_img(height, LineData(width, PixelData(3)));
    for (int i = 0; i < height; i++) {
        std::vector<std::vector<int>> line_data;
        for (int j = 0; j < width; j++) {
            int r = rgb_img[i][j][0];
            int g = rgb_img[i][j][1];
            int b = rgb_img[i][j][2];
            yuv_img[i][j][0] = 0.257 * r + 0.504 * g + 0.098 * b + 16;   // Y
            yuv_img[i][j][1] = -0.148 * r - 0.291 * g + 0.439 * b + 128; // U
            yuv_img[i][j][2] = 0.439 * r - 0.368 * g - 0.071 * b + 128;  // V
        }
    }
    return yuv_img;
}

RGBImg ColorConverter::YUV2RGB(YUVImg &yuv_img) {
    int height = yuv_img.size();
    int width = yuv_img[0].size();

    RGBImg rgb_img(height, LineData(width, PixelData(3)));
    for (int i = 0; i < height; i++) {
        std::vector<std::vector<int>> line_data;
        for (int j = 0; j < width; j++) {
            int y_ = yuv_img[i][j][0] - 16;
            int u_ = yuv_img[i][j][1] - 128;
            int v_ = yuv_img[i][j][2] - 128;
            rgb_img[i][j][0] = 1.164 * y_ + 1.596 * v_;              // R
            rgb_img[i][j][1] = 1.164 * y_ - 0.392 * u_ - 0.813 * v_; // G
            rgb_img[i][j][2] = 1.164 * y_ + 2.017 * u_;              // B
        }
    }
    return rgb_img;
}

BinaryImg ColorConverter::Gray2Binary(GrayImg &gray_img) {
    int height = gray_img.size();
    int width = gray_img[0].size();

    BinaryImg binary_img(height, BinaryLine(width, 0));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (gray_img[i][j] < 128)
                binary_img[i][j] = 0;
            else
                binary_img[i][j] = 0xff;
        }
    }

    return binary_img;
}

GrayImg ColorConverter::reserveGray(RGBImg &rgb_img) {
    YUVImg yuv_img = RGB2YUV(rgb_img);

    int height = rgb_img.size();
    int width = rgb_img[0].size();

    // Method1: gray=0.299red+0.587green+0.114blue
    // Method2: Use Y to represent Gray
    // Y ranges 16~235
    // Y to Gray: (Y-16) * 256 / 220
    GrayImg gray_img;
    for (int i = 0; i < height; i++) {
        GrayLine gray_line;
        for (int j = 0; j < width; j++) {
            gray_line.push_back((yuv_img[i][j][0] - 16) * 256 / 220);
        }
        gray_img.push_back(gray_line);
    }

    return gray_img;
}

RGBImg ColorConverter::changeChannelY(RGBImg &rgb_img) {
    YUVImg yuv_img = RGB2YUV(rgb_img);
    int height = yuv_img.size();
    int width = yuv_img[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            yuv_img[i][j][0] *= 1.1;
            if (yuv_img[i][j][0] > 235)
                yuv_img[i][j][0] = 235;
        }
    }
    return YUV2RGB(yuv_img);
}