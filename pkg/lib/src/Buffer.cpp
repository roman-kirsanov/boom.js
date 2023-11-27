#include <cstring>
#include <Boom/Utilities.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

Buffer::~Buffer() {
    if (_data != nullptr) {
        boom::Free(_data);
    }
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

Buffer::Buffer()
    : _data(nullptr)
    , _size(0)
    , _capacity(0) {}

Buffer::Buffer(std::size_t capacity)
    : _data(nullptr)
    , _size(0)
    , _capacity(0)
{
    reserve(capacity);
}

std::size_t Buffer::size() const {
    return _size;
}

std::size_t Buffer::capacity() const {
    return _capacity;
}

std::uint8_t const* Buffer::data() const {
    return _data;
}

std::uint8_t const* Buffer::begin() const {
    return _data;
}

std::uint8_t const* Buffer::end() const {
    return (_data + _size);
}

std::uint8_t* Buffer::data() {
    return _data;
}

std::string Buffer::toString() {
    return std::string(reinterpret_cast<char*>(_data), _size);
}

bool Buffer::empty() const {
    return (_size == 0);
}

void Buffer::insert(std::size_t offset, std::uint8_t const* data, std::size_t size) {
    if (data == nullptr) {
        boom::Abort("boom::Buffer::insert() failed: \"data\" cannot be nullptr");
    }
    auto const pos = boom::Clamp<std::size_t>(offset, 0, _size);
    auto const rdst = (_data + pos + size);
    auto const rsize = (_size - pos);
    auto const dst = (_data + pos);
    reserve(_size + size);
    std::memmove(rdst, dst, rsize);
    std::memcpy(dst, data, size);
}

void Buffer::insert(std::size_t offset, std::shared_ptr<boom::Buffer const> data) {
    insert(offset, data->data(), data->size());
}

void Buffer::insert(std::size_t offset, std::string const& data) {
    insert(offset, reinterpret_cast<std::uint8_t const*>(data.data()), data.size());
}

void Buffer::append(std::uint8_t const* data, std::size_t size) {
    if (data == nullptr) {
        boom::Abort("boom::Buffer::append() failed: \"data\" cannot be nullptr");
    }
    insert(_size, data, size);
}

void Buffer::append(std::shared_ptr<boom::Buffer const> data) {
    append(data->data(), data->size());
}

void Buffer::append(std::string const& data) {
    append(reinterpret_cast<std::uint8_t const*>(data.data()), data.size());
}

void Buffer::remove(std::size_t, std::size_t) {
    ;
}

void Buffer::reserve(std::size_t capacity) {
    if ((capacity + 1) > _capacity) {
        auto data = boom::Alloc<std::uint8_t>(capacity + 1);
        if (_data != nullptr) {
            std::memcpy(data, _data, _size);
            boom::Free(_data);
        }
        _data = data;
        _capacity = (capacity + 1);
    }
}

void Buffer::attach(std::uint8_t* data, std::size_t size, std::size_t capacity) {
    if (_data != nullptr) {
        boom::Free(_data);
    }
    _data = data;
    _size = size;
    _capacity = capacity;
}

void Buffer::detach() {
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

void Buffer::clear() {
    std::memset(_data, 0x0, _capacity);
    _size = 0;
}

} /* namespace boom */