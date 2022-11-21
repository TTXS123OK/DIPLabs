#include "BMPUtil.h"
#include "Convolution.h"

int main() {

    BMPImage original_img;
    original_img.load("../assets/lab5/in/lena.bmp");
    RGBImg  original_rgb_img = original_img.extractRGB();

    BMPImage img_after_mean_filtering;
    RGBImg rgb_img_mean_filtering = Convolution::meanFiltering(original_rgb_img);
    img_after_mean_filtering.buildFromRGB(rgb_img_mean_filtering);
    img_after_mean_filtering.save("../assets/lab5/out/mean_filtering.bmp");

    BMPImage img_after_laplacian_enhance;
    RGBImg rgb_img_after_laplacian_enhance = Convolution::LaplacianEnhance(original_rgb_img);
    img_after_laplacian_enhance.buildFromRGB(rgb_img_after_laplacian_enhance);
    img_after_laplacian_enhance.save("../assets/lab5/out/laplacian_enhance.bmp");

    return 0;
}