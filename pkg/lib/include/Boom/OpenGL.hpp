#pragma once

#include <Boom/Memory.hpp>

namespace boom {

struct __OpenGLImpl;

auto constexpr OpenGLColorBufferBit = 0x00004000;
auto constexpr OpenGLDepthBufferBit = 0x00000100;

struct OpenGLOptions {
    std::optional<std::int32_t> majorVersion;
    std::optional<std::int32_t> minorVersion;
    std::optional<void*> window;
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
    void* _implLoadFunc(char const*);
};

} /* namespace boom */

