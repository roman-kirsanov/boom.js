#pragma once

#include <JavaScriptCore/JSValueRef.h>
#include <Boom/JS/Scope.hpp>

namespace boom::js {

struct __ScopeImpl {
    JSObjectRef this_;
    JSValueRef* argv;
    std::size_t argc;
};

} /* namespace boom::js */