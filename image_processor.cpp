#include "args/args.h"
#include "Image/image.h"
#include "filters/filter_registry.h"
#include "bmp/loader.h"
#include "bmp/dumper.h"

#include <sstream>
#include <iostream>
#include <memory>

void WriteHelp() {
    std::cerr << "Reference for using filters: \n"
                 "The first argument is a path to input file, the second argument is a path to output file \n"
                 "-crop: Crop the image to the specified width and height. The top left of the image is used. "
                 "Parameters: width, height \n"
                 "-gs: Converts an image to grayscale. Parameters: -\n"
                 "-neg: Converts an image to a negative. Parameters: -\n"
                 "-sharp: Sharpening. Parameters: -\n"
                 "-edge: Border highlighting. Parameters: threshold\n"
                 "-blur: Gaussian blur. Parameters: sigma\n"
                 "-mosaic: Make an image looks like mosaic with blocks. Parameters: block size\n\n";
}

std::vector<argument_parser::Argument> GetArguments(int argc, char* argv[]) {
    std::vector<argument_parser::Argument> arguments = argument_parser::ParseArguments(argc, argv);
    if (arguments.size() < 2) {
        throw std::invalid_argument("You have not entered enough parameters.");
    }
    return arguments;
}

Image GetInputImage(const std::string& input_file) {
    return BMPLoader::LoadBMP(input_file);
}

void WriteOutputImage(const std::string& output_file, const Image& image) {
    BMPDumper::SaveBMP(image, output_file);
}

Image ApplyFilter(const std::vector<argument_parser::Argument>& arguments, Image image) {
    for (size_t i = 2; i < arguments.size(); ++i) {
        auto filter = FilterFactory::CreateFilter(arguments[i]);
        image = filter->Apply(image);
    }
    return image;
}

int main(int argc, char* argv[]) {
    try {
        std::vector<argument_parser::Argument> arguments = GetArguments(argc, argv);
        Image image = GetInputImage(arguments[0].Name);
        if (arguments.size() > 2) {
            image = ApplyFilter(arguments, image);
        }
        WriteOutputImage(arguments[1].Name, image);
    } catch (const std::exception& e) {
        WriteHelp();
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
