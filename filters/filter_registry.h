#pragma once
#include "filter.h"
#include <memory>
#include <string>
#include <vector>

namespace argument_parser {
struct Argument;
}

class FilterFactory {
public:
    static std::unique_ptr<Filter> CreateFilter(const argument_parser::Argument& argument);
};
