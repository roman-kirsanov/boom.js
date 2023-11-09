#pragma once

#include <windows.h>
#include <Boom/View.hpp>

namespace boom {

struct __ViewImpl {
    HWND window;
};

} /* namespace boom */