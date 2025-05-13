#pragma once
#include "filter.h"

class MosaicFilter : public Filter {
public:
    explicit MosaicFilter(size_t block_size);
    Image Apply(const Image& image) const override;

private:
    size_t block_size_;
};
