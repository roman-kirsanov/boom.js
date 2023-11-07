#pragma once

#include <string>
#include <vector>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

struct __FontImpl;

class Font final : public boom::Shared {
public:
    Font(std::uint8_t const*, std::size_t);
    Font(std::shared_ptr<boom::Buffer>);
    virtual ~Font();
    static std::vector<std::string> List();
private:
    boom::__FontImpl* _impl;
    void _implInit(std::uint8_t const*, std::size_t);
    void _implDone();
    static std::vector<std::string> _ImplList();
};

} /* namespace boom */