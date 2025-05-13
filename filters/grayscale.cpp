#include "grayscale.h"
#include <algorithm>

const int MAX_COLOR_VAL = 255;
const double RED_TO_GRAY = 0.299;
const double GREEN_TO_GRAY = 0.587;
const double BLUE_TO_GRAY = 0.114;

Image GrayscaleFilter::Apply(const Image& image) const {
    Image result(image.HeightGetter(), image.WidthGetter());

    for (size_t x = 0; x < image.HeightGetter(); ++x) {
        for (size_t y = 0; y < image.WidthGetter(); ++y) {
            Color original = image.ColorGetter(x, y);
            double red = original.red / (MAX_COLOR_VAL * 1.0);
            double green = original.green / (MAX_COLOR_VAL * 1.0);
            double blue = original.blue / (MAX_COLOR_VAL * 1.0);
            double gray_value = RED_TO_GRAY * red + GREEN_TO_GRAY * green + BLUE_TO_GRAY * blue;
            gray_value = std::clamp(gray_value, 0.0, 1.0);
            uint8_t gray = static_cast<uint8_t>(gray_value * MAX_COLOR_VAL);
            result.ColorSetter(x, y, Color(gray, gray, gray));
        }
    }

    return result;
}
