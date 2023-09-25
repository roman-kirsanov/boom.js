#include <string>
#include <cassert>
#include <Boom/JS/Value.hpp>
#include <Boom/JS/Class.hpp>
#include <Boom/JS/Context.hpp>

namespace boom::js {

Class::~Class() {
    _implDone();
}

Class::Class(boom::js::ContextRef context, std::string const& name)
    : _context(context)
    , _impl(nullptr)
{
    assert(context != nullptr);
    _implInit(name, "");
}

Class::Class(boom::js::ContextRef context, std::string const& name, std::string const& constructor)
    : _context(context)
    , _impl(nullptr)
{
    assert(context != nullptr);
    _implInit(name, constructor);
}

void Class::addMethod(std::string const& name, std::string const& body) {
    _implAddMethod(name, body);
}

void Class::addProperty(std::string const& name, std::string const& getter) {
    _implAddProperty(name, getter);
}

void Class::addProperty(std::string const& name, std::string const& getter, std::string const& setter) {
    _implAddProperty(name, getter, setter);
}

} /* namespace boom::js */