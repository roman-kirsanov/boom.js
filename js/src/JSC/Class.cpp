#include <string>
#include <cassert>
#include <iostream>
#include "Class.hpp"
#include "Context.hpp"

namespace boom::js {

void Class::_implDone() {

}

void Class::_implInit(std::string const& name, std::string const& constructor) {
    // auto string = JSStringCreateWithUTF8CString(name.c_str());
    // JSObjectMakeFunctionWithCallback(_context->_impl->context, string, boom::js::__function);
}

void Class::_implAddMethod(std::string const& name, std::string const& body) {

}

void Class::_implAddProperty(std::string const& name, std::string const& getter) {

}

void Class::_implAddProperty(std::string const& name, std::string const& getter, std::string const& setter) {

}

} /* namespace boom::js */