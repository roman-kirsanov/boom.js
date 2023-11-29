#include <cassert>
#include <Boom/Surface.hpp>
#include <Boom/ContentView.hpp>

namespace boom {

ContentView::~ContentView() {}

ContentView::ContentView()
    : boom::GraphicsView()
    , _children()
    , _hoverPath()
    , _activePath()
    , _async()
    , _texture(nullptr)
    , _surface(nullptr)
    , _viewport({ 0.0f, 0.0f })
    , _container()
    , _propagation(false)
{
    // _impl->w
}

boom::Vec2 ContentView::viewport() const {
    if ((_viewport.width == 0)
    || (_viewport.height == 0)) {
        return size();
    } else {
        return _viewport;
    }
}

boom::Transform const& ContentView::container() const {
    return _container;
}

boom::SurfaceCRef ContentView::surface() const {
    return _surface;
}

void ContentView::setViewport(boom::Vec2 viewport) {
    _viewport = viewport;
}

void ContentView::addChild(boom::NodeRef child) {
    assert(child != nullptr);
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
    }
    _children.push_back(child);
    child->_setView(boom::GetShared<boom::ContentView const>(this));
    child->_attach();
}

void ContentView::removeChild(boom::NodeRef child) {
    assert(child != nullptr);
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->_setView(nullptr);
        child->_detach();
    }
}

void ContentView::insertChild(boom::NodeRef child, std::size_t index) {
    ;
}

void ContentView::replaceChild(boom::NodeRef child, boom::NodeRef child2) {
    ;
}

void ContentView::_onRender() {
    if ((_texture == nullptr)
    || (_texture->size() != viewport())) {
        _texture = boom::MakeShared<boom::Image>(nullptr, viewport());
        _surface = boom::MakeShared<boom::Surface>(boom::SurfaceType::Image, nullptr, _texture);
    }
    _container = (
        boom::Transform()
            // .scale({ 1.0f, -1.0f })
            // .offset({ 0.0f, viewport().height })
    );
    _surface->clear({ 0.0f, 0.0f, 0.0f, 0.0f });
    for (auto& child : _children) {
        child->_render();
    }
    _surface->flush();
}

void ContentView::_onMouseWheel(boom::Vec2 wheel, boom::KeyModifiers modifiers) {
    /// TODO: ...
}

void ContentView::_onMouseMove(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        auto offset = boom::Vec2{ 0.0f, 0.0f };
        auto node = _hitTest(point);
        auto path = (node ? node->path() : std::vector<boom::NodeRef>());
        for (auto& child : _hoverPath) {
            auto const origin = child->rect().origin();
            auto const position = (point - offset - origin);
            if (std::find(path.begin(), path.end(), child) == path.end()) {
                child->_hover = false;
                child->_mouseExit(position, modifiers);
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
                child->_mouseEnter(position, modifiers);
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
            child->_mouseMove(position, modifiers);
            offset += origin;
            if (!_propagation) {
                break;
            }
        }
        _hoverPath = std::move(path);
    });
}

void ContentView::_onLButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
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
                child->_lButtonDown(position, modifiers);
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

void ContentView::_onRButtonDown(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_rButtonDown(position, modifiers);
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
        }
    });
}

void ContentView::_onLButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
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
                child->_lButtonUp(position, modifiers);
                if (std::find(_activePath.begin(), _activePath.end(), child) != _activePath.end()) {
                    child->_mouseClick(position, modifiers);
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

void ContentView::_onRButtonUp(boom::Vec2 position, boom::KeyModifiers modifiers) {
    auto const point = (position * (viewport() / size()));
    _async.push_back([this, point, modifiers]() {
        _propagation = true;
        if (auto node = _hitTest(point)) {
            auto offset = boom::Vec2{ 0.0f, 0.0f };
            auto path = node->path();
            for (auto& child : path) {
                auto const origin = child->rect().origin();
                auto const position = (point - offset - origin);
                child->_rButtonUp(position, modifiers);
                offset += origin;
                if (!_propagation) {
                    break;
                }
            }
        }
    });
}

void ContentView::_onKeyDown(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    /// TODO: ...
}

void ContentView::_onKeyUp(boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
    /// TODO: ...
}

boom::NodeRef ContentView::_hitTest(boom::Vec2 point) {
    // TODO: avoid vector copy...
    auto reversed = std::vector<boom::NodeRef>(
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

boom::NodeRef ContentView::_hitTestNode(boom::NodeRef node, boom::Vec2 point) {
    assert(node != nullptr);
    auto const rect = node->rect();
    auto const scroll = node->scroll();
    auto const point2 = (point - rect.origin() - scroll);
    // TODO: avoid vector copy...
    auto reversed = std::vector<boom::NodeRef>(
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

void ContentView::_update() {
    for (auto& fn : _async) {
        fn();
    }
    _async.clear();
    for (auto& child : _children) {
        child->_update();
    }
}

} /* namespace boom */