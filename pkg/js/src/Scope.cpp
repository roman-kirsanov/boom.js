#include <cassert>
#include <Boom/JS/Value.hpp>
#include <Boom/JS/Scope.hpp>

namespace boom::js {

Scope::~Scope() {
    _implDone();
}

Scope::Scope(boom::js::ContextRef context, void* object, void** argv, std::size_t argc)
    : _context(context)
    , _argc(argc)
    , _impl(nullptr)
{
    assert(context != nullptr);
    _implInit(object, argv, argc);
}

boom::js::ContextRef Scope::context() const {
    return _context;
}

boom::js::ValueRef Scope::thisObject() const {
    return _implThisObject();
}

std::int32_t Scope::argCount() const {
    return _argc;
}

boom::js::ValueRef Scope::getArg(std::int32_t index) const {
    return _implGetArg(index);
}

} /* namespace boom::js */