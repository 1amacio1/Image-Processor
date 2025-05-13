#include "image.h"
#include <cstddef>
#include <stdexcept>
#include <utility>

Image::Image(size_t height, size_t width) : height_(height), width_(width) {
    data_.resize(height_);
    for (size_t i = 0; i < height_; ++i) {
        data_[i].resize(width_);
    }
}

Image::Image(const std::vector<std::vector<Color>>& data)
    : data_(data), height_(data.size()), width_(data.empty() ? 0 : data.front().size()) {
}

Image::Image(const Image& other) : data_(other.PixelsGetter()), height_(other.height_), width_(other.width_) {
}

void Image::CheckParamsOfPicture(size_t x, size_t y) const {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Coordinates are out of range");
    }
}

size_t Image::WidthGetter() const {
    return width_;
}

size_t Image::HeightGetter() const {
    return height_;
}

const std::vector<std::vector<Color>>& Image::PixelsGetter() const {
    return data_;
}

Color& Image::ColorGetter(size_t x, size_t y) {
    CheckParamsOfPicture(x, y);
    Color& col = data_[x][y];
    return col;
}

const Color& Image::ColorGetter(size_t x, size_t y) const {
    CheckParamsOfPicture(x, y);
    const Color& col = data_[x][y];
    return col;
}

void Image::ColorSetter(size_t x, size_t y, Color color) {
    CheckParamsOfPicture(x, y);
    data_[x][y] = color;
}
