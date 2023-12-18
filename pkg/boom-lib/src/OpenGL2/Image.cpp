#include "Context.hpp"
#include "Image.hpp"

namespace boom {

void Image::_implInit(std::uint8_t const* data, boom::Vec2 size) {
    auto shared = boom::Context::Shared();
    _impl = new boom::__ImageImpl{ .textureId = 0 };
    shared->genTextures(1, &_impl->textureId);
    shared->bindTexture(boom::kOpenGLTexture2d, _impl->textureId);
    shared->texImage2D(boom::kOpenGLTexture2d, 0, boom::kOpenGLRgba, size.width, size.height, 0, boom::kOpenGLRgba, boom::kOpenGLUnsignedByte, nullptr);
    if (data != nullptr) {
        shared->texSubImage2D(boom::kOpenGLTexture2d, 0, 0, 0, size.width, size.height, boom::kOpenGLRgba, boom::kOpenGLUnsignedByte, data);
    }
    shared->bindTexture(boom::kOpenGLTexture2d, 0);
}

void Image::_implDone() {
    auto shared = boom::Context::Shared();
    shared->deleteTextures(1, &_impl->textureId);
    delete _impl;
}

} /* namespace boom */
