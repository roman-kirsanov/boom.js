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
    boom::OpenGL::Shared()->deleteTextures(1, &_textureId);
}

Image::Image(boom::Vec2 size)
    : Image(nullptr, size) {}

Image::Image(std::uint8_t const* data, boom::Vec2 size)
    : _size(size)
    , _textureId(0)
{
    boom::OpenGL::Shared()->genTextures(1, &_textureId);
    boom::OpenGL::Shared()->bindTexture(boom::kOpenGLTexture2d, _textureId);
    boom::OpenGL::Shared()->texImage2D(boom::kOpenGLTexture2d, 0, boom::kOpenGLRgba, size.width, size.height, 0, boom::kOpenGLRgba, boom::kOpenGLUnsignedByte, nullptr);
    if (data != nullptr) {
        boom::OpenGL::Shared()->texSubImage2D(boom::kOpenGLTexture2d, 0, 0, 0, size.width, size.height, boom::kOpenGLRgba, boom::kOpenGLUnsignedByte, data);
    }
    boom::OpenGL::Shared()->bindTexture(boom::kOpenGLTexture2d, 0);
}

boom::Vec2 Image::size() const {
    return _size;
}

boom::ImageRef Image::FromFile(std::string const& path) {
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
