#pragma once

#include <Boom/JS.hpp>

namespace boom::api {

void InitProcessAPI(boom::js::ContextRef, char const** argv, size_t argc, char const** envp);

} /* namespace boom::api */