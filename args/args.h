#pragma once

#include <string>
#include <vector>

namespace argument_parser {

struct Argument {
    std::string Name;
    std::vector<std::string> Parameters;

    void Clear();
    bool IsEmpty() const;
};

std::vector<Argument> ParseArguments(int argc, char* argv[]);
}  // namespace argument_parser
