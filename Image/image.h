#include <cstdint>
#include <vector>
#include <cstddef>

#include "color.h"

#pragma once
class Image {
public:
    Image() = default;
    Image(size_t height, size_t width);
    explicit Image(const std::vector<std::vector<Color>>& data);
    Image(const Image& other);
    ~Image() = default;

    size_t WidthGetter() const;
    size_t HeightGetter() const;
    const std::vector<std::vector<Color>>& PixelsGetter() const;

    Color& ColorGetter(size_t x, size_t y);
    const Color& ColorGetter(size_t x, size_t y) const;

    void ColorSetter(size_t x, size_t y, Color color);

private:
    void CheckParamsOfPicture(size_t x, size_t y) const;
    std::vector<std::vector<Color>> data_;
    size_t height_ = 0;
    size_t width_ = 0;
};
