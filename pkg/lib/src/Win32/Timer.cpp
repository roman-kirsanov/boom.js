#include <iostream>
#include <windows.h>
#include <Boom/Utilities.hpp>
#include <Boom/Timer.hpp>
#include <Boom/Loop.hpp>

#define TIME_HIGH_PRECISION 0

namespace boom {

struct __TimerImpl {
    MMRESULT timerId;
};

void Timer::_implInit() {
    auto const interval = static_cast<int>(_interval);
    auto const precision = TIME_HIGH_PRECISION;
    auto const userdata = reinterpret_cast<DWORD_PTR>(this);
    auto const repeat = (_repeat ? TIME_ONESHOT : TIME_PERIODIC);
    auto const timerId = timeSetEvent(interval, precision, (LPTIMECALLBACK)boom::Timer::_ImplTimerProc, userdata, repeat);
    if (timerId == 0) {
        boom::Abort("ERROR: boom::Timer::Timer() failed: \"timeSetEvent\" failed");
    }
    _impl = new boom::__TimerImpl{ .timerId = timerId };
}

void Timer::_implDone() {
    if (_impl->timerId != 0) {
        timeKillEvent(_impl->timerId);
        _impl->timerId = 0;
    }
}

void Timer::_implCancel() {
    if (_impl->timerId != 0) {
        timeKillEvent(_impl->timerId);
        _impl->timerId = 0;
    }
}

void __stdcall Timer::_ImplTimerProc(std::uint32_t uID, std::uint32_t uMsg, std::uint64_t dwUser, std::uint64_t dw1, std::uint64_t dw2) {
    std::cout << "Timer::_ImplTimerProc" << std::endl;
    boom::Timer* timer = reinterpret_cast<boom::Timer*>(dwUser);
    if (timer != nullptr) {
        timer->_loop->add(timer->_fn);
    }
}

} /* namespace boom */