#include <iostream>
#include <Boom/Window.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Image.hpp>

namespace boom {

Surface::~Surface() {
    _implDone();
}

Surface::Surface(
    boom::SurfaceType type,
    std::shared_ptr<boom::Window const> window,
    std::shared_ptr<boom::Image const> image
) : _type(type)
  , _window(window)
  , _image(image)
  , _impl(nullptr)
{
    if (type == boom::SurfaceType::Window) {
        if (window == nullptr) {
            std::cerr << "ERROR: boom::Surface::Surface() failed: \"window\" cannot be nullptr for type \"Window\"" << std::endl;
            ::exit(-1);
        }
    } else if (type == boom::SurfaceType::Image) {
        if (image == nullptr) {
            std::cerr << "ERROR: boom::Surface::Surface() failed: \"image\" cannot be nullptr for type \"Image\"" << std::endl;
            ::exit(-1);
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

std::shared_ptr<boom::Window const> Surface::window() const {
    return _window;
}

std::shared_ptr<boom::Image const> Surface::image() const {
    return _image;
}

boom::Vec2 Surface::size() const {
    if (_type == boom::SurfaceType::Window) {
        return (_window->size() * _window->pixelratio());
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
