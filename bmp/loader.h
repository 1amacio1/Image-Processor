#include "../Image/image.h"
#include <string>

class BMPLoader {
public:
    static Image LoadBMP(const std::string& filename);
};
