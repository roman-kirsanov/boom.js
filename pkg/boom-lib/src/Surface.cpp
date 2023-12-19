#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/Shaders.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Image.hpp>
#include <Boom/View.hpp>

namespace boom {

static char const* kBasicVertexShader = "\
#version 330 core\n \
uniform mat4 projection;\n \
uniform mat4 transform;\n \
in vec2 position;\n \
void main() {\n \
    gl_Position = projection * transform * vec4(position, 0.0, 1.0);\n \
}";

static char const* kBasicFragmentShader = "\
#version 330 core\n \
uniform vec4 color;\n \
uniform float opacity;\n \
out vec4 result;\n \
void main() {\n \
    result = color;\n \
    result.a = (result.a * opacity);\n \
}";

static char const* kImageVertexShader = "\
#version 330 core\n \
precision highp float;\n \
precision highp int;\n \
uniform mat4 projection;\n \
uniform mat4 transform;\n \
uniform vec4 bounds;\n \
in vec2 vertex;\n \
out vec2 position;\n \
void main() {\n \
    gl_Position = projection * transform * vec4(vertex, 0.0, 1.0);\n \
    position = (vertex - bounds.xy);\n \
}";

static char const* kImageFragmentShader = "\
#version 330 core\n \
precision highp float;\n \
precision highp int;\n \
uniform vec4 color;\n \
uniform float opacity;\n \
uniform vec2 size;\n \
uniform vec2 flip;\n \
uniform vec2 repeat;\n \
uniform vec4 npatch;\n \
uniform vec4 source;\n \
uniform vec4 destin;\n \
uniform sampler2D texture0;\n \
in vec2 position;\n \
out vec4 result;\n \
void main() {\n \
    vec2 srcSize = (source.zw - source.xy);\n \
    vec2 dstSize = (destin.zw - destin.xy);\n \
    vec2 dstPos = (position.xy - destin.xy);\n \
    vec4 src = vec4(0.0, 0.0, 0.0, 0.0);\n \
    vec4 dst = vec4(0.0, 0.0, 0.0, 0.0);\n \
    vec4 srcMM = vec4(npatch.x, npatch.y, (srcSize.x - npatch.z), (srcSize.y - npatch.w));\n \
    vec4 dstMM = vec4(npatch.x, npatch.y, (dstSize.x - npatch.z), (dstSize.y - npatch.w));\n \
    if (repeat.x == 1.0) dstPos.x = abs(mod(dstPos.x, dstSize.x));\n \
    if (repeat.y == 1.0) dstPos.y = abs(mod(dstPos.y, dstSize.y));\n \
    if (all(greaterThanEqual(dstPos, dstMM.xy)) && all(lessThan(dstPos, dstMM.zw))) {\n \
        src = srcMM;\n \
        dst = dstMM;\n \
    } else {\n \
        vec4 srcTL = vec4(0.0, 0.0, npatch.x, npatch.y);\n \
        vec4 dstTL = vec4(0.0, 0.0, npatch.x, npatch.y);\n \
        if (all(greaterThanEqual(dstPos, dstTL.xy)) && all(lessThan(dstPos, dstTL.zw))) {\n \
            src = srcTL;\n \
            dst = dstTL;\n \
        } else {\n \
            vec4 srcTM = vec4(npatch.x, 0.0, (srcSize.x - npatch.z), npatch.y);\n \
            vec4 dstTM = vec4(npatch.x, 0.0, (dstSize.x - npatch.z), npatch.y);\n \
            if (all(greaterThanEqual(dstPos, dstTM.xy)) && all(lessThan(dstPos, dstTM.zw))) {\n \
                src = srcTM;\n \
                dst = dstTM;\n \
            } else {\n \
                vec4 srcTR = vec4((srcSize.x - npatch.z), 0.0, srcSize.x, npatch.y);\n \
                vec4 dstTR = vec4((dstSize.x - npatch.z), 0.0, dstSize.x, npatch.y);\n \
                if (all(greaterThanEqual(dstPos, dstTR.xy)) && all(lessThan(dstPos, dstTR.zw))) {\n \
                    src = srcTR;\n \
                    dst = dstTR;\n \
                } else {\n \
                    vec4 srcML = vec4(0.0, npatch.y, npatch.x, (srcSize.y - npatch.w));\n \
                    vec4 dstML = vec4(0.0, npatch.y, npatch.x, (dstSize.y - npatch.w));\n \
                    if (all(greaterThanEqual(dstPos, dstML.xy)) && all(lessThan(dstPos, dstML.zw))) {\n \
                        src = srcML;\n \
                        dst = dstML;\n \
                    } else {\n \
                        vec4 srcMR = vec4((srcSize.x - npatch.z), npatch.y, srcSize.x, (srcSize.y - npatch.w));\n \
                        vec4 dstMR = vec4((dstSize.x - npatch.z), npatch.y, dstSize.x, (dstSize.y - npatch.w));\n \
                        if (all(greaterThanEqual(dstPos, dstMR.xy)) && all(lessThan(dstPos, dstMR.zw))) {\n \
                            src = srcMR;\n \
                            dst = dstMR;\n \
                        } else {\n \
                            vec4 srcBL = vec4(0.0, (srcSize.y - npatch.w), npatch.x, srcSize.y);\n \
                            vec4 dstBL = vec4(0.0, (dstSize.y - npatch.w), npatch.x, dstSize.y);\n \
                            if (all(greaterThanEqual(dstPos, dstBL.xy)) && all(lessThan(dstPos, dstBL.zw))) {\n \
                                src = srcBL;\n \
                                dst = dstBL;\n \
                            } else {\n \
                                vec4 srcBM = vec4(npatch.x, (srcSize.y - npatch.w), (srcSize.x - npatch.z), srcSize.y);\n \
                                vec4 dstBM = vec4(npatch.x, (dstSize.y - npatch.w), (dstSize.x - npatch.z), dstSize.y);\n \
                                if (all(greaterThanEqual(dstPos, dstBM.xy)) && all(lessThan(dstPos, dstBM.zw))) {\n \
                                    src = srcBM;\n \
                                    dst = dstBM;\n \
                                } else {\n \
                                    vec4 srcBR = vec4((srcSize.x - npatch.z), (srcSize.y - npatch.w), srcSize.x, srcSize.y);\n \
                                    vec4 dstBR = vec4((dstSize.x - npatch.z), (dstSize.y - npatch.w), dstSize.x, dstSize.y);\n \
                                    if (all(greaterThanEqual(dstPos, dstBR.xy)) && all(lessThan(dstPos, dstBR.zw))) {\n \
                                        src = srcBR;\n \
                                        dst = dstBR;\n \
                                    }\n \
                                }\n \
                            }\n \
                        }\n \
                    }\n \
                }\n \
            }\n \
        }\n \
    }\n \
    vec2 duv = ((dstPos - dst.xy) / (dst.zw - dst.xy));\n \
    vec2 suv = ((source.xy + mix(src.xy, src.zw, duv)) / size.xy);\n \
    if (flip.x == 1.0) suv.x = ((source.z - mix(src.x, src.z, duv.x)) / size.x);\n \
    if (flip.y == 1.0) suv.y = ((source.w - mix(src.y, src.w, duv.y)) / size.y);\n \
    result = texture(texture0, suv);\n \
    result = ((result * result.a) + (color * (1.0 - result.a)));\n \
    result.w = (result.w * opacity);\n \
}";

Surface::~Surface() {
    if (_type == boom::SurfaceType::Image) {
        _context->deleteFramebuffers(1, &_frameBufferId);
        _context->deleteFramebuffers(1, &_textureBufferId);
        _context->deleteTextures(1, &_colorBufferId);
        _context->deleteTextures(1, &_depthBufferId);
    }
}

Surface::Surface(boom::SurfaceOptions const& options)
    : _type(options.type)
    , _view(options.view.value_or(nullptr))
    , _image(options.image.value_or(nullptr))
    , _version(options.version.value_or(boom::OpenGLVersion::CompatibilityProfile_32))
    , _context(nullptr)
    , _basicShaders(nullptr)
    , _imageShaders(nullptr)
    , _frameBufferId(0)
    , _colorBufferId(0)
    , _depthBufferId(0)
    , _textureBufferId(0)
{
    if (_type == boom::SurfaceType::View) {
        if (_view == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"view\" cannot be nullptr for type \"View\"");
        }
        _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
            .shared = boom::OpenGL::Shared(),
            .view = _view,
            .version = _version
        });
    } else if (_type == boom::SurfaceType::Image) {
        if (_image == nullptr) {
            boom::Abort("boom::Surface::Surface() failed: \"image\" cannot be nullptr for type \"Image\"");
        }
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _context = boom::OpenGL::Shared();
        _context->genFramebuffers(1, &_frameBufferId);
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, _frameBufferId);
        _context->genTextures(1, &_colorBufferId);
        _context->bindTexture(boom::kOpenGLTexture2dMultisample, _colorBufferId);
        _context->texImage2DMultisample(boom::kOpenGLTexture2dMultisample, 4, boom::kOpenGLRgba, width, height, boom::kOpenGLTrue);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2dMultisample, _colorBufferId, 0);
        _context->genTextures(1, &_depthBufferId);
        _context->bindTexture(boom::kOpenGLTexture2dMultisample, _depthBufferId);
        _context->texImage2DMultisample(boom::kOpenGLTexture2dMultisample, 4, boom::kOpenGLDepth24Stencil8, width, height, boom::kOpenGLTrue);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLDepthStencilAttachment, boom::kOpenGLTexture2dMultisample, _depthBufferId, 0);
        if (_context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("boom::Surface::Surface() failed: Failed to make complete intermediate framebuffer object");
        }
        _context->genFramebuffers(1, &_textureBufferId);
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, _textureBufferId);
        _context->framebufferTexture2D(boom::kOpenGLFramebuffer, boom::kOpenGLColorAttachment0, boom::kOpenGLTexture2d, _image->_textureId, 0);
        if (_context->checkFramebufferStatus(boom::kOpenGLFramebuffer) != boom::kOpenGLFramebufferComplete) {
            boom::Abort("boom::Surface::Surface() failed: Failed to make complete texture framebuffer object");
        }
        _context->bindFramebuffer(boom::kOpenGLFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _textureBufferId);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _frameBufferId);
        _context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    }
    _basicShaders = boom::MakeShared<boom::Shaders>(_context, kBasicVertexShader, kBasicFragmentShader);
    _imageShaders = boom::MakeShared<boom::Shaders>(_context, kImageVertexShader, kImageFragmentShader);
}

boom::OpenGLCRef Surface::context() const {
    return _context;
}

boom::SurfaceType Surface::type() const {
    return _type;
}

boom::ViewCRef Surface::view() const {
    return _view;
}

boom::ImageCRef Surface::image() const {
    return _image;
}

boom::Vec2 Surface::size() const {
    if (_type == boom::SurfaceType::View) {
        return _view->size();
    } else if (_type == boom::SurfaceType::Image) {
        return _image->size();
    } else {
        return { 0.0f, 0.0f };
    }
}

void Surface::current() const {
    _context->bindFramebuffer(boom::kOpenGLFramebuffer, (
        (_type == boom::SurfaceType::Image) ? _frameBufferId :
        (_type == boom::SurfaceType::View) ? 0 : 0
    ));
    _context->viewport(0.0f, 0.0f, size().width, size().height);
    _context->enable(boom::kOpenGLMultisample);
}

void Surface::clear(boom::Color color) {
    current();
    _context->clearColor(
        color.red,
        color.green,
        color.blue,
        color.alpha
    );
    _context->clear(boom::kOpenGLColorBufferBit);
}

void Surface::flush() {
    current();
    _context->flush();
    if (_type == boom::SurfaceType::Image) {
        auto const width = _image->size().width;
        auto const height = _image->size().height;
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, _frameBufferId);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, _textureBufferId);
        _context->blitFramebuffer(0, 0, width, height, 0, 0, width, height, boom::kOpenGLColorBufferBit, boom::kOpenGLNearest);
        _context->bindFramebuffer(boom::kOpenGLReadFramebuffer, 0);
        _context->bindFramebuffer(boom::kOpenGLDrawFramebuffer, 0);
    }
}

void Surface::swap() {
    current();
    if (_type == boom::SurfaceType::View) {
        _context->swap();
    }
}

} /* namespace boom */
