#include "filter_registry.h"
#include "crop_filter.h"
#include "../args/args.h"
#include "grayscale.h"
#include "negative_filter.h"
#include "sharp.h"
#include "edge_filter.h"
#include "mosaic.h"
#include "blur.h"
#include <stdexcept>
#include <string>

std::unique_ptr<Filter> FilterFactory::CreateFilter(const argument_parser::Argument& argument) {
    const std::string& name = argument.Name;
    const std::vector<std::string>& params = argument.Parameters;

    if (name == "-crop") {
        if (params.size() != 2) {
            throw std::invalid_argument("Crop filter requires two parameters: width and height");
        }
        size_t width = std::stoul(params[0]);
        size_t height = std::stoul(params[1]);
        return std::make_unique<CropFilter>(width, height);
    } else if (name == "-gs") {
        return std::make_unique<GrayscaleFilter>();
    } else if (name == "-neg") {
        return std::make_unique<NegativeFilter>();
    } else if (name == "-sharp") {
        return std::make_unique<SharpeningFilter>();
    } else if (name == "-edge") {
        if (params.size() != 1) {
            throw std::invalid_argument("Edge detection filter requires one parameter: threshold");
        }
        double threshold = std::stod(params[0]);
        return std::make_unique<EdgeDetectionFilter>(threshold);
    } else if (name == "-blur") {
        if (params.size() != 1) {
            throw std::invalid_argument("Gaussian blur filter requires one parameter: sigma");
        }
        double sigma = std::stod(params[0]);
        return std::make_unique<GaussianBlurFilter>(sigma);
    } else if (name == "-mosaic") {
        if (params.size() != 1) {
            throw std::invalid_argument("Mosaic filter requires one parameter: block size");
        }
        size_t block_size = std::stoul(params[0]);
        return std::make_unique<MosaicFilter>(block_size);
    } else {
        throw std::invalid_argument("Unknown filter: " + name);
    }
}
