#pragma once

#include <map>
#include <iostream>
#include <optional>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ValueImpl;

struct ObjectOptions {
    bool managed;
    std::optional<boom::js::Finalizer> finalize;
};

struct PropertyOptions {
    bool readOnly;
};

class Value final : public boom::Shared {
public:
    Value(boom::js::ContextRef, void*);
    bool booleanValue() const;
    double numberValue() const;
    std::string stringValue() const;
    std::map<std::string, boom::js::ValueRef> objectValue() const;
    std::vector<boom::js::ValueRef> arrayValue() const;
    boom::js::ValueRef functionValue() const;
    std::vector<std::uint8_t> arrayBufferValue() const;
    std::vector<std::uint8_t> uint8ArrayValue() const;
    std::vector<std::uint8_t> uint8ClampedArrayValue() const;
    std::vector<std::uint16_t> uint16ArrayValue() const;
    std::vector<std::uint32_t> uint32ArrayValue() const;
    std::vector<std::int8_t> int8ArrayValue() const;
    std::vector<std::int16_t> int16ArrayValue() const;
    std::vector<std::int32_t> int32ArrayValue() const;
    std::vector<float> float32ArrayValue() const;
    std::vector<double> float64ArrayValue() const;
    std::vector<std::uint64_t> bigUint64ArrayValue() const;
    std::vector<std::int64_t> bigInt64ArrayValue() const;
    std::string toString() const;
    std::vector<std::string> listProperties() const;
    boom::js::ValueRef getValueAtIndex(std::int64_t) const;
    boom::js::ValueRef getProperty(std::string const&) const;
    void setProperty(std::string const&, boom::js::ValueRef, boom::js::PropertyOptions const& = {});
    void defineProperty(std::string const&, boom::js::Function const&);
    void defineProperty(std::string const&, boom::js::Function const&, boom::js::Function const&);
    void setPrototypeOf(boom::js::ValueRef);
    boom::js::ValueRef bind(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    boom::js::ValueRef call(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    template<boom::SharedObject T>
    std::shared_ptr<T> getPrivate() const;
    template<boom::SharedObject T>
    void setPrivate(std::shared_ptr<T>);
    void setFinalize(boom::js::Finalizer const&);
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
    static boom::js::ValueRef Object(boom::js::ContextRef, std::map<std::string, boom::js::ValueRef> = {}, boom::js::ObjectOptions const& = {});
    static boom::js::ValueRef Array(boom::js::ContextRef, std::vector<boom::js::ValueRef>);
    static boom::js::ValueRef Error(boom::js::ContextRef, std::string const&);
    static boom::js::ValueRef Function(boom::js::ContextRef, boom::js::Function const&);
private:
    boom::js::ContextRef _context;
    boom::js::__ValueImpl* _impl;
    bool _implBooleanValue() const;
    double _implNumberValue() const;
    std::string _implStringValue() const;
    std::map<std::string, boom::js::ValueRef> _implObjectValue() const;
    std::vector<std::uint8_t> _implArrayBufferValue() const;
    std::vector<std::uint8_t> _implUint8ArrayValue() const;
    std::vector<std::uint8_t> _implUint8ClampedArrayValue() const;
    std::vector<std::uint16_t> _implUint16ArrayValue() const;
    std::vector<std::uint32_t> _implUint32ArrayValue() const;
    std::vector<std::int8_t> _implInt8ArrayValue() const;
    std::vector<std::int16_t> _implInt16ArrayValue() const;
    std::vector<std::int32_t> _implInt32ArrayValue() const;
    std::vector<float> _implFloat32ArrayValue() const;
    std::vector<double> _implFloat64ArrayValue() const;
    std::vector<std::uint64_t> _implBigUint64ArrayValue() const;
    std::vector<std::int64_t> _implBigInt64ArrayValue() const;
    std::string _implToString() const;
    std::vector<std::string> _implListProperties() const;
    boom::js::ValueRef _implGetValueAtIndex(std::int64_t) const;
    boom::js::ValueRef _implGetProperty(std::string const&) const;
    void _implSetProperty(std::string const&, boom::js::ValueRef, boom::js::PropertyOptions const&);
    void _implSetPrototypeOf(boom::js::ValueRef);
    boom::js::ValueRef _implBind(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    boom::js::ValueRef _implCall(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    std::shared_ptr<boom::Shared> _implGetPrivate() const;
    void _implSetPrivate(std::shared_ptr<boom::Shared>);
    void _implSetFinalize(boom::js::Finalizer const&);
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
    static boom::js::ValueRef _ImplObject(boom::js::ContextRef, std::map<std::string, boom::js::ValueRef>, boom::js::ObjectOptions const& = {});
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