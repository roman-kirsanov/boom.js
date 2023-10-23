#include <stdexcept>
#include <Boom/Image.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

namespace boom {

bool ImageNPatch::operator==(boom::ImageNPatch const& imageNPatch) const {
    return (left == imageNPatch.left)
        && (top == imageNPatch.top)
        && (right == imageNPatch.right)
        && (bottom == imageNPatch.bottom);
}

bool ImageNPatch::operator!=(boom::ImageNPatch const& imageNPatch) const {
    return !operator==(imageNPatch);
}

Image::~Image() {
    _implDone();
}

Image::Image(boom::Vec2 size)
    : _size(size)
    , _impl(nullptr)
{
    _implInit(nullptr, size);
}

Image::Image(std::uint8_t const* data, boom::Vec2 size)
    : _size(size)
    , _impl(nullptr)
{
    _implInit(data, size);
}

boom::Vec2 Image::size() const {
    return _size;
}

std::shared_ptr<boom::Image> Image::FromFile(std::string const& path) {
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    if (data != NULL) {
        auto size = boom::Vec2{ static_cast<float>(width), static_cast<float>(height) };
        auto ret = boom::MakeShared<boom::Image>(data, size);
        free(data);
        return ret;
    } else {
        throw std::runtime_error("Failed to load image with stbi_load");
    }
}

} /* namespace boom */
