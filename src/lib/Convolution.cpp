#include "Convolution.h"

#include <cassert>
#include <cmath>

RGBImg Convolution::meanFiltering(RGBImg &img) {
    int height = img.size();
    int width = img.size();

    RGBImg res(height, LineData(width, PixelData(3, 0)));
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
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
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
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

RGBImg Convolution::bilateralFiltering(RGBImg &img, int window_size, double sigma_d, double sigma_r) {
    int height = img.size();
    int width = img.size();

    assert(window_size % 2 == 1);
    int offset_limit = (window_size - 1) / 2;

    RGBImg res(height, LineData(width, PixelData(3, 0)));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double sum_r = 0, sum_g = 0, sum_b = 0, total_weight = 0;
            for (int k = -offset_limit; k <= offset_limit; k++) {
                for (int l = -offset_limit; l <= offset_limit; l++) {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width) {
                        continue;
                    }

                    double dist = pow(k, 2) + pow(l, 2);
                    double residue =
                            pow(img[i + k][j + l][0] - img[i][j][0], 2)
                            + pow(img[i + k][j + l][1] - img[i][j][1], 2)
                            + pow(img[i + k][j + l][2] - img[i][j][2], 2);
                    double weight = exp(-0.5 * ((dist / pow(sigma_d, 2)) + residue / pow(sigma_r, 2)));
                    total_weight += weight;
                    sum_r += img[i + k][j + l][0] * weight;
                    sum_g += img[i + k][j + l][1] * weight;
                    sum_b += img[i + k][j + l][2] * weight;
                }
            }
            res[i][j][0] = (int) (sum_r / total_weight);
            res[i][j][1] = (int) (sum_g / total_weight);
            res[i][j][2] = (int) (sum_b / total_weight);
        }
    }

    return res;
}