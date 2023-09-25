#include "Value.hpp"
#include "Context.hpp"

namespace boom::js {

void Context::_implInit() {
    auto context = JSGlobalContextCreate(nullptr);
    auto global = JSContextGetGlobalObject(context);
    _impl = new boom::js::__ContextImpl{
        .context = context,
        .global = global
    };
}

void Context::_implDone() {
    JSGlobalContextRelease(_impl->context);
    delete _impl;
}

boom::js::ValueRef Context::_implGlobalThis() {
    return boom::MakeShared<boom::js::Value>(
        boom::GetShared<boom::js::Context>(this),
        (void*)_impl->global
    );
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Context::_implEvaluate(std::string const& code) {
    auto error = (JSValueRef)nullptr;
    auto context = boom::GetShared<boom::js::Context>(this);
    auto string = JSStringCreateWithUTF8CString(code.c_str());
    auto result = JSEvaluateScript(_impl->context, string, nullptr, nullptr, 0, &error);
    JSStringRelease(string);
    if (error == nullptr) {
        return boom::MakeShared<boom::js::Value>(context, (void*)result);
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(context, (void*)error)
        );
    }
}

} /* namespace boom::js */