#include <string>
#include <cassert>
#include <expected>
#include <iostream>
#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/JS/Value.hpp>
#include <Boom/JS/Scope.hpp>
#include <Boom/JS/Context.hpp>

namespace boom::js {

Value::~Value() {
    _implDone();
}

Value::Value(boom::js::ContextRef context, void* value)
    : _context(context)
    , _impl(nullptr)
{
    assert(_context != nullptr);
    assert(value != nullptr);
    _implInit(value);
}

bool Value::booleanValue() const {
    if (isBoolean()) {
        return _implBooleanValue();
    } else {
        throw boom::Error("Value is not a boolean");
    }
}

double Value::numberValue() const {
    if (isNumber()) {
        return _implNumberValue();
    } else {
        throw boom::Error("Value is not a number");
    }
}

std::string Value::stringValue() const {
    if (isString()) {
        return _implStringValue();
    } else {
        throw boom::Error("Value is not a string");
    }
}

boom::js::ValueRef Value::functionValue() const {
    if (isFunction()) {
        return boom::MakeShared<boom::js::Value>(_context, ref());
    } else {
        throw boom::Error("Value is not a function");
    }
}

std::map<std::string, boom::js::ValueRef> Value::objectValue() const {
    if (isObject()) {
        return _implObjectValue();
    } else {
        throw boom::Error("Value is not an object");
    }
}

std::vector<boom::js::ValueRef> Value::arrayValue() const {
    if (isArray()) {
        try {
            auto prop = getProperty("length");
            auto length = prop->numberValue();
            auto result = std::vector<boom::js::ValueRef>();
            result.reserve(length);
            for (std::size_t i = 0; i < length; i++) {
                result.push_back(getValueAtIndex(i));
            }
            return result;
        } catch (boom::Error& e) {
            throw e.extend("Value is not an array");
        }
    } else {
        throw boom::Error("Value is not an array");
    }
}

std::vector<std::uint8_t> Value::arrayBufferValue() const {
    if (isArrayBuffer()) {
        return _implArrayBufferValue();
    } else {
        throw boom::Error("Value is not an ArrayBuffer");
    }
}

std::vector<std::uint8_t> Value::uint8ArrayValue() const {
    if (isUint8Array()) {
        return _implUint8ArrayValue();
    } else {
        throw boom::Error("Value is not an Uint8Array");
    }
}

std::vector<std::uint8_t> Value::uint8ClampedArrayValue() const {
    if (isUint8ClampedArray()) {
        return _implUint8ClampedArrayValue();
    } else {
        throw boom::Error("Value is not an Uint8ClampedArray");
    }
}

std::vector<std::uint16_t> Value::uint16ArrayValue() const {
    if (isUint16Array()) {
        return _implUint16ArrayValue();
    } else {
        throw boom::Error("Value is not an Uint16Array");
    }
}

std::vector<std::uint32_t> Value::uint32ArrayValue() const {
    if (isUint32Array()) {
        return _implUint32ArrayValue();
    } else {
        throw boom::Error("Value is not an Uint32Array");
    }
}

std::vector<std::int8_t> Value::int8ArrayValue() const {
    if (isInt8Array()) {
        return _implInt8ArrayValue();
    } else {
        throw boom::Error("Value is not an Int8Array");
    }
}

std::vector<std::int16_t> Value::int16ArrayValue() const {
    if (isInt16Array()) {
        return _implInt16ArrayValue();
    } else {
        throw boom::Error("Value is not an Int16Array");
    }
}

std::vector<std::int32_t> Value::int32ArrayValue() const {
    if (isInt32Array()) {
        return _implInt32ArrayValue();
    } else {
        throw boom::Error("Value is not an Int32Array");
    }
}

std::vector<float> Value::float32ArrayValue() const {
    if (isFloat32Array()) {
        return _implFloat32ArrayValue();
    } else {
        throw boom::Error("Value is not a Float32Array");
    }
}

std::vector<double> Value::float64ArrayValue() const {
    if (isFloat64Array()) {
        return _implFloat64ArrayValue();
    } else {
        throw boom::Error("Value is not a Float64Array");
    }
}

std::vector<std::uint64_t> Value::bigUint64ArrayValue() const {
    if (isBigUint64Array()) {
        return _implBigUint64ArrayValue();
    } else {
        throw boom::Error("Value is not a BigUint64Array");
    }
}

std::vector<std::int64_t> Value::bigInt64ArrayValue() const {
    if (isBigInt64Array()) {
        return _implBigInt64ArrayValue();
    } else {
        throw boom::Error("Value is not a BigInt64Array");
    }
}

std::string Value::toString() const {
    return _implToString();
}

std::vector<std::string> Value::listProperties() const {
    if (isObject()) {
        return _implListProperties();
    } else {
        throw boom::Error("Value is not an Object");
    }
}

boom::js::ValueRef Value::getValueAtIndex(std::int64_t index) const {
    return _implGetValueAtIndex(index);
}

boom::js::ValueRef Value::getProperty(std::string const& name) const {
    return _implGetProperty(name);
}

void Value::setProperty(std::string const& name, boom::js::ValueRef value, boom::js::PropertyOptions const& options) {
    if (value == nullptr) {
        boom::Abort("boom::js::Value::setProperty() failed: \"value\" cannot be nullptr");
    }
    return _implSetProperty(name, value, options);
}

void Value::defineProperty(std::string const& name, boom::js::Getter const& getter) {
    try {
        auto getterFn = [getter](boom::js::ScopeRef scope) { return getter(scope); };
        auto define = _context->evaluate("Object.defineProperty");
        if (define->isFunction()) {
            define->call(boom::js::Value::Undefined(_context), {
                boom::GetShared<boom::js::Value>(this),
                boom::js::Value::String(_context, name),
                boom::js::Value::Object(_context, {
                    { "get", boom::js::Value::Function(_context, getterFn) }
                })
            });
        } else {
            throw boom::Error("\"Object.defineProperty\" is not a function");
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to define a property");
    }
}

void Value::defineProperty(std::string const& name, boom::js::Getter const& getter, boom::js::Setter const& setter) {
    try {
        auto getterFn = [getter](boom::js::ScopeRef scope) { return getter(scope); };
        auto setterFn = [setter](boom::js::ScopeRef scope) {
            setter(scope, scope->getArg(0));
            return boom::js::Value::Undefined(scope->context());
        };
        auto define = _context->evaluate("Object.defineProperty");
        if (define->isFunction()) {
            define->call(boom::js::Value::Undefined(_context), {
                boom::GetShared<boom::js::Value>(this),
                boom::js::Value::String(_context, name),
                boom::js::Value::Object(_context, {
                    { "get", boom::js::Value::Function(_context, getterFn) },
                    { "set", boom::js::Value::Function(_context, setterFn) }
                })
            });
        } else {
            throw boom::Error("\"globalThis.Object.defineProperty\" is not a function");
        }
    } catch (boom::Error& e) {
        throw e.extend("Failed to define a property");
    }
}

void Value::setPrototypeOf(boom::js::ValueRef prototype) {
    if (prototype == nullptr) {
        boom::Abort("boom::js::Value::setPrototypeOf() failed: \"prototype\" cannot be nullptr");
    }
    return _implSetPrototypeOf(prototype);
}

boom::js::ValueRef Value::bind(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    return _implBind(thisObject, arguments);
}

boom::js::ValueRef Value::call(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    return _implCall(thisObject, arguments);
}

void Value::setDestructor(boom::js::Destructor const& destructor) {
    _implSetDestructor(destructor);
}

bool Value::hasProperty(std::string const& name) const {
    return _implHasProperty(name);
}

bool Value::isNull() const {
    return _implIsNull();
}

bool Value::isUndefined() const {
    return _implIsUndefined();
}

bool Value::isBoolean() const {
    return _implIsBoolean();
}

bool Value::isNumber() const {
    return _implIsNumber();
}

bool Value::isString() const {
    return _implIsString();
}

bool Value::isObject() const {
    return _implIsObject();
}

bool Value::isSymbol() const {
    return _implIsSymbol();
}

bool Value::isFunction() const {
    return _implIsFunction();
}

bool Value::isArray() const {
    return _implIsArray();
}

bool Value::isArrayBuffer() const {
    return _implIsArrayBuffer();
}

bool Value::isUint8Array() const {
    return _implIsUint8Array();
}

bool Value::isUint8ClampedArray() const {
    return _implIsUint8ClampedArray();
}

bool Value::isUint16Array() const {
    return _implIsUint16Array();
}

bool Value::isUint32Array() const {
    return _implIsUint32Array();
}

bool Value::isInt8Array() const {
    return _implIsInt8Array();
}

bool Value::isInt16Array() const {
    return _implIsInt16Array();
}

bool Value::isInt32Array() const {
    return _implIsInt32Array();
}

bool Value::isFloat32Array() const {
    return _implIsFloat32Array();
}

bool Value::isFloat64Array() const {
    return _implIsFloat64Array();
}

bool Value::isBigUint64Array() const {
    return _implIsBigUint64Array();
}

bool Value::isBigInt64Array() const {
    return _implIsBigInt64Array();
}

bool Value::isStrictEqual(boom::js::ValueRef value) const {
    if (value == nullptr) {
        boom::Abort("boom::js::Value::isStrictEqual() failed: \"value\" cannot be nullptr");
    }
    return _implIsStrictEqual(value);
}

bool Value::isEqual(boom::js::ValueRef value) const {
    if (value == nullptr) {
        boom::Abort("boom::js::Value::isEqual() failed: \"value\" cannot be nullptr");
    }
    return _implIsEqual(value);
}

void* Value::ref() const {
    return _implRef();
}

boom::js::ValueRef Value::Null(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Null() failed: \"context\" cannot be nullptr");
    }
    return _ImplNull(context);
}

boom::js::ValueRef Value::Undefined(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Undefined() failed: \"context\" cannot be nullptr");
    }
    return _ImplUndefined(context);
}

boom::js::ValueRef Value::Boolean(boom::js::ContextRef context, bool boolean) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Boolean() failed: \"context\" cannot be nullptr");
    }
    return _ImplBoolean(context, boolean);
}

boom::js::ValueRef Value::Number(boom::js::ContextRef context, double number) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Number() failed: \"context\" cannot be nullptr");
    }
    return _ImplNumber(context, number);
}

boom::js::ValueRef Value::String(boom::js::ContextRef context, std::string const& string) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::String() failed: \"context\" cannot be nullptr");
    }
    return _ImplString(context, string);
}

boom::js::ValueRef Value::Symbol(boom::js::ContextRef context, std::string const& symbol) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Symbol() failed: \"context\" cannot be nullptr");
    }
    return _ImplSymbol(context, symbol);
}

boom::js::ValueRef Value::Object(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props, boom::js::ObjectOptions const& options) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Object() failed: \"context\" cannot be nullptr");
    }
    return _ImplObject(context, props, options);
}

boom::js::ValueRef Value::Array(boom::js::ContextRef context, std::vector<boom::js::ValueRef> values) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Array() failed: \"context\" cannot be nullptr");
    }
    return _ImplArray(context, values);
}

boom::js::ValueRef Value::Error(boom::js::ContextRef context, std::string const& message) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Error() failed: \"context\" cannot be nullptr");
    }
    return _ImplError(context, message);
}

boom::js::ValueRef Value::Function(boom::js::ContextRef context, boom::js::Function const& function) {
    if (context == nullptr) {
        boom::Abort("boom::js::Value::Function() failed: \"context\" cannot be nullptr");
    }
    return _ImplFunction(context, function);
}

} /* namespace boom::js */