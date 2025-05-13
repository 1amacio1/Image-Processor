#include "dumper.h"
#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t file_type = 0x4D42;
    uint32_t file_size = 0;
    uint16_t reserved1 = 0;
    uint16_t reserved2 = 0;
    uint32_t offset_data = 54;
};

struct BMPInfoHeader {
    uint32_t size = 40;
    int32_t width = 0;
    int32_t height = 0;
    uint16_t planes = 1;
    uint16_t bit_count = 24;
    uint32_t compression = 0;
    uint32_t size_image = 0;
    int32_t x_pixels_per_meter = 0;
    int32_t y_pixels_per_meter = 0;
    uint32_t colors_used = 0;
    uint32_t colors_important = 0;
};
#pragma pack(pop)

void BMPDumper::SaveBMP(const Image& image, const std::string& filename) {
    const size_t height = image.HeightGetter();
    const size_t width = image.WidthGetter();
    if (height == 0 || width == 0) {
        throw std::runtime_error("Invalid image dimensions");
    }

    const size_t row_padding = (4 - (width * 3) % 4) % 4;
    const size_t row_size = width * 3 + row_padding;
    const uint32_t image_size = row_size * height;

    BMPFileHeader file_header;
    file_header.file_size = sizeof(file_header) + sizeof(BMPInfoHeader) + image_size;

    BMPInfoHeader info_header;
    info_header.width = static_cast<int32_t>(width);
    info_header.height = static_cast<int32_t>(height);
    info_header.size_image = image_size;

    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Failed to create file");
    }

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    std::vector<uint8_t> row_buffer(row_size, 0);

    for (size_t y = 0; y < height; ++y) {
        const size_t image_row = height - 1 - y;
        for (size_t x = 0; x < width; ++x) {
            const Color& color = image.ColorGetter(image_row, x);
            const size_t offset = x * 3;
            row_buffer[offset] = color.blue;
            row_buffer[offset + 1] = color.green;
            row_buffer[offset + 2] = color.red;
        }
        file.write(reinterpret_cast<const char*>(row_buffer.data()), static_cast<std::streamsize>(row_size));
    }
}
