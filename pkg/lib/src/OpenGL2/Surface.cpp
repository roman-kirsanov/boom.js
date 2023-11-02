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
    if (_type == boom::SurfaceType::Window) {
        assert(_window != nullptr);
        _impl->context = boom::MakeShared<boom::Context>(boom::OpenGLOptions{
            .shared = boom::Context::Shared(),
            .window = _window
        });
    } else if (_type == boom::SurfaceType::Image) {
        assert(_image != nullptr);
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _impl->context = boom::Context::Shared();
        _impl->context->genFramebuffers(1, &_impl->frameBufferId);
        _impl->context->bindFramebuffer(boom::OpenGLFramebuffer, _impl->frameBufferId);
        _impl->context->genTextures(1, &_impl->colorBufferId);
        _impl->context->bindTexture(boom::OpenGLTexture2DMultisample, _impl->colorBufferId);
        _impl->context->texImage2DMultisample(boom::OpenGLTexture2DMultisample, 4, boom::OpenGLRGBA, width, height, boom::OpenGLTrue);
        _impl->context->framebufferTexture2D(boom::OpenGLFramebuffer, boom::OpenGLColorAttachment0, boom::OpenGLTexture2DMultisample, _impl->colorBufferId, 0);
        _impl->context->genTextures(1, &_impl->depthBufferId);
        _impl->context->bindTexture(boom::OpenGLTexture2DMultisample, _impl->depthBufferId);
        _impl->context->texImage2DMultisample(boom::OpenGLTexture2DMultisample, 4, boom::OpenGLDepth24Stencil8, width, height, boom::OpenGLTrue);
        _impl->context->framebufferTexture2D(boom::OpenGLFramebuffer, boom::OpenGLDepthStencilAttachment, boom::OpenGLTexture2DMultisample, _impl->depthBufferId, 0);
        if (_impl->context->checkFramebufferStatus(boom::OpenGLFramebuffer) != boom::OpenGLFramebufferComplete) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete intermediate framebuffer object");
        }
        _impl->context->genFramebuffers(1, &_impl->textureBufferId);
        _impl->context->bindFramebuffer(boom::OpenGLFramebuffer, _impl->textureBufferId);
        _impl->context->framebufferTexture2D(boom::OpenGLFramebuffer, boom::OpenGLColorAttachment0, boom::OpenGLTexture2D, _image->_impl->textureId, 0);
        if (_impl->context->checkFramebufferStatus(boom::OpenGLFramebuffer) != boom::OpenGLFramebufferComplete) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete texture framebuffer object");
        }
        _impl->context->bindFramebuffer(boom::OpenGLFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::OpenGLReadFramebuffer, _impl->textureBufferId);
        _impl->context->bindFramebuffer(boom::OpenGLDrawFramebuffer, _impl->frameBufferId);
        _impl->context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::OpenGLColorBufferBit, boom::OpenGLNearest);
        _impl->context->bindFramebuffer(boom::OpenGLReadFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::OpenGLDrawFramebuffer, 0);
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
    _impl->context->bindFramebuffer(boom::OpenGLFramebuffer, (
        (_type == boom::SurfaceType::Image) ? _impl->frameBufferId :
        (_type == boom::SurfaceType::Window) ? 0 : 0
    ));
    _impl->context->enable(boom::OpenGLMultisample);
    _impl->context->viewport(0.0f, 0.0f, size().width, size().height);
}

void Surface::_implClear(boom::Color color) {
    _impl->context->clearColor(
        color.red,
        color.green,
        color.blue,
        color.alpha
    );
    _impl->context->clear(boom::OpenGLColorBufferBit);
}

void Surface::_implFlush() {
    _impl->context->flush();
    if (_type == boom::SurfaceType::Image) {
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _impl->context->bindFramebuffer(boom::OpenGLReadFramebuffer, _impl->frameBufferId);
        _impl->context->bindFramebuffer(boom::OpenGLDrawFramebuffer, _impl->textureBufferId);
        _impl->context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::OpenGLColorBufferBit, boom::OpenGLNearest);
        _impl->context->bindFramebuffer(boom::OpenGLReadFramebuffer, 0);
        _impl->context->bindFramebuffer(boom::OpenGLDrawFramebuffer, 0);
    } else if (_type == boom::SurfaceType::Window) {
        _impl->context->swap();
    }
}

} /* namespace boom */
