#pragma once

#include <Boom/Memory.hpp>
#include <Boom/Window.hpp>
#include <Boom/OpenGL.hpp>
#include "Shaders.hpp"

namespace boom {

class Context final : public boom::OpenGL {
public:
    Context(boom::OpenGLOptions const& = {});
    std::shared_ptr<boom::Shaders> basicShaders() const;
    std::shared_ptr<boom::Shaders> imageShaders() const;
    virtual ~Context();
    static std::shared_ptr<boom::Context const> Shared();
protected:
    virtual void _onReady();
private:
    std::shared_ptr<boom::OpenGL> _context;
    std::shared_ptr<boom::Shaders> _basicShaders;
    std::shared_ptr<boom::Shaders> _imageShaders;
};

} /* namespace boom */
