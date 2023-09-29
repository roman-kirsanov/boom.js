#pragma once

#include <map>
#include <expected>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ScopeImpl;

class Scope final : public boom::Shared {
public:
    Scope(boom::js::ContextRef);
    boom::js::ContextRef context() const;
    boom::js::ValueRef thisObject() const;
    std::int32_t argCount() const;
    boom::js::ValueRef getArg(std::int32_t) const;
    boom::js::ValueRef result() const;
    boom::js::ValueRef error() const;
    void setResult(boom::js::ValueRef);
    void setError(boom::js::ValueRef);
    virtual ~Scope();
private:
    boom::js::ContextRef _context;
    boom::js::ValueRef _result;
    boom::js::ValueRef _error;
    boom::js::__ScopeImpl* _impl;
    void _implInit();
    void _implDone();
    boom::js::ValueRef _implThisObject() const;
    boom::js::ValueRef _implGetArg(std::int32_t) const;
};

} /* namespace boom::js */