#include <Boom/OpenGL.hpp>
#include <Boom/Surface.hpp>
#include "Context.hpp"

namespace boom {

struct __SurfaceImpl {
    std::uint32_t frameBufferId;
    std::uint32_t colorBufferId;
    std::uint32_t depthBufferId;
    std::uint32_t textureBufferId;
};

} /* namespace boom */
