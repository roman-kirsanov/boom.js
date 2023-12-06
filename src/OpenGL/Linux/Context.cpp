#include <cassert>
#include <iostream>
#include <Boom/Window.hpp>
#include "../../Win32/Window.hpp"
#include "../OpenGL.hpp"
#include "Context.hpp"

namespace boom {

void Context::_implInit(bool shared) {
    ;
    _impl = new __ContextImpl{};
}

void Context::_implDone() {
    ;
    delete _impl;
}

void Context::_implMakeCurrent() const {
    ;
}

void Context::_implFlush() const {
    glFlush();
    ;
}

} /* namespace boom */
