#include <cassert>
#include <iostream>
#include <Boom/Shaders.hpp>

namespace boom {

Shaders::~Shaders() {
    _context->deleteProgram(_shaderProgramId);
    _context->deleteShader(_vertexShaderId);
    _context->deleteShader(_fragmentShaderId);
}

Shaders::Shaders(boom::OpenGLCRef context, char const* vertexShader, char const* fragmentShader)
    : _context(context)
    , _vertexShaderId(0)
    , _fragmentShaderId(0)
    , _shaderProgramId(0)
{
    assert(context != nullptr);
    assert(vertexShader != nullptr);
    assert(fragmentShader != nullptr);
    _vertexShaderId = _context->createShader(boom::kOpenGLVertexShader);
    _fragmentShaderId = _context->createShader(boom::kOpenGLFragmentShader);
    _context->shaderSource(_vertexShaderId, 1, &vertexShader, nullptr);
    _context->shaderSource(_fragmentShaderId, 1, &fragmentShader, nullptr);
    _context->compileShader(_vertexShaderId);
    _context->compileShader(_fragmentShaderId);
    auto error = false;
    auto vertexStatus = 0;
    auto fragmentStatus = 0;
    _context->getShaderiv(_vertexShaderId, boom::kOpenGLCompileStatus, &vertexStatus);
    _context->getShaderiv(_fragmentShaderId, boom::kOpenGLCompileStatus, &fragmentStatus);
    if (vertexStatus != boom::kOpenGLTrue) {
        char buffer[512] = {0};
        _context->getShaderInfoLog(_vertexShaderId, 511, nullptr, buffer);
        std::cerr << "ERROR: boom::Shaders::Shaders() failed: Failed to compile vertex shader: " << buffer << std::endl;
    }
    if (fragmentStatus != boom::kOpenGLTrue) {
        char buffer[512] = {0};
        _context->getShaderInfoLog(_fragmentShaderId, 511, nullptr, buffer);
        std::cerr << "ERROR: boom::Shaders::Shaders() failed: Failed to compile fragment shader: " << buffer << std::endl;
    }
    if (error == true) {
        ::exit(-1);
    }
    _shaderProgramId = _context->createProgram();
    _context->attachShader(_shaderProgramId, _vertexShaderId);
    _context->attachShader(_shaderProgramId, _fragmentShaderId);
    _context->linkProgram(_shaderProgramId);
}

boom::OpenGLUInt Shaders::_use() const {
    _context->useProgram(_shaderProgramId);
    return _shaderProgramId;
}

} /* namespace boom */
