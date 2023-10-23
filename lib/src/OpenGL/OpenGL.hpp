#pragma once

#ifdef __APPLE__
    #include <OpenGL/gl3.h>
    #include <OpenGL/gl3ext.h>
#else
    #include <GL/glew.h>
    #include <GL/gl.h>
    // #include <GL/glx.h>
#endif

#include <string>
#include <iostream>

inline void glCheckError_(char const* file, int line) {
    for (;;) {
        GLenum code = glGetError();
        if (code != GL_NO_ERROR) {
            std::string error =
                (code == GL_INVALID_ENUM) ? "INVALID_ENUM" :
                (code == GL_INVALID_VALUE) ? "INVALID_VALUE" :
                (code = GL_INVALID_OPERATION) ? "INVALID_OPERATION" :
                (code = GL_OUT_OF_MEMORY) ? "OUT_OF_MEMORY" :
                (code = GL_INVALID_FRAMEBUFFER_OPERATION) ? "INVALID_FRAMEBUFFER_OPERATION" :
                "Unknown Error";
            std::cerr << "ERROR: OpenGL emited an error: " << error << ", code: " << code << ", file: \"" << file << "\", line: " << line << std::endl;
        } else {
            break;
        }
    }
}

#ifdef NDEBUG
    #define glCheckError() {}
#else
    #define glCheckError() glCheckError_(__FILE__, __LINE__)
#endif
