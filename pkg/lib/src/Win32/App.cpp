#include <iostream>
#include <windows.h>
#include <Boom/App.hpp>

namespace boom {

void App::_implInit() {}

void App::_implDone() {}

void App::_implSetTitle(std::string const& title) {
    SetConsoleTitleA(title.c_str());
}

void App::_implPollEvents(double timeout) {
    auto message = MSG{};
    auto result = MsgWaitForMultipleObjects(0, nullptr, FALSE, static_cast<DWORD>(timeout), QS_ALLINPUT);
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

} /* namespace boom */
