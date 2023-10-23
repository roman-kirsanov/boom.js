#include <map>
#include <iostream>
#include "Context.hpp"
#include "Scope.hpp"
#include "Value.hpp"

namespace boom::js {

void Scope::_implDone() {
    delete _impl;
}

void Scope::_implInit(void* this_, void** argv, std::size_t argc) {
    assert(this_ != nullptr);
    assert(argv != nullptr);
    _impl = new boom::js::__ScopeImpl{
        .this_ = (JSObjectRef)this_,
        .argv = (JSValueRef*)argv,
        .argc = argc
    };
}

boom::js::ValueRef Scope::_implThisObject() const {
    return boom::MakeShared<boom::js::Value>(_context, (void*)_impl->this_);
}

boom::js::ValueRef Scope::_implGetArg(std::int32_t index) const {
    if ((index >= 0) && (index < _impl->argc)) {
        return boom::MakeShared<boom::js::Value>(_context, (void*)_impl->argv[index]);
    } else {
        return boom::js::Value::Undefined(_context);
    }
}

} /* namespace boom::js */