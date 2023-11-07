#include <Boom/Font.hpp>

namespace boom {

struct __FontImpl {
    ;
};

void Font::_implInit(std::uint8_t const* data, std::size_t size) {
    _impl = new boom::__FontImpl{
        
    };
}

void Font::_implDone() {
    ;
    delete _impl;
}

std::vector<std::string> Font::_ImplList() {
    auto result = std::vector<std::string>();
    ;
    return result;
}

} /* namespace boom */