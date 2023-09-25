#include <Boom/Surface.hpp>
#include "Context.hpp"
#include "OpenGL.hpp"

namespace boom {

struct __SurfaceImplImpl;

struct __SurfaceImpl {
    std::shared_ptr<boom::Context const> context;
    GLuint frameBufferId;
    GLuint colorBufferId;
    GLuint depthBufferId;
    GLuint textureBufferId;
    boom::__SurfaceImplImpl* impl;
};

} /* namespace boom */
