#include "BMPUtil.h"
#include "ColorConverter.h"
#include "MorphologicalOperation.h"

int main() {
    BMPImage img;
    img.load("../assets/lab2/in/origin.bmp");
    BinaryImg binary_img = img.extractGray();

    BinaryTemplate temp = {
            { 0, 1, 1, 1, 0 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 1, 1, 1, 1, 1 },
            { 0, 1, 1, 1, 0 },
    };

    BMPImage erosion_img;
    BinaryImg after_erosion = MorphologicalOperation::erosion(binary_img, temp);
    erosion_img.buildFromGray(after_erosion, 1);
    erosion_img.save("../assets/lab2/out/after_erosion.bmp");

    BMPImage dilation_img;
    BinaryImg after_dilation = MorphologicalOperation::dilation(binary_img, temp);
    dilation_img.buildFromGray(after_dilation, 1);
    dilation_img.save("../assets/lab2/out/after_dilation.bmp");

    BMPImage open_img;
    BinaryImg after_open = MorphologicalOperation::open(binary_img, temp);
    open_img.buildFromGray(after_open, 1);
    open_img.save("../assets/lab2/out/after_open.bmp");

    BMPImage close_img;
    BinaryImg after_close = MorphologicalOperation::close(binary_img, temp);
    close_img.buildFromGray(after_close, 1);
    close_img.save("../assets/lab2/out/after_close.bmp");


    // border detection
    BMPImage img2;
    img2.load("../assets/lab2/in/soldier.bmp");
    GrayImg gray_img2 = img2.extractGray();
    BinaryImg binary_img2 = ColorConverter::Gray2Binary(gray_img2);

    BinaryTemplate temp2 = {
            {0, 1, 0},
            {1, 1, 1},
            {0, 1, 0},
    };

    BinaryImg img2_erosion = MorphologicalOperation::erosion(binary_img2, temp); // use temp2 to get thinner lines
    BinaryImg border = MorphologicalOperation::diff(binary_img2, img2_erosion);
    BMPImage border_img;
    border_img.buildFromGray(border, 1);
    border_img.save("../assets/lab2/out/soldier_border.bmp");

    return 0;
}