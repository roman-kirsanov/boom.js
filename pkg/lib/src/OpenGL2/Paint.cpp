#include <cassert>
#include <iostream>
#include <Boom/Math.hpp>
#include <Boom/OpenGL.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Paint.hpp>
#include "Surface.hpp"
#include "Image.hpp"
#include "Shaders.hpp"
#include "Context.hpp"

namespace boom {

struct __PaintImpl {
    boom::Transform projection;
    boom::Vec4 bounds;
    boom::Vec4 source;
    boom::Vec4 destin;
    std::uint32_t vertexBufferId;
    std::uint32_t vertexArrayId;
    std::shared_ptr<boom::Context const> context;
};

void Paint::_implInit() {
    _impl = new boom::__PaintImpl{
        .projection = boom::Transform(),
        .bounds = { 0.0f, 0.0f, 0.0f, 0.0f },
        .source = { 0.0f, 0.0f, 0.0f, 0.0f },
        .destin = { 0.0f, 0.0f, 0.0f, 0.0f },
        .vertexBufferId = 0,
        .vertexArrayId = 0
    };
}

void Paint::_implDone() {
    if (_impl->context != nullptr) {
        if (_impl->vertexBufferId != 0) {
            _impl->context->deleteBuffers(1, &_impl->vertexBufferId);
        }
        if (_impl->vertexArrayId != 0) {
            _impl->context->deleteVertexArrays(1, &_impl->vertexArrayId);
        }
    }
    delete _impl;
}

void Paint::_implRender(
    std::shared_ptr<boom::Surface const> surface,
    std::shared_ptr<boom::Brush const> brush,
    std::vector<boom::Vec2> const& vertices
) const {

    // TODO: Add support of "_needsUpdate" flag to speed up the rendering...

    assert(surface != nullptr);
    assert(brush != nullptr);

    auto const solidBrush = std::dynamic_pointer_cast<boom::SolidBrush const>(brush);
    auto const imageBrush = std::dynamic_pointer_cast<boom::ImageBrush const>(brush);

    if ((solidBrush == nullptr)
    && (imageBrush == nullptr)) {
        return;
    }

    auto const context = surface->_impl->context;
    if ((_impl->context != nullptr)
    && (_impl->context != context)) {
        if (_impl->vertexBufferId != 0) {
            _impl->context->deleteBuffers(1, &_impl->vertexBufferId);
            _impl->vertexBufferId = 0;
        }
        if (_impl->vertexArrayId != 0) {
            _impl->context->deleteVertexArrays(1, &_impl->vertexArrayId);
            _impl->vertexArrayId = 0;
        }
        _impl->context = context;
    }

    _impl->projection = boom::Transform().ortho(surface->size());
    _impl->bounds = [&]{
        auto minX = vertices[0].x;
        auto minY = vertices[0].y;
        auto maxX = vertices[0].x;
        auto maxY = vertices[0].y;
        for (auto const& vertex : vertices) {
            minX = boom::Min<float>(minX, vertex.x);
            minY = boom::Min<float>(minY, vertex.y);
            maxX = boom::Max<float>(maxX, vertex.x);
            maxY = boom::Max<float>(maxY, vertex.y);
        }
        return boom::Vec4{ minX, minY, (maxX - minX), (maxY - minY) };
    }();
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        _impl->source = boom::Vec4{ {}, imageBrush->image()->size() };
        _impl->destin = boom::Vec4{ {}, imageBrush->image()->size() };
        if (imageBrush->imageSlice().has_value()) {
            _impl->source = imageBrush->imageSlice().value();
            _impl->destin.width = _impl->source.width;
            _impl->destin.height = _impl->source.height;
        }
        if (imageBrush->imagePositionX() == boom::ImagePosition::Center) {
            _impl->destin.x = ((_impl->bounds.width - _impl->source.width) / 2.0f);
        } else if (imageBrush->imagePositionX() == boom::ImagePosition::End) {
            _impl->destin.x = (_impl->bounds.width - _impl->source.width);
        } else if (imageBrush->imagePositionX() == boom::ImagePosition::Stretch) {
            _impl->destin.width = _impl->bounds.width;
        }
        if (imageBrush->imagePositionY() == boom::ImagePosition::Center) {
            _impl->destin.y = ((_impl->bounds.height - _impl->source.height) / 2.0f);
        } else if (imageBrush->imagePositionY() == boom::ImagePosition::End) {
            _impl->destin.y = (_impl->bounds.height - _impl->source.height);
        } else if (imageBrush->imagePositionY() == boom::ImagePosition::Stretch) {
            _impl->destin.height = _impl->bounds.height;
        }
    }
    auto const buffer = [&]{
        auto ret = std::vector<float>();
        ret.resize(vertices.size() * 2);
        for (std::size_t i = 0; i < vertices.size(); i++) {
            auto const xIndex = (i * 2);
            auto const yIndex = (xIndex + 1);
            ret[xIndex] = vertices[i].x;
            ret[yIndex] = vertices[i].y;
        }
        return ret;
    }();

    if (_impl->vertexBufferId != 0) {
        context->deleteBuffers(1, &_impl->vertexBufferId);
        _impl->vertexBufferId = 0;
    }
    if (_impl->vertexArrayId != 0) {
        context->deleteVertexArrays(1, &_impl->vertexArrayId);
        _impl->vertexArrayId = 0;
    }
    context->genBuffers(1, &_impl->vertexBufferId);
    context->bindBuffer(boom::OpenGLArrayBuffer, _impl->vertexBufferId);
    context->bufferData(boom::OpenGLArrayBuffer, (sizeof(float) * buffer.size()), buffer.data(), boom::OpenGLStaticDraw);
    context->genVertexArrays(1, &_impl->vertexArrayId);
    context->bindVertexArray(_impl->vertexArrayId);
    context->enableVertexAttribArray(0);
    context->vertexAttribPointer(0, 2, boom::OpenGLFloat, boom::OpenGLFalse, 0, nullptr);
    surface->_makeCurrent();
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        context->activeTexture(boom::OpenGLTexture0);
        context->bindTexture(boom::OpenGLTexture2D, imageBrush->image()->_impl->textureId);
        context->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureWrapS, boom::OpenGLClampToBorder);
        context->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureWrapT, boom::OpenGLClampToBorder);
        context->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureMinFilter, (imageBrush->imageFilterMin() == boom::ImageFilter::Linear) ? boom::OpenGLLinear : boom::OpenGLNearest);
        context->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureMagFilter, (imageBrush->imageFilterMag() == boom::ImageFilter::Linear) ? boom::OpenGLLinear : boom::OpenGLNearest);
    }
    if (_blend) {
        context->enable(boom::OpenGLBlend);
        context->blendFunc(boom::OpenGLSrcAlpha, boom::OpenGLOneMinusSrcAlpha);
        // context->blendFuncSeparate(boom::OpenGLSrcAlpha, boom::OpenGLOneMinusSrcAlpha, boom::OpenGLOne, boom::OpenGLZero);
    } else {
        context->disable(boom::OpenGLBlend);
    }
    if (_scissor.has_value()) {
        context->enable(boom::OpenGLScissorTest);
        context->scissor(
            _scissor.value().x,
            _scissor.value().y,
            _scissor.value().width,
            _scissor.value().height
        );
    } else {
        context->disable(boom::OpenGLScissorTest);
    }
    auto const programId = [&]{
        auto ret = (
            ((imageBrush != nullptr) && (imageBrush->image() != nullptr))
                ? context->imageShaders()
                : context->basicShaders()
        );
        return ret->_use();
    }();
    auto const projectionLocation = context->getUniformLocation(programId, "projection");
    auto const transformLocation = context->getUniformLocation(programId, "transform");
    auto const opacityLocation = context->getUniformLocation(programId, "opacity");
    auto const colorLocation = context->getUniformLocation(programId, "color");
    context->uniformMatrix4fv(projectionLocation, 1, boom::OpenGLFalse, _impl->projection.data.data());
    context->uniformMatrix4fv(transformLocation, 1, boom::OpenGLFalse, _transform.data.data());
    context->uniform1f(opacityLocation, _opacity);
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        auto const sizeLocation = context->getUniformLocation(programId, "size");
        auto const boundsLocation = context->getUniformLocation(programId, "bounds");
        auto const sourceLocation = context->getUniformLocation(programId, "source");
        auto const destinLocation = context->getUniformLocation(programId, "destin");
        auto const repeatLocation = context->getUniformLocation(programId, "repeat");
        auto const npatchLocation = context->getUniformLocation(programId, "npatch");
        auto const flipLocation = context->getUniformLocation(programId, "flip");
        context->uniform2f(sizeLocation, imageBrush->image()->size().width, imageBrush->image()->size().height);
        context->uniform4f(boundsLocation, _impl->bounds.x, _impl->bounds.y, _impl->bounds.width, _impl->bounds.height);
        context->uniform4f(sourceLocation, _impl->source.x, _impl->source.y, _impl->source.maxX(), _impl->source.maxY());
        context->uniform4f(destinLocation, _impl->destin.x, _impl->destin.y, _impl->destin.maxX(), _impl->destin.maxY());
        context->uniform2f(repeatLocation, (imageBrush->imageRepeatX() ? 1.0f : 0.0f), (imageBrush->imageRepeatY() ? 1.0f : 0.0f));
        context->uniform4f(npatchLocation, imageBrush->imageNPatch().left, imageBrush->imageNPatch().top, imageBrush->imageNPatch().right, imageBrush->imageNPatch().bottom);
        context->uniform4f(colorLocation, imageBrush->imageColor().red, imageBrush->imageColor().green, imageBrush->imageColor().blue, imageBrush->imageColor().alpha);
        context->uniform2f(flipLocation, (imageBrush->imageFlipX() ? 1.0f : 0.0f), (imageBrush->imageFlipY() ? 1.0f : 0.0f));
    } else if (solidBrush != nullptr) {
        context->uniform4f(colorLocation, solidBrush->color().red, solidBrush->color().green, solidBrush->color().blue, solidBrush->color().alpha);
    }
    context->depthMask(boom::OpenGLFalse);
    context->bindBuffer(boom::OpenGLArrayBuffer, _impl->vertexBufferId);
    context->bindVertexArray(_impl->vertexArrayId);
    context->drawArrays(boom::OpenGLTriangles, 0, static_cast<std::int32_t>(buffer.size()));
    context->bindBuffer(boom::OpenGLArrayBuffer, 0);
    context->bindVertexArray(0);
    context->bindTexture(boom::OpenGLTexture2D, 0);
}

} /* namespace boom */
