#pragma once

#include <Boom/Color.hpp>
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

class Surface final : public boom::Object {
public:
    ~Surface();
    Surface(
        boom::SurfaceType,
        boom::ViewCRef,
        boom::ImageCRef
    );
    boom::SurfaceType type() const;
    boom::ViewCRef view() const;
    boom::ImageCRef image() const;
    boom::Vec2 size() const;
    void clear(boom::Color);
    void flush();
private:
    boom::SurfaceType _type;
    boom::ViewCRef _view;
    boom::ImageCRef _image;
    __SurfaceImpl* _impl;
    void _makeCurrent() const;
    void _implInit();
    void _implDone();
    void _implMakeCurrent() const;
    void _implClear(boom::Color);
    void _implFlush();
    friend boom::Paint;
};

} /* namespace boom */
