#pragma once

#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/OpenGL.hpp>

namespace boom {

class Paint;
class Surface;
class Shaders;

using ShadersRef = std::shared_ptr<boom::Shaders>;
using ShadersCRef = std::shared_ptr<boom::Shaders const>;

class Shaders final : public boom::Object {
public:
    Shaders(boom::OpenGLCRef, char const*, char const*);
    virtual ~Shaders();
private:
    boom::OpenGLCRef _context;
    boom::OpenGLUInt _vertexShaderId;
    boom::OpenGLUInt _fragmentShaderId;
    boom::OpenGLUInt _shaderProgramId;
    boom::OpenGLUInt _use() const;
    friend boom::Surface;
    friend boom::Paint;
};

} /* namespace boom */
