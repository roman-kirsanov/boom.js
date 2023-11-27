#pragma once

#include <windows.h>
#include <Boom/App.hpp>

namespace boom {

struct __AppImpl {
    DWORD appThreadId;
};

} /* namespace boom */