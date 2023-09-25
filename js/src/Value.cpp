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

Value::Value(boom::js::ContextRef context)
    : _context(context)
    , _impl(nullptr)
{
    assert(_context != nullptr);
    _implInit(nullptr);
}

Value::Value(boom::js::ContextRef context, void* value)
    : _context(context)
    , _impl(nullptr)
{
    assert(_context != nullptr);
    assert(value != nullptr);
    _implInit(value);
}

boom::js::ValueType Value::type() const {
    return _implType();
}

std::expected<bool, boom::js::ValueRef> Value::asBoolean() const {
    if (type() == boom::js::ValueType::Boolean) {
        return _implAsBoolean();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a boolean")
        );
    }
}

std::expected<double, boom::js::ValueRef> Value::asNumber() const {
    if (type() == boom::js::ValueType::Number) {
        return _implAsNumber();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a number")
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::asString() const {
    if (type() == boom::js::ValueType::String) {
        return _implAsString();
    } else {
        return std::unexpected(
            boom::js::Value::Error(_context, "Value is not a string")
        );
    }
}

std::expected<std::string, boom::js::ValueRef> Value::toString() const {
    return _implToString();
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::getProperty(std::string const& name) {
    return _implGetProperty(name);
}

std::expected<bool, boom::js::ValueRef> Value::hasProperty(std::string const& name) const {
    return _implHasProperty(name);
}

std::expected<void, boom::js::ValueRef> Value::setProperty(std::string const& name, boom::js::ValueRef value) {
    if (value == nullptr) {
        std::cerr << "ERROR: boom::js::Value::setProperty() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implSetProperty(name, value);
}

std::expected<void, boom::js::ValueRef> Value::defineProperty(std::string const& name, boom::js::ValueRef getter) {
    if (getter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"getter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto define = _context->evaluate("Object.defineProperty").value();
    auto result = define->call(boom::js::Value::Undefined(_context), {
        boom::GetShared<boom::js::Value>(this),
        boom::js::Value::String(_context, name),
        boom::js::Value::Object(_context, {
            { "get", getter }
        })
    });
    if (result) {
        return std::expected<void, boom::js::ValueRef>();
    } else {
        return std::unexpected(result.error());
    }
}

std::expected<void, boom::js::ValueRef> Value::defineProperty(std::string const& name, boom::js::ValueRef getter, boom::js::ValueRef setter) {
    if (getter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"getter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    if (setter == nullptr) {
        std::cerr << "ERROR: boom::js::Value::defineProperty() failed: \"setter\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto define = _context->evaluate("Object.defineProperty").value();
    auto result = define->call(boom::js::Value::Undefined(_context), {
        boom::GetShared<boom::js::Value>(this),
        boom::js::Value::String(_context, name),
        boom::js::Value::Object(_context, {
            { "get", getter },
            { "set", setter }
        })
    });
    if (result) {
        return std::expected<void, boom::js::ValueRef>();
    } else {
        return std::unexpected(result.error());
    }
}

std::expected<bool, boom::js::ValueRef> Value::ofClass(boom::js::ClassRef class_) const {
    if (class_ == nullptr) {
        std::cerr << "ERROR: boom::js::Value::setProperty() failed: \"class\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return _implOfClass(class_);
}

std::expected<bool, boom::js::ValueRef> Value::isFunction() const {
    return _implIsFunction();
}

std::expected<bool, boom::js::ValueRef> Value::isArray() const {
    return _implIsArray();
}

std::expected<boom::js::ValueRef, boom::js::ValueRef> Value::call(boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) const {
    return _implCall(thisObject, arguments);
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
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetNull();
    return value;
}

boom::js::ValueRef Value::Undefined(boom::js::ContextRef context) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Undefined() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetUndefined();
    return value;
}

boom::js::ValueRef Value::Boolean(boom::js::ContextRef context, bool boolean) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Boolean() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetBoolean(boolean);
    return value;
}

boom::js::ValueRef Value::Number(boom::js::ContextRef context, double number) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Number() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetNumber(number);
    return value;
}

boom::js::ValueRef Value::String(boom::js::ContextRef context, std::string const& string) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::String() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetString(string);
    return value;
}

boom::js::ValueRef Value::Symbol(boom::js::ContextRef context, std::string const& symbol) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Symbol() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetSymbol(symbol);
    return value;
}

boom::js::ValueRef Value::Object(boom::js::ContextRef context, std::map<std::string, boom::js::ValueRef> props) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Object() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetObject(props);
    return value;
}

boom::js::ValueRef Value::Array(boom::js::ContextRef context, std::vector<boom::js::ValueRef> values) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Array() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetArray(values);
    return value;
}

boom::js::ValueRef Value::Error(boom::js::ContextRef context, std::string const& message) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Value::Error() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto value = boom::MakeShared<boom::js::Value>(context);
    value->_implSetError(message);
    return value;
}

} /* namespace boom::js */