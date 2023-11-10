#include "Content.hpp"

namespace app {

void Content::_onRender() {
    context()->clearColor(0, 0, 1, 1);
    context()->clear(boom::kOpenGLColorBufferBit | boom::kOpenGLDepthBufferBit);
    context()->flush();
}

} /* namespace app */