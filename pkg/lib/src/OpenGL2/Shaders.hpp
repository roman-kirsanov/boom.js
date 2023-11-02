#pragma once

#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/OpenGL.hpp>

namespace boom {

class Paint;

class Shaders final : public boom::Shared {
public:
    Shaders(std::shared_ptr<boom::OpenGL>, char const*, char const*);
    virtual ~Shaders();
private:
    std::shared_ptr<boom::OpenGL> _context;
    std::uint32_t _vertexShaderId;
    std::uint32_t _fragmentShaderId;
    std::uint32_t _shaderProgramId;
    std::uint32_t _use() const;
    friend Paint;
};

} /* namespace boom */
