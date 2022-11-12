#include <cmath>
#include "GeometricTransformation.h"

RGBImg GeometricTransformation::translation(RGBImg &img, int delta_x, int delta_y) {
    int original_h = img.size();
    int original_w = img[0].size();

    int new_h = original_h + abs(delta_x);
    int new_w = original_w + abs(delta_y);

    int x_offset = delta_x > 0 ? delta_x : 0;
    int y_offset = delta_y > 0 ? delta_y : 0;

    RGBImg res(new_h, LineData(new_w, PixelData(3, 128)));
    for (int i = 0; i < original_h; i++) {
        for (int j = 0; j < original_w; j++) {
            res[i + x_offset][j + y_offset][0] = img[i][j][0];
            res[i + x_offset][j + y_offset][1] = img[i][j][1];
            res[i + x_offset][j + y_offset][2] = img[i][j][2];
        }
    }

    return res;
}

RGBImg GeometricTransformation::rotation(RGBImg &img, double angle) {
    int original_h = img.size();
    int original_w = img[0].size();

    int point0_x = 0, point0_y = 0; // before rotate
    int point1_x = 0, point1_y = original_h - 1;
    int point2_x = original_w - 1, point2_y = original_h - 1;
    int point3_x = original_w - 1, point3_y = 0;

    int point0_x_ = cos(angle) * point0_x - sin(angle) * point0_y; // after rotate
    int point0_y_ = sin(angle) * point0_x + cos(angle) * point0_y;
    int point1_x_ = cos(angle) * point1_x - sin(angle) * point1_y;
    int point1_y_ = sin(angle) * point1_x + cos(angle) * point1_y;
    int point2_x_ = cos(angle) * point2_x - sin(angle) * point2_y;
    int point2_y_ = sin(angle) * point2_x + cos(angle) * point2_y;
    int point3_x_ = cos(angle) * point3_x - sin(angle) * point3_y;
    int point3_y_ = sin(angle) * point3_x + cos(angle) * point3_y;

    auto max4 = [](int a, int b, int c, int d) {
        return (std::max(a, std::max(b, std::max(c, d))));
    };

    auto min4 = [](int a, int b, int c, int d) {
        return (std::min(a, std::min(b, std::min(c, d))));
    };

    int max_x = max4(point0_x_, point1_x_, point2_x_, point3_x_);
    int min_x = min4(point0_x_, point1_x_, point2_x_, point3_x_);
    int max_y = max4(point0_y_, point1_y_, point2_y_, point3_y_);
    int min_y = min4(point0_y_, point1_y_, point2_y_, point3_y_);

    int new_h = max_x - min_x + 1;
    int new_w = max_y - min_y + 1;

    int x_offset = abs(min_x);
    int y_offset = abs(min_y);

    RGBImg res(new_h, LineData(new_w, PixelData(3, 128)));
    for (int i = 0; i < original_h; i++) {
        for (int j = 0; j < original_w; j++) {
            int i_ = x_offset + cos(angle) * i - sin(angle) * j;
            int j_ = y_offset + sin(angle) * i + cos(angle) * j;
            res[i_][j_][0] = img[i][j][0];
            res[i_][j_][1] = img[i][j][1];
            res[i_][j_][2] = img[i][j][2];
        }
    }

    return res;
}

RGBImg GeometricTransformation::scale(RGBImg &img, double ratio) {
    int height = img.size();
    int width = img[0].size();
    int new_h = height * ratio;
    int new_w = width * ratio;

    RGBImg res(new_h, LineData(new_w, PixelData(3, 128)));
    for (int i = 0; i < new_h; i++) {
        for (int j = 0; j < new_w; j++) {
            res[i][j][0] = img[(int) (i / ratio)][(int) (j / ratio)][0];
            res[i][j][1] = img[(int) (i / ratio)][(int) (j / ratio)][1];
            res[i][j][2] = img[(int) (i / ratio)][(int) (j / ratio)][2];
        }
    }

    return res;
}