#include <iostream>
#include <Boom/Utilities.hpp>

namespace boom {

void Abort(std::string const& message) {
    std::cerr << "ERROR: " << message << std::endl;
    std::exit(-1);
}

void Warning(std::string const& message) {
    std::cerr << "WARN: " << message << std::endl;
}

std::vector<std::string> ParseArgs(char const** argv, int argc) {
    auto args = std::vector<std::string>();
    for (int i = 0; i < argc; i++) {
        args.emplace_back(argv[i]);
    }
    return args;
}

std::map<std::string, std::string> ParseEnvs(char const** envp) {
    auto envs = std::map<std::string, std::string>();
    for (auto env = envp; *env != 0; env++) {
        auto entry = std::string(*env);
        auto index = entry.find("=");
        if (index != std::string::npos) {
            auto name = entry.substr(0, index);
            auto value = entry.substr(index + 1, entry.size() - (index + 1));
            envs.insert({ name, value });
        }
    }
    return envs;
}

} /* namespace boom */