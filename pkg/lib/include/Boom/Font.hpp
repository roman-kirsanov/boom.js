#pragma once

#include <string>
#include <vector>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

struct __FontImpl;

class Font;

using FontRef = std::shared_ptr<boom::Font>;
using FontCRef = std::shared_ptr<boom::Font const>;

class Font final : public boom::Shared {
public:
    Font(std::uint8_t const*, std::size_t);
    Font(boom::BufferCRef);
    virtual ~Font();
    static std::vector<std::string> List();
private:
    boom::__FontImpl* _impl;
    void _implInit(std::uint8_t const*, std::size_t);
    void _implDone();
    static std::vector<std::string> _ImplList();
};

} /* namespace boom */