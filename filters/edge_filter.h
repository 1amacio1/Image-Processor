#pragma once
#include "filter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold);
    Image Apply(const Image& image) const override;

private:
    double threshold_;
};
