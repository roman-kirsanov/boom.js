#include <cassert>
#include <iostream>
#include <Boom/Brush.hpp>
#include <Boom/Image.hpp>
#include <Boom/Surface.hpp>
#include <Boom/ContentView.hpp>
#include <Boom/Node.hpp>

namespace boom {

Node::~Node() {
    removeFromParent();
}

Node::Node()
    : onAttach()
    , onDetach()
    , onResize()
    , onUpdate()
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
    , onFocus()
    , onBlur()
    , _tag()
    , _parent(nullptr)
    , _children()
    , _view(nullptr)
    , _container()
    , _transform()
    , _scale({ 1.0f, 1.0f })
    , _anchor({ 0.5f, 0.5f })
    , _position({ 0.0f, 0.0f })
    , _scroll({ 0.0f, 0.0f })
    , _size({ 0.0f, 0.0f })
    , _rect({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _rotate(0.0f)
    , _clip(false)
    , _resizing(false)
    , _hover(false)
    , _active(false)
    , _focused(false)
    , _focusedWithin(false)
    , _strokeWidth(1.0f)
    , _strokeRadius(0.0f)
    , _strokeColor({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _fillColor({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _image(nullptr)
    , _imageSlice(std::nullopt)
    , _imageNPatch({ 0.0f, 0.0f, 0.0f, 0.0f })
    , _imageFilterMin(boom::ImageFilter::Nearest)
    , _imageFilterMag(boom::ImageFilter::Nearest)
    , _imagePositionX(boom::ImagePosition::Stretch)
    , _imagePositionY(boom::ImagePosition::Stretch)
    , _imageRepeatX(false)
    , _imageRepeatY(false)
    , _imageFlipX(false)
    , _imageFlipY(false)
    , _fillPaint(nullptr)
    , _strokePaint(nullptr)
    , _imagePaint(nullptr)
{}

std::string const& Node::tag() const {
    return _tag;
}

boom::NodeRef Node::parent() {
    return _parent;
}

boom::NodeCRef Node::parent() const {
    return _parent;
}

std::vector<boom::NodeRef> const& Node::children() const {
    return _children;
}

std::vector<boom::NodeCRef> Node::path() const {
    auto ret = std::vector<boom::NodeCRef>();
    auto next = boom::GetShared<boom::Node>(this);
    while (next != nullptr) {
        ret.push_back(next);
        next = next->_parent;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::vector<boom::NodeRef> Node::path() {
    auto ret = std::vector<boom::NodeRef>();
    auto next = boom::GetShared<boom::Node>(this);
    while (next != nullptr) {
        ret.push_back(next);
        next = next->_parent;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

boom::ContentViewCRef Node::view() const {
    return _view;
}

boom::Transform const& Node::container() const {
    return _container;
}

boom::Transform const& Node::transform() const {
    return _transform;
}

boom::Vec2 Node::scale() const {
    return _scale;
}

boom::Vec2 Node::anchor() const {
    return _anchor;
}

boom::Vec2 Node::position() const {
    return _position;
}

boom::Vec2 Node::scroll() const {
    return _scroll;
}

boom::Vec2 Node::size() const {
    return _size;
}

boom::Vec4 Node::rect() const {
    return _rect;
}

float Node::rotate() const {
    return _rotate;
}

bool Node::clip() const {
    return _clip;
}

bool Node::hover() const {
    return _hover;
}

bool Node::active() const {
    return _active;
}

bool Node::focused() const {
    return _focused;
}

bool Node::focusedWithin() const {
    return _focusedWithin;
}

float Node::strokeWidth() const {
    return _strokeWidth;
}

float Node::strokeRadius() const {
    return _strokeRadius;
}

boom::Color Node::strokeColor() const {
    return _strokeColor;
}

boom::Color Node::fillColor() const {
    return _fillColor;
}

boom::ImageCRef Node::image() const {
    return _image;
}

std::optional<boom::Vec4> Node::imageSlice() const {
    return _imageSlice;
}

boom::ImageNPatch Node::imageNPatch() const {
    return _imageNPatch;
}

boom::ImageFilter Node::imageFilterMin() const {
    return _imageFilterMin;
}

boom::ImageFilter Node::imageFilterMag() const {
    return _imageFilterMag;
}

boom::ImagePosition Node::imagePositionX() const {
    return _imagePositionX;
}

boom::ImagePosition Node::imagePositionY() const {
    return _imagePositionY;
}

bool Node::imageRepeatX() const {
    return _imageRepeatX;
}

bool Node::imageRepeatY() const {
    return _imageRepeatY;
}

bool Node::imageFlipX() const {
    return _imageFlipX;
}

bool Node::imageFlipY() const {
    return _imageFlipY;
}

void Node::removeFromParent() {
    if (_parent != nullptr) {
        _parent->removeChild(boom::GetShared<boom::Node>(this));
        _parent = nullptr;
    }
}

void Node::addChild(boom::NodeRef child) {
    assert(child != nullptr);
    child->removeFromParent();
    _children.push_back(child);
    child->_parent = boom::GetShared<boom::Node>(this);
    child->_setView(_view);
    child->_attach();
    child->_fillPaint = nullptr;
    child->_strokePaint = nullptr;
    child->_imagePaint = nullptr;
}

void Node::removeChild(boom::NodeRef child) {
    assert(child != nullptr);
    auto pos = std::find(_children.begin(), _children.end(), child);
    if (pos != _children.end()) {
        _children.erase(pos);
        child->_parent = nullptr;
        child->_setView(nullptr);
        child->_detach();
        child->_fillPaint = nullptr;
        child->_strokePaint = nullptr;
        child->_imagePaint = nullptr;
    }
}

void Node::insertChild(boom::NodeRef child, std::size_t index) {
    ;
}

void Node::replaceChild(boom::NodeRef child, boom::NodeRef child2) {
    ;
}

void Node::setTag(std::string const& tag) {
    _tag = tag;
}

void Node::setTag(std::string && tag) {
    _tag = std::move(tag);
}

void Node::setParent(boom::NodeRef parent) {
    removeFromParent();
    if (parent != nullptr) {
        parent->addChild(boom::GetShared<boom::Node>(this));
    }
}

void Node::setScale(boom::Vec2 scale) {
    if (_scale != scale) {
        _scale = scale;
    }
}

void Node::setAnchor(boom::Vec2 anchor) {
    if (_anchor != anchor) {
        _anchor = anchor;
        _rect = {
            (_position.x - (_size.width * _anchor.x)),
            (_position.y - (_size.height * _anchor.y)),
            _size.width,
            _size.height
        };
        _fillPaint = nullptr;
        _strokePaint = nullptr;
        _imagePaint = nullptr;
    }
}

void Node::setPosition(boom::Vec2 position) {
    if (_position != position) {
        _position = position;
        _rect = {
            (_position.x - (_size.width * _anchor.x)),
            (_position.y - (_size.height * _anchor.y)),
            _size.width,
            _size.height
        };
        _fillPaint = nullptr;
        _strokePaint = nullptr;
        _imagePaint = nullptr;
    }
}

void Node::setScroll(boom::Vec2 scroll) {
    if (_scroll != scroll) {
        _scroll = scroll;
        _fillPaint = nullptr;
        _strokePaint = nullptr;
        _imagePaint = nullptr;
    }
}

void Node::setSize(boom::Vec2 size) {
    if (_size != size) {
        _size = size;
        _rect = {
            (_position.x - (_size.width * _anchor.x)),
            (_position.y - (_size.height * _anchor.y)),
            _size.width,
            _size.height
        };
        _fillPaint = nullptr;
        _strokePaint = nullptr;
        _imagePaint = nullptr;
        if (_resizing == false) {
            _resizing = true;
            _onResize();
            onResize.emit();
            _resizing = false;
        }
    }
}

void Node::setRotate(float rotate) {
    if (_rotate != rotate) {
        _rotate = rotate;
    }
}

void Node::setClip(bool clip) {
    if (_clip != clip) {
        _clip = clip;
    }
}

void Node::setStrokeWidth(float strokeWidth) {
    if (_strokeWidth != strokeWidth) {
        _strokeWidth = strokeWidth;
        _strokePaint = nullptr;
    }
}

void Node::setStrokeRadius(float strokeRadius) {
    if (_strokeRadius != strokeRadius) {
        _strokeRadius = strokeRadius;
        _strokePaint = nullptr;
    }
}

void Node::setStrokeColor(boom::Color strokeColor) {
    if (_strokeColor != strokeColor) {
        _strokeColor = strokeColor;
        _strokePaint = nullptr;
    }
}

void Node::setFillColor(boom::Color fillColor) {
    if (_fillColor != fillColor) {
        _fillColor = fillColor;
        _fillPaint = nullptr;
    }
}

void Node::setImage(boom::ImageCRef image) {
    if (_image != image) {
        _image = image;
        _imagePaint = nullptr;
    }
}

void Node::setImageSlice(std::optional<boom::Vec4> imageSlice) {
    if (_imageSlice != imageSlice) {
        _imageSlice = imageSlice;
        _imagePaint = nullptr;
    }
}

void Node::setImageSlice(boom::Vec4 imageSlice) {
    if (_imageSlice != imageSlice) {
        _imageSlice = imageSlice;
        _imagePaint = nullptr;
    }
}

void Node::setImageNPatch(boom::ImageNPatch imageNPatch) {
    if (_imageNPatch != imageNPatch) {
        _imageNPatch = imageNPatch;
        _imagePaint = nullptr;
    }
}

void Node::setImageFilterMin(boom::ImageFilter imageFilterMin) {
    if (_imageFilterMin != imageFilterMin) {
        _imageFilterMin = imageFilterMin;
        _imagePaint = nullptr;
    }
}

void Node::setImageFilterMag(boom::ImageFilter imageFilterMag) {
    if (_imageFilterMag != imageFilterMag) {
        _imageFilterMag = imageFilterMag;
        _imagePaint = nullptr;
    }
}

void Node::setImagePositionX(boom::ImagePosition imagePositionX) {
    if (_imagePositionX != imagePositionX) {
        _imagePositionX = imagePositionX;
        _imagePaint = nullptr;
    }
}

void Node::setImagePositionY(boom::ImagePosition imagePositionY) {
    if (_imagePositionY != imagePositionY) {
        _imagePositionY = imagePositionY;
        _imagePaint = nullptr;
    }
}

void Node::setImageRepeatX(bool imageRepeatX) {
    if (_imageRepeatX != imageRepeatX) {
        _imageRepeatX = imageRepeatX;
        _imagePaint = nullptr;
    }
}

void Node::setImageRepeatY(bool imageRepeatY) {
    if (_imageRepeatY != imageRepeatY) {
        _imageRepeatY = imageRepeatY;
        _imagePaint = nullptr;
    }
}

void Node::setImageFlipX(bool imageFlipX) {
    if (_imageFlipX != imageFlipX) {
        _imageFlipX = imageFlipX;
        _imagePaint = nullptr;
    }
}

void Node::setImageFlipY(bool imageFlipY) {
    if (_imageFlipY != imageFlipY) {
        _imageFlipY = imageFlipY;
        _imagePaint = nullptr;
    }
}

void Node::_setView(boom::ContentViewCRef view) {
    _view = view;
    _fillPaint = nullptr;
    _strokePaint = nullptr;
    _imagePaint = nullptr;
    for (auto& child : _children) {
        child->_setView(view);
    }
}

void Node::_attach() {
    _onAttach();
    onAttach.emit();
    for (auto child : _children) {
        child->_attach();
    }
}

void Node::_detach() {
    _onDetach();
    onDetach.emit();
    for (auto child : _children) {
        child->_detach();
    }
}

void Node::_update() {
    _onUpdate();
    onUpdate.emit();
    for (auto child : _children) {
        child->_update();
    }
}

void Node::_render() {
    assert(_view != nullptr);
    auto parentContainer = (_parent ? _parent->container() : _view->container());
    _transform = (
        boom::Transform()
            .offset(_position * -1.0f)
            .rotate(_rotate)
            .offset(_position)
    );
    _container = (
        boom::Transform()
            .scale(_scale)
            .offset(_rect.origin())
            .offset(_scroll)
            * parentContainer
            * _transform
    );
    if (_fillColor.alpha > 0) {
        if (_fillPaint == nullptr) {
            auto brush = boom::MakeShared<boom::SolidBrush>();
            brush->setColor(_fillColor);

            _fillPaint = boom::MakeShared<boom::Paint>();
            _fillPaint->setFillBrush(brush);
            _fillPaint->addRect(_rect, _strokeRadius);
        }
        _fillPaint->setTransform(parentContainer * _transform);
        _fillPaint->fill(view()->surface());
    }
    if ((_strokeColor.alpha > 0)
    && (_strokeWidth > 0.0f)) {
        if (_strokePaint == nullptr) {
            auto brush = boom::MakeShared<boom::SolidBrush>();
            brush->setColor(_strokeColor);

            _strokePaint = boom::MakeShared<boom::Paint>();
            _strokePaint->setStrokeBrush(brush);
            _strokePaint->setStrokeWidth(_strokeWidth);
            _strokePaint->addRect(_rect.zoom({ _strokeWidth / 2.0f, _strokeWidth / 2.0f }), _strokeRadius);
        }
        _strokePaint->setTransform(parentContainer * _transform);
        _strokePaint->stroke(view()->surface());
    }
    if (_image != nullptr) {
        if (_imagePaint == nullptr) {
            auto brush = boom::MakeShared<boom::ImageBrush>();
            brush->setImage(_image);
            brush->setImageSlice(_imageSlice);
            brush->setImageNPatch(_imageNPatch);
            brush->setImageFilterMin(_imageFilterMin);
            brush->setImageFilterMag(_imageFilterMag);
            brush->setImagePositionX(_imagePositionX);
            brush->setImagePositionY(_imagePositionY);
            brush->setImageRepeatX(_imageRepeatX);
            brush->setImageRepeatY(_imageRepeatY);
            brush->setImageFlipX(_imageFlipX);
            brush->setImageFlipY(_imageFlipY);

            _imagePaint = boom::MakeShared<boom::Paint>();
            _imagePaint->setFillBrush(brush);
            _imagePaint->addRect(_rect);
        }
        _imagePaint->setTransform(parentContainer * _transform);
        _imagePaint->fill(view()->surface());
    }
    _onRender();
    onRender.emit();
    for (auto child : _children) {
        child->_render();
    }
}

} /* namespace boom */
