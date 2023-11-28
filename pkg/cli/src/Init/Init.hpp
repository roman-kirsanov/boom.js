#pragma once

#include <map>
#include <string>
#include <vector>

namespace boom::cli {

void Init(std::map<std::string, std::string> const&, std::vector<std::string> const&);

} /* namespace boom::cli */