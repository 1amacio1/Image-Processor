#include "crop_filter.h"
#include <algorithm>

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

Image CropFilter::Apply(const Image& image) const {
    const size_t current_width = image.WidthGetter();
    const size_t current_height = image.HeightGetter();

    const size_t new_width = std::min(width_, current_width);
    const size_t new_height = std::min(height_, current_height);

    Image result(new_height, new_width);

    for (size_t y = 0; y < new_height; ++y) {
        for (size_t x = 0; x < new_width; ++x) {
            result.ColorSetter(y, x, image.ColorGetter(y, x));
        }
    }

    return result;
}
