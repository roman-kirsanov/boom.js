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
    JSGlobalContextSetInspectable(context, true);
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

boom::js::ValueRef Context::_implEvaluate(std::string const& code) {
    auto error = (JSValueRef)nullptr;
    auto context = boom::GetShared<boom::js::Context>(this);
    auto string = JSStringCreateWithUTF8CString(code.c_str());
    auto result = JSEvaluateScript(_impl->context, string, nullptr, nullptr, 0, &error);
    JSStringRelease(string);
    if (error == nullptr) {
        return boom::MakeShared<boom::js::Value>(context, (void*)result);
    } else {
        auto jsError = boom::MakeShared<boom::js::Value>(context, (void*)error);
        auto message = [&]{
            try {
                return jsError->getProperty("message")->stringValue();
            } catch (...) {
                return std::string("Failed to retrieve error message from JavaScript Error object");
            }
        }();
        throw boom::Error("Failed to evaluate JS script: " + message, {{ "jsError", jsError }});
    }
}

} /* namespace boom::js */