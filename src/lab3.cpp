#include "BMPUtil.h"
#include "VisibilityEnhancement.h"

int main() {
    // logarithmic demo
    BMPImage img_before_logarithmic;
    img_before_logarithmic.load("../assets/lab3/in/before_logarithmic.bmp");
    RGBImg  rgb_matrix_before_logarithmic = img_before_logarithmic.extractRGB();

    BMPImage img_after_logarithmic;
    RGBImg rgb_matrix_after_logarithmic = VisibilityEnhancement::logarithmicForRGB(rgb_matrix_before_logarithmic);
    img_after_logarithmic.buildFromRGB(rgb_matrix_after_logarithmic);
    img_after_logarithmic.save("../assets/lab3/out/after_logarithmic.bmp");

    // histogram equalization demo
    BMPImage img_before_histeq;
    img_before_histeq.load("../assets/lab3/in/before_histeq.bmp");
    GrayImg gray_matrix_before_histeq = img_before_histeq.extractGray();

    BMPImage img_after_histeq;
    Histogram eq_hist = Histogram::buildEqual(256);
    GrayImg gray_matrix_after_histeq = VisibilityEnhancement::fitHistogramForGray(gray_matrix_before_histeq, eq_hist);
    img_after_histeq.buildFromGray(gray_matrix_after_histeq, 8);
    img_after_histeq.save("../assets/lab3/out/after_histeq.bmp");

    return 0;
}