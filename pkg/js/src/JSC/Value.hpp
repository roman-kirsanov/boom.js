#pragma once

#include <JavaScriptCore/JavaScriptCore.h>
#include <Boom/JS/Value.hpp>

namespace boom::js {

struct __ValueImpl {
    JSValueRef value;
};

} /* namespace boom::js */