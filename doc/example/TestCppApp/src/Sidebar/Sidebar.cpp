#include "Sidebar.hpp"

namespace app {

void Sidebar::_onRender() {
    context()->clearColor(1, 0, 0, 1);
    context()->clear(boom::kOpenGLColorBufferBit | boom::kOpenGLDepthBufferBit);
    context()->flush();
}

} /* namespace app */