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

    BMPImage img_after_shear;
    RGBImg rgb_img_after_shear = GeometricTransformation::shear(original_rgb_img, 0.3, 0.5);
    img_after_shear.buildFromRGB(rgb_img_after_shear);
    img_after_shear.save("../assets/lab4/out/shear.bmp");

    BMPImage img_after_mirror_by_x;
    RGBImg rgb_img_after_mirror_by_x = GeometricTransformation::mirrorByXAxis(original_rgb_img);
    img_after_mirror_by_x.buildFromRGB(rgb_img_after_mirror_by_x);
    img_after_mirror_by_x.save("../assets/lab4/out/mirror_by_x.bmp");

    BMPImage img_after_mirror_by_y;
    RGBImg rgb_img_after_mirror_by_y = GeometricTransformation::mirrorByYAxis(original_rgb_img);
    img_after_mirror_by_y.buildFromRGB(rgb_img_after_mirror_by_y);
    img_after_mirror_by_y.save("../assets/lab4/out/mirror_by_y.bmp");

    return 0;
}