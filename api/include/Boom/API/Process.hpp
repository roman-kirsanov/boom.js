#pragma once

#include <Boom/JS.hpp>

namespace boom::api {

void InitProcessAPI(boom::js::ContextRef, std::vector<std::string> const&, std::map<std::string, std::string> const&);

} /* namespace boom::api */