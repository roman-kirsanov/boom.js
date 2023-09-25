#pragma once

#include <JavaScriptCore/JavaScriptCore.h>
#include <Boom/JS/Class.hpp>

namespace boom::js {

struct __ClassImpl {
    JSClassRef class_;
};

} /* namespace boom::js */