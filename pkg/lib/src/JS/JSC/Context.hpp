#pragma once

#include <JavaScriptCore/JSContextRef.h>
#include <JavaScriptCore/JSStringRef.h>
#include <Boom/JS/Context.hpp>

namespace boom::js {

struct __ContextImpl {
    JSGlobalContextRef context;
    JSValueRef global;
};

} /* namespace boom::js */