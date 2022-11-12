#include "BMPUtil.h"
#include "GeometricTransformation.h"

int main() {

    BMPImage original_img;
    original_img.load("../assets/lab4/in/lena.bmp");
    RGBImg  original_rgb_img = original_img.extractRGB();

    BMPImage img_after_translation;
    RGBImg rgb_img_after_translation = GeometricTransformation::translation(original_rgb_img, 10, 20);
    img_after_translation.buildFromRGB(rgb_img_after_translation);
    img_after_translation.save("../assets/lab4/out/translation.bmp");

    BMPImage img_after_rotation;
    RGBImg rgb_img_after_rotation = GeometricTransformation::rotation(original_rgb_img, 1);
    img_after_rotation.buildFromRGB(rgb_img_after_rotation);
    img_after_rotation.save("../assets/lab4/out/rotation.bmp");

    BMPImage img_after_scale;
    RGBImg rgb_img_after_scale = GeometricTransformation::scale(original_rgb_img, 1.5);
    img_after_scale.buildFromRGB(rgb_img_after_scale);
    img_after_scale.save("../assets/lab4/out/scale.bmp");
//
//    BMPImage img_after_histeq;
//    Histogram eq_hist = Histogram::buildEqual(256);
//    GrayImg gray_matrix_after_histeq = VisibilityEnhancement::fitHistogramForGray(gray_matrix_before_histeq, eq_hist);
//    img_after_histeq.buildFromGray(gray_matrix_after_histeq, 8);
//    img_after_histeq.save("../assets/lab3/out/after_histeq.bmp");

    return 0;
}