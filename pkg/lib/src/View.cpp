#include <Boom/Utilities.hpp>
#include <Boom/View.hpp>

namespace boom {

View::~View() {
    _implDone();
}

View::View()
    : onAttach()
    , onDetach()
    , onResize()
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
    , _windowView(false)
    , _parent(nullptr)
    , _children()
    , _impl(nullptr)
{
    _implInit();
}

std::vector<std::shared_ptr<boom::View>> const& View::children() const {
    return _children;
}

std::shared_ptr<boom::View> View::parent() const {
    return _parent;
}

boom::Vec2 View::position() const {
    return _implPosition();
}

boom::Vec2 View::size() const {
    return _implSize();
}

void View::removeFromParent() {
    if (_parent != nullptr) {
        _parent->removeChild(boom::GetShared<boom::View>(this));
        _parent = nullptr;
    }
}

void View::addChild(std::shared_ptr<boom::View> child) {
    if (child == nullptr) {
        boom::Abort("ERROR: boom::View::addChild() failed: \"child\" cannot be nullptr");
    }
    if (child->_windowView) {
        boom::Abort("ERROR: boom::View::addChild() failed: You cannot add the view attached to a window as a child view");
    }
    child->removeFromParent();
    _children.push_back(child);
    child->_parent = boom::GetShared<boom::View>(this);
    child->_attach();
}

void View::removeChild(std::shared_ptr<boom::View> child) {
    if (child == nullptr) {
        boom::Abort("ERROR: boom::View::removeChild() failed: \"child\" cannot be nullptr");
    }
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->_parent = nullptr;
        child->_detach();
    }
}

void View::replaceChild(std::shared_ptr<boom::View> oldChild, std::shared_ptr<boom::View> newChild) {
    ;
}

void View::insertChild(std::shared_ptr<boom::View> child, std::size_t index) {
    ;
}

void View::setParent(std::shared_ptr<boom::View> parent) {
    if (_windowView) {
        boom::Abort("ERROR: boom::View::setParent() failed: You cannot set the parent for a view which is attached to a window");
    }
    removeFromParent();
    if (parent != nullptr) {
        parent->addChild(boom::GetShared<boom::View>(this));
    }
}

void View::setPosition(boom::Vec2 position) {
    _implSetPosition(position);
}

void View::setSize(boom::Vec2 size) {
    if (_windowView == false) {
        _implSetSize(size);
    }
}

void View::_attach() {
    _onAttach();
    onAttach.emit(boom::GetShared<boom::View>(this));
    for (auto child : _children) {
        child->_attach();
    }
}

void View::_detach() {
    _onDetach();
    onDetach.emit(boom::GetShared<boom::View>(this));
    for (auto child : _children) {
        child->_detach();
    }
}

} /* namespace boom */