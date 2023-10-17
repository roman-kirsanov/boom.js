#pragma once

#include <Boom/Memory.hpp>

namespace boom {

class Buffer final : public boom::Shared {
public:
    Buffer();
    Buffer(std::size_t);
    std::size_t size() const;
    std::size_t capacity() const;
    std::uint8_t const* data() const;
    std::uint8_t const* begin() const;
    std::uint8_t const* end() const;
    std::uint8_t* data();
    std::string toString();
    bool empty() const;
    void insert(std::size_t, std::uint8_t const*, std::size_t);
    void insert(std::size_t, std::shared_ptr<boom::Buffer const>);
    void insert(std::size_t, std::string const&);
    void append(std::uint8_t const*, std::size_t);
    void append(std::shared_ptr<boom::Buffer const>);
    void append(std::string const&);
    void remove(std::size_t, std::size_t);
    void reserve(std::size_t);
    void attach(std::uint8_t*, std::size_t, std::size_t);
    void detach();
    void clear();
    virtual ~Buffer();
private:
    std::uint8_t* _data;
    std::size_t _size;
    std::size_t _capacity;
};

} /* namespace boom */