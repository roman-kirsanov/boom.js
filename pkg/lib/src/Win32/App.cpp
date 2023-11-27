#include <iostream>
#include <windows.h>
#include <ShellScalingApi.h>
#include <Boom/Utilities.hpp>
#include "App.hpp"

#define WM_WAKEUP (WM_USER + 999)

#define CreateTimerQueueE() [&]() { \
    auto res = CreateTimerQueue(); \
    if (res != nullptr) { \
        return res; \
    } else { \
        boom::Abort("CreateTimerQueue() failed"); \
    } \
}()

namespace boom {

void App::_implInit() {
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    auto hTimerQueue = CreateTimerQueueE();
    auto appThreadId = GetCurrentThreadId();
    _impl = new boom::__AppImpl{
        .hTimerQueue = hTimerQueue,
        .appThreadId = appThreadId
    };
}

void App::_implDone() {
    DeleteTimerQueue(_impl->hTimerQueue);
    delete _impl;
}

void App::_implSetTitle(std::string const& title) {
    SetConsoleTitleA(title.c_str());
}

void App::_implPollEvents() {
    auto message = MSG{};
    auto result = MsgWaitForMultipleObjects(0, nullptr, FALSE, static_cast<DWORD>(999), QS_ALLINPUT);
    if (result == WAIT_OBJECT_0) {
        if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT) {
                ; // TODO: exit here?
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
}

void App::_implWakeUp() {
    PostThreadMessage(_impl->appThreadId, WM_WAKEUP, 0, 0);
}

} /* namespace boom */
