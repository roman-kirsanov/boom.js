#pragma once

#include <windows.h>
#include <windowsx.h>
#include <Boom/View.hpp>

namespace boom {

struct __ViewImpl {
    HWND window;
    bool hover;
};

} /* namespace boom */