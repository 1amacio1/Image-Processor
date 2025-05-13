#include "edge_filter.h"
#include "grayscale.h"
#include <algorithm>

EdgeDetectionFilter::EdgeDetectionFilter(double threshold) : threshold_(threshold) {
}

const int MAX_COLOR_VAL = 255;

Image EdgeDetectionFilter::Apply(const Image& image) const {
    Image gray_image = GrayscaleFilter().Apply(image);

    const std::vector<std::vector<float>> kernel = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    const int radius = 1;

    Image result(gray_image.HeightGetter(), gray_image.WidthGetter());

    for (size_t x = 0; x < gray_image.HeightGetter(); ++x) {
        for (size_t y = 0; y < gray_image.WidthGetter(); ++y) {
            float sum = 0.0f;

            for (int kx = -radius; kx <= radius; ++kx) {
                for (int ky = -radius; ky <= radius; ++ky) {
                    int yi = std::clamp(static_cast<int>(y) + ky, 0, static_cast<int>(gray_image.WidthGetter()) - 1);
                    int xi = std::clamp(static_cast<int>(x) + kx, 0, static_cast<int>(gray_image.HeightGetter()) - 1);
                    sum += static_cast<float>(gray_image.ColorGetter(xi, yi).red) * kernel[kx + radius][ky + radius];
                }
            }

            uint8_t value = (sum > threshold_) ? MAX_COLOR_VAL : 0;

            result.ColorSetter(x, y, Color(value, value, value));
        }
    }

    return result;
}
