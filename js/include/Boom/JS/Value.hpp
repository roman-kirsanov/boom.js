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
    Value(boom::js::ContextRef);
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
    std::expected<bool, boom::js::ValueRef> ofClass(boom::js::ClassRef) const;
    std::expected<bool, boom::js::ValueRef> isFunction() const;
    std::expected<bool, boom::js::ValueRef> isArray() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> call(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
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
    static boom::js::ValueRef Array(boom::js::ContextRef, std::vector<boom::js::ValueRef>);
    static boom::js::ValueRef Error(boom::js::ContextRef, std::string const&);
    template<boom::Tag Tag>
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
    std::expected<bool, boom::js::ValueRef> _implOfClass(boom::js::ClassRef) const;
    std::expected<bool, boom::js::ValueRef> _implIsFunction() const;
    std::expected<bool, boom::js::ValueRef> _implIsArray() const;
    std::expected<boom::js::ValueRef, boom::js::ValueRef> _implCall(boom::js::ValueRef, std::vector<boom::js::ValueRef>) const;
    void _implInit(void*);
    void _implDone();
    void _implSetNull();
    void _implSetUndefined();
    void _implSetBoolean(bool);
    void _implSetNumber(double);
    void _implSetString(std::string const&);
    void _implSetSymbol(std::string const&);
    void _implSetObject(std::map<std::string, boom::js::ValueRef>);
    void _implSetArray(std::vector<boom::js::ValueRef>);
    void _implSetError(std::string const&);
    void _implSetFunction(void*);
    bool _implIsStrictEqual(boom::js::ValueRef) const;
    bool _implIsEqual(boom::js::ValueRef) const;
    void* _implRef() const;
    friend boom::js::Context;
};

#ifdef __JSC__
#ifndef JSBase_h

using __FnPtr = void *(*)(void *, void *, void *, size_t, const void **, void **);

extern "C" void* JSValueMakeUndefined(void*);

template<boom::Tag Tag>
boom::js::ValueRef Value::Function(boom::js::ContextRef context, boom::js::Function const& function) {
    static boom::js::ContextRef fnCtx = nullptr;
    static boom::js::Function fnImpl = [](auto context, auto, auto) {
        return boom::js::Value::Undefined(context);
    };
    static boom::js::__FnPtr fnPtr = [](auto ctx, auto, auto this_, auto argc, auto argv, auto error) {
        auto thisObject = boom::MakeShared<boom::js::Value>(fnCtx, (void*)this_);
        auto arguments = std::vector<boom::js::ValueRef>();
        arguments.reserve(argc);
        for (size_t i = 0; i < argc; i++) {
            arguments.push_back(
                boom::MakeShared<boom::js::Value>(fnCtx, (void*)argv[i])
            );
        }
        auto result = fnImpl(fnCtx, thisObject, arguments);
        if (result) {
            return result.value()->ref();
        } else {
            *error = result.error()->ref();
            return JSValueMakeUndefined(ctx);
        }
    };
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Function() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
#ifndef NDEBUG
    static auto duplicate = std::vector<std::string>();
    if (std::find(duplicate.begin(), duplicate.end(), Tag.value) == duplicate.end()) {
        duplicate.push_back(Tag.value);
    } else {
        std::cerr << "ERROR: boom::js::Value::Function() failed: Duplucate function tag found: \"" << Tag.value << "\"" << std::endl;
        std::exit(-1);
    }
#endif
    fnCtx = context;
    fnImpl = function;
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetFunction((void*)(__FnPtr)fnPtr);
    return value;
}

#endif
#endif

} /* namespace boom::js */