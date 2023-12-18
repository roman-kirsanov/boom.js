#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include "Image.hpp"
#include "Context.hpp"
#include "Surface.hpp"

namespace boom {

void Surface::_implInit() {
    _impl = new __SurfaceImpl{
        .frameBufferId = 0,
        .colorBufferId = 0,
        .depthBufferId = 0,
        .textureBufferId = 0
    };
    if (_type == boom::SurfaceType::View) {
        assert(_view != nullptr);
        _context = boom::MakeShared<boom::Context>(boom::OpenGLOptions{
            .shared = boom::Context::Shared(),
            .view = _view,
            .version = _version
        });
    } else if (_type == boom::SurfaceType::Image) {
        assert(_image != nullptr);
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _context = boom::Context::Shared();
        _context->genFramebuffers(1, &_impl->frameBufferId);
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, _impl->frameBufferId);
        _context->genTextures(1, &_impl->colorBufferId);
        _context->bindTexture(boom::kOpenGLTexture2dMultisample, _impl->colorBufferId);
        _context->texImage2DMultisample(boom::kOpenGLTexture2dMultisample, 4, boom::kOpenGLRgba, width, height, boom::kOpenGLTrue);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2dMultisample, _impl->colorBufferId, 0);
        _context->genTextures(1, &_impl->depthBufferId);
        _context->bindTexture(boom::kOpenGLTexture2dMultisample, _impl->depthBufferId);
        _context->texImage2DMultisample(boom::kOpenGLTexture2dMultisample, 4, boom::kOpenGLDepth24Stencil8, width, height, boom::kOpenGLTrue);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLDepthStencilAttachment, boom::kOpenGLTexture2dMultisample, _impl->depthBufferId, 0);
        if (_context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("boom::Surface::_implInit() failed: Failed to make complete intermediate framebuffer object");
        }
        _context->genFramebuffers(1, &_impl->textureBufferId);
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, _impl->textureBufferId);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2d, _image->_impl->textureId, 0);
        if (_context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("boom::Surface::_implInit() failed: Failed to make complete texture framebuffer object");
        }
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _impl->textureBufferId);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _impl->frameBufferId);
        _context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    }
}

void Surface::_implDone() {
    if (_type == boom::SurfaceType::Image) {
        _context->deleteFramebuffers(1, &_impl->frameBufferId);
        _context->deleteFramebuffers(1, &_impl->textureBufferId);
        _context->deleteTextures(1, &_impl->colorBufferId);
        _context->deleteTextures(1, &_impl->depthBufferId);
    }
    delete _impl;
}

void Surface::_implCurrent() const {
    _context->bindFramebuffer(boom::kOpenGLFramebuffer, (
        (_type == boom::SurfaceType::Image) ? _impl->frameBufferId :
        (_type == boom::SurfaceType::View) ? 0 : 0
    ));
    _context->viewport(0.0f, 0.0f, size().width, size().height);
    _context->enable(boom::kOpenGLMultisample);
}

void Surface::_implClear(boom::Color color) {
    _context->clearColor(
        color.red,
        color.green,
        color.blue,
        color.alpha
    );
    _context->clear(boom::kOpenGLColorBufferBit);
}

void Surface::_implFlush() {
    _context->flush();
    if (_type == boom::SurfaceType::Image) {
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _impl->frameBufferId);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _impl->textureBufferId);
        _context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    }
}

void Surface::_implSwap() {
    if (_type == boom::SurfaceType::View) {
        _context->swap();
    }
}

} /* namespace boom */
