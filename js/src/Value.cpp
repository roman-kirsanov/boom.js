#include <string>
#include <cassert>
#include <expected>
#include <iostream>
#include <Boom/JS/Value.hpp>
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

std::expected<bool, boom::js::ValueRef> Value::booleanValue() const {
    if (isBoolean()) {
        return _implBooleanValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a boolean")
        );
    }
}

std::expected<double, boom::js::ValueRef> Value::numberValue() const {
    if (isNumber()) {
        return _implNumberValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a number")
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::stringValue() const {
    if (isString()) {
        return _implStringValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a string")
        );
    }
}

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::arrayBufferValue() const {
    if (isArrayBuffer()) {
        return _implArrayBufferValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an ArrayBuffer")
        );
    }
}

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::uint8ArrayValue() const {
    if (isUint8Array()) {
        return _implUint8ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Uint8Array")
        );
    }
}

std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> Value::uint8ClampedArrayValue() const {
    if (isUint8ClampedArray()) {
        return _implUint8ClampedArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Uint8ClampedArray")
        );
    }
}

std::expected<std::vector<std::uint16_t>, boom::js::ValueRef> Value::uint16ArrayValue() const {
    if (isUint16Array()) {
        return _implUint16ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Uint16Array")
        );
    }
}

std::expected<std::vector<std::uint32_t>, boom::js::ValueRef> Value::uint32ArrayValue() const {
    if (isUint32Array()) {
        return _implUint32ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Uint32Array")
        );
    }
}

std::expected<std::vector<std::int8_t>, boom::js::ValueRef> Value::int8ArrayValue() const {
    if (isInt8Array()) {
        return _implInt8ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Int8Array")
        );
    }
}

std::expected<std::vector<std::int16_t>, boom::js::ValueRef> Value::int16ArrayValue() const {
    if (isInt16Array()) {
        return _implInt16ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Int16Array")
        );
    }
}

std::expected<std::vector<std::int32_t>, boom::js::ValueRef> Value::int32ArrayValue() const {
    if (isInt32Array()) {
        return _implInt32ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Int32Array")
        );
    }
}

std::expected<std::vector<float>, boom::js::ValueRef> Value::float32ArrayValue() const {
    if (isFloat32Array()) {
        return _implFloat32ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Float32Array")
        );
    }
}

std::expected<std::vector<double>, boom::js::ValueRef> Value::float64ArrayValue() const {
    if (isFloat64Array()) {
        return _implFloat64ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an Float64Array")
        );
    }
}

std::expected<std::vector<std::uint64_t>, boom::js::ValueRef> Value::bigUint64ArrayValue() const {
    if (isBigUint64Array()) {
        return _implBigUint64ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an BigUint64Array")
        );
    }
}

std::expected<std::vector<std::int64_t>, boom::js::ValueRef> Value::bigInt64ArrayValue() const {
    if (isBigInt64Array()) {
        return _implBigInt64ArrayValue();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not an BigInt64Array")
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::toString() const {
    return _implToString();
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::getProperty(std::string const& name) {
    return _implGetProperty(name);
}

std::expected<void, boom::js::ValueRef> Value::setProperty(std::string const& name, boom::js::ValueRef value, boom::js::PropertyOptions const& options) {
    if (value == nullptr) {
        std::cerr << "ERROR: boom::js::Value::setProperty() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implSetProperty(name, value, options);
}

std::expected<void, boom::js::ValueRef> Value::defineProperty(std::string const& name, boom::js::Function const& getter) {
    if (getter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"getter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto define = _context->evaluate("Object.defineProperty").value();
    if (define->isFunction()) {
        auto result = define->call(boom::js::Value::Undefined(_context), {
            boom::GetShared<boom::js::Value>(this),
            boom::js::Value::String(_context, name),
            boom::js::Value::Object(_context, {
                { "get", boom::js::Value::Function(_context, getter) }
            })
        });
        if (result) {
            return std::expected<void, boom::js::ValueRef>();
        } else {
            return std::unexpected(result.error());
        }
    } else {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"Object.defineProperty\" is not a function" << std::endl;
        std::exit(-1);
    }
}

std::expected<void, boom::js::ValueRef> Value::defineProperty(std::string const& name, boom::js::Function const& getter, boom::js::Function const& setter) {
    if (getter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"getter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    if (setter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"setter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto define = _context->evaluate("Object.defineProperty").value();
    if (define->isFunction()) {
        auto result = define->call(boom::js::Value::Undefined(_context), {
            boom::GetShared<boom::js::Value>(this),
            boom::js::Value::String(_context, name),
            boom::js::Value::Object(_context, {
                { "get", boom::js::Value::Function(_context, getter) },
                { "set", boom::js::Value::Function(_context, setter) }
            })
        });
        if (result) {
            return std::expected<void, boom::js::ValueRef>();
        } else {
            return std::unexpected(result.error());
        }
    } else {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"Object.defineProperty\" is not a function" << std::endl;
        std::exit(-1);
    }
}

std::expected<void, boom::js::ValueRef> Value::setPrototypeOf(boom::js::ValueRef prototype) {
    if (prototype == nullptr) {
        std::cerr << "ERROR: boom::js::Value::setPrototypeOf() failed: \"prototype\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implSetPrototypeOf(prototype);
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::bind(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    return _implBind(thisObject, arguments);
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::call(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    return _implCall(thisObject, arguments);
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
        std::cerr << "ERROR: boom::js::Value::isStrictEqual() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implIsStrictEqual(value);
}

bool Value::isEqual(boom::js::ValueRef value) const {
    if (value == nullptr) {
        std::cerr << "ERROR: boom::js::Value::isEqual() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implIsEqual(value);
}

void* Value::ref() const {
    return _implRef();
}

boom::js::ValueRef Value::Null(boom::js::ContextRef context) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Null() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplNull(context);
}

boom::js::ValueRef Value::Undefined(boom::js::ContextRef context) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Undefined() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplUndefined(context);
}

boom::js::ValueRef Value::Boolean(boom::js::ContextRef context, bool boolean) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Boolean() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplBoolean(context, boolean);
}

boom::js::ValueRef Value::Number(boom::js::ContextRef context, double number) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Number() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplNumber(context, number);
}

boom::js::ValueRef Value::String(boom::js::ContextRef context, std::string const& string) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::String() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplString(context, string);
}

boom::js::ValueRef Value::Symbol(boom::js::ContextRef context, std::string const& symbol) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Symbol() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplSymbol(context, symbol);
}

boom::js::ValueRef Value::Object(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Object() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplObject(context, props, [](auto, auto){}, [](auto, auto){});
}

boom::js::ValueRef Value::Object(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props, boom::js::Initializer const& init, boom::js::Finalizer const& done) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Object() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplObject(context, props, init, done);
}

boom::js::ValueRef Value::Array(boom::js::ContextRef context, std::vector<boom::js::ValueRef> values) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Array() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplArray(context, values);
}

boom::js::ValueRef Value::Error(boom::js::ContextRef context, std::string const& message) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Error() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplError(context, message);
}

boom::js::ValueRef Value::Function(boom::js::ContextRef context, boom::js::Function const& function) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Function() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _ImplFunction(context, function);
}

} /* namespace boom::js */