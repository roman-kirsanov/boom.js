#include "Context.hpp"
#include "Image.hpp"

namespace boom {

void Image::_implInit(std::uint8_t const* data, boom::Vec2 size) {
    auto shared = boom::Context::Shared();
    _impl = new boom::__ImageImpl{ .textureId = 0 };
    shared->genTextures(1, &_impl->textureId);
    shared->bindTexture(boom::kOpenGLTexture2D, _impl->textureId);
    shared->texImage2D(boom::kOpenGLTexture2D, 0, boom::kOpenGLRGBA, size.width, size.height, 0, boom::kOpenGLRGBA, boom::kOpenGLUnsignedByte, nullptr);
    if (data != nullptr) {
        shared->texSubImage2D(boom::kOpenGLTexture2D, 0, 0, 0, size.width, size.height, boom::kOpenGLRGBA, boom::kOpenGLUnsignedByte, data);
    }
    shared->bindTexture(boom::kOpenGLTexture2D, 0);
}

void Image::_implDone() {
    auto shared = boom::Context::Shared();
    shared->deleteTextures(1, &_impl->textureId);
    delete _impl;
}

} /* namespace boom */
