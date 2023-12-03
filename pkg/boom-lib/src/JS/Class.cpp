#include <cassert>
#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/JS/Context.hpp>
#include <Boom/JS/Scope.hpp>
#include <Boom/JS/Value.hpp>
#include <Boom/JS/Class.hpp>

namespace boom::js {

Class::~Class() {}

Class::Class(std::string const& name)
    : _name(name)
    , _parent(nullptr)
    , _constructor()
    , _destructor()
    , _properties()
    , _methods()
    , _staticProperties()
    , _staticMethods() {}

Class::Class(std::string const& name, boom::js::ClassCRef parent)
    : _name(name)
    , _parent(parent)
    , _constructor()
    , _destructor()
    , _properties()
    , _methods()
    , _staticProperties()
    , _staticMethods() {}

std::string const& Class::name() const {
    return _name;
}

boom::js::ClassCRef Class::parent() const {
    return _parent;
}

void Class::setConstructor(boom::js::Constructor const& constructor) {
    _constructor = constructor;
}

void Class::setDestructor(boom::js::Destructor const& destructor) {
    _destructor = destructor;
}

void Class::defineProperty(std::string const& name, boom::js::Getter const& getter) {
    for (auto& property : _properties) {
        if (property.name == name) {
            throw boom::Error("Property \"" + name + "\" already defined");
        }
    }
    _properties.push_back({ name, getter, std::nullopt });
}

void Class::defineProperty(std::string const& name, boom::js::Getter const& getter, boom::js::Setter const& setter) {
    for (auto& property : _properties) {
        if (property.name == name) {
            throw boom::Error("Property \"" + name + "\" already defined");
        }
    }
    _properties.push_back({ name, getter, setter });
}

void Class::defineStaticProperty(std::string const& name, boom::js::Getter const& getter) {
    for (auto& property : _staticProperties) {
        if (property.name == name) {
            throw boom::Error("Static property \"" + name + "\" already defined");
        }
    }
    _staticProperties.push_back({ name, getter, std::nullopt });
}

void Class::defineStaticProperty(std::string const& name, boom::js::Getter const& getter, boom::js::Setter const& setter) {
    for (auto& property : _staticProperties) {
        if (property.name == name) {
            throw boom::Error("Static property \"" + name + "\" already defined");
        }
    }
    _staticProperties.push_back({ name, getter, setter });
}

void Class::defineMethod(std::string const& name, boom::js::Function const& function) {
    for (auto& method : _methods) {
        if (method.name == name) {
            throw boom::Error("Method \"" + name + "\" already defined");
        }
    }
    _methods.push_back({ name, function });
}

void Class::defineStaticMethod(std::string const& name, boom::js::Function const& function) {
    for (auto& method : _staticMethods) {
        if (method.name == name) {
            throw boom::Error("Static method \"" + name + "\" already defined");
        }
    }
    _staticMethods.push_back({ name, function });
}

void Class::install(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::js::Class::install() failed: \"context\" cannot be nullptr");
    }
    if (_name.empty()) {
        boom::Abort("boom::js::Class::install() failed: \"name\" cannot be empty");
    }
    auto proto = boom::js::Value::Object(context);
    for (auto& property : _properties) {
        if (property.setter.has_value()) {
            proto->defineProperty(property.name, property.getter, property.setter.value());
        } else {
            proto->defineProperty(property.name, property.getter);
        }
    }
    for (auto& method : _methods) {
        proto->setProperty(method.name, boom::js::Value::Function(context, method.function), { .readOnly = true });
    }
    if (_parent != nullptr) {
        proto->setProperty("__proto__", context->globalThis()->getProperty(_parent->name()));
    }
    auto class_ = boom::js::Value::Function(context, [ctor=_constructor, dtor=_destructor](boom::js::ScopeRef scope) {
        ctor(scope);
        scope->thisObject()->setDestructor(dtor);
        return boom::js::Value::Undefined(scope->context());
    });
    for (auto& property : _staticProperties) {
        if (property.setter.has_value()) {
            class_->defineProperty(property.name, property.getter, property.setter.value());
        } else {
            class_->defineProperty(property.name, property.getter);
        }
    }
    for (auto& method : _staticMethods) {
        class_->setProperty(method.name, boom::js::Value::Function(context, method.function), { .readOnly = true });
    }
    class_->setProperty("prototype", proto);
    context->globalThis()->setProperty(_name, class_);
}

} /* namespace boom::js */