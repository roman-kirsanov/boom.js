#pragma once

#include <Boom/Memory.hpp>

struct GLContext;

namespace boom {

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
    ::GLContext* _context;
    void _makeCurrent();
};

} /* namespace boom */

