#include "Context.hpp"
#include "Image.hpp"

namespace boom {

void Image::_implInit(std::uint8_t const* data, boom::Vec2 size) {
    auto shared = boom::Context::Shared();
    _impl = new boom::__ImageImpl{ .textureId = 0 };
    shared->genTextures(1, &_impl->textureId);
    shared->bindTexture(boom::OpenGLTexture2D, _impl->textureId);
    shared->texImage2D(boom::OpenGLTexture2D, 0, boom::OpenGLRGBA, size.width, size.height, 0, boom::OpenGLRGBA, boom::OpenGLUnsignedByte, nullptr);
    if (data != nullptr) {
        shared->texSubImage2D(boom::OpenGLTexture2D, 0, 0, 0, size.width, size.height, boom::OpenGLRGBA, boom::OpenGLUnsignedByte, data);
    }
    shared->bindTexture(boom::OpenGLTexture2D, 0);
}

void Image::_implDone() {
    auto shared = boom::Context::Shared();
    shared->deleteTextures(1, &_impl->textureId);
    delete _impl;
}

} /* namespace boom */
