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

template<typename T>
std::expected<std::vector<T>, JSValueRef> TypedArrayValue(JSContextRef context, JSObjectRef object) {
    auto error = (JSValueRef)nullptr;
    auto ptr = (uint8_t*)JSObjectGetTypedArrayBytesPtr(context, object, &error);
    if (error != nullptr) {
        return std::unexpected(error);
    }
    auto size = JSObjectGetTypedArrayByteLength(context, object, &error);
    if (error != nullptr) {
        return std::unexpected(error);
    }
    auto offset = JSObjectGetTypedArrayByteOffset(context, object, &error);
    if (error != nullptr) {
        return std::unexpected(error);
    }
    auto length = JSObjectGetTypedArrayLength(context, object, &error);
    if (error != nullptr) {
        return std::unexpected(error);
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

std::expected<bool, boom::js::ValueRef> Value::_implBooleanValue() const {
    assert(isBoolean() == true);
    return JSValueToBoolean(_context->_impl->context, _impl->value);
}

std::expected<double, boom::js::ValueRef> Value::_implNumberValue() const {
    assert(isNumber() == true);
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

std::expected<std::string, boom::js::ValueRef> Value::_implStringValue() const {
    assert(isString() == true);
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

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::_implArrayBufferValue() const {
    assert(isArrayBuffer() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto data = (uint8_t*)JSObjectGetArrayBufferBytesPtr(_context->_impl->context, object, &error);
        if (error == nullptr) {
            auto size = JSObjectGetArrayBufferByteLength(_context->_impl->context, object, &error);
            if (error == nullptr) {
                return std::vector<std::uint8_t>(data, (data + size));
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
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::_implUint8ArrayValue() const {
    assert(isUint8Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<uint8_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::_implUint8ClampedArrayValue() const {
    assert(isUint8ClampedArray() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<uint8_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::uint16_t>, boom::js::ValueRef> Value::_implUint16ArrayValue() const {
    assert(isUint16Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<uint16_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::uint32_t>, boom::js::ValueRef> Value::_implUint32ArrayValue() const {
    assert(isUint32Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<uint32_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::int8_t>, boom::js::ValueRef> Value::_implInt8ArrayValue() const {
    assert(isInt8Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<int8_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::int16_t>, boom::js::ValueRef> Value::_implInt16ArrayValue() const {
    assert(isInt16Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<int16_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::int32_t>, boom::js::ValueRef> Value::_implInt32ArrayValue() const {
    assert(isInt32Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<int32_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<float>, boom::js::ValueRef> Value::_implFloat32ArrayValue() const {
    assert(isFloat32Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<float>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<double>, boom::js::ValueRef> Value::_implFloat64ArrayValue() const {
    assert(isFloat64Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<double>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::uint64_t>, boom::js::ValueRef> Value::_implBigUint64ArrayValue() const {
    assert(isBigUint64Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<uint64_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
    } else {
        return std::unexpected(
            boom::MakeShared<boom::js::Value>(_context, (void*)error)
        );
    }
}

std::expected<std::vector<std::int64_t>, boom::js::ValueRef> Value::_implBigInt64ArrayValue() const {
    assert(isBigInt64Array() == true);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto value = boom::js::TypedArrayValue<int64_t>(_context->_impl->context, object);
        if (value) {
            return value.value();
        } else {
            return std::unexpected(
                boom::MakeShared<boom::js::Value>(_context, (void*)value.error())
            );
        }
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

std::expected<void, boom::js::ValueRef> Value::_implSetProperty(std::string const& name, boom::js::ValueRef value, boom::js::PropertyOptions const& options) {
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
            options.readOnly ? kJSPropertyAttributeReadOnly : kJSPropertyAttributeNone,
            &error
        );
        if (error == nullptr) {
            return std::expected<void, boom::js::ValueRef>();
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

std::expected<void, boom::js::ValueRef> Value::_implSetPrototypeOf(boom::js::ValueRef prototype) {
    assert(prototype != nullptr);
    auto error = (JSValueRef)nullptr;
    auto object = JSValueToObject(_context->_impl->context, _impl->value, &error);
    if (error == nullptr) {
        auto proto = JSValueToObject(_context->_impl->context, prototype->_impl->value, &error);
        if (error == nullptr) {
            JSObjectSetPrototype(_context->_impl->context, object, proto);
            return std::expected<void, boom::js::ValueRef>();
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

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::_implCall(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
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
        .className = "BoomObject",
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
        value->setProperty(pair.first, pair.second).value();
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
    static auto const wrapFn = [](JSContextRef ctx, JSObjectRef fn, JSObjectRef this_, size_t argc, JSValueRef const* argv, JSValueRef* error) -> JSValueRef {
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
    static auto const wrapCtor = [](JSContextRef ctx, JSObjectRef ctor, size_t argc, JSValueRef const* argv, JSValueRef* error) -> JSObjectRef {
        auto priv = (boom::js::FunctionPrivate*)JSObjectGetPrivate(ctor);
        if (priv != nullptr) {
            auto thisObject = boom::js::Value::Object(priv->context);
            auto arguments = std::vector<boom::js::ValueRef>();
            arguments.reserve(argc);
            for (std::size_t i = 0; i < argc; i++) {
                arguments.push_back(
                    boom::MakeShared<boom::js::Value>(priv->context, (void*)argv[i])
                );
            }
            auto ctorObject = boom::MakeShared<boom::js::Value>(priv->context, (void*)ctor);
            auto protoObject = ctorObject->getProperty("prototype");
            if (protoObject && protoObject.value()->isObject()) {
                thisObject->setPrototypeOf(protoObject.value()).value();
            }
            auto result = priv->function.operator()(priv->context, thisObject, arguments);
            auto object = JSValueToObject(ctx, thisObject->_impl->value, nullptr);
            if (!result) {
                *error = result.error()->_impl->value;
            }
            return object;
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
    static auto const classDef = (JSClassDefinition){
        .className = "BoomFunction",
        .finalize = doneFn,
        .callAsFunction = wrapFn,
        .callAsConstructor = wrapCtor
    };
    static auto const classRef = JSClassCreate(&classDef);
    auto object = JSObjectMake(context->_impl->context, classRef, new boom::js::FunctionPrivate{
        .context = context,
        .function = function
    });
    auto value = boom::MakeShared<boom::js::Value>(context, (void*)object);
    auto proto = context->globalThis()->getProperty("Function").value()
                                      ->getProperty("prototype").value();
    if (proto->isObject()) {
        value->setPrototypeOf(proto).value();
        return value;
    } else {
        std::cerr << "ERROR: boom::js::Value::Function() failed: \"Function\" is not an object" << std::endl;
        std::exit(-1);
    }
}

} /* namespace boom::js */