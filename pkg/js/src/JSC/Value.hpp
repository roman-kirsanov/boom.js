#pragma once

#ifdef _WIN32
    #include <JavaScriptCore/JSValueRef.h>
    #include <JavaScriptCore/JSObjectRef.h>
    #include <JavaScriptCore/JSTypedArray.h>
#elif
    #include <JavaScriptCore/JavaScriptCore.h>
#endif

#include <Boom/JS/Value.hpp>

namespace boom::js {

struct __ValueImpl {
    JSValueRef value;
};

} /* namespace boom::js */