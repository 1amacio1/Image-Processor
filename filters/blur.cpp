#include "blur.h"
#include <cmath>
#include <algorithm>
#include <vector>

const int MAX_COLOR_VAL = 255;

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {
}

std::vector<double> GaussianBlurFilter::ComputeKernel() const {
    int kernel_radius = static_cast<int>(std::ceil(3 * sigma_));
    int kernel_size = 2 * kernel_radius + 1;
    std::vector<double> kernel(kernel_size);
    double sum = 0.0;

    for (int i = -kernel_radius; i <= kernel_radius; ++i) {
        double value = exp(-(i * i) / (2 * sigma_ * sigma_)) / sqrt(2 * M_PI * sigma_ * sigma_);
        kernel[i + kernel_radius] = value;
        sum += value;
    }

    for (double& val : kernel) {
        val /= sum;
    }

    return kernel;
}

Image GaussianBlurFilter::Apply(const Image& image) const {
    auto kernel = ComputeKernel();
    const int kernel_radius = (static_cast<int>(kernel.size()) - 1) / 2;
    const int width = static_cast<int>(image.WidthGetter());
    const int height = static_cast<int>(image.HeightGetter());

    Image temp_image(height, width);
    Image result(height, width);

#pragma omp parallel for
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            for (int i = -kernel_radius; i <= kernel_radius; ++i) {
                int xi = std::clamp(x + i, 0, width - 1);
                const Color& pixel = image.ColorGetter(y, xi);
                double weight = kernel[i + kernel_radius];

                r += pixel.red * weight;
                g += pixel.green * weight;
                b += pixel.blue * weight;
            }

            temp_image.ColorSetter(y, x,
                                   Color(static_cast<uint8_t>(std::clamp(b, 0.0, MAX_COLOR_VAL * 1.0)),
                                         static_cast<uint8_t>(std::clamp(g, 0.0, MAX_COLOR_VAL * 1.0)),
                                         static_cast<uint8_t>(std::clamp(r, 0.0, MAX_COLOR_VAL * 1.0))));
        }
    }

#pragma omp parallel for
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            double r = 0.0;
            double g = 0.0;
            double b = 0.0;

            for (int i = -kernel_radius; i <= kernel_radius; ++i) {
                int yi = std::clamp(y + i, 0, height - 1);
                const Color& pixel = temp_image.ColorGetter(yi, x);
                double weight = kernel[i + kernel_radius];

                r += pixel.red * weight;
                g += pixel.green * weight;
                b += pixel.blue * weight;
            }

            result.ColorSetter(y, x,
                               Color(static_cast<uint8_t>(std::clamp(b, 0.0, MAX_COLOR_VAL * 1.0)),
                                     static_cast<uint8_t>(std::clamp(g, 0.0, MAX_COLOR_VAL * 1.0)),
                                     static_cast<uint8_t>(std::clamp(r, 0.0, MAX_COLOR_VAL * 1.0))));
        }
    }

    return result;
}
