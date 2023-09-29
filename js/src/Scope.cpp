#include <cassert>
#include <Boom/JS/Value.hpp>
#include <Boom/JS/Scope.hpp>

namespace boom::js {

Scope::~Scope() {
    _implDone();
}

Scope::Scope(boom::js::ContextRef context)
    : _context(context)
    , _result(nullptr)
    , _error(nullptr)
    , _impl(nullptr)
{
    assert(context != nullptr);
    _implInit();
}

boom::js::ContextRef Scope::context() const {
    return _context;
}

boom::js::ValueRef Scope::thisObject() const {
    return _implThisObject();
}

std::int32_t Scope::argCount() const {
    return 0;
}

boom::js::ValueRef Scope::getArg(std::int32_t index) const {
    return _implGetArg(index);
}

boom::js::ValueRef Scope::result() const {
    return _result;
}

boom::js::ValueRef Scope::error() const {
    return _error;
}

void Scope::setResult(boom::js::ValueRef result) {
    _result = result;
}

void Scope::setError(boom::js::ValueRef error) {
    _error = error;
}

} /* namespace boom::js */