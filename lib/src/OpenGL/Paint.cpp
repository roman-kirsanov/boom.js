#include <cassert>
#include <iostream>
#include <Boom/Math.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Paint.hpp>
#include "Surface.hpp"
#include "Image.hpp"
#include "Shaders.hpp"
#include "OpenGL.hpp"
#include "Context.hpp"

namespace boom {

struct __PaintImpl {
    boom::Transform projection;
    boom::Vec4 bounds;
    boom::Vec4 source;
    boom::Vec4 destin;
    GLuint vertexBufferId;
    GLuint vertexArrayId;
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
        glDeleteBuffers(1, &_impl->vertexBufferId);
    }
    if (_impl->vertexArrayId != 0) {
        glDeleteVertexArrays(1, &_impl->vertexArrayId);
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
        auto ret = std::vector<GLfloat>();
        ret.resize(vertices.size() * 2);
        for (std::size_t i = 0; i < vertices.size(); i++) {
            auto const xIndex = (i * 2);
            auto const yIndex = (xIndex + 1);
            ret[xIndex] = vertices[i].x;
            ret[yIndex] = vertices[i].y;
        }
        return ret;
    }();

    boom::Context::Shared()->makeCurrent();
    if (_impl->vertexBufferId != 0) {
        glDeleteBuffers(1, &_impl->vertexBufferId);
        _impl->vertexBufferId = 0;
    }
    if (_impl->vertexArrayId != 0) {
        glDeleteVertexArrays(1, &_impl->vertexArrayId);
        _impl->vertexArrayId = 0;
    }
    glGenBuffers(1, &_impl->vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, _impl->vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * buffer.size()), buffer.data(), GL_STATIC_DRAW);
    glGenVertexArrays(1, &_impl->vertexArrayId);
    glBindVertexArray(_impl->vertexArrayId);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    surface->_makeCurrent();
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, imageBrush->image()->_impl->textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (imageBrush->imageFilterMin() == boom::ImageFilter::Linear) ? GL_LINEAR : GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (imageBrush->imageFilterMag() == boom::ImageFilter::Linear) ? GL_LINEAR : GL_NEAREST);
    }
    if (_blend) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
    } else {
        glDisable(GL_BLEND);
    }
    if (_scissor.has_value()) {
        glEnable(GL_SCISSOR_TEST);
        glScissor(
            _scissor.value().x,
            _scissor.value().y,
            _scissor.value().width,
            _scissor.value().height
        );
    } else {
        glDisable(GL_SCISSOR_TEST);
    }
    auto const programId = [&]{
        auto ret = (
            ((imageBrush != nullptr) && (imageBrush->image() != nullptr))
                ? boom::Context::Shared()->_imageShaders
                : boom::Context::Shared()->_basicShaders
        );
        return ret->_use();
    }();
    auto const projectionLocation = glGetUniformLocation(programId, "projection");
    auto const transformLocation = glGetUniformLocation(programId, "transform");
    auto const opacityLocation = glGetUniformLocation(programId, "opacity");
    auto const colorLocation = glGetUniformLocation(programId, "color");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, _impl->projection.data.data());
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, _transform.data.data());
    glUniform1f(opacityLocation, _opacity);
    if ((imageBrush != nullptr)
    && (imageBrush->image() != nullptr)) {
        auto const sizeLocation = glGetUniformLocation(programId, "size");
        auto const boundsLocation = glGetUniformLocation(programId, "bounds");
        auto const sourceLocation = glGetUniformLocation(programId, "source");
        auto const destinLocation = glGetUniformLocation(programId, "destin");
        auto const repeatLocation = glGetUniformLocation(programId, "repeat");
        auto const npatchLocation = glGetUniformLocation(programId, "npatch");
        auto const flipLocation = glGetUniformLocation(programId, "flip");
        glUniform2f(sizeLocation, imageBrush->image()->size().width, imageBrush->image()->size().height);
        glUniform4f(boundsLocation, _impl->bounds.x, _impl->bounds.y, _impl->bounds.width, _impl->bounds.height);
        glUniform4f(sourceLocation, _impl->source.x, _impl->source.y, _impl->source.maxX(), _impl->source.maxY());
        glUniform4f(destinLocation, _impl->destin.x, _impl->destin.y, _impl->destin.maxX(), _impl->destin.maxY());
        glUniform2f(repeatLocation, (imageBrush->imageRepeatX() ? 1.0f : 0.0f), (imageBrush->imageRepeatY() ? 1.0f : 0.0f));
        glUniform4f(npatchLocation, imageBrush->imageNPatch().left, imageBrush->imageNPatch().top, imageBrush->imageNPatch().right, imageBrush->imageNPatch().bottom);
        glUniform4f(colorLocation, imageBrush->imageColor().red, imageBrush->imageColor().green, imageBrush->imageColor().blue, imageBrush->imageColor().alpha);
        glUniform2f(flipLocation, (imageBrush->imageFlipX() ? 1.0f : 0.0f), (imageBrush->imageFlipY() ? 1.0f : 0.0f));
    } else if (solidBrush != nullptr) {
        glUniform4f(colorLocation, solidBrush->color().red, solidBrush->color().green, solidBrush->color().blue, solidBrush->color().alpha);
    }
    glDepthMask(GL_FALSE);
    glBindBuffer(GL_ARRAY_BUFFER, _impl->vertexBufferId);
    glBindVertexArray(_impl->vertexArrayId);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(buffer.size()));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} /* namespace boom */
