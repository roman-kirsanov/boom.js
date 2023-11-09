#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include "Image.hpp"
#include "Context.hpp"
#include "Surface.hpp"

namespace boom {

void Surface::_implInit() {
    _impl = new __SurfaceImpl{
        .context = nullptr,
        .frameBufferId = 0,
        .colorBufferId = 0,
        .depthBufferId = 0,
        .textureBufferId = 0
    };
    if (_type == boom::SurfaceType::View) {
        assert(_view != nullptr);
        _impl->context = boom::MakeShared<boom::Context>(boom::OpenGLOptions{
            .shared = boom::Context::Shared(),
            .view = _view
        });
    } else if (_type == boom::SurfaceType::Image) {
        assert(_image != nullptr);
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _impl->context = boom::Context::Shared();
        _impl->context->genFramebuffers(1, &_impl->frameBufferId);
        _impl->context->bindFramebuffer(boom::kOpenGLFramebuffer, _impl->frameBufferId);
        _impl->context->genTextures(1, &_impl->colorBufferId);
        _impl->context->bindTexture(boom::kOpenGLTexture2DMultisample, _impl->colorBufferId);
        _impl->context->texImage2DMultisample(boom::kOpenGLTexture2DMultisample, 4, boom::kOpenGLRGBA, width, height, boom::kOpenGLTrue);
        _impl->context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2DMultisample, _impl->colorBufferId, 0);
        _impl->context->genTextures(1, &_impl->depthBufferId);
        _impl->context->bindTexture(boom::kOpenGLTexture2DMultisample, _impl->depthBufferId);
        _impl->context->texImage2DMultisample(boom::kOpenGLTexture2DMultisample, 4, boom::kOpenGLDepth24Stencil8, width, height, boom::kOpenGLTrue);
        _impl->context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLDepthStencilAttachment, boom::kOpenGLTexture2DMultisample, _impl->depthBufferId, 0);
        if (_impl->context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete intermediate framebuffer object");
        }
        _impl->context->genFramebuffers(1, &_impl->textureBufferId);
        _impl->context->bindFramebuffer(boom::kOpenGLFramebuffer, _impl->textureBufferId);
        _impl->context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2D, _image->_impl->textureId, 0);
        if (_impl->context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete texture framebuffer object");
        }
        _impl->context->bindFramebuffer(boom::kOpenGLFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _impl->textureBufferId);
        _impl->context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _impl->frameBufferId);
        _impl->context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _impl->context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    }
}

void Surface::_implDone() {
    if (_type == boom::SurfaceType::Image) {
        _impl->context->deleteFramebuffers(1, &_impl->frameBufferId);
        _impl->context->deleteFramebuffers(1, &_impl->textureBufferId);
        _impl->context->deleteTextures(1, &_impl->colorBufferId);
        _impl->context->deleteTextures(1, &_impl->depthBufferId);
    }
    delete _impl;
}

void Surface::_implMakeCurrent() const {
    _impl->context->bindFramebuffer(boom::kOpenGLFramebuffer, (
        (_type == boom::SurfaceType::Image) ? _impl->frameBufferId :
        (_type == boom::SurfaceType::View) ? 0 : 0
    ));
    _impl->context->enable(boom::kOpenGLMultisample);
    _impl->context->viewport(0.0f, 0.0f, size().width, size().height);
}

void Surface::_implClear(boom::Color color) {
    _impl->context->clearColor(
        color.red,
        color.green,
        color.blue,
        color.alpha
    );
    _impl->context->clear(boom::kOpenGLColorBufferBit);
}

void Surface::_implFlush() {
    _impl->context->flush();
    if (_type == boom::SurfaceType::Image) {
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _impl->context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _impl->frameBufferId);
        _impl->context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _impl->textureBufferId);
        _impl->context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _impl->context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    } else if (_type == boom::SurfaceType::View) {
        _impl->context->swap();
    }
}

} /* namespace boom */
