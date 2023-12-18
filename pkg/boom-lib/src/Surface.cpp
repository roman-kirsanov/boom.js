#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/View.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Image.hpp>

namespace boom {

Surface::~Surface() {
    _implDone();
}

Surface::Surface(boom::SurfaceOptions const& options)
    : _type(options.type)
    , _view(options.view.value_or(nullptr))
    , _image(options.image.value_or(nullptr))
    , _version(options.version.value_or(boom::OpenGLVersion::CompatibilityProfile_32))
    , _context(nullptr)
    , _impl(nullptr)
{
    if (_type == boom::SurfaceType::View) {
        if (_view == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"view\" cannot be nullptr for type \"View\"");
        }
    } else if (_type == boom::SurfaceType::Image) {
        if (_image == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"image\" cannot be nullptr for type \"Image\"");
        }
    }
    _implInit();
}

boom::OpenGLCRef Surface::context() const {
    return _context;
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

void Surface::current() const {
    _implCurrent();
}

void Surface::clear(boom::Color color) {
    current();
    _implClear(color);
}

void Surface::flush() {
    current();
    _implFlush();
}

void Surface::swap() {
    current();
    _implSwap();
}

} /* namespace boom */
