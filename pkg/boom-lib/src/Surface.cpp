#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/View.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Image.hpp>

namespace boom {

Surface::~Surface() {
    _implDone();
}

Surface::Surface(
    boom::SurfaceType type,
    boom::ViewCRef view,
    boom::ImageCRef image
) : _type(type)
  , _view(view)
  , _image(image)
  , _impl(nullptr)
{
    if (type == boom::SurfaceType::View) {
        if (view == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"view\" cannot be nullptr for type \"View\"");
        }
    } else if (type == boom::SurfaceType::Image) {
        if (image == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"image\" cannot be nullptr for type \"Image\"");
        }
    }
    _implInit();
}

void Surface::clear(boom::Color color) {
    _makeCurrent();
    _implClear(color);
}

void Surface::flush() {
    _makeCurrent();
    _implFlush();
}

boom::SurfaceType Surface::type() const {
    return _type;
}

boom::ViewCRef Surface::view() const {
    return _view;
}

boom::ImageCRef Surface::image() const {
    return _image;
}

boom::Vec2 Surface::size() const {
    if (_type == boom::SurfaceType::View) {
        return _view->size();
    } else if (_type == boom::SurfaceType::Image) {
        return _image->size();
    } else {
        return { 0.0f, 0.0f };
    }
}

void Surface::_makeCurrent() const {
    _implMakeCurrent();
}

} /* namespace boom */