#pragma once

#include <map>
#include <string>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

class Class final : public boom::Shared {
public:
    Class();
    void setConstructor(boom::js::Constructor const&);
    void setDestructor(boom::js::Destructor const&);
    void defineProperty(std::string const&, boom::js::Getter const&);
    void defineProperty(std::string const&, boom::js::Getter const&, boom::js::Setter const&);
    void defineMethod(std::string const&, boom::js::Function const&);
    void install(std::string const&, boom::js::ContextRef);
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
    boom::js::Constructor _constructor;
    boom::js::Destructor _destructor;
    std::vector<Property> _properties;
    std::vector<Method> _methods;
};

} /* namespace boom::js */