#include <iostream>
#include <fstream>
#include <memory>
#include "BMPUtil.h"

void BMPImage::load(const std::string& path) {
    try {
        _load(path);
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
}

void BMPImage::_load(const std::string& path) {
    std::shared_ptr<FILE> file(fopen(path.c_str(), "rb"), [](FILE* p) { if (p) fclose(p); });
    if (!file.get())
        throw "File not found";
    auto reader = file.get();

    // Read file header
    fread(&file_header.bfType, sizeof(file_header.bfType), 1, reader);
    fread(&file_header.bfSize, sizeof(file_header.bfSize), 1, reader);
    fread(&file_header.bfReservered1, sizeof(file_header.bfReservered1), 1, reader);
    fread(&file_header.bfReservered2, sizeof(file_header.bfReservered2), 1, reader);
    fread(&file_header.bfOffbits, sizeof(file_header.bfOffbits), 1, reader);
    if (file_header.bfType != 0x4d42)
        throw "This is not a bmp file";

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
        throw "Unsupported info header format";

    // Read palette if exists
    if (info_header.biBitCount == 8) {
        color_palette.resize(1 << info_header.biBitCount);
        fread(color_palette.data(), sizeof(PaletteItem), color_palette.size(), reader);
    }
    else if (info_header.biBitCount != 24)
        throw "Unsupported bit depth";

    // Read pixel data, note that
    // 1. in 24bit bmp, pixel data is stored in BGR order
    // 2. Every row is forced to align to 4 bytes
    int line_bytes = info_header.biWidth * info_header.biBitCount / 8;
    int line_bytes_after_align = (line_bytes + 3) / 4 * 4;
    int byte_count = line_bytes_after_align * info_header.biHeight;
    pixel_data.resize(byte_count);
    fread(pixel_data.data(), byte_count, 1, reader);
}

void BMPImage::saveInfoFile(const std::string& path) {
    std::ofstream writer(path, std::ios::out);
    writer << "Width: " << info_header.biWidth << ", Height: " << info_header.biHeight << std::endl;
    int cnt = 0;
    for (auto pixel : pixel_data) {
        if (cnt == 0)
            writer << std::endl;
        writer << (int)pixel << ' ';
        cnt = (cnt + 1) % 3;
    }
    writer.close();
}

void BMPImage::save(const std::string& path) {
    try {
        _save(path);
    }
    catch (const char* msg) {
        std::cout << msg << std::endl;
    }
}

void BMPImage::_save(const std::string& path) {
    std::shared_ptr<FILE> file(fopen(path.c_str(), "wb"), [](FILE* p) { if (p) fclose(p); });
    if (!file.get())
        throw "Create file failed";
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
    if (info_header.biBitCount == 8) {
        fwrite(color_palette.data(), sizeof(PaletteItem), color_palette.size(), writer);
    }

    // Write pixel data
    fwrite(pixel_data.data(), pixel_data.size(), 1, writer);
    return;
}

RGBImg BMPImage::extractRGB() {
    RGBImg rgb_img;
    int line_bytes = info_header.biWidth * info_header.biBitCount / 8;
    int line_bytes_after_align = (line_bytes + 3) / 4 * 4;

    for (int i = 0; i < info_header.biHeight; i++) {
        LineData rgb_line;
        int col = 0;
        for (int j = 0; j < info_header.biWidth; j++) {
            PixelData pixel;
            pixel.push_back(pixel_data[line_bytes_after_align * i + col * 3 + 2]);
            pixel.push_back(pixel_data[line_bytes_after_align * i + col * 3 + 1]);
            pixel.push_back(pixel_data[line_bytes_after_align * i + col * 3 + 0]);
            rgb_line.push_back(pixel);
            col += 1;
        }
        rgb_img.push_back(rgb_line);
    }

    return rgb_img;
}

void BMPImage::buildFromRGB(RGBImg& rgb_img) {
    int height = rgb_img.size();
    int width = rgb_img[0].size();

    color_palette.clear();
    pixel_data.clear();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel_data.push_back(rgb_img[i][j][2]);
            pixel_data.push_back(rgb_img[i][j][1]);
            pixel_data.push_back(rgb_img[i][j][0]);
        }
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

void BMPImage::buildFromGray(GrayImg& gray_img) {
    int height = gray_img.size();
    int width = gray_img[0].size();

    color_palette.clear();
    for (int i = 0; i < 256; i++) {
        color_palette.push_back(PaletteItem{ (uint8_t)i, (uint8_t)i, (uint8_t)i, 0 });
    }

    pixel_data.clear();
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            pixel_data.push_back(gray_img[i][j]);
        }
        while (pixel_data.size() % 4 != 0)
            pixel_data.push_back(0);
    }

    file_header.bfType = 0x4d42;
    file_header.bfSize = 0x36 + 4 * 256 + pixel_data.size();
    file_header.bfReservered1 = 0;
    file_header.bfReservered2 = 0;
    file_header.bfOffbits = 0x36 + 4 * 256;

    info_header.biSize = 0x28;
    info_header.biWidth = width;
    info_header.biHeight = height;
    info_header.biPlanes = 1;
    info_header.biBitCount = 8;
    info_header.biCompression = 0;
    info_header.biSizeImage = 0;
    info_header.biXPelsPerMeter = 0;
    info_header.biYPelsPerMeter = 0;
    info_header.biClrUsed = 0;
    info_header.biClrImportant = 0;
}