#include "BMPUtil.h"

int main() {
    BMPImage img;
    img.load("../assets/lab1/in/lena.bmp");
    RGBImg rgb_img = img.extractRGB();

    GrayImg gray_img = reserveGray(rgb_img);
    BMPImage gray_bmp;
    gray_bmp.buildFromGray(gray_img);
    gray_bmp.save("../assets/lab1/out/gray.bmp");

    RGBImg rgb_img2 = changeChannelY(rgb_img);
    BMPImage img2;
    img2.buildFromRGB(rgb_img2);
    img2.save("../assets/lab1/out/new.bmp");

    return 0;
}