#include <map>
#include <iostream>
#include "Context.hpp"
#include "Value.hpp"

namespace boom::js {

void Value::_implInit(void* value) {
    _impl = new boom::js::__ValueImpl{
        .value = (
            (value == nullptr)
                ? JSValueMakeUndefined(_context->_impl->context)
                : (JSValueRef)value
        )
    };
    JSValueProtect(_context->_impl->context, _impl->value);
}

void Value::_implDone() {
    if (_impl->value != nullptr) {
        JSValueUnprotect(_context->_impl->context, _impl->value);
    }
    delete _impl;
}

boom::js::ValueType Value::_implType() const {
    static auto const map = std::map<JSType, boom::js::ValueType>({
        { kJSTypeUndefined, boom::js::ValueType::Undefined },
        { kJSTypeNull, boom::js::ValueType::Null },
        { kJSTypeBoolean, boom::js::ValueType::Boolean },
        { kJSTypeNumber, boom::js::ValueType::Number },
        { kJSTypeString, boom::js::ValueType::String },
        { kJSTypeObject, boom::js::ValueType::Object },
        { kJSTypeSymbol, boom::js::ValueType::Symbol }
    });
    assert(_impl->value != nullptr);
    auto const type = JSValueGetType(_context->_impl->context, _impl->value);
    return map.at(type);
}

std::expected<bool, boom::js::ValueRef> Value::_implAsBoolean() const {
    assert(type() == boom::js::ValueType::Boolean);
    return JSValueToBoolean(_context->_impl->context, _impl->value);
}

std::expected<double, boom::js::ValueRef> Value::_implAsNumber() const {
    assert(type() == boom::js::ValueType::Number);
    auto error = (JSValueRef)nullptr;
    auto value = JSValueToNumber(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return value;
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::_implAsString() const {
    assert(type() == boom::js::ValueType::String);
    auto error = (JSValueRef)nullptr;
    auto string = JSValueToStringCopy(_context->_impl->context, _impl->value, &error);
    if (error != nullptr) {
        auto len = JSStringGetMaximumUTF8CStringSize(string);
        auto data = boom::Alloc<char>(len + 1);
        JSStringGetUTF8CString(string, data, len);
        JSStringRelease(string);
        auto value = std::string(data);
        boom::Free(data);
        return value;
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::_implToString() const {
    auto error = (JSValueRef)nullptr;
    auto string = JSValueToStringCopy(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto len = JSStringGetMaximumUTF8CStringSize(string);
        auto data = boom::Alloc<char>(len + 1);
        JSStringGetUTF8CString(string, data, len);
        JSStringRelease(string);
        auto value = std::string(data);
        boom::Free(data);
        return value;
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::_implGetProperty(std::string const& name) {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto string = JSStringCreateWithUTF8CString(name.c_str());
        auto value = JSObjectGetProperty(_context->_impl->context, object, string, &error);
        JSStringRelease(string);
        if (error == nullptr) {
            return boom::MakeShared<boom::js::Value>(_context, (void*)value);
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)error)
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<void, boom::js::ValueRef> Value::_implSetProperty(std::string const& name, boom::js::ValueRef value) {
    assert(value != nullptr);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto string = JSStringCreateWithUTF8CString(name.c_str());
        JSObjectSetProperty(
            _context->_impl->context,
            object,
            string,
            value->_impl->value,
            0,
            &error
        );
        if (error != nullptr) {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)error)
            );
        } else {
            return std::expected<void, boom::js::ValueRef>();
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<bool, boom::js::ValueRef> Value::_implHasProperty(std::string const& name) const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto string = JSStringCreateWithUTF8CString(name.c_str());
        auto result = JSObjectHasProperty(_context->_impl->context, object, string);
        JSStringRelease(string);
        return result;
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<bool, boom::js::ValueRef> Value::_implOfClass(boom::js::ClassRef class_) const {
    assert(class_ != nullptr);
    return false;
    // return JSValueIsObjectOfClass(_context->_impl->context, _impl->value, class_->_impl->class_);
}

std::expected<bool, boom::js::ValueRef> Value::_implIsFunction() const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return JSObjectIsFunction(_context->_impl->context, object);
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<bool, boom::js::ValueRef> Value::_implIsArray() const {
    return JSValueIsArray(_context->_impl->context, _impl->value);
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::_implCall(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto this_ = JSValueToObject(_context->_impl->context, thisObject->_impl->value, nullptr);
        auto args = std::vector<JSValueRef>();
        args.reserve(arguments.size());
        for (auto arg : arguments) {
            args.push_back(arg->_impl->value);
        }
        auto result = JSObjectCallAsFunction(_context->_impl->context, object, this_, args.size(), args.data(), &error);
        if (error == nullptr) {
            return boom::MakeShared<boom::js::Value>(_context, (void*)result);
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)error)
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

void Value::_implSetNull() {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = JSValueMakeNull(_context->_impl->context);
    JSValueProtect(_context->_impl->context, _impl->value);
}

void Value::_implSetUndefined() {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = JSValueMakeUndefined(_context->_impl->context);
    JSValueProtect(_context->_impl->context, _impl->value);
}

void Value::_implSetBoolean(bool boolean) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = JSValueMakeBoolean(_context->_impl->context, boolean);
    JSValueProtect(_context->_impl->context, _impl->value);
}

void Value::_implSetNumber(double number) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = JSValueMakeNumber(_context->_impl->context, number);
    JSValueProtect(_context->_impl->context, _impl->value);
}

void Value::_implSetString(std::string const& string) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    auto jsstr = JSStringCreateWithUTF8CString(string.c_str());
    _impl->value = JSValueMakeString(_context->_impl->context, jsstr);
    JSValueProtect(_context->_impl->context, _impl->value);
    JSStringRelease(jsstr);
}

void Value::_implSetSymbol(std::string const& symbol) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    auto jsstr = JSStringCreateWithUTF8CString(symbol.c_str());
    _impl->value = JSValueMakeSymbol(_context->_impl->context, jsstr);
    JSValueProtect(_context->_impl->context, _impl->value);
    JSStringRelease(jsstr);
}

void Value::_implSetObject(std::map<std::string, boom::js::ValueRef> props) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = (JSValueRef)JSObjectMake(_context->_impl->context, nullptr, nullptr);
    JSValueProtect(_context->_impl->context, _impl->value);
    for (auto& pair : props) {
        setProperty(pair.first, pair.second);
    }
}

void Value::_implSetArray(std::vector<boom::js::ValueRef> values) {
    auto error = (JSValueRef)nullptr;
    auto args = std::vector<JSValueRef>();
    args.reserve(values.size());
    for (auto& value : values) {
        args.push_back(value->_impl->value);
    }
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = (JSValueRef)JSObjectMakeArray(_context->_impl->context, args.size(), args.data(), &error);
    JSValueProtect(_context->_impl->context, _impl->value);
    /// TODO: This should not fail....
    if (error != nullptr) {
        std::cerr << "ERROR: boom::js::Value::_implSetArray() failed: Failed to create an array" << std::endl;
        std::exit(-1);
    }
}

void Value::_implSetError(std::string const& message) {
    auto error = (JSValueRef)nullptr;
    auto string = JSStringCreateWithUTF8CString(message.c_str());
    auto value = JSValueMakeString(_context->_impl->context, string);
    auto args = std::vector<JSValueRef>({ value });
    JSStringRelease(string);
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = (JSValueRef)JSObjectMakeError(_context->_impl->context, args.size(), args.data(), &error);
    JSValueProtect(_context->_impl->context, _impl->value);
    /// TODO: This should not fail....
    if (error != nullptr) {
        std::cerr << "ERROR: boom::js::Value::_implSetError() failed: Failed to create an error" << std::endl;
        std::exit(-1);
    }
}

void Value::_implSetFunction(void* function) {
    JSValueUnprotect(_context->_impl->context, _impl->value);
    _impl->value = (JSValueRef)JSObjectMakeFunctionWithCallback(_context->_impl->context, nullptr, (JSObjectCallAsFunctionCallback)function);
    JSValueProtect(_context->_impl->context, _impl->value);
}

bool Value::_implIsStrictEqual(boom::js::ValueRef value) const {
    assert(value != nullptr);
    return JSValueIsStrictEqual(_context->_impl->context, _impl->value, value->_impl->value);
}

bool Value::_implIsEqual(boom::js::ValueRef value) const {
    assert(value != nullptr);
    return JSValueIsEqual(_context->_impl->context, _impl->value, value->_impl->value, nullptr);
}

void* Value::_implRef() const {
    return (void*)_impl->value;
}

} /* namespace boom::js */