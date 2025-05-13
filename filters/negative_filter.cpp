#include "negative_filter.h"

const int MAX_COLOR_VAL = 255;

Image NegativeFilter::Apply(const Image& image) const {
    Image result(image.HeightGetter(), image.WidthGetter());

    for (size_t x = 0; x < image.HeightGetter(); ++x) {
        for (size_t y = 0; y < image.WidthGetter(); ++y) {
            Color original = image.ColorGetter(x, y);
            uint8_t red = MAX_COLOR_VAL - original.red;
            uint8_t green = MAX_COLOR_VAL - original.green;
            uint8_t blue = MAX_COLOR_VAL - original.blue;
            result.ColorSetter(x, y, Color(blue, green, red));
        }
    }

    return result;
}
