#pragma once

#include <map>
#include <iostream>
#include <expected>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ValueImpl;

struct PropertyOptions {
    bool readOnly;
};

class Value final : public boom::Shared {
public:
    Value(boom::js::ContextRef, void*);
    std::expected<bool, boom::js::ValueRef> booleanValue() const;
    std::expected<double, boom::js::ValueRef> numberValue() const;
    std::expected<std::string, boom::js::ValueRef> stringValue() const;
    std::expected<std::map<std::string, boom::js::ValueRef>, boom::js::ValueRef> objectValue() const;
    std::expected<std::vector<boom::js::ValueRef>, boom::js::ValueRef> arrayValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> arrayBufferValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> uint8ArrayValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> uint8ClampedArrayValue() const;
    std::expected<std::vector<std::uint16_t>, boom::js::ValueRef> uint16ArrayValue() const;
    std::expected<std::vector<std::uint32_t>, boom::js::ValueRef> uint32ArrayValue() const;
    std::expected<std::vector<std::int8_t>, boom::js::ValueRef> int8ArrayValue() const;
    std::expected<std::vector<std::int16_t>, boom::js::ValueRef> int16ArrayValue() const;
    std::expected<std::vector<std::int32_t>, boom::js::ValueRef> int32ArrayValue() const;
    std::expected<std::vector<float>, boom::js::ValueRef> float32ArrayValue() const;
    std::expected<std::vector<double>, boom::js::ValueRef> float64ArrayValue() const;
    std::expected<std::vector<std::uint64_t>, boom::js::ValueRef> bigUint64ArrayValue() const;
    std::expected<std::vector<std::int64_t>, boom::js::ValueRef> bigInt64ArrayValue() const;
    std::expected<std::string, boom::js::ValueRef> toString() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> getProperty(std::string const&);
    std::expected<void, boom::js::ValueRef> setProperty(std::string const&, boom::js::ValueRef, boom::js::PropertyOptions const& = {});
    std::expected<void, boom::js::ValueRef> defineProperty(std::string const&, boom::js::Function const&);
    std::expected<void, boom::js::ValueRef> defineProperty(std::string const&, boom::js::Function const&, boom::js::Function const&);
    std::expected<void, boom::js::ValueRef> setPrototypeOf(boom::js::ValueRef);
    std::expected<boom::js::ValueRef, boom::js::ValueRef> bind(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> call(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    template<boom::SharedObject T>
    std::shared_ptr<T> getPrivate() const;
    template<boom::SharedObject T>
    void setPrivate(std::shared_ptr<T>);
    bool hasProperty(std::string const&) const;
    bool isNull() const;
    bool isUndefined() const;
    bool isBoolean() const;
    bool isNumber() const;
    bool isString() const;
    bool isObject() const;
    bool isSymbol() const;
    bool isFunction() const;
    bool isArray() const;
    bool isArrayBuffer() const;
    bool isUint8Array() const;
    bool isUint8ClampedArray() const;
    bool isUint16Array() const;
    bool isUint32Array() const;
    bool isInt8Array() const;
    bool isInt16Array() const;
    bool isInt32Array() const;
    bool isFloat32Array() const;
    bool isFloat64Array() const;
    bool isBigUint64Array() const;
    bool isBigInt64Array() const;
    bool isStrictEqual(boom::js::ValueRef) const;
    bool isEqual(boom::js::ValueRef) const;
    void* ref() const;
    virtual ~Value();
    static boom::js::ValueRef Null(boom::js::ContextRef);
    static boom::js::ValueRef Undefined(boom::js::ContextRef);
    static boom::js::ValueRef Boolean(boom::js::ContextRef, bool);
    static boom::js::ValueRef Number(boom::js::ContextRef, double);
    static boom::js::ValueRef String(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef Symbol(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef Object(boom::js::ContextRef, std::map<std::string, boom::js::ValueRef>);
    static boom::js::ValueRef Object(boom::js::ContextRef, std::map<std::string, boom::js::ValueRef>, boom::js::Initializer const&, boom::js::Finalizer const&);
    static boom::js::ValueRef Array(boom::js::ContextRef, std::vector<boom::js::ValueRef>);
    static boom::js::ValueRef Error(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef Function(boom::js::ContextRef, boom::js::Function const&);
private:
    boom::js::ContextRef _context;
    boom::js::__ValueImpl* _impl;
    std::expected<bool, boom::js::ValueRef> _implBooleanValue() const;
    std::expected<double, boom::js::ValueRef> _implNumberValue() const;
    std::expected<std::string, boom::js::ValueRef> _implStringValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> _implArrayBufferValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> _implUint8ArrayValue() const;
    std::expected<std::vector<std::uint8_t>, boom::js::ValueRef> _implUint8ClampedArrayValue() const;
    std::expected<std::vector<std::uint16_t>, boom::js::ValueRef> _implUint16ArrayValue() const;
    std::expected<std::vector<std::uint32_t>, boom::js::ValueRef> _implUint32ArrayValue() const;
    std::expected<std::vector<std::int8_t>, boom::js::ValueRef> _implInt8ArrayValue() const;
    std::expected<std::vector<std::int16_t>, boom::js::ValueRef> _implInt16ArrayValue() const;
    std::expected<std::vector<std::int32_t>, boom::js::ValueRef> _implInt32ArrayValue() const;
    std::expected<std::vector<float>, boom::js::ValueRef> _implFloat32ArrayValue() const;
    std::expected<std::vector<double>, boom::js::ValueRef> _implFloat64ArrayValue() const;
    std::expected<std::vector<std::uint64_t>, boom::js::ValueRef> _implBigUint64ArrayValue() const;
    std::expected<std::vector<std::int64_t>, boom::js::ValueRef> _implBigInt64ArrayValue() const;
    std::expected<std::string, boom::js::ValueRef> _implToString() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implGetProperty(std::string const&);
    std::expected<void, boom::js::ValueRef> _implSetProperty(std::string const&, boom::js::ValueRef, boom::js::PropertyOptions const&);
    std::expected<void, boom::js::ValueRef> _implSetPrototypeOf(boom::js::ValueRef);
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implBind(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implCall(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    std::shared_ptr<boom::Shared> _implGetPrivate() const;
    void _implSetPrivate(std::shared_ptr<boom::Shared>);
    void _implInit(void*);
    void _implDone();
    bool _implHasProperty(std::string const&) const;
    bool _implIsNull() const;
    bool _implIsUndefined() const;
    bool _implIsBoolean() const;
    bool _implIsNumber() const;
    bool _implIsString() const;
    bool _implIsObject() const;
    bool _implIsSymbol() const;
    bool _implIsFunction() const;
    bool _implIsArray() const;
    bool _implIsArrayBuffer() const;
    bool _implIsUint8Array() const;
    bool _implIsUint8ClampedArray() const;
    bool _implIsUint16Array() const;
    bool _implIsUint32Array() const;
    bool _implIsInt8Array() const;
    bool _implIsInt16Array() const;
    bool _implIsInt32Array() const;
    bool _implIsFloat32Array() const;
    bool _implIsFloat64Array() const;
    bool _implIsBigUint64Array() const;
    bool _implIsBigInt64Array() const;
    bool _implIsStrictEqual(boom::js::ValueRef) const;
    bool _implIsEqual(boom::js::ValueRef) const;
    void* _implRef() const;
    static boom::js::ValueRef _ImplNull(boom::js::ContextRef);
    static boom::js::ValueRef _ImplUndefined(boom::js::ContextRef);
    static boom::js::ValueRef _ImplBoolean(boom::js::ContextRef, bool);
    static boom::js::ValueRef _ImplNumber(boom::js::ContextRef, double);
    static boom::js::ValueRef _ImplString(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef _ImplSymbol(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef _ImplObject(boom::js::ContextRef, std::map<std::string, boom::js::ValueRef>, boom::js::Initializer const&, boom::js::Finalizer const&);
    static boom::js::ValueRef _ImplArray(boom::js::ContextRef, std::vector<boom::js::ValueRef>);
    static boom::js::ValueRef _ImplError(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef _ImplFunction(boom::js::ContextRef, boom::js::Function const&);
    friend boom::js::Context;
};

template<boom::SharedObject T>
inline std::shared_ptr<T> Value::getPrivate() const {
    auto data = _implGetPrivate();
    if (data != nullptr) {
        if (auto object = std::dynamic_pointer_cast<T>(data)) {
            return object;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

template<boom::SharedObject T>
inline void Value::setPrivate(std::shared_ptr<T> object) {
    _implSetPrivate(object);
}

} /* namespace boom::js */