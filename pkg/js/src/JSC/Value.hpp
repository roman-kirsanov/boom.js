#pragma once

#include <JavaScriptCore/JSValueRef.h>
#include <JavaScriptCore/JSObjectRef.h>
#include <JavaScriptCore/JSTypedArray.h>
#include <Boom/JS/Value.hpp>

namespace boom::js {

struct __ValueImpl {
    JSValueRef value;
};

} /* namespace boom::js */