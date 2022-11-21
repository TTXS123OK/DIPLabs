#include "Convolution.h"

RGBImg Convolution::meanFiltering(RGBImg &img) {
    int height = img.size();
    int width = img.size();

    RGBImg res(height, LineData(width, PixelData(3, 0)));
    for (int i=1; i<height-1; i++) {
        for (int j=1; j<width-1; j++) {
            for (int channel = 0; channel < 3; channel++) {
                for (int offset_x = -1; offset_x <= 1; offset_x++) {
                    for (int offset_y = -1; offset_y <= 1; offset_y++) {
                        res[i][j][channel] += 1.0 / 9 * img[i + offset_x][j + offset_y][channel];
                    }
                }
            }
        }
    }

    return res;
}

RGBImg Convolution::LaplacianEnhance(RGBImg &img) {
    int height = img.size();
    int width = img.size();

    RGBImg res(height, LineData(width, PixelData(3, 0)));
    for (int i=1; i<height-1; i++) {
        for (int j=1; j<width-1; j++) {
            for (int channel = 0; channel < 3; channel++) {
                int delta = 9 * img[i][j][channel];
                for (int offset_x = -1; offset_x <= 1; offset_x++) {
                    for (int offset_y = -1; offset_y <= 1; offset_y++) {
                        delta -= img[i + offset_x][j + offset_y][channel];
                    }
                }
                if (delta < 0) {
                    delta = 0;
                }
                res[i][j][channel] = std::min(img[i][j][channel] + delta, UINT8_MAX);
            }
        }
    }

    return res;
}