#pragma once

#include <string>
#include <Boom/Memory.hpp>
#include <Boom/Error.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ContextImpl;

class Context final : public boom::Object {
public:
    Context();
    boom::js::ValueRef globalThis();
    boom::js::ValueRef evaluate(std::string const&);
    virtual ~Context();
private:
    boom::js::__ContextImpl* _impl;
    void _implInit();
    void _implDone();
    boom::js::ValueRef _implGlobalThis();
    boom::js::ValueRef _implEvaluate(std::string const&);
    friend boom::js::Value;
};

} /* namespace boom::js */