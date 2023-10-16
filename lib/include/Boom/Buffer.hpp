#pragma once

#include <Boom/Memory.hpp>

namespace boom {

class String;

class Buffer final : boom::Shared {
public:
    Buffer();
    Buffer(std::size_t);
    std::size_t size() const;
    std::size_t capacity() const;
    std::uint8_t const* data() const;
    std::uint8_t const* cbegin() const;
    std::uint8_t const* cend() const;
    std::uint8_t const* begin();
    std::uint8_t const* end();
    std::shared_ptr<boom::String> toString();
    std::shared_ptr<boom::String const> toString() const;
    bool empty() const;
    void insert(std::size_t, std::uint8_t const*, std::size_t);
    void insert(std::size_t, std::vector<std::uint8_t> const&);
    void insert(std::size_t, std::string const&);
    void remove(std::size_t, std::size_t);
    void reserve(std::size_t);
    void clear();
    virtual ~Buffer();
private:
    std::uint8_t* _data;
    std::size_t _size;
    std::size_t _capacity;
};

} /* namespace boom */