#include "mosaic.h"
#include <algorithm>
#include <cstddef>

MosaicFilter::MosaicFilter(size_t block_size) : block_size_(std::max(static_cast<size_t>(1), block_size)) {
}

Image MosaicFilter::Apply(const Image& image) const {
    Image result(image);
    const size_t height = result.HeightGetter();
    const size_t width = result.WidthGetter();

    for (size_t x_start = 0; x_start < height; x_start += block_size_) {
        for (size_t y_start = 0; y_start < width; y_start += block_size_) {
            size_t x_end = std::min(x_start + block_size_, height);
            size_t y_end = std::min(y_start + block_size_, width);

            uint32_t total_red = 0;
            uint32_t total_green = 0;
            uint32_t total_blue = 0;
            size_t pixel_count = 0;

            for (size_t x = x_start; x < x_end; ++x) {
                for (size_t y = y_start; y < y_end; ++y) {
                    const Color& col = image.ColorGetter(x, y);
                    total_red += col.red;
                    total_green += col.green;
                    total_blue += col.blue;
                    ++pixel_count;
                }
            }

            uint8_t avg_red = static_cast<uint8_t>(total_red / pixel_count);
            uint8_t avg_green = static_cast<uint8_t>(total_green / pixel_count);
            uint8_t avg_blue = static_cast<uint8_t>(total_blue / pixel_count);

            for (size_t x = x_start; x < x_end; ++x) {
                for (size_t y = y_start; y < y_end; ++y) {
                    result.ColorSetter(x, y, Color(avg_blue, avg_green, avg_red));
                }
            }
        }
    }
    return result;
}
