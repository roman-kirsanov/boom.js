#pragma once

#include <Cocoa/Cocoa.h>
#include "../Surface.hpp"

namespace boom {

struct __SurfaceImplImpl {
    NSWindow* window;
    NSOpenGLView* view;
};

} /* namespace boom */
