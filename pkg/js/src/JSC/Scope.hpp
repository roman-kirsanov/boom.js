#pragma once

#ifdef _WIN32
    #include <JavaScriptCore/JSValueRef.h>
#elif
    #include <JavaScriptCore/JavaScriptCore.h>
#endif
#include <Boom/JS/Scope.hpp>

namespace boom::js {

struct __ScopeImpl {
    JSObjectRef this_;
    JSValueRef* argv;
    std::size_t argc;
};

} /* namespace boom::js */