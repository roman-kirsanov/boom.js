#include <map>
#include <iostream>
#include <cassert>
#include <functional>
#include <windows.h>
#include "Window.hpp"

auto const __key_map = std::map<std::int32_t, boom::Key>({
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

boom::Key __key_convert(std::int32_t code) {
    if (__key_map.find(code) != __key_map.end()) {
        return __key_map.at(code);
    } else {
        return boom::Key::Unknown;
    }
}

namespace boom {

void Window::_implDone() {
    ;
    delete _impl;
}

void Window::_implInit() {
    _impl = new __WindowImpl{};
    ;
}

boom::Vec2 Window::_implPixelratio() const {
    return {
        1.0f,
        1.0f
    };
}

boom::Vec2 Window::_implSize() const {
    return {
        0.0f,
        0.0f
    };
}

bool Window::_implVisible() const {
    return false;
}

bool Window::_implClosable() const {
    return false;
}

bool Window::_implSizable() const {
    return false;
}

bool Window::_implMaximizable() const {
    return false;
}

bool Window::_implMinimizable() const {
    return false;
}

bool Window::_implMaximized() const {
    return false;
}

bool Window::_implMinimized() const {
    return false;
}

bool Window::_implTopmost() const {
    return false;
}

void Window::_implCenter() const {
    ;
}

void Window::_implSetTitle(std::string const& title) {
    ;
}

void Window::_implSetPosition(boom::Vec2 position) {
    ;
}

void Window::_implSetSize(boom::Vec2 size) {
    ;
}

void Window::_implSetVisible(bool visible) {
    if (visible) {
        if (!true) {
            ;
            _show();
        }
    } else {
        if (true) {
            ;
            _hide();
        }
    }
}

void Window::_implSetClosable(bool closable) {
    ;
}

void Window::_implSetSizable(bool sizable) {
    ;
}

void Window::_implSetMaximizable(bool maximizable) {
    ;
}

void Window::_implSetMinimizable(bool minimizable) {
    ;
}

void Window::_implSetMaximized(bool maximized) {
    ;
}

void Window::_implSetMinimized(bool minimized) {
    ;
}

void Window::_implSetTopmost(bool topmost) {
    ;
}

} /* namespace boom */
