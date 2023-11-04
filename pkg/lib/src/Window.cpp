#include <cassert>
#include <iostream>
#include <Boom/App.hpp>
#include <Boom/Window.hpp>
#include <Boom/Surface.hpp>

namespace boom {

Window::~Window() {
    _implDone();

    if (auto app = boom::App::Current()) {
        app->onPoll.remove(_subscr);
    }
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
    , onRender()
    , onMouseMove()
    , onMouseEnter()
    , onMouseExit()
    , onMouseWheel()
    , onMouseClick()
    , onLButtonDown()
    , onRButtonDown()
    , onLButtonUp()
    , onRButtonUp()
    , onKeyDown()
    , onKeyUp()
    , _title("")
    , _subscr(0)
    , _surface(nullptr)
    , _brush(nullptr)
    , _paint(nullptr)
    , _children()
    , _hoverPath()
    , _activePath()
    , _async()
    , _viewportTexture(nullptr)
    , _viewportSurface(nullptr)
    , _viewport({ 0.0f, 0.0f })
    , _container()
    , _propagation(false)
    , _impl(nullptr)
{
    _implInit();
}

void Window::_onReady() {
    auto selfw = boom::GetWeak<boom::Window>(this);
    auto selfs = boom::GetShared<boom::Window const>(this);
    if (auto app = boom::App::Current()) {
        _subscr = app->onPoll([selfw]() {
            if (auto win = selfw.lock()) {
                win->_update();
                win->_render();
            }
        });
    }
    _surface = boom::MakeShared<boom::Surface>(boom::SurfaceType::Window, selfs, nullptr);
    _brush = boom::MakeShared<boom::ImageBrush>();
    _paint = boom::MakeShared<boom::Paint>();
    _paint->setFillBrush(_brush);
}

std::shared_ptr<boom::Surface const> Window::surface() const {
    return _viewportSurface;
}

boom::Transform const& Window::container() const {
    return _container;
}

std::string const& Window::title() const {
    return _title;
}

boom::Vec2 Window::pixelratio() const {
    return _implPixelratio();
}

boom::Vec2 Window::viewport() const {
    if ((_viewport.width == 0)
    || (_viewport.height == 0)) {
        return size();
    } else {
        return _viewport;
    }
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

void Window::setViewport(boom::Vec2 size) {
    _viewport = size;
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

void Window::addChild(std::shared_ptr<boom::Node> child) {
    assert(child != nullptr);
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
    }
    _children.push_back(child);
    child->_setWindow(boom::GetShared<boom::Window const>(this));
    child->_attach();
}

void Window::removeChild(std::shared_ptr<boom::Node> child) {
    assert(child != nullptr);
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->_setWindow(nullptr);
        child->_detach();
    }
}

void Window::insertChild(std::shared_ptr<boom::Node> child, std::size_t index) {
    ;
}

void Window::replaceChild(std::shared_ptr<boom::Node> child, std::shared_ptr<boom::Node> child2) {
    ;
}

std::shared_ptr<boom::Node> Window::_hitTest(boom::Vec2 point) {
    // TODO: avoid vector copy...
    auto reversed = std::vector<std::shared_ptr<boom::Node>>(
        _children.rbegin(),
        _children.rend()
    );
    for (auto& child : reversed) {
        auto node = _hitTestNode(child, point);
        if (node != nullptr) {
            return node;
        }
    }
    return nullptr;
}

std::shared_ptr<boom::Node> Window::_hitTestNode(std::shared_ptr<boom::Node> node, boom::Vec2 point) {
    assert(node != nullptr);
    auto const rect = node->rect();
    auto const scroll = node->scroll();
    auto const point2 = (point - rect.origin() - scroll);
    // TODO: avoid vector copy...
    auto reversed = std::vector<std::shared_ptr<boom::Node>>(
        node->_children.rbegin(),
        node->_children.rend()
    );
    for (auto& child : reversed) {
        if (auto found = _hitTestNode(child, point2)) {
            return found;
        }
    }
    if (point.inRect(rect)) {
        return node;
    } else {
        return nullptr;
    }
}

void Window::_show() {
    _onShow();
    onShow.emit();
}

void Window::_hide() {
    _onHide();
    onHide.emit();
}

void Window::_close() {
    _onClose();
    onClose.emit();
}

void Window::_resize(boom::Vec2 size) {
    _onResize();
    onResize.emit();
}

void Window::_maximize() {
    _onMaximize();
    onMaximize.emit();
}

void Window::_minimize() {
    _onMinimize();
    onMinimize.emit();
}

void Window::_demaximize() {
    _onDemaximize();
    onDemaximize.emit();
}

void Window::_deminimize() {
    _onDeminimize();
    onDeminimize.emit();
}

void Window::_pixelratio(boom::Vec2 pixelratio) {
    _onPixelratio();
    onPixelratio.emit();
}

void Window::_mouseWheel(boom::Vec2 wheel, boom::KeyModifiers modifiers) {
    _onMouseWheel(wheel, modifiers);
    onMouseWheel.emit(wheel, modifiers);
    /// TODO: ...
}

void Window::_mouseMove(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _onMouseMove(point, modifiers);
    onMouseMove.emit(point, modifiers);
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        auto offset = boom::Vec2{ 0.0f, 0.0f };
        auto node = _hitTest(point);
        auto path = (node ? node->path() : std::vector<std::shared_ptr<boom::Node>>());
        for (auto& child : _hoverPath) {
            auto const origin = child->rect().origin();
            auto const position = (point - offset - origin);
            if (std::find(path.begin(), path.end(), child) == path.end()) {
                child->_hover = false;
                child->_onMouseExit(position, modifiers);
                child->onMouseExit.emit(position, modifiers);
            }
            offset += origin;
            if (!_propagation) {
                break;
            }
        }
        offset = { 0.0f, 0.0f };
        for (auto& child : path) {
            auto const origin = child->rect().origin();
            auto const position = (point - offset - origin);
            if (std::find(_hoverPath.begin(), _hoverPath.end(), child) == _hoverPath.end()) {
                child->_hover = true;
                child->_onMouseEnter(position, modifiers);
                child->onMouseEnter.emit(position, modifiers);
            }
            offset += origin;
            if (!_propagation) {
                break;
            }
        }
        offset = { 0.0f, 0.0f };
        for (auto& child : path) {
            auto const origin = child->rect().origin();
            auto const position = (point - offset - origin);
            child->_hover = true;
            child->_onMouseMove(position, modifiers);
            child->onMouseMove.emit(position, modifiers);
            offset += origin;
            if (!_propagation) {
                break;
            }
        }
        _hoverPath = std::move(path);
    });
}

void Window::_lButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _onLButtonDown(point, modifiers);
    onLButtonDown.emit(point, modifiers);
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : _activePath) {
                if (std::find(path.begin(), path.end(), child) == path.end()) {
                    child->_active = false;
                }
            }
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_active = true;
                child->_onLButtonDown(position, modifiers);
                child->onLButtonDown.emit(position, modifiers);
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
            _activePath = path;
        } else {
            for (auto& child : _activePath) {
                child->_active = false;
            }
            _activePath = {};
        }
    });
}

void Window::_rButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _onRButtonDown(point, modifiers);
    onRButtonDown.emit(point, modifiers);
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_onRButtonDown(position, modifiers);
                child->onRButtonDown.emit(position, modifiers);
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
        }
    });
}

void Window::_lButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _onLButtonUp(point, modifiers);
    onLButtonUp.emit(point, modifiers);
    _async.push_back([this, point, modifiers]() {
        for (auto& child : _activePath) {
            child->_active = false;
        }
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_onLButtonUp(position, modifiers);
                child->onLButtonUp.emit(position, modifiers);
                if (std::find(_activePath.begin(), _activePath.end(), child) != _activePath.end()) {
                    child->_onMouseClick(position, modifiers);
                    child->onMouseClick.emit(position, modifiers);
                }
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
        }
        _activePath = {};
    });
}

void Window::_rButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _onRButtonUp(point, modifiers);
    onRButtonUp.emit(point, modifiers);
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_onRButtonUp(position, modifiers);
                child->onRButtonUp.emit(position, modifiers);
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
        }
    });
}

void Window::_keyDown(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    _onKeyDown(key, modifiers, input);
    onKeyDown.emit(key, modifiers, input);
    /// TODO: ...
}

void Window::_keyUp(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    _onKeyUp(key, modifiers, input);
    onKeyUp.emit(key, modifiers, input);
    /// TODO: ...
}

void Window::_update() {
    for (auto& fn : _async) {
        fn();
    }
    _async.clear();
    for (auto& child : _children) {
        child->_update();
    }
}

void Window::_render() {
    if (viewport() == _surface->size()) {
        _viewportTexture = nullptr;
        _viewportSurface = _surface;
    } else {
        if ((_viewportTexture == nullptr)
        || (_viewportTexture->size() != viewport())) {
            _viewportTexture = boom::MakeShared<boom::Image>(nullptr, viewport());
            _viewportSurface = boom::MakeShared<boom::Surface>(boom::SurfaceType::Image, nullptr, _viewportTexture);
        }
    }
    _container = (
        boom::Transform()
            // .scale({ 1.0f, -1.0f })
            // .offset({ 0.0f, viewport().height })
    );
    _viewportSurface->clear({ 0.0f, 0.0f, 0.0f, 0.0f });
    for (auto& child : _children) {
        child->_render();
    }
    _onRender();
    onRender.emit();
    _viewportSurface->flush();
    if (_viewportTexture != nullptr) {
        _surface->clear({ 0.0f, 0.0f, 0.0f, 0.0f });
        _brush->setImage(_viewportTexture);
        _brush->setImagePositionX(boom::ImagePosition::Stretch);
        _brush->setImagePositionY(boom::ImagePosition::Stretch);
        _brush->setImageFlipY(true);
        _paint->setRect({ 0.0f, 0.0f, _surface->size().width, _surface->size().height });
        _paint->fill(_surface);
        _surface->flush();
    }
}

} /* namespace boom */
