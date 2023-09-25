#pragma once

#include <expected>
#include <functional>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ClassImpl;

class Class final : public boom::Shared {
public:
    Class(boom::js::ContextRef, std::string const&);
    Class(boom::js::ContextRef, std::string const&, std::string const&);
    void addMethod(std::string const&, std::string const&);
    void addProperty(std::string const&, std::string const&);
    void addProperty(std::string const&, std::string const&, std::string const&);
    virtual ~Class() override;
private:
    boom::js::ContextRef _context;
    boom::js::__ClassImpl* _impl;
    void _implInit(std::string const&, std::string const&);
    void _implDone();
    void _implAddMethod(std::string const&, std::string const&);
    void _implAddProperty(std::string const&, std::string const&);
    void _implAddProperty(std::string const&, std::string const&, std::string const&);
    friend boom::js::Value;
};

} /* namespace boom::js */