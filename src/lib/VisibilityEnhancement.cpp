#include <cmath>
#include <unordered_map>

#include "VisibilityEnhancement.h"

Histogram Histogram::buildEqual(int color_num) {
    Histogram hist;
    hist.color_num = color_num;
    hist.hist = std::vector<double>(color_num, 1.0 / color_num);
    return hist;
}

Histogram Histogram::buildByGray(GrayImg gray_img) {
    Histogram hist;
    hist.color_num = 256;
    hist.hist = std::vector<double>(256, 0);

    int height = gray_img.size(), width = gray_img[0].size();
    int pixel_num = height * width;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            hist.hist[gray_img[i][j]] += 1.0 / pixel_num;
        }
    }

    return hist;
}

RGBImg VisibilityEnhancement::logarithmicForRGB(RGBImg &rgb_img) {
    uint8_t r_max = 0, g_max = 0, b_max = 0;
    int height = rgb_img.size(), width = rgb_img[0].size();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            r_max = std::max(r_max, rgb_img[i][j][0]);
            g_max = std::max(g_max, rgb_img[i][j][1]);
            b_max = std::max(b_max, rgb_img[i][j][2]);
        }
    }

    RGBImg res(height, LineData(width, PixelData(3)));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            res[i][j][0] = round(log(rgb_img[i][j][0]) / log(r_max) * 255);
            res[i][j][1] = round(log(rgb_img[i][j][1]) / log(g_max) * 255);
            res[i][j][2] = round(log(rgb_img[i][j][2]) / log(b_max) * 255);
        }
    }

    return res;
}

GrayImg VisibilityEnhancement::logarithmicForGray(GrayImg &gray_img) {
    uint8_t gray_max = 0;
    int height = gray_img.size(), width = gray_img[0].size();

    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            gray_max = std::max(gray_max, gray_img[i][j]);
        }
    }

    GrayImg res(height, GrayLine(width, 0));
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            res[i][j] = round(log(gray_img[i][j]) / log(gray_max) * 255);
        }
    }

    return res;
}

GrayImg VisibilityEnhancement::fitHistogramForGray(GrayImg &gray_img, Histogram &target_hist) {
    Histogram source_hist = Histogram::buildByGray(gray_img);
    std::unordered_map<uint8_t, uint8_t> map;

    double source_ratio = 0, target_ratio = target_hist.hist[0];
    int source_idx = 0, target_idx = 1;

    // construct color map
    while (target_idx < 256 && source_idx < 256) {
        while (source_idx < 256 && source_ratio <= target_ratio) {
            source_ratio += source_hist.hist[source_idx];
            source_idx += 1;
            map[source_idx - 1] = target_idx - 1;
        }

        while (target_idx < 256 && target_ratio < source_ratio &&
               target_ratio + target_hist.hist[target_idx] < source_ratio) {
            target_ratio += target_hist.hist[target_idx];
            target_idx += 1;
        }
        if (fabs(target_ratio - source_ratio) < fabs(target_ratio + target_hist.hist[target_idx] - source_ratio)) {
            map[source_idx - 1] = target_idx - 1;
            target_ratio += target_hist.hist[target_idx];
            target_idx += 1;
        } else {
            target_ratio += target_hist.hist[target_idx];
            target_idx += 1;
            map[source_idx - 1] = target_idx - 1;
        }
    }

    int height = gray_img.size(), width = gray_img[0].size();
    GrayImg after_fit(height, GrayLine(width, 0));
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            after_fit[i][j] = map[gray_img[i][j]];
        }
    }

    return after_fit;
}
