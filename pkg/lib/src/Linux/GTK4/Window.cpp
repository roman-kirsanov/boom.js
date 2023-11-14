#include <map>
#include <iostream>
#include <cassert>
#include <functional>
#include <gtk/gtk.h>
#include "Window.hpp"

auto const __keyMap = std::map<std::int32_t, boom::Key>({
    
});

boom::Key __keyConvert(std::int32_t code) {
    if (__keyMap.find(code) != __keyMap.end()) {
        return __keyMap.at(code);
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
