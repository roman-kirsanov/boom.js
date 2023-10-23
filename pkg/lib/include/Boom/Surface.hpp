#pragma once

#include <Boom/Color.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Math.hpp>

namespace boom {

struct __SurfaceImpl;

class Paint;
class Image;
class Window;

enum class SurfaceType {
    Window,
    Image
};

class Surface final : public boom::Shared {
public:
    ~Surface();
    Surface(
        boom::SurfaceType,
        std::shared_ptr<boom::Window const>,
        std::shared_ptr<boom::Image const>
    );
    boom::SurfaceType type() const;
    std::shared_ptr<boom::Window const> window() const;
    std::shared_ptr<boom::Image const> image() const;
    boom::Vec2 size() const;
    void clear(boom::Color);
    void flush();
private:
    boom::SurfaceType _type;
    std::shared_ptr<boom::Window const> _window;
    std::shared_ptr<boom::Image const> _image;
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
