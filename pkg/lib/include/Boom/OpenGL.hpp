#pragma once

#include <Boom/Memory.hpp>

namespace boom {

struct __OpenGLImpl;

class Window;
class OpenGL;

auto constexpr OpenGLColorBufferBit = 0x00004000u;
auto constexpr OpenGLDepthBufferBit = 0x00000100u;

struct OpenGLOptions {
    std::optional<std::shared_ptr<boom::OpenGL>> shared;
    std::optional<std::shared_ptr<boom::Window>> window;
    std::optional<std::int32_t> majorVersion;
    std::optional<std::int32_t> minorVersion;
};

class OpenGL final : public boom::Shared {
public:
    OpenGL(boom::OpenGLOptions const& = {});
	void clearColor(float, float, float, float);
	void clear(std::uint32_t);
	void flush();
	void swap();
    virtual ~OpenGL();
private:
    boom::__OpenGLImpl* _impl;
    void _current();
    void _bootstrap();
    void _implInit(boom::OpenGLOptions const&);
    void _implDone();
    void _implSwap();
    void _implCurrent();
    void _implBootstrap();
};

} /* namespace boom */

