#include <cassert>
#include <iostream>
#include <windows.h>
#include <GL/GL.h>
#include "../OpenGL.hpp"

struct GLContext {
    HDC hdc;
    HGLRC hglrc;
};

GLContext* glCreateContext(GLContextOptions const& options) {
    return nullptr;
}

void glDestroyContext(GLContext* context) {
    if (context == nullptr) {
        std::cerr << "ERROR: glDestroyContext() failed: \"context\" cannot be nullptr" << std::endl;
        std::abort();
    }
    ;
}

void glMakeCurrent(GLContext* context) {
    if (context != nullptr) {
        wglMakeCurrent(context->hdc, context->hglrc);
    } else {
        wglMakeCurrent(nullptr, nullptr);
    }
}

void glSwapBuffers(GLContext* context) {
    if (context == nullptr) {
        std::cerr << "ERROR: glSwapBuffers() failed: \"context\" cannot be nullptr" << std::endl;
        std::abort();
    }
    SwapBuffers(context->hdc);
}

void* glLoadFunc(char const* name) {
    assert(name != nullptr);
    return wglGetProcAddress(name);
}