#include "sharp.h"
#include <algorithm>

const int MAX_COLOR_VAL = 255;

Image SharpeningFilter::Apply(const Image& image) const {
    Image result(image.HeightGetter(), image.WidthGetter());

    const std::vector<std::vector<double>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    int kernel_size = 3;
    int center = kernel_size / 2;

    for (size_t x = 0; x < image.HeightGetter(); ++x) {
        for (size_t y = 0; y < image.WidthGetter(); ++y) {
            double red_sum = 0.0;
            double green_sum = 0.0;
            double blue_sum = 0.0;

            for (int i = -center; i <= center; ++i) {
                for (int j = -center; j <= center; ++j) {
                    int current_x = static_cast<int>(x) + i;
                    int current_y = static_cast<int>(y) + j;

                    current_x = std::max(0, std::min(current_x, static_cast<int>(image.HeightGetter()) - 1));
                    current_y = std::max(0, std::min(current_y, static_cast<int>(image.WidthGetter()) - 1));

                    Color neighbor = image.ColorGetter(current_x, current_y);
                    double weight = kernel[i + center][j + center];

                    red_sum += neighbor.red * weight;
                    green_sum += neighbor.green * weight;
                    blue_sum += neighbor.blue * weight;
                }
            }

            red_sum = std::clamp(red_sum, 0.0, 1.0 * MAX_COLOR_VAL);
            green_sum = std::clamp(green_sum, 0.0, 1.0 * MAX_COLOR_VAL);
            blue_sum = std::clamp(blue_sum, 0.0, 1.0 * MAX_COLOR_VAL);

            result.ColorSetter(
                x, y,
                Color(static_cast<uint8_t>(blue_sum), static_cast<uint8_t>(green_sum), static_cast<uint8_t>(red_sum)));
        }
    }

    return result;
}
