#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include "Type.h"
#include "BMPUtil.h"

void BMPImage::load(const std::string &path) {
    try {
        _load(path);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

void BMPImage::_load(const std::string &path) {
    std::shared_ptr<FILE> file(fopen(path.c_str(), "rb"), [](FILE *p) { if (p) fclose(p); });
    if (!file.get())
        throw std::runtime_error("File not found");
    auto reader = file.get();

    // Read file header
    fread(&file_header.bfType, sizeof(file_header.bfType), 1, reader);
    fread(&file_header.bfSize, sizeof(file_header.bfSize), 1, reader);
    fread(&file_header.bfReservered1, sizeof(file_header.bfReservered1), 1, reader);
    fread(&file_header.bfReservered2, sizeof(file_header.bfReservered2), 1, reader);
    fread(&file_header.bfOffbits, sizeof(file_header.bfOffbits), 1, reader);
    if (file_header.bfType != 0x4d42)
        throw std::runtime_error("This is not a bmp file");

    // Read info header
    fread(&info_header.biSize, sizeof(info_header.biSize), 1, reader);
    fread(&info_header.biWidth, sizeof(info_header.biWidth), 1, reader);
    fread(&info_header.biHeight, sizeof(info_header.biHeight), 1, reader);
    fread(&info_header.biPlanes, sizeof(info_header.biPlanes), 1, reader);
    fread(&info_header.biBitCount, sizeof(info_header.biBitCount), 1, reader);
    fread(&info_header.biCompression, sizeof(info_header.biCompression), 1, reader);
    fread(&info_header.biSizeImage, sizeof(info_header.biSizeImage), 1, reader);
    fread(&info_header.biXPelsPerMeter, sizeof(info_header.biXPelsPerMeter), 1, reader);
    fread(&info_header.biYPelsPerMeter, sizeof(info_header.biYPelsPerMeter), 1, reader);
    fread(&info_header.biClrUsed, sizeof(info_header.biClrUsed), 1, reader);
    fread(&info_header.biClrImportant, sizeof(info_header.biClrImportant), 1, reader);
    if (info_header.biSize != 40)
        throw std::runtime_error("Unsupported info header format");

    // Read palette if exists
    if (info_header.biBitCount <= 8) {
        color_palette.resize(1 << info_header.biBitCount);
        fread(color_palette.data(), sizeof(PaletteItem), color_palette.size(), reader);
    } else if (info_header.biBitCount != 24)
        throw std::runtime_error("Unsupported bit depth");

    // Read pixel data, note that
    // 1. in 24bit bmp, pixel data is stored in BGR order
    // 2. Every row is forced to align to 4 bytes
    int row_bit_cnt = info_header.biWidth * info_header.biBitCount;
    int row_byte_cnt = (row_bit_cnt + 31) / 32 * 4;
    int byte_count = row_byte_cnt * info_header.biHeight;
    pixel_data.resize(byte_count);
    fread(pixel_data.data(), byte_count, 1, reader);
}

void BMPImage::save(const std::string &path) {
    try {
        _save(path);
    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        exit(-1);
    }
}

void BMPImage::_save(const std::string &path) {
    std::shared_ptr<FILE> file(fopen(path.c_str(), "wb"), [](FILE *p) { if (p) fclose(p); });
    if (!file.get())
        throw std::runtime_error("Create file failed");
    auto writer = file.get();

    // Write file header
    fwrite(&file_header.bfType, sizeof(file_header.bfType), 1, writer);
    fwrite(&file_header.bfSize, sizeof(file_header.bfSize), 1, writer);
    fwrite(&file_header.bfReservered1, sizeof(file_header.bfReservered1), 1, writer);
    fwrite(&file_header.bfReservered2, sizeof(file_header.bfReservered2), 1, writer);
    fwrite(&file_header.bfOffbits, sizeof(file_header.bfOffbits), 1, writer);

    // Write info header
    fwrite(&info_header.biSize, sizeof(info_header.biSize), 1, writer);
    fwrite(&info_header.biWidth, sizeof(info_header.biWidth), 1, writer);
    fwrite(&info_header.biHeight, sizeof(info_header.biHeight), 1, writer);
    fwrite(&info_header.biPlanes, sizeof(info_header.biPlanes), 1, writer);
    fwrite(&info_header.biBitCount, sizeof(info_header.biBitCount), 1, writer);
    fwrite(&info_header.biCompression, sizeof(info_header.biCompression), 1, writer);
    fwrite(&info_header.biSizeImage, sizeof(info_header.biSizeImage), 1, writer);
    fwrite(&info_header.biXPelsPerMeter, sizeof(info_header.biXPelsPerMeter), 1, writer);
    fwrite(&info_header.biYPelsPerMeter, sizeof(info_header.biYPelsPerMeter), 1, writer);
    fwrite(&info_header.biClrUsed, sizeof(info_header.biClrUsed), 1, writer);
    fwrite(&info_header.biClrImportant, sizeof(info_header.biClrImportant), 1, writer);

    // If palette exists, write palette
    if (info_header.biBitCount <= 8) {
        fwrite(color_palette.data(), sizeof(PaletteItem), color_palette.size(), writer);
    }

    // Write pixel data
    fwrite(pixel_data.data(), pixel_data.size(), 1, writer);
}

RGBImg BMPImage::extractRGB() {
    assert(info_header.biBitCount == 24);

    RGBImg rgb_img(info_header.biHeight, LineData(info_header.biWidth, PixelData(3, 0)));
    int row_bit_cnt = info_header.biWidth * info_header.biBitCount;
    int row_byte_cnt = (row_bit_cnt + 31) / 32 * 4;

    for (int i = 0; i < info_header.biHeight; i++) {
        for (int j = 0; j < info_header.biWidth; j++) {
            rgb_img[info_header.biHeight - i - 1][j][0] = pixel_data[row_byte_cnt * i + 3 * j + 2];
            rgb_img[info_header.biHeight - i - 1][j][1] = pixel_data[row_byte_cnt * i + 3 * j + 1];
            rgb_img[info_header.biHeight - i - 1][j][2] = pixel_data[row_byte_cnt * i + 3 * j + 0];
        }
    }

    return rgb_img;
}

GrayImg BMPImage::extractGray() {
    assert(info_header.biBitCount <= 8);
    for (PaletteItem &item: color_palette) {
        assert(item.B == item.G && item.G == item.R);
    }

    GrayImg gray_img(info_header.biHeight, GrayLine(info_header.biWidth, 0));
    int byte_offset = 0;
    int bit_offset = 0;
    for (int i = 0; i < info_header.biHeight; i++) {
        for (int j = 0; j < info_header.biWidth; j++) {
            uint8_t index = (pixel_data[byte_offset] << bit_offset) >> (8 - info_header.biBitCount);
            gray_img[info_header.biHeight - i - 1][j] = color_palette[index].B;

            bit_offset += info_header.biBitCount;
            if (bit_offset == 8) {
                bit_offset = 0;
                byte_offset += 1;
            }
        }

        // row align to 4 bytes
        if (byte_offset % 4 != 0 || bit_offset != 0) {
            byte_offset += 4 - byte_offset % 4;
            bit_offset = 0;
        }
    }

    return gray_img;
}

void BMPImage::buildFromRGB(RGBImg &rgb_img) {
    int height = rgb_img.size();
    int width = rgb_img[0].size();

    color_palette.clear();
    pixel_data.clear();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel_data.push_back(rgb_img[height - i - 1][j][2]);
            pixel_data.push_back(rgb_img[height - i - 1][j][1]);
            pixel_data.push_back(rgb_img[height - i - 1][j][0]);
        }

        // row align to 4 bytes
        while (pixel_data.size() % 4 != 0)
            pixel_data.push_back(0);
    }

    file_header.bfType = 0x4d42;
    file_header.bfSize = 0x36 + pixel_data.size();
    file_header.bfReservered1 = 0;
    file_header.bfReservered2 = 0;
    file_header.bfOffbits = 0x36;

    info_header.biSize = 0x28;
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = 24;
    info_header.biCompression = 0;
    info_header.biSizeImage = 0;
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;
}

void BMPImage::buildFromGray(GrayImg &gray_img, int bit_depth) {
    int height = gray_img.size();
    int width = gray_img[0].size();

    color_palette.clear();
    int color_num = 1 << bit_depth;
    for (int i = 0; i < color_num; i++) {
        uint8_t color = i * 255 / (color_num - 1);
        color_palette.push_back(PaletteItem{(uint8_t) color, (uint8_t) color, (uint8_t) color, 0});
    }

    pixel_data.clear();
    uint8_t buf = 0;
    int buf_offset = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = gray_img[height - i - 1][j] / (1 << (8 - bit_depth));
            buf += index << (8 - buf_offset - bit_depth);
            buf_offset += bit_depth;

            if (buf_offset == 8) {
                pixel_data.push_back(buf);
                buf = 0;
                buf_offset = 0;
            }
        }
        while (pixel_data.size() % 4 != 0)
            pixel_data.push_back(0);
    }

    file_header.bfType = 0x4d42;
    file_header.bfSize = 0x36 + 4 * 256 + pixel_data.size();
    file_header.bfReservered1 = 0;
    file_header.bfReservered2 = 0;
    file_header.bfOffbits = 0x36 + 4 * (1 << bit_depth);

    info_header.biSize = 0x28;
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = bit_depth;
    info_header.biCompression = 0;
    info_header.biSizeImage = 0;
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;
}