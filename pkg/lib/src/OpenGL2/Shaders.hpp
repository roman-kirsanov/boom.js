#pragma once

#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/OpenGL.hpp>

namespace boom {

class Paint;

class Shaders;

using ShadersRef = std::shared_ptr<boom::Shaders>;
using ShadersCRef = std::shared_ptr<boom::Shaders const>;

class Shaders final : public boom::Shared {
public:
    Shaders(boom::OpenGLRef, char const*, char const*);
    virtual ~Shaders();
private:
    boom::OpenGLRef _context;
    std::uint32_t _vertexShaderId;
    std::uint32_t _fragmentShaderId;
    std::uint32_t _shaderProgramId;
    std::uint32_t _use() const;
    friend Paint;
};

} /* namespace boom */
