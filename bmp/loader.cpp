#include "loader.h"
#include <cstddef>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct BMPInfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bit_count;
    uint32_t compression;
    uint32_t size_image;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
};
#pragma pack(pop)

const int FILE_SIZE = 24;
const auto FILE_TYPE = 0x4D42;
Image BMPLoader::LoadBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file");
    }

    BMPFileHeader file_header;
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (file_header.file_type != FILE_TYPE) {
        throw std::runtime_error("Not a BMP file");
    }

    BMPInfoHeader info_header;
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (info_header.bit_count != FILE_SIZE) {
        throw std::runtime_error("Only 24-bit BMP is supported");
    }

    const size_t width = info_header.width;
    const size_t height = std::abs(info_header.height);
    const bool is_top_down = info_header.height < 0;

    if (width == 0 || height == 0) {
        throw std::runtime_error("Invalid image dimensions");
    }

    file.seekg(file_header.offset_data, std::ios::beg);
    const size_t row_padding = (4 - (width * 3) % 4) % 4;

    Image image(height, width);
    std::vector<uint8_t> buffer(width * 3 + row_padding);

    for (size_t row_idx = 0; row_idx < height; ++row_idx) {
        file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(buffer.size()));
        const size_t image_row = is_top_down ? row_idx : height - 1 - row_idx;

        for (size_t col = 0; col < width; ++col) {
            const size_t offset = col * 3;
            image.ColorSetter(image_row, col, Color(buffer[offset], buffer[offset + 1], buffer[offset + 2]));
        }
    }

    return image;
}
