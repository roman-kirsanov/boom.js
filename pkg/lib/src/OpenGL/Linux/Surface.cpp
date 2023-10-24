#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include "../../Win32/Window.hpp"
#include "../Image.hpp"
#include "Context.hpp"
#include "Surface.hpp"

namespace boom {

void Surface::_implInit() {
    _impl = new __SurfaceImpl{
        .context = nullptr,
        .frameBufferId = 0,
        .colorBufferId = 0,
        .depthBufferId = 0,
        .textureBufferId = 0,
        .impl = new __SurfaceImplImpl{}
    };
    if (_type == boom::SurfaceType::Window) {
        assert(_window != nullptr);
        // _impl->context = boom::MakeShared<boom::Context>();
        _impl->context = boom::Context::Shared();
        _impl->context->makeCurrent();
        ;
    } else if (_type == boom::SurfaceType::Image) {
        assert(_image != nullptr);
        _impl->context = boom::Context::Shared();
        _impl->context->makeCurrent();
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        glGenFramebuffers(1, &_impl->frameBufferId);
        glBindFramebuffer(GL_FRAMEBUFFER, _impl->frameBufferId);
        glGenTextures(1, &_impl->colorBufferId);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _impl->colorBufferId);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, width, height, GL_TRUE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, _impl->colorBufferId, 0);
        glGenTextures(1, &_impl->depthBufferId);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _impl->depthBufferId);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_DEPTH24_STENCIL8, width, height, GL_TRUE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, _impl->depthBufferId, 0);
        GLenum status1 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status1 != GL_FRAMEBUFFER_COMPLETE) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete intermediate framebuffer object");
        }
        glGenFramebuffers(1, &_impl->textureBufferId);
        glBindFramebuffer(GL_FRAMEBUFFER, _impl->textureBufferId);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _image->_impl->textureId, 0);
        GLenum status2 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status2 != GL_FRAMEBUFFER_COMPLETE) {
            boom::Abort("ERROR: boom::Surface::_implInit() failed: Failed to make complete texture framebuffer object");
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _impl->textureBufferId);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _impl->frameBufferId);
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
}

void Surface::_implDone() {
    _impl->context->makeCurrent();
    if (_type == boom::SurfaceType::Image) {
        glDeleteFramebuffers(1, &_impl->frameBufferId);
        glDeleteFramebuffers(1, &_impl->textureBufferId);
        glDeleteTextures(1, &_impl->colorBufferId);
        glDeleteTextures(1, &_impl->depthBufferId);
    }
    delete _impl->impl;
    delete _impl;
}

void Surface::_implMakeCurrent() const {
    _impl->context->makeCurrent();
    glBindFramebuffer(GL_FRAMEBUFFER, (
        (_type == boom::SurfaceType::Image) ? _impl->frameBufferId :
        (_type == boom::SurfaceType::Window) ? 0 : 0
    ));
    glEnable(GL_MULTISAMPLE);
    glViewport(0.0f, 0.0f, size().width, size().height);
}

void Surface::_implClear(boom::Color color) {
    _impl->context->makeCurrent();
    glClearColor(
        color.red,
        color.green,
        color.blue,
        color.alpha
    );
    glClear(GL_COLOR_BUFFER_BIT);
}

void Surface::_implFlush() {
    _impl->context->makeCurrent();
    _impl->context->flush();
    if (_type == boom::SurfaceType::Image) {
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _impl->frameBufferId);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _impl->textureBufferId);
        glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    }
}

} /* namespace boom */
