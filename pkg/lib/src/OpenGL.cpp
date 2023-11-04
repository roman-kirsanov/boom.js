#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include "OpenGL.hpp"

namespace boom {

static void __DebugCallback(
    std::uint32_t source,
    std::uint32_t type,
    std::uint32_t id,
    std::uint32_t severity,
    std::int32_t length,
    char const* message,
    void const* userParam
) {
    if ((id == 131169)
    || (id == 131185)
    || (id == 131218)
    || (id == 131204)) {
        return;
    }

    std::cout << "OpenGL Debug Event" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "Message (" << id << "): " <<  message << std::endl;

    switch (source) {
        case boom::kOpenGLDebugSourceApi:            std::cout << "Source: API"; break;
        case boom::kOpenGLDebugSourceWindowSystem:   std::cout << "Source: Window System"; break;
        case boom::kOpenGLDebugSourceShaderCompiler: std::cout << "Source: Shader Compiler"; break;
        case boom::kOpenGLDebugSourceThirdParty:     std::cout << "Source: Third Party"; break;
        case boom::kOpenGLDebugSourceApplication:    std::cout << "Source: Application"; break;
        case boom::kOpenGLDebugSourceOther:          std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type) {
        case boom::kOpenGLDebugTypeError:              std::cout << "Type: Error"; break;
        case boom::kOpenGLDebugTypeDeprecatedBehavior: std::cout << "Type: Deprecated Behaviour"; break;
        case boom::kOpenGLDebugTypeUndefinedBehavior:  std::cout << "Type: Undefined Behaviour"; break;
        case boom::kOpenGLDebugTypePortability:        std::cout << "Type: Portability"; break;
        case boom::kOpenGLDebugTypePerformance:        std::cout << "Type: Performance"; break;
        case boom::kOpenGLDebugTypeMarker:             std::cout << "Type: Marker"; break;
        case boom::kOpenGLDebugTypePushGroup:          std::cout << "Type: Push Group"; break;
        case boom::kOpenGLDebugTypePopGroup:           std::cout << "Type: Pop Group"; break;
        case boom::kOpenGLDebugTypeOther:              std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity) {
        case boom::kOpenGLDebugSeverityHigh:         std::cout << "Severity: High"; break;
        case boom::kOpenGLDebugSeverityMedium:       std::cout << "Severity: Medium"; break;
        case boom::kOpenGLDebugSeverityLow:          std::cout << "Severity: Low"; break;
        case boom::kOpenGLDebugSeverityNotification: std::cout << "Severity: Notification"; break;
    } std::cout << std::endl;

    std::cout << std::endl;
}

OpenGL::~OpenGL() {
    _implDone();
}

OpenGL::OpenGL(boom::OpenGLOptions const& options)
	: _impl(nullptr)
{
    _implInit(options);
    _current();
    _bootstrap();
#ifndef __APPLE__
    if (options.debug.value_or(true)) {
        enable(boom::kOpenGLDebugOutput);
        enable(boom::kOpenGLDebugOutputSynchronous);
        debugMessageCallback(boom::__DebugCallback, nullptr);
        debugMessageControl(
            boom::kOpenGLDontCare,
            boom::kOpenGLDontCare,
            boom::kOpenGLDontCare,
            0,
            nullptr,
            boom::kOpenGLTrue
        );
    }
#endif
}

void OpenGL::accum(boom::OpenGLEnum op, boom::OpenGLFloat value) const {
#ifndef NDEBUG
    if (boom::glAccum == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::accum() failed: OpenGL function \"glAccum\" not loaded");
    }
#endif
    _current();
    boom::glAccum(op, value);
}

void OpenGL::activeShaderProgram(boom::OpenGLUint pipeline, boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glActiveShaderProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::activeShaderProgram() failed: OpenGL function \"glActiveShaderProgram\" not loaded");
    }
#endif
    _current();
    boom::glActiveShaderProgram(pipeline, program);
}

void OpenGL::activeTexture(boom::OpenGLEnum texture) const {
#ifndef NDEBUG
    if (boom::glActiveTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::activeTexture() failed: OpenGL function \"glActiveTexture\" not loaded");
    }
#endif
    _current();
    boom::glActiveTexture(texture);
}

void OpenGL::alphaFunc(boom::OpenGLEnum func, boom::OpenGLFloat ref) const {
#ifndef NDEBUG
    if (boom::glAlphaFunc == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::alphaFunc() failed: OpenGL function \"glAlphaFunc\" not loaded");
    }
#endif
    _current();
    boom::glAlphaFunc(func, ref);
}

void OpenGL::alphaFuncx(boom::OpenGLEnum func, boom::OpenGLFixed ref) const {
#ifndef NDEBUG
    if (boom::glAlphaFuncx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::alphaFuncx() failed: OpenGL function \"glAlphaFuncx\" not loaded");
    }
#endif
    _current();
    boom::glAlphaFuncx(func, ref);
}

boom::OpenGLBoolean OpenGL::areTexturesResident(boom::OpenGLSizei n, boom::OpenGLUint const* textures, boom::OpenGLBoolean* residences) const {
#ifndef NDEBUG
    if (boom::glAreTexturesResident == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::areTexturesResident() failed: OpenGL function \"glAreTexturesResident\" not loaded");
    }
#endif
    _current();
    return boom::glAreTexturesResident(n, textures, residences);
}

void OpenGL::arrayElement(boom::OpenGLInt i) const {
#ifndef NDEBUG
    if (boom::glArrayElement == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::arrayElement() failed: OpenGL function \"glArrayElement\" not loaded");
    }
#endif
    _current();
    boom::glArrayElement(i);
}

void OpenGL::attachShader(boom::OpenGLUint program, boom::OpenGLUint shader) const {
#ifndef NDEBUG
    if (boom::glAttachShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::attachShader() failed: OpenGL function \"glAttachShader\" not loaded");
    }
#endif
    _current();
    boom::glAttachShader(program, shader);
}

void OpenGL::begin(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glBegin == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::begin() failed: OpenGL function \"glBegin\" not loaded");
    }
#endif
    _current();
    boom::glBegin(mode);
}

void OpenGL::beginConditionalRender(boom::OpenGLUint id, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glBeginConditionalRender == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::beginConditionalRender() failed: OpenGL function \"glBeginConditionalRender\" not loaded");
    }
#endif
    _current();
    boom::glBeginConditionalRender(id, mode);
}

void OpenGL::beginQuery(boom::OpenGLEnum target, boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glBeginQuery == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::beginQuery() failed: OpenGL function \"glBeginQuery\" not loaded");
    }
#endif
    _current();
    boom::glBeginQuery(target, id);
}

void OpenGL::beginQueryIndexed(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glBeginQueryIndexed == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::beginQueryIndexed() failed: OpenGL function \"glBeginQueryIndexed\" not loaded");
    }
#endif
    _current();
    boom::glBeginQueryIndexed(target, index, id);
}

void OpenGL::beginTransformFeedback(boom::OpenGLEnum primitiveMode) const {
#ifndef NDEBUG
    if (boom::glBeginTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::beginTransformFeedback() failed: OpenGL function \"glBeginTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glBeginTransformFeedback(primitiveMode);
}

void OpenGL::bindAttribLocation(boom::OpenGLUint program, boom::OpenGLUint index, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glBindAttribLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindAttribLocation() failed: OpenGL function \"glBindAttribLocation\" not loaded");
    }
#endif
    _current();
    boom::glBindAttribLocation(program, index, name);
}

void OpenGL::bindBuffer(boom::OpenGLEnum target, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glBindBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindBuffer() failed: OpenGL function \"glBindBuffer\" not loaded");
    }
#endif
    _current();
    boom::glBindBuffer(target, buffer);
}

void OpenGL::bindBufferBase(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glBindBufferBase == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindBufferBase() failed: OpenGL function \"glBindBufferBase\" not loaded");
    }
#endif
    _current();
    boom::glBindBufferBase(target, index, buffer);
}

void OpenGL::bindBufferRange(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glBindBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindBufferRange() failed: OpenGL function \"glBindBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glBindBufferRange(target, index, buffer, offset, size);
}

void OpenGL::bindBuffersBase(boom::OpenGLEnum target, boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* buffers) const {
#ifndef NDEBUG
    if (boom::glBindBuffersBase == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindBuffersBase() failed: OpenGL function \"glBindBuffersBase\" not loaded");
    }
#endif
    _current();
    boom::glBindBuffersBase(target, first, count, buffers);
}

void OpenGL::bindBuffersRange(boom::OpenGLEnum target, boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* buffers, boom::OpenGLIntptr const* offsets, boom::OpenGLSizeiptr const* sizes) const {
#ifndef NDEBUG
    if (boom::glBindBuffersRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindBuffersRange() failed: OpenGL function \"glBindBuffersRange\" not loaded");
    }
#endif
    _current();
    boom::glBindBuffersRange(target, first, count, buffers, offsets, sizes);
}

void OpenGL::bindFragDataLocation(boom::OpenGLUint program, boom::OpenGLUint color, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glBindFragDataLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindFragDataLocation() failed: OpenGL function \"glBindFragDataLocation\" not loaded");
    }
#endif
    _current();
    boom::glBindFragDataLocation(program, color, name);
}

void OpenGL::bindFragDataLocationIndexed(boom::OpenGLUint program, boom::OpenGLUint colorNumber, boom::OpenGLUint index, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glBindFragDataLocationIndexed == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindFragDataLocationIndexed() failed: OpenGL function \"glBindFragDataLocationIndexed\" not loaded");
    }
#endif
    _current();
    boom::glBindFragDataLocationIndexed(program, colorNumber, index, name);
}

void OpenGL::bindFramebuffer(boom::OpenGLEnum target, boom::OpenGLUint framebuffer) const {
#ifndef NDEBUG
    if (boom::glBindFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindFramebuffer() failed: OpenGL function \"glBindFramebuffer\" not loaded");
    }
#endif
    _current();
    boom::glBindFramebuffer(target, framebuffer);
}

void OpenGL::bindImageTexture(boom::OpenGLUint unit, boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLBoolean layered, boom::OpenGLInt layer, boom::OpenGLEnum access, boom::OpenGLEnum format) const {
#ifndef NDEBUG
    if (boom::glBindImageTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindImageTexture() failed: OpenGL function \"glBindImageTexture\" not loaded");
    }
#endif
    _current();
    boom::glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

void OpenGL::bindImageTextures(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* textures) const {
#ifndef NDEBUG
    if (boom::glBindImageTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindImageTextures() failed: OpenGL function \"glBindImageTextures\" not loaded");
    }
#endif
    _current();
    boom::glBindImageTextures(first, count, textures);
}

void OpenGL::bindProgramPipeline(boom::OpenGLUint pipeline) const {
#ifndef NDEBUG
    if (boom::glBindProgramPipeline == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindProgramPipeline() failed: OpenGL function \"glBindProgramPipeline\" not loaded");
    }
#endif
    _current();
    boom::glBindProgramPipeline(pipeline);
}

void OpenGL::bindRenderbuffer(boom::OpenGLEnum target, boom::OpenGLUint renderbuffer) const {
#ifndef NDEBUG
    if (boom::glBindRenderbuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindRenderbuffer() failed: OpenGL function \"glBindRenderbuffer\" not loaded");
    }
#endif
    _current();
    boom::glBindRenderbuffer(target, renderbuffer);
}

void OpenGL::bindSampler(boom::OpenGLUint unit, boom::OpenGLUint sampler) const {
#ifndef NDEBUG
    if (boom::glBindSampler == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindSampler() failed: OpenGL function \"glBindSampler\" not loaded");
    }
#endif
    _current();
    boom::glBindSampler(unit, sampler);
}

void OpenGL::bindSamplers(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* samplers) const {
#ifndef NDEBUG
    if (boom::glBindSamplers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindSamplers() failed: OpenGL function \"glBindSamplers\" not loaded");
    }
#endif
    _current();
    boom::glBindSamplers(first, count, samplers);
}

void OpenGL::bindTexture(boom::OpenGLEnum target, boom::OpenGLUint texture) const {
#ifndef NDEBUG
    if (boom::glBindTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindTexture() failed: OpenGL function \"glBindTexture\" not loaded");
    }
#endif
    _current();
    boom::glBindTexture(target, texture);
}

void OpenGL::bindTextureUnit(boom::OpenGLUint unit, boom::OpenGLUint texture) const {
#ifndef NDEBUG
    if (boom::glBindTextureUnit == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindTextureUnit() failed: OpenGL function \"glBindTextureUnit\" not loaded");
    }
#endif
    _current();
    boom::glBindTextureUnit(unit, texture);
}

void OpenGL::bindTextures(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* textures) const {
#ifndef NDEBUG
    if (boom::glBindTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindTextures() failed: OpenGL function \"glBindTextures\" not loaded");
    }
#endif
    _current();
    boom::glBindTextures(first, count, textures);
}

void OpenGL::bindTransformFeedback(boom::OpenGLEnum target, boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glBindTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindTransformFeedback() failed: OpenGL function \"glBindTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glBindTransformFeedback(target, id);
}

void OpenGL::bindVertexArray(boom::OpenGLUint array) const {
#ifndef NDEBUG
    if (boom::glBindVertexArray == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindVertexArray() failed: OpenGL function \"glBindVertexArray\" not loaded");
    }
#endif
    _current();
    boom::glBindVertexArray(array);
}

void OpenGL::bindVertexBuffer(boom::OpenGLUint bindingindex, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glBindVertexBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindVertexBuffer() failed: OpenGL function \"glBindVertexBuffer\" not loaded");
    }
#endif
    _current();
    boom::glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

void OpenGL::bindVertexBuffers(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* buffers, boom::OpenGLIntptr const* offsets, boom::OpenGLSizei const* strides) const {
#ifndef NDEBUG
    if (boom::glBindVertexBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bindVertexBuffers() failed: OpenGL function \"glBindVertexBuffers\" not loaded");
    }
#endif
    _current();
    boom::glBindVertexBuffers(first, count, buffers, offsets, strides);
}

void OpenGL::bitmap(boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLFloat xorig, boom::OpenGLFloat yorig, boom::OpenGLFloat xmove, boom::OpenGLFloat ymove, boom::OpenGLUbyte const* bitmap) const {
#ifndef NDEBUG
    if (boom::glBitmap == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bitmap() failed: OpenGL function \"glBitmap\" not loaded");
    }
#endif
    _current();
    boom::glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}

void OpenGL::blendBarrier() const {
#ifndef NDEBUG
    if (boom::glBlendBarrier == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendBarrier() failed: OpenGL function \"glBlendBarrier\" not loaded");
    }
#endif
    _current();
    boom::glBlendBarrier();
}

void OpenGL::blendColor(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue, boom::OpenGLFloat alpha) const {
#ifndef NDEBUG
    if (boom::glBlendColor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendColor() failed: OpenGL function \"glBlendColor\" not loaded");
    }
#endif
    _current();
    boom::glBlendColor(red, green, blue, alpha);
}

void OpenGL::blendEquation(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glBlendEquation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendEquation() failed: OpenGL function \"glBlendEquation\" not loaded");
    }
#endif
    _current();
    boom::glBlendEquation(mode);
}

void OpenGL::blendEquationSeparate(boom::OpenGLEnum modeRGB, boom::OpenGLEnum modeAlpha) const {
#ifndef NDEBUG
    if (boom::glBlendEquationSeparate == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendEquationSeparate() failed: OpenGL function \"glBlendEquationSeparate\" not loaded");
    }
#endif
    _current();
    boom::glBlendEquationSeparate(modeRGB, modeAlpha);
}

void OpenGL::blendEquationSeparatei(boom::OpenGLUint buf, boom::OpenGLEnum modeRGB, boom::OpenGLEnum modeAlpha) const {
#ifndef NDEBUG
    if (boom::glBlendEquationSeparatei == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendEquationSeparatei() failed: OpenGL function \"glBlendEquationSeparatei\" not loaded");
    }
#endif
    _current();
    boom::glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

void OpenGL::blendEquationi(boom::OpenGLUint buf, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glBlendEquationi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendEquationi() failed: OpenGL function \"glBlendEquationi\" not loaded");
    }
#endif
    _current();
    boom::glBlendEquationi(buf, mode);
}

void OpenGL::blendFunc(boom::OpenGLEnum sfactor, boom::OpenGLEnum dfactor) const {
#ifndef NDEBUG
    if (boom::glBlendFunc == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendFunc() failed: OpenGL function \"glBlendFunc\" not loaded");
    }
#endif
    _current();
    boom::glBlendFunc(sfactor, dfactor);
}

void OpenGL::blendFuncSeparate(boom::OpenGLEnum sfactorRGB, boom::OpenGLEnum dfactorRGB, boom::OpenGLEnum sfactorAlpha, boom::OpenGLEnum dfactorAlpha) const {
#ifndef NDEBUG
    if (boom::glBlendFuncSeparate == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendFuncSeparate() failed: OpenGL function \"glBlendFuncSeparate\" not loaded");
    }
#endif
    _current();
    boom::glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void OpenGL::blendFuncSeparatei(boom::OpenGLUint buf, boom::OpenGLEnum srcRGB, boom::OpenGLEnum dstRGB, boom::OpenGLEnum srcAlpha, boom::OpenGLEnum dstAlpha) const {
#ifndef NDEBUG
    if (boom::glBlendFuncSeparatei == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendFuncSeparatei() failed: OpenGL function \"glBlendFuncSeparatei\" not loaded");
    }
#endif
    _current();
    boom::glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

void OpenGL::blendFunci(boom::OpenGLUint buf, boom::OpenGLEnum src, boom::OpenGLEnum dst) const {
#ifndef NDEBUG
    if (boom::glBlendFunci == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blendFunci() failed: OpenGL function \"glBlendFunci\" not loaded");
    }
#endif
    _current();
    boom::glBlendFunci(buf, src, dst);
}

void OpenGL::blitFramebuffer(boom::OpenGLInt srcX0, boom::OpenGLInt srcY0, boom::OpenGLInt srcX1, boom::OpenGLInt srcY1, boom::OpenGLInt dstX0, boom::OpenGLInt dstY0, boom::OpenGLInt dstX1, boom::OpenGLInt dstY1, boom::OpenGLBitfield mask, boom::OpenGLEnum filter) const {
#ifndef NDEBUG
    if (boom::glBlitFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blitFramebuffer() failed: OpenGL function \"glBlitFramebuffer\" not loaded");
    }
#endif
    _current();
    boom::glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void OpenGL::blitNamedFramebuffer(boom::OpenGLUint readFramebuffer, boom::OpenGLUint drawFramebuffer, boom::OpenGLInt srcX0, boom::OpenGLInt srcY0, boom::OpenGLInt srcX1, boom::OpenGLInt srcY1, boom::OpenGLInt dstX0, boom::OpenGLInt dstY0, boom::OpenGLInt dstX1, boom::OpenGLInt dstY1, boom::OpenGLBitfield mask, boom::OpenGLEnum filter) const {
#ifndef NDEBUG
    if (boom::glBlitNamedFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::blitNamedFramebuffer() failed: OpenGL function \"glBlitNamedFramebuffer\" not loaded");
    }
#endif
    _current();
    boom::glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

void OpenGL::bufferData(boom::OpenGLEnum target, boom::OpenGLSizeiptr size, void const* data, boom::OpenGLEnum usage) const {
#ifndef NDEBUG
    if (boom::glBufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bufferData() failed: OpenGL function \"glBufferData\" not loaded");
    }
#endif
    _current();
    boom::glBufferData(target, size, data, usage);
}

void OpenGL::bufferStorage(boom::OpenGLEnum target, boom::OpenGLSizeiptr size, void const* data, boom::OpenGLBitfield flags) const {
#ifndef NDEBUG
    if (boom::glBufferStorage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bufferStorage() failed: OpenGL function \"glBufferStorage\" not loaded");
    }
#endif
    _current();
    boom::glBufferStorage(target, size, data, flags);
}

void OpenGL::bufferSubData(boom::OpenGLEnum target, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, void const* data) const {
#ifndef NDEBUG
    if (boom::glBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::bufferSubData() failed: OpenGL function \"glBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glBufferSubData(target, offset, size, data);
}

void OpenGL::callList(boom::OpenGLUint list) const {
#ifndef NDEBUG
    if (boom::glCallList == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::callList() failed: OpenGL function \"glCallList\" not loaded");
    }
#endif
    _current();
    boom::glCallList(list);
}

void OpenGL::callLists(boom::OpenGLSizei n, boom::OpenGLEnum type, void const* lists) const {
#ifndef NDEBUG
    if (boom::glCallLists == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::callLists() failed: OpenGL function \"glCallLists\" not loaded");
    }
#endif
    _current();
    boom::glCallLists(n, type, lists);
}

boom::OpenGLEnum OpenGL::checkFramebufferStatus(boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glCheckFramebufferStatus == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::checkFramebufferStatus() failed: OpenGL function \"glCheckFramebufferStatus\" not loaded");
    }
#endif
    _current();
    return boom::glCheckFramebufferStatus(target);
}

boom::OpenGLEnum OpenGL::checkNamedFramebufferStatus(boom::OpenGLUint framebuffer, boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glCheckNamedFramebufferStatus == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::checkNamedFramebufferStatus() failed: OpenGL function \"glCheckNamedFramebufferStatus\" not loaded");
    }
#endif
    _current();
    return boom::glCheckNamedFramebufferStatus(framebuffer, target);
}

void OpenGL::clampColor(boom::OpenGLEnum target, boom::OpenGLEnum clamp) const {
#ifndef NDEBUG
    if (boom::glClampColor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clampColor() failed: OpenGL function \"glClampColor\" not loaded");
    }
#endif
    _current();
    boom::glClampColor(target, clamp);
}

void OpenGL::clear(boom::OpenGLBitfield mask) const {
#ifndef NDEBUG
    if (boom::glClear == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clear() failed: OpenGL function \"glClear\" not loaded");
    }
#endif
    _current();
    boom::glClear(mask);
}

void OpenGL::clearAccum(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue, boom::OpenGLFloat alpha) const {
#ifndef NDEBUG
    if (boom::glClearAccum == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearAccum() failed: OpenGL function \"glClearAccum\" not loaded");
    }
#endif
    _current();
    boom::glClearAccum(red, green, blue, alpha);
}

void OpenGL::clearBufferData(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearBufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferData() failed: OpenGL function \"glClearBufferData\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferData(target, internalformat, format, type, data);
}

void OpenGL::clearBufferSubData(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferSubData() failed: OpenGL function \"glClearBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferSubData(target, internalformat, offset, size, format, type, data);
}

void OpenGL::clearBufferfi(boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLFloat depth, boom::OpenGLInt stencil) const {
#ifndef NDEBUG
    if (boom::glClearBufferfi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferfi() failed: OpenGL function \"glClearBufferfi\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

void OpenGL::clearBufferfv(boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glClearBufferfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferfv() failed: OpenGL function \"glClearBufferfv\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferfv(buffer, drawbuffer, value);
}

void OpenGL::clearBufferiv(boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glClearBufferiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferiv() failed: OpenGL function \"glClearBufferiv\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferiv(buffer, drawbuffer, value);
}

void OpenGL::clearBufferuiv(boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glClearBufferuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearBufferuiv() failed: OpenGL function \"glClearBufferuiv\" not loaded");
    }
#endif
    _current();
    boom::glClearBufferuiv(buffer, drawbuffer, value);
}

void OpenGL::clearColor(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue, boom::OpenGLFloat alpha) const {
#ifndef NDEBUG
    if (boom::glClearColor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearColor() failed: OpenGL function \"glClearColor\" not loaded");
    }
#endif
    _current();
    boom::glClearColor(red, green, blue, alpha);
}

void OpenGL::clearColorx(boom::OpenGLFixed red, boom::OpenGLFixed green, boom::OpenGLFixed blue, boom::OpenGLFixed alpha) const {
#ifndef NDEBUG
    if (boom::glClearColorx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearColorx() failed: OpenGL function \"glClearColorx\" not loaded");
    }
#endif
    _current();
    boom::glClearColorx(red, green, blue, alpha);
}

void OpenGL::clearDepth(boom::OpenGLDouble depth) const {
#ifndef NDEBUG
    if (boom::glClearDepth == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearDepth() failed: OpenGL function \"glClearDepth\" not loaded");
    }
#endif
    _current();
    boom::glClearDepth(depth);
}

void OpenGL::clearDepthf(boom::OpenGLFloat d) const {
#ifndef NDEBUG
    if (boom::glClearDepthf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearDepthf() failed: OpenGL function \"glClearDepthf\" not loaded");
    }
#endif
    _current();
    boom::glClearDepthf(d);
}

void OpenGL::clearDepthx(boom::OpenGLFixed depth) const {
#ifndef NDEBUG
    if (boom::glClearDepthx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearDepthx() failed: OpenGL function \"glClearDepthx\" not loaded");
    }
#endif
    _current();
    boom::glClearDepthx(depth);
}

void OpenGL::clearIndex(boom::OpenGLFloat c) const {
#ifndef NDEBUG
    if (boom::glClearIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearIndex() failed: OpenGL function \"glClearIndex\" not loaded");
    }
#endif
    _current();
    boom::glClearIndex(c);
}

void OpenGL::clearNamedBufferData(boom::OpenGLUint buffer, boom::OpenGLEnum internalformat, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearNamedBufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedBufferData() failed: OpenGL function \"glClearNamedBufferData\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedBufferData(buffer, internalformat, format, type, data);
}

void OpenGL::clearNamedBufferSubData(boom::OpenGLUint buffer, boom::OpenGLEnum internalformat, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearNamedBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedBufferSubData() failed: OpenGL function \"glClearNamedBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
}

void OpenGL::clearNamedFramebufferfi(boom::OpenGLUint framebuffer, boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLFloat depth, boom::OpenGLInt stencil) const {
#ifndef NDEBUG
    if (boom::glClearNamedFramebufferfi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedFramebufferfi() failed: OpenGL function \"glClearNamedFramebufferfi\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
}

void OpenGL::clearNamedFramebufferfv(boom::OpenGLUint framebuffer, boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glClearNamedFramebufferfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedFramebufferfv() failed: OpenGL function \"glClearNamedFramebufferfv\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearNamedFramebufferiv(boom::OpenGLUint framebuffer, boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glClearNamedFramebufferiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedFramebufferiv() failed: OpenGL function \"glClearNamedFramebufferiv\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearNamedFramebufferuiv(boom::OpenGLUint framebuffer, boom::OpenGLEnum buffer, boom::OpenGLInt drawbuffer, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glClearNamedFramebufferuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearNamedFramebufferuiv() failed: OpenGL function \"glClearNamedFramebufferuiv\" not loaded");
    }
#endif
    _current();
    boom::glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
}

void OpenGL::clearStencil(boom::OpenGLInt s) const {
#ifndef NDEBUG
    if (boom::glClearStencil == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearStencil() failed: OpenGL function \"glClearStencil\" not loaded");
    }
#endif
    _current();
    boom::glClearStencil(s);
}

void OpenGL::clearTexImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearTexImage() failed: OpenGL function \"glClearTexImage\" not loaded");
    }
#endif
    _current();
    boom::glClearTexImage(texture, level, format, type, data);
}

void OpenGL::clearTexSubImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* data) const {
#ifndef NDEBUG
    if (boom::glClearTexSubImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clearTexSubImage() failed: OpenGL function \"glClearTexSubImage\" not loaded");
    }
#endif
    _current();
    boom::glClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
}

void OpenGL::clientActiveTexture(boom::OpenGLEnum texture) const {
#ifndef NDEBUG
    if (boom::glClientActiveTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clientActiveTexture() failed: OpenGL function \"glClientActiveTexture\" not loaded");
    }
#endif
    _current();
    boom::glClientActiveTexture(texture);
}

boom::OpenGLEnum OpenGL::clientWaitSync(boom::OpenGLSync sync, boom::OpenGLBitfield flags, boom::OpenGLUInt64 timeout) const {
#ifndef NDEBUG
    if (boom::glClientWaitSync == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clientWaitSync() failed: OpenGL function \"glClientWaitSync\" not loaded");
    }
#endif
    _current();
    return boom::glClientWaitSync(sync, flags, timeout);
}

void OpenGL::clipControl(boom::OpenGLEnum origin, boom::OpenGLEnum depth) const {
#ifndef NDEBUG
    if (boom::glClipControl == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clipControl() failed: OpenGL function \"glClipControl\" not loaded");
    }
#endif
    _current();
    boom::glClipControl(origin, depth);
}

void OpenGL::clipPlane(boom::OpenGLEnum plane, boom::OpenGLDouble const* equation) const {
#ifndef NDEBUG
    if (boom::glClipPlane == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clipPlane() failed: OpenGL function \"glClipPlane\" not loaded");
    }
#endif
    _current();
    boom::glClipPlane(plane, equation);
}

void OpenGL::clipPlanef(boom::OpenGLEnum p, boom::OpenGLFloat const* eqn) const {
#ifndef NDEBUG
    if (boom::glClipPlanef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clipPlanef() failed: OpenGL function \"glClipPlanef\" not loaded");
    }
#endif
    _current();
    boom::glClipPlanef(p, eqn);
}

void OpenGL::clipPlanex(boom::OpenGLEnum plane, boom::OpenGLFixed const* equation) const {
#ifndef NDEBUG
    if (boom::glClipPlanex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::clipPlanex() failed: OpenGL function \"glClipPlanex\" not loaded");
    }
#endif
    _current();
    boom::glClipPlanex(plane, equation);
}

void OpenGL::color3b(boom::OpenGLByte red, boom::OpenGLByte green, boom::OpenGLByte blue) const {
#ifndef NDEBUG
    if (boom::glColor3b == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3b() failed: OpenGL function \"glColor3b\" not loaded");
    }
#endif
    _current();
    boom::glColor3b(red, green, blue);
}

void OpenGL::color3bv(boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glColor3bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3bv() failed: OpenGL function \"glColor3bv\" not loaded");
    }
#endif
    _current();
    boom::glColor3bv(v);
}

void OpenGL::color3d(boom::OpenGLDouble red, boom::OpenGLDouble green, boom::OpenGLDouble blue) const {
#ifndef NDEBUG
    if (boom::glColor3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3d() failed: OpenGL function \"glColor3d\" not loaded");
    }
#endif
    _current();
    boom::glColor3d(red, green, blue);
}

void OpenGL::color3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glColor3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3dv() failed: OpenGL function \"glColor3dv\" not loaded");
    }
#endif
    _current();
    boom::glColor3dv(v);
}

void OpenGL::color3f(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue) const {
#ifndef NDEBUG
    if (boom::glColor3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3f() failed: OpenGL function \"glColor3f\" not loaded");
    }
#endif
    _current();
    boom::glColor3f(red, green, blue);
}

void OpenGL::color3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glColor3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3fv() failed: OpenGL function \"glColor3fv\" not loaded");
    }
#endif
    _current();
    boom::glColor3fv(v);
}

void OpenGL::color3i(boom::OpenGLInt red, boom::OpenGLInt green, boom::OpenGLInt blue) const {
#ifndef NDEBUG
    if (boom::glColor3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3i() failed: OpenGL function \"glColor3i\" not loaded");
    }
#endif
    _current();
    boom::glColor3i(red, green, blue);
}

void OpenGL::color3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glColor3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3iv() failed: OpenGL function \"glColor3iv\" not loaded");
    }
#endif
    _current();
    boom::glColor3iv(v);
}

void OpenGL::color3s(boom::OpenGLShort red, boom::OpenGLShort green, boom::OpenGLShort blue) const {
#ifndef NDEBUG
    if (boom::glColor3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3s() failed: OpenGL function \"glColor3s\" not loaded");
    }
#endif
    _current();
    boom::glColor3s(red, green, blue);
}

void OpenGL::color3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glColor3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3sv() failed: OpenGL function \"glColor3sv\" not loaded");
    }
#endif
    _current();
    boom::glColor3sv(v);
}

void OpenGL::color3ub(boom::OpenGLUbyte red, boom::OpenGLUbyte green, boom::OpenGLUbyte blue) const {
#ifndef NDEBUG
    if (boom::glColor3ub == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3ub() failed: OpenGL function \"glColor3ub\" not loaded");
    }
#endif
    _current();
    boom::glColor3ub(red, green, blue);
}

void OpenGL::color3ubv(boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glColor3ubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3ubv() failed: OpenGL function \"glColor3ubv\" not loaded");
    }
#endif
    _current();
    boom::glColor3ubv(v);
}

void OpenGL::color3ui(boom::OpenGLUint red, boom::OpenGLUint green, boom::OpenGLUint blue) const {
#ifndef NDEBUG
    if (boom::glColor3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3ui() failed: OpenGL function \"glColor3ui\" not loaded");
    }
#endif
    _current();
    boom::glColor3ui(red, green, blue);
}

void OpenGL::color3uiv(boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glColor3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3uiv() failed: OpenGL function \"glColor3uiv\" not loaded");
    }
#endif
    _current();
    boom::glColor3uiv(v);
}

void OpenGL::color3us(boom::OpenGLUShort red, boom::OpenGLUShort green, boom::OpenGLUShort blue) const {
#ifndef NDEBUG
    if (boom::glColor3us == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3us() failed: OpenGL function \"glColor3us\" not loaded");
    }
#endif
    _current();
    boom::glColor3us(red, green, blue);
}

void OpenGL::color3usv(boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glColor3usv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color3usv() failed: OpenGL function \"glColor3usv\" not loaded");
    }
#endif
    _current();
    boom::glColor3usv(v);
}

void OpenGL::color4b(boom::OpenGLByte red, boom::OpenGLByte green, boom::OpenGLByte blue, boom::OpenGLByte alpha) const {
#ifndef NDEBUG
    if (boom::glColor4b == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4b() failed: OpenGL function \"glColor4b\" not loaded");
    }
#endif
    _current();
    boom::glColor4b(red, green, blue, alpha);
}

void OpenGL::color4bv(boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glColor4bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4bv() failed: OpenGL function \"glColor4bv\" not loaded");
    }
#endif
    _current();
    boom::glColor4bv(v);
}

void OpenGL::color4d(boom::OpenGLDouble red, boom::OpenGLDouble green, boom::OpenGLDouble blue, boom::OpenGLDouble alpha) const {
#ifndef NDEBUG
    if (boom::glColor4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4d() failed: OpenGL function \"glColor4d\" not loaded");
    }
#endif
    _current();
    boom::glColor4d(red, green, blue, alpha);
}

void OpenGL::color4dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glColor4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4dv() failed: OpenGL function \"glColor4dv\" not loaded");
    }
#endif
    _current();
    boom::glColor4dv(v);
}

void OpenGL::color4f(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue, boom::OpenGLFloat alpha) const {
#ifndef NDEBUG
    if (boom::glColor4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4f() failed: OpenGL function \"glColor4f\" not loaded");
    }
#endif
    _current();
    boom::glColor4f(red, green, blue, alpha);
}

void OpenGL::color4fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glColor4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4fv() failed: OpenGL function \"glColor4fv\" not loaded");
    }
#endif
    _current();
    boom::glColor4fv(v);
}

void OpenGL::color4i(boom::OpenGLInt red, boom::OpenGLInt green, boom::OpenGLInt blue, boom::OpenGLInt alpha) const {
#ifndef NDEBUG
    if (boom::glColor4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4i() failed: OpenGL function \"glColor4i\" not loaded");
    }
#endif
    _current();
    boom::glColor4i(red, green, blue, alpha);
}

void OpenGL::color4iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glColor4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4iv() failed: OpenGL function \"glColor4iv\" not loaded");
    }
#endif
    _current();
    boom::glColor4iv(v);
}

void OpenGL::color4s(boom::OpenGLShort red, boom::OpenGLShort green, boom::OpenGLShort blue, boom::OpenGLShort alpha) const {
#ifndef NDEBUG
    if (boom::glColor4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4s() failed: OpenGL function \"glColor4s\" not loaded");
    }
#endif
    _current();
    boom::glColor4s(red, green, blue, alpha);
}

void OpenGL::color4sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glColor4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4sv() failed: OpenGL function \"glColor4sv\" not loaded");
    }
#endif
    _current();
    boom::glColor4sv(v);
}

void OpenGL::color4ub(boom::OpenGLUbyte red, boom::OpenGLUbyte green, boom::OpenGLUbyte blue, boom::OpenGLUbyte alpha) const {
#ifndef NDEBUG
    if (boom::glColor4ub == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4ub() failed: OpenGL function \"glColor4ub\" not loaded");
    }
#endif
    _current();
    boom::glColor4ub(red, green, blue, alpha);
}

void OpenGL::color4ubv(boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glColor4ubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4ubv() failed: OpenGL function \"glColor4ubv\" not loaded");
    }
#endif
    _current();
    boom::glColor4ubv(v);
}

void OpenGL::color4ui(boom::OpenGLUint red, boom::OpenGLUint green, boom::OpenGLUint blue, boom::OpenGLUint alpha) const {
#ifndef NDEBUG
    if (boom::glColor4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4ui() failed: OpenGL function \"glColor4ui\" not loaded");
    }
#endif
    _current();
    boom::glColor4ui(red, green, blue, alpha);
}

void OpenGL::color4uiv(boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glColor4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4uiv() failed: OpenGL function \"glColor4uiv\" not loaded");
    }
#endif
    _current();
    boom::glColor4uiv(v);
}

void OpenGL::color4us(boom::OpenGLUShort red, boom::OpenGLUShort green, boom::OpenGLUShort blue, boom::OpenGLUShort alpha) const {
#ifndef NDEBUG
    if (boom::glColor4us == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4us() failed: OpenGL function \"glColor4us\" not loaded");
    }
#endif
    _current();
    boom::glColor4us(red, green, blue, alpha);
}

void OpenGL::color4usv(boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glColor4usv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4usv() failed: OpenGL function \"glColor4usv\" not loaded");
    }
#endif
    _current();
    boom::glColor4usv(v);
}

void OpenGL::color4x(boom::OpenGLFixed red, boom::OpenGLFixed green, boom::OpenGLFixed blue, boom::OpenGLFixed alpha) const {
#ifndef NDEBUG
    if (boom::glColor4x == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::color4x() failed: OpenGL function \"glColor4x\" not loaded");
    }
#endif
    _current();
    boom::glColor4x(red, green, blue, alpha);
}

void OpenGL::colorMask(boom::OpenGLBoolean red, boom::OpenGLBoolean green, boom::OpenGLBoolean blue, boom::OpenGLBoolean alpha) const {
#ifndef NDEBUG
    if (boom::glColorMask == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorMask() failed: OpenGL function \"glColorMask\" not loaded");
    }
#endif
    _current();
    boom::glColorMask(red, green, blue, alpha);
}

void OpenGL::colorMaski(boom::OpenGLUint index, boom::OpenGLBoolean r, boom::OpenGLBoolean g, boom::OpenGLBoolean b, boom::OpenGLBoolean a) const {
#ifndef NDEBUG
    if (boom::glColorMaski == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorMaski() failed: OpenGL function \"glColorMaski\" not loaded");
    }
#endif
    _current();
    boom::glColorMaski(index, r, g, b, a);
}

void OpenGL::colorMaterial(boom::OpenGLEnum face, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glColorMaterial == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorMaterial() failed: OpenGL function \"glColorMaterial\" not loaded");
    }
#endif
    _current();
    boom::glColorMaterial(face, mode);
}

void OpenGL::colorP3ui(boom::OpenGLEnum type, boom::OpenGLUint color) const {
#ifndef NDEBUG
    if (boom::glColorP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorP3ui() failed: OpenGL function \"glColorP3ui\" not loaded");
    }
#endif
    _current();
    boom::glColorP3ui(type, color);
}

void OpenGL::colorP3uiv(boom::OpenGLEnum type, boom::OpenGLUint const* color) const {
#ifndef NDEBUG
    if (boom::glColorP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorP3uiv() failed: OpenGL function \"glColorP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glColorP3uiv(type, color);
}

void OpenGL::colorP4ui(boom::OpenGLEnum type, boom::OpenGLUint color) const {
#ifndef NDEBUG
    if (boom::glColorP4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorP4ui() failed: OpenGL function \"glColorP4ui\" not loaded");
    }
#endif
    _current();
    boom::glColorP4ui(type, color);
}

void OpenGL::colorP4uiv(boom::OpenGLEnum type, boom::OpenGLUint const* color) const {
#ifndef NDEBUG
    if (boom::glColorP4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorP4uiv() failed: OpenGL function \"glColorP4uiv\" not loaded");
    }
#endif
    _current();
    boom::glColorP4uiv(type, color);
}

void OpenGL::colorPointer(boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glColorPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::colorPointer() failed: OpenGL function \"glColorPointer\" not loaded");
    }
#endif
    _current();
    boom::glColorPointer(size, type, stride, pointer);
}

void OpenGL::compileShader(boom::OpenGLUint shader) const {
#ifndef NDEBUG
    if (boom::glCompileShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compileShader() failed: OpenGL function \"glCompileShader\" not loaded");
    }
#endif
    _current();
    boom::glCompileShader(shader);
}

void OpenGL::compressedTexImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLInt border, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexImage1D() failed: OpenGL function \"glCompressedTexImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
}

void OpenGL::compressedTexImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLInt border, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexImage2D() failed: OpenGL function \"glCompressedTexImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void OpenGL::compressedTexImage3D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLInt border, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexImage3D() failed: OpenGL function \"glCompressedTexImage3D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
}

void OpenGL::compressedTexSubImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLSizei width, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexSubImage1D() failed: OpenGL function \"glCompressedTexSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
}

void OpenGL::compressedTexSubImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexSubImage2D() failed: OpenGL function \"glCompressedTexSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void OpenGL::compressedTexSubImage3D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTexSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTexSubImage3D() failed: OpenGL function \"glCompressedTexSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void OpenGL::compressedTextureSubImage1D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLSizei width, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTextureSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTextureSubImage1D() failed: OpenGL function \"glCompressedTextureSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
}

void OpenGL::compressedTextureSubImage2D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTextureSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTextureSubImage2D() failed: OpenGL function \"glCompressedTextureSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void OpenGL::compressedTextureSubImage3D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLSizei imageSize, void const* data) const {
#ifndef NDEBUG
    if (boom::glCompressedTextureSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::compressedTextureSubImage3D() failed: OpenGL function \"glCompressedTextureSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glCompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
}

void OpenGL::copyBufferSubData(boom::OpenGLEnum readTarget, boom::OpenGLEnum writeTarget, boom::OpenGLIntptr readOffset, boom::OpenGLIntptr writeOffset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glCopyBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyBufferSubData() failed: OpenGL function \"glCopyBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

void OpenGL::copyImageSubData(boom::OpenGLUint srcName, boom::OpenGLEnum srcTarget, boom::OpenGLInt srcLevel, boom::OpenGLInt srcX, boom::OpenGLInt srcY, boom::OpenGLInt srcZ, boom::OpenGLUint dstName, boom::OpenGLEnum dstTarget, boom::OpenGLInt dstLevel, boom::OpenGLInt dstX, boom::OpenGLInt dstY, boom::OpenGLInt dstZ, boom::OpenGLSizei srcWidth, boom::OpenGLSizei srcHeight, boom::OpenGLSizei srcDepth) const {
#ifndef NDEBUG
    if (boom::glCopyImageSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyImageSubData() failed: OpenGL function \"glCopyImageSubData\" not loaded");
    }
#endif
    _current();
    boom::glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

void OpenGL::copyNamedBufferSubData(boom::OpenGLUint readBuffer, boom::OpenGLUint writeBuffer, boom::OpenGLIntptr readOffset, boom::OpenGLIntptr writeOffset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glCopyNamedBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyNamedBufferSubData() failed: OpenGL function \"glCopyNamedBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

void OpenGL::copyPixels(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum type) const {
#ifndef NDEBUG
    if (boom::glCopyPixels == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyPixels() failed: OpenGL function \"glCopyPixels\" not loaded");
    }
#endif
    _current();
    boom::glCopyPixels(x, y, width, height, type);
}

void OpenGL::copyTexImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum internalformat, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLInt border) const {
#ifndef NDEBUG
    if (boom::glCopyTexImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTexImage1D() failed: OpenGL function \"glCopyTexImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

void OpenGL::copyTexImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum internalformat, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLInt border) const {
#ifndef NDEBUG
    if (boom::glCopyTexImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTexImage2D() failed: OpenGL function \"glCopyTexImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void OpenGL::copyTexSubImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width) const {
#ifndef NDEBUG
    if (boom::glCopyTexSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTexSubImage1D() failed: OpenGL function \"glCopyTexSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

void OpenGL::copyTexSubImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glCopyTexSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTexSubImage2D() failed: OpenGL function \"glCopyTexSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

void OpenGL::copyTexSubImage3D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glCopyTexSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTexSubImage3D() failed: OpenGL function \"glCopyTexSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void OpenGL::copyTextureSubImage1D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width) const {
#ifndef NDEBUG
    if (boom::glCopyTextureSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTextureSubImage1D() failed: OpenGL function \"glCopyTextureSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
}

void OpenGL::copyTextureSubImage2D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glCopyTextureSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTextureSubImage2D() failed: OpenGL function \"glCopyTextureSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
}

void OpenGL::copyTextureSubImage3D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glCopyTextureSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::copyTextureSubImage3D() failed: OpenGL function \"glCopyTextureSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

void OpenGL::createBuffers(boom::OpenGLSizei n, boom::OpenGLUint* buffers) const {
#ifndef NDEBUG
    if (boom::glCreateBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createBuffers() failed: OpenGL function \"glCreateBuffers\" not loaded");
    }
#endif
    _current();
    boom::glCreateBuffers(n, buffers);
}

void OpenGL::createFramebuffers(boom::OpenGLSizei n, boom::OpenGLUint* framebuffers) const {
#ifndef NDEBUG
    if (boom::glCreateFramebuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createFramebuffers() failed: OpenGL function \"glCreateFramebuffers\" not loaded");
    }
#endif
    _current();
    boom::glCreateFramebuffers(n, framebuffers);
}

boom::OpenGLUint OpenGL::createProgram() const {
#ifndef NDEBUG
    if (boom::glCreateProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createProgram() failed: OpenGL function \"glCreateProgram\" not loaded");
    }
#endif
    _current();
    return boom::glCreateProgram();
}

void OpenGL::createProgramPipelines(boom::OpenGLSizei n, boom::OpenGLUint* pipelines) const {
#ifndef NDEBUG
    if (boom::glCreateProgramPipelines == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createProgramPipelines() failed: OpenGL function \"glCreateProgramPipelines\" not loaded");
    }
#endif
    _current();
    boom::glCreateProgramPipelines(n, pipelines);
}

void OpenGL::createQueries(boom::OpenGLEnum target, boom::OpenGLSizei n, boom::OpenGLUint* ids) const {
#ifndef NDEBUG
    if (boom::glCreateQueries == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createQueries() failed: OpenGL function \"glCreateQueries\" not loaded");
    }
#endif
    _current();
    boom::glCreateQueries(target, n, ids);
}

void OpenGL::createRenderbuffers(boom::OpenGLSizei n, boom::OpenGLUint* renderbuffers) const {
#ifndef NDEBUG
    if (boom::glCreateRenderbuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createRenderbuffers() failed: OpenGL function \"glCreateRenderbuffers\" not loaded");
    }
#endif
    _current();
    boom::glCreateRenderbuffers(n, renderbuffers);
}

void OpenGL::createSamplers(boom::OpenGLSizei n, boom::OpenGLUint* samplers) const {
#ifndef NDEBUG
    if (boom::glCreateSamplers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createSamplers() failed: OpenGL function \"glCreateSamplers\" not loaded");
    }
#endif
    _current();
    boom::glCreateSamplers(n, samplers);
}

boom::OpenGLUint OpenGL::createShader(boom::OpenGLEnum type) const {
#ifndef NDEBUG
    if (boom::glCreateShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createShader() failed: OpenGL function \"glCreateShader\" not loaded");
    }
#endif
    _current();
    return boom::glCreateShader(type);
}

boom::OpenGLUint OpenGL::createShaderProgramv(boom::OpenGLEnum type, boom::OpenGLSizei count, boom::OpenGLChar const* const* strings) const {
#ifndef NDEBUG
    if (boom::glCreateShaderProgramv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createShaderProgramv() failed: OpenGL function \"glCreateShaderProgramv\" not loaded");
    }
#endif
    _current();
    return boom::glCreateShaderProgramv(type, count, strings);
}

void OpenGL::createTextures(boom::OpenGLEnum target, boom::OpenGLSizei n, boom::OpenGLUint* textures) const {
#ifndef NDEBUG
    if (boom::glCreateTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createTextures() failed: OpenGL function \"glCreateTextures\" not loaded");
    }
#endif
    _current();
    boom::glCreateTextures(target, n, textures);
}

void OpenGL::createTransformFeedbacks(boom::OpenGLSizei n, boom::OpenGLUint* ids) const {
#ifndef NDEBUG
    if (boom::glCreateTransformFeedbacks == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createTransformFeedbacks() failed: OpenGL function \"glCreateTransformFeedbacks\" not loaded");
    }
#endif
    _current();
    boom::glCreateTransformFeedbacks(n, ids);
}

void OpenGL::createVertexArrays(boom::OpenGLSizei n, boom::OpenGLUint* arrays) const {
#ifndef NDEBUG
    if (boom::glCreateVertexArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::createVertexArrays() failed: OpenGL function \"glCreateVertexArrays\" not loaded");
    }
#endif
    _current();
    boom::glCreateVertexArrays(n, arrays);
}

void OpenGL::cullFace(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glCullFace == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::cullFace() failed: OpenGL function \"glCullFace\" not loaded");
    }
#endif
    _current();
    boom::glCullFace(mode);
}

void OpenGL::debugMessageCallback(boom::OpenGLDebugProc callback, void const* userParam) const {
#ifndef NDEBUG
    if (boom::glDebugMessageCallback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::debugMessageCallback() failed: OpenGL function \"glDebugMessageCallback\" not loaded");
    }
#endif
    _current();
    boom::glDebugMessageCallback(callback, userParam);
}

void OpenGL::debugMessageControl(boom::OpenGLEnum source, boom::OpenGLEnum type, boom::OpenGLEnum severity, boom::OpenGLSizei count, boom::OpenGLUint const* ids, boom::OpenGLBoolean enabled) const {
#ifndef NDEBUG
    if (boom::glDebugMessageControl == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::debugMessageControl() failed: OpenGL function \"glDebugMessageControl\" not loaded");
    }
#endif
    _current();
    boom::glDebugMessageControl(source, type, severity, count, ids, enabled);
}

void OpenGL::debugMessageInsert(boom::OpenGLEnum source, boom::OpenGLEnum type, boom::OpenGLUint id, boom::OpenGLEnum severity, boom::OpenGLSizei length, boom::OpenGLChar const* buf) const {
#ifndef NDEBUG
    if (boom::glDebugMessageInsert == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::debugMessageInsert() failed: OpenGL function \"glDebugMessageInsert\" not loaded");
    }
#endif
    _current();
    boom::glDebugMessageInsert(source, type, id, severity, length, buf);
}

void OpenGL::deleteBuffers(boom::OpenGLSizei n, boom::OpenGLUint const* buffers) const {
#ifndef NDEBUG
    if (boom::glDeleteBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteBuffers() failed: OpenGL function \"glDeleteBuffers\" not loaded");
    }
#endif
    _current();
    boom::glDeleteBuffers(n, buffers);
}

void OpenGL::deleteFramebuffers(boom::OpenGLSizei n, boom::OpenGLUint const* framebuffers) const {
#ifndef NDEBUG
    if (boom::glDeleteFramebuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteFramebuffers() failed: OpenGL function \"glDeleteFramebuffers\" not loaded");
    }
#endif
    _current();
    boom::glDeleteFramebuffers(n, framebuffers);
}

void OpenGL::deleteLists(boom::OpenGLUint list, boom::OpenGLSizei range) const {
#ifndef NDEBUG
    if (boom::glDeleteLists == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteLists() failed: OpenGL function \"glDeleteLists\" not loaded");
    }
#endif
    _current();
    boom::glDeleteLists(list, range);
}

void OpenGL::deleteProgram(boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glDeleteProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteProgram() failed: OpenGL function \"glDeleteProgram\" not loaded");
    }
#endif
    _current();
    boom::glDeleteProgram(program);
}

void OpenGL::deleteProgramPipelines(boom::OpenGLSizei n, boom::OpenGLUint const* pipelines) const {
#ifndef NDEBUG
    if (boom::glDeleteProgramPipelines == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteProgramPipelines() failed: OpenGL function \"glDeleteProgramPipelines\" not loaded");
    }
#endif
    _current();
    boom::glDeleteProgramPipelines(n, pipelines);
}

void OpenGL::deleteQueries(boom::OpenGLSizei n, boom::OpenGLUint const* ids) const {
#ifndef NDEBUG
    if (boom::glDeleteQueries == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteQueries() failed: OpenGL function \"glDeleteQueries\" not loaded");
    }
#endif
    _current();
    boom::glDeleteQueries(n, ids);
}

void OpenGL::deleteRenderbuffers(boom::OpenGLSizei n, boom::OpenGLUint const* renderbuffers) const {
#ifndef NDEBUG
    if (boom::glDeleteRenderbuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteRenderbuffers() failed: OpenGL function \"glDeleteRenderbuffers\" not loaded");
    }
#endif
    _current();
    boom::glDeleteRenderbuffers(n, renderbuffers);
}

void OpenGL::deleteSamplers(boom::OpenGLSizei count, boom::OpenGLUint const* samplers) const {
#ifndef NDEBUG
    if (boom::glDeleteSamplers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteSamplers() failed: OpenGL function \"glDeleteSamplers\" not loaded");
    }
#endif
    _current();
    boom::glDeleteSamplers(count, samplers);
}

void OpenGL::deleteShader(boom::OpenGLUint shader) const {
#ifndef NDEBUG
    if (boom::glDeleteShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteShader() failed: OpenGL function \"glDeleteShader\" not loaded");
    }
#endif
    _current();
    boom::glDeleteShader(shader);
}

void OpenGL::deleteSync(boom::OpenGLSync sync) const {
#ifndef NDEBUG
    if (boom::glDeleteSync == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteSync() failed: OpenGL function \"glDeleteSync\" not loaded");
    }
#endif
    _current();
    boom::glDeleteSync(sync);
}

void OpenGL::deleteTextures(boom::OpenGLSizei n, boom::OpenGLUint const* textures) const {
#ifndef NDEBUG
    if (boom::glDeleteTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteTextures() failed: OpenGL function \"glDeleteTextures\" not loaded");
    }
#endif
    _current();
    boom::glDeleteTextures(n, textures);
}

void OpenGL::deleteTransformFeedbacks(boom::OpenGLSizei n, boom::OpenGLUint const* ids) const {
#ifndef NDEBUG
    if (boom::glDeleteTransformFeedbacks == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteTransformFeedbacks() failed: OpenGL function \"glDeleteTransformFeedbacks\" not loaded");
    }
#endif
    _current();
    boom::glDeleteTransformFeedbacks(n, ids);
}

void OpenGL::deleteVertexArrays(boom::OpenGLSizei n, boom::OpenGLUint const* arrays) const {
#ifndef NDEBUG
    if (boom::glDeleteVertexArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::deleteVertexArrays() failed: OpenGL function \"glDeleteVertexArrays\" not loaded");
    }
#endif
    _current();
    boom::glDeleteVertexArrays(n, arrays);
}

void OpenGL::depthFunc(boom::OpenGLEnum func) const {
#ifndef NDEBUG
    if (boom::glDepthFunc == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthFunc() failed: OpenGL function \"glDepthFunc\" not loaded");
    }
#endif
    _current();
    boom::glDepthFunc(func);
}

void OpenGL::depthMask(boom::OpenGLBoolean flag) const {
#ifndef NDEBUG
    if (boom::glDepthMask == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthMask() failed: OpenGL function \"glDepthMask\" not loaded");
    }
#endif
    _current();
    boom::glDepthMask(flag);
}

void OpenGL::depthRange(boom::OpenGLDouble n, boom::OpenGLDouble f) const {
#ifndef NDEBUG
    if (boom::glDepthRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthRange() failed: OpenGL function \"glDepthRange\" not loaded");
    }
#endif
    _current();
    boom::glDepthRange(n, f);
}

void OpenGL::depthRangeArrayv(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glDepthRangeArrayv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthRangeArrayv() failed: OpenGL function \"glDepthRangeArrayv\" not loaded");
    }
#endif
    _current();
    boom::glDepthRangeArrayv(first, count, v);
}

void OpenGL::depthRangeIndexed(boom::OpenGLUint index, boom::OpenGLDouble n, boom::OpenGLDouble f) const {
#ifndef NDEBUG
    if (boom::glDepthRangeIndexed == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthRangeIndexed() failed: OpenGL function \"glDepthRangeIndexed\" not loaded");
    }
#endif
    _current();
    boom::glDepthRangeIndexed(index, n, f);
}

void OpenGL::depthRangef(boom::OpenGLFloat n, boom::OpenGLFloat f) const {
#ifndef NDEBUG
    if (boom::glDepthRangef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthRangef() failed: OpenGL function \"glDepthRangef\" not loaded");
    }
#endif
    _current();
    boom::glDepthRangef(n, f);
}

void OpenGL::depthRangex(boom::OpenGLFixed n, boom::OpenGLFixed f) const {
#ifndef NDEBUG
    if (boom::glDepthRangex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::depthRangex() failed: OpenGL function \"glDepthRangex\" not loaded");
    }
#endif
    _current();
    boom::glDepthRangex(n, f);
}

void OpenGL::detachShader(boom::OpenGLUint program, boom::OpenGLUint shader) const {
#ifndef NDEBUG
    if (boom::glDetachShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::detachShader() failed: OpenGL function \"glDetachShader\" not loaded");
    }
#endif
    _current();
    boom::glDetachShader(program, shader);
}

void OpenGL::disable(boom::OpenGLEnum cap) const {
#ifndef NDEBUG
    if (boom::glDisable == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::disable() failed: OpenGL function \"glDisable\" not loaded");
    }
#endif
    _current();
    boom::glDisable(cap);
}

void OpenGL::disableClientState(boom::OpenGLEnum array) const {
#ifndef NDEBUG
    if (boom::glDisableClientState == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::disableClientState() failed: OpenGL function \"glDisableClientState\" not loaded");
    }
#endif
    _current();
    boom::glDisableClientState(array);
}

void OpenGL::disableVertexArrayAttrib(boom::OpenGLUint vaobj, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glDisableVertexArrayAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::disableVertexArrayAttrib() failed: OpenGL function \"glDisableVertexArrayAttrib\" not loaded");
    }
#endif
    _current();
    boom::glDisableVertexArrayAttrib(vaobj, index);
}

void OpenGL::disableVertexAttribArray(boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glDisableVertexAttribArray == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::disableVertexAttribArray() failed: OpenGL function \"glDisableVertexAttribArray\" not loaded");
    }
#endif
    _current();
    boom::glDisableVertexAttribArray(index);
}

void OpenGL::disablei(boom::OpenGLEnum target, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glDisablei == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::disablei() failed: OpenGL function \"glDisablei\" not loaded");
    }
#endif
    _current();
    boom::glDisablei(target, index);
}

void OpenGL::dispatchCompute(boom::OpenGLUint num_groups_x, boom::OpenGLUint num_groups_y, boom::OpenGLUint num_groups_z) const {
#ifndef NDEBUG
    if (boom::glDispatchCompute == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::dispatchCompute() failed: OpenGL function \"glDispatchCompute\" not loaded");
    }
#endif
    _current();
    boom::glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

void OpenGL::dispatchComputeIndirect(boom::OpenGLIntptr indirect) const {
#ifndef NDEBUG
    if (boom::glDispatchComputeIndirect == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::dispatchComputeIndirect() failed: OpenGL function \"glDispatchComputeIndirect\" not loaded");
    }
#endif
    _current();
    boom::glDispatchComputeIndirect(indirect);
}

void OpenGL::drawArrays(boom::OpenGLEnum mode, boom::OpenGLInt first, boom::OpenGLSizei count) const {
#ifndef NDEBUG
    if (boom::glDrawArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawArrays() failed: OpenGL function \"glDrawArrays\" not loaded");
    }
#endif
    _current();
    boom::glDrawArrays(mode, first, count);
}

void OpenGL::drawArraysIndirect(boom::OpenGLEnum mode, void const* indirect) const {
#ifndef NDEBUG
    if (boom::glDrawArraysIndirect == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawArraysIndirect() failed: OpenGL function \"glDrawArraysIndirect\" not loaded");
    }
#endif
    _current();
    boom::glDrawArraysIndirect(mode, indirect);
}

void OpenGL::drawArraysInstanced(boom::OpenGLEnum mode, boom::OpenGLInt first, boom::OpenGLSizei count, boom::OpenGLSizei instancecount) const {
#ifndef NDEBUG
    if (boom::glDrawArraysInstanced == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawArraysInstanced() failed: OpenGL function \"glDrawArraysInstanced\" not loaded");
    }
#endif
    _current();
    boom::glDrawArraysInstanced(mode, first, count, instancecount);
}

void OpenGL::drawArraysInstancedBaseInstance(boom::OpenGLEnum mode, boom::OpenGLInt first, boom::OpenGLSizei count, boom::OpenGLSizei instancecount, boom::OpenGLUint baseinstance) const {
#ifndef NDEBUG
    if (boom::glDrawArraysInstancedBaseInstance == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawArraysInstancedBaseInstance() failed: OpenGL function \"glDrawArraysInstancedBaseInstance\" not loaded");
    }
#endif
    _current();
    boom::glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
}

void OpenGL::drawBuffer(boom::OpenGLEnum buf) const {
#ifndef NDEBUG
    if (boom::glDrawBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawBuffer() failed: OpenGL function \"glDrawBuffer\" not loaded");
    }
#endif
    _current();
    boom::glDrawBuffer(buf);
}

void OpenGL::drawBuffers(boom::OpenGLSizei n, boom::OpenGLEnum const* bufs) const {
#ifndef NDEBUG
    if (boom::glDrawBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawBuffers() failed: OpenGL function \"glDrawBuffers\" not loaded");
    }
#endif
    _current();
    boom::glDrawBuffers(n, bufs);
}

void OpenGL::drawElements(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices) const {
#ifndef NDEBUG
    if (boom::glDrawElements == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElements() failed: OpenGL function \"glDrawElements\" not loaded");
    }
#endif
    _current();
    boom::glDrawElements(mode, count, type, indices);
}

void OpenGL::drawElementsBaseVertex(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLInt basevertex) const {
#ifndef NDEBUG
    if (boom::glDrawElementsBaseVertex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsBaseVertex() failed: OpenGL function \"glDrawElementsBaseVertex\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsBaseVertex(mode, count, type, indices, basevertex);
}

void OpenGL::drawElementsIndirect(boom::OpenGLEnum mode, boom::OpenGLEnum type, void const* indirect) const {
#ifndef NDEBUG
    if (boom::glDrawElementsIndirect == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsIndirect() failed: OpenGL function \"glDrawElementsIndirect\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsIndirect(mode, type, indirect);
}

void OpenGL::drawElementsInstanced(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLSizei instancecount) const {
#ifndef NDEBUG
    if (boom::glDrawElementsInstanced == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsInstanced() failed: OpenGL function \"glDrawElementsInstanced\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

void OpenGL::drawElementsInstancedBaseInstance(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLSizei instancecount, boom::OpenGLUint baseinstance) const {
#ifndef NDEBUG
    if (boom::glDrawElementsInstancedBaseInstance == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsInstancedBaseInstance() failed: OpenGL function \"glDrawElementsInstancedBaseInstance\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
}

void OpenGL::drawElementsInstancedBaseVertex(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLSizei instancecount, boom::OpenGLInt basevertex) const {
#ifndef NDEBUG
    if (boom::glDrawElementsInstancedBaseVertex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsInstancedBaseVertex() failed: OpenGL function \"glDrawElementsInstancedBaseVertex\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
}

void OpenGL::drawElementsInstancedBaseVertexBaseInstance(boom::OpenGLEnum mode, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLSizei instancecount, boom::OpenGLInt basevertex, boom::OpenGLUint baseinstance) const {
#ifndef NDEBUG
    if (boom::glDrawElementsInstancedBaseVertexBaseInstance == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawElementsInstancedBaseVertexBaseInstance() failed: OpenGL function \"glDrawElementsInstancedBaseVertexBaseInstance\" not loaded");
    }
#endif
    _current();
    boom::glDrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
}

void OpenGL::drawPixels(boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glDrawPixels == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawPixels() failed: OpenGL function \"glDrawPixels\" not loaded");
    }
#endif
    _current();
    boom::glDrawPixels(width, height, format, type, pixels);
}

void OpenGL::drawRangeElements(boom::OpenGLEnum mode, boom::OpenGLUint start, boom::OpenGLUint end, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices) const {
#ifndef NDEBUG
    if (boom::glDrawRangeElements == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawRangeElements() failed: OpenGL function \"glDrawRangeElements\" not loaded");
    }
#endif
    _current();
    boom::glDrawRangeElements(mode, start, end, count, type, indices);
}

void OpenGL::drawRangeElementsBaseVertex(boom::OpenGLEnum mode, boom::OpenGLUint start, boom::OpenGLUint end, boom::OpenGLSizei count, boom::OpenGLEnum type, void const* indices, boom::OpenGLInt basevertex) const {
#ifndef NDEBUG
    if (boom::glDrawRangeElementsBaseVertex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawRangeElementsBaseVertex() failed: OpenGL function \"glDrawRangeElementsBaseVertex\" not loaded");
    }
#endif
    _current();
    boom::glDrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
}

void OpenGL::drawTransformFeedback(boom::OpenGLEnum mode, boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glDrawTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawTransformFeedback() failed: OpenGL function \"glDrawTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glDrawTransformFeedback(mode, id);
}

void OpenGL::drawTransformFeedbackInstanced(boom::OpenGLEnum mode, boom::OpenGLUint id, boom::OpenGLSizei instancecount) const {
#ifndef NDEBUG
    if (boom::glDrawTransformFeedbackInstanced == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawTransformFeedbackInstanced() failed: OpenGL function \"glDrawTransformFeedbackInstanced\" not loaded");
    }
#endif
    _current();
    boom::glDrawTransformFeedbackInstanced(mode, id, instancecount);
}

void OpenGL::drawTransformFeedbackStream(boom::OpenGLEnum mode, boom::OpenGLUint id, boom::OpenGLUint stream) const {
#ifndef NDEBUG
    if (boom::glDrawTransformFeedbackStream == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawTransformFeedbackStream() failed: OpenGL function \"glDrawTransformFeedbackStream\" not loaded");
    }
#endif
    _current();
    boom::glDrawTransformFeedbackStream(mode, id, stream);
}

void OpenGL::drawTransformFeedbackStreamInstanced(boom::OpenGLEnum mode, boom::OpenGLUint id, boom::OpenGLUint stream, boom::OpenGLSizei instancecount) const {
#ifndef NDEBUG
    if (boom::glDrawTransformFeedbackStreamInstanced == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::drawTransformFeedbackStreamInstanced() failed: OpenGL function \"glDrawTransformFeedbackStreamInstanced\" not loaded");
    }
#endif
    _current();
    boom::glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
}

void OpenGL::edgeFlag(boom::OpenGLBoolean flag) const {
#ifndef NDEBUG
    if (boom::glEdgeFlag == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::edgeFlag() failed: OpenGL function \"glEdgeFlag\" not loaded");
    }
#endif
    _current();
    boom::glEdgeFlag(flag);
}

void OpenGL::edgeFlagPointer(boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glEdgeFlagPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::edgeFlagPointer() failed: OpenGL function \"glEdgeFlagPointer\" not loaded");
    }
#endif
    _current();
    boom::glEdgeFlagPointer(stride, pointer);
}

void OpenGL::edgeFlagv(boom::OpenGLBoolean const* flag) const {
#ifndef NDEBUG
    if (boom::glEdgeFlagv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::edgeFlagv() failed: OpenGL function \"glEdgeFlagv\" not loaded");
    }
#endif
    _current();
    boom::glEdgeFlagv(flag);
}

void OpenGL::enable(boom::OpenGLEnum cap) const {
#ifndef NDEBUG
    if (boom::glEnable == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::enable() failed: OpenGL function \"glEnable\" not loaded");
    }
#endif
    _current();
    boom::glEnable(cap);
}

void OpenGL::enableClientState(boom::OpenGLEnum array) const {
#ifndef NDEBUG
    if (boom::glEnableClientState == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::enableClientState() failed: OpenGL function \"glEnableClientState\" not loaded");
    }
#endif
    _current();
    boom::glEnableClientState(array);
}

void OpenGL::enableVertexArrayAttrib(boom::OpenGLUint vaobj, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glEnableVertexArrayAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::enableVertexArrayAttrib() failed: OpenGL function \"glEnableVertexArrayAttrib\" not loaded");
    }
#endif
    _current();
    boom::glEnableVertexArrayAttrib(vaobj, index);
}

void OpenGL::enableVertexAttribArray(boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glEnableVertexAttribArray == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::enableVertexAttribArray() failed: OpenGL function \"glEnableVertexAttribArray\" not loaded");
    }
#endif
    _current();
    boom::glEnableVertexAttribArray(index);
}

void OpenGL::enablei(boom::OpenGLEnum target, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glEnablei == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::enablei() failed: OpenGL function \"glEnablei\" not loaded");
    }
#endif
    _current();
    boom::glEnablei(target, index);
}

void OpenGL::end() const {
#ifndef NDEBUG
    if (boom::glEnd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::end() failed: OpenGL function \"glEnd\" not loaded");
    }
#endif
    _current();
    boom::glEnd();
}

void OpenGL::endConditionalRender() const {
#ifndef NDEBUG
    if (boom::glEndConditionalRender == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::endConditionalRender() failed: OpenGL function \"glEndConditionalRender\" not loaded");
    }
#endif
    _current();
    boom::glEndConditionalRender();
}

void OpenGL::endList() const {
#ifndef NDEBUG
    if (boom::glEndList == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::endList() failed: OpenGL function \"glEndList\" not loaded");
    }
#endif
    _current();
    boom::glEndList();
}

void OpenGL::endQuery(boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glEndQuery == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::endQuery() failed: OpenGL function \"glEndQuery\" not loaded");
    }
#endif
    _current();
    boom::glEndQuery(target);
}

void OpenGL::endQueryIndexed(boom::OpenGLEnum target, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glEndQueryIndexed == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::endQueryIndexed() failed: OpenGL function \"glEndQueryIndexed\" not loaded");
    }
#endif
    _current();
    boom::glEndQueryIndexed(target, index);
}

void OpenGL::endTransformFeedback() const {
#ifndef NDEBUG
    if (boom::glEndTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::endTransformFeedback() failed: OpenGL function \"glEndTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glEndTransformFeedback();
}

void OpenGL::evalCoord1d(boom::OpenGLDouble u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord1d() failed: OpenGL function \"glEvalCoord1d\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord1d(u);
}

void OpenGL::evalCoord1dv(boom::OpenGLDouble const* u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord1dv() failed: OpenGL function \"glEvalCoord1dv\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord1dv(u);
}

void OpenGL::evalCoord1f(boom::OpenGLFloat u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord1f() failed: OpenGL function \"glEvalCoord1f\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord1f(u);
}

void OpenGL::evalCoord1fv(boom::OpenGLFloat const* u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord1fv() failed: OpenGL function \"glEvalCoord1fv\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord1fv(u);
}

void OpenGL::evalCoord2d(boom::OpenGLDouble u, boom::OpenGLDouble v) const {
#ifndef NDEBUG
    if (boom::glEvalCoord2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord2d() failed: OpenGL function \"glEvalCoord2d\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord2d(u, v);
}

void OpenGL::evalCoord2dv(boom::OpenGLDouble const* u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord2dv() failed: OpenGL function \"glEvalCoord2dv\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord2dv(u);
}

void OpenGL::evalCoord2f(boom::OpenGLFloat u, boom::OpenGLFloat v) const {
#ifndef NDEBUG
    if (boom::glEvalCoord2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord2f() failed: OpenGL function \"glEvalCoord2f\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord2f(u, v);
}

void OpenGL::evalCoord2fv(boom::OpenGLFloat const* u) const {
#ifndef NDEBUG
    if (boom::glEvalCoord2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalCoord2fv() failed: OpenGL function \"glEvalCoord2fv\" not loaded");
    }
#endif
    _current();
    boom::glEvalCoord2fv(u);
}

void OpenGL::evalMesh1(boom::OpenGLEnum mode, boom::OpenGLInt i1, boom::OpenGLInt i2) const {
#ifndef NDEBUG
    if (boom::glEvalMesh1 == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalMesh1() failed: OpenGL function \"glEvalMesh1\" not loaded");
    }
#endif
    _current();
    boom::glEvalMesh1(mode, i1, i2);
}

void OpenGL::evalMesh2(boom::OpenGLEnum mode, boom::OpenGLInt i1, boom::OpenGLInt i2, boom::OpenGLInt j1, boom::OpenGLInt j2) const {
#ifndef NDEBUG
    if (boom::glEvalMesh2 == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalMesh2() failed: OpenGL function \"glEvalMesh2\" not loaded");
    }
#endif
    _current();
    boom::glEvalMesh2(mode, i1, i2, j1, j2);
}

void OpenGL::evalPoint1(boom::OpenGLInt i) const {
#ifndef NDEBUG
    if (boom::glEvalPoint1 == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalPoint1() failed: OpenGL function \"glEvalPoint1\" not loaded");
    }
#endif
    _current();
    boom::glEvalPoint1(i);
}

void OpenGL::evalPoint2(boom::OpenGLInt i, boom::OpenGLInt j) const {
#ifndef NDEBUG
    if (boom::glEvalPoint2 == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::evalPoint2() failed: OpenGL function \"glEvalPoint2\" not loaded");
    }
#endif
    _current();
    boom::glEvalPoint2(i, j);
}

void OpenGL::feedbackBuffer(boom::OpenGLSizei size, boom::OpenGLEnum type, boom::OpenGLFloat* buffer) const {
#ifndef NDEBUG
    if (boom::glFeedbackBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::feedbackBuffer() failed: OpenGL function \"glFeedbackBuffer\" not loaded");
    }
#endif
    _current();
    boom::glFeedbackBuffer(size, type, buffer);
}

boom::OpenGLSync OpenGL::fenceSync(boom::OpenGLEnum condition, boom::OpenGLBitfield flags) const {
#ifndef NDEBUG
    if (boom::glFenceSync == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fenceSync() failed: OpenGL function \"glFenceSync\" not loaded");
    }
#endif
    _current();
    return boom::glFenceSync(condition, flags);
}

void OpenGL::finish() const {
#ifndef NDEBUG
    if (boom::glFinish == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::finish() failed: OpenGL function \"glFinish\" not loaded");
    }
#endif
    _current();
    boom::glFinish();
}

void OpenGL::flush() const {
#ifndef NDEBUG
    if (boom::glFlush == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::flush() failed: OpenGL function \"glFlush\" not loaded");
    }
#endif
    _current();
    boom::glFlush();
}

void OpenGL::flushMappedBufferRange(boom::OpenGLEnum target, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr length) const {
#ifndef NDEBUG
    if (boom::glFlushMappedBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::flushMappedBufferRange() failed: OpenGL function \"glFlushMappedBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glFlushMappedBufferRange(target, offset, length);
}

void OpenGL::flushMappedNamedBufferRange(boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr length) const {
#ifndef NDEBUG
    if (boom::glFlushMappedNamedBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::flushMappedNamedBufferRange() failed: OpenGL function \"glFlushMappedNamedBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glFlushMappedNamedBufferRange(buffer, offset, length);
}

void OpenGL::fogCoordPointer(boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glFogCoordPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogCoordPointer() failed: OpenGL function \"glFogCoordPointer\" not loaded");
    }
#endif
    _current();
    boom::glFogCoordPointer(type, stride, pointer);
}

void OpenGL::fogCoordd(boom::OpenGLDouble coord) const {
#ifndef NDEBUG
    if (boom::glFogCoordd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogCoordd() failed: OpenGL function \"glFogCoordd\" not loaded");
    }
#endif
    _current();
    boom::glFogCoordd(coord);
}

void OpenGL::fogCoorddv(boom::OpenGLDouble const* coord) const {
#ifndef NDEBUG
    if (boom::glFogCoorddv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogCoorddv() failed: OpenGL function \"glFogCoorddv\" not loaded");
    }
#endif
    _current();
    boom::glFogCoorddv(coord);
}

void OpenGL::fogCoordf(boom::OpenGLFloat coord) const {
#ifndef NDEBUG
    if (boom::glFogCoordf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogCoordf() failed: OpenGL function \"glFogCoordf\" not loaded");
    }
#endif
    _current();
    boom::glFogCoordf(coord);
}

void OpenGL::fogCoordfv(boom::OpenGLFloat const* coord) const {
#ifndef NDEBUG
    if (boom::glFogCoordfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogCoordfv() failed: OpenGL function \"glFogCoordfv\" not loaded");
    }
#endif
    _current();
    boom::glFogCoordfv(coord);
}

void OpenGL::fogf(boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glFogf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogf() failed: OpenGL function \"glFogf\" not loaded");
    }
#endif
    _current();
    boom::glFogf(pname, param);
}

void OpenGL::fogfv(boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glFogfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogfv() failed: OpenGL function \"glFogfv\" not loaded");
    }
#endif
    _current();
    boom::glFogfv(pname, params);
}

void OpenGL::fogi(boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glFogi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogi() failed: OpenGL function \"glFogi\" not loaded");
    }
#endif
    _current();
    boom::glFogi(pname, param);
}

void OpenGL::fogiv(boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glFogiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogiv() failed: OpenGL function \"glFogiv\" not loaded");
    }
#endif
    _current();
    boom::glFogiv(pname, params);
}

void OpenGL::fogx(boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glFogx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogx() failed: OpenGL function \"glFogx\" not loaded");
    }
#endif
    _current();
    boom::glFogx(pname, param);
}

void OpenGL::fogxv(boom::OpenGLEnum pname, boom::OpenGLFixed const* param) const {
#ifndef NDEBUG
    if (boom::glFogxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::fogxv() failed: OpenGL function \"glFogxv\" not loaded");
    }
#endif
    _current();
    boom::glFogxv(pname, param);
}

void OpenGL::framebufferParameteri(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glFramebufferParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferParameteri() failed: OpenGL function \"glFramebufferParameteri\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferParameteri(target, pname, param);
}

void OpenGL::framebufferRenderbuffer(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLEnum renderbuffertarget, boom::OpenGLUint renderbuffer) const {
#ifndef NDEBUG
    if (boom::glFramebufferRenderbuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferRenderbuffer() failed: OpenGL function \"glFramebufferRenderbuffer\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void OpenGL::framebufferTexture(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLUint texture, boom::OpenGLInt level) const {
#ifndef NDEBUG
    if (boom::glFramebufferTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferTexture() failed: OpenGL function \"glFramebufferTexture\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferTexture(target, attachment, texture, level);
}

void OpenGL::framebufferTexture1D(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLEnum textarget, boom::OpenGLUint texture, boom::OpenGLInt level) const {
#ifndef NDEBUG
    if (boom::glFramebufferTexture1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferTexture1D() failed: OpenGL function \"glFramebufferTexture1D\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

void OpenGL::framebufferTexture2D(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLEnum textarget, boom::OpenGLUint texture, boom::OpenGLInt level) const {
#ifndef NDEBUG
    if (boom::glFramebufferTexture2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferTexture2D() failed: OpenGL function \"glFramebufferTexture2D\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void OpenGL::framebufferTexture3D(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLEnum textarget, boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt zoffset) const {
#ifndef NDEBUG
    if (boom::glFramebufferTexture3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferTexture3D() failed: OpenGL function \"glFramebufferTexture3D\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

void OpenGL::framebufferTextureLayer(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt layer) const {
#ifndef NDEBUG
    if (boom::glFramebufferTextureLayer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::framebufferTextureLayer() failed: OpenGL function \"glFramebufferTextureLayer\" not loaded");
    }
#endif
    _current();
    boom::glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

void OpenGL::frontFace(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glFrontFace == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::frontFace() failed: OpenGL function \"glFrontFace\" not loaded");
    }
#endif
    _current();
    boom::glFrontFace(mode);
}

void OpenGL::frustum(boom::OpenGLDouble left, boom::OpenGLDouble right, boom::OpenGLDouble bottom, boom::OpenGLDouble top, boom::OpenGLDouble zNear, boom::OpenGLDouble zFar) const {
#ifndef NDEBUG
    if (boom::glFrustum == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::frustum() failed: OpenGL function \"glFrustum\" not loaded");
    }
#endif
    _current();
    boom::glFrustum(left, right, bottom, top, zNear, zFar);
}

void OpenGL::frustumf(boom::OpenGLFloat l, boom::OpenGLFloat r, boom::OpenGLFloat b, boom::OpenGLFloat t, boom::OpenGLFloat n, boom::OpenGLFloat f) const {
#ifndef NDEBUG
    if (boom::glFrustumf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::frustumf() failed: OpenGL function \"glFrustumf\" not loaded");
    }
#endif
    _current();
    boom::glFrustumf(l, r, b, t, n, f);
}

void OpenGL::frustumx(boom::OpenGLFixed l, boom::OpenGLFixed r, boom::OpenGLFixed b, boom::OpenGLFixed t, boom::OpenGLFixed n, boom::OpenGLFixed f) const {
#ifndef NDEBUG
    if (boom::glFrustumx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::frustumx() failed: OpenGL function \"glFrustumx\" not loaded");
    }
#endif
    _current();
    boom::glFrustumx(l, r, b, t, n, f);
}

void OpenGL::genBuffers(boom::OpenGLSizei n, boom::OpenGLUint* buffers) const {
#ifndef NDEBUG
    if (boom::glGenBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genBuffers() failed: OpenGL function \"glGenBuffers\" not loaded");
    }
#endif
    _current();
    boom::glGenBuffers(n, buffers);
}

void OpenGL::genFramebuffers(boom::OpenGLSizei n, boom::OpenGLUint* framebuffers) const {
#ifndef NDEBUG
    if (boom::glGenFramebuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genFramebuffers() failed: OpenGL function \"glGenFramebuffers\" not loaded");
    }
#endif
    _current();
    boom::glGenFramebuffers(n, framebuffers);
}

boom::OpenGLUint OpenGL::genLists(boom::OpenGLSizei range) const {
#ifndef NDEBUG
    if (boom::glGenLists == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genLists() failed: OpenGL function \"glGenLists\" not loaded");
    }
#endif
    _current();
    return boom::glGenLists(range);
}

void OpenGL::genProgramPipelines(boom::OpenGLSizei n, boom::OpenGLUint* pipelines) const {
#ifndef NDEBUG
    if (boom::glGenProgramPipelines == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genProgramPipelines() failed: OpenGL function \"glGenProgramPipelines\" not loaded");
    }
#endif
    _current();
    boom::glGenProgramPipelines(n, pipelines);
}

void OpenGL::genQueries(boom::OpenGLSizei n, boom::OpenGLUint* ids) const {
#ifndef NDEBUG
    if (boom::glGenQueries == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genQueries() failed: OpenGL function \"glGenQueries\" not loaded");
    }
#endif
    _current();
    boom::glGenQueries(n, ids);
}

void OpenGL::genRenderbuffers(boom::OpenGLSizei n, boom::OpenGLUint* renderbuffers) const {
#ifndef NDEBUG
    if (boom::glGenRenderbuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genRenderbuffers() failed: OpenGL function \"glGenRenderbuffers\" not loaded");
    }
#endif
    _current();
    boom::glGenRenderbuffers(n, renderbuffers);
}

void OpenGL::genSamplers(boom::OpenGLSizei count, boom::OpenGLUint* samplers) const {
#ifndef NDEBUG
    if (boom::glGenSamplers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genSamplers() failed: OpenGL function \"glGenSamplers\" not loaded");
    }
#endif
    _current();
    boom::glGenSamplers(count, samplers);
}

void OpenGL::genTextures(boom::OpenGLSizei n, boom::OpenGLUint* textures) const {
#ifndef NDEBUG
    if (boom::glGenTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genTextures() failed: OpenGL function \"glGenTextures\" not loaded");
    }
#endif
    _current();
    boom::glGenTextures(n, textures);
}

void OpenGL::genTransformFeedbacks(boom::OpenGLSizei n, boom::OpenGLUint* ids) const {
#ifndef NDEBUG
    if (boom::glGenTransformFeedbacks == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genTransformFeedbacks() failed: OpenGL function \"glGenTransformFeedbacks\" not loaded");
    }
#endif
    _current();
    boom::glGenTransformFeedbacks(n, ids);
}

void OpenGL::genVertexArrays(boom::OpenGLSizei n, boom::OpenGLUint* arrays) const {
#ifndef NDEBUG
    if (boom::glGenVertexArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::genVertexArrays() failed: OpenGL function \"glGenVertexArrays\" not loaded");
    }
#endif
    _current();
    boom::glGenVertexArrays(n, arrays);
}

void OpenGL::generateMipmap(boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glGenerateMipmap == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::generateMipmap() failed: OpenGL function \"glGenerateMipmap\" not loaded");
    }
#endif
    _current();
    boom::glGenerateMipmap(target);
}

void OpenGL::generateTextureMipmap(boom::OpenGLUint texture) const {
#ifndef NDEBUG
    if (boom::glGenerateTextureMipmap == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::generateTextureMipmap() failed: OpenGL function \"glGenerateTextureMipmap\" not loaded");
    }
#endif
    _current();
    boom::glGenerateTextureMipmap(texture);
}

void OpenGL::getActiveAtomicCounterBufferiv(boom::OpenGLUint program, boom::OpenGLUint bufferIndex, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetActiveAtomicCounterBufferiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveAtomicCounterBufferiv() failed: OpenGL function \"glGetActiveAtomicCounterBufferiv\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
}

void OpenGL::getActiveAttrib(boom::OpenGLUint program, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLInt* size, boom::OpenGLEnum* type, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetActiveAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveAttrib() failed: OpenGL function \"glGetActiveAttrib\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

void OpenGL::getActiveSubroutineName(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetActiveSubroutineName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveSubroutineName() failed: OpenGL function \"glGetActiveSubroutineName\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveSubroutineName(program, shadertype, index, bufSize, length, name);
}

void OpenGL::getActiveSubroutineUniformName(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetActiveSubroutineUniformName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveSubroutineUniformName() failed: OpenGL function \"glGetActiveSubroutineUniformName\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveSubroutineUniformName(program, shadertype, index, bufSize, length, name);
}

void OpenGL::getActiveSubroutineUniformiv(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt* values) const {
#ifndef NDEBUG
    if (boom::glGetActiveSubroutineUniformiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveSubroutineUniformiv() failed: OpenGL function \"glGetActiveSubroutineUniformiv\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
}

void OpenGL::getActiveUniform(boom::OpenGLUint program, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLInt* size, boom::OpenGLEnum* type, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetActiveUniform == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveUniform() failed: OpenGL function \"glGetActiveUniform\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

void OpenGL::getActiveUniformBlockName(boom::OpenGLUint program, boom::OpenGLUint uniformBlockIndex, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* uniformBlockName) const {
#ifndef NDEBUG
    if (boom::glGetActiveUniformBlockName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveUniformBlockName() failed: OpenGL function \"glGetActiveUniformBlockName\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
}

void OpenGL::getActiveUniformBlockiv(boom::OpenGLUint program, boom::OpenGLUint uniformBlockIndex, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetActiveUniformBlockiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveUniformBlockiv() failed: OpenGL function \"glGetActiveUniformBlockiv\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
}

void OpenGL::getActiveUniformName(boom::OpenGLUint program, boom::OpenGLUint uniformIndex, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* uniformName) const {
#ifndef NDEBUG
    if (boom::glGetActiveUniformName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveUniformName() failed: OpenGL function \"glGetActiveUniformName\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
}

void OpenGL::getActiveUniformsiv(boom::OpenGLUint program, boom::OpenGLSizei uniformCount, boom::OpenGLUint const* uniformIndices, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetActiveUniformsiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getActiveUniformsiv() failed: OpenGL function \"glGetActiveUniformsiv\" not loaded");
    }
#endif
    _current();
    boom::glGetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
}

void OpenGL::getAttachedShaders(boom::OpenGLUint program, boom::OpenGLSizei maxCount, boom::OpenGLSizei* count, boom::OpenGLUint* shaders) const {
#ifndef NDEBUG
    if (boom::glGetAttachedShaders == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getAttachedShaders() failed: OpenGL function \"glGetAttachedShaders\" not loaded");
    }
#endif
    _current();
    boom::glGetAttachedShaders(program, maxCount, count, shaders);
}

boom::OpenGLInt OpenGL::getAttribLocation(boom::OpenGLUint program, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetAttribLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getAttribLocation() failed: OpenGL function \"glGetAttribLocation\" not loaded");
    }
#endif
    _current();
    return boom::glGetAttribLocation(program, name);
}

void OpenGL::getBooleani_v(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLBoolean* data) const {
#ifndef NDEBUG
    if (boom::glGetBooleani_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBooleani_v() failed: OpenGL function \"glGetBooleani_v\" not loaded");
    }
#endif
    _current();
    boom::glGetBooleani_v(target, index, data);
}

void OpenGL::getBooleanv(boom::OpenGLEnum pname, boom::OpenGLBoolean* data) const {
#ifndef NDEBUG
    if (boom::glGetBooleanv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBooleanv() failed: OpenGL function \"glGetBooleanv\" not loaded");
    }
#endif
    _current();
    boom::glGetBooleanv(pname, data);
}

void OpenGL::getBufferParameteri64v(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt64* params) const {
#ifndef NDEBUG
    if (boom::glGetBufferParameteri64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBufferParameteri64v() failed: OpenGL function \"glGetBufferParameteri64v\" not loaded");
    }
#endif
    _current();
    boom::glGetBufferParameteri64v(target, pname, params);
}

void OpenGL::getBufferParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetBufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBufferParameteriv() failed: OpenGL function \"glGetBufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetBufferParameteriv(target, pname, params);
}

void OpenGL::getBufferPointerv(boom::OpenGLEnum target, boom::OpenGLEnum pname, void** params) const {
#ifndef NDEBUG
    if (boom::glGetBufferPointerv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBufferPointerv() failed: OpenGL function \"glGetBufferPointerv\" not loaded");
    }
#endif
    _current();
    boom::glGetBufferPointerv(target, pname, params);
}

void OpenGL::getBufferSubData(boom::OpenGLEnum target, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, void* data) const {
#ifndef NDEBUG
    if (boom::glGetBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getBufferSubData() failed: OpenGL function \"glGetBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glGetBufferSubData(target, offset, size, data);
}

void OpenGL::getClipPlane(boom::OpenGLEnum plane, boom::OpenGLDouble* equation) const {
#ifndef NDEBUG
    if (boom::glGetClipPlane == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getClipPlane() failed: OpenGL function \"glGetClipPlane\" not loaded");
    }
#endif
    _current();
    boom::glGetClipPlane(plane, equation);
}

void OpenGL::getClipPlanef(boom::OpenGLEnum plane, boom::OpenGLFloat* equation) const {
#ifndef NDEBUG
    if (boom::glGetClipPlanef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getClipPlanef() failed: OpenGL function \"glGetClipPlanef\" not loaded");
    }
#endif
    _current();
    boom::glGetClipPlanef(plane, equation);
}

void OpenGL::getClipPlanex(boom::OpenGLEnum plane, boom::OpenGLFixed* equation) const {
#ifndef NDEBUG
    if (boom::glGetClipPlanex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getClipPlanex() failed: OpenGL function \"glGetClipPlanex\" not loaded");
    }
#endif
    _current();
    boom::glGetClipPlanex(plane, equation);
}

void OpenGL::getCompressedTexImage(boom::OpenGLEnum target, boom::OpenGLInt level, void* img) const {
#ifndef NDEBUG
    if (boom::glGetCompressedTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getCompressedTexImage() failed: OpenGL function \"glGetCompressedTexImage\" not loaded");
    }
#endif
    _current();
    boom::glGetCompressedTexImage(target, level, img);
}

void OpenGL::getCompressedTextureImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetCompressedTextureImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getCompressedTextureImage() failed: OpenGL function \"glGetCompressedTextureImage\" not loaded");
    }
#endif
    _current();
    boom::glGetCompressedTextureImage(texture, level, bufSize, pixels);
}

void OpenGL::getCompressedTextureSubImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetCompressedTextureSubImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getCompressedTextureSubImage() failed: OpenGL function \"glGetCompressedTextureSubImage\" not loaded");
    }
#endif
    _current();
    boom::glGetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
}

boom::OpenGLUint OpenGL::getDebugMessageLog(boom::OpenGLUint count, boom::OpenGLSizei bufSize, boom::OpenGLEnum* sources, boom::OpenGLEnum* types, boom::OpenGLUint* ids, boom::OpenGLEnum* severities, boom::OpenGLSizei* lengths, boom::OpenGLChar* messageLog) const {
#ifndef NDEBUG
    if (boom::glGetDebugMessageLog == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getDebugMessageLog() failed: OpenGL function \"glGetDebugMessageLog\" not loaded");
    }
#endif
    _current();
    return boom::glGetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
}

void OpenGL::getDoublei_v(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLDouble* data) const {
#ifndef NDEBUG
    if (boom::glGetDoublei_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getDoublei_v() failed: OpenGL function \"glGetDoublei_v\" not loaded");
    }
#endif
    _current();
    boom::glGetDoublei_v(target, index, data);
}

void OpenGL::getDoublev(boom::OpenGLEnum pname, boom::OpenGLDouble* data) const {
#ifndef NDEBUG
    if (boom::glGetDoublev == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getDoublev() failed: OpenGL function \"glGetDoublev\" not loaded");
    }
#endif
    _current();
    boom::glGetDoublev(pname, data);
}

boom::OpenGLEnum OpenGL::getError() const {
#ifndef NDEBUG
    if (boom::glGetError == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getError() failed: OpenGL function \"glGetError\" not loaded");
    }
#endif
    _current();
    return boom::glGetError();
}

void OpenGL::getFixedv(boom::OpenGLEnum pname, boom::OpenGLFixed* params) const {
#ifndef NDEBUG
    if (boom::glGetFixedv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFixedv() failed: OpenGL function \"glGetFixedv\" not loaded");
    }
#endif
    _current();
    boom::glGetFixedv(pname, params);
}

void OpenGL::getFloati_v(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLFloat* data) const {
#ifndef NDEBUG
    if (boom::glGetFloati_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFloati_v() failed: OpenGL function \"glGetFloati_v\" not loaded");
    }
#endif
    _current();
    boom::glGetFloati_v(target, index, data);
}

void OpenGL::getFloatv(boom::OpenGLEnum pname, boom::OpenGLFloat* data) const {
#ifndef NDEBUG
    if (boom::glGetFloatv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFloatv() failed: OpenGL function \"glGetFloatv\" not loaded");
    }
#endif
    _current();
    boom::glGetFloatv(pname, data);
}

boom::OpenGLInt OpenGL::getFragDataIndex(boom::OpenGLUint program, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetFragDataIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFragDataIndex() failed: OpenGL function \"glGetFragDataIndex\" not loaded");
    }
#endif
    _current();
    return boom::glGetFragDataIndex(program, name);
}

boom::OpenGLInt OpenGL::getFragDataLocation(boom::OpenGLUint program, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetFragDataLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFragDataLocation() failed: OpenGL function \"glGetFragDataLocation\" not loaded");
    }
#endif
    _current();
    return boom::glGetFragDataLocation(program, name);
}

void OpenGL::getFramebufferAttachmentParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum attachment, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetFramebufferAttachmentParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFramebufferAttachmentParameteriv() failed: OpenGL function \"glGetFramebufferAttachmentParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

void OpenGL::getFramebufferParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetFramebufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getFramebufferParameteriv() failed: OpenGL function \"glGetFramebufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetFramebufferParameteriv(target, pname, params);
}

boom::OpenGLEnum OpenGL::getGraphicsResetStatus() const {
#ifndef NDEBUG
    if (boom::glGetGraphicsResetStatus == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getGraphicsResetStatus() failed: OpenGL function \"glGetGraphicsResetStatus\" not loaded");
    }
#endif
    _current();
    return boom::glGetGraphicsResetStatus();
}

void OpenGL::getInteger64i_v(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLInt64* data) const {
#ifndef NDEBUG
    if (boom::glGetInteger64i_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getInteger64i_v() failed: OpenGL function \"glGetInteger64i_v\" not loaded");
    }
#endif
    _current();
    boom::glGetInteger64i_v(target, index, data);
}

void OpenGL::getInteger64v(boom::OpenGLEnum pname, boom::OpenGLInt64* data) const {
#ifndef NDEBUG
    if (boom::glGetInteger64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getInteger64v() failed: OpenGL function \"glGetInteger64v\" not loaded");
    }
#endif
    _current();
    boom::glGetInteger64v(pname, data);
}

void OpenGL::getIntegeri_v(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLInt* data) const {
#ifndef NDEBUG
    if (boom::glGetIntegeri_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getIntegeri_v() failed: OpenGL function \"glGetIntegeri_v\" not loaded");
    }
#endif
    _current();
    boom::glGetIntegeri_v(target, index, data);
}

void OpenGL::getIntegerv(boom::OpenGLEnum pname, boom::OpenGLInt* data) const {
#ifndef NDEBUG
    if (boom::glGetIntegerv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getIntegerv() failed: OpenGL function \"glGetIntegerv\" not loaded");
    }
#endif
    _current();
    boom::glGetIntegerv(pname, data);
}

void OpenGL::getInternalformati64v(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLEnum pname, boom::OpenGLSizei count, boom::OpenGLInt64* params) const {
#ifndef NDEBUG
    if (boom::glGetInternalformati64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getInternalformati64v() failed: OpenGL function \"glGetInternalformati64v\" not loaded");
    }
#endif
    _current();
    boom::glGetInternalformati64v(target, internalformat, pname, count, params);
}

void OpenGL::getInternalformativ(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLEnum pname, boom::OpenGLSizei count, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetInternalformativ == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getInternalformativ() failed: OpenGL function \"glGetInternalformativ\" not loaded");
    }
#endif
    _current();
    boom::glGetInternalformativ(target, internalformat, pname, count, params);
}

void OpenGL::getLightfv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetLightfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getLightfv() failed: OpenGL function \"glGetLightfv\" not loaded");
    }
#endif
    _current();
    boom::glGetLightfv(light, pname, params);
}

void OpenGL::getLightiv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetLightiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getLightiv() failed: OpenGL function \"glGetLightiv\" not loaded");
    }
#endif
    _current();
    boom::glGetLightiv(light, pname, params);
}

void OpenGL::getLightxv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFixed* params) const {
#ifndef NDEBUG
    if (boom::glGetLightxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getLightxv() failed: OpenGL function \"glGetLightxv\" not loaded");
    }
#endif
    _current();
    boom::glGetLightxv(light, pname, params);
}

void OpenGL::getMapdv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLDouble* v) const {
#ifndef NDEBUG
    if (boom::glGetMapdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMapdv() failed: OpenGL function \"glGetMapdv\" not loaded");
    }
#endif
    _current();
    boom::glGetMapdv(target, query, v);
}

void OpenGL::getMapfv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLFloat* v) const {
#ifndef NDEBUG
    if (boom::glGetMapfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMapfv() failed: OpenGL function \"glGetMapfv\" not loaded");
    }
#endif
    _current();
    boom::glGetMapfv(target, query, v);
}

void OpenGL::getMapiv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLInt* v) const {
#ifndef NDEBUG
    if (boom::glGetMapiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMapiv() failed: OpenGL function \"glGetMapiv\" not loaded");
    }
#endif
    _current();
    boom::glGetMapiv(target, query, v);
}

void OpenGL::getMaterialfv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetMaterialfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMaterialfv() failed: OpenGL function \"glGetMaterialfv\" not loaded");
    }
#endif
    _current();
    boom::glGetMaterialfv(face, pname, params);
}

void OpenGL::getMaterialiv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetMaterialiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMaterialiv() failed: OpenGL function \"glGetMaterialiv\" not loaded");
    }
#endif
    _current();
    boom::glGetMaterialiv(face, pname, params);
}

void OpenGL::getMaterialxv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFixed* params) const {
#ifndef NDEBUG
    if (boom::glGetMaterialxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMaterialxv() failed: OpenGL function \"glGetMaterialxv\" not loaded");
    }
#endif
    _current();
    boom::glGetMaterialxv(face, pname, params);
}

void OpenGL::getMultisamplefv(boom::OpenGLEnum pname, boom::OpenGLUint index, boom::OpenGLFloat* val) const {
#ifndef NDEBUG
    if (boom::glGetMultisamplefv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getMultisamplefv() failed: OpenGL function \"glGetMultisamplefv\" not loaded");
    }
#endif
    _current();
    boom::glGetMultisamplefv(pname, index, val);
}

void OpenGL::getNamedBufferParameteri64v(boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLInt64* params) const {
#ifndef NDEBUG
    if (boom::glGetNamedBufferParameteri64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedBufferParameteri64v() failed: OpenGL function \"glGetNamedBufferParameteri64v\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedBufferParameteri64v(buffer, pname, params);
}

void OpenGL::getNamedBufferParameteriv(boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetNamedBufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedBufferParameteriv() failed: OpenGL function \"glGetNamedBufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedBufferParameteriv(buffer, pname, params);
}

void OpenGL::getNamedBufferPointerv(boom::OpenGLUint buffer, boom::OpenGLEnum pname, void** params) const {
#ifndef NDEBUG
    if (boom::glGetNamedBufferPointerv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedBufferPointerv() failed: OpenGL function \"glGetNamedBufferPointerv\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedBufferPointerv(buffer, pname, params);
}

void OpenGL::getNamedBufferSubData(boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, void* data) const {
#ifndef NDEBUG
    if (boom::glGetNamedBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedBufferSubData() failed: OpenGL function \"glGetNamedBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedBufferSubData(buffer, offset, size, data);
}

void OpenGL::getNamedFramebufferAttachmentParameteriv(boom::OpenGLUint framebuffer, boom::OpenGLEnum attachment, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetNamedFramebufferAttachmentParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedFramebufferAttachmentParameteriv() failed: OpenGL function \"glGetNamedFramebufferAttachmentParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
}

void OpenGL::getNamedFramebufferParameteriv(boom::OpenGLUint framebuffer, boom::OpenGLEnum pname, boom::OpenGLInt* param) const {
#ifndef NDEBUG
    if (boom::glGetNamedFramebufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedFramebufferParameteriv() failed: OpenGL function \"glGetNamedFramebufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedFramebufferParameteriv(framebuffer, pname, param);
}

void OpenGL::getNamedRenderbufferParameteriv(boom::OpenGLUint renderbuffer, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetNamedRenderbufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getNamedRenderbufferParameteriv() failed: OpenGL function \"glGetNamedRenderbufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetNamedRenderbufferParameteriv(renderbuffer, pname, params);
}

void OpenGL::getObjectLabel(boom::OpenGLEnum identifier, boom::OpenGLUint name, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* label) const {
#ifndef NDEBUG
    if (boom::glGetObjectLabel == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getObjectLabel() failed: OpenGL function \"glGetObjectLabel\" not loaded");
    }
#endif
    _current();
    boom::glGetObjectLabel(identifier, name, bufSize, length, label);
}

void OpenGL::getObjectPtrLabel(void const* ptr, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* label) const {
#ifndef NDEBUG
    if (boom::glGetObjectPtrLabel == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getObjectPtrLabel() failed: OpenGL function \"glGetObjectPtrLabel\" not loaded");
    }
#endif
    _current();
    boom::glGetObjectPtrLabel(ptr, bufSize, length, label);
}

void OpenGL::getPixelMapfv(boom::OpenGLEnum map, boom::OpenGLFloat* values) const {
#ifndef NDEBUG
    if (boom::glGetPixelMapfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getPixelMapfv() failed: OpenGL function \"glGetPixelMapfv\" not loaded");
    }
#endif
    _current();
    boom::glGetPixelMapfv(map, values);
}

void OpenGL::getPixelMapuiv(boom::OpenGLEnum map, boom::OpenGLUint* values) const {
#ifndef NDEBUG
    if (boom::glGetPixelMapuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getPixelMapuiv() failed: OpenGL function \"glGetPixelMapuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetPixelMapuiv(map, values);
}

void OpenGL::getPixelMapusv(boom::OpenGLEnum map, boom::OpenGLUShort* values) const {
#ifndef NDEBUG
    if (boom::glGetPixelMapusv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getPixelMapusv() failed: OpenGL function \"glGetPixelMapusv\" not loaded");
    }
#endif
    _current();
    boom::glGetPixelMapusv(map, values);
}

void OpenGL::getPointerv(boom::OpenGLEnum pname, void** params) const {
#ifndef NDEBUG
    if (boom::glGetPointerv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getPointerv() failed: OpenGL function \"glGetPointerv\" not loaded");
    }
#endif
    _current();
    boom::glGetPointerv(pname, params);
}

void OpenGL::getPolygonStipple(boom::OpenGLUbyte* mask) const {
#ifndef NDEBUG
    if (boom::glGetPolygonStipple == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getPolygonStipple() failed: OpenGL function \"glGetPolygonStipple\" not loaded");
    }
#endif
    _current();
    boom::glGetPolygonStipple(mask);
}

void OpenGL::getProgramBinary(boom::OpenGLUint program, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLEnum* binaryFormat, void* binary) const {
#ifndef NDEBUG
    if (boom::glGetProgramBinary == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramBinary() failed: OpenGL function \"glGetProgramBinary\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramBinary(program, bufSize, length, binaryFormat, binary);
}

void OpenGL::getProgramInfoLog(boom::OpenGLUint program, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* infoLog) const {
#ifndef NDEBUG
    if (boom::glGetProgramInfoLog == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramInfoLog() failed: OpenGL function \"glGetProgramInfoLog\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void OpenGL::getProgramInterfaceiv(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetProgramInterfaceiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramInterfaceiv() failed: OpenGL function \"glGetProgramInterfaceiv\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramInterfaceiv(program, programInterface, pname, params);
}

void OpenGL::getProgramPipelineInfoLog(boom::OpenGLUint pipeline, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* infoLog) const {
#ifndef NDEBUG
    if (boom::glGetProgramPipelineInfoLog == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramPipelineInfoLog() failed: OpenGL function \"glGetProgramPipelineInfoLog\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
}

void OpenGL::getProgramPipelineiv(boom::OpenGLUint pipeline, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetProgramPipelineiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramPipelineiv() failed: OpenGL function \"glGetProgramPipelineiv\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramPipelineiv(pipeline, pname, params);
}

boom::OpenGLUint OpenGL::getProgramResourceIndex(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetProgramResourceIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramResourceIndex() failed: OpenGL function \"glGetProgramResourceIndex\" not loaded");
    }
#endif
    _current();
    return boom::glGetProgramResourceIndex(program, programInterface, name);
}

boom::OpenGLInt OpenGL::getProgramResourceLocation(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetProgramResourceLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramResourceLocation() failed: OpenGL function \"glGetProgramResourceLocation\" not loaded");
    }
#endif
    _current();
    return boom::glGetProgramResourceLocation(program, programInterface, name);
}

boom::OpenGLInt OpenGL::getProgramResourceLocationIndex(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetProgramResourceLocationIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramResourceLocationIndex() failed: OpenGL function \"glGetProgramResourceLocationIndex\" not loaded");
    }
#endif
    _current();
    return boom::glGetProgramResourceLocationIndex(program, programInterface, name);
}

void OpenGL::getProgramResourceName(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetProgramResourceName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramResourceName() failed: OpenGL function \"glGetProgramResourceName\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramResourceName(program, programInterface, index, bufSize, length, name);
}

void OpenGL::getProgramResourceiv(boom::OpenGLUint program, boom::OpenGLEnum programInterface, boom::OpenGLUint index, boom::OpenGLSizei propCount, boom::OpenGLEnum const* props, boom::OpenGLSizei count, boom::OpenGLSizei* length, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetProgramResourceiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramResourceiv() failed: OpenGL function \"glGetProgramResourceiv\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramResourceiv(program, programInterface, index, propCount, props, count, length, params);
}

void OpenGL::getProgramStageiv(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLEnum pname, boom::OpenGLInt* values) const {
#ifndef NDEBUG
    if (boom::glGetProgramStageiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramStageiv() failed: OpenGL function \"glGetProgramStageiv\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramStageiv(program, shadertype, pname, values);
}

void OpenGL::getProgramiv(boom::OpenGLUint program, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetProgramiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getProgramiv() failed: OpenGL function \"glGetProgramiv\" not loaded");
    }
#endif
    _current();
    boom::glGetProgramiv(program, pname, params);
}

void OpenGL::getQueryBufferObjecti64v(boom::OpenGLUint id, boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLIntptr offset) const {
#ifndef NDEBUG
    if (boom::glGetQueryBufferObjecti64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryBufferObjecti64v() failed: OpenGL function \"glGetQueryBufferObjecti64v\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryBufferObjecti64v(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectiv(boom::OpenGLUint id, boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLIntptr offset) const {
#ifndef NDEBUG
    if (boom::glGetQueryBufferObjectiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryBufferObjectiv() failed: OpenGL function \"glGetQueryBufferObjectiv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryBufferObjectiv(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectui64v(boom::OpenGLUint id, boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLIntptr offset) const {
#ifndef NDEBUG
    if (boom::glGetQueryBufferObjectui64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryBufferObjectui64v() failed: OpenGL function \"glGetQueryBufferObjectui64v\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryBufferObjectui64v(id, buffer, pname, offset);
}

void OpenGL::getQueryBufferObjectuiv(boom::OpenGLUint id, boom::OpenGLUint buffer, boom::OpenGLEnum pname, boom::OpenGLIntptr offset) const {
#ifndef NDEBUG
    if (boom::glGetQueryBufferObjectuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryBufferObjectuiv() failed: OpenGL function \"glGetQueryBufferObjectuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryBufferObjectuiv(id, buffer, pname, offset);
}

void OpenGL::getQueryIndexediv(boom::OpenGLEnum target, boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryIndexediv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryIndexediv() failed: OpenGL function \"glGetQueryIndexediv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryIndexediv(target, index, pname, params);
}

void OpenGL::getQueryObjecti64v(boom::OpenGLUint id, boom::OpenGLEnum pname, boom::OpenGLInt64* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryObjecti64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryObjecti64v() failed: OpenGL function \"glGetQueryObjecti64v\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryObjecti64v(id, pname, params);
}

void OpenGL::getQueryObjectiv(boom::OpenGLUint id, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryObjectiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryObjectiv() failed: OpenGL function \"glGetQueryObjectiv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryObjectiv(id, pname, params);
}

void OpenGL::getQueryObjectui64v(boom::OpenGLUint id, boom::OpenGLEnum pname, boom::OpenGLUInt64* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryObjectui64v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryObjectui64v() failed: OpenGL function \"glGetQueryObjectui64v\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryObjectui64v(id, pname, params);
}

void OpenGL::getQueryObjectuiv(boom::OpenGLUint id, boom::OpenGLEnum pname, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryObjectuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryObjectuiv() failed: OpenGL function \"glGetQueryObjectuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryObjectuiv(id, pname, params);
}

void OpenGL::getQueryiv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetQueryiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getQueryiv() failed: OpenGL function \"glGetQueryiv\" not loaded");
    }
#endif
    _current();
    boom::glGetQueryiv(target, pname, params);
}

void OpenGL::getRenderbufferParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetRenderbufferParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getRenderbufferParameteriv() failed: OpenGL function \"glGetRenderbufferParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetRenderbufferParameteriv(target, pname, params);
}

void OpenGL::getSamplerParameterIiv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetSamplerParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSamplerParameterIiv() failed: OpenGL function \"glGetSamplerParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glGetSamplerParameterIiv(sampler, pname, params);
}

void OpenGL::getSamplerParameterIuiv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetSamplerParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSamplerParameterIuiv() failed: OpenGL function \"glGetSamplerParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetSamplerParameterIuiv(sampler, pname, params);
}

void OpenGL::getSamplerParameterfv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetSamplerParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSamplerParameterfv() failed: OpenGL function \"glGetSamplerParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glGetSamplerParameterfv(sampler, pname, params);
}

void OpenGL::getSamplerParameteriv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetSamplerParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSamplerParameteriv() failed: OpenGL function \"glGetSamplerParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetSamplerParameteriv(sampler, pname, params);
}

void OpenGL::getShaderInfoLog(boom::OpenGLUint shader, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* infoLog) const {
#ifndef NDEBUG
    if (boom::glGetShaderInfoLog == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getShaderInfoLog() failed: OpenGL function \"glGetShaderInfoLog\" not loaded");
    }
#endif
    _current();
    boom::glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void OpenGL::getShaderPrecisionFormat(boom::OpenGLEnum shadertype, boom::OpenGLEnum precisiontype, boom::OpenGLInt* range, boom::OpenGLInt* precision) const {
#ifndef NDEBUG
    if (boom::glGetShaderPrecisionFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getShaderPrecisionFormat() failed: OpenGL function \"glGetShaderPrecisionFormat\" not loaded");
    }
#endif
    _current();
    boom::glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void OpenGL::getShaderSource(boom::OpenGLUint shader, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLChar* source) const {
#ifndef NDEBUG
    if (boom::glGetShaderSource == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getShaderSource() failed: OpenGL function \"glGetShaderSource\" not loaded");
    }
#endif
    _current();
    boom::glGetShaderSource(shader, bufSize, length, source);
}

void OpenGL::getShaderiv(boom::OpenGLUint shader, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetShaderiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getShaderiv() failed: OpenGL function \"glGetShaderiv\" not loaded");
    }
#endif
    _current();
    boom::glGetShaderiv(shader, pname, params);
}

boom::OpenGLUbyte const* OpenGL::getString(boom::OpenGLEnum name) const {
#ifndef NDEBUG
    if (boom::glGetString == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getString() failed: OpenGL function \"glGetString\" not loaded");
    }
#endif
    _current();
    return boom::glGetString(name);
}

boom::OpenGLUbyte const* OpenGL::getStringi(boom::OpenGLEnum name, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glGetStringi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getStringi() failed: OpenGL function \"glGetStringi\" not loaded");
    }
#endif
    _current();
    return boom::glGetStringi(name, index);
}

boom::OpenGLUint OpenGL::getSubroutineIndex(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetSubroutineIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSubroutineIndex() failed: OpenGL function \"glGetSubroutineIndex\" not loaded");
    }
#endif
    _current();
    return boom::glGetSubroutineIndex(program, shadertype, name);
}

boom::OpenGLInt OpenGL::getSubroutineUniformLocation(boom::OpenGLUint program, boom::OpenGLEnum shadertype, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetSubroutineUniformLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSubroutineUniformLocation() failed: OpenGL function \"glGetSubroutineUniformLocation\" not loaded");
    }
#endif
    _current();
    return boom::glGetSubroutineUniformLocation(program, shadertype, name);
}

void OpenGL::getSynciv(boom::OpenGLSync sync, boom::OpenGLEnum pname, boom::OpenGLSizei count, boom::OpenGLSizei* length, boom::OpenGLInt* values) const {
#ifndef NDEBUG
    if (boom::glGetSynciv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getSynciv() failed: OpenGL function \"glGetSynciv\" not loaded");
    }
#endif
    _current();
    boom::glGetSynciv(sync, pname, count, length, values);
}

void OpenGL::getTexEnvfv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTexEnvfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexEnvfv() failed: OpenGL function \"glGetTexEnvfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexEnvfv(target, pname, params);
}

void OpenGL::getTexEnviv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTexEnviv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexEnviv() failed: OpenGL function \"glGetTexEnviv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexEnviv(target, pname, params);
}

void OpenGL::getTexEnvxv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed* params) const {
#ifndef NDEBUG
    if (boom::glGetTexEnvxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexEnvxv() failed: OpenGL function \"glGetTexEnvxv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexEnvxv(target, pname, params);
}

void OpenGL::getTexGendv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLDouble* params) const {
#ifndef NDEBUG
    if (boom::glGetTexGendv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexGendv() failed: OpenGL function \"glGetTexGendv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexGendv(coord, pname, params);
}

void OpenGL::getTexGenfv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTexGenfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexGenfv() failed: OpenGL function \"glGetTexGenfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexGenfv(coord, pname, params);
}

void OpenGL::getTexGeniv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTexGeniv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexGeniv() failed: OpenGL function \"glGetTexGeniv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexGeniv(coord, pname, params);
}

void OpenGL::getTexImage(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum format, boom::OpenGLEnum type, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexImage() failed: OpenGL function \"glGetTexImage\" not loaded");
    }
#endif
    _current();
    boom::glGetTexImage(target, level, format, type, pixels);
}

void OpenGL::getTexLevelParameterfv(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTexLevelParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexLevelParameterfv() failed: OpenGL function \"glGetTexLevelParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexLevelParameterfv(target, level, pname, params);
}

void OpenGL::getTexLevelParameteriv(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTexLevelParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexLevelParameteriv() failed: OpenGL function \"glGetTexLevelParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexLevelParameteriv(target, level, pname, params);
}

void OpenGL::getTexParameterIiv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTexParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexParameterIiv() failed: OpenGL function \"glGetTexParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexParameterIiv(target, pname, params);
}

void OpenGL::getTexParameterIuiv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetTexParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexParameterIuiv() failed: OpenGL function \"glGetTexParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexParameterIuiv(target, pname, params);
}

void OpenGL::getTexParameterfv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTexParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexParameterfv() failed: OpenGL function \"glGetTexParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexParameterfv(target, pname, params);
}

void OpenGL::getTexParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTexParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexParameteriv() failed: OpenGL function \"glGetTexParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexParameteriv(target, pname, params);
}

void OpenGL::getTexParameterxv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed* params) const {
#ifndef NDEBUG
    if (boom::glGetTexParameterxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTexParameterxv() failed: OpenGL function \"glGetTexParameterxv\" not loaded");
    }
#endif
    _current();
    boom::glGetTexParameterxv(target, pname, params);
}

void OpenGL::getTextureImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetTextureImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureImage() failed: OpenGL function \"glGetTextureImage\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureImage(texture, level, format, type, bufSize, pixels);
}

void OpenGL::getTextureLevelParameterfv(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureLevelParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureLevelParameterfv() failed: OpenGL function \"glGetTextureLevelParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureLevelParameterfv(texture, level, pname, params);
}

void OpenGL::getTextureLevelParameteriv(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureLevelParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureLevelParameteriv() failed: OpenGL function \"glGetTextureLevelParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureLevelParameteriv(texture, level, pname, params);
}

void OpenGL::getTextureParameterIiv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureParameterIiv() failed: OpenGL function \"glGetTextureParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureParameterIiv(texture, pname, params);
}

void OpenGL::getTextureParameterIuiv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureParameterIuiv() failed: OpenGL function \"glGetTextureParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureParameterIuiv(texture, pname, params);
}

void OpenGL::getTextureParameterfv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureParameterfv() failed: OpenGL function \"glGetTextureParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureParameterfv(texture, pname, params);
}

void OpenGL::getTextureParameteriv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetTextureParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureParameteriv() failed: OpenGL function \"glGetTextureParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureParameteriv(texture, pname, params);
}

void OpenGL::getTextureSubImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetTextureSubImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTextureSubImage() failed: OpenGL function \"glGetTextureSubImage\" not loaded");
    }
#endif
    _current();
    boom::glGetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
}

void OpenGL::getTransformFeedbackVarying(boom::OpenGLUint program, boom::OpenGLUint index, boom::OpenGLSizei bufSize, boom::OpenGLSizei* length, boom::OpenGLSizei* size, boom::OpenGLEnum* type, boom::OpenGLChar* name) const {
#ifndef NDEBUG
    if (boom::glGetTransformFeedbackVarying == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTransformFeedbackVarying() failed: OpenGL function \"glGetTransformFeedbackVarying\" not loaded");
    }
#endif
    _current();
    boom::glGetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
}

void OpenGL::getTransformFeedbacki64_v(boom::OpenGLUint xfb, boom::OpenGLEnum pname, boom::OpenGLUint index, boom::OpenGLInt64* param) const {
#ifndef NDEBUG
    if (boom::glGetTransformFeedbacki64_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTransformFeedbacki64_v() failed: OpenGL function \"glGetTransformFeedbacki64_v\" not loaded");
    }
#endif
    _current();
    boom::glGetTransformFeedbacki64_v(xfb, pname, index, param);
}

void OpenGL::getTransformFeedbacki_v(boom::OpenGLUint xfb, boom::OpenGLEnum pname, boom::OpenGLUint index, boom::OpenGLInt* param) const {
#ifndef NDEBUG
    if (boom::glGetTransformFeedbacki_v == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTransformFeedbacki_v() failed: OpenGL function \"glGetTransformFeedbacki_v\" not loaded");
    }
#endif
    _current();
    boom::glGetTransformFeedbacki_v(xfb, pname, index, param);
}

void OpenGL::getTransformFeedbackiv(boom::OpenGLUint xfb, boom::OpenGLEnum pname, boom::OpenGLInt* param) const {
#ifndef NDEBUG
    if (boom::glGetTransformFeedbackiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getTransformFeedbackiv() failed: OpenGL function \"glGetTransformFeedbackiv\" not loaded");
    }
#endif
    _current();
    boom::glGetTransformFeedbackiv(xfb, pname, param);
}

boom::OpenGLUint OpenGL::getUniformBlockIndex(boom::OpenGLUint program, boom::OpenGLChar const* uniformBlockName) const {
#ifndef NDEBUG
    if (boom::glGetUniformBlockIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformBlockIndex() failed: OpenGL function \"glGetUniformBlockIndex\" not loaded");
    }
#endif
    _current();
    return boom::glGetUniformBlockIndex(program, uniformBlockName);
}

void OpenGL::getUniformIndices(boom::OpenGLUint program, boom::OpenGLSizei uniformCount, boom::OpenGLChar const* const* uniformNames, boom::OpenGLUint* uniformIndices) const {
#ifndef NDEBUG
    if (boom::glGetUniformIndices == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformIndices() failed: OpenGL function \"glGetUniformIndices\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
}

boom::OpenGLInt OpenGL::getUniformLocation(boom::OpenGLUint program, boom::OpenGLChar const* name) const {
#ifndef NDEBUG
    if (boom::glGetUniformLocation == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformLocation() failed: OpenGL function \"glGetUniformLocation\" not loaded");
    }
#endif
    _current();
    return boom::glGetUniformLocation(program, name);
}

void OpenGL::getUniformSubroutineuiv(boom::OpenGLEnum shadertype, boom::OpenGLInt location, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetUniformSubroutineuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformSubroutineuiv() failed: OpenGL function \"glGetUniformSubroutineuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformSubroutineuiv(shadertype, location, params);
}

void OpenGL::getUniformdv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLDouble* params) const {
#ifndef NDEBUG
    if (boom::glGetUniformdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformdv() failed: OpenGL function \"glGetUniformdv\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformdv(program, location, params);
}

void OpenGL::getUniformfv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetUniformfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformfv() failed: OpenGL function \"glGetUniformfv\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformfv(program, location, params);
}

void OpenGL::getUniformiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetUniformiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformiv() failed: OpenGL function \"glGetUniformiv\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformiv(program, location, params);
}

void OpenGL::getUniformuiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetUniformuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getUniformuiv() failed: OpenGL function \"glGetUniformuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetUniformuiv(program, location, params);
}

void OpenGL::getVertexArrayIndexed64iv(boom::OpenGLUint vaobj, boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt64* param) const {
#ifndef NDEBUG
    if (boom::glGetVertexArrayIndexed64iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexArrayIndexed64iv() failed: OpenGL function \"glGetVertexArrayIndexed64iv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexArrayIndexed64iv(vaobj, index, pname, param);
}

void OpenGL::getVertexArrayIndexediv(boom::OpenGLUint vaobj, boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt* param) const {
#ifndef NDEBUG
    if (boom::glGetVertexArrayIndexediv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexArrayIndexediv() failed: OpenGL function \"glGetVertexArrayIndexediv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexArrayIndexediv(vaobj, index, pname, param);
}

void OpenGL::getVertexArrayiv(boom::OpenGLUint vaobj, boom::OpenGLEnum pname, boom::OpenGLInt* param) const {
#ifndef NDEBUG
    if (boom::glGetVertexArrayiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexArrayiv() failed: OpenGL function \"glGetVertexArrayiv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexArrayiv(vaobj, pname, param);
}

void OpenGL::getVertexAttribIiv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribIiv() failed: OpenGL function \"glGetVertexAttribIiv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribIiv(index, pname, params);
}

void OpenGL::getVertexAttribIuiv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribIuiv() failed: OpenGL function \"glGetVertexAttribIuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribIuiv(index, pname, params);
}

void OpenGL::getVertexAttribLdv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLDouble* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribLdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribLdv() failed: OpenGL function \"glGetVertexAttribLdv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribLdv(index, pname, params);
}

void OpenGL::getVertexAttribPointerv(boom::OpenGLUint index, boom::OpenGLEnum pname, void** pointer) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribPointerv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribPointerv() failed: OpenGL function \"glGetVertexAttribPointerv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribPointerv(index, pname, pointer);
}

void OpenGL::getVertexAttribdv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLDouble* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribdv() failed: OpenGL function \"glGetVertexAttribdv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribdv(index, pname, params);
}

void OpenGL::getVertexAttribfv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribfv() failed: OpenGL function \"glGetVertexAttribfv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribfv(index, pname, params);
}

void OpenGL::getVertexAttribiv(boom::OpenGLUint index, boom::OpenGLEnum pname, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetVertexAttribiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getVertexAttribiv() failed: OpenGL function \"glGetVertexAttribiv\" not loaded");
    }
#endif
    _current();
    boom::glGetVertexAttribiv(index, pname, params);
}

void OpenGL::getnColorTable(boom::OpenGLEnum target, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* table) const {
#ifndef NDEBUG
    if (boom::glGetnColorTable == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnColorTable() failed: OpenGL function \"glGetnColorTable\" not loaded");
    }
#endif
    _current();
    boom::glGetnColorTable(target, format, type, bufSize, table);
}

void OpenGL::getnCompressedTexImage(boom::OpenGLEnum target, boom::OpenGLInt lod, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetnCompressedTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnCompressedTexImage() failed: OpenGL function \"glGetnCompressedTexImage\" not loaded");
    }
#endif
    _current();
    boom::glGetnCompressedTexImage(target, lod, bufSize, pixels);
}

void OpenGL::getnConvolutionFilter(boom::OpenGLEnum target, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* image) const {
#ifndef NDEBUG
    if (boom::glGetnConvolutionFilter == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnConvolutionFilter() failed: OpenGL function \"glGetnConvolutionFilter\" not loaded");
    }
#endif
    _current();
    boom::glGetnConvolutionFilter(target, format, type, bufSize, image);
}

void OpenGL::getnHistogram(boom::OpenGLEnum target, boom::OpenGLBoolean reset, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* values) const {
#ifndef NDEBUG
    if (boom::glGetnHistogram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnHistogram() failed: OpenGL function \"glGetnHistogram\" not loaded");
    }
#endif
    _current();
    boom::glGetnHistogram(target, reset, format, type, bufSize, values);
}

void OpenGL::getnMapdv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLSizei bufSize, boom::OpenGLDouble* v) const {
#ifndef NDEBUG
    if (boom::glGetnMapdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnMapdv() failed: OpenGL function \"glGetnMapdv\" not loaded");
    }
#endif
    _current();
    boom::glGetnMapdv(target, query, bufSize, v);
}

void OpenGL::getnMapfv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLSizei bufSize, boom::OpenGLFloat* v) const {
#ifndef NDEBUG
    if (boom::glGetnMapfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnMapfv() failed: OpenGL function \"glGetnMapfv\" not loaded");
    }
#endif
    _current();
    boom::glGetnMapfv(target, query, bufSize, v);
}

void OpenGL::getnMapiv(boom::OpenGLEnum target, boom::OpenGLEnum query, boom::OpenGLSizei bufSize, boom::OpenGLInt* v) const {
#ifndef NDEBUG
    if (boom::glGetnMapiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnMapiv() failed: OpenGL function \"glGetnMapiv\" not loaded");
    }
#endif
    _current();
    boom::glGetnMapiv(target, query, bufSize, v);
}

void OpenGL::getnMinmax(boom::OpenGLEnum target, boom::OpenGLBoolean reset, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* values) const {
#ifndef NDEBUG
    if (boom::glGetnMinmax == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnMinmax() failed: OpenGL function \"glGetnMinmax\" not loaded");
    }
#endif
    _current();
    boom::glGetnMinmax(target, reset, format, type, bufSize, values);
}

void OpenGL::getnPixelMapfv(boom::OpenGLEnum map, boom::OpenGLSizei bufSize, boom::OpenGLFloat* values) const {
#ifndef NDEBUG
    if (boom::glGetnPixelMapfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnPixelMapfv() failed: OpenGL function \"glGetnPixelMapfv\" not loaded");
    }
#endif
    _current();
    boom::glGetnPixelMapfv(map, bufSize, values);
}

void OpenGL::getnPixelMapuiv(boom::OpenGLEnum map, boom::OpenGLSizei bufSize, boom::OpenGLUint* values) const {
#ifndef NDEBUG
    if (boom::glGetnPixelMapuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnPixelMapuiv() failed: OpenGL function \"glGetnPixelMapuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetnPixelMapuiv(map, bufSize, values);
}

void OpenGL::getnPixelMapusv(boom::OpenGLEnum map, boom::OpenGLSizei bufSize, boom::OpenGLUShort* values) const {
#ifndef NDEBUG
    if (boom::glGetnPixelMapusv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnPixelMapusv() failed: OpenGL function \"glGetnPixelMapusv\" not loaded");
    }
#endif
    _current();
    boom::glGetnPixelMapusv(map, bufSize, values);
}

void OpenGL::getnPolygonStipple(boom::OpenGLSizei bufSize, boom::OpenGLUbyte* pattern) const {
#ifndef NDEBUG
    if (boom::glGetnPolygonStipple == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnPolygonStipple() failed: OpenGL function \"glGetnPolygonStipple\" not loaded");
    }
#endif
    _current();
    boom::glGetnPolygonStipple(bufSize, pattern);
}

void OpenGL::getnSeparableFilter(boom::OpenGLEnum target, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei rowBufSize, void* row, boom::OpenGLSizei columnBufSize, void* column, void* span) const {
#ifndef NDEBUG
    if (boom::glGetnSeparableFilter == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnSeparableFilter() failed: OpenGL function \"glGetnSeparableFilter\" not loaded");
    }
#endif
    _current();
    boom::glGetnSeparableFilter(target, format, type, rowBufSize, row, columnBufSize, column, span);
}

void OpenGL::getnTexImage(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* pixels) const {
#ifndef NDEBUG
    if (boom::glGetnTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnTexImage() failed: OpenGL function \"glGetnTexImage\" not loaded");
    }
#endif
    _current();
    boom::glGetnTexImage(target, level, format, type, bufSize, pixels);
}

void OpenGL::getnUniformdv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei bufSize, boom::OpenGLDouble* params) const {
#ifndef NDEBUG
    if (boom::glGetnUniformdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnUniformdv() failed: OpenGL function \"glGetnUniformdv\" not loaded");
    }
#endif
    _current();
    boom::glGetnUniformdv(program, location, bufSize, params);
}

void OpenGL::getnUniformfv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei bufSize, boom::OpenGLFloat* params) const {
#ifndef NDEBUG
    if (boom::glGetnUniformfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnUniformfv() failed: OpenGL function \"glGetnUniformfv\" not loaded");
    }
#endif
    _current();
    boom::glGetnUniformfv(program, location, bufSize, params);
}

void OpenGL::getnUniformiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei bufSize, boom::OpenGLInt* params) const {
#ifndef NDEBUG
    if (boom::glGetnUniformiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnUniformiv() failed: OpenGL function \"glGetnUniformiv\" not loaded");
    }
#endif
    _current();
    boom::glGetnUniformiv(program, location, bufSize, params);
}

void OpenGL::getnUniformuiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei bufSize, boom::OpenGLUint* params) const {
#ifndef NDEBUG
    if (boom::glGetnUniformuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::getnUniformuiv() failed: OpenGL function \"glGetnUniformuiv\" not loaded");
    }
#endif
    _current();
    boom::glGetnUniformuiv(program, location, bufSize, params);
}

void OpenGL::hint(boom::OpenGLEnum target, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glHint == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::hint() failed: OpenGL function \"glHint\" not loaded");
    }
#endif
    _current();
    boom::glHint(target, mode);
}

void OpenGL::indexMask(boom::OpenGLUint mask) const {
#ifndef NDEBUG
    if (boom::glIndexMask == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexMask() failed: OpenGL function \"glIndexMask\" not loaded");
    }
#endif
    _current();
    boom::glIndexMask(mask);
}

void OpenGL::indexPointer(boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glIndexPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexPointer() failed: OpenGL function \"glIndexPointer\" not loaded");
    }
#endif
    _current();
    boom::glIndexPointer(type, stride, pointer);
}

void OpenGL::indexd(boom::OpenGLDouble c) const {
#ifndef NDEBUG
    if (boom::glIndexd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexd() failed: OpenGL function \"glIndexd\" not loaded");
    }
#endif
    _current();
    boom::glIndexd(c);
}

void OpenGL::indexdv(boom::OpenGLDouble const* c) const {
#ifndef NDEBUG
    if (boom::glIndexdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexdv() failed: OpenGL function \"glIndexdv\" not loaded");
    }
#endif
    _current();
    boom::glIndexdv(c);
}

void OpenGL::indexf(boom::OpenGLFloat c) const {
#ifndef NDEBUG
    if (boom::glIndexf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexf() failed: OpenGL function \"glIndexf\" not loaded");
    }
#endif
    _current();
    boom::glIndexf(c);
}

void OpenGL::indexfv(boom::OpenGLFloat const* c) const {
#ifndef NDEBUG
    if (boom::glIndexfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexfv() failed: OpenGL function \"glIndexfv\" not loaded");
    }
#endif
    _current();
    boom::glIndexfv(c);
}

void OpenGL::indexi(boom::OpenGLInt c) const {
#ifndef NDEBUG
    if (boom::glIndexi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexi() failed: OpenGL function \"glIndexi\" not loaded");
    }
#endif
    _current();
    boom::glIndexi(c);
}

void OpenGL::indexiv(boom::OpenGLInt const* c) const {
#ifndef NDEBUG
    if (boom::glIndexiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexiv() failed: OpenGL function \"glIndexiv\" not loaded");
    }
#endif
    _current();
    boom::glIndexiv(c);
}

void OpenGL::indexs(boom::OpenGLShort c) const {
#ifndef NDEBUG
    if (boom::glIndexs == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexs() failed: OpenGL function \"glIndexs\" not loaded");
    }
#endif
    _current();
    boom::glIndexs(c);
}

void OpenGL::indexsv(boom::OpenGLShort const* c) const {
#ifndef NDEBUG
    if (boom::glIndexsv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexsv() failed: OpenGL function \"glIndexsv\" not loaded");
    }
#endif
    _current();
    boom::glIndexsv(c);
}

void OpenGL::indexub(boom::OpenGLUbyte c) const {
#ifndef NDEBUG
    if (boom::glIndexub == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexub() failed: OpenGL function \"glIndexub\" not loaded");
    }
#endif
    _current();
    boom::glIndexub(c);
}

void OpenGL::indexubv(boom::OpenGLUbyte const* c) const {
#ifndef NDEBUG
    if (boom::glIndexubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::indexubv() failed: OpenGL function \"glIndexubv\" not loaded");
    }
#endif
    _current();
    boom::glIndexubv(c);
}

void OpenGL::initNames() const {
#ifndef NDEBUG
    if (boom::glInitNames == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::initNames() failed: OpenGL function \"glInitNames\" not loaded");
    }
#endif
    _current();
    boom::glInitNames();
}

void OpenGL::interleavedArrays(boom::OpenGLEnum format, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glInterleavedArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::interleavedArrays() failed: OpenGL function \"glInterleavedArrays\" not loaded");
    }
#endif
    _current();
    boom::glInterleavedArrays(format, stride, pointer);
}

void OpenGL::invalidateBufferData(boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glInvalidateBufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateBufferData() failed: OpenGL function \"glInvalidateBufferData\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateBufferData(buffer);
}

void OpenGL::invalidateBufferSubData(boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr length) const {
#ifndef NDEBUG
    if (boom::glInvalidateBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateBufferSubData() failed: OpenGL function \"glInvalidateBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateBufferSubData(buffer, offset, length);
}

void OpenGL::invalidateFramebuffer(boom::OpenGLEnum target, boom::OpenGLSizei numAttachments, boom::OpenGLEnum const* attachments) const {
#ifndef NDEBUG
    if (boom::glInvalidateFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateFramebuffer() failed: OpenGL function \"glInvalidateFramebuffer\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateFramebuffer(target, numAttachments, attachments);
}

void OpenGL::invalidateNamedFramebufferData(boom::OpenGLUint framebuffer, boom::OpenGLSizei numAttachments, boom::OpenGLEnum const* attachments) const {
#ifndef NDEBUG
    if (boom::glInvalidateNamedFramebufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateNamedFramebufferData() failed: OpenGL function \"glInvalidateNamedFramebufferData\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
}

void OpenGL::invalidateNamedFramebufferSubData(boom::OpenGLUint framebuffer, boom::OpenGLSizei numAttachments, boom::OpenGLEnum const* attachments, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glInvalidateNamedFramebufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateNamedFramebufferSubData() failed: OpenGL function \"glInvalidateNamedFramebufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
}

void OpenGL::invalidateSubFramebuffer(boom::OpenGLEnum target, boom::OpenGLSizei numAttachments, boom::OpenGLEnum const* attachments, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glInvalidateSubFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateSubFramebuffer() failed: OpenGL function \"glInvalidateSubFramebuffer\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
}

void OpenGL::invalidateTexImage(boom::OpenGLUint texture, boom::OpenGLInt level) const {
#ifndef NDEBUG
    if (boom::glInvalidateTexImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateTexImage() failed: OpenGL function \"glInvalidateTexImage\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateTexImage(texture, level);
}

void OpenGL::invalidateTexSubImage(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth) const {
#ifndef NDEBUG
    if (boom::glInvalidateTexSubImage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::invalidateTexSubImage() failed: OpenGL function \"glInvalidateTexSubImage\" not loaded");
    }
#endif
    _current();
    boom::glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

boom::OpenGLBoolean OpenGL::isBuffer(boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glIsBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isBuffer() failed: OpenGL function \"glIsBuffer\" not loaded");
    }
#endif
    _current();
    return boom::glIsBuffer(buffer);
}

boom::OpenGLBoolean OpenGL::isEnabled(boom::OpenGLEnum cap) const {
#ifndef NDEBUG
    if (boom::glIsEnabled == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isEnabled() failed: OpenGL function \"glIsEnabled\" not loaded");
    }
#endif
    _current();
    return boom::glIsEnabled(cap);
}

boom::OpenGLBoolean OpenGL::isEnabledi(boom::OpenGLEnum target, boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glIsEnabledi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isEnabledi() failed: OpenGL function \"glIsEnabledi\" not loaded");
    }
#endif
    _current();
    return boom::glIsEnabledi(target, index);
}

boom::OpenGLBoolean OpenGL::isFramebuffer(boom::OpenGLUint framebuffer) const {
#ifndef NDEBUG
    if (boom::glIsFramebuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isFramebuffer() failed: OpenGL function \"glIsFramebuffer\" not loaded");
    }
#endif
    _current();
    return boom::glIsFramebuffer(framebuffer);
}

boom::OpenGLBoolean OpenGL::isList(boom::OpenGLUint list) const {
#ifndef NDEBUG
    if (boom::glIsList == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isList() failed: OpenGL function \"glIsList\" not loaded");
    }
#endif
    _current();
    return boom::glIsList(list);
}

boom::OpenGLBoolean OpenGL::isProgram(boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glIsProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isProgram() failed: OpenGL function \"glIsProgram\" not loaded");
    }
#endif
    _current();
    return boom::glIsProgram(program);
}

boom::OpenGLBoolean OpenGL::isProgramPipeline(boom::OpenGLUint pipeline) const {
#ifndef NDEBUG
    if (boom::glIsProgramPipeline == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isProgramPipeline() failed: OpenGL function \"glIsProgramPipeline\" not loaded");
    }
#endif
    _current();
    return boom::glIsProgramPipeline(pipeline);
}

boom::OpenGLBoolean OpenGL::isQuery(boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glIsQuery == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isQuery() failed: OpenGL function \"glIsQuery\" not loaded");
    }
#endif
    _current();
    return boom::glIsQuery(id);
}

boom::OpenGLBoolean OpenGL::isRenderbuffer(boom::OpenGLUint renderbuffer) const {
#ifndef NDEBUG
    if (boom::glIsRenderbuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isRenderbuffer() failed: OpenGL function \"glIsRenderbuffer\" not loaded");
    }
#endif
    _current();
    return boom::glIsRenderbuffer(renderbuffer);
}

boom::OpenGLBoolean OpenGL::isSampler(boom::OpenGLUint sampler) const {
#ifndef NDEBUG
    if (boom::glIsSampler == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isSampler() failed: OpenGL function \"glIsSampler\" not loaded");
    }
#endif
    _current();
    return boom::glIsSampler(sampler);
}

boom::OpenGLBoolean OpenGL::isShader(boom::OpenGLUint shader) const {
#ifndef NDEBUG
    if (boom::glIsShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isShader() failed: OpenGL function \"glIsShader\" not loaded");
    }
#endif
    _current();
    return boom::glIsShader(shader);
}

boom::OpenGLBoolean OpenGL::isSync(boom::OpenGLSync sync) const {
#ifndef NDEBUG
    if (boom::glIsSync == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isSync() failed: OpenGL function \"glIsSync\" not loaded");
    }
#endif
    _current();
    return boom::glIsSync(sync);
}

boom::OpenGLBoolean OpenGL::isTexture(boom::OpenGLUint texture) const {
#ifndef NDEBUG
    if (boom::glIsTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isTexture() failed: OpenGL function \"glIsTexture\" not loaded");
    }
#endif
    _current();
    return boom::glIsTexture(texture);
}

boom::OpenGLBoolean OpenGL::isTransformFeedback(boom::OpenGLUint id) const {
#ifndef NDEBUG
    if (boom::glIsTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isTransformFeedback() failed: OpenGL function \"glIsTransformFeedback\" not loaded");
    }
#endif
    _current();
    return boom::glIsTransformFeedback(id);
}

boom::OpenGLBoolean OpenGL::isVertexArray(boom::OpenGLUint array) const {
#ifndef NDEBUG
    if (boom::glIsVertexArray == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::isVertexArray() failed: OpenGL function \"glIsVertexArray\" not loaded");
    }
#endif
    _current();
    return boom::glIsVertexArray(array);
}

void OpenGL::lightModelf(boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glLightModelf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModelf() failed: OpenGL function \"glLightModelf\" not loaded");
    }
#endif
    _current();
    boom::glLightModelf(pname, param);
}

void OpenGL::lightModelfv(boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glLightModelfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModelfv() failed: OpenGL function \"glLightModelfv\" not loaded");
    }
#endif
    _current();
    boom::glLightModelfv(pname, params);
}

void OpenGL::lightModeli(boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glLightModeli == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModeli() failed: OpenGL function \"glLightModeli\" not loaded");
    }
#endif
    _current();
    boom::glLightModeli(pname, param);
}

void OpenGL::lightModeliv(boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glLightModeliv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModeliv() failed: OpenGL function \"glLightModeliv\" not loaded");
    }
#endif
    _current();
    boom::glLightModeliv(pname, params);
}

void OpenGL::lightModelx(boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glLightModelx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModelx() failed: OpenGL function \"glLightModelx\" not loaded");
    }
#endif
    _current();
    boom::glLightModelx(pname, param);
}

void OpenGL::lightModelxv(boom::OpenGLEnum pname, boom::OpenGLFixed const* param) const {
#ifndef NDEBUG
    if (boom::glLightModelxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightModelxv() failed: OpenGL function \"glLightModelxv\" not loaded");
    }
#endif
    _current();
    boom::glLightModelxv(pname, param);
}

void OpenGL::lightf(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glLightf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightf() failed: OpenGL function \"glLightf\" not loaded");
    }
#endif
    _current();
    boom::glLightf(light, pname, param);
}

void OpenGL::lightfv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glLightfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightfv() failed: OpenGL function \"glLightfv\" not loaded");
    }
#endif
    _current();
    boom::glLightfv(light, pname, params);
}

void OpenGL::lighti(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glLighti == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lighti() failed: OpenGL function \"glLighti\" not loaded");
    }
#endif
    _current();
    boom::glLighti(light, pname, param);
}

void OpenGL::lightiv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glLightiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightiv() failed: OpenGL function \"glLightiv\" not loaded");
    }
#endif
    _current();
    boom::glLightiv(light, pname, params);
}

void OpenGL::lightx(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glLightx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightx() failed: OpenGL function \"glLightx\" not loaded");
    }
#endif
    _current();
    boom::glLightx(light, pname, param);
}

void OpenGL::lightxv(boom::OpenGLEnum light, boom::OpenGLEnum pname, boom::OpenGLFixed const* params) const {
#ifndef NDEBUG
    if (boom::glLightxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lightxv() failed: OpenGL function \"glLightxv\" not loaded");
    }
#endif
    _current();
    boom::glLightxv(light, pname, params);
}

void OpenGL::lineStipple(boom::OpenGLInt factor, boom::OpenGLUShort pattern) const {
#ifndef NDEBUG
    if (boom::glLineStipple == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lineStipple() failed: OpenGL function \"glLineStipple\" not loaded");
    }
#endif
    _current();
    boom::glLineStipple(factor, pattern);
}

void OpenGL::lineWidth(boom::OpenGLFloat width) const {
#ifndef NDEBUG
    if (boom::glLineWidth == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lineWidth() failed: OpenGL function \"glLineWidth\" not loaded");
    }
#endif
    _current();
    boom::glLineWidth(width);
}

void OpenGL::lineWidthx(boom::OpenGLFixed width) const {
#ifndef NDEBUG
    if (boom::glLineWidthx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::lineWidthx() failed: OpenGL function \"glLineWidthx\" not loaded");
    }
#endif
    _current();
    boom::glLineWidthx(width);
}

void OpenGL::linkProgram(boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glLinkProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::linkProgram() failed: OpenGL function \"glLinkProgram\" not loaded");
    }
#endif
    _current();
    boom::glLinkProgram(program);
}

void OpenGL::listBase(boom::OpenGLUint base) const {
#ifndef NDEBUG
    if (boom::glListBase == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::listBase() failed: OpenGL function \"glListBase\" not loaded");
    }
#endif
    _current();
    boom::glListBase(base);
}

void OpenGL::loadIdentity() const {
#ifndef NDEBUG
    if (boom::glLoadIdentity == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadIdentity() failed: OpenGL function \"glLoadIdentity\" not loaded");
    }
#endif
    _current();
    boom::glLoadIdentity();
}

void OpenGL::loadMatrixd(boom::OpenGLDouble const* m) const {
#ifndef NDEBUG
    if (boom::glLoadMatrixd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadMatrixd() failed: OpenGL function \"glLoadMatrixd\" not loaded");
    }
#endif
    _current();
    boom::glLoadMatrixd(m);
}

void OpenGL::loadMatrixf(boom::OpenGLFloat const* m) const {
#ifndef NDEBUG
    if (boom::glLoadMatrixf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadMatrixf() failed: OpenGL function \"glLoadMatrixf\" not loaded");
    }
#endif
    _current();
    boom::glLoadMatrixf(m);
}

void OpenGL::loadMatrixx(boom::OpenGLFixed const* m) const {
#ifndef NDEBUG
    if (boom::glLoadMatrixx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadMatrixx() failed: OpenGL function \"glLoadMatrixx\" not loaded");
    }
#endif
    _current();
    boom::glLoadMatrixx(m);
}

void OpenGL::loadName(boom::OpenGLUint name) const {
#ifndef NDEBUG
    if (boom::glLoadName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadName() failed: OpenGL function \"glLoadName\" not loaded");
    }
#endif
    _current();
    boom::glLoadName(name);
}

void OpenGL::loadTransposeMatrixd(boom::OpenGLDouble const* m) const {
#ifndef NDEBUG
    if (boom::glLoadTransposeMatrixd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadTransposeMatrixd() failed: OpenGL function \"glLoadTransposeMatrixd\" not loaded");
    }
#endif
    _current();
    boom::glLoadTransposeMatrixd(m);
}

void OpenGL::loadTransposeMatrixf(boom::OpenGLFloat const* m) const {
#ifndef NDEBUG
    if (boom::glLoadTransposeMatrixf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::loadTransposeMatrixf() failed: OpenGL function \"glLoadTransposeMatrixf\" not loaded");
    }
#endif
    _current();
    boom::glLoadTransposeMatrixf(m);
}

void OpenGL::logicOp(boom::OpenGLEnum opcode) const {
#ifndef NDEBUG
    if (boom::glLogicOp == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::logicOp() failed: OpenGL function \"glLogicOp\" not loaded");
    }
#endif
    _current();
    boom::glLogicOp(opcode);
}

void OpenGL::map1d(boom::OpenGLEnum target, boom::OpenGLDouble u1, boom::OpenGLDouble u2, boom::OpenGLInt stride, boom::OpenGLInt order, boom::OpenGLDouble const* points) const {
#ifndef NDEBUG
    if (boom::glMap1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::map1d() failed: OpenGL function \"glMap1d\" not loaded");
    }
#endif
    _current();
    boom::glMap1d(target, u1, u2, stride, order, points);
}

void OpenGL::map1f(boom::OpenGLEnum target, boom::OpenGLFloat u1, boom::OpenGLFloat u2, boom::OpenGLInt stride, boom::OpenGLInt order, boom::OpenGLFloat const* points) const {
#ifndef NDEBUG
    if (boom::glMap1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::map1f() failed: OpenGL function \"glMap1f\" not loaded");
    }
#endif
    _current();
    boom::glMap1f(target, u1, u2, stride, order, points);
}

void OpenGL::map2d(boom::OpenGLEnum target, boom::OpenGLDouble u1, boom::OpenGLDouble u2, boom::OpenGLInt ustride, boom::OpenGLInt uorder, boom::OpenGLDouble v1, boom::OpenGLDouble v2, boom::OpenGLInt vstride, boom::OpenGLInt vorder, boom::OpenGLDouble const* points) const {
#ifndef NDEBUG
    if (boom::glMap2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::map2d() failed: OpenGL function \"glMap2d\" not loaded");
    }
#endif
    _current();
    boom::glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void OpenGL::map2f(boom::OpenGLEnum target, boom::OpenGLFloat u1, boom::OpenGLFloat u2, boom::OpenGLInt ustride, boom::OpenGLInt uorder, boom::OpenGLFloat v1, boom::OpenGLFloat v2, boom::OpenGLInt vstride, boom::OpenGLInt vorder, boom::OpenGLFloat const* points) const {
#ifndef NDEBUG
    if (boom::glMap2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::map2f() failed: OpenGL function \"glMap2f\" not loaded");
    }
#endif
    _current();
    boom::glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

void* OpenGL::mapBuffer(boom::OpenGLEnum target, boom::OpenGLEnum access) const {
#ifndef NDEBUG
    if (boom::glMapBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapBuffer() failed: OpenGL function \"glMapBuffer\" not loaded");
    }
#endif
    _current();
    return boom::glMapBuffer(target, access);
}

void* OpenGL::mapBufferRange(boom::OpenGLEnum target, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr length, boom::OpenGLBitfield access) const {
#ifndef NDEBUG
    if (boom::glMapBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapBufferRange() failed: OpenGL function \"glMapBufferRange\" not loaded");
    }
#endif
    _current();
    return boom::glMapBufferRange(target, offset, length, access);
}

void OpenGL::mapGrid1d(boom::OpenGLInt un, boom::OpenGLDouble u1, boom::OpenGLDouble u2) const {
#ifndef NDEBUG
    if (boom::glMapGrid1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapGrid1d() failed: OpenGL function \"glMapGrid1d\" not loaded");
    }
#endif
    _current();
    boom::glMapGrid1d(un, u1, u2);
}

void OpenGL::mapGrid1f(boom::OpenGLInt un, boom::OpenGLFloat u1, boom::OpenGLFloat u2) const {
#ifndef NDEBUG
    if (boom::glMapGrid1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapGrid1f() failed: OpenGL function \"glMapGrid1f\" not loaded");
    }
#endif
    _current();
    boom::glMapGrid1f(un, u1, u2);
}

void OpenGL::mapGrid2d(boom::OpenGLInt un, boom::OpenGLDouble u1, boom::OpenGLDouble u2, boom::OpenGLInt vn, boom::OpenGLDouble v1, boom::OpenGLDouble v2) const {
#ifndef NDEBUG
    if (boom::glMapGrid2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapGrid2d() failed: OpenGL function \"glMapGrid2d\" not loaded");
    }
#endif
    _current();
    boom::glMapGrid2d(un, u1, u2, vn, v1, v2);
}

void OpenGL::mapGrid2f(boom::OpenGLInt un, boom::OpenGLFloat u1, boom::OpenGLFloat u2, boom::OpenGLInt vn, boom::OpenGLFloat v1, boom::OpenGLFloat v2) const {
#ifndef NDEBUG
    if (boom::glMapGrid2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapGrid2f() failed: OpenGL function \"glMapGrid2f\" not loaded");
    }
#endif
    _current();
    boom::glMapGrid2f(un, u1, u2, vn, v1, v2);
}

void* OpenGL::mapNamedBuffer(boom::OpenGLUint buffer, boom::OpenGLEnum access) const {
#ifndef NDEBUG
    if (boom::glMapNamedBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapNamedBuffer() failed: OpenGL function \"glMapNamedBuffer\" not loaded");
    }
#endif
    _current();
    return boom::glMapNamedBuffer(buffer, access);
}

void* OpenGL::mapNamedBufferRange(boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr length, boom::OpenGLBitfield access) const {
#ifndef NDEBUG
    if (boom::glMapNamedBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::mapNamedBufferRange() failed: OpenGL function \"glMapNamedBufferRange\" not loaded");
    }
#endif
    _current();
    return boom::glMapNamedBufferRange(buffer, offset, length, access);
}

void OpenGL::materialf(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glMaterialf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materialf() failed: OpenGL function \"glMaterialf\" not loaded");
    }
#endif
    _current();
    boom::glMaterialf(face, pname, param);
}

void OpenGL::materialfv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glMaterialfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materialfv() failed: OpenGL function \"glMaterialfv\" not loaded");
    }
#endif
    _current();
    boom::glMaterialfv(face, pname, params);
}

void OpenGL::materiali(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glMateriali == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materiali() failed: OpenGL function \"glMateriali\" not loaded");
    }
#endif
    _current();
    boom::glMateriali(face, pname, param);
}

void OpenGL::materialiv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glMaterialiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materialiv() failed: OpenGL function \"glMaterialiv\" not loaded");
    }
#endif
    _current();
    boom::glMaterialiv(face, pname, params);
}

void OpenGL::materialx(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glMaterialx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materialx() failed: OpenGL function \"glMaterialx\" not loaded");
    }
#endif
    _current();
    boom::glMaterialx(face, pname, param);
}

void OpenGL::materialxv(boom::OpenGLEnum face, boom::OpenGLEnum pname, boom::OpenGLFixed const* param) const {
#ifndef NDEBUG
    if (boom::glMaterialxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::materialxv() failed: OpenGL function \"glMaterialxv\" not loaded");
    }
#endif
    _current();
    boom::glMaterialxv(face, pname, param);
}

void OpenGL::matrixMode(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glMatrixMode == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::matrixMode() failed: OpenGL function \"glMatrixMode\" not loaded");
    }
#endif
    _current();
    boom::glMatrixMode(mode);
}

void OpenGL::memoryBarrier(boom::OpenGLBitfield barriers) const {
#ifndef NDEBUG
    if (boom::glMemoryBarrier == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::memoryBarrier() failed: OpenGL function \"glMemoryBarrier\" not loaded");
    }
#endif
    _current();
    boom::glMemoryBarrier(barriers);
}

void OpenGL::memoryBarrierByRegion(boom::OpenGLBitfield barriers) const {
#ifndef NDEBUG
    if (boom::glMemoryBarrierByRegion == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::memoryBarrierByRegion() failed: OpenGL function \"glMemoryBarrierByRegion\" not loaded");
    }
#endif
    _current();
    boom::glMemoryBarrierByRegion(barriers);
}

void OpenGL::minSampleShading(boom::OpenGLFloat value) const {
#ifndef NDEBUG
    if (boom::glMinSampleShading == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::minSampleShading() failed: OpenGL function \"glMinSampleShading\" not loaded");
    }
#endif
    _current();
    boom::glMinSampleShading(value);
}

void OpenGL::multMatrixd(boom::OpenGLDouble const* m) const {
#ifndef NDEBUG
    if (boom::glMultMatrixd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multMatrixd() failed: OpenGL function \"glMultMatrixd\" not loaded");
    }
#endif
    _current();
    boom::glMultMatrixd(m);
}

void OpenGL::multMatrixf(boom::OpenGLFloat const* m) const {
#ifndef NDEBUG
    if (boom::glMultMatrixf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multMatrixf() failed: OpenGL function \"glMultMatrixf\" not loaded");
    }
#endif
    _current();
    boom::glMultMatrixf(m);
}

void OpenGL::multMatrixx(boom::OpenGLFixed const* m) const {
#ifndef NDEBUG
    if (boom::glMultMatrixx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multMatrixx() failed: OpenGL function \"glMultMatrixx\" not loaded");
    }
#endif
    _current();
    boom::glMultMatrixx(m);
}

void OpenGL::multTransposeMatrixd(boom::OpenGLDouble const* m) const {
#ifndef NDEBUG
    if (boom::glMultTransposeMatrixd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multTransposeMatrixd() failed: OpenGL function \"glMultTransposeMatrixd\" not loaded");
    }
#endif
    _current();
    boom::glMultTransposeMatrixd(m);
}

void OpenGL::multTransposeMatrixf(boom::OpenGLFloat const* m) const {
#ifndef NDEBUG
    if (boom::glMultTransposeMatrixf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multTransposeMatrixf() failed: OpenGL function \"glMultTransposeMatrixf\" not loaded");
    }
#endif
    _current();
    boom::glMultTransposeMatrixf(m);
}

void OpenGL::multiDrawArrays(boom::OpenGLEnum mode, boom::OpenGLInt const* first, boom::OpenGLSizei const* count, boom::OpenGLSizei drawcount) const {
#ifndef NDEBUG
    if (boom::glMultiDrawArrays == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawArrays() failed: OpenGL function \"glMultiDrawArrays\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawArrays(mode, first, count, drawcount);
}

void OpenGL::multiDrawArraysIndirect(boom::OpenGLEnum mode, void const* indirect, boom::OpenGLSizei drawcount, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glMultiDrawArraysIndirect == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawArraysIndirect() failed: OpenGL function \"glMultiDrawArraysIndirect\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawArraysIndirect(mode, indirect, drawcount, stride);
}

void OpenGL::multiDrawArraysIndirectCount(boom::OpenGLEnum mode, void const* indirect, boom::OpenGLIntptr drawcount, boom::OpenGLSizei maxdrawcount, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glMultiDrawArraysIndirectCount == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawArraysIndirectCount() failed: OpenGL function \"glMultiDrawArraysIndirectCount\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawArraysIndirectCount(mode, indirect, drawcount, maxdrawcount, stride);
}

void OpenGL::multiDrawElements(boom::OpenGLEnum mode, boom::OpenGLSizei const* count, boom::OpenGLEnum type, void const* const* indices, boom::OpenGLSizei drawcount) const {
#ifndef NDEBUG
    if (boom::glMultiDrawElements == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawElements() failed: OpenGL function \"glMultiDrawElements\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawElements(mode, count, type, indices, drawcount);
}

void OpenGL::multiDrawElementsBaseVertex(boom::OpenGLEnum mode, boom::OpenGLSizei const* count, boom::OpenGLEnum type, void const* const* indices, boom::OpenGLSizei drawcount, boom::OpenGLInt const* basevertex) const {
#ifndef NDEBUG
    if (boom::glMultiDrawElementsBaseVertex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawElementsBaseVertex() failed: OpenGL function \"glMultiDrawElementsBaseVertex\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
}

void OpenGL::multiDrawElementsIndirect(boom::OpenGLEnum mode, boom::OpenGLEnum type, void const* indirect, boom::OpenGLSizei drawcount, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glMultiDrawElementsIndirect == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawElementsIndirect() failed: OpenGL function \"glMultiDrawElementsIndirect\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
}

void OpenGL::multiDrawElementsIndirectCount(boom::OpenGLEnum mode, boom::OpenGLEnum type, void const* indirect, boom::OpenGLIntptr drawcount, boom::OpenGLSizei maxdrawcount, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glMultiDrawElementsIndirectCount == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiDrawElementsIndirectCount() failed: OpenGL function \"glMultiDrawElementsIndirectCount\" not loaded");
    }
#endif
    _current();
    boom::glMultiDrawElementsIndirectCount(mode, type, indirect, drawcount, maxdrawcount, stride);
}

void OpenGL::multiTexCoord1d(boom::OpenGLEnum target, boom::OpenGLDouble s) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1d() failed: OpenGL function \"glMultiTexCoord1d\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1d(target, s);
}

void OpenGL::multiTexCoord1dv(boom::OpenGLEnum target, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1dv() failed: OpenGL function \"glMultiTexCoord1dv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1dv(target, v);
}

void OpenGL::multiTexCoord1f(boom::OpenGLEnum target, boom::OpenGLFloat s) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1f() failed: OpenGL function \"glMultiTexCoord1f\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1f(target, s);
}

void OpenGL::multiTexCoord1fv(boom::OpenGLEnum target, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1fv() failed: OpenGL function \"glMultiTexCoord1fv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1fv(target, v);
}

void OpenGL::multiTexCoord1i(boom::OpenGLEnum target, boom::OpenGLInt s) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1i() failed: OpenGL function \"glMultiTexCoord1i\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1i(target, s);
}

void OpenGL::multiTexCoord1iv(boom::OpenGLEnum target, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1iv() failed: OpenGL function \"glMultiTexCoord1iv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1iv(target, v);
}

void OpenGL::multiTexCoord1s(boom::OpenGLEnum target, boom::OpenGLShort s) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1s() failed: OpenGL function \"glMultiTexCoord1s\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1s(target, s);
}

void OpenGL::multiTexCoord1sv(boom::OpenGLEnum target, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord1sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord1sv() failed: OpenGL function \"glMultiTexCoord1sv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord1sv(target, v);
}

void OpenGL::multiTexCoord2d(boom::OpenGLEnum target, boom::OpenGLDouble s, boom::OpenGLDouble t) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2d() failed: OpenGL function \"glMultiTexCoord2d\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2d(target, s, t);
}

void OpenGL::multiTexCoord2dv(boom::OpenGLEnum target, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2dv() failed: OpenGL function \"glMultiTexCoord2dv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2dv(target, v);
}

void OpenGL::multiTexCoord2f(boom::OpenGLEnum target, boom::OpenGLFloat s, boom::OpenGLFloat t) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2f() failed: OpenGL function \"glMultiTexCoord2f\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2f(target, s, t);
}

void OpenGL::multiTexCoord2fv(boom::OpenGLEnum target, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2fv() failed: OpenGL function \"glMultiTexCoord2fv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2fv(target, v);
}

void OpenGL::multiTexCoord2i(boom::OpenGLEnum target, boom::OpenGLInt s, boom::OpenGLInt t) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2i() failed: OpenGL function \"glMultiTexCoord2i\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2i(target, s, t);
}

void OpenGL::multiTexCoord2iv(boom::OpenGLEnum target, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2iv() failed: OpenGL function \"glMultiTexCoord2iv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2iv(target, v);
}

void OpenGL::multiTexCoord2s(boom::OpenGLEnum target, boom::OpenGLShort s, boom::OpenGLShort t) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2s() failed: OpenGL function \"glMultiTexCoord2s\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2s(target, s, t);
}

void OpenGL::multiTexCoord2sv(boom::OpenGLEnum target, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord2sv() failed: OpenGL function \"glMultiTexCoord2sv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord2sv(target, v);
}

void OpenGL::multiTexCoord3d(boom::OpenGLEnum target, boom::OpenGLDouble s, boom::OpenGLDouble t, boom::OpenGLDouble r) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3d() failed: OpenGL function \"glMultiTexCoord3d\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3d(target, s, t, r);
}

void OpenGL::multiTexCoord3dv(boom::OpenGLEnum target, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3dv() failed: OpenGL function \"glMultiTexCoord3dv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3dv(target, v);
}

void OpenGL::multiTexCoord3f(boom::OpenGLEnum target, boom::OpenGLFloat s, boom::OpenGLFloat t, boom::OpenGLFloat r) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3f() failed: OpenGL function \"glMultiTexCoord3f\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3f(target, s, t, r);
}

void OpenGL::multiTexCoord3fv(boom::OpenGLEnum target, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3fv() failed: OpenGL function \"glMultiTexCoord3fv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3fv(target, v);
}

void OpenGL::multiTexCoord3i(boom::OpenGLEnum target, boom::OpenGLInt s, boom::OpenGLInt t, boom::OpenGLInt r) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3i() failed: OpenGL function \"glMultiTexCoord3i\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3i(target, s, t, r);
}

void OpenGL::multiTexCoord3iv(boom::OpenGLEnum target, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3iv() failed: OpenGL function \"glMultiTexCoord3iv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3iv(target, v);
}

void OpenGL::multiTexCoord3s(boom::OpenGLEnum target, boom::OpenGLShort s, boom::OpenGLShort t, boom::OpenGLShort r) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3s() failed: OpenGL function \"glMultiTexCoord3s\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3s(target, s, t, r);
}

void OpenGL::multiTexCoord3sv(boom::OpenGLEnum target, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord3sv() failed: OpenGL function \"glMultiTexCoord3sv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord3sv(target, v);
}

void OpenGL::multiTexCoord4d(boom::OpenGLEnum target, boom::OpenGLDouble s, boom::OpenGLDouble t, boom::OpenGLDouble r, boom::OpenGLDouble q) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4d() failed: OpenGL function \"glMultiTexCoord4d\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4d(target, s, t, r, q);
}

void OpenGL::multiTexCoord4dv(boom::OpenGLEnum target, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4dv() failed: OpenGL function \"glMultiTexCoord4dv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4dv(target, v);
}

void OpenGL::multiTexCoord4f(boom::OpenGLEnum target, boom::OpenGLFloat s, boom::OpenGLFloat t, boom::OpenGLFloat r, boom::OpenGLFloat q) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4f() failed: OpenGL function \"glMultiTexCoord4f\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4f(target, s, t, r, q);
}

void OpenGL::multiTexCoord4fv(boom::OpenGLEnum target, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4fv() failed: OpenGL function \"glMultiTexCoord4fv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4fv(target, v);
}

void OpenGL::multiTexCoord4i(boom::OpenGLEnum target, boom::OpenGLInt s, boom::OpenGLInt t, boom::OpenGLInt r, boom::OpenGLInt q) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4i() failed: OpenGL function \"glMultiTexCoord4i\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4i(target, s, t, r, q);
}

void OpenGL::multiTexCoord4iv(boom::OpenGLEnum target, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4iv() failed: OpenGL function \"glMultiTexCoord4iv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4iv(target, v);
}

void OpenGL::multiTexCoord4s(boom::OpenGLEnum target, boom::OpenGLShort s, boom::OpenGLShort t, boom::OpenGLShort r, boom::OpenGLShort q) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4s() failed: OpenGL function \"glMultiTexCoord4s\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4s(target, s, t, r, q);
}

void OpenGL::multiTexCoord4sv(boom::OpenGLEnum target, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4sv() failed: OpenGL function \"glMultiTexCoord4sv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4sv(target, v);
}

void OpenGL::multiTexCoord4x(boom::OpenGLEnum texture, boom::OpenGLFixed s, boom::OpenGLFixed t, boom::OpenGLFixed r, boom::OpenGLFixed q) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoord4x == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoord4x() failed: OpenGL function \"glMultiTexCoord4x\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoord4x(texture, s, t, r, q);
}

void OpenGL::multiTexCoordP1ui(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP1ui() failed: OpenGL function \"glMultiTexCoordP1ui\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP1ui(texture, type, coords);
}

void OpenGL::multiTexCoordP1uiv(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP1uiv() failed: OpenGL function \"glMultiTexCoordP1uiv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP1uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP2ui(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP2ui() failed: OpenGL function \"glMultiTexCoordP2ui\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP2ui(texture, type, coords);
}

void OpenGL::multiTexCoordP2uiv(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP2uiv() failed: OpenGL function \"glMultiTexCoordP2uiv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP2uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP3ui(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP3ui() failed: OpenGL function \"glMultiTexCoordP3ui\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP3ui(texture, type, coords);
}

void OpenGL::multiTexCoordP3uiv(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP3uiv() failed: OpenGL function \"glMultiTexCoordP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP3uiv(texture, type, coords);
}

void OpenGL::multiTexCoordP4ui(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP4ui() failed: OpenGL function \"glMultiTexCoordP4ui\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP4ui(texture, type, coords);
}

void OpenGL::multiTexCoordP4uiv(boom::OpenGLEnum texture, boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glMultiTexCoordP4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::multiTexCoordP4uiv() failed: OpenGL function \"glMultiTexCoordP4uiv\" not loaded");
    }
#endif
    _current();
    boom::glMultiTexCoordP4uiv(texture, type, coords);
}

void OpenGL::namedBufferData(boom::OpenGLUint buffer, boom::OpenGLSizeiptr size, void const* data, boom::OpenGLEnum usage) const {
#ifndef NDEBUG
    if (boom::glNamedBufferData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedBufferData() failed: OpenGL function \"glNamedBufferData\" not loaded");
    }
#endif
    _current();
    boom::glNamedBufferData(buffer, size, data, usage);
}

void OpenGL::namedBufferStorage(boom::OpenGLUint buffer, boom::OpenGLSizeiptr size, void const* data, boom::OpenGLBitfield flags) const {
#ifndef NDEBUG
    if (boom::glNamedBufferStorage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedBufferStorage() failed: OpenGL function \"glNamedBufferStorage\" not loaded");
    }
#endif
    _current();
    boom::glNamedBufferStorage(buffer, size, data, flags);
}

void OpenGL::namedBufferSubData(boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size, void const* data) const {
#ifndef NDEBUG
    if (boom::glNamedBufferSubData == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedBufferSubData() failed: OpenGL function \"glNamedBufferSubData\" not loaded");
    }
#endif
    _current();
    boom::glNamedBufferSubData(buffer, offset, size, data);
}

void OpenGL::namedFramebufferDrawBuffer(boom::OpenGLUint framebuffer, boom::OpenGLEnum buf) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferDrawBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferDrawBuffer() failed: OpenGL function \"glNamedFramebufferDrawBuffer\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferDrawBuffer(framebuffer, buf);
}

void OpenGL::namedFramebufferDrawBuffers(boom::OpenGLUint framebuffer, boom::OpenGLSizei n, boom::OpenGLEnum const* bufs) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferDrawBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferDrawBuffers() failed: OpenGL function \"glNamedFramebufferDrawBuffers\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

void OpenGL::namedFramebufferParameteri(boom::OpenGLUint framebuffer, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferParameteri() failed: OpenGL function \"glNamedFramebufferParameteri\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferParameteri(framebuffer, pname, param);
}

void OpenGL::namedFramebufferReadBuffer(boom::OpenGLUint framebuffer, boom::OpenGLEnum src) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferReadBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferReadBuffer() failed: OpenGL function \"glNamedFramebufferReadBuffer\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferReadBuffer(framebuffer, src);
}

void OpenGL::namedFramebufferRenderbuffer(boom::OpenGLUint framebuffer, boom::OpenGLEnum attachment, boom::OpenGLEnum renderbuffertarget, boom::OpenGLUint renderbuffer) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferRenderbuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferRenderbuffer() failed: OpenGL function \"glNamedFramebufferRenderbuffer\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

void OpenGL::namedFramebufferTexture(boom::OpenGLUint framebuffer, boom::OpenGLEnum attachment, boom::OpenGLUint texture, boom::OpenGLInt level) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferTexture == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferTexture() failed: OpenGL function \"glNamedFramebufferTexture\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferTexture(framebuffer, attachment, texture, level);
}

void OpenGL::namedFramebufferTextureLayer(boom::OpenGLUint framebuffer, boom::OpenGLEnum attachment, boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt layer) const {
#ifndef NDEBUG
    if (boom::glNamedFramebufferTextureLayer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedFramebufferTextureLayer() failed: OpenGL function \"glNamedFramebufferTextureLayer\" not loaded");
    }
#endif
    _current();
    boom::glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
}

void OpenGL::namedRenderbufferStorage(boom::OpenGLUint renderbuffer, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glNamedRenderbufferStorage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedRenderbufferStorage() failed: OpenGL function \"glNamedRenderbufferStorage\" not loaded");
    }
#endif
    _current();
    boom::glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
}

void OpenGL::namedRenderbufferStorageMultisample(boom::OpenGLUint renderbuffer, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glNamedRenderbufferStorageMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::namedRenderbufferStorageMultisample() failed: OpenGL function \"glNamedRenderbufferStorageMultisample\" not loaded");
    }
#endif
    _current();
    boom::glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
}

void OpenGL::newList(boom::OpenGLUint list, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glNewList == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::newList() failed: OpenGL function \"glNewList\" not loaded");
    }
#endif
    _current();
    boom::glNewList(list, mode);
}

void OpenGL::normal3b(boom::OpenGLByte nx, boom::OpenGLByte ny, boom::OpenGLByte nz) const {
#ifndef NDEBUG
    if (boom::glNormal3b == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3b() failed: OpenGL function \"glNormal3b\" not loaded");
    }
#endif
    _current();
    boom::glNormal3b(nx, ny, nz);
}

void OpenGL::normal3bv(boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glNormal3bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3bv() failed: OpenGL function \"glNormal3bv\" not loaded");
    }
#endif
    _current();
    boom::glNormal3bv(v);
}

void OpenGL::normal3d(boom::OpenGLDouble nx, boom::OpenGLDouble ny, boom::OpenGLDouble nz) const {
#ifndef NDEBUG
    if (boom::glNormal3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3d() failed: OpenGL function \"glNormal3d\" not loaded");
    }
#endif
    _current();
    boom::glNormal3d(nx, ny, nz);
}

void OpenGL::normal3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glNormal3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3dv() failed: OpenGL function \"glNormal3dv\" not loaded");
    }
#endif
    _current();
    boom::glNormal3dv(v);
}

void OpenGL::normal3f(boom::OpenGLFloat nx, boom::OpenGLFloat ny, boom::OpenGLFloat nz) const {
#ifndef NDEBUG
    if (boom::glNormal3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3f() failed: OpenGL function \"glNormal3f\" not loaded");
    }
#endif
    _current();
    boom::glNormal3f(nx, ny, nz);
}

void OpenGL::normal3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glNormal3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3fv() failed: OpenGL function \"glNormal3fv\" not loaded");
    }
#endif
    _current();
    boom::glNormal3fv(v);
}

void OpenGL::normal3i(boom::OpenGLInt nx, boom::OpenGLInt ny, boom::OpenGLInt nz) const {
#ifndef NDEBUG
    if (boom::glNormal3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3i() failed: OpenGL function \"glNormal3i\" not loaded");
    }
#endif
    _current();
    boom::glNormal3i(nx, ny, nz);
}

void OpenGL::normal3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glNormal3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3iv() failed: OpenGL function \"glNormal3iv\" not loaded");
    }
#endif
    _current();
    boom::glNormal3iv(v);
}

void OpenGL::normal3s(boom::OpenGLShort nx, boom::OpenGLShort ny, boom::OpenGLShort nz) const {
#ifndef NDEBUG
    if (boom::glNormal3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3s() failed: OpenGL function \"glNormal3s\" not loaded");
    }
#endif
    _current();
    boom::glNormal3s(nx, ny, nz);
}

void OpenGL::normal3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glNormal3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3sv() failed: OpenGL function \"glNormal3sv\" not loaded");
    }
#endif
    _current();
    boom::glNormal3sv(v);
}

void OpenGL::normal3x(boom::OpenGLFixed nx, boom::OpenGLFixed ny, boom::OpenGLFixed nz) const {
#ifndef NDEBUG
    if (boom::glNormal3x == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normal3x() failed: OpenGL function \"glNormal3x\" not loaded");
    }
#endif
    _current();
    boom::glNormal3x(nx, ny, nz);
}

void OpenGL::normalP3ui(boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glNormalP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normalP3ui() failed: OpenGL function \"glNormalP3ui\" not loaded");
    }
#endif
    _current();
    boom::glNormalP3ui(type, coords);
}

void OpenGL::normalP3uiv(boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glNormalP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normalP3uiv() failed: OpenGL function \"glNormalP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glNormalP3uiv(type, coords);
}

void OpenGL::normalPointer(boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glNormalPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::normalPointer() failed: OpenGL function \"glNormalPointer\" not loaded");
    }
#endif
    _current();
    boom::glNormalPointer(type, stride, pointer);
}

void OpenGL::objectLabel(boom::OpenGLEnum identifier, boom::OpenGLUint name, boom::OpenGLSizei length, boom::OpenGLChar const* label) const {
#ifndef NDEBUG
    if (boom::glObjectLabel == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::objectLabel() failed: OpenGL function \"glObjectLabel\" not loaded");
    }
#endif
    _current();
    boom::glObjectLabel(identifier, name, length, label);
}

void OpenGL::objectPtrLabel(void const* ptr, boom::OpenGLSizei length, boom::OpenGLChar const* label) const {
#ifndef NDEBUG
    if (boom::glObjectPtrLabel == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::objectPtrLabel() failed: OpenGL function \"glObjectPtrLabel\" not loaded");
    }
#endif
    _current();
    boom::glObjectPtrLabel(ptr, length, label);
}

void OpenGL::ortho(boom::OpenGLDouble left, boom::OpenGLDouble right, boom::OpenGLDouble bottom, boom::OpenGLDouble top, boom::OpenGLDouble zNear, boom::OpenGLDouble zFar) const {
#ifndef NDEBUG
    if (boom::glOrtho == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::ortho() failed: OpenGL function \"glOrtho\" not loaded");
    }
#endif
    _current();
    boom::glOrtho(left, right, bottom, top, zNear, zFar);
}

void OpenGL::orthof(boom::OpenGLFloat l, boom::OpenGLFloat r, boom::OpenGLFloat b, boom::OpenGLFloat t, boom::OpenGLFloat n, boom::OpenGLFloat f) const {
#ifndef NDEBUG
    if (boom::glOrthof == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::orthof() failed: OpenGL function \"glOrthof\" not loaded");
    }
#endif
    _current();
    boom::glOrthof(l, r, b, t, n, f);
}

void OpenGL::orthox(boom::OpenGLFixed l, boom::OpenGLFixed r, boom::OpenGLFixed b, boom::OpenGLFixed t, boom::OpenGLFixed n, boom::OpenGLFixed f) const {
#ifndef NDEBUG
    if (boom::glOrthox == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::orthox() failed: OpenGL function \"glOrthox\" not loaded");
    }
#endif
    _current();
    boom::glOrthox(l, r, b, t, n, f);
}

void OpenGL::passThrough(boom::OpenGLFloat token) const {
#ifndef NDEBUG
    if (boom::glPassThrough == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::passThrough() failed: OpenGL function \"glPassThrough\" not loaded");
    }
#endif
    _current();
    boom::glPassThrough(token);
}

void OpenGL::patchParameterfv(boom::OpenGLEnum pname, boom::OpenGLFloat const* values) const {
#ifndef NDEBUG
    if (boom::glPatchParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::patchParameterfv() failed: OpenGL function \"glPatchParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glPatchParameterfv(pname, values);
}

void OpenGL::patchParameteri(boom::OpenGLEnum pname, boom::OpenGLInt value) const {
#ifndef NDEBUG
    if (boom::glPatchParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::patchParameteri() failed: OpenGL function \"glPatchParameteri\" not loaded");
    }
#endif
    _current();
    boom::glPatchParameteri(pname, value);
}

void OpenGL::pauseTransformFeedback() const {
#ifndef NDEBUG
    if (boom::glPauseTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pauseTransformFeedback() failed: OpenGL function \"glPauseTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glPauseTransformFeedback();
}

void OpenGL::pixelMapfv(boom::OpenGLEnum map, boom::OpenGLSizei mapsize, boom::OpenGLFloat const* values) const {
#ifndef NDEBUG
    if (boom::glPixelMapfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelMapfv() failed: OpenGL function \"glPixelMapfv\" not loaded");
    }
#endif
    _current();
    boom::glPixelMapfv(map, mapsize, values);
}

void OpenGL::pixelMapuiv(boom::OpenGLEnum map, boom::OpenGLSizei mapsize, boom::OpenGLUint const* values) const {
#ifndef NDEBUG
    if (boom::glPixelMapuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelMapuiv() failed: OpenGL function \"glPixelMapuiv\" not loaded");
    }
#endif
    _current();
    boom::glPixelMapuiv(map, mapsize, values);
}

void OpenGL::pixelMapusv(boom::OpenGLEnum map, boom::OpenGLSizei mapsize, boom::OpenGLUShort const* values) const {
#ifndef NDEBUG
    if (boom::glPixelMapusv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelMapusv() failed: OpenGL function \"glPixelMapusv\" not loaded");
    }
#endif
    _current();
    boom::glPixelMapusv(map, mapsize, values);
}

void OpenGL::pixelStoref(boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glPixelStoref == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelStoref() failed: OpenGL function \"glPixelStoref\" not loaded");
    }
#endif
    _current();
    boom::glPixelStoref(pname, param);
}

void OpenGL::pixelStorei(boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glPixelStorei == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelStorei() failed: OpenGL function \"glPixelStorei\" not loaded");
    }
#endif
    _current();
    boom::glPixelStorei(pname, param);
}

void OpenGL::pixelTransferf(boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glPixelTransferf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelTransferf() failed: OpenGL function \"glPixelTransferf\" not loaded");
    }
#endif
    _current();
    boom::glPixelTransferf(pname, param);
}

void OpenGL::pixelTransferi(boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glPixelTransferi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelTransferi() failed: OpenGL function \"glPixelTransferi\" not loaded");
    }
#endif
    _current();
    boom::glPixelTransferi(pname, param);
}

void OpenGL::pixelZoom(boom::OpenGLFloat xfactor, boom::OpenGLFloat yfactor) const {
#ifndef NDEBUG
    if (boom::glPixelZoom == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pixelZoom() failed: OpenGL function \"glPixelZoom\" not loaded");
    }
#endif
    _current();
    boom::glPixelZoom(xfactor, yfactor);
}

void OpenGL::pointParameterf(boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glPointParameterf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameterf() failed: OpenGL function \"glPointParameterf\" not loaded");
    }
#endif
    _current();
    boom::glPointParameterf(pname, param);
}

void OpenGL::pointParameterfv(boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glPointParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameterfv() failed: OpenGL function \"glPointParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glPointParameterfv(pname, params);
}

void OpenGL::pointParameteri(boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glPointParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameteri() failed: OpenGL function \"glPointParameteri\" not loaded");
    }
#endif
    _current();
    boom::glPointParameteri(pname, param);
}

void OpenGL::pointParameteriv(boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glPointParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameteriv() failed: OpenGL function \"glPointParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glPointParameteriv(pname, params);
}

void OpenGL::pointParameterx(boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glPointParameterx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameterx() failed: OpenGL function \"glPointParameterx\" not loaded");
    }
#endif
    _current();
    boom::glPointParameterx(pname, param);
}

void OpenGL::pointParameterxv(boom::OpenGLEnum pname, boom::OpenGLFixed const* params) const {
#ifndef NDEBUG
    if (boom::glPointParameterxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointParameterxv() failed: OpenGL function \"glPointParameterxv\" not loaded");
    }
#endif
    _current();
    boom::glPointParameterxv(pname, params);
}

void OpenGL::pointSize(boom::OpenGLFloat size) const {
#ifndef NDEBUG
    if (boom::glPointSize == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointSize() failed: OpenGL function \"glPointSize\" not loaded");
    }
#endif
    _current();
    boom::glPointSize(size);
}

void OpenGL::pointSizex(boom::OpenGLFixed size) const {
#ifndef NDEBUG
    if (boom::glPointSizex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pointSizex() failed: OpenGL function \"glPointSizex\" not loaded");
    }
#endif
    _current();
    boom::glPointSizex(size);
}

void OpenGL::polygonMode(boom::OpenGLEnum face, boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glPolygonMode == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::polygonMode() failed: OpenGL function \"glPolygonMode\" not loaded");
    }
#endif
    _current();
    boom::glPolygonMode(face, mode);
}

void OpenGL::polygonOffset(boom::OpenGLFloat factor, boom::OpenGLFloat units) const {
#ifndef NDEBUG
    if (boom::glPolygonOffset == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::polygonOffset() failed: OpenGL function \"glPolygonOffset\" not loaded");
    }
#endif
    _current();
    boom::glPolygonOffset(factor, units);
}

void OpenGL::polygonOffsetClamp(boom::OpenGLFloat factor, boom::OpenGLFloat units, boom::OpenGLFloat clamp) const {
#ifndef NDEBUG
    if (boom::glPolygonOffsetClamp == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::polygonOffsetClamp() failed: OpenGL function \"glPolygonOffsetClamp\" not loaded");
    }
#endif
    _current();
    boom::glPolygonOffsetClamp(factor, units, clamp);
}

void OpenGL::polygonOffsetx(boom::OpenGLFixed factor, boom::OpenGLFixed units) const {
#ifndef NDEBUG
    if (boom::glPolygonOffsetx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::polygonOffsetx() failed: OpenGL function \"glPolygonOffsetx\" not loaded");
    }
#endif
    _current();
    boom::glPolygonOffsetx(factor, units);
}

void OpenGL::polygonStipple(boom::OpenGLUbyte const* mask) const {
#ifndef NDEBUG
    if (boom::glPolygonStipple == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::polygonStipple() failed: OpenGL function \"glPolygonStipple\" not loaded");
    }
#endif
    _current();
    boom::glPolygonStipple(mask);
}

void OpenGL::popAttrib() const {
#ifndef NDEBUG
    if (boom::glPopAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::popAttrib() failed: OpenGL function \"glPopAttrib\" not loaded");
    }
#endif
    _current();
    boom::glPopAttrib();
}

void OpenGL::popClientAttrib() const {
#ifndef NDEBUG
    if (boom::glPopClientAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::popClientAttrib() failed: OpenGL function \"glPopClientAttrib\" not loaded");
    }
#endif
    _current();
    boom::glPopClientAttrib();
}

void OpenGL::popDebugGroup() const {
#ifndef NDEBUG
    if (boom::glPopDebugGroup == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::popDebugGroup() failed: OpenGL function \"glPopDebugGroup\" not loaded");
    }
#endif
    _current();
    boom::glPopDebugGroup();
}

void OpenGL::popMatrix() const {
#ifndef NDEBUG
    if (boom::glPopMatrix == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::popMatrix() failed: OpenGL function \"glPopMatrix\" not loaded");
    }
#endif
    _current();
    boom::glPopMatrix();
}

void OpenGL::popName() const {
#ifndef NDEBUG
    if (boom::glPopName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::popName() failed: OpenGL function \"glPopName\" not loaded");
    }
#endif
    _current();
    boom::glPopName();
}

void OpenGL::primitiveBoundingBox(boom::OpenGLFloat minX, boom::OpenGLFloat minY, boom::OpenGLFloat minZ, boom::OpenGLFloat minW, boom::OpenGLFloat maxX, boom::OpenGLFloat maxY, boom::OpenGLFloat maxZ, boom::OpenGLFloat maxW) const {
#ifndef NDEBUG
    if (boom::glPrimitiveBoundingBox == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::primitiveBoundingBox() failed: OpenGL function \"glPrimitiveBoundingBox\" not loaded");
    }
#endif
    _current();
    boom::glPrimitiveBoundingBox(minX, minY, minZ, minW, maxX, maxY, maxZ, maxW);
}

void OpenGL::primitiveRestartIndex(boom::OpenGLUint index) const {
#ifndef NDEBUG
    if (boom::glPrimitiveRestartIndex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::primitiveRestartIndex() failed: OpenGL function \"glPrimitiveRestartIndex\" not loaded");
    }
#endif
    _current();
    boom::glPrimitiveRestartIndex(index);
}

void OpenGL::prioritizeTextures(boom::OpenGLSizei n, boom::OpenGLUint const* textures, boom::OpenGLFloat const* priorities) const {
#ifndef NDEBUG
    if (boom::glPrioritizeTextures == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::prioritizeTextures() failed: OpenGL function \"glPrioritizeTextures\" not loaded");
    }
#endif
    _current();
    boom::glPrioritizeTextures(n, textures, priorities);
}

void OpenGL::programBinary(boom::OpenGLUint program, boom::OpenGLEnum binaryFormat, void const* binary, boom::OpenGLSizei length) const {
#ifndef NDEBUG
    if (boom::glProgramBinary == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programBinary() failed: OpenGL function \"glProgramBinary\" not loaded");
    }
#endif
    _current();
    boom::glProgramBinary(program, binaryFormat, binary, length);
}

void OpenGL::programParameteri(boom::OpenGLUint program, boom::OpenGLEnum pname, boom::OpenGLInt value) const {
#ifndef NDEBUG
    if (boom::glProgramParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programParameteri() failed: OpenGL function \"glProgramParameteri\" not loaded");
    }
#endif
    _current();
    boom::glProgramParameteri(program, pname, value);
}

void OpenGL::programUniform1d(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLDouble v0) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1d() failed: OpenGL function \"glProgramUniform1d\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1d(program, location, v0);
}

void OpenGL::programUniform1dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1dv() failed: OpenGL function \"glProgramUniform1dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1dv(program, location, count, value);
}

void OpenGL::programUniform1f(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLFloat v0) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1f() failed: OpenGL function \"glProgramUniform1f\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1f(program, location, v0);
}

void OpenGL::programUniform1fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1fv() failed: OpenGL function \"glProgramUniform1fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1fv(program, location, count, value);
}

void OpenGL::programUniform1i(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLInt v0) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1i() failed: OpenGL function \"glProgramUniform1i\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1i(program, location, v0);
}

void OpenGL::programUniform1iv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1iv() failed: OpenGL function \"glProgramUniform1iv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1iv(program, location, count, value);
}

void OpenGL::programUniform1ui(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLUint v0) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1ui() failed: OpenGL function \"glProgramUniform1ui\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1ui(program, location, v0);
}

void OpenGL::programUniform1uiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform1uiv() failed: OpenGL function \"glProgramUniform1uiv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform1uiv(program, location, count, value);
}

void OpenGL::programUniform2d(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLDouble v0, boom::OpenGLDouble v1) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2d() failed: OpenGL function \"glProgramUniform2d\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2d(program, location, v0, v1);
}

void OpenGL::programUniform2dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2dv() failed: OpenGL function \"glProgramUniform2dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2dv(program, location, count, value);
}

void OpenGL::programUniform2f(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2f() failed: OpenGL function \"glProgramUniform2f\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2f(program, location, v0, v1);
}

void OpenGL::programUniform2fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2fv() failed: OpenGL function \"glProgramUniform2fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2fv(program, location, count, value);
}

void OpenGL::programUniform2i(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2i() failed: OpenGL function \"glProgramUniform2i\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2i(program, location, v0, v1);
}

void OpenGL::programUniform2iv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2iv() failed: OpenGL function \"glProgramUniform2iv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2iv(program, location, count, value);
}

void OpenGL::programUniform2ui(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2ui() failed: OpenGL function \"glProgramUniform2ui\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2ui(program, location, v0, v1);
}

void OpenGL::programUniform2uiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform2uiv() failed: OpenGL function \"glProgramUniform2uiv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform2uiv(program, location, count, value);
}

void OpenGL::programUniform3d(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLDouble v0, boom::OpenGLDouble v1, boom::OpenGLDouble v2) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3d() failed: OpenGL function \"glProgramUniform3d\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3d(program, location, v0, v1, v2);
}

void OpenGL::programUniform3dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3dv() failed: OpenGL function \"glProgramUniform3dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3dv(program, location, count, value);
}

void OpenGL::programUniform3f(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1, boom::OpenGLFloat v2) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3f() failed: OpenGL function \"glProgramUniform3f\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3f(program, location, v0, v1, v2);
}

void OpenGL::programUniform3fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3fv() failed: OpenGL function \"glProgramUniform3fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3fv(program, location, count, value);
}

void OpenGL::programUniform3i(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1, boom::OpenGLInt v2) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3i() failed: OpenGL function \"glProgramUniform3i\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3i(program, location, v0, v1, v2);
}

void OpenGL::programUniform3iv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3iv() failed: OpenGL function \"glProgramUniform3iv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3iv(program, location, count, value);
}

void OpenGL::programUniform3ui(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1, boom::OpenGLUint v2) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3ui() failed: OpenGL function \"glProgramUniform3ui\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3ui(program, location, v0, v1, v2);
}

void OpenGL::programUniform3uiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform3uiv() failed: OpenGL function \"glProgramUniform3uiv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform3uiv(program, location, count, value);
}

void OpenGL::programUniform4d(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLDouble v0, boom::OpenGLDouble v1, boom::OpenGLDouble v2, boom::OpenGLDouble v3) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4d() failed: OpenGL function \"glProgramUniform4d\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4d(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4dv() failed: OpenGL function \"glProgramUniform4dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4dv(program, location, count, value);
}

void OpenGL::programUniform4f(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1, boom::OpenGLFloat v2, boom::OpenGLFloat v3) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4f() failed: OpenGL function \"glProgramUniform4f\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4f(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4fv() failed: OpenGL function \"glProgramUniform4fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4fv(program, location, count, value);
}

void OpenGL::programUniform4i(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1, boom::OpenGLInt v2, boom::OpenGLInt v3) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4i() failed: OpenGL function \"glProgramUniform4i\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4i(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4iv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4iv() failed: OpenGL function \"glProgramUniform4iv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4iv(program, location, count, value);
}

void OpenGL::programUniform4ui(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1, boom::OpenGLUint v2, boom::OpenGLUint v3) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4ui() failed: OpenGL function \"glProgramUniform4ui\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

void OpenGL::programUniform4uiv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniform4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniform4uiv() failed: OpenGL function \"glProgramUniform4uiv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniform4uiv(program, location, count, value);
}

void OpenGL::programUniformMatrix2dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2dv() failed: OpenGL function \"glProgramUniformMatrix2dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2fv() failed: OpenGL function \"glProgramUniformMatrix2fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x3dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2x3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2x3dv() failed: OpenGL function \"glProgramUniformMatrix2x3dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2x3dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x3fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2x3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2x3fv() failed: OpenGL function \"glProgramUniformMatrix2x3fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x4dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2x4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2x4dv() failed: OpenGL function \"glProgramUniformMatrix2x4dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2x4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix2x4fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix2x4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix2x4fv() failed: OpenGL function \"glProgramUniformMatrix2x4fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3dv() failed: OpenGL function \"glProgramUniformMatrix3dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3fv() failed: OpenGL function \"glProgramUniformMatrix3fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x2dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3x2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3x2dv() failed: OpenGL function \"glProgramUniformMatrix3x2dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3x2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x2fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3x2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3x2fv() failed: OpenGL function \"glProgramUniformMatrix3x2fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x4dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3x4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3x4dv() failed: OpenGL function \"glProgramUniformMatrix3x4dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3x4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix3x4fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix3x4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix3x4fv() failed: OpenGL function \"glProgramUniformMatrix3x4fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4dv() failed: OpenGL function \"glProgramUniformMatrix4dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4fv() failed: OpenGL function \"glProgramUniformMatrix4fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x2dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4x2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4x2dv() failed: OpenGL function \"glProgramUniformMatrix4x2dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4x2dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x2fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4x2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4x2fv() failed: OpenGL function \"glProgramUniformMatrix4x2fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x3dv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4x3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4x3dv() failed: OpenGL function \"glProgramUniformMatrix4x3dv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4x3dv(program, location, count, transpose, value);
}

void OpenGL::programUniformMatrix4x3fv(boom::OpenGLUint program, boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glProgramUniformMatrix4x3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::programUniformMatrix4x3fv() failed: OpenGL function \"glProgramUniformMatrix4x3fv\" not loaded");
    }
#endif
    _current();
    boom::glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
}

void OpenGL::provokingVertex(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glProvokingVertex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::provokingVertex() failed: OpenGL function \"glProvokingVertex\" not loaded");
    }
#endif
    _current();
    boom::glProvokingVertex(mode);
}

void OpenGL::pushAttrib(boom::OpenGLBitfield mask) const {
#ifndef NDEBUG
    if (boom::glPushAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pushAttrib() failed: OpenGL function \"glPushAttrib\" not loaded");
    }
#endif
    _current();
    boom::glPushAttrib(mask);
}

void OpenGL::pushClientAttrib(boom::OpenGLBitfield mask) const {
#ifndef NDEBUG
    if (boom::glPushClientAttrib == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pushClientAttrib() failed: OpenGL function \"glPushClientAttrib\" not loaded");
    }
#endif
    _current();
    boom::glPushClientAttrib(mask);
}

void OpenGL::pushDebugGroup(boom::OpenGLEnum source, boom::OpenGLUint id, boom::OpenGLSizei length, boom::OpenGLChar const* message) const {
#ifndef NDEBUG
    if (boom::glPushDebugGroup == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pushDebugGroup() failed: OpenGL function \"glPushDebugGroup\" not loaded");
    }
#endif
    _current();
    boom::glPushDebugGroup(source, id, length, message);
}

void OpenGL::pushMatrix() const {
#ifndef NDEBUG
    if (boom::glPushMatrix == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pushMatrix() failed: OpenGL function \"glPushMatrix\" not loaded");
    }
#endif
    _current();
    boom::glPushMatrix();
}

void OpenGL::pushName(boom::OpenGLUint name) const {
#ifndef NDEBUG
    if (boom::glPushName == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::pushName() failed: OpenGL function \"glPushName\" not loaded");
    }
#endif
    _current();
    boom::glPushName(name);
}

void OpenGL::queryCounter(boom::OpenGLUint id, boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glQueryCounter == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::queryCounter() failed: OpenGL function \"glQueryCounter\" not loaded");
    }
#endif
    _current();
    boom::glQueryCounter(id, target);
}

void OpenGL::rasterPos2d(boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glRasterPos2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2d() failed: OpenGL function \"glRasterPos2d\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2d(x, y);
}

void OpenGL::rasterPos2dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2dv() failed: OpenGL function \"glRasterPos2dv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2dv(v);
}

void OpenGL::rasterPos2f(boom::OpenGLFloat x, boom::OpenGLFloat y) const {
#ifndef NDEBUG
    if (boom::glRasterPos2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2f() failed: OpenGL function \"glRasterPos2f\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2f(x, y);
}

void OpenGL::rasterPos2fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2fv() failed: OpenGL function \"glRasterPos2fv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2fv(v);
}

void OpenGL::rasterPos2i(boom::OpenGLInt x, boom::OpenGLInt y) const {
#ifndef NDEBUG
    if (boom::glRasterPos2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2i() failed: OpenGL function \"glRasterPos2i\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2i(x, y);
}

void OpenGL::rasterPos2iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2iv() failed: OpenGL function \"glRasterPos2iv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2iv(v);
}

void OpenGL::rasterPos2s(boom::OpenGLShort x, boom::OpenGLShort y) const {
#ifndef NDEBUG
    if (boom::glRasterPos2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2s() failed: OpenGL function \"glRasterPos2s\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2s(x, y);
}

void OpenGL::rasterPos2sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos2sv() failed: OpenGL function \"glRasterPos2sv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos2sv(v);
}

void OpenGL::rasterPos3d(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glRasterPos3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3d() failed: OpenGL function \"glRasterPos3d\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3d(x, y, z);
}

void OpenGL::rasterPos3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3dv() failed: OpenGL function \"glRasterPos3dv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3dv(v);
}

void OpenGL::rasterPos3f(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glRasterPos3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3f() failed: OpenGL function \"glRasterPos3f\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3f(x, y, z);
}

void OpenGL::rasterPos3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3fv() failed: OpenGL function \"glRasterPos3fv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3fv(v);
}

void OpenGL::rasterPos3i(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z) const {
#ifndef NDEBUG
    if (boom::glRasterPos3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3i() failed: OpenGL function \"glRasterPos3i\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3i(x, y, z);
}

void OpenGL::rasterPos3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3iv() failed: OpenGL function \"glRasterPos3iv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3iv(v);
}

void OpenGL::rasterPos3s(boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z) const {
#ifndef NDEBUG
    if (boom::glRasterPos3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3s() failed: OpenGL function \"glRasterPos3s\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3s(x, y, z);
}

void OpenGL::rasterPos3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos3sv() failed: OpenGL function \"glRasterPos3sv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos3sv(v);
}

void OpenGL::rasterPos4d(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z, boom::OpenGLDouble w) const {
#ifndef NDEBUG
    if (boom::glRasterPos4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4d() failed: OpenGL function \"glRasterPos4d\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4d(x, y, z, w);
}

void OpenGL::rasterPos4dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4dv() failed: OpenGL function \"glRasterPos4dv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4dv(v);
}

void OpenGL::rasterPos4f(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z, boom::OpenGLFloat w) const {
#ifndef NDEBUG
    if (boom::glRasterPos4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4f() failed: OpenGL function \"glRasterPos4f\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4f(x, y, z, w);
}

void OpenGL::rasterPos4fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4fv() failed: OpenGL function \"glRasterPos4fv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4fv(v);
}

void OpenGL::rasterPos4i(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z, boom::OpenGLInt w) const {
#ifndef NDEBUG
    if (boom::glRasterPos4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4i() failed: OpenGL function \"glRasterPos4i\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4i(x, y, z, w);
}

void OpenGL::rasterPos4iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4iv() failed: OpenGL function \"glRasterPos4iv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4iv(v);
}

void OpenGL::rasterPos4s(boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z, boom::OpenGLShort w) const {
#ifndef NDEBUG
    if (boom::glRasterPos4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4s() failed: OpenGL function \"glRasterPos4s\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4s(x, y, z, w);
}

void OpenGL::rasterPos4sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glRasterPos4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rasterPos4sv() failed: OpenGL function \"glRasterPos4sv\" not loaded");
    }
#endif
    _current();
    boom::glRasterPos4sv(v);
}

void OpenGL::readBuffer(boom::OpenGLEnum src) const {
#ifndef NDEBUG
    if (boom::glReadBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::readBuffer() failed: OpenGL function \"glReadBuffer\" not loaded");
    }
#endif
    _current();
    boom::glReadBuffer(src);
}

void OpenGL::readPixels(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLEnum type, void* pixels) const {
#ifndef NDEBUG
    if (boom::glReadPixels == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::readPixels() failed: OpenGL function \"glReadPixels\" not loaded");
    }
#endif
    _current();
    boom::glReadPixels(x, y, width, height, format, type, pixels);
}

void OpenGL::readnPixels(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLEnum type, boom::OpenGLSizei bufSize, void* data) const {
#ifndef NDEBUG
    if (boom::glReadnPixels == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::readnPixels() failed: OpenGL function \"glReadnPixels\" not loaded");
    }
#endif
    _current();
    boom::glReadnPixels(x, y, width, height, format, type, bufSize, data);
}

void OpenGL::rectd(boom::OpenGLDouble x1, boom::OpenGLDouble y1, boom::OpenGLDouble x2, boom::OpenGLDouble y2) const {
#ifndef NDEBUG
    if (boom::glRectd == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectd() failed: OpenGL function \"glRectd\" not loaded");
    }
#endif
    _current();
    boom::glRectd(x1, y1, x2, y2);
}

void OpenGL::rectdv(boom::OpenGLDouble const* v1, boom::OpenGLDouble const* v2) const {
#ifndef NDEBUG
    if (boom::glRectdv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectdv() failed: OpenGL function \"glRectdv\" not loaded");
    }
#endif
    _current();
    boom::glRectdv(v1, v2);
}

void OpenGL::rectf(boom::OpenGLFloat x1, boom::OpenGLFloat y1, boom::OpenGLFloat x2, boom::OpenGLFloat y2) const {
#ifndef NDEBUG
    if (boom::glRectf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectf() failed: OpenGL function \"glRectf\" not loaded");
    }
#endif
    _current();
    boom::glRectf(x1, y1, x2, y2);
}

void OpenGL::rectfv(boom::OpenGLFloat const* v1, boom::OpenGLFloat const* v2) const {
#ifndef NDEBUG
    if (boom::glRectfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectfv() failed: OpenGL function \"glRectfv\" not loaded");
    }
#endif
    _current();
    boom::glRectfv(v1, v2);
}

void OpenGL::recti(boom::OpenGLInt x1, boom::OpenGLInt y1, boom::OpenGLInt x2, boom::OpenGLInt y2) const {
#ifndef NDEBUG
    if (boom::glRecti == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::recti() failed: OpenGL function \"glRecti\" not loaded");
    }
#endif
    _current();
    boom::glRecti(x1, y1, x2, y2);
}

void OpenGL::rectiv(boom::OpenGLInt const* v1, boom::OpenGLInt const* v2) const {
#ifndef NDEBUG
    if (boom::glRectiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectiv() failed: OpenGL function \"glRectiv\" not loaded");
    }
#endif
    _current();
    boom::glRectiv(v1, v2);
}

void OpenGL::rects(boom::OpenGLShort x1, boom::OpenGLShort y1, boom::OpenGLShort x2, boom::OpenGLShort y2) const {
#ifndef NDEBUG
    if (boom::glRects == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rects() failed: OpenGL function \"glRects\" not loaded");
    }
#endif
    _current();
    boom::glRects(x1, y1, x2, y2);
}

void OpenGL::rectsv(boom::OpenGLShort const* v1, boom::OpenGLShort const* v2) const {
#ifndef NDEBUG
    if (boom::glRectsv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rectsv() failed: OpenGL function \"glRectsv\" not loaded");
    }
#endif
    _current();
    boom::glRectsv(v1, v2);
}

void OpenGL::releaseShaderCompiler() const {
#ifndef NDEBUG
    if (boom::glReleaseShaderCompiler == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::releaseShaderCompiler() failed: OpenGL function \"glReleaseShaderCompiler\" not loaded");
    }
#endif
    _current();
    boom::glReleaseShaderCompiler();
}

boom::OpenGLInt OpenGL::renderMode(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glRenderMode == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::renderMode() failed: OpenGL function \"glRenderMode\" not loaded");
    }
#endif
    _current();
    return boom::glRenderMode(mode);
}

void OpenGL::renderbufferStorage(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glRenderbufferStorage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::renderbufferStorage() failed: OpenGL function \"glRenderbufferStorage\" not loaded");
    }
#endif
    _current();
    boom::glRenderbufferStorage(target, internalformat, width, height);
}

void OpenGL::renderbufferStorageMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glRenderbufferStorageMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::renderbufferStorageMultisample() failed: OpenGL function \"glRenderbufferStorageMultisample\" not loaded");
    }
#endif
    _current();
    boom::glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

void OpenGL::resumeTransformFeedback() const {
#ifndef NDEBUG
    if (boom::glResumeTransformFeedback == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::resumeTransformFeedback() failed: OpenGL function \"glResumeTransformFeedback\" not loaded");
    }
#endif
    _current();
    boom::glResumeTransformFeedback();
}

void OpenGL::rotated(boom::OpenGLDouble angle, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glRotated == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rotated() failed: OpenGL function \"glRotated\" not loaded");
    }
#endif
    _current();
    boom::glRotated(angle, x, y, z);
}

void OpenGL::rotatef(boom::OpenGLFloat angle, boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glRotatef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rotatef() failed: OpenGL function \"glRotatef\" not loaded");
    }
#endif
    _current();
    boom::glRotatef(angle, x, y, z);
}

void OpenGL::rotatex(boom::OpenGLFixed angle, boom::OpenGLFixed x, boom::OpenGLFixed y, boom::OpenGLFixed z) const {
#ifndef NDEBUG
    if (boom::glRotatex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::rotatex() failed: OpenGL function \"glRotatex\" not loaded");
    }
#endif
    _current();
    boom::glRotatex(angle, x, y, z);
}

void OpenGL::sampleCoverage(boom::OpenGLFloat value, boom::OpenGLBoolean invert) const {
#ifndef NDEBUG
    if (boom::glSampleCoverage == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::sampleCoverage() failed: OpenGL function \"glSampleCoverage\" not loaded");
    }
#endif
    _current();
    boom::glSampleCoverage(value, invert);
}

void OpenGL::sampleCoveragex(boom::OpenGLClampx value, boom::OpenGLBoolean invert) const {
#ifndef NDEBUG
    if (boom::glSampleCoveragex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::sampleCoveragex() failed: OpenGL function \"glSampleCoveragex\" not loaded");
    }
#endif
    _current();
    boom::glSampleCoveragex(value, invert);
}

void OpenGL::sampleMaski(boom::OpenGLUint maskNumber, boom::OpenGLBitfield mask) const {
#ifndef NDEBUG
    if (boom::glSampleMaski == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::sampleMaski() failed: OpenGL function \"glSampleMaski\" not loaded");
    }
#endif
    _current();
    boom::glSampleMaski(maskNumber, mask);
}

void OpenGL::samplerParameterIiv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLInt const* param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameterIiv() failed: OpenGL function \"glSamplerParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameterIiv(sampler, pname, param);
}

void OpenGL::samplerParameterIuiv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLUint const* param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameterIuiv() failed: OpenGL function \"glSamplerParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameterIuiv(sampler, pname, param);
}

void OpenGL::samplerParameterf(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameterf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameterf() failed: OpenGL function \"glSamplerParameterf\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameterf(sampler, pname, param);
}

void OpenGL::samplerParameterfv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLFloat const* param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameterfv() failed: OpenGL function \"glSamplerParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameterfv(sampler, pname, param);
}

void OpenGL::samplerParameteri(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameteri() failed: OpenGL function \"glSamplerParameteri\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameteri(sampler, pname, param);
}

void OpenGL::samplerParameteriv(boom::OpenGLUint sampler, boom::OpenGLEnum pname, boom::OpenGLInt const* param) const {
#ifndef NDEBUG
    if (boom::glSamplerParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::samplerParameteriv() failed: OpenGL function \"glSamplerParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glSamplerParameteriv(sampler, pname, param);
}

void OpenGL::scaled(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glScaled == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scaled() failed: OpenGL function \"glScaled\" not loaded");
    }
#endif
    _current();
    boom::glScaled(x, y, z);
}

void OpenGL::scalef(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glScalef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scalef() failed: OpenGL function \"glScalef\" not loaded");
    }
#endif
    _current();
    boom::glScalef(x, y, z);
}

void OpenGL::scalex(boom::OpenGLFixed x, boom::OpenGLFixed y, boom::OpenGLFixed z) const {
#ifndef NDEBUG
    if (boom::glScalex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scalex() failed: OpenGL function \"glScalex\" not loaded");
    }
#endif
    _current();
    boom::glScalex(x, y, z);
}

void OpenGL::scissor(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glScissor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scissor() failed: OpenGL function \"glScissor\" not loaded");
    }
#endif
    _current();
    boom::glScissor(x, y, width, height);
}

void OpenGL::scissorArrayv(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glScissorArrayv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scissorArrayv() failed: OpenGL function \"glScissorArrayv\" not loaded");
    }
#endif
    _current();
    boom::glScissorArrayv(first, count, v);
}

void OpenGL::scissorIndexed(boom::OpenGLUint index, boom::OpenGLInt left, boom::OpenGLInt bottom, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glScissorIndexed == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scissorIndexed() failed: OpenGL function \"glScissorIndexed\" not loaded");
    }
#endif
    _current();
    boom::glScissorIndexed(index, left, bottom, width, height);
}

void OpenGL::scissorIndexedv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glScissorIndexedv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::scissorIndexedv() failed: OpenGL function \"glScissorIndexedv\" not loaded");
    }
#endif
    _current();
    boom::glScissorIndexedv(index, v);
}

void OpenGL::secondaryColor3b(boom::OpenGLByte red, boom::OpenGLByte green, boom::OpenGLByte blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3b == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3b() failed: OpenGL function \"glSecondaryColor3b\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3b(red, green, blue);
}

void OpenGL::secondaryColor3bv(boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3bv() failed: OpenGL function \"glSecondaryColor3bv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3bv(v);
}

void OpenGL::secondaryColor3d(boom::OpenGLDouble red, boom::OpenGLDouble green, boom::OpenGLDouble blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3d() failed: OpenGL function \"glSecondaryColor3d\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3d(red, green, blue);
}

void OpenGL::secondaryColor3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3dv() failed: OpenGL function \"glSecondaryColor3dv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3dv(v);
}

void OpenGL::secondaryColor3f(boom::OpenGLFloat red, boom::OpenGLFloat green, boom::OpenGLFloat blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3f() failed: OpenGL function \"glSecondaryColor3f\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3f(red, green, blue);
}

void OpenGL::secondaryColor3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3fv() failed: OpenGL function \"glSecondaryColor3fv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3fv(v);
}

void OpenGL::secondaryColor3i(boom::OpenGLInt red, boom::OpenGLInt green, boom::OpenGLInt blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3i() failed: OpenGL function \"glSecondaryColor3i\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3i(red, green, blue);
}

void OpenGL::secondaryColor3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3iv() failed: OpenGL function \"glSecondaryColor3iv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3iv(v);
}

void OpenGL::secondaryColor3s(boom::OpenGLShort red, boom::OpenGLShort green, boom::OpenGLShort blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3s() failed: OpenGL function \"glSecondaryColor3s\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3s(red, green, blue);
}

void OpenGL::secondaryColor3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3sv() failed: OpenGL function \"glSecondaryColor3sv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3sv(v);
}

void OpenGL::secondaryColor3ub(boom::OpenGLUbyte red, boom::OpenGLUbyte green, boom::OpenGLUbyte blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3ub == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3ub() failed: OpenGL function \"glSecondaryColor3ub\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3ub(red, green, blue);
}

void OpenGL::secondaryColor3ubv(boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3ubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3ubv() failed: OpenGL function \"glSecondaryColor3ubv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3ubv(v);
}

void OpenGL::secondaryColor3ui(boom::OpenGLUint red, boom::OpenGLUint green, boom::OpenGLUint blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3ui() failed: OpenGL function \"glSecondaryColor3ui\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3ui(red, green, blue);
}

void OpenGL::secondaryColor3uiv(boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3uiv() failed: OpenGL function \"glSecondaryColor3uiv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3uiv(v);
}

void OpenGL::secondaryColor3us(boom::OpenGLUShort red, boom::OpenGLUShort green, boom::OpenGLUShort blue) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3us == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3us() failed: OpenGL function \"glSecondaryColor3us\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3us(red, green, blue);
}

void OpenGL::secondaryColor3usv(boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glSecondaryColor3usv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColor3usv() failed: OpenGL function \"glSecondaryColor3usv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColor3usv(v);
}

void OpenGL::secondaryColorP3ui(boom::OpenGLEnum type, boom::OpenGLUint color) const {
#ifndef NDEBUG
    if (boom::glSecondaryColorP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColorP3ui() failed: OpenGL function \"glSecondaryColorP3ui\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColorP3ui(type, color);
}

void OpenGL::secondaryColorP3uiv(boom::OpenGLEnum type, boom::OpenGLUint const* color) const {
#ifndef NDEBUG
    if (boom::glSecondaryColorP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColorP3uiv() failed: OpenGL function \"glSecondaryColorP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColorP3uiv(type, color);
}

void OpenGL::secondaryColorPointer(boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glSecondaryColorPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::secondaryColorPointer() failed: OpenGL function \"glSecondaryColorPointer\" not loaded");
    }
#endif
    _current();
    boom::glSecondaryColorPointer(size, type, stride, pointer);
}

void OpenGL::selectBuffer(boom::OpenGLSizei size, boom::OpenGLUint* buffer) const {
#ifndef NDEBUG
    if (boom::glSelectBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::selectBuffer() failed: OpenGL function \"glSelectBuffer\" not loaded");
    }
#endif
    _current();
    boom::glSelectBuffer(size, buffer);
}

void OpenGL::shadeModel(boom::OpenGLEnum mode) const {
#ifndef NDEBUG
    if (boom::glShadeModel == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::shadeModel() failed: OpenGL function \"glShadeModel\" not loaded");
    }
#endif
    _current();
    boom::glShadeModel(mode);
}

void OpenGL::shaderBinary(boom::OpenGLSizei count, boom::OpenGLUint const* shaders, boom::OpenGLEnum binaryFormat, void const* binary, boom::OpenGLSizei length) const {
#ifndef NDEBUG
    if (boom::glShaderBinary == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::shaderBinary() failed: OpenGL function \"glShaderBinary\" not loaded");
    }
#endif
    _current();
    boom::glShaderBinary(count, shaders, binaryFormat, binary, length);
}

void OpenGL::shaderSource(boom::OpenGLUint shader, boom::OpenGLSizei count, boom::OpenGLChar const* const* string, boom::OpenGLInt const* length) const {
#ifndef NDEBUG
    if (boom::glShaderSource == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::shaderSource() failed: OpenGL function \"glShaderSource\" not loaded");
    }
#endif
    _current();
    boom::glShaderSource(shader, count, string, length);
}

void OpenGL::shaderStorageBlockBinding(boom::OpenGLUint program, boom::OpenGLUint storageBlockIndex, boom::OpenGLUint storageBlockBinding) const {
#ifndef NDEBUG
    if (boom::glShaderStorageBlockBinding == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::shaderStorageBlockBinding() failed: OpenGL function \"glShaderStorageBlockBinding\" not loaded");
    }
#endif
    _current();
    boom::glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
}

void OpenGL::specializeShader(boom::OpenGLUint shader, boom::OpenGLChar const* pEntryPoint, boom::OpenGLUint numSpecializationConstants, boom::OpenGLUint const* pConstantIndex, boom::OpenGLUint const* pConstantValue) const {
#ifndef NDEBUG
    if (boom::glSpecializeShader == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::specializeShader() failed: OpenGL function \"glSpecializeShader\" not loaded");
    }
#endif
    _current();
    boom::glSpecializeShader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);
}

void OpenGL::stencilFunc(boom::OpenGLEnum func, boom::OpenGLInt ref, boom::OpenGLUint mask) const {
#ifndef NDEBUG
    if (boom::glStencilFunc == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilFunc() failed: OpenGL function \"glStencilFunc\" not loaded");
    }
#endif
    _current();
    boom::glStencilFunc(func, ref, mask);
}

void OpenGL::stencilFuncSeparate(boom::OpenGLEnum face, boom::OpenGLEnum func, boom::OpenGLInt ref, boom::OpenGLUint mask) const {
#ifndef NDEBUG
    if (boom::glStencilFuncSeparate == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilFuncSeparate() failed: OpenGL function \"glStencilFuncSeparate\" not loaded");
    }
#endif
    _current();
    boom::glStencilFuncSeparate(face, func, ref, mask);
}

void OpenGL::stencilMask(boom::OpenGLUint mask) const {
#ifndef NDEBUG
    if (boom::glStencilMask == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilMask() failed: OpenGL function \"glStencilMask\" not loaded");
    }
#endif
    _current();
    boom::glStencilMask(mask);
}

void OpenGL::stencilMaskSeparate(boom::OpenGLEnum face, boom::OpenGLUint mask) const {
#ifndef NDEBUG
    if (boom::glStencilMaskSeparate == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilMaskSeparate() failed: OpenGL function \"glStencilMaskSeparate\" not loaded");
    }
#endif
    _current();
    boom::glStencilMaskSeparate(face, mask);
}

void OpenGL::stencilOp(boom::OpenGLEnum fail, boom::OpenGLEnum zfail, boom::OpenGLEnum zpass) const {
#ifndef NDEBUG
    if (boom::glStencilOp == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilOp() failed: OpenGL function \"glStencilOp\" not loaded");
    }
#endif
    _current();
    boom::glStencilOp(fail, zfail, zpass);
}

void OpenGL::stencilOpSeparate(boom::OpenGLEnum face, boom::OpenGLEnum sfail, boom::OpenGLEnum dpfail, boom::OpenGLEnum dppass) const {
#ifndef NDEBUG
    if (boom::glStencilOpSeparate == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::stencilOpSeparate() failed: OpenGL function \"glStencilOpSeparate\" not loaded");
    }
#endif
    _current();
    boom::glStencilOpSeparate(face, sfail, dpfail, dppass);
}

void OpenGL::texBuffer(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glTexBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texBuffer() failed: OpenGL function \"glTexBuffer\" not loaded");
    }
#endif
    _current();
    boom::glTexBuffer(target, internalformat, buffer);
}

void OpenGL::texBufferRange(boom::OpenGLEnum target, boom::OpenGLEnum internalformat, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glTexBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texBufferRange() failed: OpenGL function \"glTexBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glTexBufferRange(target, internalformat, buffer, offset, size);
}

void OpenGL::texCoord1d(boom::OpenGLDouble s) const {
#ifndef NDEBUG
    if (boom::glTexCoord1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1d() failed: OpenGL function \"glTexCoord1d\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1d(s);
}

void OpenGL::texCoord1dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1dv() failed: OpenGL function \"glTexCoord1dv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1dv(v);
}

void OpenGL::texCoord1f(boom::OpenGLFloat s) const {
#ifndef NDEBUG
    if (boom::glTexCoord1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1f() failed: OpenGL function \"glTexCoord1f\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1f(s);
}

void OpenGL::texCoord1fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1fv() failed: OpenGL function \"glTexCoord1fv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1fv(v);
}

void OpenGL::texCoord1i(boom::OpenGLInt s) const {
#ifndef NDEBUG
    if (boom::glTexCoord1i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1i() failed: OpenGL function \"glTexCoord1i\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1i(s);
}

void OpenGL::texCoord1iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord1iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1iv() failed: OpenGL function \"glTexCoord1iv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1iv(v);
}

void OpenGL::texCoord1s(boom::OpenGLShort s) const {
#ifndef NDEBUG
    if (boom::glTexCoord1s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1s() failed: OpenGL function \"glTexCoord1s\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1s(s);
}

void OpenGL::texCoord1sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord1sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord1sv() failed: OpenGL function \"glTexCoord1sv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord1sv(v);
}

void OpenGL::texCoord2d(boom::OpenGLDouble s, boom::OpenGLDouble t) const {
#ifndef NDEBUG
    if (boom::glTexCoord2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2d() failed: OpenGL function \"glTexCoord2d\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2d(s, t);
}

void OpenGL::texCoord2dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2dv() failed: OpenGL function \"glTexCoord2dv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2dv(v);
}

void OpenGL::texCoord2f(boom::OpenGLFloat s, boom::OpenGLFloat t) const {
#ifndef NDEBUG
    if (boom::glTexCoord2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2f() failed: OpenGL function \"glTexCoord2f\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2f(s, t);
}

void OpenGL::texCoord2fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2fv() failed: OpenGL function \"glTexCoord2fv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2fv(v);
}

void OpenGL::texCoord2i(boom::OpenGLInt s, boom::OpenGLInt t) const {
#ifndef NDEBUG
    if (boom::glTexCoord2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2i() failed: OpenGL function \"glTexCoord2i\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2i(s, t);
}

void OpenGL::texCoord2iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2iv() failed: OpenGL function \"glTexCoord2iv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2iv(v);
}

void OpenGL::texCoord2s(boom::OpenGLShort s, boom::OpenGLShort t) const {
#ifndef NDEBUG
    if (boom::glTexCoord2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2s() failed: OpenGL function \"glTexCoord2s\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2s(s, t);
}

void OpenGL::texCoord2sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord2sv() failed: OpenGL function \"glTexCoord2sv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord2sv(v);
}

void OpenGL::texCoord3d(boom::OpenGLDouble s, boom::OpenGLDouble t, boom::OpenGLDouble r) const {
#ifndef NDEBUG
    if (boom::glTexCoord3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3d() failed: OpenGL function \"glTexCoord3d\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3d(s, t, r);
}

void OpenGL::texCoord3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3dv() failed: OpenGL function \"glTexCoord3dv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3dv(v);
}

void OpenGL::texCoord3f(boom::OpenGLFloat s, boom::OpenGLFloat t, boom::OpenGLFloat r) const {
#ifndef NDEBUG
    if (boom::glTexCoord3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3f() failed: OpenGL function \"glTexCoord3f\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3f(s, t, r);
}

void OpenGL::texCoord3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3fv() failed: OpenGL function \"glTexCoord3fv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3fv(v);
}

void OpenGL::texCoord3i(boom::OpenGLInt s, boom::OpenGLInt t, boom::OpenGLInt r) const {
#ifndef NDEBUG
    if (boom::glTexCoord3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3i() failed: OpenGL function \"glTexCoord3i\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3i(s, t, r);
}

void OpenGL::texCoord3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3iv() failed: OpenGL function \"glTexCoord3iv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3iv(v);
}

void OpenGL::texCoord3s(boom::OpenGLShort s, boom::OpenGLShort t, boom::OpenGLShort r) const {
#ifndef NDEBUG
    if (boom::glTexCoord3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3s() failed: OpenGL function \"glTexCoord3s\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3s(s, t, r);
}

void OpenGL::texCoord3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord3sv() failed: OpenGL function \"glTexCoord3sv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord3sv(v);
}

void OpenGL::texCoord4d(boom::OpenGLDouble s, boom::OpenGLDouble t, boom::OpenGLDouble r, boom::OpenGLDouble q) const {
#ifndef NDEBUG
    if (boom::glTexCoord4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4d() failed: OpenGL function \"glTexCoord4d\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4d(s, t, r, q);
}

void OpenGL::texCoord4dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4dv() failed: OpenGL function \"glTexCoord4dv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4dv(v);
}

void OpenGL::texCoord4f(boom::OpenGLFloat s, boom::OpenGLFloat t, boom::OpenGLFloat r, boom::OpenGLFloat q) const {
#ifndef NDEBUG
    if (boom::glTexCoord4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4f() failed: OpenGL function \"glTexCoord4f\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4f(s, t, r, q);
}

void OpenGL::texCoord4fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4fv() failed: OpenGL function \"glTexCoord4fv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4fv(v);
}

void OpenGL::texCoord4i(boom::OpenGLInt s, boom::OpenGLInt t, boom::OpenGLInt r, boom::OpenGLInt q) const {
#ifndef NDEBUG
    if (boom::glTexCoord4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4i() failed: OpenGL function \"glTexCoord4i\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4i(s, t, r, q);
}

void OpenGL::texCoord4iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4iv() failed: OpenGL function \"glTexCoord4iv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4iv(v);
}

void OpenGL::texCoord4s(boom::OpenGLShort s, boom::OpenGLShort t, boom::OpenGLShort r, boom::OpenGLShort q) const {
#ifndef NDEBUG
    if (boom::glTexCoord4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4s() failed: OpenGL function \"glTexCoord4s\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4s(s, t, r, q);
}

void OpenGL::texCoord4sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glTexCoord4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoord4sv() failed: OpenGL function \"glTexCoord4sv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoord4sv(v);
}

void OpenGL::texCoordP1ui(boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP1ui() failed: OpenGL function \"glTexCoordP1ui\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP1ui(type, coords);
}

void OpenGL::texCoordP1uiv(boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP1uiv() failed: OpenGL function \"glTexCoordP1uiv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP1uiv(type, coords);
}

void OpenGL::texCoordP2ui(boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP2ui() failed: OpenGL function \"glTexCoordP2ui\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP2ui(type, coords);
}

void OpenGL::texCoordP2uiv(boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP2uiv() failed: OpenGL function \"glTexCoordP2uiv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP2uiv(type, coords);
}

void OpenGL::texCoordP3ui(boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP3ui() failed: OpenGL function \"glTexCoordP3ui\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP3ui(type, coords);
}

void OpenGL::texCoordP3uiv(boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP3uiv() failed: OpenGL function \"glTexCoordP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP3uiv(type, coords);
}

void OpenGL::texCoordP4ui(boom::OpenGLEnum type, boom::OpenGLUint coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP4ui() failed: OpenGL function \"glTexCoordP4ui\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP4ui(type, coords);
}

void OpenGL::texCoordP4uiv(boom::OpenGLEnum type, boom::OpenGLUint const* coords) const {
#ifndef NDEBUG
    if (boom::glTexCoordP4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordP4uiv() failed: OpenGL function \"glTexCoordP4uiv\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordP4uiv(type, coords);
}

void OpenGL::texCoordPointer(boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glTexCoordPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texCoordPointer() failed: OpenGL function \"glTexCoordPointer\" not loaded");
    }
#endif
    _current();
    boom::glTexCoordPointer(size, type, stride, pointer);
}

void OpenGL::texEnvf(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glTexEnvf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnvf() failed: OpenGL function \"glTexEnvf\" not loaded");
    }
#endif
    _current();
    boom::glTexEnvf(target, pname, param);
}

void OpenGL::texEnvfv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glTexEnvfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnvfv() failed: OpenGL function \"glTexEnvfv\" not loaded");
    }
#endif
    _current();
    boom::glTexEnvfv(target, pname, params);
}

void OpenGL::texEnvi(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glTexEnvi == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnvi() failed: OpenGL function \"glTexEnvi\" not loaded");
    }
#endif
    _current();
    boom::glTexEnvi(target, pname, param);
}

void OpenGL::texEnviv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glTexEnviv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnviv() failed: OpenGL function \"glTexEnviv\" not loaded");
    }
#endif
    _current();
    boom::glTexEnviv(target, pname, params);
}

void OpenGL::texEnvx(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glTexEnvx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnvx() failed: OpenGL function \"glTexEnvx\" not loaded");
    }
#endif
    _current();
    boom::glTexEnvx(target, pname, param);
}

void OpenGL::texEnvxv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed const* params) const {
#ifndef NDEBUG
    if (boom::glTexEnvxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texEnvxv() failed: OpenGL function \"glTexEnvxv\" not loaded");
    }
#endif
    _current();
    boom::glTexEnvxv(target, pname, params);
}

void OpenGL::texGend(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLDouble param) const {
#ifndef NDEBUG
    if (boom::glTexGend == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGend() failed: OpenGL function \"glTexGend\" not loaded");
    }
#endif
    _current();
    boom::glTexGend(coord, pname, param);
}

void OpenGL::texGendv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLDouble const* params) const {
#ifndef NDEBUG
    if (boom::glTexGendv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGendv() failed: OpenGL function \"glTexGendv\" not loaded");
    }
#endif
    _current();
    boom::glTexGendv(coord, pname, params);
}

void OpenGL::texGenf(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glTexGenf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGenf() failed: OpenGL function \"glTexGenf\" not loaded");
    }
#endif
    _current();
    boom::glTexGenf(coord, pname, param);
}

void OpenGL::texGenfv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glTexGenfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGenfv() failed: OpenGL function \"glTexGenfv\" not loaded");
    }
#endif
    _current();
    boom::glTexGenfv(coord, pname, params);
}

void OpenGL::texGeni(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glTexGeni == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGeni() failed: OpenGL function \"glTexGeni\" not loaded");
    }
#endif
    _current();
    boom::glTexGeni(coord, pname, param);
}

void OpenGL::texGeniv(boom::OpenGLEnum coord, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glTexGeniv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texGeniv() failed: OpenGL function \"glTexGeniv\" not loaded");
    }
#endif
    _current();
    boom::glTexGeniv(coord, pname, params);
}

void OpenGL::texImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt internalformat, boom::OpenGLSizei width, boom::OpenGLInt border, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage1D() failed: OpenGL function \"glTexImage1D\" not loaded");
    }
#endif
    _current();
    boom::glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

void OpenGL::texImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLInt border, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage2D() failed: OpenGL function \"glTexImage2D\" not loaded");
    }
#endif
    _current();
    boom::glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void OpenGL::texImage3D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLInt border, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage3D() failed: OpenGL function \"glTexImage3D\" not loaded");
    }
#endif
    _current();
    boom::glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
}

#ifdef __APPLE__

void OpenGL::texImage2DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLInt internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexImage2DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage2DMultisample() failed: OpenGL function \"glTexImage2DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::texImage3DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLInt internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexImage3DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage3DMultisample() failed: OpenGL function \"glTexImage3DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

#else

void OpenGL::texImage2DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexImage2DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage2DMultisample() failed: OpenGL function \"glTexImage2DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::texImage3DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexImage3DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texImage3DMultisample() failed: OpenGL function \"glTexImage3DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

#endif

void OpenGL::texParameterIiv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glTexParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterIiv() failed: OpenGL function \"glTexParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterIiv(target, pname, params);
}

void OpenGL::texParameterIuiv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLUint const* params) const {
#ifndef NDEBUG
    if (boom::glTexParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterIuiv() failed: OpenGL function \"glTexParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterIuiv(target, pname, params);
}

void OpenGL::texParameterf(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glTexParameterf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterf() failed: OpenGL function \"glTexParameterf\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterf(target, pname, param);
}

void OpenGL::texParameterfv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFloat const* params) const {
#ifndef NDEBUG
    if (boom::glTexParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterfv() failed: OpenGL function \"glTexParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterfv(target, pname, params);
}

void OpenGL::texParameteri(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glTexParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameteri() failed: OpenGL function \"glTexParameteri\" not loaded");
    }
#endif
    _current();
    boom::glTexParameteri(target, pname, param);
}

void OpenGL::texParameteriv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glTexParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameteriv() failed: OpenGL function \"glTexParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glTexParameteriv(target, pname, params);
}

void OpenGL::texParameterx(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed param) const {
#ifndef NDEBUG
    if (boom::glTexParameterx == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterx() failed: OpenGL function \"glTexParameterx\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterx(target, pname, param);
}

void OpenGL::texParameterxv(boom::OpenGLEnum target, boom::OpenGLEnum pname, boom::OpenGLFixed const* params) const {
#ifndef NDEBUG
    if (boom::glTexParameterxv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texParameterxv() failed: OpenGL function \"glTexParameterxv\" not loaded");
    }
#endif
    _current();
    boom::glTexParameterxv(target, pname, params);
}

void OpenGL::texStorage1D(boom::OpenGLEnum target, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width) const {
#ifndef NDEBUG
    if (boom::glTexStorage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texStorage1D() failed: OpenGL function \"glTexStorage1D\" not loaded");
    }
#endif
    _current();
    boom::glTexStorage1D(target, levels, internalformat, width);
}

void OpenGL::texStorage2D(boom::OpenGLEnum target, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glTexStorage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texStorage2D() failed: OpenGL function \"glTexStorage2D\" not loaded");
    }
#endif
    _current();
    boom::glTexStorage2D(target, levels, internalformat, width, height);
}

void OpenGL::texStorage2DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexStorage2DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texStorage2DMultisample() failed: OpenGL function \"glTexStorage2DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::texStorage3D(boom::OpenGLEnum target, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth) const {
#ifndef NDEBUG
    if (boom::glTexStorage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texStorage3D() failed: OpenGL function \"glTexStorage3D\" not loaded");
    }
#endif
    _current();
    boom::glTexStorage3D(target, levels, internalformat, width, height, depth);
}

void OpenGL::texStorage3DMultisample(boom::OpenGLEnum target, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTexStorage3DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texStorage3DMultisample() failed: OpenGL function \"glTexStorage3DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void OpenGL::texSubImage1D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLSizei width, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texSubImage1D() failed: OpenGL function \"glTexSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void OpenGL::texSubImage2D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texSubImage2D() failed: OpenGL function \"glTexSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void OpenGL::texSubImage3D(boom::OpenGLEnum target, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTexSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::texSubImage3D() failed: OpenGL function \"glTexSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void OpenGL::textureBarrier() const {
#ifndef NDEBUG
    if (boom::glTextureBarrier == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureBarrier() failed: OpenGL function \"glTextureBarrier\" not loaded");
    }
#endif
    _current();
    boom::glTextureBarrier();
}

void OpenGL::textureBuffer(boom::OpenGLUint texture, boom::OpenGLEnum internalformat, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glTextureBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureBuffer() failed: OpenGL function \"glTextureBuffer\" not loaded");
    }
#endif
    _current();
    boom::glTextureBuffer(texture, internalformat, buffer);
}

void OpenGL::textureBufferRange(boom::OpenGLUint texture, boom::OpenGLEnum internalformat, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glTextureBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureBufferRange() failed: OpenGL function \"glTextureBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glTextureBufferRange(texture, internalformat, buffer, offset, size);
}

void OpenGL::textureParameterIiv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLInt const* params) const {
#ifndef NDEBUG
    if (boom::glTextureParameterIiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameterIiv() failed: OpenGL function \"glTextureParameterIiv\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameterIiv(texture, pname, params);
}

void OpenGL::textureParameterIuiv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLUint const* params) const {
#ifndef NDEBUG
    if (boom::glTextureParameterIuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameterIuiv() failed: OpenGL function \"glTextureParameterIuiv\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameterIuiv(texture, pname, params);
}

void OpenGL::textureParameterf(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLFloat param) const {
#ifndef NDEBUG
    if (boom::glTextureParameterf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameterf() failed: OpenGL function \"glTextureParameterf\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameterf(texture, pname, param);
}

void OpenGL::textureParameterfv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLFloat const* param) const {
#ifndef NDEBUG
    if (boom::glTextureParameterfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameterfv() failed: OpenGL function \"glTextureParameterfv\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameterfv(texture, pname, param);
}

void OpenGL::textureParameteri(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLInt param) const {
#ifndef NDEBUG
    if (boom::glTextureParameteri == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameteri() failed: OpenGL function \"glTextureParameteri\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameteri(texture, pname, param);
}

void OpenGL::textureParameteriv(boom::OpenGLUint texture, boom::OpenGLEnum pname, boom::OpenGLInt const* param) const {
#ifndef NDEBUG
    if (boom::glTextureParameteriv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureParameteriv() failed: OpenGL function \"glTextureParameteriv\" not loaded");
    }
#endif
    _current();
    boom::glTextureParameteriv(texture, pname, param);
}

void OpenGL::textureStorage1D(boom::OpenGLUint texture, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width) const {
#ifndef NDEBUG
    if (boom::glTextureStorage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureStorage1D() failed: OpenGL function \"glTextureStorage1D\" not loaded");
    }
#endif
    _current();
    boom::glTextureStorage1D(texture, levels, internalformat, width);
}

void OpenGL::textureStorage2D(boom::OpenGLUint texture, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glTextureStorage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureStorage2D() failed: OpenGL function \"glTextureStorage2D\" not loaded");
    }
#endif
    _current();
    boom::glTextureStorage2D(texture, levels, internalformat, width, height);
}

void OpenGL::textureStorage2DMultisample(boom::OpenGLUint texture, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTextureStorage2DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureStorage2DMultisample() failed: OpenGL function \"glTextureStorage2DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
}

void OpenGL::textureStorage3D(boom::OpenGLUint texture, boom::OpenGLSizei levels, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth) const {
#ifndef NDEBUG
    if (boom::glTextureStorage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureStorage3D() failed: OpenGL function \"glTextureStorage3D\" not loaded");
    }
#endif
    _current();
    boom::glTextureStorage3D(texture, levels, internalformat, width, height, depth);
}

void OpenGL::textureStorage3DMultisample(boom::OpenGLUint texture, boom::OpenGLSizei samples, boom::OpenGLEnum internalformat, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLBoolean fixedsamplelocations) const {
#ifndef NDEBUG
    if (boom::glTextureStorage3DMultisample == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureStorage3DMultisample() failed: OpenGL function \"glTextureStorage3DMultisample\" not loaded");
    }
#endif
    _current();
    boom::glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

void OpenGL::textureSubImage1D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLSizei width, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTextureSubImage1D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureSubImage1D() failed: OpenGL function \"glTextureSubImage1D\" not loaded");
    }
#endif
    _current();
    boom::glTextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
}

void OpenGL::textureSubImage2D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTextureSubImage2D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureSubImage2D() failed: OpenGL function \"glTextureSubImage2D\" not loaded");
    }
#endif
    _current();
    boom::glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
}

void OpenGL::textureSubImage3D(boom::OpenGLUint texture, boom::OpenGLInt level, boom::OpenGLInt xoffset, boom::OpenGLInt yoffset, boom::OpenGLInt zoffset, boom::OpenGLSizei width, boom::OpenGLSizei height, boom::OpenGLSizei depth, boom::OpenGLEnum format, boom::OpenGLEnum type, void const* pixels) const {
#ifndef NDEBUG
    if (boom::glTextureSubImage3D == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureSubImage3D() failed: OpenGL function \"glTextureSubImage3D\" not loaded");
    }
#endif
    _current();
    boom::glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void OpenGL::textureView(boom::OpenGLUint texture, boom::OpenGLEnum target, boom::OpenGLUint origtexture, boom::OpenGLEnum internalformat, boom::OpenGLUint minlevel, boom::OpenGLUint numlevels, boom::OpenGLUint minlayer, boom::OpenGLUint numlayers) const {
#ifndef NDEBUG
    if (boom::glTextureView == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::textureView() failed: OpenGL function \"glTextureView\" not loaded");
    }
#endif
    _current();
    boom::glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

void OpenGL::transformFeedbackBufferBase(boom::OpenGLUint xfb, boom::OpenGLUint index, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glTransformFeedbackBufferBase == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::transformFeedbackBufferBase() failed: OpenGL function \"glTransformFeedbackBufferBase\" not loaded");
    }
#endif
    _current();
    boom::glTransformFeedbackBufferBase(xfb, index, buffer);
}

void OpenGL::transformFeedbackBufferRange(boom::OpenGLUint xfb, boom::OpenGLUint index, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizeiptr size) const {
#ifndef NDEBUG
    if (boom::glTransformFeedbackBufferRange == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::transformFeedbackBufferRange() failed: OpenGL function \"glTransformFeedbackBufferRange\" not loaded");
    }
#endif
    _current();
    boom::glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
}

void OpenGL::transformFeedbackVaryings(boom::OpenGLUint program, boom::OpenGLSizei count, boom::OpenGLChar const* const* varyings, boom::OpenGLEnum bufferMode) const {
#ifndef NDEBUG
    if (boom::glTransformFeedbackVaryings == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::transformFeedbackVaryings() failed: OpenGL function \"glTransformFeedbackVaryings\" not loaded");
    }
#endif
    _current();
    boom::glTransformFeedbackVaryings(program, count, varyings, bufferMode);
}

void OpenGL::translated(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glTranslated == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::translated() failed: OpenGL function \"glTranslated\" not loaded");
    }
#endif
    _current();
    boom::glTranslated(x, y, z);
}

void OpenGL::translatef(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glTranslatef == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::translatef() failed: OpenGL function \"glTranslatef\" not loaded");
    }
#endif
    _current();
    boom::glTranslatef(x, y, z);
}

void OpenGL::translatex(boom::OpenGLFixed x, boom::OpenGLFixed y, boom::OpenGLFixed z) const {
#ifndef NDEBUG
    if (boom::glTranslatex == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::translatex() failed: OpenGL function \"glTranslatex\" not loaded");
    }
#endif
    _current();
    boom::glTranslatex(x, y, z);
}

void OpenGL::uniform1d(boom::OpenGLInt location, boom::OpenGLDouble x) const {
#ifndef NDEBUG
    if (boom::glUniform1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1d() failed: OpenGL function \"glUniform1d\" not loaded");
    }
#endif
    _current();
    boom::glUniform1d(location, x);
}

void OpenGL::uniform1dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniform1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1dv() failed: OpenGL function \"glUniform1dv\" not loaded");
    }
#endif
    _current();
    boom::glUniform1dv(location, count, value);
}

void OpenGL::uniform1f(boom::OpenGLInt location, boom::OpenGLFloat v0) const {
#ifndef NDEBUG
    if (boom::glUniform1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1f() failed: OpenGL function \"glUniform1f\" not loaded");
    }
#endif
    _current();
    boom::glUniform1f(location, v0);
}

void OpenGL::uniform1fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniform1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1fv() failed: OpenGL function \"glUniform1fv\" not loaded");
    }
#endif
    _current();
    boom::glUniform1fv(location, count, value);
}

void OpenGL::uniform1i(boom::OpenGLInt location, boom::OpenGLInt v0) const {
#ifndef NDEBUG
    if (boom::glUniform1i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1i() failed: OpenGL function \"glUniform1i\" not loaded");
    }
#endif
    _current();
    boom::glUniform1i(location, v0);
}

void OpenGL::uniform1iv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glUniform1iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1iv() failed: OpenGL function \"glUniform1iv\" not loaded");
    }
#endif
    _current();
    boom::glUniform1iv(location, count, value);
}

void OpenGL::uniform1ui(boom::OpenGLInt location, boom::OpenGLUint v0) const {
#ifndef NDEBUG
    if (boom::glUniform1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1ui() failed: OpenGL function \"glUniform1ui\" not loaded");
    }
#endif
    _current();
    boom::glUniform1ui(location, v0);
}

void OpenGL::uniform1uiv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glUniform1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform1uiv() failed: OpenGL function \"glUniform1uiv\" not loaded");
    }
#endif
    _current();
    boom::glUniform1uiv(location, count, value);
}

void OpenGL::uniform2d(boom::OpenGLInt location, boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glUniform2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2d() failed: OpenGL function \"glUniform2d\" not loaded");
    }
#endif
    _current();
    boom::glUniform2d(location, x, y);
}

void OpenGL::uniform2dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniform2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2dv() failed: OpenGL function \"glUniform2dv\" not loaded");
    }
#endif
    _current();
    boom::glUniform2dv(location, count, value);
}

void OpenGL::uniform2f(boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1) const {
#ifndef NDEBUG
    if (boom::glUniform2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2f() failed: OpenGL function \"glUniform2f\" not loaded");
    }
#endif
    _current();
    boom::glUniform2f(location, v0, v1);
}

void OpenGL::uniform2fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniform2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2fv() failed: OpenGL function \"glUniform2fv\" not loaded");
    }
#endif
    _current();
    boom::glUniform2fv(location, count, value);
}

void OpenGL::uniform2i(boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1) const {
#ifndef NDEBUG
    if (boom::glUniform2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2i() failed: OpenGL function \"glUniform2i\" not loaded");
    }
#endif
    _current();
    boom::glUniform2i(location, v0, v1);
}

void OpenGL::uniform2iv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glUniform2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2iv() failed: OpenGL function \"glUniform2iv\" not loaded");
    }
#endif
    _current();
    boom::glUniform2iv(location, count, value);
}

void OpenGL::uniform2ui(boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1) const {
#ifndef NDEBUG
    if (boom::glUniform2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2ui() failed: OpenGL function \"glUniform2ui\" not loaded");
    }
#endif
    _current();
    boom::glUniform2ui(location, v0, v1);
}

void OpenGL::uniform2uiv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glUniform2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform2uiv() failed: OpenGL function \"glUniform2uiv\" not loaded");
    }
#endif
    _current();
    boom::glUniform2uiv(location, count, value);
}

void OpenGL::uniform3d(boom::OpenGLInt location, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glUniform3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3d() failed: OpenGL function \"glUniform3d\" not loaded");
    }
#endif
    _current();
    boom::glUniform3d(location, x, y, z);
}

void OpenGL::uniform3dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniform3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3dv() failed: OpenGL function \"glUniform3dv\" not loaded");
    }
#endif
    _current();
    boom::glUniform3dv(location, count, value);
}

void OpenGL::uniform3f(boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1, boom::OpenGLFloat v2) const {
#ifndef NDEBUG
    if (boom::glUniform3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3f() failed: OpenGL function \"glUniform3f\" not loaded");
    }
#endif
    _current();
    boom::glUniform3f(location, v0, v1, v2);
}

void OpenGL::uniform3fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniform3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3fv() failed: OpenGL function \"glUniform3fv\" not loaded");
    }
#endif
    _current();
    boom::glUniform3fv(location, count, value);
}

void OpenGL::uniform3i(boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1, boom::OpenGLInt v2) const {
#ifndef NDEBUG
    if (boom::glUniform3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3i() failed: OpenGL function \"glUniform3i\" not loaded");
    }
#endif
    _current();
    boom::glUniform3i(location, v0, v1, v2);
}

void OpenGL::uniform3iv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glUniform3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3iv() failed: OpenGL function \"glUniform3iv\" not loaded");
    }
#endif
    _current();
    boom::glUniform3iv(location, count, value);
}

void OpenGL::uniform3ui(boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1, boom::OpenGLUint v2) const {
#ifndef NDEBUG
    if (boom::glUniform3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3ui() failed: OpenGL function \"glUniform3ui\" not loaded");
    }
#endif
    _current();
    boom::glUniform3ui(location, v0, v1, v2);
}

void OpenGL::uniform3uiv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glUniform3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform3uiv() failed: OpenGL function \"glUniform3uiv\" not loaded");
    }
#endif
    _current();
    boom::glUniform3uiv(location, count, value);
}

void OpenGL::uniform4d(boom::OpenGLInt location, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z, boom::OpenGLDouble w) const {
#ifndef NDEBUG
    if (boom::glUniform4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4d() failed: OpenGL function \"glUniform4d\" not loaded");
    }
#endif
    _current();
    boom::glUniform4d(location, x, y, z, w);
}

void OpenGL::uniform4dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniform4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4dv() failed: OpenGL function \"glUniform4dv\" not loaded");
    }
#endif
    _current();
    boom::glUniform4dv(location, count, value);
}

void OpenGL::uniform4f(boom::OpenGLInt location, boom::OpenGLFloat v0, boom::OpenGLFloat v1, boom::OpenGLFloat v2, boom::OpenGLFloat v3) const {
#ifndef NDEBUG
    if (boom::glUniform4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4f() failed: OpenGL function \"glUniform4f\" not loaded");
    }
#endif
    _current();
    boom::glUniform4f(location, v0, v1, v2, v3);
}

void OpenGL::uniform4fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniform4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4fv() failed: OpenGL function \"glUniform4fv\" not loaded");
    }
#endif
    _current();
    boom::glUniform4fv(location, count, value);
}

void OpenGL::uniform4i(boom::OpenGLInt location, boom::OpenGLInt v0, boom::OpenGLInt v1, boom::OpenGLInt v2, boom::OpenGLInt v3) const {
#ifndef NDEBUG
    if (boom::glUniform4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4i() failed: OpenGL function \"glUniform4i\" not loaded");
    }
#endif
    _current();
    boom::glUniform4i(location, v0, v1, v2, v3);
}

void OpenGL::uniform4iv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLInt const* value) const {
#ifndef NDEBUG
    if (boom::glUniform4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4iv() failed: OpenGL function \"glUniform4iv\" not loaded");
    }
#endif
    _current();
    boom::glUniform4iv(location, count, value);
}

void OpenGL::uniform4ui(boom::OpenGLInt location, boom::OpenGLUint v0, boom::OpenGLUint v1, boom::OpenGLUint v2, boom::OpenGLUint v3) const {
#ifndef NDEBUG
    if (boom::glUniform4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4ui() failed: OpenGL function \"glUniform4ui\" not loaded");
    }
#endif
    _current();
    boom::glUniform4ui(location, v0, v1, v2, v3);
}

void OpenGL::uniform4uiv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glUniform4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniform4uiv() failed: OpenGL function \"glUniform4uiv\" not loaded");
    }
#endif
    _current();
    boom::glUniform4uiv(location, count, value);
}

void OpenGL::uniformBlockBinding(boom::OpenGLUint program, boom::OpenGLUint uniformBlockIndex, boom::OpenGLUint uniformBlockBinding) const {
#ifndef NDEBUG
    if (boom::glUniformBlockBinding == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformBlockBinding() failed: OpenGL function \"glUniformBlockBinding\" not loaded");
    }
#endif
    _current();
    boom::glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

void OpenGL::uniformMatrix2dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2dv() failed: OpenGL function \"glUniformMatrix2dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2fv() failed: OpenGL function \"glUniformMatrix2fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x3dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2x3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2x3dv() failed: OpenGL function \"glUniformMatrix2x3dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2x3dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x3fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2x3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2x3fv() failed: OpenGL function \"glUniformMatrix2x3fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2x3fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x4dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2x4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2x4dv() failed: OpenGL function \"glUniformMatrix2x4dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2x4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix2x4fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix2x4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix2x4fv() failed: OpenGL function \"glUniformMatrix2x4fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix2x4fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3dv() failed: OpenGL function \"glUniformMatrix3dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3fv() failed: OpenGL function \"glUniformMatrix3fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x2dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3x2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3x2dv() failed: OpenGL function \"glUniformMatrix3x2dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3x2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x2fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3x2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3x2fv() failed: OpenGL function \"glUniformMatrix3x2fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3x2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x4dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3x4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3x4dv() failed: OpenGL function \"glUniformMatrix3x4dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3x4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix3x4fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix3x4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix3x4fv() failed: OpenGL function \"glUniformMatrix3x4fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix3x4fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4dv() failed: OpenGL function \"glUniformMatrix4dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4fv() failed: OpenGL function \"glUniformMatrix4fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x2dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4x2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4x2dv() failed: OpenGL function \"glUniformMatrix4x2dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4x2dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x2fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4x2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4x2fv() failed: OpenGL function \"glUniformMatrix4x2fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4x2fv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x3dv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLDouble const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4x3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4x3dv() failed: OpenGL function \"glUniformMatrix4x3dv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4x3dv(location, count, transpose, value);
}

void OpenGL::uniformMatrix4x3fv(boom::OpenGLInt location, boom::OpenGLSizei count, boom::OpenGLBoolean transpose, boom::OpenGLFloat const* value) const {
#ifndef NDEBUG
    if (boom::glUniformMatrix4x3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformMatrix4x3fv() failed: OpenGL function \"glUniformMatrix4x3fv\" not loaded");
    }
#endif
    _current();
    boom::glUniformMatrix4x3fv(location, count, transpose, value);
}

void OpenGL::uniformSubroutinesuiv(boom::OpenGLEnum shadertype, boom::OpenGLSizei count, boom::OpenGLUint const* indices) const {
#ifndef NDEBUG
    if (boom::glUniformSubroutinesuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::uniformSubroutinesuiv() failed: OpenGL function \"glUniformSubroutinesuiv\" not loaded");
    }
#endif
    _current();
    boom::glUniformSubroutinesuiv(shadertype, count, indices);
}

boom::OpenGLBoolean OpenGL::unmapBuffer(boom::OpenGLEnum target) const {
#ifndef NDEBUG
    if (boom::glUnmapBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::unmapBuffer() failed: OpenGL function \"glUnmapBuffer\" not loaded");
    }
#endif
    _current();
    return boom::glUnmapBuffer(target);
}

boom::OpenGLBoolean OpenGL::unmapNamedBuffer(boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glUnmapNamedBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::unmapNamedBuffer() failed: OpenGL function \"glUnmapNamedBuffer\" not loaded");
    }
#endif
    _current();
    return boom::glUnmapNamedBuffer(buffer);
}

void OpenGL::useProgram(boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glUseProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::useProgram() failed: OpenGL function \"glUseProgram\" not loaded");
    }
#endif
    _current();
    boom::glUseProgram(program);
}

void OpenGL::useProgramStages(boom::OpenGLUint pipeline, boom::OpenGLBitfield stages, boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glUseProgramStages == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::useProgramStages() failed: OpenGL function \"glUseProgramStages\" not loaded");
    }
#endif
    _current();
    boom::glUseProgramStages(pipeline, stages, program);
}

void OpenGL::validateProgram(boom::OpenGLUint program) const {
#ifndef NDEBUG
    if (boom::glValidateProgram == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::validateProgram() failed: OpenGL function \"glValidateProgram\" not loaded");
    }
#endif
    _current();
    boom::glValidateProgram(program);
}

void OpenGL::validateProgramPipeline(boom::OpenGLUint pipeline) const {
#ifndef NDEBUG
    if (boom::glValidateProgramPipeline == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::validateProgramPipeline() failed: OpenGL function \"glValidateProgramPipeline\" not loaded");
    }
#endif
    _current();
    boom::glValidateProgramPipeline(pipeline);
}

void OpenGL::vertex2d(boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glVertex2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2d() failed: OpenGL function \"glVertex2d\" not loaded");
    }
#endif
    _current();
    boom::glVertex2d(x, y);
}

void OpenGL::vertex2dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertex2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2dv() failed: OpenGL function \"glVertex2dv\" not loaded");
    }
#endif
    _current();
    boom::glVertex2dv(v);
}

void OpenGL::vertex2f(boom::OpenGLFloat x, boom::OpenGLFloat y) const {
#ifndef NDEBUG
    if (boom::glVertex2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2f() failed: OpenGL function \"glVertex2f\" not loaded");
    }
#endif
    _current();
    boom::glVertex2f(x, y);
}

void OpenGL::vertex2fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertex2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2fv() failed: OpenGL function \"glVertex2fv\" not loaded");
    }
#endif
    _current();
    boom::glVertex2fv(v);
}

void OpenGL::vertex2i(boom::OpenGLInt x, boom::OpenGLInt y) const {
#ifndef NDEBUG
    if (boom::glVertex2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2i() failed: OpenGL function \"glVertex2i\" not loaded");
    }
#endif
    _current();
    boom::glVertex2i(x, y);
}

void OpenGL::vertex2iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertex2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2iv() failed: OpenGL function \"glVertex2iv\" not loaded");
    }
#endif
    _current();
    boom::glVertex2iv(v);
}

void OpenGL::vertex2s(boom::OpenGLShort x, boom::OpenGLShort y) const {
#ifndef NDEBUG
    if (boom::glVertex2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2s() failed: OpenGL function \"glVertex2s\" not loaded");
    }
#endif
    _current();
    boom::glVertex2s(x, y);
}

void OpenGL::vertex2sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertex2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex2sv() failed: OpenGL function \"glVertex2sv\" not loaded");
    }
#endif
    _current();
    boom::glVertex2sv(v);
}

void OpenGL::vertex3d(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glVertex3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3d() failed: OpenGL function \"glVertex3d\" not loaded");
    }
#endif
    _current();
    boom::glVertex3d(x, y, z);
}

void OpenGL::vertex3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertex3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3dv() failed: OpenGL function \"glVertex3dv\" not loaded");
    }
#endif
    _current();
    boom::glVertex3dv(v);
}

void OpenGL::vertex3f(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glVertex3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3f() failed: OpenGL function \"glVertex3f\" not loaded");
    }
#endif
    _current();
    boom::glVertex3f(x, y, z);
}

void OpenGL::vertex3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertex3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3fv() failed: OpenGL function \"glVertex3fv\" not loaded");
    }
#endif
    _current();
    boom::glVertex3fv(v);
}

void OpenGL::vertex3i(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z) const {
#ifndef NDEBUG
    if (boom::glVertex3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3i() failed: OpenGL function \"glVertex3i\" not loaded");
    }
#endif
    _current();
    boom::glVertex3i(x, y, z);
}

void OpenGL::vertex3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertex3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3iv() failed: OpenGL function \"glVertex3iv\" not loaded");
    }
#endif
    _current();
    boom::glVertex3iv(v);
}

void OpenGL::vertex3s(boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z) const {
#ifndef NDEBUG
    if (boom::glVertex3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3s() failed: OpenGL function \"glVertex3s\" not loaded");
    }
#endif
    _current();
    boom::glVertex3s(x, y, z);
}

void OpenGL::vertex3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertex3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex3sv() failed: OpenGL function \"glVertex3sv\" not loaded");
    }
#endif
    _current();
    boom::glVertex3sv(v);
}

void OpenGL::vertex4d(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z, boom::OpenGLDouble w) const {
#ifndef NDEBUG
    if (boom::glVertex4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4d() failed: OpenGL function \"glVertex4d\" not loaded");
    }
#endif
    _current();
    boom::glVertex4d(x, y, z, w);
}

void OpenGL::vertex4dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertex4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4dv() failed: OpenGL function \"glVertex4dv\" not loaded");
    }
#endif
    _current();
    boom::glVertex4dv(v);
}

void OpenGL::vertex4f(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z, boom::OpenGLFloat w) const {
#ifndef NDEBUG
    if (boom::glVertex4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4f() failed: OpenGL function \"glVertex4f\" not loaded");
    }
#endif
    _current();
    boom::glVertex4f(x, y, z, w);
}

void OpenGL::vertex4fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertex4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4fv() failed: OpenGL function \"glVertex4fv\" not loaded");
    }
#endif
    _current();
    boom::glVertex4fv(v);
}

void OpenGL::vertex4i(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z, boom::OpenGLInt w) const {
#ifndef NDEBUG
    if (boom::glVertex4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4i() failed: OpenGL function \"glVertex4i\" not loaded");
    }
#endif
    _current();
    boom::glVertex4i(x, y, z, w);
}

void OpenGL::vertex4iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertex4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4iv() failed: OpenGL function \"glVertex4iv\" not loaded");
    }
#endif
    _current();
    boom::glVertex4iv(v);
}

void OpenGL::vertex4s(boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z, boom::OpenGLShort w) const {
#ifndef NDEBUG
    if (boom::glVertex4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4s() failed: OpenGL function \"glVertex4s\" not loaded");
    }
#endif
    _current();
    boom::glVertex4s(x, y, z, w);
}

void OpenGL::vertex4sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertex4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertex4sv() failed: OpenGL function \"glVertex4sv\" not loaded");
    }
#endif
    _current();
    boom::glVertex4sv(v);
}

void OpenGL::vertexArrayAttribBinding(boom::OpenGLUint vaobj, boom::OpenGLUint attribindex, boom::OpenGLUint bindingindex) const {
#ifndef NDEBUG
    if (boom::glVertexArrayAttribBinding == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayAttribBinding() failed: OpenGL function \"glVertexArrayAttribBinding\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
}

void OpenGL::vertexArrayAttribFormat(boom::OpenGLUint vaobj, boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexArrayAttribFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayAttribFormat() failed: OpenGL function \"glVertexArrayAttribFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
}

void OpenGL::vertexArrayAttribIFormat(boom::OpenGLUint vaobj, boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexArrayAttribIFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayAttribIFormat() failed: OpenGL function \"glVertexArrayAttribIFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
}

void OpenGL::vertexArrayAttribLFormat(boom::OpenGLUint vaobj, boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexArrayAttribLFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayAttribLFormat() failed: OpenGL function \"glVertexArrayAttribLFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
}

void OpenGL::vertexArrayBindingDivisor(boom::OpenGLUint vaobj, boom::OpenGLUint bindingindex, boom::OpenGLUint divisor) const {
#ifndef NDEBUG
    if (boom::glVertexArrayBindingDivisor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayBindingDivisor() failed: OpenGL function \"glVertexArrayBindingDivisor\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
}

void OpenGL::vertexArrayElementBuffer(boom::OpenGLUint vaobj, boom::OpenGLUint buffer) const {
#ifndef NDEBUG
    if (boom::glVertexArrayElementBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayElementBuffer() failed: OpenGL function \"glVertexArrayElementBuffer\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayElementBuffer(vaobj, buffer);
}

void OpenGL::vertexArrayVertexBuffer(boom::OpenGLUint vaobj, boom::OpenGLUint bindingindex, boom::OpenGLUint buffer, boom::OpenGLIntptr offset, boom::OpenGLSizei stride) const {
#ifndef NDEBUG
    if (boom::glVertexArrayVertexBuffer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayVertexBuffer() failed: OpenGL function \"glVertexArrayVertexBuffer\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
}

void OpenGL::vertexArrayVertexBuffers(boom::OpenGLUint vaobj, boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLUint const* buffers, boom::OpenGLIntptr const* offsets, boom::OpenGLSizei const* strides) const {
#ifndef NDEBUG
    if (boom::glVertexArrayVertexBuffers == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexArrayVertexBuffers() failed: OpenGL function \"glVertexArrayVertexBuffers\" not loaded");
    }
#endif
    _current();
    boom::glVertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
}

void OpenGL::vertexAttrib1d(boom::OpenGLUint index, boom::OpenGLDouble x) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1d() failed: OpenGL function \"glVertexAttrib1d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1d(index, x);
}

void OpenGL::vertexAttrib1dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1dv() failed: OpenGL function \"glVertexAttrib1dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1dv(index, v);
}

void OpenGL::vertexAttrib1f(boom::OpenGLUint index, boom::OpenGLFloat x) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1f() failed: OpenGL function \"glVertexAttrib1f\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1f(index, x);
}

void OpenGL::vertexAttrib1fv(boom::OpenGLUint index, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1fv() failed: OpenGL function \"glVertexAttrib1fv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1fv(index, v);
}

void OpenGL::vertexAttrib1s(boom::OpenGLUint index, boom::OpenGLShort x) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1s() failed: OpenGL function \"glVertexAttrib1s\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1s(index, x);
}

void OpenGL::vertexAttrib1sv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib1sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib1sv() failed: OpenGL function \"glVertexAttrib1sv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib1sv(index, v);
}

void OpenGL::vertexAttrib2d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2d() failed: OpenGL function \"glVertexAttrib2d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2d(index, x, y);
}

void OpenGL::vertexAttrib2dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2dv() failed: OpenGL function \"glVertexAttrib2dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2dv(index, v);
}

void OpenGL::vertexAttrib2f(boom::OpenGLUint index, boom::OpenGLFloat x, boom::OpenGLFloat y) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2f() failed: OpenGL function \"glVertexAttrib2f\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2f(index, x, y);
}

void OpenGL::vertexAttrib2fv(boom::OpenGLUint index, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2fv() failed: OpenGL function \"glVertexAttrib2fv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2fv(index, v);
}

void OpenGL::vertexAttrib2s(boom::OpenGLUint index, boom::OpenGLShort x, boom::OpenGLShort y) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2s() failed: OpenGL function \"glVertexAttrib2s\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2s(index, x, y);
}

void OpenGL::vertexAttrib2sv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib2sv() failed: OpenGL function \"glVertexAttrib2sv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib2sv(index, v);
}

void OpenGL::vertexAttrib3d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3d() failed: OpenGL function \"glVertexAttrib3d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3d(index, x, y, z);
}

void OpenGL::vertexAttrib3dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3dv() failed: OpenGL function \"glVertexAttrib3dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3dv(index, v);
}

void OpenGL::vertexAttrib3f(boom::OpenGLUint index, boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3f() failed: OpenGL function \"glVertexAttrib3f\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3f(index, x, y, z);
}

void OpenGL::vertexAttrib3fv(boom::OpenGLUint index, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3fv() failed: OpenGL function \"glVertexAttrib3fv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3fv(index, v);
}

void OpenGL::vertexAttrib3s(boom::OpenGLUint index, boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3s() failed: OpenGL function \"glVertexAttrib3s\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3s(index, x, y, z);
}

void OpenGL::vertexAttrib3sv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib3sv() failed: OpenGL function \"glVertexAttrib3sv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib3sv(index, v);
}

void OpenGL::vertexAttrib4Nbv(boom::OpenGLUint index, boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nbv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nbv() failed: OpenGL function \"glVertexAttrib4Nbv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nbv(index, v);
}

void OpenGL::vertexAttrib4Niv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Niv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Niv() failed: OpenGL function \"glVertexAttrib4Niv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Niv(index, v);
}

void OpenGL::vertexAttrib4Nsv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nsv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nsv() failed: OpenGL function \"glVertexAttrib4Nsv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nsv(index, v);
}

void OpenGL::vertexAttrib4Nub(boom::OpenGLUint index, boom::OpenGLUbyte x, boom::OpenGLUbyte y, boom::OpenGLUbyte z, boom::OpenGLUbyte w) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nub == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nub() failed: OpenGL function \"glVertexAttrib4Nub\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nub(index, x, y, z, w);
}

void OpenGL::vertexAttrib4Nubv(boom::OpenGLUint index, boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nubv() failed: OpenGL function \"glVertexAttrib4Nubv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nubv(index, v);
}

void OpenGL::vertexAttrib4Nuiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nuiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nuiv() failed: OpenGL function \"glVertexAttrib4Nuiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nuiv(index, v);
}

void OpenGL::vertexAttrib4Nusv(boom::OpenGLUint index, boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4Nusv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4Nusv() failed: OpenGL function \"glVertexAttrib4Nusv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4Nusv(index, v);
}

void OpenGL::vertexAttrib4bv(boom::OpenGLUint index, boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4bv() failed: OpenGL function \"glVertexAttrib4bv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4bv(index, v);
}

void OpenGL::vertexAttrib4d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z, boom::OpenGLDouble w) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4d() failed: OpenGL function \"glVertexAttrib4d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4d(index, x, y, z, w);
}

void OpenGL::vertexAttrib4dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4dv() failed: OpenGL function \"glVertexAttrib4dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4dv(index, v);
}

void OpenGL::vertexAttrib4f(boom::OpenGLUint index, boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z, boom::OpenGLFloat w) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4f() failed: OpenGL function \"glVertexAttrib4f\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4f(index, x, y, z, w);
}

void OpenGL::vertexAttrib4fv(boom::OpenGLUint index, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4fv() failed: OpenGL function \"glVertexAttrib4fv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4fv(index, v);
}

void OpenGL::vertexAttrib4iv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4iv() failed: OpenGL function \"glVertexAttrib4iv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4iv(index, v);
}

void OpenGL::vertexAttrib4s(boom::OpenGLUint index, boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z, boom::OpenGLShort w) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4s() failed: OpenGL function \"glVertexAttrib4s\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4s(index, x, y, z, w);
}

void OpenGL::vertexAttrib4sv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4sv() failed: OpenGL function \"glVertexAttrib4sv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4sv(index, v);
}

void OpenGL::vertexAttrib4ubv(boom::OpenGLUint index, boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4ubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4ubv() failed: OpenGL function \"glVertexAttrib4ubv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4ubv(index, v);
}

void OpenGL::vertexAttrib4uiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4uiv() failed: OpenGL function \"glVertexAttrib4uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4uiv(index, v);
}

void OpenGL::vertexAttrib4usv(boom::OpenGLUint index, boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttrib4usv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttrib4usv() failed: OpenGL function \"glVertexAttrib4usv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttrib4usv(index, v);
}

void OpenGL::vertexAttribBinding(boom::OpenGLUint attribindex, boom::OpenGLUint bindingindex) const {
#ifndef NDEBUG
    if (boom::glVertexAttribBinding == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribBinding() failed: OpenGL function \"glVertexAttribBinding\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribBinding(attribindex, bindingindex);
}

void OpenGL::vertexAttribDivisor(boom::OpenGLUint index, boom::OpenGLUint divisor) const {
#ifndef NDEBUG
    if (boom::glVertexAttribDivisor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribDivisor() failed: OpenGL function \"glVertexAttribDivisor\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribDivisor(index, divisor);
}

void OpenGL::vertexAttribFormat(boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexAttribFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribFormat() failed: OpenGL function \"glVertexAttribFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

void OpenGL::vertexAttribI1i(boom::OpenGLUint index, boom::OpenGLInt x) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI1i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI1i() failed: OpenGL function \"glVertexAttribI1i\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI1i(index, x);
}

void OpenGL::vertexAttribI1iv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI1iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI1iv() failed: OpenGL function \"glVertexAttribI1iv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI1iv(index, v);
}

void OpenGL::vertexAttribI1ui(boom::OpenGLUint index, boom::OpenGLUint x) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI1ui() failed: OpenGL function \"glVertexAttribI1ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI1ui(index, x);
}

void OpenGL::vertexAttribI1uiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI1uiv() failed: OpenGL function \"glVertexAttribI1uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI1uiv(index, v);
}

void OpenGL::vertexAttribI2i(boom::OpenGLUint index, boom::OpenGLInt x, boom::OpenGLInt y) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI2i() failed: OpenGL function \"glVertexAttribI2i\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI2i(index, x, y);
}

void OpenGL::vertexAttribI2iv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI2iv() failed: OpenGL function \"glVertexAttribI2iv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI2iv(index, v);
}

void OpenGL::vertexAttribI2ui(boom::OpenGLUint index, boom::OpenGLUint x, boom::OpenGLUint y) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI2ui() failed: OpenGL function \"glVertexAttribI2ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI2ui(index, x, y);
}

void OpenGL::vertexAttribI2uiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI2uiv() failed: OpenGL function \"glVertexAttribI2uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI2uiv(index, v);
}

void OpenGL::vertexAttribI3i(boom::OpenGLUint index, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI3i() failed: OpenGL function \"glVertexAttribI3i\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI3i(index, x, y, z);
}

void OpenGL::vertexAttribI3iv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI3iv() failed: OpenGL function \"glVertexAttribI3iv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI3iv(index, v);
}

void OpenGL::vertexAttribI3ui(boom::OpenGLUint index, boom::OpenGLUint x, boom::OpenGLUint y, boom::OpenGLUint z) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI3ui() failed: OpenGL function \"glVertexAttribI3ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI3ui(index, x, y, z);
}

void OpenGL::vertexAttribI3uiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI3uiv() failed: OpenGL function \"glVertexAttribI3uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI3uiv(index, v);
}

void OpenGL::vertexAttribI4bv(boom::OpenGLUint index, boom::OpenGLByte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4bv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4bv() failed: OpenGL function \"glVertexAttribI4bv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4bv(index, v);
}

void OpenGL::vertexAttribI4i(boom::OpenGLUint index, boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z, boom::OpenGLInt w) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4i() failed: OpenGL function \"glVertexAttribI4i\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4i(index, x, y, z, w);
}

void OpenGL::vertexAttribI4iv(boom::OpenGLUint index, boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4iv() failed: OpenGL function \"glVertexAttribI4iv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4iv(index, v);
}

void OpenGL::vertexAttribI4sv(boom::OpenGLUint index, boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4sv() failed: OpenGL function \"glVertexAttribI4sv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4sv(index, v);
}

void OpenGL::vertexAttribI4ubv(boom::OpenGLUint index, boom::OpenGLUbyte const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4ubv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4ubv() failed: OpenGL function \"glVertexAttribI4ubv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4ubv(index, v);
}

void OpenGL::vertexAttribI4ui(boom::OpenGLUint index, boom::OpenGLUint x, boom::OpenGLUint y, boom::OpenGLUint z, boom::OpenGLUint w) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4ui() failed: OpenGL function \"glVertexAttribI4ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4ui(index, x, y, z, w);
}

void OpenGL::vertexAttribI4uiv(boom::OpenGLUint index, boom::OpenGLUint const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4uiv() failed: OpenGL function \"glVertexAttribI4uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4uiv(index, v);
}

void OpenGL::vertexAttribI4usv(boom::OpenGLUint index, boom::OpenGLUShort const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribI4usv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribI4usv() failed: OpenGL function \"glVertexAttribI4usv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribI4usv(index, v);
}

void OpenGL::vertexAttribIFormat(boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexAttribIFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribIFormat() failed: OpenGL function \"glVertexAttribIFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

void OpenGL::vertexAttribIPointer(boom::OpenGLUint index, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glVertexAttribIPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribIPointer() failed: OpenGL function \"glVertexAttribIPointer\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribIPointer(index, size, type, stride, pointer);
}

void OpenGL::vertexAttribL1d(boom::OpenGLUint index, boom::OpenGLDouble x) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL1d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL1d() failed: OpenGL function \"glVertexAttribL1d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL1d(index, x);
}

void OpenGL::vertexAttribL1dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL1dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL1dv() failed: OpenGL function \"glVertexAttribL1dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL1dv(index, v);
}

void OpenGL::vertexAttribL2d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL2d() failed: OpenGL function \"glVertexAttribL2d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL2d(index, x, y);
}

void OpenGL::vertexAttribL2dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL2dv() failed: OpenGL function \"glVertexAttribL2dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL2dv(index, v);
}

void OpenGL::vertexAttribL3d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL3d() failed: OpenGL function \"glVertexAttribL3d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL3d(index, x, y, z);
}

void OpenGL::vertexAttribL3dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL3dv() failed: OpenGL function \"glVertexAttribL3dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL3dv(index, v);
}

void OpenGL::vertexAttribL4d(boom::OpenGLUint index, boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z, boom::OpenGLDouble w) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL4d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL4d() failed: OpenGL function \"glVertexAttribL4d\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL4d(index, x, y, z, w);
}

void OpenGL::vertexAttribL4dv(boom::OpenGLUint index, boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glVertexAttribL4dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribL4dv() failed: OpenGL function \"glVertexAttribL4dv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribL4dv(index, v);
}

void OpenGL::vertexAttribLFormat(boom::OpenGLUint attribindex, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLUint relativeoffset) const {
#ifndef NDEBUG
    if (boom::glVertexAttribLFormat == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribLFormat() failed: OpenGL function \"glVertexAttribLFormat\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribLFormat(attribindex, size, type, relativeoffset);
}

void OpenGL::vertexAttribLPointer(boom::OpenGLUint index, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glVertexAttribLPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribLPointer() failed: OpenGL function \"glVertexAttribLPointer\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribLPointer(index, size, type, stride, pointer);
}

void OpenGL::vertexAttribP1ui(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP1ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP1ui() failed: OpenGL function \"glVertexAttribP1ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP1ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP1uiv(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP1uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP1uiv() failed: OpenGL function \"glVertexAttribP1uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP1uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP2ui(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP2ui() failed: OpenGL function \"glVertexAttribP2ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP2ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP2uiv(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP2uiv() failed: OpenGL function \"glVertexAttribP2uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP2uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP3ui(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP3ui() failed: OpenGL function \"glVertexAttribP3ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP3ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP3uiv(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP3uiv() failed: OpenGL function \"glVertexAttribP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP3uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribP4ui(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP4ui() failed: OpenGL function \"glVertexAttribP4ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP4ui(index, type, normalized, value);
}

void OpenGL::vertexAttribP4uiv(boom::OpenGLUint index, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexAttribP4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribP4uiv() failed: OpenGL function \"glVertexAttribP4uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribP4uiv(index, type, normalized, value);
}

void OpenGL::vertexAttribPointer(boom::OpenGLUint index, boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLBoolean normalized, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glVertexAttribPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexAttribPointer() failed: OpenGL function \"glVertexAttribPointer\" not loaded");
    }
#endif
    _current();
    boom::glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void OpenGL::vertexBindingDivisor(boom::OpenGLUint bindingindex, boom::OpenGLUint divisor) const {
#ifndef NDEBUG
    if (boom::glVertexBindingDivisor == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexBindingDivisor() failed: OpenGL function \"glVertexBindingDivisor\" not loaded");
    }
#endif
    _current();
    boom::glVertexBindingDivisor(bindingindex, divisor);
}

void OpenGL::vertexP2ui(boom::OpenGLEnum type, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexP2ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP2ui() failed: OpenGL function \"glVertexP2ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexP2ui(type, value);
}

void OpenGL::vertexP2uiv(boom::OpenGLEnum type, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexP2uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP2uiv() failed: OpenGL function \"glVertexP2uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexP2uiv(type, value);
}

void OpenGL::vertexP3ui(boom::OpenGLEnum type, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexP3ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP3ui() failed: OpenGL function \"glVertexP3ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexP3ui(type, value);
}

void OpenGL::vertexP3uiv(boom::OpenGLEnum type, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexP3uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP3uiv() failed: OpenGL function \"glVertexP3uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexP3uiv(type, value);
}

void OpenGL::vertexP4ui(boom::OpenGLEnum type, boom::OpenGLUint value) const {
#ifndef NDEBUG
    if (boom::glVertexP4ui == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP4ui() failed: OpenGL function \"glVertexP4ui\" not loaded");
    }
#endif
    _current();
    boom::glVertexP4ui(type, value);
}

void OpenGL::vertexP4uiv(boom::OpenGLEnum type, boom::OpenGLUint const* value) const {
#ifndef NDEBUG
    if (boom::glVertexP4uiv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexP4uiv() failed: OpenGL function \"glVertexP4uiv\" not loaded");
    }
#endif
    _current();
    boom::glVertexP4uiv(type, value);
}

void OpenGL::vertexPointer(boom::OpenGLInt size, boom::OpenGLEnum type, boom::OpenGLSizei stride, void const* pointer) const {
#ifndef NDEBUG
    if (boom::glVertexPointer == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::vertexPointer() failed: OpenGL function \"glVertexPointer\" not loaded");
    }
#endif
    _current();
    boom::glVertexPointer(size, type, stride, pointer);
}

void OpenGL::viewport(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLSizei width, boom::OpenGLSizei height) const {
#ifndef NDEBUG
    if (boom::glViewport == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::viewport() failed: OpenGL function \"glViewport\" not loaded");
    }
#endif
    _current();
    boom::glViewport(x, y, width, height);
}

void OpenGL::viewportArrayv(boom::OpenGLUint first, boom::OpenGLSizei count, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glViewportArrayv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::viewportArrayv() failed: OpenGL function \"glViewportArrayv\" not loaded");
    }
#endif
    _current();
    boom::glViewportArrayv(first, count, v);
}

void OpenGL::viewportIndexedf(boom::OpenGLUint index, boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat w, boom::OpenGLFloat h) const {
#ifndef NDEBUG
    if (boom::glViewportIndexedf == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::viewportIndexedf() failed: OpenGL function \"glViewportIndexedf\" not loaded");
    }
#endif
    _current();
    boom::glViewportIndexedf(index, x, y, w, h);
}

void OpenGL::viewportIndexedfv(boom::OpenGLUint index, boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glViewportIndexedfv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::viewportIndexedfv() failed: OpenGL function \"glViewportIndexedfv\" not loaded");
    }
#endif
    _current();
    boom::glViewportIndexedfv(index, v);
}

void OpenGL::waitSync(boom::OpenGLSync sync, boom::OpenGLBitfield flags, boom::OpenGLUInt64 timeout) const {
#ifndef NDEBUG
    if (boom::glWaitSync == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::waitSync() failed: OpenGL function \"glWaitSync\" not loaded");
    }
#endif
    _current();
    boom::glWaitSync(sync, flags, timeout);
}

void OpenGL::windowPos2d(boom::OpenGLDouble x, boom::OpenGLDouble y) const {
#ifndef NDEBUG
    if (boom::glWindowPos2d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2d() failed: OpenGL function \"glWindowPos2d\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2d(x, y);
}

void OpenGL::windowPos2dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos2dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2dv() failed: OpenGL function \"glWindowPos2dv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2dv(v);
}

void OpenGL::windowPos2f(boom::OpenGLFloat x, boom::OpenGLFloat y) const {
#ifndef NDEBUG
    if (boom::glWindowPos2f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2f() failed: OpenGL function \"glWindowPos2f\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2f(x, y);
}

void OpenGL::windowPos2fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos2fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2fv() failed: OpenGL function \"glWindowPos2fv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2fv(v);
}

void OpenGL::windowPos2i(boom::OpenGLInt x, boom::OpenGLInt y) const {
#ifndef NDEBUG
    if (boom::glWindowPos2i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2i() failed: OpenGL function \"glWindowPos2i\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2i(x, y);
}

void OpenGL::windowPos2iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos2iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2iv() failed: OpenGL function \"glWindowPos2iv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2iv(v);
}

void OpenGL::windowPos2s(boom::OpenGLShort x, boom::OpenGLShort y) const {
#ifndef NDEBUG
    if (boom::glWindowPos2s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2s() failed: OpenGL function \"glWindowPos2s\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2s(x, y);
}

void OpenGL::windowPos2sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos2sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos2sv() failed: OpenGL function \"glWindowPos2sv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos2sv(v);
}

void OpenGL::windowPos3d(boom::OpenGLDouble x, boom::OpenGLDouble y, boom::OpenGLDouble z) const {
#ifndef NDEBUG
    if (boom::glWindowPos3d == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3d() failed: OpenGL function \"glWindowPos3d\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3d(x, y, z);
}

void OpenGL::windowPos3dv(boom::OpenGLDouble const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos3dv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3dv() failed: OpenGL function \"glWindowPos3dv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3dv(v);
}

void OpenGL::windowPos3f(boom::OpenGLFloat x, boom::OpenGLFloat y, boom::OpenGLFloat z) const {
#ifndef NDEBUG
    if (boom::glWindowPos3f == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3f() failed: OpenGL function \"glWindowPos3f\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3f(x, y, z);
}

void OpenGL::windowPos3fv(boom::OpenGLFloat const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos3fv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3fv() failed: OpenGL function \"glWindowPos3fv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3fv(v);
}

void OpenGL::windowPos3i(boom::OpenGLInt x, boom::OpenGLInt y, boom::OpenGLInt z) const {
#ifndef NDEBUG
    if (boom::glWindowPos3i == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3i() failed: OpenGL function \"glWindowPos3i\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3i(x, y, z);
}

void OpenGL::windowPos3iv(boom::OpenGLInt const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos3iv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3iv() failed: OpenGL function \"glWindowPos3iv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3iv(v);
}

void OpenGL::windowPos3s(boom::OpenGLShort x, boom::OpenGLShort y, boom::OpenGLShort z) const {
#ifndef NDEBUG
    if (boom::glWindowPos3s == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3s() failed: OpenGL function \"glWindowPos3s\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3s(x, y, z);
}

void OpenGL::windowPos3sv(boom::OpenGLShort const* v) const {
#ifndef NDEBUG
    if (boom::glWindowPos3sv == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::windowPos3sv() failed: OpenGL function \"glWindowPos3sv\" not loaded");
    }
#endif
    _current();
    boom::glWindowPos3sv(v);
}

void OpenGL::swap() const {
    _current();
    _implSwap();
}

void OpenGL::_current() const {
    _implCurrent();
}

void OpenGL::_bootstrap() {
    _implBootstrap();
}

boom::OpenGLAccumFn glAccum = nullptr;
boom::OpenGLActiveShaderProgramFn glActiveShaderProgram = nullptr;
boom::OpenGLActiveTextureFn glActiveTexture = nullptr;
boom::OpenGLAlphaFuncFn glAlphaFunc = nullptr;
boom::OpenGLAlphaFuncxFn glAlphaFuncx = nullptr;
boom::OpenGLAreTexturesResidentFn glAreTexturesResident = nullptr;
boom::OpenGLArrayElementFn glArrayElement = nullptr;
boom::OpenGLAttachShaderFn glAttachShader = nullptr;
boom::OpenGLBeginFn glBegin = nullptr;
boom::OpenGLBeginConditionalRenderFn glBeginConditionalRender = nullptr;
boom::OpenGLBeginQueryFn glBeginQuery = nullptr;
boom::OpenGLBeginQueryIndexedFn glBeginQueryIndexed = nullptr;
boom::OpenGLBeginTransformFeedbackFn glBeginTransformFeedback = nullptr;
boom::OpenGLBindAttribLocationFn glBindAttribLocation = nullptr;
boom::OpenGLBindBufferFn glBindBuffer = nullptr;
boom::OpenGLBindBufferBaseFn glBindBufferBase = nullptr;
boom::OpenGLBindBufferRangeFn glBindBufferRange = nullptr;
boom::OpenGLBindBuffersBaseFn glBindBuffersBase = nullptr;
boom::OpenGLBindBuffersRangeFn glBindBuffersRange = nullptr;
boom::OpenGLBindFragDataLocationFn glBindFragDataLocation = nullptr;
boom::OpenGLBindFragDataLocationIndexedFn glBindFragDataLocationIndexed = nullptr;
boom::OpenGLBindFramebufferFn glBindFramebuffer = nullptr;
boom::OpenGLBindImageTextureFn glBindImageTexture = nullptr;
boom::OpenGLBindImageTexturesFn glBindImageTextures = nullptr;
boom::OpenGLBindProgramPipelineFn glBindProgramPipeline = nullptr;
boom::OpenGLBindRenderbufferFn glBindRenderbuffer = nullptr;
boom::OpenGLBindSamplerFn glBindSampler = nullptr;
boom::OpenGLBindSamplersFn glBindSamplers = nullptr;
boom::OpenGLBindTextureFn glBindTexture = nullptr;
boom::OpenGLBindTextureUnitFn glBindTextureUnit = nullptr;
boom::OpenGLBindTexturesFn glBindTextures = nullptr;
boom::OpenGLBindTransformFeedbackFn glBindTransformFeedback = nullptr;
boom::OpenGLBindVertexArrayFn glBindVertexArray = nullptr;
boom::OpenGLBindVertexBufferFn glBindVertexBuffer = nullptr;
boom::OpenGLBindVertexBuffersFn glBindVertexBuffers = nullptr;
boom::OpenGLBitmapFn glBitmap = nullptr;
boom::OpenGLBlendBarrierFn glBlendBarrier = nullptr;
boom::OpenGLBlendColorFn glBlendColor = nullptr;
boom::OpenGLBlendEquationFn glBlendEquation = nullptr;
boom::OpenGLBlendEquationSeparateFn glBlendEquationSeparate = nullptr;
boom::OpenGLBlendEquationSeparateiFn glBlendEquationSeparatei = nullptr;
boom::OpenGLBlendEquationiFn glBlendEquationi = nullptr;
boom::OpenGLBlendFuncFn glBlendFunc = nullptr;
boom::OpenGLBlendFuncSeparateFn glBlendFuncSeparate = nullptr;
boom::OpenGLBlendFuncSeparateiFn glBlendFuncSeparatei = nullptr;
boom::OpenGLBlendFunciFn glBlendFunci = nullptr;
boom::OpenGLBlitFramebufferFn glBlitFramebuffer = nullptr;
boom::OpenGLBlitNamedFramebufferFn glBlitNamedFramebuffer = nullptr;
boom::OpenGLBufferDataFn glBufferData = nullptr;
boom::OpenGLBufferStorageFn glBufferStorage = nullptr;
boom::OpenGLBufferSubDataFn glBufferSubData = nullptr;
boom::OpenGLCallListFn glCallList = nullptr;
boom::OpenGLCallListsFn glCallLists = nullptr;
boom::OpenGLCheckFramebufferStatusFn glCheckFramebufferStatus = nullptr;
boom::OpenGLCheckNamedFramebufferStatusFn glCheckNamedFramebufferStatus = nullptr;
boom::OpenGLClampColorFn glClampColor = nullptr;
boom::OpenGLClearFn glClear = nullptr;
boom::OpenGLClearAccumFn glClearAccum = nullptr;
boom::OpenGLClearBufferDataFn glClearBufferData = nullptr;
boom::OpenGLClearBufferSubDataFn glClearBufferSubData = nullptr;
boom::OpenGLClearBufferfiFn glClearBufferfi = nullptr;
boom::OpenGLClearBufferfvFn glClearBufferfv = nullptr;
boom::OpenGLClearBufferivFn glClearBufferiv = nullptr;
boom::OpenGLClearBufferuivFn glClearBufferuiv = nullptr;
boom::OpenGLClearColorFn glClearColor = nullptr;
boom::OpenGLClearColorxFn glClearColorx = nullptr;
boom::OpenGLClearDepthFn glClearDepth = nullptr;
boom::OpenGLClearDepthfFn glClearDepthf = nullptr;
boom::OpenGLClearDepthxFn glClearDepthx = nullptr;
boom::OpenGLClearIndexFn glClearIndex = nullptr;
boom::OpenGLClearNamedBufferDataFn glClearNamedBufferData = nullptr;
boom::OpenGLClearNamedBufferSubDataFn glClearNamedBufferSubData = nullptr;
boom::OpenGLClearNamedFramebufferfiFn glClearNamedFramebufferfi = nullptr;
boom::OpenGLClearNamedFramebufferfvFn glClearNamedFramebufferfv = nullptr;
boom::OpenGLClearNamedFramebufferivFn glClearNamedFramebufferiv = nullptr;
boom::OpenGLClearNamedFramebufferuivFn glClearNamedFramebufferuiv = nullptr;
boom::OpenGLClearStencilFn glClearStencil = nullptr;
boom::OpenGLClearTexImageFn glClearTexImage = nullptr;
boom::OpenGLClearTexSubImageFn glClearTexSubImage = nullptr;
boom::OpenGLClientActiveTextureFn glClientActiveTexture = nullptr;
boom::OpenGLClientWaitSyncFn glClientWaitSync = nullptr;
boom::OpenGLClipControlFn glClipControl = nullptr;
boom::OpenGLClipPlaneFn glClipPlane = nullptr;
boom::OpenGLClipPlanefFn glClipPlanef = nullptr;
boom::OpenGLClipPlanexFn glClipPlanex = nullptr;
boom::OpenGLColor3bFn glColor3b = nullptr;
boom::OpenGLColor3bvFn glColor3bv = nullptr;
boom::OpenGLColor3dFn glColor3d = nullptr;
boom::OpenGLColor3dvFn glColor3dv = nullptr;
boom::OpenGLColor3fFn glColor3f = nullptr;
boom::OpenGLColor3fvFn glColor3fv = nullptr;
boom::OpenGLColor3iFn glColor3i = nullptr;
boom::OpenGLColor3ivFn glColor3iv = nullptr;
boom::OpenGLColor3sFn glColor3s = nullptr;
boom::OpenGLColor3svFn glColor3sv = nullptr;
boom::OpenGLColor3ubFn glColor3ub = nullptr;
boom::OpenGLColor3ubvFn glColor3ubv = nullptr;
boom::OpenGLColor3uiFn glColor3ui = nullptr;
boom::OpenGLColor3uivFn glColor3uiv = nullptr;
boom::OpenGLColor3usFn glColor3us = nullptr;
boom::OpenGLColor3usvFn glColor3usv = nullptr;
boom::OpenGLColor4bFn glColor4b = nullptr;
boom::OpenGLColor4bvFn glColor4bv = nullptr;
boom::OpenGLColor4dFn glColor4d = nullptr;
boom::OpenGLColor4dvFn glColor4dv = nullptr;
boom::OpenGLColor4fFn glColor4f = nullptr;
boom::OpenGLColor4fvFn glColor4fv = nullptr;
boom::OpenGLColor4iFn glColor4i = nullptr;
boom::OpenGLColor4ivFn glColor4iv = nullptr;
boom::OpenGLColor4sFn glColor4s = nullptr;
boom::OpenGLColor4svFn glColor4sv = nullptr;
boom::OpenGLColor4ubFn glColor4ub = nullptr;
boom::OpenGLColor4ubvFn glColor4ubv = nullptr;
boom::OpenGLColor4uiFn glColor4ui = nullptr;
boom::OpenGLColor4uivFn glColor4uiv = nullptr;
boom::OpenGLColor4usFn glColor4us = nullptr;
boom::OpenGLColor4usvFn glColor4usv = nullptr;
boom::OpenGLColor4xFn glColor4x = nullptr;
boom::OpenGLColorMaskFn glColorMask = nullptr;
boom::OpenGLColorMaskiFn glColorMaski = nullptr;
boom::OpenGLColorMaterialFn glColorMaterial = nullptr;
boom::OpenGLColorP3uiFn glColorP3ui = nullptr;
boom::OpenGLColorP3uivFn glColorP3uiv = nullptr;
boom::OpenGLColorP4uiFn glColorP4ui = nullptr;
boom::OpenGLColorP4uivFn glColorP4uiv = nullptr;
boom::OpenGLColorPointerFn glColorPointer = nullptr;
boom::OpenGLCompileShaderFn glCompileShader = nullptr;
boom::OpenGLCompressedTexImage1DFn glCompressedTexImage1D = nullptr;
boom::OpenGLCompressedTexImage2DFn glCompressedTexImage2D = nullptr;
boom::OpenGLCompressedTexImage3DFn glCompressedTexImage3D = nullptr;
boom::OpenGLCompressedTexSubImage1DFn glCompressedTexSubImage1D = nullptr;
boom::OpenGLCompressedTexSubImage2DFn glCompressedTexSubImage2D = nullptr;
boom::OpenGLCompressedTexSubImage3DFn glCompressedTexSubImage3D = nullptr;
boom::OpenGLCompressedTextureSubImage1DFn glCompressedTextureSubImage1D = nullptr;
boom::OpenGLCompressedTextureSubImage2DFn glCompressedTextureSubImage2D = nullptr;
boom::OpenGLCompressedTextureSubImage3DFn glCompressedTextureSubImage3D = nullptr;
boom::OpenGLCopyBufferSubDataFn glCopyBufferSubData = nullptr;
boom::OpenGLCopyImageSubDataFn glCopyImageSubData = nullptr;
boom::OpenGLCopyNamedBufferSubDataFn glCopyNamedBufferSubData = nullptr;
boom::OpenGLCopyPixelsFn glCopyPixels = nullptr;
boom::OpenGLCopyTexImage1DFn glCopyTexImage1D = nullptr;
boom::OpenGLCopyTexImage2DFn glCopyTexImage2D = nullptr;
boom::OpenGLCopyTexSubImage1DFn glCopyTexSubImage1D = nullptr;
boom::OpenGLCopyTexSubImage2DFn glCopyTexSubImage2D = nullptr;
boom::OpenGLCopyTexSubImage3DFn glCopyTexSubImage3D = nullptr;
boom::OpenGLCopyTextureSubImage1DFn glCopyTextureSubImage1D = nullptr;
boom::OpenGLCopyTextureSubImage2DFn glCopyTextureSubImage2D = nullptr;
boom::OpenGLCopyTextureSubImage3DFn glCopyTextureSubImage3D = nullptr;
boom::OpenGLCreateBuffersFn glCreateBuffers = nullptr;
boom::OpenGLCreateFramebuffersFn glCreateFramebuffers = nullptr;
boom::OpenGLCreateProgramFn glCreateProgram = nullptr;
boom::OpenGLCreateProgramPipelinesFn glCreateProgramPipelines = nullptr;
boom::OpenGLCreateQueriesFn glCreateQueries = nullptr;
boom::OpenGLCreateRenderbuffersFn glCreateRenderbuffers = nullptr;
boom::OpenGLCreateSamplersFn glCreateSamplers = nullptr;
boom::OpenGLCreateShaderFn glCreateShader = nullptr;
boom::OpenGLCreateShaderProgramvFn glCreateShaderProgramv = nullptr;
boom::OpenGLCreateTexturesFn glCreateTextures = nullptr;
boom::OpenGLCreateTransformFeedbacksFn glCreateTransformFeedbacks = nullptr;
boom::OpenGLCreateVertexArraysFn glCreateVertexArrays = nullptr;
boom::OpenGLCullFaceFn glCullFace = nullptr;
boom::OpenGLDebugMessageCallbackFn glDebugMessageCallback = nullptr;
boom::OpenGLDebugMessageControlFn glDebugMessageControl = nullptr;
boom::OpenGLDebugMessageInsertFn glDebugMessageInsert = nullptr;
boom::OpenGLDeleteBuffersFn glDeleteBuffers = nullptr;
boom::OpenGLDeleteFramebuffersFn glDeleteFramebuffers = nullptr;
boom::OpenGLDeleteListsFn glDeleteLists = nullptr;
boom::OpenGLDeleteProgramFn glDeleteProgram = nullptr;
boom::OpenGLDeleteProgramPipelinesFn glDeleteProgramPipelines = nullptr;
boom::OpenGLDeleteQueriesFn glDeleteQueries = nullptr;
boom::OpenGLDeleteRenderbuffersFn glDeleteRenderbuffers = nullptr;
boom::OpenGLDeleteSamplersFn glDeleteSamplers = nullptr;
boom::OpenGLDeleteShaderFn glDeleteShader = nullptr;
boom::OpenGLDeleteSyncFn glDeleteSync = nullptr;
boom::OpenGLDeleteTexturesFn glDeleteTextures = nullptr;
boom::OpenGLDeleteTransformFeedbacksFn glDeleteTransformFeedbacks = nullptr;
boom::OpenGLDeleteVertexArraysFn glDeleteVertexArrays = nullptr;
boom::OpenGLDepthFuncFn glDepthFunc = nullptr;
boom::OpenGLDepthMaskFn glDepthMask = nullptr;
boom::OpenGLDepthRangeFn glDepthRange = nullptr;
boom::OpenGLDepthRangeArrayvFn glDepthRangeArrayv = nullptr;
boom::OpenGLDepthRangeIndexedFn glDepthRangeIndexed = nullptr;
boom::OpenGLDepthRangefFn glDepthRangef = nullptr;
boom::OpenGLDepthRangexFn glDepthRangex = nullptr;
boom::OpenGLDetachShaderFn glDetachShader = nullptr;
boom::OpenGLDisableFn glDisable = nullptr;
boom::OpenGLDisableClientStateFn glDisableClientState = nullptr;
boom::OpenGLDisableVertexArrayAttribFn glDisableVertexArrayAttrib = nullptr;
boom::OpenGLDisableVertexAttribArrayFn glDisableVertexAttribArray = nullptr;
boom::OpenGLDisableiFn glDisablei = nullptr;
boom::OpenGLDispatchComputeFn glDispatchCompute = nullptr;
boom::OpenGLDispatchComputeIndirectFn glDispatchComputeIndirect = nullptr;
boom::OpenGLDrawArraysFn glDrawArrays = nullptr;
boom::OpenGLDrawArraysIndirectFn glDrawArraysIndirect = nullptr;
boom::OpenGLDrawArraysInstancedFn glDrawArraysInstanced = nullptr;
boom::OpenGLDrawArraysInstancedBaseInstanceFn glDrawArraysInstancedBaseInstance = nullptr;
boom::OpenGLDrawBufferFn glDrawBuffer = nullptr;
boom::OpenGLDrawBuffersFn glDrawBuffers = nullptr;
boom::OpenGLDrawElementsFn glDrawElements = nullptr;
boom::OpenGLDrawElementsBaseVertexFn glDrawElementsBaseVertex = nullptr;
boom::OpenGLDrawElementsIndirectFn glDrawElementsIndirect = nullptr;
boom::OpenGLDrawElementsInstancedFn glDrawElementsInstanced = nullptr;
boom::OpenGLDrawElementsInstancedBaseInstanceFn glDrawElementsInstancedBaseInstance = nullptr;
boom::OpenGLDrawElementsInstancedBaseVertexFn glDrawElementsInstancedBaseVertex = nullptr;
boom::OpenGLDrawElementsInstancedBaseVertexBaseInstanceFn glDrawElementsInstancedBaseVertexBaseInstance = nullptr;
boom::OpenGLDrawPixelsFn glDrawPixels = nullptr;
boom::OpenGLDrawRangeElementsFn glDrawRangeElements = nullptr;
boom::OpenGLDrawRangeElementsBaseVertexFn glDrawRangeElementsBaseVertex = nullptr;
boom::OpenGLDrawTransformFeedbackFn glDrawTransformFeedback = nullptr;
boom::OpenGLDrawTransformFeedbackInstancedFn glDrawTransformFeedbackInstanced = nullptr;
boom::OpenGLDrawTransformFeedbackStreamFn glDrawTransformFeedbackStream = nullptr;
boom::OpenGLDrawTransformFeedbackStreamInstancedFn glDrawTransformFeedbackStreamInstanced = nullptr;
boom::OpenGLEdgeFlagFn glEdgeFlag = nullptr;
boom::OpenGLEdgeFlagPointerFn glEdgeFlagPointer = nullptr;
boom::OpenGLEdgeFlagvFn glEdgeFlagv = nullptr;
boom::OpenGLEnableFn glEnable = nullptr;
boom::OpenGLEnableClientStateFn glEnableClientState = nullptr;
boom::OpenGLEnableVertexArrayAttribFn glEnableVertexArrayAttrib = nullptr;
boom::OpenGLEnableVertexAttribArrayFn glEnableVertexAttribArray = nullptr;
boom::OpenGLEnableiFn glEnablei = nullptr;
boom::OpenGLEndFn glEnd = nullptr;
boom::OpenGLEndConditionalRenderFn glEndConditionalRender = nullptr;
boom::OpenGLEndListFn glEndList = nullptr;
boom::OpenGLEndQueryFn glEndQuery = nullptr;
boom::OpenGLEndQueryIndexedFn glEndQueryIndexed = nullptr;
boom::OpenGLEndTransformFeedbackFn glEndTransformFeedback = nullptr;
boom::OpenGLEvalCoord1dFn glEvalCoord1d = nullptr;
boom::OpenGLEvalCoord1dvFn glEvalCoord1dv = nullptr;
boom::OpenGLEvalCoord1fFn glEvalCoord1f = nullptr;
boom::OpenGLEvalCoord1fvFn glEvalCoord1fv = nullptr;
boom::OpenGLEvalCoord2dFn glEvalCoord2d = nullptr;
boom::OpenGLEvalCoord2dvFn glEvalCoord2dv = nullptr;
boom::OpenGLEvalCoord2fFn glEvalCoord2f = nullptr;
boom::OpenGLEvalCoord2fvFn glEvalCoord2fv = nullptr;
boom::OpenGLEvalMesh1Fn glEvalMesh1 = nullptr;
boom::OpenGLEvalMesh2Fn glEvalMesh2 = nullptr;
boom::OpenGLEvalPoint1Fn glEvalPoint1 = nullptr;
boom::OpenGLEvalPoint2Fn glEvalPoint2 = nullptr;
boom::OpenGLFeedbackBufferFn glFeedbackBuffer = nullptr;
boom::OpenGLFenceSyncFn glFenceSync = nullptr;
boom::OpenGLFinishFn glFinish = nullptr;
boom::OpenGLFlushFn glFlush = nullptr;
boom::OpenGLFlushMappedBufferRangeFn glFlushMappedBufferRange = nullptr;
boom::OpenGLFlushMappedNamedBufferRangeFn glFlushMappedNamedBufferRange = nullptr;
boom::OpenGLFogCoordPointerFn glFogCoordPointer = nullptr;
boom::OpenGLFogCoorddFn glFogCoordd = nullptr;
boom::OpenGLFogCoorddvFn glFogCoorddv = nullptr;
boom::OpenGLFogCoordfFn glFogCoordf = nullptr;
boom::OpenGLFogCoordfvFn glFogCoordfv = nullptr;
boom::OpenGLFogfFn glFogf = nullptr;
boom::OpenGLFogfvFn glFogfv = nullptr;
boom::OpenGLFogiFn glFogi = nullptr;
boom::OpenGLFogivFn glFogiv = nullptr;
boom::OpenGLFogxFn glFogx = nullptr;
boom::OpenGLFogxvFn glFogxv = nullptr;
boom::OpenGLFramebufferParameteriFn glFramebufferParameteri = nullptr;
boom::OpenGLFramebufferRenderbufferFn glFramebufferRenderbuffer = nullptr;
boom::OpenGLFramebufferTextureFn glFramebufferTexture = nullptr;
boom::OpenGLFramebufferTexture1DFn glFramebufferTexture1D = nullptr;
boom::OpenGLFramebufferTexture2DFn glFramebufferTexture2D = nullptr;
boom::OpenGLFramebufferTexture3DFn glFramebufferTexture3D = nullptr;
boom::OpenGLFramebufferTextureLayerFn glFramebufferTextureLayer = nullptr;
boom::OpenGLFrontFaceFn glFrontFace = nullptr;
boom::OpenGLFrustumFn glFrustum = nullptr;
boom::OpenGLFrustumfFn glFrustumf = nullptr;
boom::OpenGLFrustumxFn glFrustumx = nullptr;
boom::OpenGLGenBuffersFn glGenBuffers = nullptr;
boom::OpenGLGenFramebuffersFn glGenFramebuffers = nullptr;
boom::OpenGLGenListsFn glGenLists = nullptr;
boom::OpenGLGenProgramPipelinesFn glGenProgramPipelines = nullptr;
boom::OpenGLGenQueriesFn glGenQueries = nullptr;
boom::OpenGLGenRenderbuffersFn glGenRenderbuffers = nullptr;
boom::OpenGLGenSamplersFn glGenSamplers = nullptr;
boom::OpenGLGenTexturesFn glGenTextures = nullptr;
boom::OpenGLGenTransformFeedbacksFn glGenTransformFeedbacks = nullptr;
boom::OpenGLGenVertexArraysFn glGenVertexArrays = nullptr;
boom::OpenGLGenerateMipmapFn glGenerateMipmap = nullptr;
boom::OpenGLGenerateTextureMipmapFn glGenerateTextureMipmap = nullptr;
boom::OpenGLGetActiveAtomicCounterBufferivFn glGetActiveAtomicCounterBufferiv = nullptr;
boom::OpenGLGetActiveAttribFn glGetActiveAttrib = nullptr;
boom::OpenGLGetActiveSubroutineNameFn glGetActiveSubroutineName = nullptr;
boom::OpenGLGetActiveSubroutineUniformNameFn glGetActiveSubroutineUniformName = nullptr;
boom::OpenGLGetActiveSubroutineUniformivFn glGetActiveSubroutineUniformiv = nullptr;
boom::OpenGLGetActiveUniformFn glGetActiveUniform = nullptr;
boom::OpenGLGetActiveUniformBlockNameFn glGetActiveUniformBlockName = nullptr;
boom::OpenGLGetActiveUniformBlockivFn glGetActiveUniformBlockiv = nullptr;
boom::OpenGLGetActiveUniformNameFn glGetActiveUniformName = nullptr;
boom::OpenGLGetActiveUniformsivFn glGetActiveUniformsiv = nullptr;
boom::OpenGLGetAttachedShadersFn glGetAttachedShaders = nullptr;
boom::OpenGLGetAttribLocationFn glGetAttribLocation = nullptr;
boom::OpenGLGetBooleani_vFn glGetBooleani_v = nullptr;
boom::OpenGLGetBooleanvFn glGetBooleanv = nullptr;
boom::OpenGLGetBufferParameteri64vFn glGetBufferParameteri64v = nullptr;
boom::OpenGLGetBufferParameterivFn glGetBufferParameteriv = nullptr;
boom::OpenGLGetBufferPointervFn glGetBufferPointerv = nullptr;
boom::OpenGLGetBufferSubDataFn glGetBufferSubData = nullptr;
boom::OpenGLGetClipPlaneFn glGetClipPlane = nullptr;
boom::OpenGLGetClipPlanefFn glGetClipPlanef = nullptr;
boom::OpenGLGetClipPlanexFn glGetClipPlanex = nullptr;
boom::OpenGLGetCompressedTexImageFn glGetCompressedTexImage = nullptr;
boom::OpenGLGetCompressedTextureImageFn glGetCompressedTextureImage = nullptr;
boom::OpenGLGetCompressedTextureSubImageFn glGetCompressedTextureSubImage = nullptr;
boom::OpenGLGetDebugMessageLogFn glGetDebugMessageLog = nullptr;
boom::OpenGLGetDoublei_vFn glGetDoublei_v = nullptr;
boom::OpenGLGetDoublevFn glGetDoublev = nullptr;
boom::OpenGLGetErrorFn glGetError = nullptr;
boom::OpenGLGetFixedvFn glGetFixedv = nullptr;
boom::OpenGLGetFloati_vFn glGetFloati_v = nullptr;
boom::OpenGLGetFloatvFn glGetFloatv = nullptr;
boom::OpenGLGetFragDataIndexFn glGetFragDataIndex = nullptr;
boom::OpenGLGetFragDataLocationFn glGetFragDataLocation = nullptr;
boom::OpenGLGetFramebufferAttachmentParameterivFn glGetFramebufferAttachmentParameteriv = nullptr;
boom::OpenGLGetFramebufferParameterivFn glGetFramebufferParameteriv = nullptr;
boom::OpenGLGetGraphicsResetStatusFn glGetGraphicsResetStatus = nullptr;
boom::OpenGLGetInteger64i_vFn glGetInteger64i_v = nullptr;
boom::OpenGLGetInteger64vFn glGetInteger64v = nullptr;
boom::OpenGLGetIntegeri_vFn glGetIntegeri_v = nullptr;
boom::OpenGLGetIntegervFn glGetIntegerv = nullptr;
boom::OpenGLGetInternalformati64vFn glGetInternalformati64v = nullptr;
boom::OpenGLGetInternalformativFn glGetInternalformativ = nullptr;
boom::OpenGLGetLightfvFn glGetLightfv = nullptr;
boom::OpenGLGetLightivFn glGetLightiv = nullptr;
boom::OpenGLGetLightxvFn glGetLightxv = nullptr;
boom::OpenGLGetMapdvFn glGetMapdv = nullptr;
boom::OpenGLGetMapfvFn glGetMapfv = nullptr;
boom::OpenGLGetMapivFn glGetMapiv = nullptr;
boom::OpenGLGetMaterialfvFn glGetMaterialfv = nullptr;
boom::OpenGLGetMaterialivFn glGetMaterialiv = nullptr;
boom::OpenGLGetMaterialxvFn glGetMaterialxv = nullptr;
boom::OpenGLGetMultisamplefvFn glGetMultisamplefv = nullptr;
boom::OpenGLGetNamedBufferParameteri64vFn glGetNamedBufferParameteri64v = nullptr;
boom::OpenGLGetNamedBufferParameterivFn glGetNamedBufferParameteriv = nullptr;
boom::OpenGLGetNamedBufferPointervFn glGetNamedBufferPointerv = nullptr;
boom::OpenGLGetNamedBufferSubDataFn glGetNamedBufferSubData = nullptr;
boom::OpenGLGetNamedFramebufferAttachmentParameterivFn glGetNamedFramebufferAttachmentParameteriv = nullptr;
boom::OpenGLGetNamedFramebufferParameterivFn glGetNamedFramebufferParameteriv = nullptr;
boom::OpenGLGetNamedRenderbufferParameterivFn glGetNamedRenderbufferParameteriv = nullptr;
boom::OpenGLGetObjectLabelFn glGetObjectLabel = nullptr;
boom::OpenGLGetObjectPtrLabelFn glGetObjectPtrLabel = nullptr;
boom::OpenGLGetPixelMapfvFn glGetPixelMapfv = nullptr;
boom::OpenGLGetPixelMapuivFn glGetPixelMapuiv = nullptr;
boom::OpenGLGetPixelMapusvFn glGetPixelMapusv = nullptr;
boom::OpenGLGetPointervFn glGetPointerv = nullptr;
boom::OpenGLGetPolygonStippleFn glGetPolygonStipple = nullptr;
boom::OpenGLGetProgramBinaryFn glGetProgramBinary = nullptr;
boom::OpenGLGetProgramInfoLogFn glGetProgramInfoLog = nullptr;
boom::OpenGLGetProgramInterfaceivFn glGetProgramInterfaceiv = nullptr;
boom::OpenGLGetProgramPipelineInfoLogFn glGetProgramPipelineInfoLog = nullptr;
boom::OpenGLGetProgramPipelineivFn glGetProgramPipelineiv = nullptr;
boom::OpenGLGetProgramResourceIndexFn glGetProgramResourceIndex = nullptr;
boom::OpenGLGetProgramResourceLocationFn glGetProgramResourceLocation = nullptr;
boom::OpenGLGetProgramResourceLocationIndexFn glGetProgramResourceLocationIndex = nullptr;
boom::OpenGLGetProgramResourceNameFn glGetProgramResourceName = nullptr;
boom::OpenGLGetProgramResourceivFn glGetProgramResourceiv = nullptr;
boom::OpenGLGetProgramStageivFn glGetProgramStageiv = nullptr;
boom::OpenGLGetProgramivFn glGetProgramiv = nullptr;
boom::OpenGLGetQueryBufferObjecti64vFn glGetQueryBufferObjecti64v = nullptr;
boom::OpenGLGetQueryBufferObjectivFn glGetQueryBufferObjectiv = nullptr;
boom::OpenGLGetQueryBufferObjectui64vFn glGetQueryBufferObjectui64v = nullptr;
boom::OpenGLGetQueryBufferObjectuivFn glGetQueryBufferObjectuiv = nullptr;
boom::OpenGLGetQueryIndexedivFn glGetQueryIndexediv = nullptr;
boom::OpenGLGetQueryObjecti64vFn glGetQueryObjecti64v = nullptr;
boom::OpenGLGetQueryObjectivFn glGetQueryObjectiv = nullptr;
boom::OpenGLGetQueryObjectui64vFn glGetQueryObjectui64v = nullptr;
boom::OpenGLGetQueryObjectuivFn glGetQueryObjectuiv = nullptr;
boom::OpenGLGetQueryivFn glGetQueryiv = nullptr;
boom::OpenGLGetRenderbufferParameterivFn glGetRenderbufferParameteriv = nullptr;
boom::OpenGLGetSamplerParameterIivFn glGetSamplerParameterIiv = nullptr;
boom::OpenGLGetSamplerParameterIuivFn glGetSamplerParameterIuiv = nullptr;
boom::OpenGLGetSamplerParameterfvFn glGetSamplerParameterfv = nullptr;
boom::OpenGLGetSamplerParameterivFn glGetSamplerParameteriv = nullptr;
boom::OpenGLGetShaderInfoLogFn glGetShaderInfoLog = nullptr;
boom::OpenGLGetShaderPrecisionFormatFn glGetShaderPrecisionFormat = nullptr;
boom::OpenGLGetShaderSourceFn glGetShaderSource = nullptr;
boom::OpenGLGetShaderivFn glGetShaderiv = nullptr;
boom::OpenGLGetStringFn glGetString = nullptr;
boom::OpenGLGetStringiFn glGetStringi = nullptr;
boom::OpenGLGetSubroutineIndexFn glGetSubroutineIndex = nullptr;
boom::OpenGLGetSubroutineUniformLocationFn glGetSubroutineUniformLocation = nullptr;
boom::OpenGLGetSyncivFn glGetSynciv = nullptr;
boom::OpenGLGetTexEnvfvFn glGetTexEnvfv = nullptr;
boom::OpenGLGetTexEnvivFn glGetTexEnviv = nullptr;
boom::OpenGLGetTexEnvxvFn glGetTexEnvxv = nullptr;
boom::OpenGLGetTexGendvFn glGetTexGendv = nullptr;
boom::OpenGLGetTexGenfvFn glGetTexGenfv = nullptr;
boom::OpenGLGetTexGenivFn glGetTexGeniv = nullptr;
boom::OpenGLGetTexImageFn glGetTexImage = nullptr;
boom::OpenGLGetTexLevelParameterfvFn glGetTexLevelParameterfv = nullptr;
boom::OpenGLGetTexLevelParameterivFn glGetTexLevelParameteriv = nullptr;
boom::OpenGLGetTexParameterIivFn glGetTexParameterIiv = nullptr;
boom::OpenGLGetTexParameterIuivFn glGetTexParameterIuiv = nullptr;
boom::OpenGLGetTexParameterfvFn glGetTexParameterfv = nullptr;
boom::OpenGLGetTexParameterivFn glGetTexParameteriv = nullptr;
boom::OpenGLGetTexParameterxvFn glGetTexParameterxv = nullptr;
boom::OpenGLGetTextureImageFn glGetTextureImage = nullptr;
boom::OpenGLGetTextureLevelParameterfvFn glGetTextureLevelParameterfv = nullptr;
boom::OpenGLGetTextureLevelParameterivFn glGetTextureLevelParameteriv = nullptr;
boom::OpenGLGetTextureParameterIivFn glGetTextureParameterIiv = nullptr;
boom::OpenGLGetTextureParameterIuivFn glGetTextureParameterIuiv = nullptr;
boom::OpenGLGetTextureParameterfvFn glGetTextureParameterfv = nullptr;
boom::OpenGLGetTextureParameterivFn glGetTextureParameteriv = nullptr;
boom::OpenGLGetTextureSubImageFn glGetTextureSubImage = nullptr;
boom::OpenGLGetTransformFeedbackVaryingFn glGetTransformFeedbackVarying = nullptr;
boom::OpenGLGetTransformFeedbacki64_vFn glGetTransformFeedbacki64_v = nullptr;
boom::OpenGLGetTransformFeedbacki_vFn glGetTransformFeedbacki_v = nullptr;
boom::OpenGLGetTransformFeedbackivFn glGetTransformFeedbackiv = nullptr;
boom::OpenGLGetUniformBlockIndexFn glGetUniformBlockIndex = nullptr;
boom::OpenGLGetUniformIndicesFn glGetUniformIndices = nullptr;
boom::OpenGLGetUniformLocationFn glGetUniformLocation = nullptr;
boom::OpenGLGetUniformSubroutineuivFn glGetUniformSubroutineuiv = nullptr;
boom::OpenGLGetUniformdvFn glGetUniformdv = nullptr;
boom::OpenGLGetUniformfvFn glGetUniformfv = nullptr;
boom::OpenGLGetUniformivFn glGetUniformiv = nullptr;
boom::OpenGLGetUniformuivFn glGetUniformuiv = nullptr;
boom::OpenGLGetVertexArrayIndexed64ivFn glGetVertexArrayIndexed64iv = nullptr;
boom::OpenGLGetVertexArrayIndexedivFn glGetVertexArrayIndexediv = nullptr;
boom::OpenGLGetVertexArrayivFn glGetVertexArrayiv = nullptr;
boom::OpenGLGetVertexAttribIivFn glGetVertexAttribIiv = nullptr;
boom::OpenGLGetVertexAttribIuivFn glGetVertexAttribIuiv = nullptr;
boom::OpenGLGetVertexAttribLdvFn glGetVertexAttribLdv = nullptr;
boom::OpenGLGetVertexAttribPointervFn glGetVertexAttribPointerv = nullptr;
boom::OpenGLGetVertexAttribdvFn glGetVertexAttribdv = nullptr;
boom::OpenGLGetVertexAttribfvFn glGetVertexAttribfv = nullptr;
boom::OpenGLGetVertexAttribivFn glGetVertexAttribiv = nullptr;
boom::OpenGLGetnColorTableFn glGetnColorTable = nullptr;
boom::OpenGLGetnCompressedTexImageFn glGetnCompressedTexImage = nullptr;
boom::OpenGLGetnConvolutionFilterFn glGetnConvolutionFilter = nullptr;
boom::OpenGLGetnHistogramFn glGetnHistogram = nullptr;
boom::OpenGLGetnMapdvFn glGetnMapdv = nullptr;
boom::OpenGLGetnMapfvFn glGetnMapfv = nullptr;
boom::OpenGLGetnMapivFn glGetnMapiv = nullptr;
boom::OpenGLGetnMinmaxFn glGetnMinmax = nullptr;
boom::OpenGLGetnPixelMapfvFn glGetnPixelMapfv = nullptr;
boom::OpenGLGetnPixelMapuivFn glGetnPixelMapuiv = nullptr;
boom::OpenGLGetnPixelMapusvFn glGetnPixelMapusv = nullptr;
boom::OpenGLGetnPolygonStippleFn glGetnPolygonStipple = nullptr;
boom::OpenGLGetnSeparableFilterFn glGetnSeparableFilter = nullptr;
boom::OpenGLGetnTexImageFn glGetnTexImage = nullptr;
boom::OpenGLGetnUniformdvFn glGetnUniformdv = nullptr;
boom::OpenGLGetnUniformfvFn glGetnUniformfv = nullptr;
boom::OpenGLGetnUniformivFn glGetnUniformiv = nullptr;
boom::OpenGLGetnUniformuivFn glGetnUniformuiv = nullptr;
boom::OpenGLHintFn glHint = nullptr;
boom::OpenGLIndexMaskFn glIndexMask = nullptr;
boom::OpenGLIndexPointerFn glIndexPointer = nullptr;
boom::OpenGLIndexdFn glIndexd = nullptr;
boom::OpenGLIndexdvFn glIndexdv = nullptr;
boom::OpenGLIndexfFn glIndexf = nullptr;
boom::OpenGLIndexfvFn glIndexfv = nullptr;
boom::OpenGLIndexiFn glIndexi = nullptr;
boom::OpenGLIndexivFn glIndexiv = nullptr;
boom::OpenGLIndexsFn glIndexs = nullptr;
boom::OpenGLIndexsvFn glIndexsv = nullptr;
boom::OpenGLIndexubFn glIndexub = nullptr;
boom::OpenGLIndexubvFn glIndexubv = nullptr;
boom::OpenGLInitNamesFn glInitNames = nullptr;
boom::OpenGLInterleavedArraysFn glInterleavedArrays = nullptr;
boom::OpenGLInvalidateBufferDataFn glInvalidateBufferData = nullptr;
boom::OpenGLInvalidateBufferSubDataFn glInvalidateBufferSubData = nullptr;
boom::OpenGLInvalidateFramebufferFn glInvalidateFramebuffer = nullptr;
boom::OpenGLInvalidateNamedFramebufferDataFn glInvalidateNamedFramebufferData = nullptr;
boom::OpenGLInvalidateNamedFramebufferSubDataFn glInvalidateNamedFramebufferSubData = nullptr;
boom::OpenGLInvalidateSubFramebufferFn glInvalidateSubFramebuffer = nullptr;
boom::OpenGLInvalidateTexImageFn glInvalidateTexImage = nullptr;
boom::OpenGLInvalidateTexSubImageFn glInvalidateTexSubImage = nullptr;
boom::OpenGLIsBufferFn glIsBuffer = nullptr;
boom::OpenGLIsEnabledFn glIsEnabled = nullptr;
boom::OpenGLIsEnablediFn glIsEnabledi = nullptr;
boom::OpenGLIsFramebufferFn glIsFramebuffer = nullptr;
boom::OpenGLIsListFn glIsList = nullptr;
boom::OpenGLIsProgramFn glIsProgram = nullptr;
boom::OpenGLIsProgramPipelineFn glIsProgramPipeline = nullptr;
boom::OpenGLIsQueryFn glIsQuery = nullptr;
boom::OpenGLIsRenderbufferFn glIsRenderbuffer = nullptr;
boom::OpenGLIsSamplerFn glIsSampler = nullptr;
boom::OpenGLIsShaderFn glIsShader = nullptr;
boom::OpenGLIsSyncFn glIsSync = nullptr;
boom::OpenGLIsTextureFn glIsTexture = nullptr;
boom::OpenGLIsTransformFeedbackFn glIsTransformFeedback = nullptr;
boom::OpenGLIsVertexArrayFn glIsVertexArray = nullptr;
boom::OpenGLLightModelfFn glLightModelf = nullptr;
boom::OpenGLLightModelfvFn glLightModelfv = nullptr;
boom::OpenGLLightModeliFn glLightModeli = nullptr;
boom::OpenGLLightModelivFn glLightModeliv = nullptr;
boom::OpenGLLightModelxFn glLightModelx = nullptr;
boom::OpenGLLightModelxvFn glLightModelxv = nullptr;
boom::OpenGLLightfFn glLightf = nullptr;
boom::OpenGLLightfvFn glLightfv = nullptr;
boom::OpenGLLightiFn glLighti = nullptr;
boom::OpenGLLightivFn glLightiv = nullptr;
boom::OpenGLLightxFn glLightx = nullptr;
boom::OpenGLLightxvFn glLightxv = nullptr;
boom::OpenGLLineStippleFn glLineStipple = nullptr;
boom::OpenGLLineWidthFn glLineWidth = nullptr;
boom::OpenGLLineWidthxFn glLineWidthx = nullptr;
boom::OpenGLLinkProgramFn glLinkProgram = nullptr;
boom::OpenGLListBaseFn glListBase = nullptr;
boom::OpenGLLoadIdentityFn glLoadIdentity = nullptr;
boom::OpenGLLoadMatrixdFn glLoadMatrixd = nullptr;
boom::OpenGLLoadMatrixfFn glLoadMatrixf = nullptr;
boom::OpenGLLoadMatrixxFn glLoadMatrixx = nullptr;
boom::OpenGLLoadNameFn glLoadName = nullptr;
boom::OpenGLLoadTransposeMatrixdFn glLoadTransposeMatrixd = nullptr;
boom::OpenGLLoadTransposeMatrixfFn glLoadTransposeMatrixf = nullptr;
boom::OpenGLLogicOpFn glLogicOp = nullptr;
boom::OpenGLMap1dFn glMap1d = nullptr;
boom::OpenGLMap1fFn glMap1f = nullptr;
boom::OpenGLMap2dFn glMap2d = nullptr;
boom::OpenGLMap2fFn glMap2f = nullptr;
boom::OpenGLMapBufferFn glMapBuffer = nullptr;
boom::OpenGLMapBufferRangeFn glMapBufferRange = nullptr;
boom::OpenGLMapGrid1dFn glMapGrid1d = nullptr;
boom::OpenGLMapGrid1fFn glMapGrid1f = nullptr;
boom::OpenGLMapGrid2dFn glMapGrid2d = nullptr;
boom::OpenGLMapGrid2fFn glMapGrid2f = nullptr;
boom::OpenGLMapNamedBufferFn glMapNamedBuffer = nullptr;
boom::OpenGLMapNamedBufferRangeFn glMapNamedBufferRange = nullptr;
boom::OpenGLMaterialfFn glMaterialf = nullptr;
boom::OpenGLMaterialfvFn glMaterialfv = nullptr;
boom::OpenGLMaterialiFn glMateriali = nullptr;
boom::OpenGLMaterialivFn glMaterialiv = nullptr;
boom::OpenGLMaterialxFn glMaterialx = nullptr;
boom::OpenGLMaterialxvFn glMaterialxv = nullptr;
boom::OpenGLMatrixModeFn glMatrixMode = nullptr;
boom::OpenGLMemoryBarrierFn glMemoryBarrier = nullptr;
boom::OpenGLMemoryBarrierByRegionFn glMemoryBarrierByRegion = nullptr;
boom::OpenGLMinSampleShadingFn glMinSampleShading = nullptr;
boom::OpenGLMultMatrixdFn glMultMatrixd = nullptr;
boom::OpenGLMultMatrixfFn glMultMatrixf = nullptr;
boom::OpenGLMultMatrixxFn glMultMatrixx = nullptr;
boom::OpenGLMultTransposeMatrixdFn glMultTransposeMatrixd = nullptr;
boom::OpenGLMultTransposeMatrixfFn glMultTransposeMatrixf = nullptr;
boom::OpenGLMultiDrawArraysFn glMultiDrawArrays = nullptr;
boom::OpenGLMultiDrawArraysIndirectFn glMultiDrawArraysIndirect = nullptr;
boom::OpenGLMultiDrawArraysIndirectCountFn glMultiDrawArraysIndirectCount = nullptr;
boom::OpenGLMultiDrawElementsFn glMultiDrawElements = nullptr;
boom::OpenGLMultiDrawElementsBaseVertexFn glMultiDrawElementsBaseVertex = nullptr;
boom::OpenGLMultiDrawElementsIndirectFn glMultiDrawElementsIndirect = nullptr;
boom::OpenGLMultiDrawElementsIndirectCountFn glMultiDrawElementsIndirectCount = nullptr;
boom::OpenGLMultiTexCoord1dFn glMultiTexCoord1d = nullptr;
boom::OpenGLMultiTexCoord1dvFn glMultiTexCoord1dv = nullptr;
boom::OpenGLMultiTexCoord1fFn glMultiTexCoord1f = nullptr;
boom::OpenGLMultiTexCoord1fvFn glMultiTexCoord1fv = nullptr;
boom::OpenGLMultiTexCoord1iFn glMultiTexCoord1i = nullptr;
boom::OpenGLMultiTexCoord1ivFn glMultiTexCoord1iv = nullptr;
boom::OpenGLMultiTexCoord1sFn glMultiTexCoord1s = nullptr;
boom::OpenGLMultiTexCoord1svFn glMultiTexCoord1sv = nullptr;
boom::OpenGLMultiTexCoord2dFn glMultiTexCoord2d = nullptr;
boom::OpenGLMultiTexCoord2dvFn glMultiTexCoord2dv = nullptr;
boom::OpenGLMultiTexCoord2fFn glMultiTexCoord2f = nullptr;
boom::OpenGLMultiTexCoord2fvFn glMultiTexCoord2fv = nullptr;
boom::OpenGLMultiTexCoord2iFn glMultiTexCoord2i = nullptr;
boom::OpenGLMultiTexCoord2ivFn glMultiTexCoord2iv = nullptr;
boom::OpenGLMultiTexCoord2sFn glMultiTexCoord2s = nullptr;
boom::OpenGLMultiTexCoord2svFn glMultiTexCoord2sv = nullptr;
boom::OpenGLMultiTexCoord3dFn glMultiTexCoord3d = nullptr;
boom::OpenGLMultiTexCoord3dvFn glMultiTexCoord3dv = nullptr;
boom::OpenGLMultiTexCoord3fFn glMultiTexCoord3f = nullptr;
boom::OpenGLMultiTexCoord3fvFn glMultiTexCoord3fv = nullptr;
boom::OpenGLMultiTexCoord3iFn glMultiTexCoord3i = nullptr;
boom::OpenGLMultiTexCoord3ivFn glMultiTexCoord3iv = nullptr;
boom::OpenGLMultiTexCoord3sFn glMultiTexCoord3s = nullptr;
boom::OpenGLMultiTexCoord3svFn glMultiTexCoord3sv = nullptr;
boom::OpenGLMultiTexCoord4dFn glMultiTexCoord4d = nullptr;
boom::OpenGLMultiTexCoord4dvFn glMultiTexCoord4dv = nullptr;
boom::OpenGLMultiTexCoord4fFn glMultiTexCoord4f = nullptr;
boom::OpenGLMultiTexCoord4fvFn glMultiTexCoord4fv = nullptr;
boom::OpenGLMultiTexCoord4iFn glMultiTexCoord4i = nullptr;
boom::OpenGLMultiTexCoord4ivFn glMultiTexCoord4iv = nullptr;
boom::OpenGLMultiTexCoord4sFn glMultiTexCoord4s = nullptr;
boom::OpenGLMultiTexCoord4svFn glMultiTexCoord4sv = nullptr;
boom::OpenGLMultiTexCoord4xFn glMultiTexCoord4x = nullptr;
boom::OpenGLMultiTexCoordP1uiFn glMultiTexCoordP1ui = nullptr;
boom::OpenGLMultiTexCoordP1uivFn glMultiTexCoordP1uiv = nullptr;
boom::OpenGLMultiTexCoordP2uiFn glMultiTexCoordP2ui = nullptr;
boom::OpenGLMultiTexCoordP2uivFn glMultiTexCoordP2uiv = nullptr;
boom::OpenGLMultiTexCoordP3uiFn glMultiTexCoordP3ui = nullptr;
boom::OpenGLMultiTexCoordP3uivFn glMultiTexCoordP3uiv = nullptr;
boom::OpenGLMultiTexCoordP4uiFn glMultiTexCoordP4ui = nullptr;
boom::OpenGLMultiTexCoordP4uivFn glMultiTexCoordP4uiv = nullptr;
boom::OpenGLNamedBufferDataFn glNamedBufferData = nullptr;
boom::OpenGLNamedBufferStorageFn glNamedBufferStorage = nullptr;
boom::OpenGLNamedBufferSubDataFn glNamedBufferSubData = nullptr;
boom::OpenGLNamedFramebufferDrawBufferFn glNamedFramebufferDrawBuffer = nullptr;
boom::OpenGLNamedFramebufferDrawBuffersFn glNamedFramebufferDrawBuffers = nullptr;
boom::OpenGLNamedFramebufferParameteriFn glNamedFramebufferParameteri = nullptr;
boom::OpenGLNamedFramebufferReadBufferFn glNamedFramebufferReadBuffer = nullptr;
boom::OpenGLNamedFramebufferRenderbufferFn glNamedFramebufferRenderbuffer = nullptr;
boom::OpenGLNamedFramebufferTextureFn glNamedFramebufferTexture = nullptr;
boom::OpenGLNamedFramebufferTextureLayerFn glNamedFramebufferTextureLayer = nullptr;
boom::OpenGLNamedRenderbufferStorageFn glNamedRenderbufferStorage = nullptr;
boom::OpenGLNamedRenderbufferStorageMultisampleFn glNamedRenderbufferStorageMultisample = nullptr;
boom::OpenGLNewListFn glNewList = nullptr;
boom::OpenGLNormal3bFn glNormal3b = nullptr;
boom::OpenGLNormal3bvFn glNormal3bv = nullptr;
boom::OpenGLNormal3dFn glNormal3d = nullptr;
boom::OpenGLNormal3dvFn glNormal3dv = nullptr;
boom::OpenGLNormal3fFn glNormal3f = nullptr;
boom::OpenGLNormal3fvFn glNormal3fv = nullptr;
boom::OpenGLNormal3iFn glNormal3i = nullptr;
boom::OpenGLNormal3ivFn glNormal3iv = nullptr;
boom::OpenGLNormal3sFn glNormal3s = nullptr;
boom::OpenGLNormal3svFn glNormal3sv = nullptr;
boom::OpenGLNormal3xFn glNormal3x = nullptr;
boom::OpenGLNormalP3uiFn glNormalP3ui = nullptr;
boom::OpenGLNormalP3uivFn glNormalP3uiv = nullptr;
boom::OpenGLNormalPointerFn glNormalPointer = nullptr;
boom::OpenGLObjectLabelFn glObjectLabel = nullptr;
boom::OpenGLObjectPtrLabelFn glObjectPtrLabel = nullptr;
boom::OpenGLOrthoFn glOrtho = nullptr;
boom::OpenGLOrthofFn glOrthof = nullptr;
boom::OpenGLOrthoxFn glOrthox = nullptr;
boom::OpenGLPassThroughFn glPassThrough = nullptr;
boom::OpenGLPatchParameterfvFn glPatchParameterfv = nullptr;
boom::OpenGLPatchParameteriFn glPatchParameteri = nullptr;
boom::OpenGLPauseTransformFeedbackFn glPauseTransformFeedback = nullptr;
boom::OpenGLPixelMapfvFn glPixelMapfv = nullptr;
boom::OpenGLPixelMapuivFn glPixelMapuiv = nullptr;
boom::OpenGLPixelMapusvFn glPixelMapusv = nullptr;
boom::OpenGLPixelStorefFn glPixelStoref = nullptr;
boom::OpenGLPixelStoreiFn glPixelStorei = nullptr;
boom::OpenGLPixelTransferfFn glPixelTransferf = nullptr;
boom::OpenGLPixelTransferiFn glPixelTransferi = nullptr;
boom::OpenGLPixelZoomFn glPixelZoom = nullptr;
boom::OpenGLPointParameterfFn glPointParameterf = nullptr;
boom::OpenGLPointParameterfvFn glPointParameterfv = nullptr;
boom::OpenGLPointParameteriFn glPointParameteri = nullptr;
boom::OpenGLPointParameterivFn glPointParameteriv = nullptr;
boom::OpenGLPointParameterxFn glPointParameterx = nullptr;
boom::OpenGLPointParameterxvFn glPointParameterxv = nullptr;
boom::OpenGLPointSizeFn glPointSize = nullptr;
boom::OpenGLPointSizexFn glPointSizex = nullptr;
boom::OpenGLPolygonModeFn glPolygonMode = nullptr;
boom::OpenGLPolygonOffsetFn glPolygonOffset = nullptr;
boom::OpenGLPolygonOffsetClampFn glPolygonOffsetClamp = nullptr;
boom::OpenGLPolygonOffsetxFn glPolygonOffsetx = nullptr;
boom::OpenGLPolygonStippleFn glPolygonStipple = nullptr;
boom::OpenGLPopAttribFn glPopAttrib = nullptr;
boom::OpenGLPopClientAttribFn glPopClientAttrib = nullptr;
boom::OpenGLPopDebugGroupFn glPopDebugGroup = nullptr;
boom::OpenGLPopMatrixFn glPopMatrix = nullptr;
boom::OpenGLPopNameFn glPopName = nullptr;
boom::OpenGLPrimitiveBoundingBoxFn glPrimitiveBoundingBox = nullptr;
boom::OpenGLPrimitiveRestartIndexFn glPrimitiveRestartIndex = nullptr;
boom::OpenGLPrioritizeTexturesFn glPrioritizeTextures = nullptr;
boom::OpenGLProgramBinaryFn glProgramBinary = nullptr;
boom::OpenGLProgramParameteriFn glProgramParameteri = nullptr;
boom::OpenGLProgramUniform1dFn glProgramUniform1d = nullptr;
boom::OpenGLProgramUniform1dvFn glProgramUniform1dv = nullptr;
boom::OpenGLProgramUniform1fFn glProgramUniform1f = nullptr;
boom::OpenGLProgramUniform1fvFn glProgramUniform1fv = nullptr;
boom::OpenGLProgramUniform1iFn glProgramUniform1i = nullptr;
boom::OpenGLProgramUniform1ivFn glProgramUniform1iv = nullptr;
boom::OpenGLProgramUniform1uiFn glProgramUniform1ui = nullptr;
boom::OpenGLProgramUniform1uivFn glProgramUniform1uiv = nullptr;
boom::OpenGLProgramUniform2dFn glProgramUniform2d = nullptr;
boom::OpenGLProgramUniform2dvFn glProgramUniform2dv = nullptr;
boom::OpenGLProgramUniform2fFn glProgramUniform2f = nullptr;
boom::OpenGLProgramUniform2fvFn glProgramUniform2fv = nullptr;
boom::OpenGLProgramUniform2iFn glProgramUniform2i = nullptr;
boom::OpenGLProgramUniform2ivFn glProgramUniform2iv = nullptr;
boom::OpenGLProgramUniform2uiFn glProgramUniform2ui = nullptr;
boom::OpenGLProgramUniform2uivFn glProgramUniform2uiv = nullptr;
boom::OpenGLProgramUniform3dFn glProgramUniform3d = nullptr;
boom::OpenGLProgramUniform3dvFn glProgramUniform3dv = nullptr;
boom::OpenGLProgramUniform3fFn glProgramUniform3f = nullptr;
boom::OpenGLProgramUniform3fvFn glProgramUniform3fv = nullptr;
boom::OpenGLProgramUniform3iFn glProgramUniform3i = nullptr;
boom::OpenGLProgramUniform3ivFn glProgramUniform3iv = nullptr;
boom::OpenGLProgramUniform3uiFn glProgramUniform3ui = nullptr;
boom::OpenGLProgramUniform3uivFn glProgramUniform3uiv = nullptr;
boom::OpenGLProgramUniform4dFn glProgramUniform4d = nullptr;
boom::OpenGLProgramUniform4dvFn glProgramUniform4dv = nullptr;
boom::OpenGLProgramUniform4fFn glProgramUniform4f = nullptr;
boom::OpenGLProgramUniform4fvFn glProgramUniform4fv = nullptr;
boom::OpenGLProgramUniform4iFn glProgramUniform4i = nullptr;
boom::OpenGLProgramUniform4ivFn glProgramUniform4iv = nullptr;
boom::OpenGLProgramUniform4uiFn glProgramUniform4ui = nullptr;
boom::OpenGLProgramUniform4uivFn glProgramUniform4uiv = nullptr;
boom::OpenGLProgramUniformMatrix2dvFn glProgramUniformMatrix2dv = nullptr;
boom::OpenGLProgramUniformMatrix2fvFn glProgramUniformMatrix2fv = nullptr;
boom::OpenGLProgramUniformMatrix2x3dvFn glProgramUniformMatrix2x3dv = nullptr;
boom::OpenGLProgramUniformMatrix2x3fvFn glProgramUniformMatrix2x3fv = nullptr;
boom::OpenGLProgramUniformMatrix2x4dvFn glProgramUniformMatrix2x4dv = nullptr;
boom::OpenGLProgramUniformMatrix2x4fvFn glProgramUniformMatrix2x4fv = nullptr;
boom::OpenGLProgramUniformMatrix3dvFn glProgramUniformMatrix3dv = nullptr;
boom::OpenGLProgramUniformMatrix3fvFn glProgramUniformMatrix3fv = nullptr;
boom::OpenGLProgramUniformMatrix3x2dvFn glProgramUniformMatrix3x2dv = nullptr;
boom::OpenGLProgramUniformMatrix3x2fvFn glProgramUniformMatrix3x2fv = nullptr;
boom::OpenGLProgramUniformMatrix3x4dvFn glProgramUniformMatrix3x4dv = nullptr;
boom::OpenGLProgramUniformMatrix3x4fvFn glProgramUniformMatrix3x4fv = nullptr;
boom::OpenGLProgramUniformMatrix4dvFn glProgramUniformMatrix4dv = nullptr;
boom::OpenGLProgramUniformMatrix4fvFn glProgramUniformMatrix4fv = nullptr;
boom::OpenGLProgramUniformMatrix4x2dvFn glProgramUniformMatrix4x2dv = nullptr;
boom::OpenGLProgramUniformMatrix4x2fvFn glProgramUniformMatrix4x2fv = nullptr;
boom::OpenGLProgramUniformMatrix4x3dvFn glProgramUniformMatrix4x3dv = nullptr;
boom::OpenGLProgramUniformMatrix4x3fvFn glProgramUniformMatrix4x3fv = nullptr;
boom::OpenGLProvokingVertexFn glProvokingVertex = nullptr;
boom::OpenGLPushAttribFn glPushAttrib = nullptr;
boom::OpenGLPushClientAttribFn glPushClientAttrib = nullptr;
boom::OpenGLPushDebugGroupFn glPushDebugGroup = nullptr;
boom::OpenGLPushMatrixFn glPushMatrix = nullptr;
boom::OpenGLPushNameFn glPushName = nullptr;
boom::OpenGLQueryCounterFn glQueryCounter = nullptr;
boom::OpenGLRasterPos2dFn glRasterPos2d = nullptr;
boom::OpenGLRasterPos2dvFn glRasterPos2dv = nullptr;
boom::OpenGLRasterPos2fFn glRasterPos2f = nullptr;
boom::OpenGLRasterPos2fvFn glRasterPos2fv = nullptr;
boom::OpenGLRasterPos2iFn glRasterPos2i = nullptr;
boom::OpenGLRasterPos2ivFn glRasterPos2iv = nullptr;
boom::OpenGLRasterPos2sFn glRasterPos2s = nullptr;
boom::OpenGLRasterPos2svFn glRasterPos2sv = nullptr;
boom::OpenGLRasterPos3dFn glRasterPos3d = nullptr;
boom::OpenGLRasterPos3dvFn glRasterPos3dv = nullptr;
boom::OpenGLRasterPos3fFn glRasterPos3f = nullptr;
boom::OpenGLRasterPos3fvFn glRasterPos3fv = nullptr;
boom::OpenGLRasterPos3iFn glRasterPos3i = nullptr;
boom::OpenGLRasterPos3ivFn glRasterPos3iv = nullptr;
boom::OpenGLRasterPos3sFn glRasterPos3s = nullptr;
boom::OpenGLRasterPos3svFn glRasterPos3sv = nullptr;
boom::OpenGLRasterPos4dFn glRasterPos4d = nullptr;
boom::OpenGLRasterPos4dvFn glRasterPos4dv = nullptr;
boom::OpenGLRasterPos4fFn glRasterPos4f = nullptr;
boom::OpenGLRasterPos4fvFn glRasterPos4fv = nullptr;
boom::OpenGLRasterPos4iFn glRasterPos4i = nullptr;
boom::OpenGLRasterPos4ivFn glRasterPos4iv = nullptr;
boom::OpenGLRasterPos4sFn glRasterPos4s = nullptr;
boom::OpenGLRasterPos4svFn glRasterPos4sv = nullptr;
boom::OpenGLReadBufferFn glReadBuffer = nullptr;
boom::OpenGLReadPixelsFn glReadPixels = nullptr;
boom::OpenGLReadnPixelsFn glReadnPixels = nullptr;
boom::OpenGLRectdFn glRectd = nullptr;
boom::OpenGLRectdvFn glRectdv = nullptr;
boom::OpenGLRectfFn glRectf = nullptr;
boom::OpenGLRectfvFn glRectfv = nullptr;
boom::OpenGLRectiFn glRecti = nullptr;
boom::OpenGLRectivFn glRectiv = nullptr;
boom::OpenGLRectsFn glRects = nullptr;
boom::OpenGLRectsvFn glRectsv = nullptr;
boom::OpenGLReleaseShaderCompilerFn glReleaseShaderCompiler = nullptr;
boom::OpenGLRenderModeFn glRenderMode = nullptr;
boom::OpenGLRenderbufferStorageFn glRenderbufferStorage = nullptr;
boom::OpenGLRenderbufferStorageMultisampleFn glRenderbufferStorageMultisample = nullptr;
boom::OpenGLResumeTransformFeedbackFn glResumeTransformFeedback = nullptr;
boom::OpenGLRotatedFn glRotated = nullptr;
boom::OpenGLRotatefFn glRotatef = nullptr;
boom::OpenGLRotatexFn glRotatex = nullptr;
boom::OpenGLSampleCoverageFn glSampleCoverage = nullptr;
boom::OpenGLSampleCoveragexFn glSampleCoveragex = nullptr;
boom::OpenGLSampleMaskiFn glSampleMaski = nullptr;
boom::OpenGLSamplerParameterIivFn glSamplerParameterIiv = nullptr;
boom::OpenGLSamplerParameterIuivFn glSamplerParameterIuiv = nullptr;
boom::OpenGLSamplerParameterfFn glSamplerParameterf = nullptr;
boom::OpenGLSamplerParameterfvFn glSamplerParameterfv = nullptr;
boom::OpenGLSamplerParameteriFn glSamplerParameteri = nullptr;
boom::OpenGLSamplerParameterivFn glSamplerParameteriv = nullptr;
boom::OpenGLScaledFn glScaled = nullptr;
boom::OpenGLScalefFn glScalef = nullptr;
boom::OpenGLScalexFn glScalex = nullptr;
boom::OpenGLScissorFn glScissor = nullptr;
boom::OpenGLScissorArrayvFn glScissorArrayv = nullptr;
boom::OpenGLScissorIndexedFn glScissorIndexed = nullptr;
boom::OpenGLScissorIndexedvFn glScissorIndexedv = nullptr;
boom::OpenGLSecondaryColor3bFn glSecondaryColor3b = nullptr;
boom::OpenGLSecondaryColor3bvFn glSecondaryColor3bv = nullptr;
boom::OpenGLSecondaryColor3dFn glSecondaryColor3d = nullptr;
boom::OpenGLSecondaryColor3dvFn glSecondaryColor3dv = nullptr;
boom::OpenGLSecondaryColor3fFn glSecondaryColor3f = nullptr;
boom::OpenGLSecondaryColor3fvFn glSecondaryColor3fv = nullptr;
boom::OpenGLSecondaryColor3iFn glSecondaryColor3i = nullptr;
boom::OpenGLSecondaryColor3ivFn glSecondaryColor3iv = nullptr;
boom::OpenGLSecondaryColor3sFn glSecondaryColor3s = nullptr;
boom::OpenGLSecondaryColor3svFn glSecondaryColor3sv = nullptr;
boom::OpenGLSecondaryColor3ubFn glSecondaryColor3ub = nullptr;
boom::OpenGLSecondaryColor3ubvFn glSecondaryColor3ubv = nullptr;
boom::OpenGLSecondaryColor3uiFn glSecondaryColor3ui = nullptr;
boom::OpenGLSecondaryColor3uivFn glSecondaryColor3uiv = nullptr;
boom::OpenGLSecondaryColor3usFn glSecondaryColor3us = nullptr;
boom::OpenGLSecondaryColor3usvFn glSecondaryColor3usv = nullptr;
boom::OpenGLSecondaryColorP3uiFn glSecondaryColorP3ui = nullptr;
boom::OpenGLSecondaryColorP3uivFn glSecondaryColorP3uiv = nullptr;
boom::OpenGLSecondaryColorPointerFn glSecondaryColorPointer = nullptr;
boom::OpenGLSelectBufferFn glSelectBuffer = nullptr;
boom::OpenGLShadeModelFn glShadeModel = nullptr;
boom::OpenGLShaderBinaryFn glShaderBinary = nullptr;
boom::OpenGLShaderSourceFn glShaderSource = nullptr;
boom::OpenGLShaderStorageBlockBindingFn glShaderStorageBlockBinding = nullptr;
boom::OpenGLSpecializeShaderFn glSpecializeShader = nullptr;
boom::OpenGLStencilFuncFn glStencilFunc = nullptr;
boom::OpenGLStencilFuncSeparateFn glStencilFuncSeparate = nullptr;
boom::OpenGLStencilMaskFn glStencilMask = nullptr;
boom::OpenGLStencilMaskSeparateFn glStencilMaskSeparate = nullptr;
boom::OpenGLStencilOpFn glStencilOp = nullptr;
boom::OpenGLStencilOpSeparateFn glStencilOpSeparate = nullptr;
boom::OpenGLTexBufferFn glTexBuffer = nullptr;
boom::OpenGLTexBufferRangeFn glTexBufferRange = nullptr;
boom::OpenGLTexCoord1dFn glTexCoord1d = nullptr;
boom::OpenGLTexCoord1dvFn glTexCoord1dv = nullptr;
boom::OpenGLTexCoord1fFn glTexCoord1f = nullptr;
boom::OpenGLTexCoord1fvFn glTexCoord1fv = nullptr;
boom::OpenGLTexCoord1iFn glTexCoord1i = nullptr;
boom::OpenGLTexCoord1ivFn glTexCoord1iv = nullptr;
boom::OpenGLTexCoord1sFn glTexCoord1s = nullptr;
boom::OpenGLTexCoord1svFn glTexCoord1sv = nullptr;
boom::OpenGLTexCoord2dFn glTexCoord2d = nullptr;
boom::OpenGLTexCoord2dvFn glTexCoord2dv = nullptr;
boom::OpenGLTexCoord2fFn glTexCoord2f = nullptr;
boom::OpenGLTexCoord2fvFn glTexCoord2fv = nullptr;
boom::OpenGLTexCoord2iFn glTexCoord2i = nullptr;
boom::OpenGLTexCoord2ivFn glTexCoord2iv = nullptr;
boom::OpenGLTexCoord2sFn glTexCoord2s = nullptr;
boom::OpenGLTexCoord2svFn glTexCoord2sv = nullptr;
boom::OpenGLTexCoord3dFn glTexCoord3d = nullptr;
boom::OpenGLTexCoord3dvFn glTexCoord3dv = nullptr;
boom::OpenGLTexCoord3fFn glTexCoord3f = nullptr;
boom::OpenGLTexCoord3fvFn glTexCoord3fv = nullptr;
boom::OpenGLTexCoord3iFn glTexCoord3i = nullptr;
boom::OpenGLTexCoord3ivFn glTexCoord3iv = nullptr;
boom::OpenGLTexCoord3sFn glTexCoord3s = nullptr;
boom::OpenGLTexCoord3svFn glTexCoord3sv = nullptr;
boom::OpenGLTexCoord4dFn glTexCoord4d = nullptr;
boom::OpenGLTexCoord4dvFn glTexCoord4dv = nullptr;
boom::OpenGLTexCoord4fFn glTexCoord4f = nullptr;
boom::OpenGLTexCoord4fvFn glTexCoord4fv = nullptr;
boom::OpenGLTexCoord4iFn glTexCoord4i = nullptr;
boom::OpenGLTexCoord4ivFn glTexCoord4iv = nullptr;
boom::OpenGLTexCoord4sFn glTexCoord4s = nullptr;
boom::OpenGLTexCoord4svFn glTexCoord4sv = nullptr;
boom::OpenGLTexCoordP1uiFn glTexCoordP1ui = nullptr;
boom::OpenGLTexCoordP1uivFn glTexCoordP1uiv = nullptr;
boom::OpenGLTexCoordP2uiFn glTexCoordP2ui = nullptr;
boom::OpenGLTexCoordP2uivFn glTexCoordP2uiv = nullptr;
boom::OpenGLTexCoordP3uiFn glTexCoordP3ui = nullptr;
boom::OpenGLTexCoordP3uivFn glTexCoordP3uiv = nullptr;
boom::OpenGLTexCoordP4uiFn glTexCoordP4ui = nullptr;
boom::OpenGLTexCoordP4uivFn glTexCoordP4uiv = nullptr;
boom::OpenGLTexCoordPointerFn glTexCoordPointer = nullptr;
boom::OpenGLTexEnvfFn glTexEnvf = nullptr;
boom::OpenGLTexEnvfvFn glTexEnvfv = nullptr;
boom::OpenGLTexEnviFn glTexEnvi = nullptr;
boom::OpenGLTexEnvivFn glTexEnviv = nullptr;
boom::OpenGLTexEnvxFn glTexEnvx = nullptr;
boom::OpenGLTexEnvxvFn glTexEnvxv = nullptr;
boom::OpenGLTexGendFn glTexGend = nullptr;
boom::OpenGLTexGendvFn glTexGendv = nullptr;
boom::OpenGLTexGenfFn glTexGenf = nullptr;
boom::OpenGLTexGenfvFn glTexGenfv = nullptr;
boom::OpenGLTexGeniFn glTexGeni = nullptr;
boom::OpenGLTexGenivFn glTexGeniv = nullptr;
boom::OpenGLTexImage1DFn glTexImage1D = nullptr;
boom::OpenGLTexImage2DFn glTexImage2D = nullptr;
boom::OpenGLTexImage2DMultisampleFn glTexImage2DMultisample = nullptr;
boom::OpenGLTexImage3DFn glTexImage3D = nullptr;
boom::OpenGLTexImage3DMultisampleFn glTexImage3DMultisample = nullptr;
boom::OpenGLTexParameterIivFn glTexParameterIiv = nullptr;
boom::OpenGLTexParameterIuivFn glTexParameterIuiv = nullptr;
boom::OpenGLTexParameterfFn glTexParameterf = nullptr;
boom::OpenGLTexParameterfvFn glTexParameterfv = nullptr;
boom::OpenGLTexParameteriFn glTexParameteri = nullptr;
boom::OpenGLTexParameterivFn glTexParameteriv = nullptr;
boom::OpenGLTexParameterxFn glTexParameterx = nullptr;
boom::OpenGLTexParameterxvFn glTexParameterxv = nullptr;
boom::OpenGLTexStorage1DFn glTexStorage1D = nullptr;
boom::OpenGLTexStorage2DFn glTexStorage2D = nullptr;
boom::OpenGLTexStorage2DMultisampleFn glTexStorage2DMultisample = nullptr;
boom::OpenGLTexStorage3DFn glTexStorage3D = nullptr;
boom::OpenGLTexStorage3DMultisampleFn glTexStorage3DMultisample = nullptr;
boom::OpenGLTexSubImage1DFn glTexSubImage1D = nullptr;
boom::OpenGLTexSubImage2DFn glTexSubImage2D = nullptr;
boom::OpenGLTexSubImage3DFn glTexSubImage3D = nullptr;
boom::OpenGLTextureBarrierFn glTextureBarrier = nullptr;
boom::OpenGLTextureBufferFn glTextureBuffer = nullptr;
boom::OpenGLTextureBufferRangeFn glTextureBufferRange = nullptr;
boom::OpenGLTextureParameterIivFn glTextureParameterIiv = nullptr;
boom::OpenGLTextureParameterIuivFn glTextureParameterIuiv = nullptr;
boom::OpenGLTextureParameterfFn glTextureParameterf = nullptr;
boom::OpenGLTextureParameterfvFn glTextureParameterfv = nullptr;
boom::OpenGLTextureParameteriFn glTextureParameteri = nullptr;
boom::OpenGLTextureParameterivFn glTextureParameteriv = nullptr;
boom::OpenGLTextureStorage1DFn glTextureStorage1D = nullptr;
boom::OpenGLTextureStorage2DFn glTextureStorage2D = nullptr;
boom::OpenGLTextureStorage2DMultisampleFn glTextureStorage2DMultisample = nullptr;
boom::OpenGLTextureStorage3DFn glTextureStorage3D = nullptr;
boom::OpenGLTextureStorage3DMultisampleFn glTextureStorage3DMultisample = nullptr;
boom::OpenGLTextureSubImage1DFn glTextureSubImage1D = nullptr;
boom::OpenGLTextureSubImage2DFn glTextureSubImage2D = nullptr;
boom::OpenGLTextureSubImage3DFn glTextureSubImage3D = nullptr;
boom::OpenGLTextureViewFn glTextureView = nullptr;
boom::OpenGLTransformFeedbackBufferBaseFn glTransformFeedbackBufferBase = nullptr;
boom::OpenGLTransformFeedbackBufferRangeFn glTransformFeedbackBufferRange = nullptr;
boom::OpenGLTransformFeedbackVaryingsFn glTransformFeedbackVaryings = nullptr;
boom::OpenGLTranslatedFn glTranslated = nullptr;
boom::OpenGLTranslatefFn glTranslatef = nullptr;
boom::OpenGLTranslatexFn glTranslatex = nullptr;
boom::OpenGLUniform1dFn glUniform1d = nullptr;
boom::OpenGLUniform1dvFn glUniform1dv = nullptr;
boom::OpenGLUniform1fFn glUniform1f = nullptr;
boom::OpenGLUniform1fvFn glUniform1fv = nullptr;
boom::OpenGLUniform1iFn glUniform1i = nullptr;
boom::OpenGLUniform1ivFn glUniform1iv = nullptr;
boom::OpenGLUniform1uiFn glUniform1ui = nullptr;
boom::OpenGLUniform1uivFn glUniform1uiv = nullptr;
boom::OpenGLUniform2dFn glUniform2d = nullptr;
boom::OpenGLUniform2dvFn glUniform2dv = nullptr;
boom::OpenGLUniform2fFn glUniform2f = nullptr;
boom::OpenGLUniform2fvFn glUniform2fv = nullptr;
boom::OpenGLUniform2iFn glUniform2i = nullptr;
boom::OpenGLUniform2ivFn glUniform2iv = nullptr;
boom::OpenGLUniform2uiFn glUniform2ui = nullptr;
boom::OpenGLUniform2uivFn glUniform2uiv = nullptr;
boom::OpenGLUniform3dFn glUniform3d = nullptr;
boom::OpenGLUniform3dvFn glUniform3dv = nullptr;
boom::OpenGLUniform3fFn glUniform3f = nullptr;
boom::OpenGLUniform3fvFn glUniform3fv = nullptr;
boom::OpenGLUniform3iFn glUniform3i = nullptr;
boom::OpenGLUniform3ivFn glUniform3iv = nullptr;
boom::OpenGLUniform3uiFn glUniform3ui = nullptr;
boom::OpenGLUniform3uivFn glUniform3uiv = nullptr;
boom::OpenGLUniform4dFn glUniform4d = nullptr;
boom::OpenGLUniform4dvFn glUniform4dv = nullptr;
boom::OpenGLUniform4fFn glUniform4f = nullptr;
boom::OpenGLUniform4fvFn glUniform4fv = nullptr;
boom::OpenGLUniform4iFn glUniform4i = nullptr;
boom::OpenGLUniform4ivFn glUniform4iv = nullptr;
boom::OpenGLUniform4uiFn glUniform4ui = nullptr;
boom::OpenGLUniform4uivFn glUniform4uiv = nullptr;
boom::OpenGLUniformBlockBindingFn glUniformBlockBinding = nullptr;
boom::OpenGLUniformMatrix2dvFn glUniformMatrix2dv = nullptr;
boom::OpenGLUniformMatrix2fvFn glUniformMatrix2fv = nullptr;
boom::OpenGLUniformMatrix2x3dvFn glUniformMatrix2x3dv = nullptr;
boom::OpenGLUniformMatrix2x3fvFn glUniformMatrix2x3fv = nullptr;
boom::OpenGLUniformMatrix2x4dvFn glUniformMatrix2x4dv = nullptr;
boom::OpenGLUniformMatrix2x4fvFn glUniformMatrix2x4fv = nullptr;
boom::OpenGLUniformMatrix3dvFn glUniformMatrix3dv = nullptr;
boom::OpenGLUniformMatrix3fvFn glUniformMatrix3fv = nullptr;
boom::OpenGLUniformMatrix3x2dvFn glUniformMatrix3x2dv = nullptr;
boom::OpenGLUniformMatrix3x2fvFn glUniformMatrix3x2fv = nullptr;
boom::OpenGLUniformMatrix3x4dvFn glUniformMatrix3x4dv = nullptr;
boom::OpenGLUniformMatrix3x4fvFn glUniformMatrix3x4fv = nullptr;
boom::OpenGLUniformMatrix4dvFn glUniformMatrix4dv = nullptr;
boom::OpenGLUniformMatrix4fvFn glUniformMatrix4fv = nullptr;
boom::OpenGLUniformMatrix4x2dvFn glUniformMatrix4x2dv = nullptr;
boom::OpenGLUniformMatrix4x2fvFn glUniformMatrix4x2fv = nullptr;
boom::OpenGLUniformMatrix4x3dvFn glUniformMatrix4x3dv = nullptr;
boom::OpenGLUniformMatrix4x3fvFn glUniformMatrix4x3fv = nullptr;
boom::OpenGLUniformSubroutinesuivFn glUniformSubroutinesuiv = nullptr;
boom::OpenGLUnmapBufferFn glUnmapBuffer = nullptr;
boom::OpenGLUnmapNamedBufferFn glUnmapNamedBuffer = nullptr;
boom::OpenGLUseProgramFn glUseProgram = nullptr;
boom::OpenGLUseProgramStagesFn glUseProgramStages = nullptr;
boom::OpenGLValidateProgramFn glValidateProgram = nullptr;
boom::OpenGLValidateProgramPipelineFn glValidateProgramPipeline = nullptr;
boom::OpenGLVertex2dFn glVertex2d = nullptr;
boom::OpenGLVertex2dvFn glVertex2dv = nullptr;
boom::OpenGLVertex2fFn glVertex2f = nullptr;
boom::OpenGLVertex2fvFn glVertex2fv = nullptr;
boom::OpenGLVertex2iFn glVertex2i = nullptr;
boom::OpenGLVertex2ivFn glVertex2iv = nullptr;
boom::OpenGLVertex2sFn glVertex2s = nullptr;
boom::OpenGLVertex2svFn glVertex2sv = nullptr;
boom::OpenGLVertex3dFn glVertex3d = nullptr;
boom::OpenGLVertex3dvFn glVertex3dv = nullptr;
boom::OpenGLVertex3fFn glVertex3f = nullptr;
boom::OpenGLVertex3fvFn glVertex3fv = nullptr;
boom::OpenGLVertex3iFn glVertex3i = nullptr;
boom::OpenGLVertex3ivFn glVertex3iv = nullptr;
boom::OpenGLVertex3sFn glVertex3s = nullptr;
boom::OpenGLVertex3svFn glVertex3sv = nullptr;
boom::OpenGLVertex4dFn glVertex4d = nullptr;
boom::OpenGLVertex4dvFn glVertex4dv = nullptr;
boom::OpenGLVertex4fFn glVertex4f = nullptr;
boom::OpenGLVertex4fvFn glVertex4fv = nullptr;
boom::OpenGLVertex4iFn glVertex4i = nullptr;
boom::OpenGLVertex4ivFn glVertex4iv = nullptr;
boom::OpenGLVertex4sFn glVertex4s = nullptr;
boom::OpenGLVertex4svFn glVertex4sv = nullptr;
boom::OpenGLVertexArrayAttribBindingFn glVertexArrayAttribBinding = nullptr;
boom::OpenGLVertexArrayAttribFormatFn glVertexArrayAttribFormat = nullptr;
boom::OpenGLVertexArrayAttribIFormatFn glVertexArrayAttribIFormat = nullptr;
boom::OpenGLVertexArrayAttribLFormatFn glVertexArrayAttribLFormat = nullptr;
boom::OpenGLVertexArrayBindingDivisorFn glVertexArrayBindingDivisor = nullptr;
boom::OpenGLVertexArrayElementBufferFn glVertexArrayElementBuffer = nullptr;
boom::OpenGLVertexArrayVertexBufferFn glVertexArrayVertexBuffer = nullptr;
boom::OpenGLVertexArrayVertexBuffersFn glVertexArrayVertexBuffers = nullptr;
boom::OpenGLVertexAttrib1dFn glVertexAttrib1d = nullptr;
boom::OpenGLVertexAttrib1dvFn glVertexAttrib1dv = nullptr;
boom::OpenGLVertexAttrib1fFn glVertexAttrib1f = nullptr;
boom::OpenGLVertexAttrib1fvFn glVertexAttrib1fv = nullptr;
boom::OpenGLVertexAttrib1sFn glVertexAttrib1s = nullptr;
boom::OpenGLVertexAttrib1svFn glVertexAttrib1sv = nullptr;
boom::OpenGLVertexAttrib2dFn glVertexAttrib2d = nullptr;
boom::OpenGLVertexAttrib2dvFn glVertexAttrib2dv = nullptr;
boom::OpenGLVertexAttrib2fFn glVertexAttrib2f = nullptr;
boom::OpenGLVertexAttrib2fvFn glVertexAttrib2fv = nullptr;
boom::OpenGLVertexAttrib2sFn glVertexAttrib2s = nullptr;
boom::OpenGLVertexAttrib2svFn glVertexAttrib2sv = nullptr;
boom::OpenGLVertexAttrib3dFn glVertexAttrib3d = nullptr;
boom::OpenGLVertexAttrib3dvFn glVertexAttrib3dv = nullptr;
boom::OpenGLVertexAttrib3fFn glVertexAttrib3f = nullptr;
boom::OpenGLVertexAttrib3fvFn glVertexAttrib3fv = nullptr;
boom::OpenGLVertexAttrib3sFn glVertexAttrib3s = nullptr;
boom::OpenGLVertexAttrib3svFn glVertexAttrib3sv = nullptr;
boom::OpenGLVertexAttrib4NbvFn glVertexAttrib4Nbv = nullptr;
boom::OpenGLVertexAttrib4NivFn glVertexAttrib4Niv = nullptr;
boom::OpenGLVertexAttrib4NsvFn glVertexAttrib4Nsv = nullptr;
boom::OpenGLVertexAttrib4NubFn glVertexAttrib4Nub = nullptr;
boom::OpenGLVertexAttrib4NubvFn glVertexAttrib4Nubv = nullptr;
boom::OpenGLVertexAttrib4NuivFn glVertexAttrib4Nuiv = nullptr;
boom::OpenGLVertexAttrib4NusvFn glVertexAttrib4Nusv = nullptr;
boom::OpenGLVertexAttrib4bvFn glVertexAttrib4bv = nullptr;
boom::OpenGLVertexAttrib4dFn glVertexAttrib4d = nullptr;
boom::OpenGLVertexAttrib4dvFn glVertexAttrib4dv = nullptr;
boom::OpenGLVertexAttrib4fFn glVertexAttrib4f = nullptr;
boom::OpenGLVertexAttrib4fvFn glVertexAttrib4fv = nullptr;
boom::OpenGLVertexAttrib4ivFn glVertexAttrib4iv = nullptr;
boom::OpenGLVertexAttrib4sFn glVertexAttrib4s = nullptr;
boom::OpenGLVertexAttrib4svFn glVertexAttrib4sv = nullptr;
boom::OpenGLVertexAttrib4ubvFn glVertexAttrib4ubv = nullptr;
boom::OpenGLVertexAttrib4uivFn glVertexAttrib4uiv = nullptr;
boom::OpenGLVertexAttrib4usvFn glVertexAttrib4usv = nullptr;
boom::OpenGLVertexAttribBindingFn glVertexAttribBinding = nullptr;
boom::OpenGLVertexAttribDivisorFn glVertexAttribDivisor = nullptr;
boom::OpenGLVertexAttribFormatFn glVertexAttribFormat = nullptr;
boom::OpenGLVertexAttribI1iFn glVertexAttribI1i = nullptr;
boom::OpenGLVertexAttribI1ivFn glVertexAttribI1iv = nullptr;
boom::OpenGLVertexAttribI1uiFn glVertexAttribI1ui = nullptr;
boom::OpenGLVertexAttribI1uivFn glVertexAttribI1uiv = nullptr;
boom::OpenGLVertexAttribI2iFn glVertexAttribI2i = nullptr;
boom::OpenGLVertexAttribI2ivFn glVertexAttribI2iv = nullptr;
boom::OpenGLVertexAttribI2uiFn glVertexAttribI2ui = nullptr;
boom::OpenGLVertexAttribI2uivFn glVertexAttribI2uiv = nullptr;
boom::OpenGLVertexAttribI3iFn glVertexAttribI3i = nullptr;
boom::OpenGLVertexAttribI3ivFn glVertexAttribI3iv = nullptr;
boom::OpenGLVertexAttribI3uiFn glVertexAttribI3ui = nullptr;
boom::OpenGLVertexAttribI3uivFn glVertexAttribI3uiv = nullptr;
boom::OpenGLVertexAttribI4bvFn glVertexAttribI4bv = nullptr;
boom::OpenGLVertexAttribI4iFn glVertexAttribI4i = nullptr;
boom::OpenGLVertexAttribI4ivFn glVertexAttribI4iv = nullptr;
boom::OpenGLVertexAttribI4svFn glVertexAttribI4sv = nullptr;
boom::OpenGLVertexAttribI4ubvFn glVertexAttribI4ubv = nullptr;
boom::OpenGLVertexAttribI4uiFn glVertexAttribI4ui = nullptr;
boom::OpenGLVertexAttribI4uivFn glVertexAttribI4uiv = nullptr;
boom::OpenGLVertexAttribI4usvFn glVertexAttribI4usv = nullptr;
boom::OpenGLVertexAttribIFormatFn glVertexAttribIFormat = nullptr;
boom::OpenGLVertexAttribIPointerFn glVertexAttribIPointer = nullptr;
boom::OpenGLVertexAttribL1dFn glVertexAttribL1d = nullptr;
boom::OpenGLVertexAttribL1dvFn glVertexAttribL1dv = nullptr;
boom::OpenGLVertexAttribL2dFn glVertexAttribL2d = nullptr;
boom::OpenGLVertexAttribL2dvFn glVertexAttribL2dv = nullptr;
boom::OpenGLVertexAttribL3dFn glVertexAttribL3d = nullptr;
boom::OpenGLVertexAttribL3dvFn glVertexAttribL3dv = nullptr;
boom::OpenGLVertexAttribL4dFn glVertexAttribL4d = nullptr;
boom::OpenGLVertexAttribL4dvFn glVertexAttribL4dv = nullptr;
boom::OpenGLVertexAttribLFormatFn glVertexAttribLFormat = nullptr;
boom::OpenGLVertexAttribLPointerFn glVertexAttribLPointer = nullptr;
boom::OpenGLVertexAttribP1uiFn glVertexAttribP1ui = nullptr;
boom::OpenGLVertexAttribP1uivFn glVertexAttribP1uiv = nullptr;
boom::OpenGLVertexAttribP2uiFn glVertexAttribP2ui = nullptr;
boom::OpenGLVertexAttribP2uivFn glVertexAttribP2uiv = nullptr;
boom::OpenGLVertexAttribP3uiFn glVertexAttribP3ui = nullptr;
boom::OpenGLVertexAttribP3uivFn glVertexAttribP3uiv = nullptr;
boom::OpenGLVertexAttribP4uiFn glVertexAttribP4ui = nullptr;
boom::OpenGLVertexAttribP4uivFn glVertexAttribP4uiv = nullptr;
boom::OpenGLVertexAttribPointerFn glVertexAttribPointer = nullptr;
boom::OpenGLVertexBindingDivisorFn glVertexBindingDivisor = nullptr;
boom::OpenGLVertexP2uiFn glVertexP2ui = nullptr;
boom::OpenGLVertexP2uivFn glVertexP2uiv = nullptr;
boom::OpenGLVertexP3uiFn glVertexP3ui = nullptr;
boom::OpenGLVertexP3uivFn glVertexP3uiv = nullptr;
boom::OpenGLVertexP4uiFn glVertexP4ui = nullptr;
boom::OpenGLVertexP4uivFn glVertexP4uiv = nullptr;
boom::OpenGLVertexPointerFn glVertexPointer = nullptr;
boom::OpenGLViewportFn glViewport = nullptr;
boom::OpenGLViewportArrayvFn glViewportArrayv = nullptr;
boom::OpenGLViewportIndexedfFn glViewportIndexedf = nullptr;
boom::OpenGLViewportIndexedfvFn glViewportIndexedfv = nullptr;
boom::OpenGLWaitSyncFn glWaitSync = nullptr;
boom::OpenGLWindowPos2dFn glWindowPos2d = nullptr;
boom::OpenGLWindowPos2dvFn glWindowPos2dv = nullptr;
boom::OpenGLWindowPos2fFn glWindowPos2f = nullptr;
boom::OpenGLWindowPos2fvFn glWindowPos2fv = nullptr;
boom::OpenGLWindowPos2iFn glWindowPos2i = nullptr;
boom::OpenGLWindowPos2ivFn glWindowPos2iv = nullptr;
boom::OpenGLWindowPos2sFn glWindowPos2s = nullptr;
boom::OpenGLWindowPos2svFn glWindowPos2sv = nullptr;
boom::OpenGLWindowPos3dFn glWindowPos3d = nullptr;
boom::OpenGLWindowPos3dvFn glWindowPos3dv = nullptr;
boom::OpenGLWindowPos3fFn glWindowPos3f = nullptr;
boom::OpenGLWindowPos3fvFn glWindowPos3fv = nullptr;
boom::OpenGLWindowPos3iFn glWindowPos3i = nullptr;
boom::OpenGLWindowPos3ivFn glWindowPos3iv = nullptr;
boom::OpenGLWindowPos3sFn glWindowPos3s = nullptr;
boom::OpenGLWindowPos3svFn glWindowPos3sv = nullptr;

} /* namespace boom */