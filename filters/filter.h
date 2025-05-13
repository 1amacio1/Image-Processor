#pragma once
#include "../Image/image.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;
};
