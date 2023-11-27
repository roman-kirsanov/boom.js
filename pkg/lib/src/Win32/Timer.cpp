#include <map>
#include <mutex>
#include <optional>
#include <iostream>
#include <windows.h>
#include <Boom/Utilities.hpp>
#include <Boom/Timer.hpp>
#include "App.hpp"

#define TIME_HIGH_PRECISION 0

#define CreateTimerQueueE() [&]() { \
    auto res = CreateTimerQueue(); \
    if (res != nullptr) { \
        return res; \
    } else { \
        boom::Abort("CreateTimerQueue() failed"); \
    } \
}()

#define CreateTimerQueueTimerE(...) [&]() { \
    auto res = CreateTimerQueueTimer(__VA_ARGS__); \
    if (res != TRUE) { \
        boom::Abort("CreateTimerQueueTimer() failed"); \
    } \
}()

namespace boom {

struct __Timer {
    std::size_t id;
    std::function<void()> fn;
    HANDLE hTimer;
};

static auto __mutex = std::mutex();
static auto __timers = std::vector<boom::__Timer>();
static VOID CALLBACK __TimerProc(LPVOID lParam, std::uint8_t);

static HANDLE __TimerQueue() {
    static auto hQueue = CreateTimerQueueE();
    return hQueue;
}

static std::size_t __TimerSet(std::function<void()> const& fn, double interval, bool repeat) {
    static auto nextId = std::atomic<std::size_t>(1);
    auto id = nextId++;
    auto hTimer = (HANDLE)0;
    auto timeout = static_cast<int>(interval);
    auto interval2 = (repeat ? timeout : 0);
    auto lock = std::lock_guard(__mutex);
    CreateTimerQueueTimerE(
        &hTimer,
        boom::__TimerQueue(),
        boom::__TimerProc,
        (void*)id,
        timeout,
        interval2,
        WT_EXECUTEDEFAULT
    );
    boom::__timers.push_back({ id, fn, hTimer });
    return id;
}

static std::optional<boom::__Timer> __TimerGet(std::size_t id) {
    auto lock = std::lock_guard(__mutex);
    auto pos = std::find_if(
        boom::__timers.begin(),
        boom::__timers.end(),
        [id](auto& timer) { return (timer.id == id); }
    );
    if (pos != boom::__timers.end()) {
        return *pos;
    } else {
        return std::nullopt;
    }
}

static void __TimerUnset(std::size_t id) {
    auto lock = std::lock_guard(__mutex);
    auto pos = std::find_if(
        boom::__timers.begin(),
        boom::__timers.end(),
        [id](auto& timer) { return (timer.id == id); }
    );
    if (pos != boom::__timers.end()) {
        DeleteTimerQueueTimer(boom::__TimerQueue(), (*pos).hTimer, INVALID_HANDLE_VALUE);
        boom::__timers.erase(pos);
    }
}

static VOID CALLBACK __TimerProc(LPVOID lParam, std::uint8_t) {
    if (auto timer = boom::__TimerGet((std::size_t)lParam)) {
        (*timer).fn.operator()();
    }
}

struct __TimerImpl {
    std::size_t id;
};

void Timer::_implInit() {
    _impl = new boom::__TimerImpl{
        .id = boom::__TimerSet(
            [fn=_fn]() {
                boom::App::Default()->async(fn);
            },
            _interval,
            _repeat
        )
    };
}

void Timer::_implDone() {
    if (_impl->id != 0) {
        boom::__TimerUnset(_impl->id);
        _impl->id = 0;
    }
    delete _impl;
}

void Timer::_implCancel() {
    if (_impl->id != 0) {
        boom::__TimerUnset(_impl->id);
        _impl->id = 0;
    }
}

} /* namespace boom */