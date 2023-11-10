#include <Boom/Utilities.hpp>
#include "View.hpp"

namespace boom {

std::intptr_t View::_ImplViewProc(void* hwnd, std::uint32_t message, std::uintptr_t wparam,  std::intptr_t lparam) {
    boom::View* view = (boom::View*)GetWindowLongPtr((HWND)hwnd, GWLP_USERDATA);
    if (view != nullptr) {
        ;
    }
    return DefWindowProc((HWND)hwnd, message, wparam, lparam);
}

void View::_implInit() {
    static auto const VIEW_CLASS_NAME = "BoomViewClass";
    static auto const VIEW_CLASS_DEF = WNDCLASSA{
        .lpfnWndProc = (WNDPROC)boom::View::_ImplViewProc,
        .hInstance = GetModuleHandle(nullptr),
        .hCursor = LoadCursor(nullptr, IDC_ARROW),
        .lpszClassName = VIEW_CLASS_NAME
    };
    static auto classRegistered = false;
    if (classRegistered == false) {
        classRegistered = true;
        RegisterClassA(&VIEW_CLASS_DEF);
    }
    auto window = CreateWindowExA(
        0,
        VIEW_CLASS_NAME,
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
        boom::Abort("boom::View::View() failed: Failed to create a window");
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

void View::_implAddChild(std::shared_ptr<boom::View> child) {
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

void View::_implRemoveChild(std::shared_ptr<boom::View> child) {
    if (auto parent = GetParent(child->_impl->window)) {
        ShowWindow(child->_impl->window, SW_HIDE);
        SetWindowLongPtr(child->_impl->window, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetParent(child->_impl->window, nullptr);
    }
}

void View::_implReplaceChild(std::shared_ptr<boom::View>, std::shared_ptr<boom::View>) {

}

void View::_implInsertChild(std::shared_ptr<boom::View>, std::size_t) {

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

} /* namespace boom */