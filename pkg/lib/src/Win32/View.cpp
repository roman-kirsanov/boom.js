#include <Boom/Utilities.hpp>
#include "View.hpp"

namespace boom {

boom::Vec2 GetPosition(std::intptr_t lparam) {
    auto const x = GET_X_LPARAM(lparam);
    auto const y = GET_Y_LPARAM(lparam);
    return {
        .x = static_cast<float>(x),
        .y = static_cast<float>(y)
    };
}

boom::KeyModifiers GetKeyModifiers() {
    auto const control = GetAsyncKeyState(VK_CONTROL) & 0x8000;
    auto const shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
    auto const alt = GetAsyncKeyState(VK_MENU) & 0x8000;
    auto const meta = GetAsyncKeyState(VK_LWIN) & 0x8000
                    + GetAsyncKeyState(VK_RWIN) & 0x8000;
    return boom::KeyModifiers{
        .control = (control > 0),
        .shift = (shift > 0),
        .meta = (meta > 0),
        .alt = (alt > 0)
    };
}

std::intptr_t View::_ImplViewProc(void* hwnd, std::uint32_t message, std::uintptr_t wparam, std::intptr_t lparam) {
    boom::View* view = (boom::View*)GetWindowLongPtr((HWND)hwnd, GWLP_USERDATA);
    if (view != nullptr) {
        if (message == WM_MOUSEMOVE) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            if (view->_impl->hover == false) {
                auto track = TRACKMOUSEEVENT{
                    .cbSize = sizeof(TRACKMOUSEEVENT),
                    .dwFlags = TME_LEAVE,
                    .hwndTrack = (HWND)hwnd
                };
                TrackMouseEvent(&track);
                view->_mouseEnter(position, modifiers);
                view->_impl->hover = true;
            }
            view->_mouseMove(position, modifiers);
        } else if (message == WM_MOUSELEAVE) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_mouseExit(position, modifiers);
            view->_impl->hover = false;
        } else if (message == WM_LBUTTONDOWN) {
            if (GetFocus() != (HWND)hwnd) {
                SetFocus((HWND)hwnd);
                // TODO: trigger focus...
            }
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_lButtonDown(position, modifiers);
        } else if (message == WM_RBUTTONDOWN) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_rButtonDown(position, modifiers);
        } else if (message == WM_MBUTTONDOWN) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_mButtonDown(position, modifiers);
        } else if (message == WM_LBUTTONUP) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_lButtonUp(position, modifiers);
        } else if (message == WM_RBUTTONUP) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_rButtonUp(position, modifiers);
        } else if (message == WM_MBUTTONUP) {
            auto const position = boom::GetPosition(lparam);
            auto const modifiers = boom::GetKeyModifiers();
            view->_mButtonUp(position, modifiers);
        } else if (message == WM_KEYDOWN) {
            auto const modifiers = boom::GetKeyModifiers();
            view->_keyDown(boom::Key::Unknown, modifiers, "");
        } else if (message == WM_KEYUP) {
            auto const modifiers = boom::GetKeyModifiers();
            view->_keyUp(boom::Key::Unknown, modifiers, "");
        } else if (message == WM_KILLFOCUS) {
            // TODO: trigger blur...
        }
    }
    return DefWindowProc((HWND)hwnd, message, wparam, lparam);
}

void View::_implInit() {
    static auto const kViewClassName = "BoomViewClass";
    static auto const kViewClassDef = WNDCLASSA{
        .lpfnWndProc = (WNDPROC)boom::View::_ImplViewProc,
        .hInstance = GetModuleHandle(nullptr),
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .lpszClassName = kViewClassName
    };
    static auto classRegistered = false;
    if (classRegistered == false) {
        classRegistered = true;
        RegisterClassA(&kViewClassDef);
    }
    auto window = CreateWindowExA(
        0,
        kViewClassName,
        "",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        nullptr,
        nullptr,
        GetModuleHandle(nullptr),
        nullptr
    );
    if (window) {
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);
        _impl = new boom::__ViewImpl{ .window = window };
    } else {
        boom::Abort("boom::View::View() failed: Failed to create a view");
    }
}

void View::_implDone() {
    DestroyWindow(_impl->window);
    delete _impl;
}

boom::Vec2 View::_implPosition() const {
    auto rect = RECT{};
    GetClientRect(_impl->window, &rect);
    return {
        static_cast<float>(rect.left),
        static_cast<float>(rect.top)
    };
}

boom::Vec2 View::_implSize() const {
    auto rect = RECT{};
    GetClientRect(_impl->window, &rect);
    return {
        static_cast<float>(rect.right - rect.left),
        static_cast<float>(rect.bottom - rect.top)
    };
}

bool View::_implHover() const {
    return _impl->hover;
}

bool View::_implFocused() const {
    return (GetFocus() == (HWND)_impl->window);
}

void View::_implAddChild(boom::ViewRef child) {
    if (auto parent = GetParent(child->_impl->window)) {
        ShowWindow(child->_impl->window, SW_HIDE);
        SetWindowLongPtr(child->_impl->window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetParent(child->_impl->window, nullptr);
    }
    auto style = GetWindowLongPtr(child->_impl->window, GWL_STYLE);
    SetWindowLongPtr(child->_impl->window, GWL_STYLE, (style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU)) | WS_CHILD);
    SetParent(child->_impl->window, _impl->window);
    ShowWindow(child->_impl->window, SW_SHOW);
    InvalidateRect(child->_impl->window, nullptr, TRUE);
}

void View::_implRemoveChild(boom::ViewRef child) {
    if (auto parent = GetParent(child->_impl->window)) {
        ShowWindow(child->_impl->window, SW_HIDE);
        SetWindowLongPtr(child->_impl->window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetParent(child->_impl->window, nullptr);
    }
}

void View::_implReplaceChild(boom::ViewRef, boom::ViewRef) {

}

void View::_implInsertChild(boom::ViewRef, std::size_t) {

}

void View::_implSetPosition(boom::Vec2 position) {
    SetWindowPos(_impl->window, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void View::_implSetSize(boom::Vec2 size) {
    SetWindowPos(
        _impl->window,
        nullptr,
        0, 0,
        size.width,
        size.height,
        (SWP_NOMOVE | SWP_NOZORDER)
    );
}

void View::_implSetFocus() {
    SetFocus((HWND)_impl->window);
}

} /* namespace boom */