#pragma once

#include <JavaScriptCore/JavaScriptCore.h>
#include <Boom/JS/Scope.hpp>

namespace boom::js {

struct __ScopeImpl {
    JSObjectRef this_;
    JSValueRef* argv;
    std::size_t argc;
};

} /* namespace boom::js */