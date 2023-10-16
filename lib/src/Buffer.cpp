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

std::size_t Buffer::size() const {
    return _size;
}

std::size_t Buffer::capacity() const {
    return _capacity;
}

std::uint8_t const* Buffer::data() const {
    return _data;
}

std::uint8_t const* Buffer::cbegin() const {
    return _data;
}

std::uint8_t const* Buffer::cend() const {
    return (_data + _size);
}

std::uint8_t const* Buffer::begin() {
    return _data;
}

std::uint8_t const* Buffer::end() {
    return (_data + _size);
}

std::shared_ptr<boom::String> Buffer::toString() {
    return nullptr; /// TODO: ...
}

std::shared_ptr<boom::String const> Buffer::toString() const {
    return nullptr; /// TODO: ...
}

bool Buffer::empty() const {
    return (_size == 0);
}

void Buffer::insert(std::size_t offset, std::uint8_t const* data, std::size_t size) {
    auto const pos = boom::Clamp<std::size_t>(offset, 0, _size);
    auto const rdst = (_data + pos + size);
    auto const rsize = (_size - pos);
    auto const dst = (_data + pos);
    reserve(_size + size);
    std::memmove(rdst, dst, rsize);
    std::memcpy(dst, data, size);
}

void Buffer::insert(std::size_t offset, std::vector<std::uint8_t> const& data) {
    insert(offset, data.data(), data.size());
}

void Buffer::insert(std::size_t offset, std::string const& data) {
    insert(offset, reinterpret_cast<std::uint8_t const*>(data.data()), data.size());
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

void Buffer::clear() {
    std::memset(_data, 0x0, _capacity);
    _size = 0;
}

} /* namespace boom */