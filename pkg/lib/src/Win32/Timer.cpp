#include <iostream>
#include <windows.h>
#include <Boom/Utilities.hpp>
#include <Boom/Timer.hpp>
#include <Boom/Loop.hpp>

#define TIME_HIGH_PRECISION 0

namespace boom {

struct __TimerImpl {
    HANDLE hTimer;
};

void Timer::_implInit() {
    auto hTimer = (HANDLE)0;
    auto timeout = static_cast<int>(_interval);
    auto interval = (_repeat ? timeout : 0);
    auto result = CreateTimerQueueTimer(
        &hTimer,
        nullptr,
        boom::Timer::_ImplTimerProc,
        static_cast<void*>(this),
        timeout,
        interval,
        WT_EXECUTEINTIMERTHREAD
    );
    if (!result) {
        boom::Abort("ERROR: boom::Timer::Timer() failed: \"CreateTimerQueueTimer\" failed");
    }
    _impl = new boom::__TimerImpl{ .hTimer = hTimer };
}

void Timer::_implDone() {
    if (_impl->hTimer != 0) {
        DeleteTimerQueueTimer(nullptr, _impl->hTimer, INVALID_HANDLE_VALUE);
        _impl->hTimer = 0;
    }
}

void Timer::_implCancel() {
    if (_impl->hTimer != 0) {
        DeleteTimerQueueTimer(nullptr, _impl->hTimer, INVALID_HANDLE_VALUE);
        _impl->hTimer = 0;
    }
}

void __stdcall Timer::_ImplTimerProc(void* lParam, std::uint8_t) {
    if (auto timer = static_cast<boom::Timer*>(lParam)) {
        timer->_loop->add(timer->_fn);
    }
}

} /* namespace boom */