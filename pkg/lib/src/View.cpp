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
    , _attaching(false)
    , _detaching(false)
    , _resizing(false)
    , _windowView(false)
    , _parent(nullptr)
    , _children()
    , _impl(nullptr)
{
    _implInit();
}

std::vector<boom::ViewRef> const& View::children() const {
    return _children;
}

boom::ViewRef View::parent() const {
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

void View::addChild(boom::ViewRef child) {
    if (child == nullptr) {
        boom::Abort("boom::View::addChild() failed: \"child\" cannot be nullptr");
    }
    if (child->_windowView) {
        boom::Abort("boom::View::addChild() failed: You cannot add the view attached to a window as a child view");
    }
    child->removeFromParent();
    _children.push_back(child);
    child->_parent = boom::GetShared<boom::View>(this);
    _implAddChild(child);
    child->_attach();
}

void View::removeChild(boom::ViewRef child) {
    if (child == nullptr) {
        boom::Abort("boom::View::removeChild() failed: \"child\" cannot be nullptr");
    }
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->_parent = nullptr;
        _implRemoveChild(child);
        child->_detach();
    }
}

void View::replaceChild(boom::ViewRef oldChild, boom::ViewRef newChild) {
    ;
}

void View::insertChild(boom::ViewRef child, std::size_t index) {
    ;
}

void View::setParent(boom::ViewRef parent) {
    if (_windowView) {
        boom::Abort("boom::View::setParent() failed: You cannot set the parent for a view which is attached to a window");
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
    _implSetSize(size);
    _resize();
}

void View::_attach() {
    if (_attaching == false) {
        _attaching = true;
        _onAttach();
        onAttach.emit(boom::GetShared<boom::View>(this));
        _attaching = false;
    }
    for (auto child : _children) {
        child->_attach();
    }
}

void View::_detach() {
    if (_detaching == false) {
        _detaching = true;
        _onDetach();
        onDetach.emit(boom::GetShared<boom::View>(this));
        _detaching = false;
    }
    for (auto child : _children) {
        child->_detach();
    }
}

void View::_resize() {
    if (_resizing == false) {
        _resizing = true;
        _onResize();
        onResize.emit(boom::GetShared<boom::View>(this));
        _resizing = false;
    }
}

} /* namespace boom */