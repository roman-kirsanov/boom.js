#pragma once

#include <Cocoa/Cocoa.h>
#include "../Context.hpp"

namespace boom {

struct __ContextImpl {
    NSOpenGLContext* context;
};

} /* namespace boom */
