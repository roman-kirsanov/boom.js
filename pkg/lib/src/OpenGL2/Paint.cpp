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
    if (_impl->vertexBufferId != 0) {
        boom::Context::Shared()->deleteBuffers(1, &_impl->vertexBufferId);
    }
    if (_impl->vertexArrayId != 0) {
        boom::Context::Shared()->deleteVertexArrays(1, &_impl->vertexArrayId);
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

    auto sharedContext = boom::Context::Shared();
    auto surfaceContext = surface->_impl->context;

    if (_impl->vertexBufferId != 0) {
        sharedContext->deleteBuffers(1, &_impl->vertexBufferId);
        _impl->vertexBufferId = 0;
    }
    if (_impl->vertexArrayId != 0) {
        sharedContext->deleteVertexArrays(1, &_impl->vertexArrayId);
        _impl->vertexArrayId = 0;
    }
    sharedContext->genBuffers(1, &_impl->vertexBufferId);
    sharedContext->bindBuffer(boom::OpenGLArrayBuffer, _impl->vertexBufferId);
    sharedContext->bufferData(boom::OpenGLArrayBuffer, (sizeof(float) * buffer.size()), buffer.data(), boom::OpenGLStaticDraw);
    sharedContext->genVertexArrays(1, &_impl->vertexArrayId);
    sharedContext->bindVertexArray(_impl->vertexArrayId);
    sharedContext->enableVertexAttribArray(0);
    sharedContext->vertexAttribPointer(0, 2, boom::OpenGLFloat, boom::OpenGLFalse, 0, nullptr);
    surface->_makeCurrent();
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        surfaceContext->activeTexture(boom::OpenGLTexture0);
        surfaceContext->bindTexture(boom::OpenGLTexture2D, imageBrush->image()->_impl->textureId);
        surfaceContext->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureWrapS, boom::OpenGLClampToBorder);
        surfaceContext->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureWrapT, boom::OpenGLClampToBorder);
        surfaceContext->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureMinFilter, (imageBrush->imageFilterMin() == boom::ImageFilter::Linear) ? boom::OpenGLLinear : boom::OpenGLNearest);
        surfaceContext->texParameteri(boom::OpenGLTexture2D, boom::OpenGLTextureMagFilter, (imageBrush->imageFilterMag() == boom::ImageFilter::Linear) ? boom::OpenGLLinear : boom::OpenGLNearest);
    }
    if (_blend) {
        surfaceContext->enable(boom::OpenGLBlend);
        surfaceContext->blendFunc(boom::OpenGLSrcAlpha, boom::OpenGLOneMinusSrcAlpha);
        // surfaceContext->blendFuncSeparate(boom::OpenGLSrcAlpha, boom::OpenGLOneMinusSrcAlpha, boom::OpenGLOne, boom::OpenGLZero);
    } else {
        surfaceContext->disable(boom::OpenGLBlend);
    }
    if (_scissor.has_value()) {
        surfaceContext->enable(boom::OpenGLScissorTest);
        surfaceContext->scissor(
            _scissor.value().x,
            _scissor.value().y,
            _scissor.value().width,
            _scissor.value().height
        );
    } else {
        surfaceContext->disable(boom::OpenGLScissorTest);
    }
    auto const programId = [&]{
        auto ret = (
            ((imageBrush != nullptr) && (imageBrush->image() != nullptr))
                ? sharedContext->imageShaders()
                : sharedContext->basicShaders()
        );
        return ret->_use();
    }();
    auto const projectionLocation = surfaceContext->getUniformLocation(programId, "projection");
    auto const transformLocation = surfaceContext->getUniformLocation(programId, "transform");
    auto const opacityLocation = surfaceContext->getUniformLocation(programId, "opacity");
    auto const colorLocation = surfaceContext->getUniformLocation(programId, "color");
    surfaceContext->uniformMatrix4fv(projectionLocation, 1, boom::OpenGLFalse, _impl->projection.data.data());
    surfaceContext->uniformMatrix4fv(transformLocation, 1, boom::OpenGLFalse, _transform.data.data());
    surfaceContext->uniform1f(opacityLocation, _opacity);
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        auto const sizeLocation = surfaceContext->getUniformLocation(programId, "size");
        auto const boundsLocation = surfaceContext->getUniformLocation(programId, "bounds");
        auto const sourceLocation = surfaceContext->getUniformLocation(programId, "source");
        auto const destinLocation = surfaceContext->getUniformLocation(programId, "destin");
        auto const repeatLocation = surfaceContext->getUniformLocation(programId, "repeat");
        auto const npatchLocation = surfaceContext->getUniformLocation(programId, "npatch");
        auto const flipLocation = surfaceContext->getUniformLocation(programId, "flip");
        surfaceContext->uniform2f(sizeLocation, imageBrush->image()->size().width, imageBrush->image()->size().height);
        surfaceContext->uniform4f(boundsLocation, _impl->bounds.x, _impl->bounds.y, _impl->bounds.width, _impl->bounds.height);
        surfaceContext->uniform4f(sourceLocation, _impl->source.x, _impl->source.y, _impl->source.maxX(), _impl->source.maxY());
        surfaceContext->uniform4f(destinLocation, _impl->destin.x, _impl->destin.y, _impl->destin.maxX(), _impl->destin.maxY());
        surfaceContext->uniform2f(repeatLocation, (imageBrush->imageRepeatX() ? 1.0f : 0.0f), (imageBrush->imageRepeatY() ? 1.0f : 0.0f));
        surfaceContext->uniform4f(npatchLocation, imageBrush->imageNPatch().left, imageBrush->imageNPatch().top, imageBrush->imageNPatch().right, imageBrush->imageNPatch().bottom);
        surfaceContext->uniform4f(colorLocation, imageBrush->imageColor().red, imageBrush->imageColor().green, imageBrush->imageColor().blue, imageBrush->imageColor().alpha);
        surfaceContext->uniform2f(flipLocation, (imageBrush->imageFlipX() ? 1.0f : 0.0f), (imageBrush->imageFlipY() ? 1.0f : 0.0f));
    } else if (solidBrush != nullptr) {
        surfaceContext->uniform4f(colorLocation, solidBrush->color().red, solidBrush->color().green, solidBrush->color().blue, solidBrush->color().alpha);
    }
    surfaceContext->depthMask(boom::OpenGLFalse);
    surfaceContext->bindBuffer(boom::OpenGLArrayBuffer, _impl->vertexBufferId);
    surfaceContext->bindVertexArray(_impl->vertexArrayId);
    surfaceContext->drawArrays(boom::OpenGLTriangles, 0, static_cast<std::int32_t>(buffer.size()));
    surfaceContext->bindBuffer(boom::OpenGLArrayBuffer, 0);
    surfaceContext->bindVertexArray(0);
    surfaceContext->bindTexture(boom::OpenGLTexture2D, 0);
}

} /* namespace boom */
