#pragma once

#ifdef _WIN32
    #include <JavaScriptCore/JSContextRef.h>
    #include <JavaScriptCore/JSStringRef.h>
#elif
    #include <JavaScriptCore/JavaScriptCore.h>
#endif

#include <Boom/JS/Context.hpp>

namespace boom::js {

struct __ContextImpl {
    JSGlobalContextRef context;
    JSValueRef global;
};

} /* namespace boom::js */