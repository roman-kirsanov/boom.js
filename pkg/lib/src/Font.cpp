#include <Boom/Utilities.hpp>
#include <Boom/Error.hpp>
#include <Boom/File.hpp>
#include <Boom/Font.hpp>

namespace boom {

Font::~Font() {
    _implDone();
}

Font::Font(std::uint8_t const* data, std::size_t size)
    : _impl(nullptr)
{
    if (data == nullptr) {
        boom::Abort("boom::Font::Font() failed: \"data\" cannot be nullptr");
    }
    _implInit(data, size);
}

Font::Font(std::shared_ptr<boom::Buffer> buffer)
    : _impl(nullptr)
{
    _implInit(buffer->data(), buffer->size());
}

std::vector<std::string> Font::List() {
    return _ImplList();
}

} /* namespace boom */