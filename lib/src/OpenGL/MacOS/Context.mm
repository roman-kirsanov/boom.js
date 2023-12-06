#include <cassert>
#include <iostream>
#include <Boom/Window.hpp>
#include "../../MacOS/Window.hpp"
#include "../OpenGL.hpp"
#include "Context.hpp"

namespace boom {

void Context::_implInit(bool shared) {
    NSOpenGLPixelFormat* format = [[NSOpenGLPixelFormat alloc]
        initWithAttributes: (NSOpenGLPixelFormatAttribute[]){
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion4_1Core,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples,       4,
            0
        }
    ];
    NSOpenGLContext* context = [[NSOpenGLContext alloc]
        initWithFormat: format
          shareContext: (shared ? nil : boom::Context::Shared()->_impl->context)
    ];
    [context setValues: (GLint[]){ 0 } forParameter: NSOpenGLContextParameterSurfaceOpacity];
    _impl = new __ContextImpl{ .context = context };
}

void Context::_implDone() {
    _impl->context = nil;
    delete _impl;
}

void Context::_implMakeCurrent() const {
    [_impl->context makeCurrentContext];
}

void Context::_implFlush() const {
    glFlush();
    [_impl->context flushBuffer];
}

} /* namespace boom */
