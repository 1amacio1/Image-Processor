#include "args.h"

namespace argument_parser {

void Argument::Clear() {
    Name.clear();
    Parameters.clear();
}

bool Argument::IsEmpty() const {
    return Name.empty() && Parameters.empty();
}

std::vector<Argument> ParseArguments(int argc, char* argv[]) {
    std::vector<Argument> arguments;

    if (argc < 2) {
        return arguments;
    }

    arguments.emplace_back(Argument{argv[1], {}});
    if (argc > 2) {
        arguments.emplace_back(Argument{argv[2], {}});
    }

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.front() == '-') {
            arguments.emplace_back(Argument{arg, {}});
        } else if (!arguments.empty()) {
            arguments.back().Parameters.push_back(arg);
        }
    }

    return arguments;
}

}  // namespace argument_parser
