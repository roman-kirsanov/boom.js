#pragma once

#include <windows.h>
#include <Boom/Application.hpp>

namespace boom {

struct __AppImpl {
    DWORD appThreadId;
};

} /* namespace boom */