#pragma once

#include <windows.h>
#include <Boom/App.hpp>

namespace boom {

struct __AppImpl {
    HANDLE hTimerQueue;
    DWORD appThreadId;
};

} /* namespace boom */