#include <map>
#include <iostream>
#include "Context.hpp"
#include "Value.hpp"

namespace boom::js {

struct ObjectPrivate {
    std::shared_ptr<boom::Shared> data;
    boom::js::ContextRef context;
    boom::js::Initializer init;
    boom::js::Finalizer done;
};

struct FunctionPrivate {
    boom::js::ContextRef context;
    boom::js::Function function;
};

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
        auto this_ = (JSObjectRef)nullptr;
        if (thisObject != nullptr) {
            this_ = JSValueToObject(_context->_impl->context, thisObject->_impl->value, nullptr);
        }
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

std::shared_ptr<boom::Shared> Value::_implGetPrivate() const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(object);
        if (priv != nullptr) {
            return priv->data;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

void Value::_implSetPrivate(std::shared_ptr<boom::Shared> data) {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(object);
        if (priv != nullptr) {
            priv->data = data;
        }
    }
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

boom::js::ValueRef Value::_ImplNull(boom::js::ContextRef context) {
    return boom::MakeShared<boom::js::Value>(context, (void*)JSValueMakeNull(context->_impl->context));
}

boom::js::ValueRef Value::_ImplUndefined(boom::js::ContextRef context) {
    return boom::MakeShared<boom::js::Value>(context, (void*)JSValueMakeUndefined(context->_impl->context));
}

boom::js::ValueRef Value::_ImplBoolean(boom::js::ContextRef context, bool boolean) {
    return boom::MakeShared<boom::js::Value>(context, (void*)JSValueMakeBoolean(context->_impl->context, boolean));
}

boom::js::ValueRef Value::_ImplNumber(boom::js::ContextRef context, double number) {
    return boom::MakeShared<boom::js::Value>(context, (void*)JSValueMakeNumber(context->_impl->context, number));
}

boom::js::ValueRef Value::_ImplString(boom::js::ContextRef context, std::string const& string) {
    auto jsstr = JSStringCreateWithUTF8CString(string.c_str());
    auto value = JSValueMakeString(context->_impl->context, jsstr);
    JSStringRelease(jsstr);
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

boom::js::ValueRef Value::_ImplSymbol(boom::js::ContextRef context, std::string const& symbol) {
    auto jsstr = JSStringCreateWithUTF8CString(symbol.c_str());
    auto value = JSValueMakeSymbol(context->_impl->context, jsstr);
    JSStringRelease(jsstr);
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

boom::js::ValueRef Value::_ImplObject(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props, boom::js::Initializer const& init, boom::js::Finalizer const& done) {
    static auto const initFn = [](JSContextRef ctx, JSObjectRef obj) -> void {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(obj);
        if (priv != nullptr) {
            priv->init.operator()(
                priv->context,
                boom::MakeShared<boom::js::Value>(priv->context, (void*)obj)
            );
        }
    };
    static auto const doneFn = [](JSObjectRef obj) -> void {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(obj);
        if (priv != nullptr) {
            priv->done.operator()(
                priv->context,
                boom::MakeShared<boom::js::Value>(priv->context, (void*)obj)
            );
            delete priv;
        }
    };
    static auto const classDef = (JSClassDefinition){
        .className = "NativeObject",
        .initialize = initFn,
        .finalize = doneFn
    };
    static auto const classRef = JSClassCreate(&classDef);
    auto object = JSObjectMake(context->_impl->context, classRef, new boom::js::ObjectPrivate{
        .data = nullptr,
        .context = context,
        .init = init,
        .done = done
    });
    auto value = boom::MakeShared<boom::js::Value>(context, (void*)object);
    for (auto& pair : props) {
        value->setProperty(pair.first, pair.second);
    }
    return value;
}

boom::js::ValueRef Value::_ImplArray(boom::js::ContextRef context, std::vector<boom::js::ValueRef> values) {
    auto error = (JSValueRef)nullptr;
    auto args = std::vector<JSValueRef>();
    args.reserve(values.size());
    for (auto& value : values) {
        args.push_back(value->_impl->value);
    }
    auto value = (JSValueRef)JSObjectMakeArray(context->_impl->context, args.size(), args.data(), &error);
    /// TODO: This should not fail....
    if (error != nullptr) {
        std::cerr << "ERROR: boom::js::Value::_ImplArray() failed: Failed to create an array" << std::endl;
        std::exit(-1);
    }
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

boom::js::ValueRef Value::_ImplError(boom::js::ContextRef context, std::string const& message) {
    auto error = (JSValueRef)nullptr;
    auto string = JSStringCreateWithUTF8CString(message.c_str());
    auto args = std::vector<JSValueRef>({
        JSValueMakeString(context->_impl->context, string)
    });
    JSStringRelease(string);
    auto value = (JSValueRef)JSObjectMakeError(context->_impl->context, args.size(), args.data(), &error);
    /// TODO: This should not fail....
    if (error != nullptr) {
        std::cerr << "ERROR: boom::js::Value::_ImplError() failed: Failed to create an error" << std::endl;
        std::exit(-1);
    }
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

boom::js::ValueRef Value::_ImplFunction(boom::js::ContextRef context, boom::js::Function const& function) {
    static auto const wrapFn = [](JSContextRef ctx, JSObjectRef fn, JSObjectRef this_, size_t argc, const JSValueRef* argv, JSValueRef* error) -> JSValueRef {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(fn);
        if (priv != nullptr) {
            auto object = boom::MakeShared<boom::js::Value>(priv->context, (void*)this_);
            auto arguments = std::vector<boom::js::ValueRef>();
            arguments.reserve(argc);
            for (std::size_t i = 0; i < argc; i++) {
                arguments.push_back(
                    boom::MakeShared<boom::js::Value>(priv->context, (void*)argv[i])
                );
            }
            auto result = priv->function.operator()(priv->context, object, arguments);
            if (result) {
                return result.value()->_impl->value;
            } else {
                *error = result.error()->_impl->value;
                return JSValueMakeUndefined(ctx);
            }
        } else {
            return JSValueMakeUndefined(ctx);
        }
    };
    static auto const doneFn = [](JSObjectRef fn) -> void {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(fn);
        if (priv != nullptr) {
            delete priv;
        }
    };
    static auto const classDef = (JSClassDefinition){
        .className = "NativeFunction",
        .finalize = doneFn,
        .callAsFunction = wrapFn
    };
    static auto const classRef = JSClassCreate(&classDef);
    auto value = JSObjectMake(context->_impl->context, classRef, new boom::js::FunctionPrivate{
        .context = context,
        .function = function
    });
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

} /* namespace boom::js */