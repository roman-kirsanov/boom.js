#include <cassert>
#include <iostream>
#include <windows.h>
#include <GL/GL.h>
#include <Boom/Utilities.hpp>
#include "../OpenGL.hpp"

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB 0x2093
#define WGL_CONTEXT_FLAGS_ARB 0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_DRAW_TO_WINDOW_ARB 0x2001
#define WGL_ACCELERATION_ARB 0x2003
#define WGL_SUPPORT_OPENGL_ARB 0x2010
#define WGL_DOUBLE_BUFFER_ARB 0x2011
#define WGL_PIXEL_TYPE_ARB 0x2013
#define WGL_COLOR_BITS_ARB 0x2014
#define WGL_DEPTH_BITS_ARB 0x2022
#define WGL_STENCIL_BITS_ARB 0x2023
#define WGL_FULL_ACCELERATION_ARB 0x2027
#define WGL_TYPE_RGBA_ARB 0x202B

#define RegisterClassE(...) { \
    if (!RegisterClassA(__VA_ARGS__)) { \
        boom::Abort("ERROR: RegisterClass() failed"); \
    } \
}

#define CreateWindowExE(...) [&]{ \
    auto __ret = CreateWindowExA(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("ERROR: CreateWindowEx() failed"); \
    } \
    return __ret; \
}()

#define GetDCE(...) [&]{ \
    auto __ret = GetDC(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("ERROR: GetDC() failed"); \
    } \
    return __ret; \
}()

#define ChoosePixelFormatE(...) [&]{ \
    auto __ret = ChoosePixelFormat(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("ERROR: ChoosePixelFormat() failed"); \
    } \
    return __ret; \
}()

#define DescribePixelFormatE(...) { \
    if (!DescribePixelFormat(__VA_ARGS__)) { \
        boom::Abort("ERROR: DescribePixelFormat() failed"); \
    } \
}

#define SetPixelFormatE(...) [&]{ \
    if (!SetPixelFormat(__VA_ARGS__)) { \
        boom::Abort("ERROR: SetPixelFormat() failed"); \
    } \
}()

#define wglCreateContextE(...) [&]{ \
    auto __ret = wglCreateContext(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("ERROR: wglCreateContext() failed"); \
    } \
    return __ret; \
}()

#define wglMakeCurrentE(...) { \
    if (!wglMakeCurrent(__VA_ARGS__)) { \
        boom::Abort("ERROR: wglMakeCurrent() failed"); \
    } \
}

#define wglDeleteContextE(...) { \
    if (!wglDeleteContext(__VA_ARGS__)) { \
        boom::Abort("ERROR: wglDeleteContext() failed"); \
    } \
}

#define ReleaseDCE(...) { \
    if (!ReleaseDC(__VA_ARGS__)) { \
        boom::Abort("ERROR: ReleaseDC() failed"); \
    } \
}

#define DestroyWindowE(...) { \
    if (!DestroyWindow(__VA_ARGS__)) { \
        boom::Abort("ERROR: DestroyWindow() failed"); \
    } \
}

namespace boom {

using WGLCreateContextAttribsARB = HGLRC(WINAPI*)(HDC, HGLRC, const int*);
using WGLChoosePixelFormatARB = BOOL(WINAPI*)(HDC, const int*, const FLOAT*, UINT, int*, UINT*);

static LRESULT CALLBACK DummyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

static auto wglCreateContextAttribsARB = (WGLCreateContextAttribsARB)nullptr;
static auto wglChoosePixelFormatARB = (WGLChoosePixelFormatARB)nullptr;

static auto const DUMMY_WINDOW_CLASS_NAME = "OpenGLDummyWindowClass";
static auto const DUMMY_WINDOW_CLASS_DEF = WNDCLASSA{
    .style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
	.lpfnWndProc = boom::DummyWndProc,
	.hInstance = GetModuleHandle(nullptr),
	.lpszClassName = DUMMY_WINDOW_CLASS_NAME
};

struct __OpenGLImpl {
    HWND window;
    HDC device;
    HGLRC context;
};

void OpenGL::_implInit(boom::OpenGLOptions const& options) {
    if ((wglCreateContextAttribsARB == nullptr)
    || (wglChoosePixelFormatARB == nullptr)) {
        RegisterClassE(&DUMMY_WINDOW_CLASS_DEF);
		auto window = CreateWindowExE(
			0,
			DUMMY_WINDOW_CLASS_NAME,
			"",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);
        auto device = GetDCE(window);
        auto format = PIXELFORMATDESCRIPTOR{
            .nSize = sizeof(PIXELFORMATDESCRIPTOR),
            .nVersion = 1,
            .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            .iPixelType = PFD_TYPE_RGBA,
            .cColorBits = 32,
            .cAlphaBits = 8,
            .cDepthBits = 24,
            .cStencilBits = 8,
            .iLayerType = PFD_MAIN_PLANE
        };
        auto formatId = ChoosePixelFormatE(device, &format);
        SetPixelFormatE(device, formatId, &format);
        auto context = wglCreateContextE(device);
        wglMakeCurrentE(device, context);
        boom::wglCreateContextAttribsARB = (boom::WGLCreateContextAttribsARB)wglGetProcAddress("wglCreateContextAttribsARB");
        boom::wglChoosePixelFormatARB = (boom::WGLChoosePixelFormatARB)wglGetProcAddress("wglChoosePixelFormatARB");
        wglMakeCurrentE(nullptr, nullptr);
        wglDeleteContextE(context);
        ReleaseDCE(window, device);
        DestroyWindowE(window);
    }
    if (boom::wglCreateContextAttribsARB == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::OpenGL() failed: Failed to obtain \"wglCreateContextAttribsARB\" function pointer");
    }
    if (boom::wglChoosePixelFormatARB == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::OpenGL() failed: Failed to obtain \"wglChoosePixelFormatARB\" function pointer");
    }
    auto window = (HWND)nullptr;
    if (options.window.has_value()) {
        window = (HWND)options.window.value();
    } else {
        window = CreateWindowExE(
            0,
            DUMMY_WINDOW_CLASS_NAME,
            "",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );
    }
    auto device = GetDCE(window);
    UINT formats = 0;
    int formatId = 0;
    int formatAttrs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
        WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB,     32,
        WGL_DEPTH_BITS_ARB,     24,
        WGL_STENCIL_BITS_ARB,   8,
        0
    };
    boom::wglChoosePixelFormatARB(device, formatAttrs, 0, 1, &formatId, &formats);
    if (formats == 0) {
        boom::Abort("ERROR: boom::OpenGL::OpenGL() failed: wglChoosePixelFormatARB() failed");
    }
    auto formatDescr = PIXELFORMATDESCRIPTOR{};
    DescribePixelFormatE(device, formatId, sizeof(formatDescr), &formatDescr);
    SetPixelFormatE(device, formatId, &formatDescr);
    int contextAttrs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, options.majorVersion.value_or(3),
        WGL_CONTEXT_MINOR_VERSION_ARB, options.minorVersion.value_or(2),
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    auto context = boom::wglCreateContextAttribsARB(device, 0, contextAttrs);
    if (context == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::OpenGL() failed: wglCreateContextAttribsARB() failed");
    }
    _impl = new boom::__OpenGLImpl{
        .window = window,
        .device = device,
        .context = context
    };
}

void OpenGL::_implDone() {
    wglDeleteContextE(_impl->context);
    DestroyWindowE(_impl->window);
    ReleaseDCE(_impl->window, _impl->device);
    delete _impl;
}

void OpenGL::_implSwap() {
    SwapBuffers(_impl->device);
}

void OpenGL::_implCurrent() {
    wglMakeCurrent(_impl->device, _impl->context);
}

void OpenGL::_implBootstrap() {
    static auto bootstrapped = false;
    if (bootstrapped == false) {
        boom::glCullFace = (boom::GLCullFace)wglGetProcAddress("glCullFace");
        boom::glFrontFace = (boom::GLFrontFace)wglGetProcAddress("glFrontFace");
        boom::glHint = (boom::GLHint)wglGetProcAddress("glHint");
        boom::glLineWidth = (boom::GLLineWidth)wglGetProcAddress("glLineWidth");
        boom::glPointSize = (boom::GLPointSize)wglGetProcAddress("glPointSize");
        boom::glPolygonMode = (boom::GLPolygonMode)wglGetProcAddress("glPolygonMode");
        boom::glScissor = (boom::GLScissor)wglGetProcAddress("glScissor");
        boom::glTexParameterf = (boom::GLTexParameterf)wglGetProcAddress("glTexParameterf");
        boom::glTexParameterfv = (boom::GLTexParameterfv)wglGetProcAddress("glTexParameterfv");
        boom::glTexParameteri = (boom::GLTexParameteri)wglGetProcAddress("glTexParameteri");
        boom::glTexParameteriv = (boom::GLTexParameteriv)wglGetProcAddress("glTexParameteriv");
        boom::glTexImage1D = (boom::GLTexImage1D)wglGetProcAddress("glTexImage1D");
        boom::glTexImage2D = (boom::GLTexImage2D)wglGetProcAddress("glTexImage2D");
        boom::glDrawBuffer = (boom::GLDrawBuffer)wglGetProcAddress("glDrawBuffer");
        boom::glClear = (boom::GLClear)wglGetProcAddress("glClear");
        boom::glClearColor = (boom::GLClearColor)wglGetProcAddress("glClearColor");
        boom::glClearStencil = (boom::GLClearStencil)wglGetProcAddress("glClearStencil");
        boom::glClearDepth = (boom::GLClearDepth)wglGetProcAddress("glClearDepth");
        boom::glStencilMask = (boom::GLStencilMask)wglGetProcAddress("glStencilMask");
        boom::glColorMask = (boom::GLColorMask)wglGetProcAddress("glColorMask");
        boom::glDepthMask = (boom::GLDepthMask)wglGetProcAddress("glDepthMask");
        boom::glDisable = (boom::GLDisable)wglGetProcAddress("glDisable");
        boom::glEnable = (boom::GLEnable)wglGetProcAddress("glEnable");
        boom::glFinish = (boom::GLFinish)wglGetProcAddress("glFinish");
        boom::glFlush = (boom::GLFlush)wglGetProcAddress("glFlush");
        boom::glBlendFunc = (boom::GLBlendFunc)wglGetProcAddress("glBlendFunc");
        boom::glLogicOp = (boom::GLLogicOp)wglGetProcAddress("glLogicOp");
        boom::glStencilFunc = (boom::GLStencilFunc)wglGetProcAddress("glStencilFunc");
        boom::glStencilOp = (boom::GLStencilOp)wglGetProcAddress("glStencilOp");
        boom::glDepthFunc = (boom::GLDepthFunc)wglGetProcAddress("glDepthFunc");
        boom::glPixelStoref = (boom::GLPixelStoref)wglGetProcAddress("glPixelStoref");
        boom::glPixelStorei = (boom::GLPixelStorei)wglGetProcAddress("glPixelStorei");
        boom::glReadBuffer = (boom::GLReadBuffer)wglGetProcAddress("glReadBuffer");
        boom::glReadPixels = (boom::GLReadPixels)wglGetProcAddress("glReadPixels");
        boom::glGetBooleanv = (boom::GLGetBooleanv)wglGetProcAddress("glGetBooleanv");
        boom::glGetDoublev = (boom::GLGetDoublev)wglGetProcAddress("glGetDoublev");
        boom::glGetFloatv = (boom::GLGetFloatv)wglGetProcAddress("glGetFloatv");
        boom::glGetIntegerv = (boom::GLGetIntegerv)wglGetProcAddress("glGetIntegerv");
        boom::glGetTexImage = (boom::GLGetTexImage)wglGetProcAddress("glGetTexImage");
        boom::glGetTexParameterfv = (boom::GLGetTexParameterfv)wglGetProcAddress("glGetTexParameterfv");
        boom::glGetTexParameteriv = (boom::GLGetTexParameteriv)wglGetProcAddress("glGetTexParameteriv");
        boom::glGetTexLevelParameterfv = (boom::GLGetTexLevelParameterfv)wglGetProcAddress("glGetTexLevelParameterfv");
        boom::glGetTexLevelParameteriv = (boom::GLGetTexLevelParameteriv)wglGetProcAddress("glGetTexLevelParameteriv");
        boom::glDepthRange = (boom::GLDepthRange)wglGetProcAddress("glDepthRange");
        boom::glViewport = (boom::GLViewport)wglGetProcAddress("glViewport");
        boom::glDrawArrays = (boom::GLDrawArrays)wglGetProcAddress("glDrawArrays");
        boom::glDrawElements = (boom::GLDrawElements)wglGetProcAddress("glDrawElements");
        boom::glPolygonOffset = (boom::GLPolygonOffset)wglGetProcAddress("glPolygonOffset");
        boom::glCopyTexImage1D = (boom::GLCopyTexImage1D)wglGetProcAddress("glCopyTexImage1D");
        boom::glCopyTexImage2D = (boom::GLCopyTexImage2D)wglGetProcAddress("glCopyTexImage2D");
        boom::glCopyTexSubImage1D = (boom::GLCopyTexSubImage1D)wglGetProcAddress("glCopyTexSubImage1D");
        boom::glCopyTexSubImage2D = (boom::GLCopyTexSubImage2D)wglGetProcAddress("glCopyTexSubImage2D");
        boom::glTexSubImage1D = (boom::GLTexSubImage1D)wglGetProcAddress("glTexSubImage1D");
        boom::glTexSubImage2D = (boom::GLTexSubImage2D)wglGetProcAddress("glTexSubImage2D");
        boom::glBindTexture = (boom::GLBindTexture)wglGetProcAddress("glBindTexture");
        boom::glDeleteTextures = (boom::GLDeleteTextures)wglGetProcAddress("glDeleteTextures");
        boom::glGenTextures = (boom::GLGenTextures)wglGetProcAddress("glGenTextures");
        boom::glDrawRangeElements = (boom::GLDrawRangeElements)wglGetProcAddress("glDrawRangeElements");
        boom::glTexImage3D = (boom::GLTexImage3D)wglGetProcAddress("glTexImage3D");
        boom::glTexSubImage3D = (boom::GLTexSubImage3D)wglGetProcAddress("glTexSubImage3D");
        boom::glCopyTexSubImage3D = (boom::GLCopyTexSubImage3D)wglGetProcAddress("glCopyTexSubImage3D");
        boom::glActiveTexture = (boom::GLActiveTexture)wglGetProcAddress("glActiveTexture");
        boom::glSampleCoverage = (boom::GLSampleCoverage)wglGetProcAddress("glSampleCoverage");
        boom::glCompressedTexImage3D = (boom::GLCompressedTexImage3D)wglGetProcAddress("glCompressedTexImage3D");
        boom::glCompressedTexImage2D = (boom::GLCompressedTexImage2D)wglGetProcAddress("glCompressedTexImage2D");
        boom::glCompressedTexImage1D = (boom::GLCompressedTexImage1D)wglGetProcAddress("glCompressedTexImage1D");
        boom::glCompressedTexSubImage3D = (boom::GLCompressedTexSubImage3D)wglGetProcAddress("glCompressedTexSubImage3D");
        boom::glCompressedTexSubImage2D = (boom::GLCompressedTexSubImage2D)wglGetProcAddress("glCompressedTexSubImage2D");
        boom::glCompressedTexSubImage1D = (boom::GLCompressedTexSubImage1D)wglGetProcAddress("glCompressedTexSubImage1D");
        boom::glGetCompressedTexImage = (boom::GLGetCompressedTexImage)wglGetProcAddress("glGetCompressedTexImage");
        boom::glBlendFuncSeparate = (boom::GLBlendFuncSeparate)wglGetProcAddress("glBlendFuncSeparate");
        boom::glMultiDrawArrays = (boom::GLMultiDrawArrays)wglGetProcAddress("glMultiDrawArrays");
        boom::glMultiDrawElements = (boom::GLMultiDrawElements)wglGetProcAddress("glMultiDrawElements");
        boom::glPointParameterf = (boom::GLPointParameterf)wglGetProcAddress("glPointParameterf");
        boom::glPointParameterfv = (boom::GLPointParameterfv)wglGetProcAddress("glPointParameterfv");
        boom::glPointParameteri = (boom::GLPointParameteri)wglGetProcAddress("glPointParameteri");
        boom::glPointParameteriv = (boom::GLPointParameteriv)wglGetProcAddress("glPointParameteriv");
        boom::glBlendColor = (boom::GLBlendColor)wglGetProcAddress("glBlendColor");
        boom::glBlendEquation = (boom::GLBlendEquation)wglGetProcAddress("glBlendEquation");
        boom::glGenQueries = (boom::GLGenQueries)wglGetProcAddress("glGenQueries");
        boom::glDeleteQueries = (boom::GLDeleteQueries)wglGetProcAddress("glDeleteQueries");
        boom::glBeginQuery = (boom::GLBeginQuery)wglGetProcAddress("glBeginQuery");
        boom::glEndQuery = (boom::GLEndQuery)wglGetProcAddress("glEndQuery");
        boom::glGetQueryiv = (boom::GLGetQueryiv)wglGetProcAddress("glGetQueryiv");
        boom::glGetQueryObjectiv = (boom::GLGetQueryObjectiv)wglGetProcAddress("glGetQueryObjectiv");
        boom::glGetQueryObjectuiv = (boom::GLGetQueryObjectuiv)wglGetProcAddress("glGetQueryObjectuiv");
        boom::glBindBuffer = (boom::GLBindBuffer)wglGetProcAddress("glBindBuffer");
        boom::glDeleteBuffers = (boom::GLDeleteBuffers)wglGetProcAddress("glDeleteBuffers");
        boom::glGenBuffers = (boom::GLGenBuffers)wglGetProcAddress("glGenBuffers");
        boom::glBufferData = (boom::GLBufferData)wglGetProcAddress("glBufferData");
        boom::glBufferSubData = (boom::GLBufferSubData)wglGetProcAddress("glBufferSubData");
        boom::glGetBufferSubData = (boom::GLGetBufferSubData)wglGetProcAddress("glGetBufferSubData");
        boom::glGetBufferParameteriv = (boom::GLGetBufferParameteriv)wglGetProcAddress("glGetBufferParameteriv");
        boom::glGetBufferPointerv = (boom::GLGetBufferPointerv)wglGetProcAddress("glGetBufferPointerv");
        boom::glBlendEquationSeparate = (boom::GLBlendEquationSeparate)wglGetProcAddress("glBlendEquationSeparate");
        boom::glDrawBuffers = (boom::GLDrawBuffers)wglGetProcAddress("glDrawBuffers");
        boom::glStencilOpSeparate = (boom::GLStencilOpSeparate)wglGetProcAddress("glStencilOpSeparate");
        boom::glStencilFuncSeparate = (boom::GLStencilFuncSeparate)wglGetProcAddress("glStencilFuncSeparate");
        boom::glStencilMaskSeparate = (boom::GLStencilMaskSeparate)wglGetProcAddress("glStencilMaskSeparate");
        boom::glAttachShader = (boom::GLAttachShader)wglGetProcAddress("glAttachShader");
        boom::glBindAttribLocation = (boom::GLBindAttribLocation)wglGetProcAddress("glBindAttribLocation");
        boom::glCompileShader = (boom::GLCompileShader)wglGetProcAddress("glCompileShader");
        boom::glDeleteProgram = (boom::GLDeleteProgram)wglGetProcAddress("glDeleteProgram");
        boom::glDeleteShader = (boom::GLDeleteShader)wglGetProcAddress("glDeleteShader");
        boom::glDetachShader = (boom::GLDetachShader)wglGetProcAddress("glDetachShader");
        boom::glDisableVertexAttribArray = (boom::GLDisableVertexAttribArray)wglGetProcAddress("glDisableVertexAttribArray");
        boom::glEnableVertexAttribArray = (boom::GLEnableVertexAttribArray)wglGetProcAddress("glEnableVertexAttribArray");
        boom::glGetActiveAttrib = (boom::GLGetActiveAttrib)wglGetProcAddress("glGetActiveAttrib");
        boom::glGetActiveUniform = (boom::GLGetActiveUniform)wglGetProcAddress("glGetActiveUniform");
        boom::glGetAttachedShaders = (boom::GLGetAttachedShaders)wglGetProcAddress("glGetAttachedShaders");
        boom::glGetProgramiv = (boom::GLGetProgramiv)wglGetProcAddress("glGetProgramiv");
        boom::glGetProgramInfoLog = (boom::GLGetProgramInfoLog)wglGetProcAddress("glGetProgramInfoLog");
        boom::glGetShaderiv = (boom::GLGetShaderiv)wglGetProcAddress("glGetShaderiv");
        boom::glGetShaderInfoLog = (boom::GLGetShaderInfoLog)wglGetProcAddress("glGetShaderInfoLog");
        boom::glGetShaderSource = (boom::GLGetShaderSource)wglGetProcAddress("glGetShaderSource");
        boom::glGetUniformfv = (boom::GLGetUniformfv)wglGetProcAddress("glGetUniformfv");
        boom::glGetUniformiv = (boom::GLGetUniformiv)wglGetProcAddress("glGetUniformiv");
        boom::glGetVertexAttribdv = (boom::GLGetVertexAttribdv)wglGetProcAddress("glGetVertexAttribdv");
        boom::glGetVertexAttribfv = (boom::GLGetVertexAttribfv)wglGetProcAddress("glGetVertexAttribfv");
        boom::glGetVertexAttribiv = (boom::GLGetVertexAttribiv)wglGetProcAddress("glGetVertexAttribiv");
        boom::glGetVertexAttribPointerv = (boom::GLGetVertexAttribPointerv)wglGetProcAddress("glGetVertexAttribPointerv");
        boom::glLinkProgram = (boom::GLLinkProgram)wglGetProcAddress("glLinkProgram");
        boom::glShaderSource = (boom::GLShaderSource)wglGetProcAddress("glShaderSource");
        boom::glUseProgram = (boom::GLUseProgram)wglGetProcAddress("glUseProgram");
        boom::glUniform1f = (boom::GLUniform1f)wglGetProcAddress("glUniform1f");
        boom::glUniform2f = (boom::GLUniform2f)wglGetProcAddress("glUniform2f");
        boom::glUniform3f = (boom::GLUniform3f)wglGetProcAddress("glUniform3f");
        boom::glUniform4f = (boom::GLUniform4f)wglGetProcAddress("glUniform4f");
        boom::glUniform1i = (boom::GLUniform1i)wglGetProcAddress("glUniform1i");
        boom::glUniform2i = (boom::GLUniform2i)wglGetProcAddress("glUniform2i");
        boom::glUniform3i = (boom::GLUniform3i)wglGetProcAddress("glUniform3i");
        boom::glUniform4i = (boom::GLUniform4i)wglGetProcAddress("glUniform4i");
        boom::glUniform1fv = (boom::GLUniform1fv)wglGetProcAddress("glUniform1fv");
        boom::glUniform2fv = (boom::GLUniform2fv)wglGetProcAddress("glUniform2fv");
        boom::glUniform3fv = (boom::GLUniform3fv)wglGetProcAddress("glUniform3fv");
        boom::glUniform4fv = (boom::GLUniform4fv)wglGetProcAddress("glUniform4fv");
        boom::glUniform1iv = (boom::GLUniform1iv)wglGetProcAddress("glUniform1iv");
        boom::glUniform2iv = (boom::GLUniform2iv)wglGetProcAddress("glUniform2iv");
        boom::glUniform3iv = (boom::GLUniform3iv)wglGetProcAddress("glUniform3iv");
        boom::glUniform4iv = (boom::GLUniform4iv)wglGetProcAddress("glUniform4iv");
        boom::glUniformMatrix2fv = (boom::GLUniformMatrix2fv)wglGetProcAddress("glUniformMatrix2fv");
        boom::glUniformMatrix3fv = (boom::GLUniformMatrix3fv)wglGetProcAddress("glUniformMatrix3fv");
        boom::glUniformMatrix4fv = (boom::GLUniformMatrix4fv)wglGetProcAddress("glUniformMatrix4fv");
        boom::glValidateProgram = (boom::GLValidateProgram)wglGetProcAddress("glValidateProgram");
        boom::glVertexAttrib1d = (boom::GLVertexAttrib1d)wglGetProcAddress("glVertexAttrib1d");
        boom::glVertexAttrib1dv = (boom::GLVertexAttrib1dv)wglGetProcAddress("glVertexAttrib1dv");
        boom::glVertexAttrib1f = (boom::GLVertexAttrib1f)wglGetProcAddress("glVertexAttrib1f");
        boom::glVertexAttrib1fv = (boom::GLVertexAttrib1fv)wglGetProcAddress("glVertexAttrib1fv");
        boom::glVertexAttrib1s = (boom::GLVertexAttrib1s)wglGetProcAddress("glVertexAttrib1s");
        boom::glVertexAttrib1sv = (boom::GLVertexAttrib1sv)wglGetProcAddress("glVertexAttrib1sv");
        boom::glVertexAttrib2d = (boom::GLVertexAttrib2d)wglGetProcAddress("glVertexAttrib2d");
        boom::glVertexAttrib2dv = (boom::GLVertexAttrib2dv)wglGetProcAddress("glVertexAttrib2dv");
        boom::glVertexAttrib2f = (boom::GLVertexAttrib2f)wglGetProcAddress("glVertexAttrib2f");
        boom::glVertexAttrib2fv = (boom::GLVertexAttrib2fv)wglGetProcAddress("glVertexAttrib2fv");
        boom::glVertexAttrib2s = (boom::GLVertexAttrib2s)wglGetProcAddress("glVertexAttrib2s");
        boom::glVertexAttrib2sv = (boom::GLVertexAttrib2sv)wglGetProcAddress("glVertexAttrib2sv");
        boom::glVertexAttrib3d = (boom::GLVertexAttrib3d)wglGetProcAddress("glVertexAttrib3d");
        boom::glVertexAttrib3dv = (boom::GLVertexAttrib3dv)wglGetProcAddress("glVertexAttrib3dv");
        boom::glVertexAttrib3f = (boom::GLVertexAttrib3f)wglGetProcAddress("glVertexAttrib3f");
        boom::glVertexAttrib3fv = (boom::GLVertexAttrib3fv)wglGetProcAddress("glVertexAttrib3fv");
        boom::glVertexAttrib3s = (boom::GLVertexAttrib3s)wglGetProcAddress("glVertexAttrib3s");
        boom::glVertexAttrib3sv = (boom::GLVertexAttrib3sv)wglGetProcAddress("glVertexAttrib3sv");
        boom::glVertexAttrib4Nbv = (boom::GLVertexAttrib4Nbv)wglGetProcAddress("glVertexAttrib4Nbv");
        boom::glVertexAttrib4Niv = (boom::GLVertexAttrib4Niv)wglGetProcAddress("glVertexAttrib4Niv");
        boom::glVertexAttrib4Nsv = (boom::GLVertexAttrib4Nsv)wglGetProcAddress("glVertexAttrib4Nsv");
        boom::glVertexAttrib4Nub = (boom::GLVertexAttrib4Nub)wglGetProcAddress("glVertexAttrib4Nub");
        boom::glVertexAttrib4Nubv = (boom::GLVertexAttrib4Nubv)wglGetProcAddress("glVertexAttrib4Nubv");
        boom::glVertexAttrib4Nuiv = (boom::GLVertexAttrib4Nuiv)wglGetProcAddress("glVertexAttrib4Nuiv");
        boom::glVertexAttrib4Nusv = (boom::GLVertexAttrib4Nusv)wglGetProcAddress("glVertexAttrib4Nusv");
        boom::glVertexAttrib4bv = (boom::GLVertexAttrib4bv)wglGetProcAddress("glVertexAttrib4bv");
        boom::glVertexAttrib4d = (boom::GLVertexAttrib4d)wglGetProcAddress("glVertexAttrib4d");
        boom::glVertexAttrib4dv = (boom::GLVertexAttrib4dv)wglGetProcAddress("glVertexAttrib4dv");
        boom::glVertexAttrib4f = (boom::GLVertexAttrib4f)wglGetProcAddress("glVertexAttrib4f");
        boom::glVertexAttrib4fv = (boom::GLVertexAttrib4fv)wglGetProcAddress("glVertexAttrib4fv");
        boom::glVertexAttrib4iv = (boom::GLVertexAttrib4iv)wglGetProcAddress("glVertexAttrib4iv");
        boom::glVertexAttrib4s = (boom::GLVertexAttrib4s)wglGetProcAddress("glVertexAttrib4s");
        boom::glVertexAttrib4sv = (boom::GLVertexAttrib4sv)wglGetProcAddress("glVertexAttrib4sv");
        boom::glVertexAttrib4ubv = (boom::GLVertexAttrib4ubv)wglGetProcAddress("glVertexAttrib4ubv");
        boom::glVertexAttrib4uiv = (boom::GLVertexAttrib4uiv)wglGetProcAddress("glVertexAttrib4uiv");
        boom::glVertexAttrib4usv = (boom::GLVertexAttrib4usv)wglGetProcAddress("glVertexAttrib4usv");
        boom::glVertexAttribPointer = (boom::GLVertexAttribPointer)wglGetProcAddress("glVertexAttribPointer");
        boom::glUniformMatrix2x3fv = (boom::GLUniformMatrix2x3fv)wglGetProcAddress("glUniformMatrix2x3fv");
        boom::glUniformMatrix3x2fv = (boom::GLUniformMatrix3x2fv)wglGetProcAddress("glUniformMatrix3x2fv");
        boom::glUniformMatrix2x4fv = (boom::GLUniformMatrix2x4fv)wglGetProcAddress("glUniformMatrix2x4fv");
        boom::glUniformMatrix4x2fv = (boom::GLUniformMatrix4x2fv)wglGetProcAddress("glUniformMatrix4x2fv");
        boom::glUniformMatrix3x4fv = (boom::GLUniformMatrix3x4fv)wglGetProcAddress("glUniformMatrix3x4fv");
        boom::glUniformMatrix4x3fv = (boom::GLUniformMatrix4x3fv)wglGetProcAddress("glUniformMatrix4x3fv");
        boom::glColorMaski = (boom::GLColorMaski)wglGetProcAddress("glColorMaski");
        boom::glGetBooleani_v = (boom::GLGetBooleani_v)wglGetProcAddress("glGetBooleani_v");
        boom::glGetIntegeri_v = (boom::GLGetIntegeri_v)wglGetProcAddress("glGetIntegeri_v");
        boom::glEnablei = (boom::GLEnablei)wglGetProcAddress("glEnablei");
        boom::glDisablei = (boom::GLDisablei)wglGetProcAddress("glDisablei");
        boom::glBeginTransformFeedback = (boom::GLBeginTransformFeedback)wglGetProcAddress("glBeginTransformFeedback");
        boom::glEndTransformFeedback = (boom::GLEndTransformFeedback)wglGetProcAddress("glEndTransformFeedback");
        boom::glBindBufferRange = (boom::GLBindBufferRange)wglGetProcAddress("glBindBufferRange");
        boom::glBindBufferBase = (boom::GLBindBufferBase)wglGetProcAddress("glBindBufferBase");
        boom::glTransformFeedbackVaryings = (boom::GLTransformFeedbackVaryings)wglGetProcAddress("glTransformFeedbackVaryings");
        boom::glGetTransformFeedbackVarying = (boom::GLGetTransformFeedbackVarying)wglGetProcAddress("glGetTransformFeedbackVarying");
        boom::glClampColor = (boom::GLClampColor)wglGetProcAddress("glClampColor");
        boom::glBeginConditionalRender = (boom::GLBeginConditionalRender)wglGetProcAddress("glBeginConditionalRender");
        boom::glEndConditionalRender = (boom::GLEndConditionalRender)wglGetProcAddress("glEndConditionalRender");
        boom::glVertexAttribIPointer = (boom::GLVertexAttribIPointer)wglGetProcAddress("glVertexAttribIPointer");
        boom::glGetVertexAttribIiv = (boom::GLGetVertexAttribIiv)wglGetProcAddress("glGetVertexAttribIiv");
        boom::glGetVertexAttribIuiv = (boom::GLGetVertexAttribIuiv)wglGetProcAddress("glGetVertexAttribIuiv");
        boom::glVertexAttribI1i = (boom::GLVertexAttribI1i)wglGetProcAddress("glVertexAttribI1i");
        boom::glVertexAttribI2i = (boom::GLVertexAttribI2i)wglGetProcAddress("glVertexAttribI2i");
        boom::glVertexAttribI3i = (boom::GLVertexAttribI3i)wglGetProcAddress("glVertexAttribI3i");
        boom::glVertexAttribI4i = (boom::GLVertexAttribI4i)wglGetProcAddress("glVertexAttribI4i");
        boom::glVertexAttribI1ui = (boom::GLVertexAttribI1ui)wglGetProcAddress("glVertexAttribI1ui");
        boom::glVertexAttribI2ui = (boom::GLVertexAttribI2ui)wglGetProcAddress("glVertexAttribI2ui");
        boom::glVertexAttribI3ui = (boom::GLVertexAttribI3ui)wglGetProcAddress("glVertexAttribI3ui");
        boom::glVertexAttribI4ui = (boom::GLVertexAttribI4ui)wglGetProcAddress("glVertexAttribI4ui");
        boom::glVertexAttribI1iv = (boom::GLVertexAttribI1iv)wglGetProcAddress("glVertexAttribI1iv");
        boom::glVertexAttribI2iv = (boom::GLVertexAttribI2iv)wglGetProcAddress("glVertexAttribI2iv");
        boom::glVertexAttribI3iv = (boom::GLVertexAttribI3iv)wglGetProcAddress("glVertexAttribI3iv");
        boom::glVertexAttribI4iv = (boom::GLVertexAttribI4iv)wglGetProcAddress("glVertexAttribI4iv");
        boom::glVertexAttribI1uiv = (boom::GLVertexAttribI1uiv)wglGetProcAddress("glVertexAttribI1uiv");
        boom::glVertexAttribI2uiv = (boom::GLVertexAttribI2uiv)wglGetProcAddress("glVertexAttribI2uiv");
        boom::glVertexAttribI3uiv = (boom::GLVertexAttribI3uiv)wglGetProcAddress("glVertexAttribI3uiv");
        boom::glVertexAttribI4uiv = (boom::GLVertexAttribI4uiv)wglGetProcAddress("glVertexAttribI4uiv");
        boom::glVertexAttribI4bv = (boom::GLVertexAttribI4bv)wglGetProcAddress("glVertexAttribI4bv");
        boom::glVertexAttribI4sv = (boom::GLVertexAttribI4sv)wglGetProcAddress("glVertexAttribI4sv");
        boom::glVertexAttribI4ubv = (boom::GLVertexAttribI4ubv)wglGetProcAddress("glVertexAttribI4ubv");
        boom::glVertexAttribI4usv = (boom::GLVertexAttribI4usv)wglGetProcAddress("glVertexAttribI4usv");
        boom::glGetUniformuiv = (boom::GLGetUniformuiv)wglGetProcAddress("glGetUniformuiv");
        boom::glBindFragDataLocation = (boom::GLBindFragDataLocation)wglGetProcAddress("glBindFragDataLocation");
        boom::glUniform1ui = (boom::GLUniform1ui)wglGetProcAddress("glUniform1ui");
        boom::glUniform2ui = (boom::GLUniform2ui)wglGetProcAddress("glUniform2ui");
        boom::glUniform3ui = (boom::GLUniform3ui)wglGetProcAddress("glUniform3ui");
        boom::glUniform4ui = (boom::GLUniform4ui)wglGetProcAddress("glUniform4ui");
        boom::glUniform1uiv = (boom::GLUniform1uiv)wglGetProcAddress("glUniform1uiv");
        boom::glUniform2uiv = (boom::GLUniform2uiv)wglGetProcAddress("glUniform2uiv");
        boom::glUniform3uiv = (boom::GLUniform3uiv)wglGetProcAddress("glUniform3uiv");
        boom::glUniform4uiv = (boom::GLUniform4uiv)wglGetProcAddress("glUniform4uiv");
        boom::glTexParameterIiv = (boom::GLTexParameterIiv)wglGetProcAddress("glTexParameterIiv");
        boom::glTexParameterIuiv = (boom::GLTexParameterIuiv)wglGetProcAddress("glTexParameterIuiv");
        boom::glGetTexParameterIiv = (boom::GLGetTexParameterIiv)wglGetProcAddress("glGetTexParameterIiv");
        boom::glGetTexParameterIuiv = (boom::GLGetTexParameterIuiv)wglGetProcAddress("glGetTexParameterIuiv");
        boom::glClearBufferiv = (boom::GLClearBufferiv)wglGetProcAddress("glClearBufferiv");
        boom::glClearBufferuiv = (boom::GLClearBufferuiv)wglGetProcAddress("glClearBufferuiv");
        boom::glClearBufferfv = (boom::GLClearBufferfv)wglGetProcAddress("glClearBufferfv");
        boom::glClearBufferfi = (boom::GLClearBufferfi)wglGetProcAddress("glClearBufferfi");
        boom::glBindRenderbuffer = (boom::GLBindRenderbuffer)wglGetProcAddress("glBindRenderbuffer");
        boom::glDeleteRenderbuffers = (boom::GLDeleteRenderbuffers)wglGetProcAddress("glDeleteRenderbuffers");
        boom::glGenRenderbuffers = (boom::GLGenRenderbuffers)wglGetProcAddress("glGenRenderbuffers");
        boom::glRenderbufferStorage = (boom::GLRenderbufferStorage)wglGetProcAddress("glRenderbufferStorage");
        boom::glGetRenderbufferParameteriv = (boom::GLGetRenderbufferParameteriv)wglGetProcAddress("glGetRenderbufferParameteriv");
        boom::glBindFramebuffer = (boom::GLBindFramebuffer)wglGetProcAddress("glBindFramebuffer");
        boom::glDeleteFramebuffers = (boom::GLDeleteFramebuffers)wglGetProcAddress("glDeleteFramebuffers");
        boom::glGenFramebuffers = (boom::GLGenFramebuffers)wglGetProcAddress("glGenFramebuffers");
        boom::glFramebufferTexture1D = (boom::GLFramebufferTexture1D)wglGetProcAddress("glFramebufferTexture1D");
        boom::glFramebufferTexture2D = (boom::GLFramebufferTexture2D)wglGetProcAddress("glFramebufferTexture2D");
        boom::glFramebufferTexture3D = (boom::GLFramebufferTexture3D)wglGetProcAddress("glFramebufferTexture3D");
        boom::glFramebufferRenderbuffer = (boom::GLFramebufferRenderbuffer)wglGetProcAddress("glFramebufferRenderbuffer");
        boom::glGetFramebufferAttachmentParameteriv = (boom::GLGetFramebufferAttachmentParameteriv)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
        boom::glGenerateMipmap = (boom::GLGenerateMipmap)wglGetProcAddress("glGenerateMipmap");
        boom::glBlitFramebuffer = (boom::GLBlitFramebuffer)wglGetProcAddress("glBlitFramebuffer");
        boom::glRenderbufferStorageMultisample = (boom::GLRenderbufferStorageMultisample)wglGetProcAddress("glRenderbufferStorageMultisample");
        boom::glFramebufferTextureLayer = (boom::GLFramebufferTextureLayer)wglGetProcAddress("glFramebufferTextureLayer");
        boom::glFlushMappedBufferRange = (boom::GLFlushMappedBufferRange)wglGetProcAddress("glFlushMappedBufferRange");
        boom::glBindVertexArray = (boom::GLBindVertexArray)wglGetProcAddress("glBindVertexArray");
        boom::glDeleteVertexArrays = (boom::GLDeleteVertexArrays)wglGetProcAddress("glDeleteVertexArrays");
        boom::glGenVertexArrays = (boom::GLGenVertexArrays)wglGetProcAddress("glGenVertexArrays");
        boom::glDrawArraysInstanced = (boom::GLDrawArraysInstanced)wglGetProcAddress("glDrawArraysInstanced");
        boom::glDrawElementsInstanced = (boom::GLDrawElementsInstanced)wglGetProcAddress("glDrawElementsInstanced");
        boom::glTexBuffer = (boom::GLTexBuffer)wglGetProcAddress("glTexBuffer");
        boom::glPrimitiveRestartIndex = (boom::GLPrimitiveRestartIndex)wglGetProcAddress("glPrimitiveRestartIndex");
        boom::glCopyBufferSubData = (boom::GLCopyBufferSubData)wglGetProcAddress("glCopyBufferSubData");
        boom::glGetUniformIndices = (boom::GLGetUniformIndices)wglGetProcAddress("glGetUniformIndices");
        boom::glGetActiveUniformsiv = (boom::GLGetActiveUniformsiv)wglGetProcAddress("glGetActiveUniformsiv");
        boom::glGetActiveUniformName = (boom::GLGetActiveUniformName)wglGetProcAddress("glGetActiveUniformName");
        boom::glGetActiveUniformBlockiv = (boom::GLGetActiveUniformBlockiv)wglGetProcAddress("glGetActiveUniformBlockiv");
        boom::glGetActiveUniformBlockName = (boom::GLGetActiveUniformBlockName)wglGetProcAddress("glGetActiveUniformBlockName");
        boom::glUniformBlockBinding = (boom::GLUniformBlockBinding)wglGetProcAddress("glUniformBlockBinding");
        boom::glDrawElementsBaseVertex = (boom::GLDrawElementsBaseVertex)wglGetProcAddress("glDrawElementsBaseVertex");
        boom::glDrawRangeElementsBaseVertex = (boom::GLDrawRangeElementsBaseVertex)wglGetProcAddress("glDrawRangeElementsBaseVertex");
        boom::glDrawElementsInstancedBaseVertex = (boom::GLDrawElementsInstancedBaseVertex)wglGetProcAddress("glDrawElementsInstancedBaseVertex");
        boom::glMultiDrawElementsBaseVertex = (boom::GLMultiDrawElementsBaseVertex)wglGetProcAddress("glMultiDrawElementsBaseVertex");
        boom::glProvokingVertex = (boom::GLProvokingVertex)wglGetProcAddress("glProvokingVertex");
        boom::glDeleteSync = (boom::GLDeleteSync)wglGetProcAddress("glDeleteSync");
        boom::glWaitSync = (boom::GLWaitSync)wglGetProcAddress("glWaitSync");
        boom::glGetInteger64v = (boom::GLGetInteger64v)wglGetProcAddress("glGetInteger64v");
        boom::glGetSynciv = (boom::GLGetSynciv)wglGetProcAddress("glGetSynciv");
        boom::glGetInteger64i_v = (boom::GLGetInteger64i_v)wglGetProcAddress("glGetInteger64i_v");
        boom::glGetBufferParameteri64v = (boom::GLGetBufferParameteri64v)wglGetProcAddress("glGetBufferParameteri64v");
        boom::glFramebufferTexture = (boom::GLFramebufferTexture)wglGetProcAddress("glFramebufferTexture");
        boom::glTexImage2DMultisample = (boom::GLTexImage2DMultisample)wglGetProcAddress("glTexImage2DMultisample");
        boom::glTexImage3DMultisample = (boom::GLTexImage3DMultisample)wglGetProcAddress("glTexImage3DMultisample");
        boom::glGetMultisamplefv = (boom::GLGetMultisamplefv)wglGetProcAddress("glGetMultisamplefv");
        boom::glSampleMaski = (boom::GLSampleMaski)wglGetProcAddress("glSampleMaski");
        boom::glBindFragDataLocationIndexed = (boom::GLBindFragDataLocationIndexed)wglGetProcAddress("glBindFragDataLocationIndexed");
        boom::glGenSamplers = (boom::GLGenSamplers)wglGetProcAddress("glGenSamplers");
        boom::glDeleteSamplers = (boom::GLDeleteSamplers)wglGetProcAddress("glDeleteSamplers");
        boom::glBindSampler = (boom::GLBindSampler)wglGetProcAddress("glBindSampler");
        boom::glSamplerParameteri = (boom::GLSamplerParameteri)wglGetProcAddress("glSamplerParameteri");
        boom::glSamplerParameteriv = (boom::GLSamplerParameteriv)wglGetProcAddress("glSamplerParameteriv");
        boom::glSamplerParameterf = (boom::GLSamplerParameterf)wglGetProcAddress("glSamplerParameterf");
        boom::glSamplerParameterfv = (boom::GLSamplerParameterfv)wglGetProcAddress("glSamplerParameterfv");
        boom::glSamplerParameterIiv = (boom::GLSamplerParameterIiv)wglGetProcAddress("glSamplerParameterIiv");
        boom::glSamplerParameterIuiv = (boom::GLSamplerParameterIuiv)wglGetProcAddress("glSamplerParameterIuiv");
        boom::glGetSamplerParameteriv = (boom::GLGetSamplerParameteriv)wglGetProcAddress("glGetSamplerParameteriv");
        boom::glGetSamplerParameterIiv = (boom::GLGetSamplerParameterIiv)wglGetProcAddress("glGetSamplerParameterIiv");
        boom::glGetSamplerParameterfv = (boom::GLGetSamplerParameterfv)wglGetProcAddress("glGetSamplerParameterfv");
        boom::glGetSamplerParameterIuiv = (boom::GLGetSamplerParameterIuiv)wglGetProcAddress("glGetSamplerParameterIuiv");
        boom::glQueryCounter = (boom::GLQueryCounter)wglGetProcAddress("glQueryCounter");
        boom::glGetQueryObjecti64v = (boom::GLGetQueryObjecti64v)wglGetProcAddress("glGetQueryObjecti64v");
        boom::glGetQueryObjectui64v = (boom::GLGetQueryObjectui64v)wglGetProcAddress("glGetQueryObjectui64v");
        boom::glVertexAttribDivisor = (boom::GLVertexAttribDivisor)wglGetProcAddress("glVertexAttribDivisor");
        boom::glVertexAttribP1ui = (boom::GLVertexAttribP1ui)wglGetProcAddress("glVertexAttribP1ui");
        boom::glVertexAttribP1uiv = (boom::GLVertexAttribP1uiv)wglGetProcAddress("glVertexAttribP1uiv");
        boom::glVertexAttribP2ui = (boom::GLVertexAttribP2ui)wglGetProcAddress("glVertexAttribP2ui");
        boom::glVertexAttribP2uiv = (boom::GLVertexAttribP2uiv)wglGetProcAddress("glVertexAttribP2uiv");
        boom::glVertexAttribP3ui = (boom::GLVertexAttribP3ui)wglGetProcAddress("glVertexAttribP3ui");
        boom::glVertexAttribP3uiv = (boom::GLVertexAttribP3uiv)wglGetProcAddress("glVertexAttribP3uiv");
        boom::glVertexAttribP4ui = (boom::GLVertexAttribP4ui)wglGetProcAddress("glVertexAttribP4ui");
        boom::glVertexAttribP4uiv = (boom::GLVertexAttribP4uiv)wglGetProcAddress("glVertexAttribP4uiv");
        boom::glVertexP2ui = (boom::GLVertexP2ui)wglGetProcAddress("glVertexP2ui");
        boom::glVertexP2uiv = (boom::GLVertexP2uiv)wglGetProcAddress("glVertexP2uiv");
        boom::glVertexP3ui = (boom::GLVertexP3ui)wglGetProcAddress("glVertexP3ui");
        boom::glVertexP3uiv = (boom::GLVertexP3uiv)wglGetProcAddress("glVertexP3uiv");
        boom::glVertexP4ui = (boom::GLVertexP4ui)wglGetProcAddress("glVertexP4ui");
        boom::glVertexP4uiv = (boom::GLVertexP4uiv)wglGetProcAddress("glVertexP4uiv");
        boom::glTexCoordP1ui = (boom::GLTexCoordP1ui)wglGetProcAddress("glTexCoordP1ui");
        boom::glTexCoordP1uiv = (boom::GLTexCoordP1uiv)wglGetProcAddress("glTexCoordP1uiv");
        boom::glTexCoordP2ui = (boom::GLTexCoordP2ui)wglGetProcAddress("glTexCoordP2ui");
        boom::glTexCoordP2uiv = (boom::GLTexCoordP2uiv)wglGetProcAddress("glTexCoordP2uiv");
        boom::glTexCoordP3ui = (boom::GLTexCoordP3ui)wglGetProcAddress("glTexCoordP3ui");
        boom::glTexCoordP3uiv = (boom::GLTexCoordP3uiv)wglGetProcAddress("glTexCoordP3uiv");
        boom::glTexCoordP4ui = (boom::GLTexCoordP4ui)wglGetProcAddress("glTexCoordP4ui");
        boom::glTexCoordP4uiv = (boom::GLTexCoordP4uiv)wglGetProcAddress("glTexCoordP4uiv");
        boom::glMultiTexCoordP1ui = (boom::GLMultiTexCoordP1ui)wglGetProcAddress("glMultiTexCoordP1ui");
        boom::glMultiTexCoordP1uiv = (boom::GLMultiTexCoordP1uiv)wglGetProcAddress("glMultiTexCoordP1uiv");
        boom::glMultiTexCoordP2ui = (boom::GLMultiTexCoordP2ui)wglGetProcAddress("glMultiTexCoordP2ui");
        boom::glMultiTexCoordP2uiv = (boom::GLMultiTexCoordP2uiv)wglGetProcAddress("glMultiTexCoordP2uiv");
        boom::glMultiTexCoordP3ui = (boom::GLMultiTexCoordP3ui)wglGetProcAddress("glMultiTexCoordP3ui");
        boom::glMultiTexCoordP3uiv = (boom::GLMultiTexCoordP3uiv)wglGetProcAddress("glMultiTexCoordP3uiv");
        boom::glMultiTexCoordP4ui = (boom::GLMultiTexCoordP4ui)wglGetProcAddress("glMultiTexCoordP4ui");
        boom::glMultiTexCoordP4uiv = (boom::GLMultiTexCoordP4uiv)wglGetProcAddress("glMultiTexCoordP4uiv");
        boom::glNormalP3ui = (boom::GLNormalP3ui)wglGetProcAddress("glNormalP3ui");
        boom::glNormalP3uiv = (boom::GLNormalP3uiv)wglGetProcAddress("glNormalP3uiv");
        boom::glColorP3ui = (boom::GLColorP3ui)wglGetProcAddress("glColorP3ui");
        boom::glColorP3uiv = (boom::GLColorP3uiv)wglGetProcAddress("glColorP3uiv");
        boom::glColorP4ui = (boom::GLColorP4ui)wglGetProcAddress("glColorP4ui");
        boom::glColorP4uiv = (boom::GLColorP4uiv)wglGetProcAddress("glColorP4uiv");
        boom::glSecondaryColorP3ui = (boom::GLSecondaryColorP3ui)wglGetProcAddress("glSecondaryColorP3ui");
        boom::glSecondaryColorP3uiv = (boom::GLSecondaryColorP3uiv)wglGetProcAddress("glSecondaryColorP3uiv");
        boom::glMinSampleShading = (boom::GLMinSampleShading)wglGetProcAddress("glMinSampleShading");
        boom::glBlendEquationi = (boom::GLBlendEquationi)wglGetProcAddress("glBlendEquationi");
        boom::glBlendEquationSeparatei = (boom::GLBlendEquationSeparatei)wglGetProcAddress("glBlendEquationSeparatei");
        boom::glBlendFunci = (boom::GLBlendFunci)wglGetProcAddress("glBlendFunci");
        boom::glBlendFuncSeparatei = (boom::GLBlendFuncSeparatei)wglGetProcAddress("glBlendFuncSeparatei");
        boom::glDrawArraysIndirect = (boom::GLDrawArraysIndirect)wglGetProcAddress("glDrawArraysIndirect");
        boom::glDrawElementsIndirect = (boom::GLDrawElementsIndirect)wglGetProcAddress("glDrawElementsIndirect");
        boom::glUniform1d = (boom::GLUniform1d)wglGetProcAddress("glUniform1d");
        boom::glUniform2d = (boom::GLUniform2d)wglGetProcAddress("glUniform2d");
        boom::glUniform3d = (boom::GLUniform3d)wglGetProcAddress("glUniform3d");
        boom::glUniform4d = (boom::GLUniform4d)wglGetProcAddress("glUniform4d");
        boom::glUniform1dv = (boom::GLUniform1dv)wglGetProcAddress("glUniform1dv");
        boom::glUniform2dv = (boom::GLUniform2dv)wglGetProcAddress("glUniform2dv");
        boom::glUniform3dv = (boom::GLUniform3dv)wglGetProcAddress("glUniform3dv");
        boom::glUniform4dv = (boom::GLUniform4dv)wglGetProcAddress("glUniform4dv");
        boom::glUniformMatrix2dv = (boom::GLUniformMatrix2dv)wglGetProcAddress("glUniformMatrix2dv");
        boom::glUniformMatrix3dv = (boom::GLUniformMatrix3dv)wglGetProcAddress("glUniformMatrix3dv");
        boom::glUniformMatrix4dv = (boom::GLUniformMatrix4dv)wglGetProcAddress("glUniformMatrix4dv");
        boom::glUniformMatrix2x3dv = (boom::GLUniformMatrix2x3dv)wglGetProcAddress("glUniformMatrix2x3dv");
        boom::glUniformMatrix2x4dv = (boom::GLUniformMatrix2x4dv)wglGetProcAddress("glUniformMatrix2x4dv");
        boom::glUniformMatrix3x2dv = (boom::GLUniformMatrix3x2dv)wglGetProcAddress("glUniformMatrix3x2dv");
        boom::glUniformMatrix3x4dv = (boom::GLUniformMatrix3x4dv)wglGetProcAddress("glUniformMatrix3x4dv");
        boom::glUniformMatrix4x2dv = (boom::GLUniformMatrix4x2dv)wglGetProcAddress("glUniformMatrix4x2dv");
        boom::glUniformMatrix4x3dv = (boom::GLUniformMatrix4x3dv)wglGetProcAddress("glUniformMatrix4x3dv");
        boom::glGetUniformdv = (boom::GLGetUniformdv)wglGetProcAddress("glGetUniformdv");
        boom::glGetActiveSubroutineUniformiv = (boom::GLGetActiveSubroutineUniformiv)wglGetProcAddress("glGetActiveSubroutineUniformiv");
        boom::glGetActiveSubroutineUniformName = (boom::GLGetActiveSubroutineUniformName)wglGetProcAddress("glGetActiveSubroutineUniformName");
        boom::glGetActiveSubroutineName = (boom::GLGetActiveSubroutineName)wglGetProcAddress("glGetActiveSubroutineName");
        boom::glUniformSubroutinesuiv = (boom::GLUniformSubroutinesuiv)wglGetProcAddress("glUniformSubroutinesuiv");
        boom::glGetUniformSubroutineuiv = (boom::GLGetUniformSubroutineuiv)wglGetProcAddress("glGetUniformSubroutineuiv");
        boom::glGetProgramStageiv = (boom::GLGetProgramStageiv)wglGetProcAddress("glGetProgramStageiv");
        boom::glPatchParameteri = (boom::GLPatchParameteri)wglGetProcAddress("glPatchParameteri");
        boom::glPatchParameterfv = (boom::GLPatchParameterfv)wglGetProcAddress("glPatchParameterfv");
        boom::glBindTransformFeedback = (boom::GLBindTransformFeedback)wglGetProcAddress("glBindTransformFeedback");
        boom::glDeleteTransformFeedbacks = (boom::GLDeleteTransformFeedbacks)wglGetProcAddress("glDeleteTransformFeedbacks");
        boom::glGenTransformFeedbacks = (boom::GLGenTransformFeedbacks)wglGetProcAddress("glGenTransformFeedbacks");
        boom::glPauseTransformFeedback = (boom::GLPauseTransformFeedback)wglGetProcAddress("glPauseTransformFeedback");
        boom::glResumeTransformFeedback = (boom::GLResumeTransformFeedback)wglGetProcAddress("glResumeTransformFeedback");
        boom::glDrawTransformFeedback = (boom::GLDrawTransformFeedback)wglGetProcAddress("glDrawTransformFeedback");
        boom::glDrawTransformFeedbackStream = (boom::GLDrawTransformFeedbackStream)wglGetProcAddress("glDrawTransformFeedbackStream");
        boom::glBeginQueryIndexed = (boom::GLBeginQueryIndexed)wglGetProcAddress("glBeginQueryIndexed");
        boom::glEndQueryIndexed = (boom::GLEndQueryIndexed)wglGetProcAddress("glEndQueryIndexed");
        boom::glGetQueryIndexediv = (boom::GLGetQueryIndexediv)wglGetProcAddress("glGetQueryIndexediv");
        boom::glReleaseShaderCompiler = (boom::GLReleaseShaderCompiler)wglGetProcAddress("glReleaseShaderCompiler");
        boom::glShaderBinary = (boom::GLShaderBinary)wglGetProcAddress("glShaderBinary");
        boom::glGetShaderPrecisionFormat = (boom::GLGetShaderPrecisionFormat)wglGetProcAddress("glGetShaderPrecisionFormat");
        boom::glDepthRangef = (boom::GLDepthRangef)wglGetProcAddress("glDepthRangef");
        boom::glClearDepthf = (boom::GLClearDepthf)wglGetProcAddress("glClearDepthf");
        boom::glGetProgramBinary = (boom::GLGetProgramBinary)wglGetProcAddress("glGetProgramBinary");
        boom::glProgramBinary = (boom::GLProgramBinary)wglGetProcAddress("glProgramBinary");
        boom::glProgramParameteri = (boom::GLProgramParameteri)wglGetProcAddress("glProgramParameteri");
        boom::glUseProgramStages = (boom::GLUseProgramStages)wglGetProcAddress("glUseProgramStages");
        boom::glActiveShaderProgram = (boom::GLActiveShaderProgram)wglGetProcAddress("glActiveShaderProgram");
        boom::glBindProgramPipeline = (boom::GLBindProgramPipeline)wglGetProcAddress("glBindProgramPipeline");
        boom::glDeleteProgramPipelines = (boom::GLDeleteProgramPipelines)wglGetProcAddress("glDeleteProgramPipelines");
        boom::glGenProgramPipelines = (boom::GLGenProgramPipelines)wglGetProcAddress("glGenProgramPipelines");
        boom::glGetProgramPipelineiv = (boom::GLGetProgramPipelineiv)wglGetProcAddress("glGetProgramPipelineiv");
        boom::glProgramUniform1i = (boom::GLProgramUniform1i)wglGetProcAddress("glProgramUniform1i");
        boom::glProgramUniform1iv = (boom::GLProgramUniform1iv)wglGetProcAddress("glProgramUniform1iv");
        boom::glProgramUniform1f = (boom::GLProgramUniform1f)wglGetProcAddress("glProgramUniform1f");
        boom::glProgramUniform1fv = (boom::GLProgramUniform1fv)wglGetProcAddress("glProgramUniform1fv");
        boom::glProgramUniform1d = (boom::GLProgramUniform1d)wglGetProcAddress("glProgramUniform1d");
        boom::glProgramUniform1dv = (boom::GLProgramUniform1dv)wglGetProcAddress("glProgramUniform1dv");
        boom::glProgramUniform1ui = (boom::GLProgramUniform1ui)wglGetProcAddress("glProgramUniform1ui");
        boom::glProgramUniform1uiv = (boom::GLProgramUniform1uiv)wglGetProcAddress("glProgramUniform1uiv");
        boom::glProgramUniform2i = (boom::GLProgramUniform2i)wglGetProcAddress("glProgramUniform2i");
        boom::glProgramUniform2iv = (boom::GLProgramUniform2iv)wglGetProcAddress("glProgramUniform2iv");
        boom::glProgramUniform2f = (boom::GLProgramUniform2f)wglGetProcAddress("glProgramUniform2f");
        boom::glProgramUniform2fv = (boom::GLProgramUniform2fv)wglGetProcAddress("glProgramUniform2fv");
        boom::glProgramUniform2d = (boom::GLProgramUniform2d)wglGetProcAddress("glProgramUniform2d");
        boom::glProgramUniform2dv = (boom::GLProgramUniform2dv)wglGetProcAddress("glProgramUniform2dv");
        boom::glProgramUniform2ui = (boom::GLProgramUniform2ui)wglGetProcAddress("glProgramUniform2ui");
        boom::glProgramUniform2uiv = (boom::GLProgramUniform2uiv)wglGetProcAddress("glProgramUniform2uiv");
        boom::glProgramUniform3i = (boom::GLProgramUniform3i)wglGetProcAddress("glProgramUniform3i");
        boom::glProgramUniform3iv = (boom::GLProgramUniform3iv)wglGetProcAddress("glProgramUniform3iv");
        boom::glProgramUniform3f = (boom::GLProgramUniform3f)wglGetProcAddress("glProgramUniform3f");
        boom::glProgramUniform3fv = (boom::GLProgramUniform3fv)wglGetProcAddress("glProgramUniform3fv");
        boom::glProgramUniform3d = (boom::GLProgramUniform3d)wglGetProcAddress("glProgramUniform3d");
        boom::glProgramUniform3dv = (boom::GLProgramUniform3dv)wglGetProcAddress("glProgramUniform3dv");
        boom::glProgramUniform3ui = (boom::GLProgramUniform3ui)wglGetProcAddress("glProgramUniform3ui");
        boom::glProgramUniform3uiv = (boom::GLProgramUniform3uiv)wglGetProcAddress("glProgramUniform3uiv");
        boom::glProgramUniform4i = (boom::GLProgramUniform4i)wglGetProcAddress("glProgramUniform4i");
        boom::glProgramUniform4iv = (boom::GLProgramUniform4iv)wglGetProcAddress("glProgramUniform4iv");
        boom::glProgramUniform4f = (boom::GLProgramUniform4f)wglGetProcAddress("glProgramUniform4f");
        boom::glProgramUniform4fv = (boom::GLProgramUniform4fv)wglGetProcAddress("glProgramUniform4fv");
        boom::glProgramUniform4d = (boom::GLProgramUniform4d)wglGetProcAddress("glProgramUniform4d");
        boom::glProgramUniform4dv = (boom::GLProgramUniform4dv)wglGetProcAddress("glProgramUniform4dv");
        boom::glProgramUniform4ui = (boom::GLProgramUniform4ui)wglGetProcAddress("glProgramUniform4ui");
        boom::glProgramUniform4uiv = (boom::GLProgramUniform4uiv)wglGetProcAddress("glProgramUniform4uiv");
        boom::glProgramUniformMatrix2fv = (boom::GLProgramUniformMatrix2fv)wglGetProcAddress("glProgramUniformMatrix2fv");
        boom::glProgramUniformMatrix3fv = (boom::GLProgramUniformMatrix3fv)wglGetProcAddress("glProgramUniformMatrix3fv");
        boom::glProgramUniformMatrix4fv = (boom::GLProgramUniformMatrix4fv)wglGetProcAddress("glProgramUniformMatrix4fv");
        boom::glProgramUniformMatrix2dv = (boom::GLProgramUniformMatrix2dv)wglGetProcAddress("glProgramUniformMatrix2dv");
        boom::glProgramUniformMatrix3dv = (boom::GLProgramUniformMatrix3dv)wglGetProcAddress("glProgramUniformMatrix3dv");
        boom::glProgramUniformMatrix4dv = (boom::GLProgramUniformMatrix4dv)wglGetProcAddress("glProgramUniformMatrix4dv");
        boom::glProgramUniformMatrix2x3fv = (boom::GLProgramUniformMatrix2x3fv)wglGetProcAddress("glProgramUniformMatrix2x3fv");
        boom::glProgramUniformMatrix3x2fv = (boom::GLProgramUniformMatrix3x2fv)wglGetProcAddress("glProgramUniformMatrix3x2fv");
        boom::glProgramUniformMatrix2x4fv = (boom::GLProgramUniformMatrix2x4fv)wglGetProcAddress("glProgramUniformMatrix2x4fv");
        boom::glProgramUniformMatrix4x2fv = (boom::GLProgramUniformMatrix4x2fv)wglGetProcAddress("glProgramUniformMatrix4x2fv");
        boom::glProgramUniformMatrix3x4fv = (boom::GLProgramUniformMatrix3x4fv)wglGetProcAddress("glProgramUniformMatrix3x4fv");
        boom::glProgramUniformMatrix4x3fv = (boom::GLProgramUniformMatrix4x3fv)wglGetProcAddress("glProgramUniformMatrix4x3fv");
        boom::glProgramUniformMatrix2x3dv = (boom::GLProgramUniformMatrix2x3dv)wglGetProcAddress("glProgramUniformMatrix2x3dv");
        boom::glProgramUniformMatrix3x2dv = (boom::GLProgramUniformMatrix3x2dv)wglGetProcAddress("glProgramUniformMatrix3x2dv");
        boom::glProgramUniformMatrix2x4dv = (boom::GLProgramUniformMatrix2x4dv)wglGetProcAddress("glProgramUniformMatrix2x4dv");
        boom::glProgramUniformMatrix4x2dv = (boom::GLProgramUniformMatrix4x2dv)wglGetProcAddress("glProgramUniformMatrix4x2dv");
        boom::glProgramUniformMatrix3x4dv = (boom::GLProgramUniformMatrix3x4dv)wglGetProcAddress("glProgramUniformMatrix3x4dv");
        boom::glProgramUniformMatrix4x3dv = (boom::GLProgramUniformMatrix4x3dv)wglGetProcAddress("glProgramUniformMatrix4x3dv");
        boom::glValidateProgramPipeline = (boom::GLValidateProgramPipeline)wglGetProcAddress("glValidateProgramPipeline");
        boom::glGetProgramPipelineInfoLog = (boom::GLGetProgramPipelineInfoLog)wglGetProcAddress("glGetProgramPipelineInfoLog");
        boom::glVertexAttribL1d = (boom::GLVertexAttribL1d)wglGetProcAddress("glVertexAttribL1d");
        boom::glVertexAttribL2d = (boom::GLVertexAttribL2d)wglGetProcAddress("glVertexAttribL2d");
        boom::glVertexAttribL3d = (boom::GLVertexAttribL3d)wglGetProcAddress("glVertexAttribL3d");
        boom::glVertexAttribL4d = (boom::GLVertexAttribL4d)wglGetProcAddress("glVertexAttribL4d");
        boom::glVertexAttribL1dv = (boom::GLVertexAttribL1dv)wglGetProcAddress("glVertexAttribL1dv");
        boom::glVertexAttribL2dv = (boom::GLVertexAttribL2dv)wglGetProcAddress("glVertexAttribL2dv");
        boom::glVertexAttribL3dv = (boom::GLVertexAttribL3dv)wglGetProcAddress("glVertexAttribL3dv");
        boom::glVertexAttribL4dv = (boom::GLVertexAttribL4dv)wglGetProcAddress("glVertexAttribL4dv");
        boom::glVertexAttribLPointer = (boom::GLVertexAttribLPointer)wglGetProcAddress("glVertexAttribLPointer");
        boom::glGetVertexAttribLdv = (boom::GLGetVertexAttribLdv)wglGetProcAddress("glGetVertexAttribLdv");
        boom::glViewportArrayv = (boom::GLViewportArrayv)wglGetProcAddress("glViewportArrayv");
        boom::glViewportIndexedf = (boom::GLViewportIndexedf)wglGetProcAddress("glViewportIndexedf");
        boom::glViewportIndexedfv = (boom::GLViewportIndexedfv)wglGetProcAddress("glViewportIndexedfv");
        boom::glScissorArrayv = (boom::GLScissorArrayv)wglGetProcAddress("glScissorArrayv");
        boom::glScissorIndexed = (boom::GLScissorIndexed)wglGetProcAddress("glScissorIndexed");
        boom::glScissorIndexedv = (boom::GLScissorIndexedv)wglGetProcAddress("glScissorIndexedv");
        boom::glDepthRangeArrayv = (boom::GLDepthRangeArrayv)wglGetProcAddress("glDepthRangeArrayv");
        boom::glDepthRangeIndexed = (boom::GLDepthRangeIndexed)wglGetProcAddress("glDepthRangeIndexed");
        boom::glGetFloati_v = (boom::GLGetFloati_v)wglGetProcAddress("glGetFloati_v");
        boom::glGetDoublei_v = (boom::GLGetDoublei_v)wglGetProcAddress("glGetDoublei_v");
        boom::glDrawArraysInstancedBaseInstance = (boom::GLDrawArraysInstancedBaseInstance)wglGetProcAddress("glDrawArraysInstancedBaseInstance");
        boom::glDrawElementsInstancedBaseInstance = (boom::GLDrawElementsInstancedBaseInstance)wglGetProcAddress("glDrawElementsInstancedBaseInstance");
        boom::glDrawElementsInstancedBaseVertexBaseInstance = (boom::GLDrawElementsInstancedBaseVertexBaseInstance)wglGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
        boom::glGetInternalformativ = (boom::GLGetInternalformativ)wglGetProcAddress("glGetInternalformativ");
        boom::glGetActiveAtomicCounterBufferiv = (boom::GLGetActiveAtomicCounterBufferiv)wglGetProcAddress("glGetActiveAtomicCounterBufferiv");
        boom::glBindImageTexture = (boom::GLBindImageTexture)wglGetProcAddress("glBindImageTexture");
        boom::glMemoryBarrier = (boom::GLMemoryBarrier)wglGetProcAddress("glMemoryBarrier");
        boom::glTexStorage1D = (boom::GLTexStorage1D)wglGetProcAddress("glTexStorage1D");
        boom::glTexStorage2D = (boom::GLTexStorage2D)wglGetProcAddress("glTexStorage2D");
        boom::glTexStorage3D = (boom::GLTexStorage3D)wglGetProcAddress("glTexStorage3D");
        boom::glDrawTransformFeedbackInstanced = (boom::GLDrawTransformFeedbackInstanced)wglGetProcAddress("glDrawTransformFeedbackInstanced");
        boom::glDrawTransformFeedbackStreamInstanced = (boom::GLDrawTransformFeedbackStreamInstanced)wglGetProcAddress("glDrawTransformFeedbackStreamInstanced");
        boom::glClearBufferData = (boom::GLClearBufferData)wglGetProcAddress("glClearBufferData");
        boom::glClearBufferSubData = (boom::GLClearBufferSubData)wglGetProcAddress("glClearBufferSubData");
        boom::glDispatchCompute = (boom::GLDispatchCompute)wglGetProcAddress("glDispatchCompute");
        boom::glDispatchComputeIndirect = (boom::GLDispatchComputeIndirect)wglGetProcAddress("glDispatchComputeIndirect");
        boom::glCopyImageSubData = (boom::GLCopyImageSubData)wglGetProcAddress("glCopyImageSubData");
        boom::glFramebufferParameteri = (boom::GLFramebufferParameteri)wglGetProcAddress("glFramebufferParameteri");
        boom::glGetFramebufferParameteriv = (boom::GLGetFramebufferParameteriv)wglGetProcAddress("glGetFramebufferParameteriv");
        boom::glGetInternalformati64v = (boom::GLGetInternalformati64v)wglGetProcAddress("glGetInternalformati64v");
        boom::glInvalidateTexSubImage = (boom::GLInvalidateTexSubImage)wglGetProcAddress("glInvalidateTexSubImage");
        boom::glInvalidateTexImage = (boom::GLInvalidateTexImage)wglGetProcAddress("glInvalidateTexImage");
        boom::glInvalidateBufferSubData = (boom::GLInvalidateBufferSubData)wglGetProcAddress("glInvalidateBufferSubData");
        boom::glInvalidateBufferData = (boom::GLInvalidateBufferData)wglGetProcAddress("glInvalidateBufferData");
        boom::glInvalidateFramebuffer = (boom::GLInvalidateFramebuffer)wglGetProcAddress("glInvalidateFramebuffer");
        boom::glInvalidateSubFramebuffer = (boom::GLInvalidateSubFramebuffer)wglGetProcAddress("glInvalidateSubFramebuffer");
        boom::glMultiDrawArraysIndirect = (boom::GLMultiDrawArraysIndirect)wglGetProcAddress("glMultiDrawArraysIndirect");
        boom::glMultiDrawElementsIndirect = (boom::GLMultiDrawElementsIndirect)wglGetProcAddress("glMultiDrawElementsIndirect");
        boom::glGetProgramInterfaceiv = (boom::GLGetProgramInterfaceiv)wglGetProcAddress("glGetProgramInterfaceiv");
        boom::glGetProgramResourceName = (boom::GLGetProgramResourceName)wglGetProcAddress("glGetProgramResourceName");
        boom::glGetProgramResourceiv = (boom::GLGetProgramResourceiv)wglGetProcAddress("glGetProgramResourceiv");
        boom::glShaderStorageBlockBinding = (boom::GLShaderStorageBlockBinding)wglGetProcAddress("glShaderStorageBlockBinding");
        boom::glTexBufferRange = (boom::GLTexBufferRange)wglGetProcAddress("glTexBufferRange");
        boom::glTexStorage2DMultisample = (boom::GLTexStorage2DMultisample)wglGetProcAddress("glTexStorage2DMultisample");
        boom::glTexStorage3DMultisample = (boom::GLTexStorage3DMultisample)wglGetProcAddress("glTexStorage3DMultisample");
        boom::glTextureView = (boom::GLTextureView)wglGetProcAddress("glTextureView");
        boom::glBindVertexBuffer = (boom::GLBindVertexBuffer)wglGetProcAddress("glBindVertexBuffer");
        boom::glVertexAttribFormat = (boom::GLVertexAttribFormat)wglGetProcAddress("glVertexAttribFormat");
        boom::glVertexAttribIFormat = (boom::GLVertexAttribIFormat)wglGetProcAddress("glVertexAttribIFormat");
        boom::glVertexAttribLFormat = (boom::GLVertexAttribLFormat)wglGetProcAddress("glVertexAttribLFormat");
        boom::glVertexAttribBinding = (boom::GLVertexAttribBinding)wglGetProcAddress("glVertexAttribBinding");
        boom::glVertexBindingDivisor = (boom::GLVertexBindingDivisor)wglGetProcAddress("glVertexBindingDivisor");
        boom::glDebugMessageControl = (boom::GLDebugMessageControl)wglGetProcAddress("glDebugMessageControl");
        boom::glDebugMessageInsert = (boom::GLDebugMessageInsert)wglGetProcAddress("glDebugMessageInsert");
        boom::glDebugMessageCallback = (boom::GLDebugMessageCallback)wglGetProcAddress("glDebugMessageCallback");
        boom::glPushDebugGroup = (boom::GLPushDebugGroup)wglGetProcAddress("glPushDebugGroup");
        boom::glPopDebugGroup = (boom::GLPopDebugGroup)wglGetProcAddress("glPopDebugGroup");
        boom::glObjectLabel = (boom::GLObjectLabel)wglGetProcAddress("glObjectLabel");
        boom::glGetObjectLabel = (boom::GLGetObjectLabel)wglGetProcAddress("glGetObjectLabel");
        boom::glObjectPtrLabel = (boom::GLObjectPtrLabel)wglGetProcAddress("glObjectPtrLabel");
        boom::glGetObjectPtrLabel = (boom::GLGetObjectPtrLabel)wglGetProcAddress("glGetObjectPtrLabel");
        boom::glGetPointerv = (boom::GLGetPointerv)wglGetProcAddress("glGetPointerv");
        boom::glBufferStorage = (boom::GLBufferStorage)wglGetProcAddress("glBufferStorage");
        boom::glClearTexImage = (boom::GLClearTexImage)wglGetProcAddress("glClearTexImage");
        boom::glClearTexSubImage = (boom::GLClearTexSubImage)wglGetProcAddress("glClearTexSubImage");
        boom::glBindBuffersBase = (boom::GLBindBuffersBase)wglGetProcAddress("glBindBuffersBase");
        boom::glBindBuffersRange = (boom::GLBindBuffersRange)wglGetProcAddress("glBindBuffersRange");
        boom::glBindTextures = (boom::GLBindTextures)wglGetProcAddress("glBindTextures");
        boom::glBindSamplers = (boom::GLBindSamplers)wglGetProcAddress("glBindSamplers");
        boom::glBindImageTextures = (boom::GLBindImageTextures)wglGetProcAddress("glBindImageTextures");
        boom::glBindVertexBuffers = (boom::GLBindVertexBuffers)wglGetProcAddress("glBindVertexBuffers");
        boom::glClipControl = (boom::GLClipControl)wglGetProcAddress("glClipControl");
        boom::glCreateTransformFeedbacks = (boom::GLCreateTransformFeedbacks)wglGetProcAddress("glCreateTransformFeedbacks");
        boom::glTransformFeedbackBufferBase = (boom::GLTransformFeedbackBufferBase)wglGetProcAddress("glTransformFeedbackBufferBase");
        boom::glTransformFeedbackBufferRange = (boom::GLTransformFeedbackBufferRange)wglGetProcAddress("glTransformFeedbackBufferRange");
        boom::glGetTransformFeedbackiv = (boom::GLGetTransformFeedbackiv)wglGetProcAddress("glGetTransformFeedbackiv");
        boom::glGetTransformFeedbacki_v = (boom::GLGetTransformFeedbacki_v)wglGetProcAddress("glGetTransformFeedbacki_v");
        boom::glGetTransformFeedbacki64_v = (boom::GLGetTransformFeedbacki64_v)wglGetProcAddress("glGetTransformFeedbacki64_v");
        boom::glCreateBuffers = (boom::GLCreateBuffers)wglGetProcAddress("glCreateBuffers");
        boom::glNamedBufferStorage = (boom::GLNamedBufferStorage)wglGetProcAddress("glNamedBufferStorage");
        boom::glNamedBufferData = (boom::GLNamedBufferData)wglGetProcAddress("glNamedBufferData");
        boom::glNamedBufferSubData = (boom::GLNamedBufferSubData)wglGetProcAddress("glNamedBufferSubData");
        boom::glCopyNamedBufferSubData = (boom::GLCopyNamedBufferSubData)wglGetProcAddress("glCopyNamedBufferSubData");
        boom::glClearNamedBufferData = (boom::GLClearNamedBufferData)wglGetProcAddress("glClearNamedBufferData");
        boom::glClearNamedBufferSubData = (boom::GLClearNamedBufferSubData)wglGetProcAddress("glClearNamedBufferSubData");
        boom::glFlushMappedNamedBufferRange = (boom::GLFlushMappedNamedBufferRange)wglGetProcAddress("glFlushMappedNamedBufferRange");
        boom::glGetNamedBufferParameteriv = (boom::GLGetNamedBufferParameteriv)wglGetProcAddress("glGetNamedBufferParameteriv");
        boom::glGetNamedBufferParameteri64v = (boom::GLGetNamedBufferParameteri64v)wglGetProcAddress("glGetNamedBufferParameteri64v");
        boom::glGetNamedBufferPointerv = (boom::GLGetNamedBufferPointerv)wglGetProcAddress("glGetNamedBufferPointerv");
        boom::glGetNamedBufferSubData = (boom::GLGetNamedBufferSubData)wglGetProcAddress("glGetNamedBufferSubData");
        boom::glCreateFramebuffers = (boom::GLCreateFramebuffers)wglGetProcAddress("glCreateFramebuffers");
        boom::glNamedFramebufferRenderbuffer = (boom::GLNamedFramebufferRenderbuffer)wglGetProcAddress("glNamedFramebufferRenderbuffer");
        boom::glNamedFramebufferParameteri = (boom::GLNamedFramebufferParameteri)wglGetProcAddress("glNamedFramebufferParameteri");
        boom::glNamedFramebufferTexture = (boom::GLNamedFramebufferTexture)wglGetProcAddress("glNamedFramebufferTexture");
        boom::glNamedFramebufferTextureLayer = (boom::GLNamedFramebufferTextureLayer)wglGetProcAddress("glNamedFramebufferTextureLayer");
        boom::glNamedFramebufferDrawBuffer = (boom::GLNamedFramebufferDrawBuffer)wglGetProcAddress("glNamedFramebufferDrawBuffer");
        boom::glNamedFramebufferDrawBuffers = (boom::GLNamedFramebufferDrawBuffers)wglGetProcAddress("glNamedFramebufferDrawBuffers");
        boom::glNamedFramebufferReadBuffer = (boom::GLNamedFramebufferReadBuffer)wglGetProcAddress("glNamedFramebufferReadBuffer");
        boom::glInvalidateNamedFramebufferData = (boom::GLInvalidateNamedFramebufferData)wglGetProcAddress("glInvalidateNamedFramebufferData");
        boom::glInvalidateNamedFramebufferSubData = (boom::GLInvalidateNamedFramebufferSubData)wglGetProcAddress("glInvalidateNamedFramebufferSubData");
        boom::glClearNamedFramebufferiv = (boom::GLClearNamedFramebufferiv)wglGetProcAddress("glClearNamedFramebufferiv");
        boom::glClearNamedFramebufferuiv = (boom::GLClearNamedFramebufferuiv)wglGetProcAddress("glClearNamedFramebufferuiv");
        boom::glClearNamedFramebufferfv = (boom::GLClearNamedFramebufferfv)wglGetProcAddress("glClearNamedFramebufferfv");
        boom::glClearNamedFramebufferfi = (boom::GLClearNamedFramebufferfi)wglGetProcAddress("glClearNamedFramebufferfi");
        boom::glBlitNamedFramebuffer = (boom::GLBlitNamedFramebuffer)wglGetProcAddress("glBlitNamedFramebuffer");
        boom::glGetNamedFramebufferParameteriv = (boom::GLGetNamedFramebufferParameteriv)wglGetProcAddress("glGetNamedFramebufferParameteriv");
        boom::glGetNamedFramebufferAttachmentParameteriv = (boom::GLGetNamedFramebufferAttachmentParameteriv)wglGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
        boom::glCreateRenderbuffers = (boom::GLCreateRenderbuffers)wglGetProcAddress("glCreateRenderbuffers");
        boom::glNamedRenderbufferStorage = (boom::GLNamedRenderbufferStorage)wglGetProcAddress("glNamedRenderbufferStorage");
        boom::glNamedRenderbufferStorageMultisample = (boom::GLNamedRenderbufferStorageMultisample)wglGetProcAddress("glNamedRenderbufferStorageMultisample");
        boom::glGetNamedRenderbufferParameteriv = (boom::GLGetNamedRenderbufferParameteriv)wglGetProcAddress("glGetNamedRenderbufferParameteriv");
        boom::glCreateTextures = (boom::GLCreateTextures)wglGetProcAddress("glCreateTextures");
        boom::glTextureBuffer = (boom::GLTextureBuffer)wglGetProcAddress("glTextureBuffer");
        boom::glTextureBufferRange = (boom::GLTextureBufferRange)wglGetProcAddress("glTextureBufferRange");
        boom::glTextureStorage1D = (boom::GLTextureStorage1D)wglGetProcAddress("glTextureStorage1D");
        boom::glTextureStorage2D = (boom::GLTextureStorage2D)wglGetProcAddress("glTextureStorage2D");
        boom::glTextureStorage3D = (boom::GLTextureStorage3D)wglGetProcAddress("glTextureStorage3D");
        boom::glTextureStorage2DMultisample = (boom::GLTextureStorage2DMultisample)wglGetProcAddress("glTextureStorage2DMultisample");
        boom::glTextureStorage3DMultisample = (boom::GLTextureStorage3DMultisample)wglGetProcAddress("glTextureStorage3DMultisample");
        boom::glTextureSubImage1D = (boom::GLTextureSubImage1D)wglGetProcAddress("glTextureSubImage1D");
        boom::glTextureSubImage2D = (boom::GLTextureSubImage2D)wglGetProcAddress("glTextureSubImage2D");
        boom::glTextureSubImage3D = (boom::GLTextureSubImage3D)wglGetProcAddress("glTextureSubImage3D");
        boom::glCompressedTextureSubImage1D = (boom::GLCompressedTextureSubImage1D)wglGetProcAddress("glCompressedTextureSubImage1D");
        boom::glCompressedTextureSubImage2D = (boom::GLCompressedTextureSubImage2D)wglGetProcAddress("glCompressedTextureSubImage2D");
        boom::glCompressedTextureSubImage3D = (boom::GLCompressedTextureSubImage3D)wglGetProcAddress("glCompressedTextureSubImage3D");
        boom::glCopyTextureSubImage1D = (boom::GLCopyTextureSubImage1D)wglGetProcAddress("glCopyTextureSubImage1D");
        boom::glCopyTextureSubImage2D = (boom::GLCopyTextureSubImage2D)wglGetProcAddress("glCopyTextureSubImage2D");
        boom::glCopyTextureSubImage3D = (boom::GLCopyTextureSubImage3D)wglGetProcAddress("glCopyTextureSubImage3D");
        boom::glTextureParameterf = (boom::GLTextureParameterf)wglGetProcAddress("glTextureParameterf");
        boom::glTextureParameterfv = (boom::GLTextureParameterfv)wglGetProcAddress("glTextureParameterfv");
        boom::glTextureParameteri = (boom::GLTextureParameteri)wglGetProcAddress("glTextureParameteri");
        boom::glTextureParameterIiv = (boom::GLTextureParameterIiv)wglGetProcAddress("glTextureParameterIiv");
        boom::glTextureParameterIuiv = (boom::GLTextureParameterIuiv)wglGetProcAddress("glTextureParameterIuiv");
        boom::glTextureParameteriv = (boom::GLTextureParameteriv)wglGetProcAddress("glTextureParameteriv");
        boom::glGenerateTextureMipmap = (boom::GLGenerateTextureMipmap)wglGetProcAddress("glGenerateTextureMipmap");
        boom::glBindTextureUnit = (boom::GLBindTextureUnit)wglGetProcAddress("glBindTextureUnit");
        boom::glGetTextureImage = (boom::GLGetTextureImage)wglGetProcAddress("glGetTextureImage");
        boom::glGetCompressedTextureImage = (boom::GLGetCompressedTextureImage)wglGetProcAddress("glGetCompressedTextureImage");
        boom::glGetTextureLevelParameterfv = (boom::GLGetTextureLevelParameterfv)wglGetProcAddress("glGetTextureLevelParameterfv");
        boom::glGetTextureLevelParameteriv = (boom::GLGetTextureLevelParameteriv)wglGetProcAddress("glGetTextureLevelParameteriv");
        boom::glGetTextureParameterfv = (boom::GLGetTextureParameterfv)wglGetProcAddress("glGetTextureParameterfv");
        boom::glGetTextureParameterIiv = (boom::GLGetTextureParameterIiv)wglGetProcAddress("glGetTextureParameterIiv");
        boom::glGetTextureParameterIuiv = (boom::GLGetTextureParameterIuiv)wglGetProcAddress("glGetTextureParameterIuiv");
        boom::glGetTextureParameteriv = (boom::GLGetTextureParameteriv)wglGetProcAddress("glGetTextureParameteriv");
        boom::glCreateVertexArrays = (boom::GLCreateVertexArrays)wglGetProcAddress("glCreateVertexArrays");
        boom::glDisableVertexArrayAttrib = (boom::GLDisableVertexArrayAttrib)wglGetProcAddress("glDisableVertexArrayAttrib");
        boom::glEnableVertexArrayAttrib = (boom::GLEnableVertexArrayAttrib)wglGetProcAddress("glEnableVertexArrayAttrib");
        boom::glVertexArrayElementBuffer = (boom::GLVertexArrayElementBuffer)wglGetProcAddress("glVertexArrayElementBuffer");
        boom::glVertexArrayVertexBuffer = (boom::GLVertexArrayVertexBuffer)wglGetProcAddress("glVertexArrayVertexBuffer");
        boom::glVertexArrayVertexBuffers = (boom::GLVertexArrayVertexBuffers)wglGetProcAddress("glVertexArrayVertexBuffers");
        boom::glVertexArrayAttribBinding = (boom::GLVertexArrayAttribBinding)wglGetProcAddress("glVertexArrayAttribBinding");
        boom::glVertexArrayAttribFormat = (boom::GLVertexArrayAttribFormat)wglGetProcAddress("glVertexArrayAttribFormat");
        boom::glVertexArrayAttribIFormat = (boom::GLVertexArrayAttribIFormat)wglGetProcAddress("glVertexArrayAttribIFormat");
        boom::glVertexArrayAttribLFormat = (boom::GLVertexArrayAttribLFormat)wglGetProcAddress("glVertexArrayAttribLFormat");
        boom::glVertexArrayBindingDivisor = (boom::GLVertexArrayBindingDivisor)wglGetProcAddress("glVertexArrayBindingDivisor");
        boom::glGetVertexArrayiv = (boom::GLGetVertexArrayiv)wglGetProcAddress("glGetVertexArrayiv");
        boom::glGetVertexArrayIndexediv = (boom::GLGetVertexArrayIndexediv)wglGetProcAddress("glGetVertexArrayIndexediv");
        boom::glGetVertexArrayIndexed64iv = (boom::GLGetVertexArrayIndexed64iv)wglGetProcAddress("glGetVertexArrayIndexed64iv");
        boom::glCreateSamplers = (boom::GLCreateSamplers)wglGetProcAddress("glCreateSamplers");
        boom::glCreateProgramPipelines = (boom::GLCreateProgramPipelines)wglGetProcAddress("glCreateProgramPipelines");
        boom::glCreateQueries = (boom::GLCreateQueries)wglGetProcAddress("glCreateQueries");
        boom::glGetQueryBufferObjecti64v = (boom::GLGetQueryBufferObjecti64v)wglGetProcAddress("glGetQueryBufferObjecti64v");
        boom::glGetQueryBufferObjectiv = (boom::GLGetQueryBufferObjectiv)wglGetProcAddress("glGetQueryBufferObjectiv");
        boom::glGetQueryBufferObjectui64v = (boom::GLGetQueryBufferObjectui64v)wglGetProcAddress("glGetQueryBufferObjectui64v");
        boom::glGetQueryBufferObjectuiv = (boom::GLGetQueryBufferObjectuiv)wglGetProcAddress("glGetQueryBufferObjectuiv");
        boom::glMemoryBarrierByRegion = (boom::GLMemoryBarrierByRegion)wglGetProcAddress("glMemoryBarrierByRegion");
        boom::glGetTextureSubImage = (boom::GLGetTextureSubImage)wglGetProcAddress("glGetTextureSubImage");
        boom::glGetCompressedTextureSubImage = (boom::GLGetCompressedTextureSubImage)wglGetProcAddress("glGetCompressedTextureSubImage");
        boom::glGetnCompressedTexImage = (boom::GLGetnCompressedTexImage)wglGetProcAddress("glGetnCompressedTexImage");
        boom::glGetnTexImage = (boom::GLGetnTexImage)wglGetProcAddress("glGetnTexImage");
        boom::glGetnUniformdv = (boom::GLGetnUniformdv)wglGetProcAddress("glGetnUniformdv");
        boom::glGetnUniformfv = (boom::GLGetnUniformfv)wglGetProcAddress("glGetnUniformfv");
        boom::glGetnUniformiv = (boom::GLGetnUniformiv)wglGetProcAddress("glGetnUniformiv");
        boom::glGetnUniformuiv = (boom::GLGetnUniformuiv)wglGetProcAddress("glGetnUniformuiv");
        boom::glReadnPixels = (boom::GLReadnPixels)wglGetProcAddress("glReadnPixels");
        boom::glGetnMapdv = (boom::GLGetnMapdv)wglGetProcAddress("glGetnMapdv");
        boom::glGetnMapfv = (boom::GLGetnMapfv)wglGetProcAddress("glGetnMapfv");
        boom::glGetnMapiv = (boom::GLGetnMapiv)wglGetProcAddress("glGetnMapiv");
        boom::glGetnPixelMapfv = (boom::GLGetnPixelMapfv)wglGetProcAddress("glGetnPixelMapfv");
        boom::glGetnPixelMapuiv = (boom::GLGetnPixelMapuiv)wglGetProcAddress("glGetnPixelMapuiv");
        boom::glGetnPixelMapusv = (boom::GLGetnPixelMapusv)wglGetProcAddress("glGetnPixelMapusv");
        boom::glGetnPolygonStipple = (boom::GLGetnPolygonStipple)wglGetProcAddress("glGetnPolygonStipple");
        boom::glGetnColorTable = (boom::GLGetnColorTable)wglGetProcAddress("glGetnColorTable");
        boom::glGetnConvolutionFilter = (boom::GLGetnConvolutionFilter)wglGetProcAddress("glGetnConvolutionFilter");
        boom::glGetnSeparableFilter = (boom::GLGetnSeparableFilter)wglGetProcAddress("glGetnSeparableFilter");
        boom::glGetnHistogram = (boom::GLGetnHistogram)wglGetProcAddress("glGetnHistogram");
        boom::glGetnMinmax = (boom::GLGetnMinmax)wglGetProcAddress("glGetnMinmax");
        boom::glTextureBarrier = (boom::GLTextureBarrier)wglGetProcAddress("glTextureBarrier");
        boom::glSpecializeShader = (boom::GLSpecializeShader)wglGetProcAddress("glSpecializeShader");
        boom::glMultiDrawArraysIndirectCount = (boom::GLMultiDrawArraysIndirectCount)wglGetProcAddress("glMultiDrawArraysIndirectCount");
        boom::glMultiDrawElementsIndirectCount = (boom::GLMultiDrawElementsIndirectCount)wglGetProcAddress("glMultiDrawElementsIndirectCount");
        boom::glPolygonOffsetClamp = (boom::GLPolygonOffsetClamp)wglGetProcAddress("glPolygonOffsetClamp");
        boom::glBlendBarrier = (boom::GLBlendBarrier)wglGetProcAddress("glBlendBarrier");
        boom::glPrimitiveBoundingBox = (boom::GLPrimitiveBoundingBox)wglGetProcAddress("glPrimitiveBoundingBox");
        bootstrapped = true;
    }
}

} /* namespace boom */