#include <map>
#include <iostream>
#include <cassert>
#include <functional>
#include <gtk/gtk.h>
#include <Boom/Utilities.hpp>
#include "Window.hpp"
#include "View.hpp"
#include "App.hpp"

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
    gtk_window_destroy(GTK_WINDOW(_impl->window));
    delete _impl;
}

void Window::_implInit() {
    _impl = new boom::__WindowImpl{
        .window = gtk_window_new()
    };
}

boom::Vec2 Window::_implPixelratio() const {
    return {
        1.0f,
        1.0f
    };
}

boom::Vec2 Window::_implSize() const {
    auto width = 0;
    auto height = 0;
    gtk_widget_get_size_request(_impl->window, &width, &height);
    return {
        static_cast<float>(width),
        static_cast<float>(height)
    };
}

bool Window::_implVisible() const {
    return gtk_widget_get_visible(_impl->window);
}

bool Window::_implClosable() const {
    return gtk_window_get_deletable(GTK_WINDOW(_impl->window));
}

bool Window::_implSizable() const {
    return gtk_window_get_resizable(GTK_WINDOW(_impl->window));
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

void Window::_implSetView(std::shared_ptr<boom::View> view) {
    if (_view != nullptr) {
        gtk_window_set_child(GTK_WINDOW(_impl->window), nullptr);
    }
    if (view != nullptr) {
        gtk_window_set_child(GTK_WINDOW(_impl->window), view->_impl->widget);
    }
}

} /* namespace boom */
