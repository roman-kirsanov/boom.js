#include <map>
#include <iostream>
#include <cassert>
#include <functional>
#include <windows.h>
#include <Boom/Utilities.hpp>
#include "Window.hpp"
#include "View.hpp"

auto const __KeyMap = std::map<std::int32_t, boom::Key>({
    { '0', boom::Key::_0 },
    { '1', boom::Key::_1 },
    { '2', boom::Key::_2 },
    { '3', boom::Key::_3 },
    { '4', boom::Key::_4 },
    { '5', boom::Key::_5 },
    { '6', boom::Key::_6 },
    { '7', boom::Key::_7 },
    { '8', boom::Key::_8 },
    { '9', boom::Key::_9 },
    { 'A', boom::Key::A },
    { 'B', boom::Key::B },
    { 'C', boom::Key::C },
    { 'D', boom::Key::D },
    { 'E', boom::Key::E },
    { 'F', boom::Key::F },
    { 'G', boom::Key::G },
    { 'H', boom::Key::H },
    { 'I', boom::Key::I },
    { 'J', boom::Key::J },
    { 'K', boom::Key::K },
    { 'L', boom::Key::L },
    { 'M', boom::Key::M },
    { 'N', boom::Key::N },
    { 'O', boom::Key::O },
    { 'P', boom::Key::P },
    { 'Q', boom::Key::Q },
    { 'R', boom::Key::R },
    { 'S', boom::Key::S },
    { 'T', boom::Key::T },
    { 'U', boom::Key::U },
    { 'V', boom::Key::V },
    { 'W', boom::Key::W },
    { 'X', boom::Key::X },
    { 'Y', boom::Key::Y },
    { 'Z', boom::Key::Z },
    { VK_F1, boom::Key::F1 },
    { VK_F2, boom::Key::F2 },
    { VK_F3, boom::Key::F3 },
    { VK_F4, boom::Key::F4 },
    { VK_F5, boom::Key::F5 },
    { VK_F6, boom::Key::F6 },
    { VK_F7, boom::Key::F7 },
    { VK_F8, boom::Key::F8 },
    { VK_F9, boom::Key::F9 },
    { VK_F10, boom::Key::F10 },
    { VK_F11, boom::Key::F11 },
    { VK_F12, boom::Key::F12 },
    { VK_F13, boom::Key::F13 },
    { VK_F14, boom::Key::F14 },
    { VK_F15, boom::Key::F15 },
    { VK_F16, boom::Key::F16 },
    { VK_F17, boom::Key::F17 },
    { VK_F18, boom::Key::F18 },
    { VK_F19, boom::Key::F19 },
    { VK_F20, boom::Key::F20 },
    { VK_MENU, boom::Key::Alt },
    { VK_DOWN, boom::Key::ArrowDown },
    { VK_LEFT, boom::Key::ArrowLeft },
    { VK_RIGHT, boom::Key::ArrowRight },
    { VK_UP, boom::Key::ArrowUp },
    { VK_OEM_5, boom::Key::Backslash },
    { VK_OEM_4, boom::Key::BracketLeft },
    { VK_OEM_6, boom::Key::BracketRight },
    { VK_CAPITAL, boom::Key::Capslock },
    { VK_OEM_COMMA, boom::Key::Comma },
    { VK_CONTROL, boom::Key::Control },
    { VK_BACK, boom::Key::Backspace },
    { VK_END, boom::Key::End },
    { VK_OEM_PLUS, boom::Key::Equal },
    { VK_ESCAPE, boom::Key::Escape },
    { VK_DELETE, boom::Key::ForwardDelete },
    { VK_OEM_3, boom::Key::Grave },
    { VK_HOME, boom::Key::Home },
    { VK_LWIN, boom::Key::Meta },
    { VK_OEM_MINUS, boom::Key::Minus },
    { VK_VOLUME_MUTE, boom::Key::Mute },
    { VK_NEXT, boom::Key::PageDown },
    { VK_PRIOR, boom::Key::PageUp },
    { VK_OEM_PERIOD, boom::Key::Period },
    { VK_OEM_7, boom::Key::Quote },
    { VK_RETURN, boom::Key::Return },
    { VK_RMENU, boom::Key::RightAlt },
    { VK_RCONTROL, boom::Key::RightControl },
    { VK_RSHIFT, boom::Key::RightShift },
    { VK_OEM_1, boom::Key::Semicolon },
    { VK_SHIFT, boom::Key::Shift },
    { VK_OEM_2, boom::Key::Slash },
    { VK_SPACE, boom::Key::Space },
    { VK_TAB, boom::Key::Tab },
    { VK_VOLUME_DOWN, boom::Key::VolumeDown },
    { VK_VOLUME_UP, boom::Key::VolumeUp },
    { VK_CLEAR, boom::Key::KeypadClear },
    { VK_DECIMAL, boom::Key::KeypadDecimal },
    { VK_DIVIDE, boom::Key::KeypadDivide },
    { VK_RETURN, boom::Key::KeypadEnter },
    { VK_SUBTRACT, boom::Key::KeypadMinus },
    { VK_MULTIPLY, boom::Key::KeypadMultiply },
    { VK_ADD, boom::Key::KeypadPlus },
    { VK_NUMPAD0, boom::Key::Keypad0 },
    { VK_NUMPAD1, boom::Key::Keypad1 },
    { VK_NUMPAD2, boom::Key::Keypad2 },
    { VK_NUMPAD3, boom::Key::Keypad3 },
    { VK_NUMPAD4, boom::Key::Keypad4 },
    { VK_NUMPAD5, boom::Key::Keypad5 },
    { VK_NUMPAD6, boom::Key::Keypad6 },
    { VK_NUMPAD7, boom::Key::Keypad7 },
    { VK_NUMPAD8, boom::Key::Keypad8 },
    { VK_NUMPAD9, boom::Key::Keypad9 }
});

static boom::Key __KeyConvert(std::int32_t code) {
    if (__KeyMap.find(code) != __KeyMap.end()) {
        return __KeyMap.at(code);
    } else {
        return boom::Key::Unknown;
    }
}

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
    boom::Window* window = (boom::Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (window != nullptr) {
        if (message == WM_SIZE) {
            if (window->view()) {
                window->view()->setSize(window->size());
            }
        }
    }
    return DefWindowProc(hwnd, message, wparam, lparam);
}

namespace boom {

void Window::_implDone() {
    DestroyWindow(_impl->window);
    delete _impl;
}

void Window::_implInit() {
    static auto const WINDOW_CLASS_NAME = "BoomWindowClass";
    static auto const WINDOW_CLASS_DEF = WNDCLASSA{
        .lpfnWndProc = WindowProc,
        .hInstance = GetModuleHandle(nullptr),
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .lpszClassName = WINDOW_CLASS_NAME
    };
    static auto classRegistered = false;
    if (classRegistered == false) {
        classRegistered = true;
        RegisterClassA(&WINDOW_CLASS_DEF);
    }
    auto window = CreateWindowExA(
        0,
        WINDOW_CLASS_NAME,
        "",
        WS_OVERLAPPEDWINDOW,
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
        _impl = new boom::__WindowImpl{ .window = window };
    } else {
        boom::Abort("boom::Window::Window() failed: Failed to create a window");
    }
}

boom::Vec2 Window::_implPixelratio() const {
    return {
        1.0f,
        1.0f
    };
}

boom::Vec2 Window::_implSize() const {
    auto rect = RECT{};
    GetClientRect(_impl->window, &rect);
    return {
        static_cast<float>(rect.right - rect.left),
        static_cast<float>(rect.bottom - rect.top)
    };
}

bool Window::_implVisible() const {
    return IsWindowVisible(_impl->window);
}

bool Window::_implClosable() const {
    return true; // TODO: Looks like on Windows there is no way of disabling close button...
}

bool Window::_implSizable() const {
    return ((GetWindowLongPtr(_impl->window, GWL_STYLE) & WS_SIZEBOX) != 0);
}

bool Window::_implMaximizable() const {
    return ((GetWindowLongPtr(_impl->window, GWL_STYLE) & WS_MAXIMIZEBOX) != 0);
}

bool Window::_implMinimizable() const {
    return ((GetWindowLongPtr(_impl->window, GWL_STYLE) & WS_MINIMIZEBOX) != 0);
}

bool Window::_implMaximized() const {
    return IsZoomed(_impl->window);
}

bool Window::_implMinimized() const {
    return IsIconic(_impl->window);
}

bool Window::_implTopmost() const {
    return ((GetWindowLongPtr(_impl->window, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0);
}

void Window::_implCenter() const {
    auto rect = RECT{};
    GetWindowRect(_impl->window, &rect);
    SetWindowPos(
        _impl->window,
        nullptr,
        ((GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left)) / 2),
        ((GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top)) / 2),
        0,
        0,
        SWP_NOZORDER | SWP_NOSIZE
    );
}

void Window::_implSetTitle(std::string const& title) {
    SetWindowTextA(_impl->window, title.c_str());
}

void Window::_implSetPosition(boom::Vec2 position) {
    SetWindowPos(_impl->window, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::_implSetSize(boom::Vec2 size) {
    auto dwStyle = (DWORD)GetWindowLongPtr(_impl->window, GWL_STYLE);
    auto dwExStyle = (DWORD)GetWindowLongPtr(_impl->window, GWL_EXSTYLE);
    auto bMenu = GetMenu(_impl->window) != nullptr;
    auto rect = RECT{
        0, 0,
        static_cast<long>(size.width),
        static_cast<long>(size.height)
    };
    AdjustWindowRectEx(&rect, dwStyle, bMenu, dwExStyle);
    SetWindowPos(
        _impl->window,
        nullptr,
        0, 0,
        (rect.right - rect.left),
        (rect.bottom - rect.top),
        (SWP_NOMOVE | SWP_NOZORDER)
    );
}

void Window::_implSetVisible(bool visible) {
    if (visible) {
        if (IsWindowVisible(_impl->window) == FALSE) {
            ShowWindow(_impl->window, SW_SHOW);
            _show();
        }
    } else {
        if (IsWindowVisible(_impl->window) == TRUE) {
            ShowWindow(_impl->window, SW_HIDE);
            _hide();
        }
    }
}

void Window::_implSetClosable(bool closable) {
    ; // TODO: Looks like on Windows there is no way of disabling close button...
}

void Window::_implSetSizable(bool sizable) {
    auto style = GetWindowLongPtr(_impl->window, GWL_STYLE);
    SetWindowLongPtrA(_impl->window, GWL_STYLE, (sizable ? (style | WS_SIZEBOX) : (style & ~WS_SIZEBOX)));
}

void Window::_implSetMaximizable(bool maximizable) {
    auto style = GetWindowLongPtr(_impl->window, GWL_STYLE);
    SetWindowLongPtrA(_impl->window, GWL_STYLE, (maximizable ? (style | WS_MAXIMIZEBOX) : (style & ~WS_MAXIMIZEBOX)));
}

void Window::_implSetMinimizable(bool minimizable) {
    auto style = GetWindowLongPtr(_impl->window, GWL_STYLE);
    SetWindowLongPtrA(_impl->window, GWL_STYLE, (minimizable ? (style | WS_MINIMIZEBOX) : (style & ~WS_MINIMIZEBOX)));
}

void Window::_implSetMaximized(bool maximized) {
    ShowWindow(_impl->window, (maximized ? SW_MAXIMIZE : SW_RESTORE));
}

void Window::_implSetMinimized(bool minimized) {
    ShowWindow(_impl->window, (minimized ? SW_MINIMIZE : SW_RESTORE));
}

void Window::_implSetTopmost(bool topmost) {
    SetWindowPos(_impl->window, (topmost ? HWND_TOPMOST : HWND_NOTOPMOST), 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void Window::_implSetView(std::shared_ptr<boom::View> view) {
    if (_view != nullptr) {
        ShowWindow(_view->_impl->window, SW_HIDE);
        SetWindowLongPtr(_view->_impl->window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetParent(_view->_impl->window, nullptr);
    }
    if (view != nullptr) {
        auto style = GetWindowLongPtr(view->_impl->window, GWL_STYLE);
        SetWindowLongPtr(view->_impl->window, GWL_STYLE, (style & ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU)) | WS_CHILD);
        SetParent(view->_impl->window, _impl->window);
        ShowWindow(view->_impl->window, SW_SHOW);
        InvalidateRect(view->_impl->window, nullptr, TRUE);
    }
}

} /* namespace boom */
