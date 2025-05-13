#pragma once
#include "filter.h"
#include <vector>

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma);
    Image Apply(const Image& image) const override;

private:
    double sigma_;
    std::vector<double> ComputeKernel() const;
};
