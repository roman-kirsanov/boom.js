#pragma once

#include <map>
#include <iostream>
#include <expected>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

struct __ValueImpl;

enum class ValueType {
    Undefined,
    Null,
    Boolean,
    Number,
    String,
    Object,
    Symbol
};

class Value final : public boom::Shared {
public:
    Value(boom::js::ContextRef, void*);
    boom::js::ValueType type() const;
    std::expected<bool, boom::js::ValueRef> asBoolean() const;
    std::expected<double, boom::js::ValueRef> asNumber() const;
    std::expected<std::string, boom::js::ValueRef> asString() const;
    std::expected<std::string, boom::js::ValueRef> toString() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> getProperty(std::string const&);
    std::expected<void, boom::js::ValueRef> setProperty(std::string const&, boom::js::ValueRef);
    std::expected<void, boom::js::ValueRef> defineProperty(std::string const&, boom::js::ValueRef);
    std::expected<void, boom::js::ValueRef> defineProperty(std::string const&, boom::js::ValueRef, boom::js::ValueRef);
    std::expected<bool, boom::js::ValueRef> hasProperty(std::string const&) const;
    std::expected<bool, boom::js::ValueRef> isFunction() const;
    std::expected<bool, boom::js::ValueRef> isArray() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> call(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    template<boom::SharedObject T>
    std::shared_ptr<T> getPrivate() const;
    template<boom::SharedObject T>
    void setPrivate(std::shared_ptr<T>);
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
    boom::js::ValueType _implType() const;
    std::expected<bool, boom::js::ValueRef> _implAsBoolean() const;
    std::expected<double, boom::js::ValueRef> _implAsNumber() const;
    std::expected<std::string, boom::js::ValueRef> _implAsString() const;
    std::expected<std::string, boom::js::ValueRef> _implToString() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implGetProperty(std::string const&);
    std::expected<void, boom::js::ValueRef> _implSetProperty(std::string const&, boom::js::ValueRef);
    std::expected<bool, boom::js::ValueRef> _implHasProperty(std::string const&) const;
    std::expected<bool, boom::js::ValueRef> _implIsFunction() const;
    std::expected<bool, boom::js::ValueRef> _implIsArray() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implCall(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    std::shared_ptr<boom::Shared> _implGetPrivate() const;
    void _implSetPrivate(std::shared_ptr<boom::Shared>);
    void _implInit(void*);
    void _implDone();
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