#include "Header.hpp"

namespace app {

void Header::_onRender() {
    context()->clearColor(0, 1, 0, 1);
    context()->clear(boom::kOpenGLColorBufferBit | boom::kOpenGLDepthBufferBit);
    context()->flush();
}

} /* namespace app */