#pragma once

#include <optional>
#include <Boom/Color.hpp>
#include <Boom/OpenGL.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Math.hpp>

namespace boom {

struct __SurfaceImpl;

class Paint;
class Image;
class View;
class Surface;

using ViewRef = std::shared_ptr<boom::View>;
using ViewCRef = std::shared_ptr<boom::View const>;
using ImageRef = std::shared_ptr<boom::Image>;
using ImageCRef = std::shared_ptr<boom::Image const>;
using SurfaceRef = std::shared_ptr<boom::Surface>;
using SurfaceCRef = std::shared_ptr<boom::Surface const>;
using SurfaceWRef = std::weak_ptr<boom::Surface>;
using SurfaceCWRef = std::weak_ptr<boom::Surface const>;

enum class SurfaceType {
    View,
    Image
};

struct SurfaceOptions {
    boom::SurfaceType type;
    std::optional<boom::ImageCRef> image;
    std::optional<boom::ViewCRef> view;
    std::optional<boom::OpenGLVersion> version;
};

class Surface final : public boom::Object {
public:
    ~Surface();
    Surface(boom::SurfaceOptions const&);
    boom::OpenGLCRef context() const;
    boom::SurfaceType type() const;
    boom::ViewCRef view() const;
    boom::ImageCRef image() const;
    boom::Vec2 size() const;
    void current() const;
    void clear(boom::Color);
    void flush();
    void swap();
private:
    boom::SurfaceType _type;
    boom::ViewCRef _view;
    boom::ImageCRef _image;
    boom::OpenGLCRef _context;
    boom::OpenGLVersion _version;
    __SurfaceImpl* _impl;
    void _implInit();
    void _implDone();
    void _implCurrent() const;
    void _implClear(boom::Color);
    void _implFlush();
    void _implSwap();
    friend boom::Paint;
};

} /* namespace boom */
