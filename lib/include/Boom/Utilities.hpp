#pragma once

#include <map>
#include <vector>
#include <string>

namespace boom {

std::vector<std::string> ParseArgs(char const**, int);
std::map<std::string, std::string> ParseEnvs(char const**);

} /* namespace boom */