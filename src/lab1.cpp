#include "BMPUtil.h"
#include "ColorConverter.h"

int main() {
    BMPImage img;
    img.load("../assets/lab1/in/lena.bmp");
    RGBImg rgb_img = img.extractRGB();

    GrayImg gray_img = ColorConverter::reserveGray(rgb_img);
    BMPImage gray_bmp;
    gray_bmp.buildFromGray(gray_img, 8);
    gray_bmp.save("../assets/lab1/out/lena_gray.bmp");

    BMPImage binary_bmp;
    binary_bmp.buildFromGray(gray_img, 1);
    binary_bmp.save("../assets/lab1/out/lena_binary.bmp");

    RGBImg rgb_img2 = ColorConverter::changeChannelY(rgb_img);
    BMPImage img2;
    img2.buildFromRGB(rgb_img2);
    img2.save("../assets/lab1/out/lena_convertY.bmp");

    return 0;
}