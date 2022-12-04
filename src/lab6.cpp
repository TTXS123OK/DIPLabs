#include "BMPUtil.h"
#include "Convolution.h"

#include <sstream>
#include <iostream>

int main() {

    BMPImage original_img;
    original_img.load("../assets/lab6/in/noise.bmp");
    RGBImg  original_rgb_img = original_img.extractRGB();

    std::vector<int> window_sizes = {5, 15, 25};
    std::vector<int> sigma_d_vec = {30, 75, 120};
    std::vector<int> sigma_r_vec = {30, 75, 120};
    for (int window_size : window_sizes) {
        for (double sigma_d:sigma_d_vec) {
            for (double sigma_r : sigma_r_vec) {
                std::ostringstream file_name;
                file_name << "../assets/lab6/out/denoise_" << window_size << "_" << sigma_d << "_" << sigma_r << ".bmp";

                BMPImage img_after_bilateral_filter;
                RGBImg rgb_img_after_bilateral_filter = Convolution::bilateralFiltering(original_rgb_img, window_size, sigma_d, sigma_r);
                img_after_bilateral_filter.buildFromRGB(rgb_img_after_bilateral_filter);
                img_after_bilateral_filter.save(file_name.str());

                std::cout << file_name.str() << " generated" << std::endl;
            }
        }
    }

    return 0;
}