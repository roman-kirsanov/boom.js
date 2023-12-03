#include <cassert>
#include <iostream>
#include <Boom/View.hpp>
#include <Boom/Window.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/Application.hpp>

namespace boom {

Window::~Window() {
    _implDone();
}

Window::Window()
    : onShow()
    , onHide()
    , onClose()
    , onResize()
    , onMaximize()
    , onMinimize()
    , onDemaximize()
    , onDeminimize()
    , onPixelratio()
    , _view(nullptr)
    , _title("")
    , _impl(nullptr)
{
    _implInit();
}

boom::ViewRef Window::view() const {
    return _view;
}

std::string const& Window::title() const {
    return _title;
}

boom::Vec2 Window::pixelratio() const {
    return _implPixelratio();
}

boom::Vec2 Window::size() const {
    return _implSize();
}

bool Window::visible() const {
    return _implVisible();
}

bool Window::closable() const {
    return _implClosable();
}

bool Window::sizable() const {
    return _implSizable();
}

bool Window::maximizable() const {
    return _implMaximizable();
}

bool Window::minimizable() const {
    return _implMinimizable();
}

bool Window::maximized() const {
    return _implMaximized();
}

bool Window::minimized() const {
    return _implMinimized();
}

bool Window::topmost() const {
    return _implTopmost();
}

void Window::center() const {
    _implCenter();
}

void Window::setPosition(boom::Vec2 position) {
    _implSetPosition(position);
}

void Window::setSize(boom::Vec2 size) {
    _implSetSize(size);
}

void Window::setTitle(std::string const& title) {
    _title = title;
    _implSetTitle(title);
}

void Window::setVisible(bool visible) {
    _implSetVisible(visible);
}

void Window::setClosable(bool closable) {
    _implSetClosable(closable);
}

void Window::setSizable(bool sizable) {
    _implSetSizable(sizable);
}

void Window::setMaximizable(bool maximizable) {
    _implSetMaximizable(maximizable);
}

void Window::setMinimizable(bool minimizable) {
    _implSetMinimizable(minimizable);
}

void Window::setMaximized(bool maximized) {
    _implSetMaximized(maximized);
}

void Window::setMinimized(bool minimized) {
    _implSetMinimized(minimized);
}

void Window::setTopmost(bool topmost) {
    _implSetTopmost(topmost);
}

void Window::setView(boom::ViewRef view) {
    _implSetView(view);
    if (_view != nullptr) {
        _view->_detach();
        _view = nullptr;
    }
    if (view != nullptr) {
        _view = view;
        _view->setPosition({ 0.0f, 0.0f });
        _view->setSize(size());
        _view->_attach();
    }
}

void Window::_show() {
    _onShow();
    onShow.emit(boom::GetShared<boom::Window>(this));
}

void Window::_hide() {
    _onHide();
    onHide.emit(boom::GetShared<boom::Window>(this));
}

void Window::_close() {
    _onClose();
    onClose.emit(boom::GetShared<boom::Window>(this));
}

void Window::_resize() {
    _onResize();
    onResize.emit(boom::GetShared<boom::Window>(this));
    if (_view != nullptr) {
        _view->setPosition({ 0.0f, 0.0f });
        _view->setSize(size());
    }
}

void Window::_maximize() {
    _onMaximize();
    onMaximize.emit(boom::GetShared<boom::Window>(this));
}

void Window::_minimize() {
    _onMinimize();
    onMinimize.emit(boom::GetShared<boom::Window>(this));
}

void Window::_demaximize() {
    _onDemaximize();
    onDemaximize.emit(boom::GetShared<boom::Window>(this));
}

void Window::_deminimize() {
    _onDeminimize();
    onDeminimize.emit(boom::GetShared<boom::Window>(this));
}

void Window::_pixelratio() {
    _onPixelratio();
    onPixelratio.emit(boom::GetShared<boom::Window>(this));
}

} /* namespace boom */
