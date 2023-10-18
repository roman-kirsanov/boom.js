#include <Boom/JS/Value.hpp>
#include <Boom/JS/Context.hpp>

namespace boom::js {

Context::~Context() {
    _implDone();
}

Context::Context()
    : _impl(nullptr)
{
    _implInit();
}

boom::js::ValueRef Context::globalThis() {
    return _implGlobalThis();
}

boom::js::ValueRef Context::evaluate(std::string const& code) {
    return _implEvaluate(code);
}

void* Context::ref() const {
    return _implRef();
}

} /* namespace boom::js */