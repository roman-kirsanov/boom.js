#include <cassert>
#include <iostream>
#include "Shaders.hpp"
#include "OpenGL.hpp"

namespace boom {

Shaders::~Shaders() {
    glDeleteProgram(_shaderProgramId);
    glDeleteShader(_vertexShaderId);
    glDeleteShader(_fragmentShaderId);
}

Shaders::Shaders(char const* vertexShader, char const* fragmentShader)
    : _vertexShaderId(0)
    , _fragmentShaderId(0)
    , _shaderProgramId(0)
{
    assert(vertexShader != NULL);
    assert(fragmentShader != NULL);
    _vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    _fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_vertexShaderId, 1, &vertexShader, NULL);
    glShaderSource(_fragmentShaderId, 1, &fragmentShader, NULL);
    glCompileShader(_vertexShaderId);
    glCompileShader(_fragmentShaderId);
    GLint vertexStatus = 0;
    GLint fragmentStatus = 0;
    bool error = false;
    glGetShaderiv(_vertexShaderId, GL_COMPILE_STATUS, &vertexStatus);
    glGetShaderiv(_fragmentShaderId, GL_COMPILE_STATUS, &fragmentStatus);
    if (vertexStatus != GL_TRUE) {
        char buffer[512] = {0};
        glGetShaderInfoLog(_vertexShaderId, 511, NULL, buffer);
        std::cerr << "ERROR: boom::shaders::shaders() failed: Failed to compile vertex shader: " << buffer << std::endl;
    }
    if (fragmentStatus != GL_TRUE) {
        char buffer[512] = {0};
        glGetShaderInfoLog(_fragmentShaderId, 511, NULL, buffer);
        std::cerr << "ERROR: boom::shaders::shaders() failed: Failed to compile fragment shader: " << buffer << std::endl;
    }
    if (error == true) {
        ::exit(-1);
    }
    _shaderProgramId = glCreateProgram();
    glAttachShader(_shaderProgramId, _vertexShaderId);
    glAttachShader(_shaderProgramId, _fragmentShaderId);
    glLinkProgram(_shaderProgramId);
}

std::uint32_t Shaders::_use() const {
    glUseProgram(_shaderProgramId);
    return _shaderProgramId;
}

} /* namespace boom */
