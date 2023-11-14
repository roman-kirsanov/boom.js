#pragma once

#include <map>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ScopeImpl;

class Scope final : public boom::Shared {
public:
    Scope(boom::js::ContextRef, void*, void**, std::size_t);
    boom::js::ContextRef context() const;
    boom::js::ValueRef thisObject() const;
    std::size_t argCount() const;
    boom::js::ValueRef getArg(std::size_t) const;
    virtual ~Scope();
private:
    boom::js::ContextRef _context;
    std::size_t _argc;
    boom::js::__ScopeImpl* _impl;
    void _implInit(void*, void**, std::size_t);
    void _implDone();
    boom::js::ValueRef _implThisObject() const;
    boom::js::ValueRef _implGetArg(std::size_t) const;
};

} /* namespace boom::js */