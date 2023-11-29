#pragma once

#include <map>
#include <string>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

class Class;

using ClassRef = std::shared_ptr<boom::js::Class>;
using ClassCRef = std::shared_ptr<boom::js::Class const>;
using ClassWRef = std::weak_ptr<boom::js::Class>;
using ClassCWRef = std::weak_ptr<boom::js::Class const>;

class Class final : public boom::Shared {
public:
    Class(std::string const&);
    Class(std::string const&, boom::js::ClassCRef);
    std::string const& name() const;
    boom::js::ClassCRef parent() const;
    void setConstructor(boom::js::Constructor const&);
    void setDestructor(boom::js::Destructor const&);
    void defineProperty(std::string const&, boom::js::Getter const&);
    void defineProperty(std::string const&, boom::js::Getter const&, boom::js::Setter const&);
    void defineMethod(std::string const&, boom::js::Function const&);
    void defineStaticProperty(std::string const&, boom::js::Getter const&);
    void defineStaticProperty(std::string const&, boom::js::Getter const&, boom::js::Setter const&);
    void defineStaticMethod(std::string const&, boom::js::Function const&);
    void install(boom::js::ContextRef);
    virtual ~Class();
private:
    struct Property {
        std::string name;
        boom::js::Getter getter;
        std::optional<boom::js::Setter> setter;
    };
    struct Method {
        std::string name;
        boom::js::Function function;
    };
    std::string _name;
    boom::js::ClassCRef _parent;
    boom::js::Constructor _constructor;
    boom::js::Destructor _destructor;
    std::vector<Property> _properties;
    std::vector<Method> _methods;
    std::vector<Property> _staticProperties;
    std::vector<Method> _staticMethods;
};

} /* namespace boom::js */