#pragma once

#include <Boom/JS.hpp>

namespace boom::api {

auto constexpr kViewValueKey = 1;

void InitViewAPI(boom::js::ContextRef);

} /* namespace boom::api */