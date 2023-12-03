#pragma once

#include <cinttypes>
#include <Boom/Memory.hpp>

namespace boom {

class Paint;

class Shaders final {
public:
    Shaders(boom::Shaders const&) = delete;
    Shaders(boom::Shaders &&) = delete;
    boom::Shaders& operator=(boom::Shaders const&) = delete;
    boom::Shaders& operator=(boom::Shaders &) = delete;
    ~Shaders();
    Shaders(char const*, char const*);
private:
    std::uint32_t _vertexShaderId;
    std::uint32_t _fragmentShaderId;
    std::uint32_t _shaderProgramId;
    std::uint32_t _use() const;
    friend Paint;
};

} /* namespace boom */
