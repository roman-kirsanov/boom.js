#include <cassert>
#include <iostream>
#include "Context.hpp"
#include "Shaders.hpp"

char const* BASIC_VERTEX_SHADER = "\
#version 330 core\n \
uniform mat4 projection;\n \
uniform mat4 transform;\n \
in vec2 position;\n \
void main() {\n \
    gl_Position = projection * transform * vec4(position, 0.0, 1.0);\n \
}";

char const* BASIC_FRAGMENT_SHADER = "\
#version 330 core\n \
uniform vec4 color;\n \
uniform float opacity;\n \
out vec4 result;\n \
void main() {\n \
    result = color;\n \
    result.a = (result.a * opacity);\n \
}";

char const* TEXTURE_VERTEX_SHADER = "\
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

char const* TEXTURE_FRAGMENT_SHADER = "\
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

namespace boom {

Context::~Context() {
    _basicShaders = nullptr;
    _imageShaders = nullptr;
}

Context::Context(boom::OpenGLOptions const& options)
    : boom::OpenGL(options)
    , _basicShaders(nullptr)
    , _imageShaders(nullptr)
{}

void Context::_onReady() {
    _basicShaders = boom::MakeShared<boom::Shaders>(
        boom::GetShared<boom::Context>(this),
        BASIC_VERTEX_SHADER,
        BASIC_FRAGMENT_SHADER
    );
    _imageShaders = boom::MakeShared<boom::Shaders>(
        boom::GetShared<boom::Context>(this),
        TEXTURE_VERTEX_SHADER,
        TEXTURE_FRAGMENT_SHADER
    );
}

boom::ShadersRef Context::basicShaders() const {
    return _basicShaders;
}

boom::ShadersRef Context::imageShaders() const {
    return _imageShaders;
}

std::shared_ptr<boom::Context const> Context::Shared() {
    static auto context = boom::MakeShared<boom::Context>();
    return context;
}

} /* namespace boom */
