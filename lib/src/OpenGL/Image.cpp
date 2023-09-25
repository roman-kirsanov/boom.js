#include "Context.hpp"
#include "Image.hpp"

namespace boom {

void Image::_implInit(std::uint8_t const* data, boom::Vec2 size) {
    boom::Context::Shared()->makeCurrent();
    _impl = new boom::__ImageImpl{ .textureId = 0 };
    glGenTextures(1, &_impl->textureId);
    glBindTexture(GL_TEXTURE_2D, _impl->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.width, size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    if (data != nullptr) {
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, size.width, size.height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Image::_implDone() {
    boom::Context::Shared()->makeCurrent();
    glDeleteTextures(1, &_impl->textureId);
    delete _impl;
}

} /* namespace boom */
