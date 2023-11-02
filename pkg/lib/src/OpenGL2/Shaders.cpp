#include <cassert>
#include <iostream>
#include "Shaders.hpp"

namespace boom {

Shaders::~Shaders() {
    _context->deleteProgram(_shaderProgramId);
    _context->deleteShader(_vertexShaderId);
    _context->deleteShader(_fragmentShaderId);
}

Shaders::Shaders(std::shared_ptr<boom::OpenGL> context, char const* vertexShader, char const* fragmentShader)
    : _context(context)
    , _vertexShaderId(0)
    , _fragmentShaderId(0)
    , _shaderProgramId(0)
{
    assert(context != nullptr);
    assert(vertexShader != nullptr);
    assert(fragmentShader != nullptr);
    _vertexShaderId = _context->createShader(boom::OpenGLVertexShader);
    _fragmentShaderId = _context->createShader(boom::OpenGLFragmentShader);
    _context->shaderSource(_vertexShaderId, 1, &vertexShader, nullptr);
    _context->shaderSource(_fragmentShaderId, 1, &fragmentShader, nullptr);
    _context->compileShader(_vertexShaderId);
    _context->compileShader(_fragmentShaderId);
    auto vertexStatus = 0;
    auto fragmentStatus = 0;
    bool error = false;
    _context->getShaderiv(_vertexShaderId, boom::OpenGLCompileStatus, &vertexStatus);
    _context->getShaderiv(_fragmentShaderId, boom::OpenGLCompileStatus, &fragmentStatus);
    if (vertexStatus != boom::OpenGLTrue) {
        char buffer[512] = {0};
        _context->getShaderInfoLog(_vertexShaderId, 511, nullptr, buffer);
        std::cerr << "ERROR: boom::shaders::shaders() failed: Failed to compile vertex shader: " << buffer << std::endl;
    }
    if (fragmentStatus != boom::OpenGLTrue) {
        char buffer[512] = {0};
        _context->getShaderInfoLog(_fragmentShaderId, 511, nullptr, buffer);
        std::cerr << "ERROR: boom::shaders::shaders() failed: Failed to compile fragment shader: " << buffer << std::endl;
    }
    if (error == true) {
        ::exit(-1);
    }
    _shaderProgramId = _context->createProgram();
    _context->attachShader(_shaderProgramId, _vertexShaderId);
    _context->attachShader(_shaderProgramId, _fragmentShaderId);
    _context->linkProgram(_shaderProgramId);
}

std::uint32_t Shaders::_use() const {
    _context->useProgram(_shaderProgramId);
    return _shaderProgramId;
}

} /* namespace boom */
