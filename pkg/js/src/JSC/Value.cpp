#include <map>
#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include "Context.hpp"
#include "Scope.hpp"
#include "Value.hpp"

namespace boom::js {

struct ObjectPrivate {
    std::shared_ptr<boom::Shared> data;
    boom::js::ContextRef context;
    boom::js::Destructor destructor;
};

struct FunctionPrivate {
    boom::js::ContextRef context;
    boom::js::Function function;
};

template<typename T>
std::vector<T> TypedArrayValue(boom::js::ContextRef context, JSObjectRef object) {
    auto error = (JSValueRef)nullptr;
    auto ptr = (uint8_t*)JSObjectGetTypedArrayBytesPtr((JSContextRef)context->ref(), object, &error);
    if (error != nullptr) {
        throw boom::Error("Failed to obtain typed array data pointer", {
            { "jsError", boom::MakeShared<boom::js::Value>(context, (void*)error) }
        });
    }
    auto offset = JSObjectGetTypedArrayByteOffset((JSContextRef)context->ref(), object, &error);
    if (error != nullptr) {
        throw boom::Error("Failed to obtain typed array offset", {
            { "jsError", boom::MakeShared<boom::js::Value>(context, (void*)error) }
        });
    }
    auto length = JSObjectGetTypedArrayLength((JSContextRef)context->ref(), object, &error);
    if (error != nullptr) {
        throw boom::Error("Failed to obtain typed array length", {
            { "jsError", boom::MakeShared<boom::js::Value>(context, (void*)error) }
        });
    }
    auto data = (T*)(ptr + offset);
    return std::vector<T>(data, (data + length));
}

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

bool Value::_implBooleanValue() const {
    assert(isBoolean() == true);
    return JSValueToBoolean(_context->_impl->context, _impl->value);
}

double Value::_implNumberValue() const {
    assert(isNumber() == true);
    auto error = (JSValueRef)nullptr;
    auto value = JSValueToNumber(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return value;
    } else {
        throw boom::Error("Value is not a number", {
            { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
        });
    }
}

std::string Value::_implStringValue() const {
    assert(isString() == true);
    auto error = (JSValueRef)nullptr;
    auto string = JSValueToStringCopy(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto size = JSStringGetMaximumUTF8CStringSize(string);
        auto data = boom::Alloc<char>(size + 1);
        JSStringGetUTF8CString(string, data, size);
        JSStringRelease(string);
        auto value = std::string(data);
        boom::Free(data);
        return value;
    } else {
        throw boom::Error("Value is not a string", {
            { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
        });
    }
}

std::map<std::string, boom::js::ValueRef> Value::_implObjectValue() const {
    assert(isObject() == true);
    try {
        auto names = listProperties();
        auto props = std::map<std::string, boom::js::ValueRef>();
        for (auto& name : names) {
            props[name] = getProperty(name);
        }
        return props;
    } catch (boom::Error& e) {
        throw e.extend("Value is not an object");
    }
}

std::vector<std::uint8_t> Value::_implArrayBufferValue() const {
    assert(isArrayBuffer() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto data = (uint8_t*)JSObjectGetArrayBufferBytesPtr(_context->_impl->context, object, &error);
            if (error == nullptr) {
                auto size = JSObjectGetArrayBufferByteLength(_context->_impl->context, object, &error);
                if (error == nullptr) {
                    return std::vector<std::uint8_t>(data, (data + size));
                } else {
                    throw boom::Error("Failed to obtain array buffer length", {
                        { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                    });
                }
            } else {
                throw boom::Error("Failed to obtain array buffer data pointer", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not ArrayBuffer");
    }
}

std::vector<std::uint8_t> Value::_implUint8ArrayValue() const {
    assert(isUint8Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<uint8_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Uint8Array");
    }
}

std::vector<std::uint8_t> Value::_implUint8ClampedArrayValue() const {
    assert(isUint8ClampedArray() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<uint8_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Uint8ClampedArray");
    }
}

std::vector<std::uint16_t> Value::_implUint16ArrayValue() const {
    assert(isUint16Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<uint16_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Uint16Array");
    }
}

std::vector<std::uint32_t> Value::_implUint32ArrayValue() const {
    assert(isUint32Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<uint32_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Uint32Array");
    }
}

std::vector<std::int8_t> Value::_implInt8ArrayValue() const {
    assert(isInt8Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<int8_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Int8Array");
    }
}

std::vector<std::int16_t> Value::_implInt16ArrayValue() const {
    assert(isInt16Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<int16_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Int16Array");
    }
}

std::vector<std::int32_t> Value::_implInt32ArrayValue() const {
    assert(isInt32Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<int32_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Int32Array");
    }
}

std::vector<float> Value::_implFloat32ArrayValue() const {
    assert(isFloat32Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<float>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Float32Array");
    }
}

std::vector<double> Value::_implFloat64ArrayValue() const {
    assert(isFloat64Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<double>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not Float64Array");
    }
}

std::vector<std::uint64_t> Value::_implBigUint64ArrayValue() const {
    assert(isBigUint64Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<uint64_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not BigUint64Array");
    }
}

std::vector<std::int64_t> Value::_implBigInt64ArrayValue() const {
    assert(isBigInt64Array() == true);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            return boom::js::TypedArrayValue<int64_t>(_context, object);
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Value is not BigInt64Array");
    }
}

std::string Value::_implToString() const {
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
        throw boom::Error("Value is not a string", {
            { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
        });
    }
}

std::vector<std::string> Value::_implListProperties() const {
    assert(isObject());
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto names = std::vector<std::string>();
            auto array = JSObjectCopyPropertyNames(_context->_impl->context, object);
            auto length = JSPropertyNameArrayGetCount(array);
            for (std::size_t i = 0; i < length; i++) {
                auto name = JSPropertyNameArrayGetNameAtIndex(array, i);
                auto size = JSStringGetMaximumUTF8CStringSize(name);
                auto data = boom::Alloc<char>(size + 1);
                JSStringGetUTF8CString(name, data, size);
                JSStringRelease(name);
                names.emplace_back(data);
                boom::Free(data);
            }
            JSPropertyNameArrayRelease(array);
            return names;
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to list properties");
    }
}

boom::js::ValueRef Value::_implGetValueAtIndex(std::int64_t index) const {
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto value = JSObjectGetPropertyAtIndex(_context->_impl->context, object, index, &error);
            if (error == nullptr) {
                return boom::MakeShared<boom::js::Value>(_context, (void*)value);
            } else {
                throw boom::Error("Failed to get value at index (JSC)", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to get value at index");
    }
}

boom::js::ValueRef Value::_implGetProperty(std::string const& name) const {
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto string = JSStringCreateWithUTF8CString(name.c_str());
            auto value = JSObjectGetProperty(_context->_impl->context, object, string, &error);
            JSStringRelease(string);
            if (error == nullptr) {
                return boom::MakeShared<boom::js::Value>(_context, (void*)value);
            } else {
                throw boom::Error("Failed to get property value (JSC)", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to get property value");
    }
}

void Value::_implSetProperty(std::string const& name, boom::js::ValueRef value, boom::js::PropertyOptions const& options) {
    assert(value != nullptr);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto string = JSStringCreateWithUTF8CString(name.c_str());
            JSObjectSetProperty(
                _context->_impl->context,
                object,
                string,
                value->_impl->value,
                options.readOnly ? kJSPropertyAttributeReadOnly : kJSPropertyAttributeNone,
                &error
            );
            if (error != nullptr) {
                throw boom::Error("Failed to set property value (JSC)", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to set property value");
    }
}

void Value::_implSetPrototypeOf(boom::js::ValueRef prototype) {
    assert(prototype != nullptr);
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto proto = JSValueToObject(_context->_impl->context, prototype->_impl->value, &error);
            if (error == nullptr) {
                JSObjectSetPrototype(_context->_impl->context, object, proto);
            } else {
                throw boom::Error("Failed to obtain object reference of prototype", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to set prototype");
    }
}

boom::js::ValueRef Value::_implBind(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    assert(isFunction());
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto name = JSStringCreateWithUTF8CString("bind");
            auto bind_ = JSObjectGetProperty(_context->_impl->context, object, name, &error);
            JSStringRelease(name);
            if (error == nullptr) {
                auto bindobj = JSValueToObject(_context->_impl->context, bind_, &error);
                if (error == nullptr) {
                    if (JSObjectIsFunction(_context->_impl->context, bindobj)) {
                        auto this_ = (JSObjectRef)nullptr;
                        if ((thisObject != nullptr)
                        && (JSValueIsObject(_context->_impl->context, thisObject->_impl->value))) {
                            this_ = JSValueToObject(_context->_impl->context, thisObject->_impl->value, nullptr);
                        }
                        auto args = std::vector<JSValueRef>();
                        args.reserve(arguments.size());
                        for (auto arg : arguments) {
                            args.push_back(arg->_impl->value);
                        }
                        auto result = JSObjectCallAsFunction(_context->_impl->context, bindobj, this_, args.size(), args.data(), &error);
                        if (error == nullptr) {
                            return boom::MakeShared<boom::js::Value>(_context, (void*)result);
                        } else {
                            throw boom::Error("Failed to call \"bind\" function", {
                                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                            });
                        }
                    } else {
                        throw boom::Error("\"bind\" value is not a function", {
                            { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                        });
                    }
                } else {
                    throw boom::Error("Failed to obtain object reference of \"bind\" value", {
                        { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                    });
                }
            } else {
                throw boom::Error("Failed to get \"bind\" property", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to bind function");
    }
}

boom::js::ValueRef Value::_implCall(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    assert(isFunction());
    try {
        auto error = (JSValueRef)nullptr;
        auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
        if (error == nullptr) {
            auto this_ = (JSObjectRef)nullptr;
            if ((thisObject != nullptr)
            && (JSValueIsObject(_context->_impl->context, thisObject->_impl->value))) {
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
                throw boom::Error("Function failed", {
                    { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
                });
            }
        } else {
            throw boom::Error("Failed to obtain object reference", {
                { "jsError", boom::MakeShared<boom::js::Value>(_context, (void*)error) }
            });
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to call a function");
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

void Value::_implSetDestructor(boom::js::Destructor const& destructor) {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(object);
        if (priv != nullptr) {
            priv->destructor = destructor;
        }
    }
}

bool Value::_implHasProperty(std::string const& name) const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto string = JSStringCreateWithUTF8CString(name.c_str());
        auto result = JSObjectHasProperty(_context->_impl->context, object, string);
        JSStringRelease(string);
        return result;
    } else {
        return false;
    }
}

bool Value::_implIsNull() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeNull;
}

bool Value::_implIsUndefined() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeUndefined;
}

bool Value::_implIsBoolean() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeBoolean;
}

bool Value::_implIsNumber() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeNumber;
}

bool Value::_implIsString() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeString;
}

bool Value::_implIsObject() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeObject;
}

bool Value::_implIsSymbol() const {
    return JSValueGetType(_context->_impl->context, _impl->value) == kJSTypeSymbol;
}

bool Value::_implIsFunction() const {
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return JSObjectIsFunction(_context->_impl->context, object);
    } else {
        return false;
    }
}

bool Value::_implIsArray() const {
    return JSValueIsArray(_context->_impl->context, _impl->value);
}

bool Value::_implIsArrayBuffer() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeArrayBuffer);
    } else {
        return false;
    }
}

bool Value::_implIsUint8Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeUint8Array);
    } else {
        return false;
    }
}

bool Value::_implIsUint8ClampedArray() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeUint8ClampedArray);
    } else {
        return false;
    }
}

bool Value::_implIsUint16Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeUint16Array);
    } else {
        return false;
    }
}

bool Value::_implIsUint32Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeUint32Array);
    } else {
        return false;
    }
}

bool Value::_implIsInt8Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeInt8Array);
    } else {
        return false;
    }
}

bool Value::_implIsInt16Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeInt16Array);
    } else {
        return false;
    }
}

bool Value::_implIsInt32Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeInt32Array);
    } else {
        return false;
    }
}

bool Value::_implIsFloat32Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeFloat32Array);
    } else {
        return false;
    }
}

bool Value::_implIsFloat64Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeFloat64Array);
    } else {
        return false;
    }
}

bool Value::_implIsBigUint64Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeBigUint64Array);
    } else {
        return false;
    }
}

bool Value::_implIsBigInt64Array() const {
    auto error = (JSValueRef)nullptr;
    auto type = JSValueGetTypedArrayType(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        return (type == kJSTypedArrayTypeBigInt64Array);
    } else {
        return false;
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

boom::js::ValueRef Value::_ImplObject(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props, boom::js::ObjectOptions const& options) {
    static auto const doneFn = [](JSObjectRef obj) -> void {
        auto priv = (boom::js::ObjectPrivate*)JSObjectGetPrivate(obj);
        auto scope = boom::MakeShared<boom::js::Scope>(priv->context, (void*)obj, nullptr, 0);
        if (priv != nullptr) {
            priv->destructor.operator()(scope);
            delete priv;
        }
    };
    static auto const classDef = JSClassDefinition{
        .className = "ManagedObject",
        .finalize = doneFn
    };
    static auto const classRef = JSClassCreate(&classDef);
    try {
        auto object = (JSObjectRef)nullptr;
        if (options.managed || options.destructor.has_value()) {
            object = JSObjectMake(context->_impl->context, classRef, new boom::js::ObjectPrivate{
                .data = nullptr,
                .context = context,
                .destructor = options.destructor.value_or([](auto){})
            });
        } else {
            object = JSObjectMake(context->_impl->context, nullptr, nullptr);
        }
        auto value = boom::MakeShared<boom::js::Value>(context, (void*)object);
        for (auto& pair : props) {
            value->setProperty(pair.first, pair.second);
        }
        return value;
    } catch (boom::Error& e) {
        throw e.extend("Failed to construct an object");
    }
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
        boom::Abort("boom::js::Value::_ImplArray() failed: Failed to create an array");
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
        boom::Abort("boom::js::Value::_ImplError() failed: Failed to create an error");
    }
    return boom::MakeShared<boom::js::Value>(context, (void*)value);
}

boom::js::ValueRef Value::_ImplFunction(boom::js::ContextRef context, boom::js::Function const& function) {
    static auto const wrapFn = [](JSContextRef ctx, JSObjectRef fn, JSObjectRef this_, std::size_t argc, JSValueRef const* argv, JSValueRef* error) -> JSValueRef {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(fn);
        if (priv != nullptr) {
            auto scope = boom::MakeShared<boom::js::Scope>(priv->context, (void*)this_, (void**)argv, argc);
            try {
                auto result = priv->function.operator()(scope);
                return result->_impl->value;
            } catch (boom::Error& e) {
                if (auto jsError = e.data<boom::js::Value>("jsError")) {
                    *error = jsError->_impl->value;
                } else {
                    *error = boom::js::Value::Error(priv->context, e.what())->_impl->value;
                }
                return JSValueMakeUndefined(ctx);
            }
        } else {
            return JSValueMakeUndefined(ctx);
        }
    };
    static auto const wrapCtor = [](JSContextRef ctx, JSObjectRef ctor, size_t argc, JSValueRef const* argv, JSValueRef* error) -> JSObjectRef {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(ctor);
        if (priv != nullptr) {
            try {
                auto thisObject = boom::js::Value::Object(priv->context, {}, { .managed = true });
                auto ctorObject = boom::MakeShared<boom::js::Value>(priv->context, (void*)ctor);
                if (ctorObject->hasProperty("prototype")) {
                    auto protoObject = ctorObject->getProperty("prototype");
                    if (protoObject->isObject()) {
                        thisObject->setPrototypeOf(protoObject);
                    }
                }
                auto object = JSValueToObject(ctx, thisObject->_impl->value, nullptr);
                auto scope = boom::MakeShared<boom::js::Scope>(priv->context, (void*)object, (void**)argv, argc);
                try {
                    priv->function.operator()(scope);
                } catch (boom::Error& e) {
                    if (auto jsError = e.data<boom::js::Value>("jsError")) {
                        *error = jsError->_impl->value;
                    } else {
                        *error = boom::js::Value::Error(priv->context, e.what())->_impl->value;
                    }
                }
                return object;
            } catch (boom::Error& e) {
                *error = boom::js::Value::Error(priv->context, e.what())->_impl->value;
                return JSObjectMake(ctx, nullptr, nullptr);
            }
        } else {
            return JSObjectMake(ctx, nullptr, nullptr);
        }
    };
    static auto const doneFn = [](JSObjectRef fn) -> void {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(fn);
        if (priv != nullptr) {
            delete priv;
        }
    };
    static auto const classDef = JSClassDefinition{
        .className = "BoomFunction",
        .finalize = doneFn,
        .callAsFunction = wrapFn,
        .callAsConstructor = wrapCtor
    };
    static auto const classRef = JSClassCreate(&classDef);
    try {
        auto object = JSObjectMake(context->_impl->context, classRef, new boom::js::FunctionPrivate{
            .context = context,
            .function = function
        });
        auto value = boom::MakeShared<boom::js::Value>(context, (void*)object);
        auto proto = context->globalThis()->getProperty("Function")
                                          ->getProperty("prototype");
        if (proto->isObject()) {
            value->setPrototypeOf(proto);
            return value;
        } else {
            throw boom::Error("\"globalThis.Function\" is not an object");
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to construct a function");
    }
}

} /* namespace boom::js */