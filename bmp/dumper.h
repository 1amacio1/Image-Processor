#include "../Image/image.h"
#include <string>

class BMPDumper {
public:
    static void SaveBMP(const Image& image, const std::string& filename);
};
