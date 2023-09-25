#pragma once

#include <Boom/Memory.hpp>
#include <Boom/Window.hpp>
#include "Shaders.hpp"

namespace boom {

struct __ContextImpl;

class Surface;
class Paint;

class Context final : public boom::Shared {
public:
    Context();
    void makeCurrent() const;
    void flush() const;
    virtual ~Context();
    static std::shared_ptr<boom::Context const> Shared();
private:
    Context(bool);
    std::shared_ptr<boom::Shaders> _basicShaders;
    std::shared_ptr<boom::Shaders> _imageShaders;
    boom::__ContextImpl* _impl;
    void _implMakeCurrent() const;
    void _implFlush() const;
    void _implInit(bool);
    void _implDone();
    friend boom::Paint;
    friend boom::Surface;
};

} /* namespace boom */
