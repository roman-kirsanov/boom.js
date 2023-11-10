#include <cassert>
#include <iostream>
#include <windows.h>
#include <GL/GL.h>
#include <Boom/Utilities.hpp>
#include "View.hpp"
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

#define wglShareListsE(...) { \
    if (!wglShareLists(__VA_ARGS__)) { \
        boom::Abort("ERROR: wglShareLists() failed"); \
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
    if (options.view.has_value()) {
        window = options.view.value()->_impl->window;
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
        WGL_CONTEXT_MAJOR_VERSION_ARB, options.majorVersion.value_or(4),
        WGL_CONTEXT_MINOR_VERSION_ARB, options.minorVersion.value_or(1),
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };
    auto context = boom::wglCreateContextAttribsARB(device, 0, contextAttrs);
    if (context == nullptr) {
        boom::Abort("ERROR: boom::OpenGL::OpenGL() failed: wglCreateContextAttribsARB() failed");
    }
    if (options.shared.has_value()) {
        wglShareListsE(options.shared.value()->_impl->context, context);
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

void OpenGL::_implSwap() const {
    SwapBuffers(_impl->device);
}

void OpenGL::_implCurrent() const {
    wglMakeCurrent(_impl->device, _impl->context);
}

void OpenGL::_implBootstrap() {
    static auto bootstrapped = false;
    if (bootstrapped == false) {
        boom::glAccum = (boom::OpenGLAccumFn)wglGetProcAddress("glAccum");
        boom::glActiveShaderProgram = (boom::OpenGLActiveShaderProgramFn)wglGetProcAddress("glActiveShaderProgram");
        boom::glActiveTexture = (boom::OpenGLActiveTextureFn)wglGetProcAddress("glActiveTexture");
        boom::glAlphaFunc = (boom::OpenGLAlphaFuncFn)wglGetProcAddress("glAlphaFunc");
        boom::glAlphaFuncx = (boom::OpenGLAlphaFuncxFn)wglGetProcAddress("glAlphaFuncx");
        boom::glAreTexturesResident = (boom::OpenGLAreTexturesResidentFn)wglGetProcAddress("glAreTexturesResident");
        boom::glArrayElement = (boom::OpenGLArrayElementFn)wglGetProcAddress("glArrayElement");
        boom::glAttachShader = (boom::OpenGLAttachShaderFn)wglGetProcAddress("glAttachShader");
        boom::glBegin = (boom::OpenGLBeginFn)wglGetProcAddress("glBegin");
        boom::glBeginConditionalRender = (boom::OpenGLBeginConditionalRenderFn)wglGetProcAddress("glBeginConditionalRender");
        boom::glBeginQuery = (boom::OpenGLBeginQueryFn)wglGetProcAddress("glBeginQuery");
        boom::glBeginQueryIndexed = (boom::OpenGLBeginQueryIndexedFn)wglGetProcAddress("glBeginQueryIndexed");
        boom::glBeginTransformFeedback = (boom::OpenGLBeginTransformFeedbackFn)wglGetProcAddress("glBeginTransformFeedback");
        boom::glBindAttribLocation = (boom::OpenGLBindAttribLocationFn)wglGetProcAddress("glBindAttribLocation");
        boom::glBindBuffer = (boom::OpenGLBindBufferFn)wglGetProcAddress("glBindBuffer");
        boom::glBindBufferBase = (boom::OpenGLBindBufferBaseFn)wglGetProcAddress("glBindBufferBase");
        boom::glBindBufferRange = (boom::OpenGLBindBufferRangeFn)wglGetProcAddress("glBindBufferRange");
        boom::glBindBuffersBase = (boom::OpenGLBindBuffersBaseFn)wglGetProcAddress("glBindBuffersBase");
        boom::glBindBuffersRange = (boom::OpenGLBindBuffersRangeFn)wglGetProcAddress("glBindBuffersRange");
        boom::glBindFragDataLocation = (boom::OpenGLBindFragDataLocationFn)wglGetProcAddress("glBindFragDataLocation");
        boom::glBindFragDataLocationIndexed = (boom::OpenGLBindFragDataLocationIndexedFn)wglGetProcAddress("glBindFragDataLocationIndexed");
        boom::glBindFramebuffer = (boom::OpenGLBindFramebufferFn)wglGetProcAddress("glBindFramebuffer");
        boom::glBindImageTexture = (boom::OpenGLBindImageTextureFn)wglGetProcAddress("glBindImageTexture");
        boom::glBindImageTextures = (boom::OpenGLBindImageTexturesFn)wglGetProcAddress("glBindImageTextures");
        boom::glBindProgramPipeline = (boom::OpenGLBindProgramPipelineFn)wglGetProcAddress("glBindProgramPipeline");
        boom::glBindRenderbuffer = (boom::OpenGLBindRenderbufferFn)wglGetProcAddress("glBindRenderbuffer");
        boom::glBindSampler = (boom::OpenGLBindSamplerFn)wglGetProcAddress("glBindSampler");
        boom::glBindSamplers = (boom::OpenGLBindSamplersFn)wglGetProcAddress("glBindSamplers");
        boom::glBindTexture = (boom::OpenGLBindTextureFn)wglGetProcAddress("glBindTexture");
        boom::glBindTextureUnit = (boom::OpenGLBindTextureUnitFn)wglGetProcAddress("glBindTextureUnit");
        boom::glBindTextures = (boom::OpenGLBindTexturesFn)wglGetProcAddress("glBindTextures");
        boom::glBindTransformFeedback = (boom::OpenGLBindTransformFeedbackFn)wglGetProcAddress("glBindTransformFeedback");
        boom::glBindVertexArray = (boom::OpenGLBindVertexArrayFn)wglGetProcAddress("glBindVertexArray");
        boom::glBindVertexBuffer = (boom::OpenGLBindVertexBufferFn)wglGetProcAddress("glBindVertexBuffer");
        boom::glBindVertexBuffers = (boom::OpenGLBindVertexBuffersFn)wglGetProcAddress("glBindVertexBuffers");
        boom::glBitmap = (boom::OpenGLBitmapFn)wglGetProcAddress("glBitmap");
        boom::glBlendBarrier = (boom::OpenGLBlendBarrierFn)wglGetProcAddress("glBlendBarrier");
        boom::glBlendColor = (boom::OpenGLBlendColorFn)wglGetProcAddress("glBlendColor");
        boom::glBlendEquation = (boom::OpenGLBlendEquationFn)wglGetProcAddress("glBlendEquation");
        boom::glBlendEquationSeparate = (boom::OpenGLBlendEquationSeparateFn)wglGetProcAddress("glBlendEquationSeparate");
        boom::glBlendEquationSeparatei = (boom::OpenGLBlendEquationSeparateiFn)wglGetProcAddress("glBlendEquationSeparatei");
        boom::glBlendEquationi = (boom::OpenGLBlendEquationiFn)wglGetProcAddress("glBlendEquationi");
        boom::glBlendFunc = (boom::OpenGLBlendFuncFn)wglGetProcAddress("glBlendFunc");
        boom::glBlendFuncSeparate = (boom::OpenGLBlendFuncSeparateFn)wglGetProcAddress("glBlendFuncSeparate");
        boom::glBlendFuncSeparatei = (boom::OpenGLBlendFuncSeparateiFn)wglGetProcAddress("glBlendFuncSeparatei");
        boom::glBlendFunci = (boom::OpenGLBlendFunciFn)wglGetProcAddress("glBlendFunci");
        boom::glBlitFramebuffer = (boom::OpenGLBlitFramebufferFn)wglGetProcAddress("glBlitFramebuffer");
        boom::glBlitNamedFramebuffer = (boom::OpenGLBlitNamedFramebufferFn)wglGetProcAddress("glBlitNamedFramebuffer");
        boom::glBufferData = (boom::OpenGLBufferDataFn)wglGetProcAddress("glBufferData");
        boom::glBufferStorage = (boom::OpenGLBufferStorageFn)wglGetProcAddress("glBufferStorage");
        boom::glBufferSubData = (boom::OpenGLBufferSubDataFn)wglGetProcAddress("glBufferSubData");
        boom::glCallList = (boom::OpenGLCallListFn)wglGetProcAddress("glCallList");
        boom::glCallLists = (boom::OpenGLCallListsFn)wglGetProcAddress("glCallLists");
        boom::glCheckFramebufferStatus = (boom::OpenGLCheckFramebufferStatusFn)wglGetProcAddress("glCheckFramebufferStatus");
        boom::glCheckNamedFramebufferStatus = (boom::OpenGLCheckNamedFramebufferStatusFn)wglGetProcAddress("glCheckNamedFramebufferStatus");
        boom::glClampColor = (boom::OpenGLClampColorFn)wglGetProcAddress("glClampColor");
        boom::glClear = (boom::OpenGLClearFn)wglGetProcAddress("glClear");
        boom::glClearAccum = (boom::OpenGLClearAccumFn)wglGetProcAddress("glClearAccum");
        boom::glClearBufferData = (boom::OpenGLClearBufferDataFn)wglGetProcAddress("glClearBufferData");
        boom::glClearBufferSubData = (boom::OpenGLClearBufferSubDataFn)wglGetProcAddress("glClearBufferSubData");
        boom::glClearBufferfi = (boom::OpenGLClearBufferfiFn)wglGetProcAddress("glClearBufferfi");
        boom::glClearBufferfv = (boom::OpenGLClearBufferfvFn)wglGetProcAddress("glClearBufferfv");
        boom::glClearBufferiv = (boom::OpenGLClearBufferivFn)wglGetProcAddress("glClearBufferiv");
        boom::glClearBufferuiv = (boom::OpenGLClearBufferuivFn)wglGetProcAddress("glClearBufferuiv");
        boom::glClearColor = (boom::OpenGLClearColorFn)wglGetProcAddress("glClearColor");
        boom::glClearColorx = (boom::OpenGLClearColorxFn)wglGetProcAddress("glClearColorx");
        boom::glClearDepth = (boom::OpenGLClearDepthFn)wglGetProcAddress("glClearDepth");
        boom::glClearDepthf = (boom::OpenGLClearDepthfFn)wglGetProcAddress("glClearDepthf");
        boom::glClearDepthx = (boom::OpenGLClearDepthxFn)wglGetProcAddress("glClearDepthx");
        boom::glClearIndex = (boom::OpenGLClearIndexFn)wglGetProcAddress("glClearIndex");
        boom::glClearNamedBufferData = (boom::OpenGLClearNamedBufferDataFn)wglGetProcAddress("glClearNamedBufferData");
        boom::glClearNamedBufferSubData = (boom::OpenGLClearNamedBufferSubDataFn)wglGetProcAddress("glClearNamedBufferSubData");
        boom::glClearNamedFramebufferfi = (boom::OpenGLClearNamedFramebufferfiFn)wglGetProcAddress("glClearNamedFramebufferfi");
        boom::glClearNamedFramebufferfv = (boom::OpenGLClearNamedFramebufferfvFn)wglGetProcAddress("glClearNamedFramebufferfv");
        boom::glClearNamedFramebufferiv = (boom::OpenGLClearNamedFramebufferivFn)wglGetProcAddress("glClearNamedFramebufferiv");
        boom::glClearNamedFramebufferuiv = (boom::OpenGLClearNamedFramebufferuivFn)wglGetProcAddress("glClearNamedFramebufferuiv");
        boom::glClearStencil = (boom::OpenGLClearStencilFn)wglGetProcAddress("glClearStencil");
        boom::glClearTexImage = (boom::OpenGLClearTexImageFn)wglGetProcAddress("glClearTexImage");
        boom::glClearTexSubImage = (boom::OpenGLClearTexSubImageFn)wglGetProcAddress("glClearTexSubImage");
        boom::glClientActiveTexture = (boom::OpenGLClientActiveTextureFn)wglGetProcAddress("glClientActiveTexture");
        boom::glClientWaitSync = (boom::OpenGLClientWaitSyncFn)wglGetProcAddress("glClientWaitSync");
        boom::glClipControl = (boom::OpenGLClipControlFn)wglGetProcAddress("glClipControl");
        boom::glClipPlane = (boom::OpenGLClipPlaneFn)wglGetProcAddress("glClipPlane");
        boom::glClipPlanef = (boom::OpenGLClipPlanefFn)wglGetProcAddress("glClipPlanef");
        boom::glClipPlanex = (boom::OpenGLClipPlanexFn)wglGetProcAddress("glClipPlanex");
        boom::glColor3b = (boom::OpenGLColor3bFn)wglGetProcAddress("glColor3b");
        boom::glColor3bv = (boom::OpenGLColor3bvFn)wglGetProcAddress("glColor3bv");
        boom::glColor3d = (boom::OpenGLColor3dFn)wglGetProcAddress("glColor3d");
        boom::glColor3dv = (boom::OpenGLColor3dvFn)wglGetProcAddress("glColor3dv");
        boom::glColor3f = (boom::OpenGLColor3fFn)wglGetProcAddress("glColor3f");
        boom::glColor3fv = (boom::OpenGLColor3fvFn)wglGetProcAddress("glColor3fv");
        boom::glColor3i = (boom::OpenGLColor3iFn)wglGetProcAddress("glColor3i");
        boom::glColor3iv = (boom::OpenGLColor3ivFn)wglGetProcAddress("glColor3iv");
        boom::glColor3s = (boom::OpenGLColor3sFn)wglGetProcAddress("glColor3s");
        boom::glColor3sv = (boom::OpenGLColor3svFn)wglGetProcAddress("glColor3sv");
        boom::glColor3ub = (boom::OpenGLColor3ubFn)wglGetProcAddress("glColor3ub");
        boom::glColor3ubv = (boom::OpenGLColor3ubvFn)wglGetProcAddress("glColor3ubv");
        boom::glColor3ui = (boom::OpenGLColor3uiFn)wglGetProcAddress("glColor3ui");
        boom::glColor3uiv = (boom::OpenGLColor3uivFn)wglGetProcAddress("glColor3uiv");
        boom::glColor3us = (boom::OpenGLColor3usFn)wglGetProcAddress("glColor3us");
        boom::glColor3usv = (boom::OpenGLColor3usvFn)wglGetProcAddress("glColor3usv");
        boom::glColor4b = (boom::OpenGLColor4bFn)wglGetProcAddress("glColor4b");
        boom::glColor4bv = (boom::OpenGLColor4bvFn)wglGetProcAddress("glColor4bv");
        boom::glColor4d = (boom::OpenGLColor4dFn)wglGetProcAddress("glColor4d");
        boom::glColor4dv = (boom::OpenGLColor4dvFn)wglGetProcAddress("glColor4dv");
        boom::glColor4f = (boom::OpenGLColor4fFn)wglGetProcAddress("glColor4f");
        boom::glColor4fv = (boom::OpenGLColor4fvFn)wglGetProcAddress("glColor4fv");
        boom::glColor4i = (boom::OpenGLColor4iFn)wglGetProcAddress("glColor4i");
        boom::glColor4iv = (boom::OpenGLColor4ivFn)wglGetProcAddress("glColor4iv");
        boom::glColor4s = (boom::OpenGLColor4sFn)wglGetProcAddress("glColor4s");
        boom::glColor4sv = (boom::OpenGLColor4svFn)wglGetProcAddress("glColor4sv");
        boom::glColor4ub = (boom::OpenGLColor4ubFn)wglGetProcAddress("glColor4ub");
        boom::glColor4ubv = (boom::OpenGLColor4ubvFn)wglGetProcAddress("glColor4ubv");
        boom::glColor4ui = (boom::OpenGLColor4uiFn)wglGetProcAddress("glColor4ui");
        boom::glColor4uiv = (boom::OpenGLColor4uivFn)wglGetProcAddress("glColor4uiv");
        boom::glColor4us = (boom::OpenGLColor4usFn)wglGetProcAddress("glColor4us");
        boom::glColor4usv = (boom::OpenGLColor4usvFn)wglGetProcAddress("glColor4usv");
        boom::glColor4x = (boom::OpenGLColor4xFn)wglGetProcAddress("glColor4x");
        boom::glColorMask = (boom::OpenGLColorMaskFn)wglGetProcAddress("glColorMask");
        boom::glColorMaski = (boom::OpenGLColorMaskiFn)wglGetProcAddress("glColorMaski");
        boom::glColorMaterial = (boom::OpenGLColorMaterialFn)wglGetProcAddress("glColorMaterial");
        boom::glColorP3ui = (boom::OpenGLColorP3uiFn)wglGetProcAddress("glColorP3ui");
        boom::glColorP3uiv = (boom::OpenGLColorP3uivFn)wglGetProcAddress("glColorP3uiv");
        boom::glColorP4ui = (boom::OpenGLColorP4uiFn)wglGetProcAddress("glColorP4ui");
        boom::glColorP4uiv = (boom::OpenGLColorP4uivFn)wglGetProcAddress("glColorP4uiv");
        boom::glColorPointer = (boom::OpenGLColorPointerFn)wglGetProcAddress("glColorPointer");
        boom::glCompileShader = (boom::OpenGLCompileShaderFn)wglGetProcAddress("glCompileShader");
        boom::glCompressedTexImage1D = (boom::OpenGLCompressedTexImage1DFn)wglGetProcAddress("glCompressedTexImage1D");
        boom::glCompressedTexImage2D = (boom::OpenGLCompressedTexImage2DFn)wglGetProcAddress("glCompressedTexImage2D");
        boom::glCompressedTexImage3D = (boom::OpenGLCompressedTexImage3DFn)wglGetProcAddress("glCompressedTexImage3D");
        boom::glCompressedTexSubImage1D = (boom::OpenGLCompressedTexSubImage1DFn)wglGetProcAddress("glCompressedTexSubImage1D");
        boom::glCompressedTexSubImage2D = (boom::OpenGLCompressedTexSubImage2DFn)wglGetProcAddress("glCompressedTexSubImage2D");
        boom::glCompressedTexSubImage3D = (boom::OpenGLCompressedTexSubImage3DFn)wglGetProcAddress("glCompressedTexSubImage3D");
        boom::glCompressedTextureSubImage1D = (boom::OpenGLCompressedTextureSubImage1DFn)wglGetProcAddress("glCompressedTextureSubImage1D");
        boom::glCompressedTextureSubImage2D = (boom::OpenGLCompressedTextureSubImage2DFn)wglGetProcAddress("glCompressedTextureSubImage2D");
        boom::glCompressedTextureSubImage3D = (boom::OpenGLCompressedTextureSubImage3DFn)wglGetProcAddress("glCompressedTextureSubImage3D");
        boom::glCopyBufferSubData = (boom::OpenGLCopyBufferSubDataFn)wglGetProcAddress("glCopyBufferSubData");
        boom::glCopyImageSubData = (boom::OpenGLCopyImageSubDataFn)wglGetProcAddress("glCopyImageSubData");
        boom::glCopyNamedBufferSubData = (boom::OpenGLCopyNamedBufferSubDataFn)wglGetProcAddress("glCopyNamedBufferSubData");
        boom::glCopyPixels = (boom::OpenGLCopyPixelsFn)wglGetProcAddress("glCopyPixels");
        boom::glCopyTexImage1D = (boom::OpenGLCopyTexImage1DFn)wglGetProcAddress("glCopyTexImage1D");
        boom::glCopyTexImage2D = (boom::OpenGLCopyTexImage2DFn)wglGetProcAddress("glCopyTexImage2D");
        boom::glCopyTexSubImage1D = (boom::OpenGLCopyTexSubImage1DFn)wglGetProcAddress("glCopyTexSubImage1D");
        boom::glCopyTexSubImage2D = (boom::OpenGLCopyTexSubImage2DFn)wglGetProcAddress("glCopyTexSubImage2D");
        boom::glCopyTexSubImage3D = (boom::OpenGLCopyTexSubImage3DFn)wglGetProcAddress("glCopyTexSubImage3D");
        boom::glCopyTextureSubImage1D = (boom::OpenGLCopyTextureSubImage1DFn)wglGetProcAddress("glCopyTextureSubImage1D");
        boom::glCopyTextureSubImage2D = (boom::OpenGLCopyTextureSubImage2DFn)wglGetProcAddress("glCopyTextureSubImage2D");
        boom::glCopyTextureSubImage3D = (boom::OpenGLCopyTextureSubImage3DFn)wglGetProcAddress("glCopyTextureSubImage3D");
        boom::glCreateBuffers = (boom::OpenGLCreateBuffersFn)wglGetProcAddress("glCreateBuffers");
        boom::glCreateFramebuffers = (boom::OpenGLCreateFramebuffersFn)wglGetProcAddress("glCreateFramebuffers");
        boom::glCreateProgram = (boom::OpenGLCreateProgramFn)wglGetProcAddress("glCreateProgram");
        boom::glCreateProgramPipelines = (boom::OpenGLCreateProgramPipelinesFn)wglGetProcAddress("glCreateProgramPipelines");
        boom::glCreateQueries = (boom::OpenGLCreateQueriesFn)wglGetProcAddress("glCreateQueries");
        boom::glCreateRenderbuffers = (boom::OpenGLCreateRenderbuffersFn)wglGetProcAddress("glCreateRenderbuffers");
        boom::glCreateSamplers = (boom::OpenGLCreateSamplersFn)wglGetProcAddress("glCreateSamplers");
        boom::glCreateShader = (boom::OpenGLCreateShaderFn)wglGetProcAddress("glCreateShader");
        boom::glCreateShaderProgramv = (boom::OpenGLCreateShaderProgramvFn)wglGetProcAddress("glCreateShaderProgramv");
        boom::glCreateTextures = (boom::OpenGLCreateTexturesFn)wglGetProcAddress("glCreateTextures");
        boom::glCreateTransformFeedbacks = (boom::OpenGLCreateTransformFeedbacksFn)wglGetProcAddress("glCreateTransformFeedbacks");
        boom::glCreateVertexArrays = (boom::OpenGLCreateVertexArraysFn)wglGetProcAddress("glCreateVertexArrays");
        boom::glCullFace = (boom::OpenGLCullFaceFn)wglGetProcAddress("glCullFace");
        boom::glDebugMessageCallback = (boom::OpenGLDebugMessageCallbackFn)wglGetProcAddress("glDebugMessageCallback");
        boom::glDebugMessageControl = (boom::OpenGLDebugMessageControlFn)wglGetProcAddress("glDebugMessageControl");
        boom::glDebugMessageInsert = (boom::OpenGLDebugMessageInsertFn)wglGetProcAddress("glDebugMessageInsert");
        boom::glDeleteBuffers = (boom::OpenGLDeleteBuffersFn)wglGetProcAddress("glDeleteBuffers");
        boom::glDeleteFramebuffers = (boom::OpenGLDeleteFramebuffersFn)wglGetProcAddress("glDeleteFramebuffers");
        boom::glDeleteLists = (boom::OpenGLDeleteListsFn)wglGetProcAddress("glDeleteLists");
        boom::glDeleteProgram = (boom::OpenGLDeleteProgramFn)wglGetProcAddress("glDeleteProgram");
        boom::glDeleteProgramPipelines = (boom::OpenGLDeleteProgramPipelinesFn)wglGetProcAddress("glDeleteProgramPipelines");
        boom::glDeleteQueries = (boom::OpenGLDeleteQueriesFn)wglGetProcAddress("glDeleteQueries");
        boom::glDeleteRenderbuffers = (boom::OpenGLDeleteRenderbuffersFn)wglGetProcAddress("glDeleteRenderbuffers");
        boom::glDeleteSamplers = (boom::OpenGLDeleteSamplersFn)wglGetProcAddress("glDeleteSamplers");
        boom::glDeleteShader = (boom::OpenGLDeleteShaderFn)wglGetProcAddress("glDeleteShader");
        boom::glDeleteSync = (boom::OpenGLDeleteSyncFn)wglGetProcAddress("glDeleteSync");
        boom::glDeleteTextures = (boom::OpenGLDeleteTexturesFn)wglGetProcAddress("glDeleteTextures");
        boom::glDeleteTransformFeedbacks = (boom::OpenGLDeleteTransformFeedbacksFn)wglGetProcAddress("glDeleteTransformFeedbacks");
        boom::glDeleteVertexArrays = (boom::OpenGLDeleteVertexArraysFn)wglGetProcAddress("glDeleteVertexArrays");
        boom::glDepthFunc = (boom::OpenGLDepthFuncFn)wglGetProcAddress("glDepthFunc");
        boom::glDepthMask = (boom::OpenGLDepthMaskFn)wglGetProcAddress("glDepthMask");
        boom::glDepthRange = (boom::OpenGLDepthRangeFn)wglGetProcAddress("glDepthRange");
        boom::glDepthRangeArrayv = (boom::OpenGLDepthRangeArrayvFn)wglGetProcAddress("glDepthRangeArrayv");
        boom::glDepthRangeIndexed = (boom::OpenGLDepthRangeIndexedFn)wglGetProcAddress("glDepthRangeIndexed");
        boom::glDepthRangef = (boom::OpenGLDepthRangefFn)wglGetProcAddress("glDepthRangef");
        boom::glDepthRangex = (boom::OpenGLDepthRangexFn)wglGetProcAddress("glDepthRangex");
        boom::glDetachShader = (boom::OpenGLDetachShaderFn)wglGetProcAddress("glDetachShader");
        boom::glDisable = (boom::OpenGLDisableFn)wglGetProcAddress("glDisable");
        boom::glDisableClientState = (boom::OpenGLDisableClientStateFn)wglGetProcAddress("glDisableClientState");
        boom::glDisableVertexArrayAttrib = (boom::OpenGLDisableVertexArrayAttribFn)wglGetProcAddress("glDisableVertexArrayAttrib");
        boom::glDisableVertexAttribArray = (boom::OpenGLDisableVertexAttribArrayFn)wglGetProcAddress("glDisableVertexAttribArray");
        boom::glDisablei = (boom::OpenGLDisableiFn)wglGetProcAddress("glDisablei");
        boom::glDispatchCompute = (boom::OpenGLDispatchComputeFn)wglGetProcAddress("glDispatchCompute");
        boom::glDispatchComputeIndirect = (boom::OpenGLDispatchComputeIndirectFn)wglGetProcAddress("glDispatchComputeIndirect");
        boom::glDrawArrays = (boom::OpenGLDrawArraysFn)wglGetProcAddress("glDrawArrays");
        boom::glDrawArraysIndirect = (boom::OpenGLDrawArraysIndirectFn)wglGetProcAddress("glDrawArraysIndirect");
        boom::glDrawArraysInstanced = (boom::OpenGLDrawArraysInstancedFn)wglGetProcAddress("glDrawArraysInstanced");
        boom::glDrawArraysInstancedBaseInstance = (boom::OpenGLDrawArraysInstancedBaseInstanceFn)wglGetProcAddress("glDrawArraysInstancedBaseInstance");
        boom::glDrawBuffer = (boom::OpenGLDrawBufferFn)wglGetProcAddress("glDrawBuffer");
        boom::glDrawBuffers = (boom::OpenGLDrawBuffersFn)wglGetProcAddress("glDrawBuffers");
        boom::glDrawElements = (boom::OpenGLDrawElementsFn)wglGetProcAddress("glDrawElements");
        boom::glDrawElementsBaseVertex = (boom::OpenGLDrawElementsBaseVertexFn)wglGetProcAddress("glDrawElementsBaseVertex");
        boom::glDrawElementsIndirect = (boom::OpenGLDrawElementsIndirectFn)wglGetProcAddress("glDrawElementsIndirect");
        boom::glDrawElementsInstanced = (boom::OpenGLDrawElementsInstancedFn)wglGetProcAddress("glDrawElementsInstanced");
        boom::glDrawElementsInstancedBaseInstance = (boom::OpenGLDrawElementsInstancedBaseInstanceFn)wglGetProcAddress("glDrawElementsInstancedBaseInstance");
        boom::glDrawElementsInstancedBaseVertex = (boom::OpenGLDrawElementsInstancedBaseVertexFn)wglGetProcAddress("glDrawElementsInstancedBaseVertex");
        boom::glDrawElementsInstancedBaseVertexBaseInstance = (boom::OpenGLDrawElementsInstancedBaseVertexBaseInstanceFn)wglGetProcAddress("glDrawElementsInstancedBaseVertexBaseInstance");
        boom::glDrawPixels = (boom::OpenGLDrawPixelsFn)wglGetProcAddress("glDrawPixels");
        boom::glDrawRangeElements = (boom::OpenGLDrawRangeElementsFn)wglGetProcAddress("glDrawRangeElements");
        boom::glDrawRangeElementsBaseVertex = (boom::OpenGLDrawRangeElementsBaseVertexFn)wglGetProcAddress("glDrawRangeElementsBaseVertex");
        boom::glDrawTransformFeedback = (boom::OpenGLDrawTransformFeedbackFn)wglGetProcAddress("glDrawTransformFeedback");
        boom::glDrawTransformFeedbackInstanced = (boom::OpenGLDrawTransformFeedbackInstancedFn)wglGetProcAddress("glDrawTransformFeedbackInstanced");
        boom::glDrawTransformFeedbackStream = (boom::OpenGLDrawTransformFeedbackStreamFn)wglGetProcAddress("glDrawTransformFeedbackStream");
        boom::glDrawTransformFeedbackStreamInstanced = (boom::OpenGLDrawTransformFeedbackStreamInstancedFn)wglGetProcAddress("glDrawTransformFeedbackStreamInstanced");
        boom::glEdgeFlag = (boom::OpenGLEdgeFlagFn)wglGetProcAddress("glEdgeFlag");
        boom::glEdgeFlagPointer = (boom::OpenGLEdgeFlagPointerFn)wglGetProcAddress("glEdgeFlagPointer");
        boom::glEdgeFlagv = (boom::OpenGLEdgeFlagvFn)wglGetProcAddress("glEdgeFlagv");
        boom::glEnable = (boom::OpenGLEnableFn)wglGetProcAddress("glEnable");
        boom::glEnableClientState = (boom::OpenGLEnableClientStateFn)wglGetProcAddress("glEnableClientState");
        boom::glEnableVertexArrayAttrib = (boom::OpenGLEnableVertexArrayAttribFn)wglGetProcAddress("glEnableVertexArrayAttrib");
        boom::glEnableVertexAttribArray = (boom::OpenGLEnableVertexAttribArrayFn)wglGetProcAddress("glEnableVertexAttribArray");
        boom::glEnablei = (boom::OpenGLEnableiFn)wglGetProcAddress("glEnablei");
        boom::glEnd = (boom::OpenGLEndFn)wglGetProcAddress("glEnd");
        boom::glEndConditionalRender = (boom::OpenGLEndConditionalRenderFn)wglGetProcAddress("glEndConditionalRender");
        boom::glEndList = (boom::OpenGLEndListFn)wglGetProcAddress("glEndList");
        boom::glEndQuery = (boom::OpenGLEndQueryFn)wglGetProcAddress("glEndQuery");
        boom::glEndQueryIndexed = (boom::OpenGLEndQueryIndexedFn)wglGetProcAddress("glEndQueryIndexed");
        boom::glEndTransformFeedback = (boom::OpenGLEndTransformFeedbackFn)wglGetProcAddress("glEndTransformFeedback");
        boom::glEvalCoord1d = (boom::OpenGLEvalCoord1dFn)wglGetProcAddress("glEvalCoord1d");
        boom::glEvalCoord1dv = (boom::OpenGLEvalCoord1dvFn)wglGetProcAddress("glEvalCoord1dv");
        boom::glEvalCoord1f = (boom::OpenGLEvalCoord1fFn)wglGetProcAddress("glEvalCoord1f");
        boom::glEvalCoord1fv = (boom::OpenGLEvalCoord1fvFn)wglGetProcAddress("glEvalCoord1fv");
        boom::glEvalCoord2d = (boom::OpenGLEvalCoord2dFn)wglGetProcAddress("glEvalCoord2d");
        boom::glEvalCoord2dv = (boom::OpenGLEvalCoord2dvFn)wglGetProcAddress("glEvalCoord2dv");
        boom::glEvalCoord2f = (boom::OpenGLEvalCoord2fFn)wglGetProcAddress("glEvalCoord2f");
        boom::glEvalCoord2fv = (boom::OpenGLEvalCoord2fvFn)wglGetProcAddress("glEvalCoord2fv");
        boom::glEvalMesh1 = (boom::OpenGLEvalMesh1Fn)wglGetProcAddress("glEvalMesh1");
        boom::glEvalMesh2 = (boom::OpenGLEvalMesh2Fn)wglGetProcAddress("glEvalMesh2");
        boom::glEvalPoint1 = (boom::OpenGLEvalPoint1Fn)wglGetProcAddress("glEvalPoint1");
        boom::glEvalPoint2 = (boom::OpenGLEvalPoint2Fn)wglGetProcAddress("glEvalPoint2");
        boom::glFeedbackBuffer = (boom::OpenGLFeedbackBufferFn)wglGetProcAddress("glFeedbackBuffer");
        boom::glFenceSync = (boom::OpenGLFenceSyncFn)wglGetProcAddress("glFenceSync");
        boom::glFinish = (boom::OpenGLFinishFn)wglGetProcAddress("glFinish");
        boom::glFlush = (boom::OpenGLFlushFn)wglGetProcAddress("glFlush");
        boom::glFlushMappedBufferRange = (boom::OpenGLFlushMappedBufferRangeFn)wglGetProcAddress("glFlushMappedBufferRange");
        boom::glFlushMappedNamedBufferRange = (boom::OpenGLFlushMappedNamedBufferRangeFn)wglGetProcAddress("glFlushMappedNamedBufferRange");
        boom::glFogCoordPointer = (boom::OpenGLFogCoordPointerFn)wglGetProcAddress("glFogCoordPointer");
        boom::glFogCoordd = (boom::OpenGLFogCoorddFn)wglGetProcAddress("glFogCoordd");
        boom::glFogCoorddv = (boom::OpenGLFogCoorddvFn)wglGetProcAddress("glFogCoorddv");
        boom::glFogCoordf = (boom::OpenGLFogCoordfFn)wglGetProcAddress("glFogCoordf");
        boom::glFogCoordfv = (boom::OpenGLFogCoordfvFn)wglGetProcAddress("glFogCoordfv");
        boom::glFogf = (boom::OpenGLFogfFn)wglGetProcAddress("glFogf");
        boom::glFogfv = (boom::OpenGLFogfvFn)wglGetProcAddress("glFogfv");
        boom::glFogi = (boom::OpenGLFogiFn)wglGetProcAddress("glFogi");
        boom::glFogiv = (boom::OpenGLFogivFn)wglGetProcAddress("glFogiv");
        boom::glFogx = (boom::OpenGLFogxFn)wglGetProcAddress("glFogx");
        boom::glFogxv = (boom::OpenGLFogxvFn)wglGetProcAddress("glFogxv");
        boom::glFramebufferParameteri = (boom::OpenGLFramebufferParameteriFn)wglGetProcAddress("glFramebufferParameteri");
        boom::glFramebufferRenderbuffer = (boom::OpenGLFramebufferRenderbufferFn)wglGetProcAddress("glFramebufferRenderbuffer");
        boom::glFramebufferTexture = (boom::OpenGLFramebufferTextureFn)wglGetProcAddress("glFramebufferTexture");
        boom::glFramebufferTexture1D = (boom::OpenGLFramebufferTexture1DFn)wglGetProcAddress("glFramebufferTexture1D");
        boom::glFramebufferTexture2D = (boom::OpenGLFramebufferTexture2DFn)wglGetProcAddress("glFramebufferTexture2D");
        boom::glFramebufferTexture3D = (boom::OpenGLFramebufferTexture3DFn)wglGetProcAddress("glFramebufferTexture3D");
        boom::glFramebufferTextureLayer = (boom::OpenGLFramebufferTextureLayerFn)wglGetProcAddress("glFramebufferTextureLayer");
        boom::glFrontFace = (boom::OpenGLFrontFaceFn)wglGetProcAddress("glFrontFace");
        boom::glFrustum = (boom::OpenGLFrustumFn)wglGetProcAddress("glFrustum");
        boom::glFrustumf = (boom::OpenGLFrustumfFn)wglGetProcAddress("glFrustumf");
        boom::glFrustumx = (boom::OpenGLFrustumxFn)wglGetProcAddress("glFrustumx");
        boom::glGenBuffers = (boom::OpenGLGenBuffersFn)wglGetProcAddress("glGenBuffers");
        boom::glGenFramebuffers = (boom::OpenGLGenFramebuffersFn)wglGetProcAddress("glGenFramebuffers");
        boom::glGenLists = (boom::OpenGLGenListsFn)wglGetProcAddress("glGenLists");
        boom::glGenProgramPipelines = (boom::OpenGLGenProgramPipelinesFn)wglGetProcAddress("glGenProgramPipelines");
        boom::glGenQueries = (boom::OpenGLGenQueriesFn)wglGetProcAddress("glGenQueries");
        boom::glGenRenderbuffers = (boom::OpenGLGenRenderbuffersFn)wglGetProcAddress("glGenRenderbuffers");
        boom::glGenSamplers = (boom::OpenGLGenSamplersFn)wglGetProcAddress("glGenSamplers");
        boom::glGenTextures = (boom::OpenGLGenTexturesFn)wglGetProcAddress("glGenTextures");
        boom::glGenTransformFeedbacks = (boom::OpenGLGenTransformFeedbacksFn)wglGetProcAddress("glGenTransformFeedbacks");
        boom::glGenVertexArrays = (boom::OpenGLGenVertexArraysFn)wglGetProcAddress("glGenVertexArrays");
        boom::glGenerateMipmap = (boom::OpenGLGenerateMipmapFn)wglGetProcAddress("glGenerateMipmap");
        boom::glGenerateTextureMipmap = (boom::OpenGLGenerateTextureMipmapFn)wglGetProcAddress("glGenerateTextureMipmap");
        boom::glGetActiveAtomicCounterBufferiv = (boom::OpenGLGetActiveAtomicCounterBufferivFn)wglGetProcAddress("glGetActiveAtomicCounterBufferiv");
        boom::glGetActiveAttrib = (boom::OpenGLGetActiveAttribFn)wglGetProcAddress("glGetActiveAttrib");
        boom::glGetActiveSubroutineName = (boom::OpenGLGetActiveSubroutineNameFn)wglGetProcAddress("glGetActiveSubroutineName");
        boom::glGetActiveSubroutineUniformName = (boom::OpenGLGetActiveSubroutineUniformNameFn)wglGetProcAddress("glGetActiveSubroutineUniformName");
        boom::glGetActiveSubroutineUniformiv = (boom::OpenGLGetActiveSubroutineUniformivFn)wglGetProcAddress("glGetActiveSubroutineUniformiv");
        boom::glGetActiveUniform = (boom::OpenGLGetActiveUniformFn)wglGetProcAddress("glGetActiveUniform");
        boom::glGetActiveUniformBlockName = (boom::OpenGLGetActiveUniformBlockNameFn)wglGetProcAddress("glGetActiveUniformBlockName");
        boom::glGetActiveUniformBlockiv = (boom::OpenGLGetActiveUniformBlockivFn)wglGetProcAddress("glGetActiveUniformBlockiv");
        boom::glGetActiveUniformName = (boom::OpenGLGetActiveUniformNameFn)wglGetProcAddress("glGetActiveUniformName");
        boom::glGetActiveUniformsiv = (boom::OpenGLGetActiveUniformsivFn)wglGetProcAddress("glGetActiveUniformsiv");
        boom::glGetAttachedShaders = (boom::OpenGLGetAttachedShadersFn)wglGetProcAddress("glGetAttachedShaders");
        boom::glGetAttribLocation = (boom::OpenGLGetAttribLocationFn)wglGetProcAddress("glGetAttribLocation");
        boom::glGetBooleani_v = (boom::OpenGLGetBooleani_vFn)wglGetProcAddress("glGetBooleani_v");
        boom::glGetBooleanv = (boom::OpenGLGetBooleanvFn)wglGetProcAddress("glGetBooleanv");
        boom::glGetBufferParameteri64v = (boom::OpenGLGetBufferParameteri64vFn)wglGetProcAddress("glGetBufferParameteri64v");
        boom::glGetBufferParameteriv = (boom::OpenGLGetBufferParameterivFn)wglGetProcAddress("glGetBufferParameteriv");
        boom::glGetBufferPointerv = (boom::OpenGLGetBufferPointervFn)wglGetProcAddress("glGetBufferPointerv");
        boom::glGetBufferSubData = (boom::OpenGLGetBufferSubDataFn)wglGetProcAddress("glGetBufferSubData");
        boom::glGetClipPlane = (boom::OpenGLGetClipPlaneFn)wglGetProcAddress("glGetClipPlane");
        boom::glGetClipPlanef = (boom::OpenGLGetClipPlanefFn)wglGetProcAddress("glGetClipPlanef");
        boom::glGetClipPlanex = (boom::OpenGLGetClipPlanexFn)wglGetProcAddress("glGetClipPlanex");
        boom::glGetCompressedTexImage = (boom::OpenGLGetCompressedTexImageFn)wglGetProcAddress("glGetCompressedTexImage");
        boom::glGetCompressedTextureImage = (boom::OpenGLGetCompressedTextureImageFn)wglGetProcAddress("glGetCompressedTextureImage");
        boom::glGetCompressedTextureSubImage = (boom::OpenGLGetCompressedTextureSubImageFn)wglGetProcAddress("glGetCompressedTextureSubImage");
        boom::glGetDebugMessageLog = (boom::OpenGLGetDebugMessageLogFn)wglGetProcAddress("glGetDebugMessageLog");
        boom::glGetDoublei_v = (boom::OpenGLGetDoublei_vFn)wglGetProcAddress("glGetDoublei_v");
        boom::glGetDoublev = (boom::OpenGLGetDoublevFn)wglGetProcAddress("glGetDoublev");
        boom::glGetError = (boom::OpenGLGetErrorFn)wglGetProcAddress("glGetError");
        boom::glGetFixedv = (boom::OpenGLGetFixedvFn)wglGetProcAddress("glGetFixedv");
        boom::glGetFloati_v = (boom::OpenGLGetFloati_vFn)wglGetProcAddress("glGetFloati_v");
        boom::glGetFloatv = (boom::OpenGLGetFloatvFn)wglGetProcAddress("glGetFloatv");
        boom::glGetFragDataIndex = (boom::OpenGLGetFragDataIndexFn)wglGetProcAddress("glGetFragDataIndex");
        boom::glGetFragDataLocation = (boom::OpenGLGetFragDataLocationFn)wglGetProcAddress("glGetFragDataLocation");
        boom::glGetFramebufferAttachmentParameteriv = (boom::OpenGLGetFramebufferAttachmentParameterivFn)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
        boom::glGetFramebufferParameteriv = (boom::OpenGLGetFramebufferParameterivFn)wglGetProcAddress("glGetFramebufferParameteriv");
        boom::glGetGraphicsResetStatus = (boom::OpenGLGetGraphicsResetStatusFn)wglGetProcAddress("glGetGraphicsResetStatus");
        boom::glGetInteger64i_v = (boom::OpenGLGetInteger64i_vFn)wglGetProcAddress("glGetInteger64i_v");
        boom::glGetInteger64v = (boom::OpenGLGetInteger64vFn)wglGetProcAddress("glGetInteger64v");
        boom::glGetIntegeri_v = (boom::OpenGLGetIntegeri_vFn)wglGetProcAddress("glGetIntegeri_v");
        boom::glGetIntegerv = (boom::OpenGLGetIntegervFn)wglGetProcAddress("glGetIntegerv");
        boom::glGetInternalformati64v = (boom::OpenGLGetInternalformati64vFn)wglGetProcAddress("glGetInternalformati64v");
        boom::glGetInternalformativ = (boom::OpenGLGetInternalformativFn)wglGetProcAddress("glGetInternalformativ");
        boom::glGetLightfv = (boom::OpenGLGetLightfvFn)wglGetProcAddress("glGetLightfv");
        boom::glGetLightiv = (boom::OpenGLGetLightivFn)wglGetProcAddress("glGetLightiv");
        boom::glGetLightxv = (boom::OpenGLGetLightxvFn)wglGetProcAddress("glGetLightxv");
        boom::glGetMapdv = (boom::OpenGLGetMapdvFn)wglGetProcAddress("glGetMapdv");
        boom::glGetMapfv = (boom::OpenGLGetMapfvFn)wglGetProcAddress("glGetMapfv");
        boom::glGetMapiv = (boom::OpenGLGetMapivFn)wglGetProcAddress("glGetMapiv");
        boom::glGetMaterialfv = (boom::OpenGLGetMaterialfvFn)wglGetProcAddress("glGetMaterialfv");
        boom::glGetMaterialiv = (boom::OpenGLGetMaterialivFn)wglGetProcAddress("glGetMaterialiv");
        boom::glGetMaterialxv = (boom::OpenGLGetMaterialxvFn)wglGetProcAddress("glGetMaterialxv");
        boom::glGetMultisamplefv = (boom::OpenGLGetMultisamplefvFn)wglGetProcAddress("glGetMultisamplefv");
        boom::glGetNamedBufferParameteri64v = (boom::OpenGLGetNamedBufferParameteri64vFn)wglGetProcAddress("glGetNamedBufferParameteri64v");
        boom::glGetNamedBufferParameteriv = (boom::OpenGLGetNamedBufferParameterivFn)wglGetProcAddress("glGetNamedBufferParameteriv");
        boom::glGetNamedBufferPointerv = (boom::OpenGLGetNamedBufferPointervFn)wglGetProcAddress("glGetNamedBufferPointerv");
        boom::glGetNamedBufferSubData = (boom::OpenGLGetNamedBufferSubDataFn)wglGetProcAddress("glGetNamedBufferSubData");
        boom::glGetNamedFramebufferAttachmentParameteriv = (boom::OpenGLGetNamedFramebufferAttachmentParameterivFn)wglGetProcAddress("glGetNamedFramebufferAttachmentParameteriv");
        boom::glGetNamedFramebufferParameteriv = (boom::OpenGLGetNamedFramebufferParameterivFn)wglGetProcAddress("glGetNamedFramebufferParameteriv");
        boom::glGetNamedRenderbufferParameteriv = (boom::OpenGLGetNamedRenderbufferParameterivFn)wglGetProcAddress("glGetNamedRenderbufferParameteriv");
        boom::glGetObjectLabel = (boom::OpenGLGetObjectLabelFn)wglGetProcAddress("glGetObjectLabel");
        boom::glGetObjectPtrLabel = (boom::OpenGLGetObjectPtrLabelFn)wglGetProcAddress("glGetObjectPtrLabel");
        boom::glGetPixelMapfv = (boom::OpenGLGetPixelMapfvFn)wglGetProcAddress("glGetPixelMapfv");
        boom::glGetPixelMapuiv = (boom::OpenGLGetPixelMapuivFn)wglGetProcAddress("glGetPixelMapuiv");
        boom::glGetPixelMapusv = (boom::OpenGLGetPixelMapusvFn)wglGetProcAddress("glGetPixelMapusv");
        boom::glGetPointerv = (boom::OpenGLGetPointervFn)wglGetProcAddress("glGetPointerv");
        boom::glGetPolygonStipple = (boom::OpenGLGetPolygonStippleFn)wglGetProcAddress("glGetPolygonStipple");
        boom::glGetProgramBinary = (boom::OpenGLGetProgramBinaryFn)wglGetProcAddress("glGetProgramBinary");
        boom::glGetProgramInfoLog = (boom::OpenGLGetProgramInfoLogFn)wglGetProcAddress("glGetProgramInfoLog");
        boom::glGetProgramInterfaceiv = (boom::OpenGLGetProgramInterfaceivFn)wglGetProcAddress("glGetProgramInterfaceiv");
        boom::glGetProgramPipelineInfoLog = (boom::OpenGLGetProgramPipelineInfoLogFn)wglGetProcAddress("glGetProgramPipelineInfoLog");
        boom::glGetProgramPipelineiv = (boom::OpenGLGetProgramPipelineivFn)wglGetProcAddress("glGetProgramPipelineiv");
        boom::glGetProgramResourceIndex = (boom::OpenGLGetProgramResourceIndexFn)wglGetProcAddress("glGetProgramResourceIndex");
        boom::glGetProgramResourceLocation = (boom::OpenGLGetProgramResourceLocationFn)wglGetProcAddress("glGetProgramResourceLocation");
        boom::glGetProgramResourceLocationIndex = (boom::OpenGLGetProgramResourceLocationIndexFn)wglGetProcAddress("glGetProgramResourceLocationIndex");
        boom::glGetProgramResourceName = (boom::OpenGLGetProgramResourceNameFn)wglGetProcAddress("glGetProgramResourceName");
        boom::glGetProgramResourceiv = (boom::OpenGLGetProgramResourceivFn)wglGetProcAddress("glGetProgramResourceiv");
        boom::glGetProgramStageiv = (boom::OpenGLGetProgramStageivFn)wglGetProcAddress("glGetProgramStageiv");
        boom::glGetProgramiv = (boom::OpenGLGetProgramivFn)wglGetProcAddress("glGetProgramiv");
        boom::glGetQueryBufferObjecti64v = (boom::OpenGLGetQueryBufferObjecti64vFn)wglGetProcAddress("glGetQueryBufferObjecti64v");
        boom::glGetQueryBufferObjectiv = (boom::OpenGLGetQueryBufferObjectivFn)wglGetProcAddress("glGetQueryBufferObjectiv");
        boom::glGetQueryBufferObjectui64v = (boom::OpenGLGetQueryBufferObjectui64vFn)wglGetProcAddress("glGetQueryBufferObjectui64v");
        boom::glGetQueryBufferObjectuiv = (boom::OpenGLGetQueryBufferObjectuivFn)wglGetProcAddress("glGetQueryBufferObjectuiv");
        boom::glGetQueryIndexediv = (boom::OpenGLGetQueryIndexedivFn)wglGetProcAddress("glGetQueryIndexediv");
        boom::glGetQueryObjecti64v = (boom::OpenGLGetQueryObjecti64vFn)wglGetProcAddress("glGetQueryObjecti64v");
        boom::glGetQueryObjectiv = (boom::OpenGLGetQueryObjectivFn)wglGetProcAddress("glGetQueryObjectiv");
        boom::glGetQueryObjectui64v = (boom::OpenGLGetQueryObjectui64vFn)wglGetProcAddress("glGetQueryObjectui64v");
        boom::glGetQueryObjectuiv = (boom::OpenGLGetQueryObjectuivFn)wglGetProcAddress("glGetQueryObjectuiv");
        boom::glGetQueryiv = (boom::OpenGLGetQueryivFn)wglGetProcAddress("glGetQueryiv");
        boom::glGetRenderbufferParameteriv = (boom::OpenGLGetRenderbufferParameterivFn)wglGetProcAddress("glGetRenderbufferParameteriv");
        boom::glGetSamplerParameterIiv = (boom::OpenGLGetSamplerParameterIivFn)wglGetProcAddress("glGetSamplerParameterIiv");
        boom::glGetSamplerParameterIuiv = (boom::OpenGLGetSamplerParameterIuivFn)wglGetProcAddress("glGetSamplerParameterIuiv");
        boom::glGetSamplerParameterfv = (boom::OpenGLGetSamplerParameterfvFn)wglGetProcAddress("glGetSamplerParameterfv");
        boom::glGetSamplerParameteriv = (boom::OpenGLGetSamplerParameterivFn)wglGetProcAddress("glGetSamplerParameteriv");
        boom::glGetShaderInfoLog = (boom::OpenGLGetShaderInfoLogFn)wglGetProcAddress("glGetShaderInfoLog");
        boom::glGetShaderPrecisionFormat = (boom::OpenGLGetShaderPrecisionFormatFn)wglGetProcAddress("glGetShaderPrecisionFormat");
        boom::glGetShaderSource = (boom::OpenGLGetShaderSourceFn)wglGetProcAddress("glGetShaderSource");
        boom::glGetShaderiv = (boom::OpenGLGetShaderivFn)wglGetProcAddress("glGetShaderiv");
        boom::glGetString = (boom::OpenGLGetStringFn)wglGetProcAddress("glGetString");
        boom::glGetStringi = (boom::OpenGLGetStringiFn)wglGetProcAddress("glGetStringi");
        boom::glGetSubroutineIndex = (boom::OpenGLGetSubroutineIndexFn)wglGetProcAddress("glGetSubroutineIndex");
        boom::glGetSubroutineUniformLocation = (boom::OpenGLGetSubroutineUniformLocationFn)wglGetProcAddress("glGetSubroutineUniformLocation");
        boom::glGetSynciv = (boom::OpenGLGetSyncivFn)wglGetProcAddress("glGetSynciv");
        boom::glGetTexEnvfv = (boom::OpenGLGetTexEnvfvFn)wglGetProcAddress("glGetTexEnvfv");
        boom::glGetTexEnviv = (boom::OpenGLGetTexEnvivFn)wglGetProcAddress("glGetTexEnviv");
        boom::glGetTexEnvxv = (boom::OpenGLGetTexEnvxvFn)wglGetProcAddress("glGetTexEnvxv");
        boom::glGetTexGendv = (boom::OpenGLGetTexGendvFn)wglGetProcAddress("glGetTexGendv");
        boom::glGetTexGenfv = (boom::OpenGLGetTexGenfvFn)wglGetProcAddress("glGetTexGenfv");
        boom::glGetTexGeniv = (boom::OpenGLGetTexGenivFn)wglGetProcAddress("glGetTexGeniv");
        boom::glGetTexImage = (boom::OpenGLGetTexImageFn)wglGetProcAddress("glGetTexImage");
        boom::glGetTexLevelParameterfv = (boom::OpenGLGetTexLevelParameterfvFn)wglGetProcAddress("glGetTexLevelParameterfv");
        boom::glGetTexLevelParameteriv = (boom::OpenGLGetTexLevelParameterivFn)wglGetProcAddress("glGetTexLevelParameteriv");
        boom::glGetTexParameterIiv = (boom::OpenGLGetTexParameterIivFn)wglGetProcAddress("glGetTexParameterIiv");
        boom::glGetTexParameterIuiv = (boom::OpenGLGetTexParameterIuivFn)wglGetProcAddress("glGetTexParameterIuiv");
        boom::glGetTexParameterfv = (boom::OpenGLGetTexParameterfvFn)wglGetProcAddress("glGetTexParameterfv");
        boom::glGetTexParameteriv = (boom::OpenGLGetTexParameterivFn)wglGetProcAddress("glGetTexParameteriv");
        boom::glGetTexParameterxv = (boom::OpenGLGetTexParameterxvFn)wglGetProcAddress("glGetTexParameterxv");
        boom::glGetTextureImage = (boom::OpenGLGetTextureImageFn)wglGetProcAddress("glGetTextureImage");
        boom::glGetTextureLevelParameterfv = (boom::OpenGLGetTextureLevelParameterfvFn)wglGetProcAddress("glGetTextureLevelParameterfv");
        boom::glGetTextureLevelParameteriv = (boom::OpenGLGetTextureLevelParameterivFn)wglGetProcAddress("glGetTextureLevelParameteriv");
        boom::glGetTextureParameterIiv = (boom::OpenGLGetTextureParameterIivFn)wglGetProcAddress("glGetTextureParameterIiv");
        boom::glGetTextureParameterIuiv = (boom::OpenGLGetTextureParameterIuivFn)wglGetProcAddress("glGetTextureParameterIuiv");
        boom::glGetTextureParameterfv = (boom::OpenGLGetTextureParameterfvFn)wglGetProcAddress("glGetTextureParameterfv");
        boom::glGetTextureParameteriv = (boom::OpenGLGetTextureParameterivFn)wglGetProcAddress("glGetTextureParameteriv");
        boom::glGetTextureSubImage = (boom::OpenGLGetTextureSubImageFn)wglGetProcAddress("glGetTextureSubImage");
        boom::glGetTransformFeedbackVarying = (boom::OpenGLGetTransformFeedbackVaryingFn)wglGetProcAddress("glGetTransformFeedbackVarying");
        boom::glGetTransformFeedbacki64_v = (boom::OpenGLGetTransformFeedbacki64_vFn)wglGetProcAddress("glGetTransformFeedbacki64_v");
        boom::glGetTransformFeedbacki_v = (boom::OpenGLGetTransformFeedbacki_vFn)wglGetProcAddress("glGetTransformFeedbacki_v");
        boom::glGetTransformFeedbackiv = (boom::OpenGLGetTransformFeedbackivFn)wglGetProcAddress("glGetTransformFeedbackiv");
        boom::glGetUniformBlockIndex = (boom::OpenGLGetUniformBlockIndexFn)wglGetProcAddress("glGetUniformBlockIndex");
        boom::glGetUniformIndices = (boom::OpenGLGetUniformIndicesFn)wglGetProcAddress("glGetUniformIndices");
        boom::glGetUniformLocation = (boom::OpenGLGetUniformLocationFn)wglGetProcAddress("glGetUniformLocation");
        boom::glGetUniformSubroutineuiv = (boom::OpenGLGetUniformSubroutineuivFn)wglGetProcAddress("glGetUniformSubroutineuiv");
        boom::glGetUniformdv = (boom::OpenGLGetUniformdvFn)wglGetProcAddress("glGetUniformdv");
        boom::glGetUniformfv = (boom::OpenGLGetUniformfvFn)wglGetProcAddress("glGetUniformfv");
        boom::glGetUniformiv = (boom::OpenGLGetUniformivFn)wglGetProcAddress("glGetUniformiv");
        boom::glGetUniformuiv = (boom::OpenGLGetUniformuivFn)wglGetProcAddress("glGetUniformuiv");
        boom::glGetVertexArrayIndexed64iv = (boom::OpenGLGetVertexArrayIndexed64ivFn)wglGetProcAddress("glGetVertexArrayIndexed64iv");
        boom::glGetVertexArrayIndexediv = (boom::OpenGLGetVertexArrayIndexedivFn)wglGetProcAddress("glGetVertexArrayIndexediv");
        boom::glGetVertexArrayiv = (boom::OpenGLGetVertexArrayivFn)wglGetProcAddress("glGetVertexArrayiv");
        boom::glGetVertexAttribIiv = (boom::OpenGLGetVertexAttribIivFn)wglGetProcAddress("glGetVertexAttribIiv");
        boom::glGetVertexAttribIuiv = (boom::OpenGLGetVertexAttribIuivFn)wglGetProcAddress("glGetVertexAttribIuiv");
        boom::glGetVertexAttribLdv = (boom::OpenGLGetVertexAttribLdvFn)wglGetProcAddress("glGetVertexAttribLdv");
        boom::glGetVertexAttribPointerv = (boom::OpenGLGetVertexAttribPointervFn)wglGetProcAddress("glGetVertexAttribPointerv");
        boom::glGetVertexAttribdv = (boom::OpenGLGetVertexAttribdvFn)wglGetProcAddress("glGetVertexAttribdv");
        boom::glGetVertexAttribfv = (boom::OpenGLGetVertexAttribfvFn)wglGetProcAddress("glGetVertexAttribfv");
        boom::glGetVertexAttribiv = (boom::OpenGLGetVertexAttribivFn)wglGetProcAddress("glGetVertexAttribiv");
        boom::glGetnColorTable = (boom::OpenGLGetnColorTableFn)wglGetProcAddress("glGetnColorTable");
        boom::glGetnCompressedTexImage = (boom::OpenGLGetnCompressedTexImageFn)wglGetProcAddress("glGetnCompressedTexImage");
        boom::glGetnConvolutionFilter = (boom::OpenGLGetnConvolutionFilterFn)wglGetProcAddress("glGetnConvolutionFilter");
        boom::glGetnHistogram = (boom::OpenGLGetnHistogramFn)wglGetProcAddress("glGetnHistogram");
        boom::glGetnMapdv = (boom::OpenGLGetnMapdvFn)wglGetProcAddress("glGetnMapdv");
        boom::glGetnMapfv = (boom::OpenGLGetnMapfvFn)wglGetProcAddress("glGetnMapfv");
        boom::glGetnMapiv = (boom::OpenGLGetnMapivFn)wglGetProcAddress("glGetnMapiv");
        boom::glGetnMinmax = (boom::OpenGLGetnMinmaxFn)wglGetProcAddress("glGetnMinmax");
        boom::glGetnPixelMapfv = (boom::OpenGLGetnPixelMapfvFn)wglGetProcAddress("glGetnPixelMapfv");
        boom::glGetnPixelMapuiv = (boom::OpenGLGetnPixelMapuivFn)wglGetProcAddress("glGetnPixelMapuiv");
        boom::glGetnPixelMapusv = (boom::OpenGLGetnPixelMapusvFn)wglGetProcAddress("glGetnPixelMapusv");
        boom::glGetnPolygonStipple = (boom::OpenGLGetnPolygonStippleFn)wglGetProcAddress("glGetnPolygonStipple");
        boom::glGetnSeparableFilter = (boom::OpenGLGetnSeparableFilterFn)wglGetProcAddress("glGetnSeparableFilter");
        boom::glGetnTexImage = (boom::OpenGLGetnTexImageFn)wglGetProcAddress("glGetnTexImage");
        boom::glGetnUniformdv = (boom::OpenGLGetnUniformdvFn)wglGetProcAddress("glGetnUniformdv");
        boom::glGetnUniformfv = (boom::OpenGLGetnUniformfvFn)wglGetProcAddress("glGetnUniformfv");
        boom::glGetnUniformiv = (boom::OpenGLGetnUniformivFn)wglGetProcAddress("glGetnUniformiv");
        boom::glGetnUniformuiv = (boom::OpenGLGetnUniformuivFn)wglGetProcAddress("glGetnUniformuiv");
        boom::glHint = (boom::OpenGLHintFn)wglGetProcAddress("glHint");
        boom::glIndexMask = (boom::OpenGLIndexMaskFn)wglGetProcAddress("glIndexMask");
        boom::glIndexPointer = (boom::OpenGLIndexPointerFn)wglGetProcAddress("glIndexPointer");
        boom::glIndexd = (boom::OpenGLIndexdFn)wglGetProcAddress("glIndexd");
        boom::glIndexdv = (boom::OpenGLIndexdvFn)wglGetProcAddress("glIndexdv");
        boom::glIndexf = (boom::OpenGLIndexfFn)wglGetProcAddress("glIndexf");
        boom::glIndexfv = (boom::OpenGLIndexfvFn)wglGetProcAddress("glIndexfv");
        boom::glIndexi = (boom::OpenGLIndexiFn)wglGetProcAddress("glIndexi");
        boom::glIndexiv = (boom::OpenGLIndexivFn)wglGetProcAddress("glIndexiv");
        boom::glIndexs = (boom::OpenGLIndexsFn)wglGetProcAddress("glIndexs");
        boom::glIndexsv = (boom::OpenGLIndexsvFn)wglGetProcAddress("glIndexsv");
        boom::glIndexub = (boom::OpenGLIndexubFn)wglGetProcAddress("glIndexub");
        boom::glIndexubv = (boom::OpenGLIndexubvFn)wglGetProcAddress("glIndexubv");
        boom::glInitNames = (boom::OpenGLInitNamesFn)wglGetProcAddress("glInitNames");
        boom::glInterleavedArrays = (boom::OpenGLInterleavedArraysFn)wglGetProcAddress("glInterleavedArrays");
        boom::glInvalidateBufferData = (boom::OpenGLInvalidateBufferDataFn)wglGetProcAddress("glInvalidateBufferData");
        boom::glInvalidateBufferSubData = (boom::OpenGLInvalidateBufferSubDataFn)wglGetProcAddress("glInvalidateBufferSubData");
        boom::glInvalidateFramebuffer = (boom::OpenGLInvalidateFramebufferFn)wglGetProcAddress("glInvalidateFramebuffer");
        boom::glInvalidateNamedFramebufferData = (boom::OpenGLInvalidateNamedFramebufferDataFn)wglGetProcAddress("glInvalidateNamedFramebufferData");
        boom::glInvalidateNamedFramebufferSubData = (boom::OpenGLInvalidateNamedFramebufferSubDataFn)wglGetProcAddress("glInvalidateNamedFramebufferSubData");
        boom::glInvalidateSubFramebuffer = (boom::OpenGLInvalidateSubFramebufferFn)wglGetProcAddress("glInvalidateSubFramebuffer");
        boom::glInvalidateTexImage = (boom::OpenGLInvalidateTexImageFn)wglGetProcAddress("glInvalidateTexImage");
        boom::glInvalidateTexSubImage = (boom::OpenGLInvalidateTexSubImageFn)wglGetProcAddress("glInvalidateTexSubImage");
        boom::glIsBuffer = (boom::OpenGLIsBufferFn)wglGetProcAddress("glIsBuffer");
        boom::glIsEnabled = (boom::OpenGLIsEnabledFn)wglGetProcAddress("glIsEnabled");
        boom::glIsEnabledi = (boom::OpenGLIsEnablediFn)wglGetProcAddress("glIsEnabledi");
        boom::glIsFramebuffer = (boom::OpenGLIsFramebufferFn)wglGetProcAddress("glIsFramebuffer");
        boom::glIsList = (boom::OpenGLIsListFn)wglGetProcAddress("glIsList");
        boom::glIsProgram = (boom::OpenGLIsProgramFn)wglGetProcAddress("glIsProgram");
        boom::glIsProgramPipeline = (boom::OpenGLIsProgramPipelineFn)wglGetProcAddress("glIsProgramPipeline");
        boom::glIsQuery = (boom::OpenGLIsQueryFn)wglGetProcAddress("glIsQuery");
        boom::glIsRenderbuffer = (boom::OpenGLIsRenderbufferFn)wglGetProcAddress("glIsRenderbuffer");
        boom::glIsSampler = (boom::OpenGLIsSamplerFn)wglGetProcAddress("glIsSampler");
        boom::glIsShader = (boom::OpenGLIsShaderFn)wglGetProcAddress("glIsShader");
        boom::glIsSync = (boom::OpenGLIsSyncFn)wglGetProcAddress("glIsSync");
        boom::glIsTexture = (boom::OpenGLIsTextureFn)wglGetProcAddress("glIsTexture");
        boom::glIsTransformFeedback = (boom::OpenGLIsTransformFeedbackFn)wglGetProcAddress("glIsTransformFeedback");
        boom::glIsVertexArray = (boom::OpenGLIsVertexArrayFn)wglGetProcAddress("glIsVertexArray");
        boom::glLightModelf = (boom::OpenGLLightModelfFn)wglGetProcAddress("glLightModelf");
        boom::glLightModelfv = (boom::OpenGLLightModelfvFn)wglGetProcAddress("glLightModelfv");
        boom::glLightModeli = (boom::OpenGLLightModeliFn)wglGetProcAddress("glLightModeli");
        boom::glLightModeliv = (boom::OpenGLLightModelivFn)wglGetProcAddress("glLightModeliv");
        boom::glLightModelx = (boom::OpenGLLightModelxFn)wglGetProcAddress("glLightModelx");
        boom::glLightModelxv = (boom::OpenGLLightModelxvFn)wglGetProcAddress("glLightModelxv");
        boom::glLightf = (boom::OpenGLLightfFn)wglGetProcAddress("glLightf");
        boom::glLightfv = (boom::OpenGLLightfvFn)wglGetProcAddress("glLightfv");
        boom::glLighti = (boom::OpenGLLightiFn)wglGetProcAddress("glLighti");
        boom::glLightiv = (boom::OpenGLLightivFn)wglGetProcAddress("glLightiv");
        boom::glLightx = (boom::OpenGLLightxFn)wglGetProcAddress("glLightx");
        boom::glLightxv = (boom::OpenGLLightxvFn)wglGetProcAddress("glLightxv");
        boom::glLineStipple = (boom::OpenGLLineStippleFn)wglGetProcAddress("glLineStipple");
        boom::glLineWidth = (boom::OpenGLLineWidthFn)wglGetProcAddress("glLineWidth");
        boom::glLineWidthx = (boom::OpenGLLineWidthxFn)wglGetProcAddress("glLineWidthx");
        boom::glLinkProgram = (boom::OpenGLLinkProgramFn)wglGetProcAddress("glLinkProgram");
        boom::glListBase = (boom::OpenGLListBaseFn)wglGetProcAddress("glListBase");
        boom::glLoadIdentity = (boom::OpenGLLoadIdentityFn)wglGetProcAddress("glLoadIdentity");
        boom::glLoadMatrixd = (boom::OpenGLLoadMatrixdFn)wglGetProcAddress("glLoadMatrixd");
        boom::glLoadMatrixf = (boom::OpenGLLoadMatrixfFn)wglGetProcAddress("glLoadMatrixf");
        boom::glLoadMatrixx = (boom::OpenGLLoadMatrixxFn)wglGetProcAddress("glLoadMatrixx");
        boom::glLoadName = (boom::OpenGLLoadNameFn)wglGetProcAddress("glLoadName");
        boom::glLoadTransposeMatrixd = (boom::OpenGLLoadTransposeMatrixdFn)wglGetProcAddress("glLoadTransposeMatrixd");
        boom::glLoadTransposeMatrixf = (boom::OpenGLLoadTransposeMatrixfFn)wglGetProcAddress("glLoadTransposeMatrixf");
        boom::glLogicOp = (boom::OpenGLLogicOpFn)wglGetProcAddress("glLogicOp");
        boom::glMap1d = (boom::OpenGLMap1dFn)wglGetProcAddress("glMap1d");
        boom::glMap1f = (boom::OpenGLMap1fFn)wglGetProcAddress("glMap1f");
        boom::glMap2d = (boom::OpenGLMap2dFn)wglGetProcAddress("glMap2d");
        boom::glMap2f = (boom::OpenGLMap2fFn)wglGetProcAddress("glMap2f");
        boom::glMapBuffer = (boom::OpenGLMapBufferFn)wglGetProcAddress("glMapBuffer");
        boom::glMapBufferRange = (boom::OpenGLMapBufferRangeFn)wglGetProcAddress("glMapBufferRange");
        boom::glMapGrid1d = (boom::OpenGLMapGrid1dFn)wglGetProcAddress("glMapGrid1d");
        boom::glMapGrid1f = (boom::OpenGLMapGrid1fFn)wglGetProcAddress("glMapGrid1f");
        boom::glMapGrid2d = (boom::OpenGLMapGrid2dFn)wglGetProcAddress("glMapGrid2d");
        boom::glMapGrid2f = (boom::OpenGLMapGrid2fFn)wglGetProcAddress("glMapGrid2f");
        boom::glMapNamedBuffer = (boom::OpenGLMapNamedBufferFn)wglGetProcAddress("glMapNamedBuffer");
        boom::glMapNamedBufferRange = (boom::OpenGLMapNamedBufferRangeFn)wglGetProcAddress("glMapNamedBufferRange");
        boom::glMaterialf = (boom::OpenGLMaterialfFn)wglGetProcAddress("glMaterialf");
        boom::glMaterialfv = (boom::OpenGLMaterialfvFn)wglGetProcAddress("glMaterialfv");
        boom::glMateriali = (boom::OpenGLMaterialiFn)wglGetProcAddress("glMateriali");
        boom::glMaterialiv = (boom::OpenGLMaterialivFn)wglGetProcAddress("glMaterialiv");
        boom::glMaterialx = (boom::OpenGLMaterialxFn)wglGetProcAddress("glMaterialx");
        boom::glMaterialxv = (boom::OpenGLMaterialxvFn)wglGetProcAddress("glMaterialxv");
        boom::glMatrixMode = (boom::OpenGLMatrixModeFn)wglGetProcAddress("glMatrixMode");
        boom::glMemoryBarrier = (boom::OpenGLMemoryBarrierFn)wglGetProcAddress("glMemoryBarrier");
        boom::glMemoryBarrierByRegion = (boom::OpenGLMemoryBarrierByRegionFn)wglGetProcAddress("glMemoryBarrierByRegion");
        boom::glMinSampleShading = (boom::OpenGLMinSampleShadingFn)wglGetProcAddress("glMinSampleShading");
        boom::glMultMatrixd = (boom::OpenGLMultMatrixdFn)wglGetProcAddress("glMultMatrixd");
        boom::glMultMatrixf = (boom::OpenGLMultMatrixfFn)wglGetProcAddress("glMultMatrixf");
        boom::glMultMatrixx = (boom::OpenGLMultMatrixxFn)wglGetProcAddress("glMultMatrixx");
        boom::glMultTransposeMatrixd = (boom::OpenGLMultTransposeMatrixdFn)wglGetProcAddress("glMultTransposeMatrixd");
        boom::glMultTransposeMatrixf = (boom::OpenGLMultTransposeMatrixfFn)wglGetProcAddress("glMultTransposeMatrixf");
        boom::glMultiDrawArrays = (boom::OpenGLMultiDrawArraysFn)wglGetProcAddress("glMultiDrawArrays");
        boom::glMultiDrawArraysIndirect = (boom::OpenGLMultiDrawArraysIndirectFn)wglGetProcAddress("glMultiDrawArraysIndirect");
        boom::glMultiDrawArraysIndirectCount = (boom::OpenGLMultiDrawArraysIndirectCountFn)wglGetProcAddress("glMultiDrawArraysIndirectCount");
        boom::glMultiDrawElements = (boom::OpenGLMultiDrawElementsFn)wglGetProcAddress("glMultiDrawElements");
        boom::glMultiDrawElementsBaseVertex = (boom::OpenGLMultiDrawElementsBaseVertexFn)wglGetProcAddress("glMultiDrawElementsBaseVertex");
        boom::glMultiDrawElementsIndirect = (boom::OpenGLMultiDrawElementsIndirectFn)wglGetProcAddress("glMultiDrawElementsIndirect");
        boom::glMultiDrawElementsIndirectCount = (boom::OpenGLMultiDrawElementsIndirectCountFn)wglGetProcAddress("glMultiDrawElementsIndirectCount");
        boom::glMultiTexCoord1d = (boom::OpenGLMultiTexCoord1dFn)wglGetProcAddress("glMultiTexCoord1d");
        boom::glMultiTexCoord1dv = (boom::OpenGLMultiTexCoord1dvFn)wglGetProcAddress("glMultiTexCoord1dv");
        boom::glMultiTexCoord1f = (boom::OpenGLMultiTexCoord1fFn)wglGetProcAddress("glMultiTexCoord1f");
        boom::glMultiTexCoord1fv = (boom::OpenGLMultiTexCoord1fvFn)wglGetProcAddress("glMultiTexCoord1fv");
        boom::glMultiTexCoord1i = (boom::OpenGLMultiTexCoord1iFn)wglGetProcAddress("glMultiTexCoord1i");
        boom::glMultiTexCoord1iv = (boom::OpenGLMultiTexCoord1ivFn)wglGetProcAddress("glMultiTexCoord1iv");
        boom::glMultiTexCoord1s = (boom::OpenGLMultiTexCoord1sFn)wglGetProcAddress("glMultiTexCoord1s");
        boom::glMultiTexCoord1sv = (boom::OpenGLMultiTexCoord1svFn)wglGetProcAddress("glMultiTexCoord1sv");
        boom::glMultiTexCoord2d = (boom::OpenGLMultiTexCoord2dFn)wglGetProcAddress("glMultiTexCoord2d");
        boom::glMultiTexCoord2dv = (boom::OpenGLMultiTexCoord2dvFn)wglGetProcAddress("glMultiTexCoord2dv");
        boom::glMultiTexCoord2f = (boom::OpenGLMultiTexCoord2fFn)wglGetProcAddress("glMultiTexCoord2f");
        boom::glMultiTexCoord2fv = (boom::OpenGLMultiTexCoord2fvFn)wglGetProcAddress("glMultiTexCoord2fv");
        boom::glMultiTexCoord2i = (boom::OpenGLMultiTexCoord2iFn)wglGetProcAddress("glMultiTexCoord2i");
        boom::glMultiTexCoord2iv = (boom::OpenGLMultiTexCoord2ivFn)wglGetProcAddress("glMultiTexCoord2iv");
        boom::glMultiTexCoord2s = (boom::OpenGLMultiTexCoord2sFn)wglGetProcAddress("glMultiTexCoord2s");
        boom::glMultiTexCoord2sv = (boom::OpenGLMultiTexCoord2svFn)wglGetProcAddress("glMultiTexCoord2sv");
        boom::glMultiTexCoord3d = (boom::OpenGLMultiTexCoord3dFn)wglGetProcAddress("glMultiTexCoord3d");
        boom::glMultiTexCoord3dv = (boom::OpenGLMultiTexCoord3dvFn)wglGetProcAddress("glMultiTexCoord3dv");
        boom::glMultiTexCoord3f = (boom::OpenGLMultiTexCoord3fFn)wglGetProcAddress("glMultiTexCoord3f");
        boom::glMultiTexCoord3fv = (boom::OpenGLMultiTexCoord3fvFn)wglGetProcAddress("glMultiTexCoord3fv");
        boom::glMultiTexCoord3i = (boom::OpenGLMultiTexCoord3iFn)wglGetProcAddress("glMultiTexCoord3i");
        boom::glMultiTexCoord3iv = (boom::OpenGLMultiTexCoord3ivFn)wglGetProcAddress("glMultiTexCoord3iv");
        boom::glMultiTexCoord3s = (boom::OpenGLMultiTexCoord3sFn)wglGetProcAddress("glMultiTexCoord3s");
        boom::glMultiTexCoord3sv = (boom::OpenGLMultiTexCoord3svFn)wglGetProcAddress("glMultiTexCoord3sv");
        boom::glMultiTexCoord4d = (boom::OpenGLMultiTexCoord4dFn)wglGetProcAddress("glMultiTexCoord4d");
        boom::glMultiTexCoord4dv = (boom::OpenGLMultiTexCoord4dvFn)wglGetProcAddress("glMultiTexCoord4dv");
        boom::glMultiTexCoord4f = (boom::OpenGLMultiTexCoord4fFn)wglGetProcAddress("glMultiTexCoord4f");
        boom::glMultiTexCoord4fv = (boom::OpenGLMultiTexCoord4fvFn)wglGetProcAddress("glMultiTexCoord4fv");
        boom::glMultiTexCoord4i = (boom::OpenGLMultiTexCoord4iFn)wglGetProcAddress("glMultiTexCoord4i");
        boom::glMultiTexCoord4iv = (boom::OpenGLMultiTexCoord4ivFn)wglGetProcAddress("glMultiTexCoord4iv");
        boom::glMultiTexCoord4s = (boom::OpenGLMultiTexCoord4sFn)wglGetProcAddress("glMultiTexCoord4s");
        boom::glMultiTexCoord4sv = (boom::OpenGLMultiTexCoord4svFn)wglGetProcAddress("glMultiTexCoord4sv");
        boom::glMultiTexCoord4x = (boom::OpenGLMultiTexCoord4xFn)wglGetProcAddress("glMultiTexCoord4x");
        boom::glMultiTexCoordP1ui = (boom::OpenGLMultiTexCoordP1uiFn)wglGetProcAddress("glMultiTexCoordP1ui");
        boom::glMultiTexCoordP1uiv = (boom::OpenGLMultiTexCoordP1uivFn)wglGetProcAddress("glMultiTexCoordP1uiv");
        boom::glMultiTexCoordP2ui = (boom::OpenGLMultiTexCoordP2uiFn)wglGetProcAddress("glMultiTexCoordP2ui");
        boom::glMultiTexCoordP2uiv = (boom::OpenGLMultiTexCoordP2uivFn)wglGetProcAddress("glMultiTexCoordP2uiv");
        boom::glMultiTexCoordP3ui = (boom::OpenGLMultiTexCoordP3uiFn)wglGetProcAddress("glMultiTexCoordP3ui");
        boom::glMultiTexCoordP3uiv = (boom::OpenGLMultiTexCoordP3uivFn)wglGetProcAddress("glMultiTexCoordP3uiv");
        boom::glMultiTexCoordP4ui = (boom::OpenGLMultiTexCoordP4uiFn)wglGetProcAddress("glMultiTexCoordP4ui");
        boom::glMultiTexCoordP4uiv = (boom::OpenGLMultiTexCoordP4uivFn)wglGetProcAddress("glMultiTexCoordP4uiv");
        boom::glNamedBufferData = (boom::OpenGLNamedBufferDataFn)wglGetProcAddress("glNamedBufferData");
        boom::glNamedBufferStorage = (boom::OpenGLNamedBufferStorageFn)wglGetProcAddress("glNamedBufferStorage");
        boom::glNamedBufferSubData = (boom::OpenGLNamedBufferSubDataFn)wglGetProcAddress("glNamedBufferSubData");
        boom::glNamedFramebufferDrawBuffer = (boom::OpenGLNamedFramebufferDrawBufferFn)wglGetProcAddress("glNamedFramebufferDrawBuffer");
        boom::glNamedFramebufferDrawBuffers = (boom::OpenGLNamedFramebufferDrawBuffersFn)wglGetProcAddress("glNamedFramebufferDrawBuffers");
        boom::glNamedFramebufferParameteri = (boom::OpenGLNamedFramebufferParameteriFn)wglGetProcAddress("glNamedFramebufferParameteri");
        boom::glNamedFramebufferReadBuffer = (boom::OpenGLNamedFramebufferReadBufferFn)wglGetProcAddress("glNamedFramebufferReadBuffer");
        boom::glNamedFramebufferRenderbuffer = (boom::OpenGLNamedFramebufferRenderbufferFn)wglGetProcAddress("glNamedFramebufferRenderbuffer");
        boom::glNamedFramebufferTexture = (boom::OpenGLNamedFramebufferTextureFn)wglGetProcAddress("glNamedFramebufferTexture");
        boom::glNamedFramebufferTextureLayer = (boom::OpenGLNamedFramebufferTextureLayerFn)wglGetProcAddress("glNamedFramebufferTextureLayer");
        boom::glNamedRenderbufferStorage = (boom::OpenGLNamedRenderbufferStorageFn)wglGetProcAddress("glNamedRenderbufferStorage");
        boom::glNamedRenderbufferStorageMultisample = (boom::OpenGLNamedRenderbufferStorageMultisampleFn)wglGetProcAddress("glNamedRenderbufferStorageMultisample");
        boom::glNewList = (boom::OpenGLNewListFn)wglGetProcAddress("glNewList");
        boom::glNormal3b = (boom::OpenGLNormal3bFn)wglGetProcAddress("glNormal3b");
        boom::glNormal3bv = (boom::OpenGLNormal3bvFn)wglGetProcAddress("glNormal3bv");
        boom::glNormal3d = (boom::OpenGLNormal3dFn)wglGetProcAddress("glNormal3d");
        boom::glNormal3dv = (boom::OpenGLNormal3dvFn)wglGetProcAddress("glNormal3dv");
        boom::glNormal3f = (boom::OpenGLNormal3fFn)wglGetProcAddress("glNormal3f");
        boom::glNormal3fv = (boom::OpenGLNormal3fvFn)wglGetProcAddress("glNormal3fv");
        boom::glNormal3i = (boom::OpenGLNormal3iFn)wglGetProcAddress("glNormal3i");
        boom::glNormal3iv = (boom::OpenGLNormal3ivFn)wglGetProcAddress("glNormal3iv");
        boom::glNormal3s = (boom::OpenGLNormal3sFn)wglGetProcAddress("glNormal3s");
        boom::glNormal3sv = (boom::OpenGLNormal3svFn)wglGetProcAddress("glNormal3sv");
        boom::glNormal3x = (boom::OpenGLNormal3xFn)wglGetProcAddress("glNormal3x");
        boom::glNormalP3ui = (boom::OpenGLNormalP3uiFn)wglGetProcAddress("glNormalP3ui");
        boom::glNormalP3uiv = (boom::OpenGLNormalP3uivFn)wglGetProcAddress("glNormalP3uiv");
        boom::glNormalPointer = (boom::OpenGLNormalPointerFn)wglGetProcAddress("glNormalPointer");
        boom::glObjectLabel = (boom::OpenGLObjectLabelFn)wglGetProcAddress("glObjectLabel");
        boom::glObjectPtrLabel = (boom::OpenGLObjectPtrLabelFn)wglGetProcAddress("glObjectPtrLabel");
        boom::glOrtho = (boom::OpenGLOrthoFn)wglGetProcAddress("glOrtho");
        boom::glOrthof = (boom::OpenGLOrthofFn)wglGetProcAddress("glOrthof");
        boom::glOrthox = (boom::OpenGLOrthoxFn)wglGetProcAddress("glOrthox");
        boom::glPassThrough = (boom::OpenGLPassThroughFn)wglGetProcAddress("glPassThrough");
        boom::glPatchParameterfv = (boom::OpenGLPatchParameterfvFn)wglGetProcAddress("glPatchParameterfv");
        boom::glPatchParameteri = (boom::OpenGLPatchParameteriFn)wglGetProcAddress("glPatchParameteri");
        boom::glPauseTransformFeedback = (boom::OpenGLPauseTransformFeedbackFn)wglGetProcAddress("glPauseTransformFeedback");
        boom::glPixelMapfv = (boom::OpenGLPixelMapfvFn)wglGetProcAddress("glPixelMapfv");
        boom::glPixelMapuiv = (boom::OpenGLPixelMapuivFn)wglGetProcAddress("glPixelMapuiv");
        boom::glPixelMapusv = (boom::OpenGLPixelMapusvFn)wglGetProcAddress("glPixelMapusv");
        boom::glPixelStoref = (boom::OpenGLPixelStorefFn)wglGetProcAddress("glPixelStoref");
        boom::glPixelStorei = (boom::OpenGLPixelStoreiFn)wglGetProcAddress("glPixelStorei");
        boom::glPixelTransferf = (boom::OpenGLPixelTransferfFn)wglGetProcAddress("glPixelTransferf");
        boom::glPixelTransferi = (boom::OpenGLPixelTransferiFn)wglGetProcAddress("glPixelTransferi");
        boom::glPixelZoom = (boom::OpenGLPixelZoomFn)wglGetProcAddress("glPixelZoom");
        boom::glPointParameterf = (boom::OpenGLPointParameterfFn)wglGetProcAddress("glPointParameterf");
        boom::glPointParameterfv = (boom::OpenGLPointParameterfvFn)wglGetProcAddress("glPointParameterfv");
        boom::glPointParameteri = (boom::OpenGLPointParameteriFn)wglGetProcAddress("glPointParameteri");
        boom::glPointParameteriv = (boom::OpenGLPointParameterivFn)wglGetProcAddress("glPointParameteriv");
        boom::glPointParameterx = (boom::OpenGLPointParameterxFn)wglGetProcAddress("glPointParameterx");
        boom::glPointParameterxv = (boom::OpenGLPointParameterxvFn)wglGetProcAddress("glPointParameterxv");
        boom::glPointSize = (boom::OpenGLPointSizeFn)wglGetProcAddress("glPointSize");
        boom::glPointSizex = (boom::OpenGLPointSizexFn)wglGetProcAddress("glPointSizex");
        boom::glPolygonMode = (boom::OpenGLPolygonModeFn)wglGetProcAddress("glPolygonMode");
        boom::glPolygonOffset = (boom::OpenGLPolygonOffsetFn)wglGetProcAddress("glPolygonOffset");
        boom::glPolygonOffsetClamp = (boom::OpenGLPolygonOffsetClampFn)wglGetProcAddress("glPolygonOffsetClamp");
        boom::glPolygonOffsetx = (boom::OpenGLPolygonOffsetxFn)wglGetProcAddress("glPolygonOffsetx");
        boom::glPolygonStipple = (boom::OpenGLPolygonStippleFn)wglGetProcAddress("glPolygonStipple");
        boom::glPopAttrib = (boom::OpenGLPopAttribFn)wglGetProcAddress("glPopAttrib");
        boom::glPopClientAttrib = (boom::OpenGLPopClientAttribFn)wglGetProcAddress("glPopClientAttrib");
        boom::glPopDebugGroup = (boom::OpenGLPopDebugGroupFn)wglGetProcAddress("glPopDebugGroup");
        boom::glPopMatrix = (boom::OpenGLPopMatrixFn)wglGetProcAddress("glPopMatrix");
        boom::glPopName = (boom::OpenGLPopNameFn)wglGetProcAddress("glPopName");
        boom::glPrimitiveBoundingBox = (boom::OpenGLPrimitiveBoundingBoxFn)wglGetProcAddress("glPrimitiveBoundingBox");
        boom::glPrimitiveRestartIndex = (boom::OpenGLPrimitiveRestartIndexFn)wglGetProcAddress("glPrimitiveRestartIndex");
        boom::glPrioritizeTextures = (boom::OpenGLPrioritizeTexturesFn)wglGetProcAddress("glPrioritizeTextures");
        boom::glProgramBinary = (boom::OpenGLProgramBinaryFn)wglGetProcAddress("glProgramBinary");
        boom::glProgramParameteri = (boom::OpenGLProgramParameteriFn)wglGetProcAddress("glProgramParameteri");
        boom::glProgramUniform1d = (boom::OpenGLProgramUniform1dFn)wglGetProcAddress("glProgramUniform1d");
        boom::glProgramUniform1dv = (boom::OpenGLProgramUniform1dvFn)wglGetProcAddress("glProgramUniform1dv");
        boom::glProgramUniform1f = (boom::OpenGLProgramUniform1fFn)wglGetProcAddress("glProgramUniform1f");
        boom::glProgramUniform1fv = (boom::OpenGLProgramUniform1fvFn)wglGetProcAddress("glProgramUniform1fv");
        boom::glProgramUniform1i = (boom::OpenGLProgramUniform1iFn)wglGetProcAddress("glProgramUniform1i");
        boom::glProgramUniform1iv = (boom::OpenGLProgramUniform1ivFn)wglGetProcAddress("glProgramUniform1iv");
        boom::glProgramUniform1ui = (boom::OpenGLProgramUniform1uiFn)wglGetProcAddress("glProgramUniform1ui");
        boom::glProgramUniform1uiv = (boom::OpenGLProgramUniform1uivFn)wglGetProcAddress("glProgramUniform1uiv");
        boom::glProgramUniform2d = (boom::OpenGLProgramUniform2dFn)wglGetProcAddress("glProgramUniform2d");
        boom::glProgramUniform2dv = (boom::OpenGLProgramUniform2dvFn)wglGetProcAddress("glProgramUniform2dv");
        boom::glProgramUniform2f = (boom::OpenGLProgramUniform2fFn)wglGetProcAddress("glProgramUniform2f");
        boom::glProgramUniform2fv = (boom::OpenGLProgramUniform2fvFn)wglGetProcAddress("glProgramUniform2fv");
        boom::glProgramUniform2i = (boom::OpenGLProgramUniform2iFn)wglGetProcAddress("glProgramUniform2i");
        boom::glProgramUniform2iv = (boom::OpenGLProgramUniform2ivFn)wglGetProcAddress("glProgramUniform2iv");
        boom::glProgramUniform2ui = (boom::OpenGLProgramUniform2uiFn)wglGetProcAddress("glProgramUniform2ui");
        boom::glProgramUniform2uiv = (boom::OpenGLProgramUniform2uivFn)wglGetProcAddress("glProgramUniform2uiv");
        boom::glProgramUniform3d = (boom::OpenGLProgramUniform3dFn)wglGetProcAddress("glProgramUniform3d");
        boom::glProgramUniform3dv = (boom::OpenGLProgramUniform3dvFn)wglGetProcAddress("glProgramUniform3dv");
        boom::glProgramUniform3f = (boom::OpenGLProgramUniform3fFn)wglGetProcAddress("glProgramUniform3f");
        boom::glProgramUniform3fv = (boom::OpenGLProgramUniform3fvFn)wglGetProcAddress("glProgramUniform3fv");
        boom::glProgramUniform3i = (boom::OpenGLProgramUniform3iFn)wglGetProcAddress("glProgramUniform3i");
        boom::glProgramUniform3iv = (boom::OpenGLProgramUniform3ivFn)wglGetProcAddress("glProgramUniform3iv");
        boom::glProgramUniform3ui = (boom::OpenGLProgramUniform3uiFn)wglGetProcAddress("glProgramUniform3ui");
        boom::glProgramUniform3uiv = (boom::OpenGLProgramUniform3uivFn)wglGetProcAddress("glProgramUniform3uiv");
        boom::glProgramUniform4d = (boom::OpenGLProgramUniform4dFn)wglGetProcAddress("glProgramUniform4d");
        boom::glProgramUniform4dv = (boom::OpenGLProgramUniform4dvFn)wglGetProcAddress("glProgramUniform4dv");
        boom::glProgramUniform4f = (boom::OpenGLProgramUniform4fFn)wglGetProcAddress("glProgramUniform4f");
        boom::glProgramUniform4fv = (boom::OpenGLProgramUniform4fvFn)wglGetProcAddress("glProgramUniform4fv");
        boom::glProgramUniform4i = (boom::OpenGLProgramUniform4iFn)wglGetProcAddress("glProgramUniform4i");
        boom::glProgramUniform4iv = (boom::OpenGLProgramUniform4ivFn)wglGetProcAddress("glProgramUniform4iv");
        boom::glProgramUniform4ui = (boom::OpenGLProgramUniform4uiFn)wglGetProcAddress("glProgramUniform4ui");
        boom::glProgramUniform4uiv = (boom::OpenGLProgramUniform4uivFn)wglGetProcAddress("glProgramUniform4uiv");
        boom::glProgramUniformMatrix2dv = (boom::OpenGLProgramUniformMatrix2dvFn)wglGetProcAddress("glProgramUniformMatrix2dv");
        boom::glProgramUniformMatrix2fv = (boom::OpenGLProgramUniformMatrix2fvFn)wglGetProcAddress("glProgramUniformMatrix2fv");
        boom::glProgramUniformMatrix2x3dv = (boom::OpenGLProgramUniformMatrix2x3dvFn)wglGetProcAddress("glProgramUniformMatrix2x3dv");
        boom::glProgramUniformMatrix2x3fv = (boom::OpenGLProgramUniformMatrix2x3fvFn)wglGetProcAddress("glProgramUniformMatrix2x3fv");
        boom::glProgramUniformMatrix2x4dv = (boom::OpenGLProgramUniformMatrix2x4dvFn)wglGetProcAddress("glProgramUniformMatrix2x4dv");
        boom::glProgramUniformMatrix2x4fv = (boom::OpenGLProgramUniformMatrix2x4fvFn)wglGetProcAddress("glProgramUniformMatrix2x4fv");
        boom::glProgramUniformMatrix3dv = (boom::OpenGLProgramUniformMatrix3dvFn)wglGetProcAddress("glProgramUniformMatrix3dv");
        boom::glProgramUniformMatrix3fv = (boom::OpenGLProgramUniformMatrix3fvFn)wglGetProcAddress("glProgramUniformMatrix3fv");
        boom::glProgramUniformMatrix3x2dv = (boom::OpenGLProgramUniformMatrix3x2dvFn)wglGetProcAddress("glProgramUniformMatrix3x2dv");
        boom::glProgramUniformMatrix3x2fv = (boom::OpenGLProgramUniformMatrix3x2fvFn)wglGetProcAddress("glProgramUniformMatrix3x2fv");
        boom::glProgramUniformMatrix3x4dv = (boom::OpenGLProgramUniformMatrix3x4dvFn)wglGetProcAddress("glProgramUniformMatrix3x4dv");
        boom::glProgramUniformMatrix3x4fv = (boom::OpenGLProgramUniformMatrix3x4fvFn)wglGetProcAddress("glProgramUniformMatrix3x4fv");
        boom::glProgramUniformMatrix4dv = (boom::OpenGLProgramUniformMatrix4dvFn)wglGetProcAddress("glProgramUniformMatrix4dv");
        boom::glProgramUniformMatrix4fv = (boom::OpenGLProgramUniformMatrix4fvFn)wglGetProcAddress("glProgramUniformMatrix4fv");
        boom::glProgramUniformMatrix4x2dv = (boom::OpenGLProgramUniformMatrix4x2dvFn)wglGetProcAddress("glProgramUniformMatrix4x2dv");
        boom::glProgramUniformMatrix4x2fv = (boom::OpenGLProgramUniformMatrix4x2fvFn)wglGetProcAddress("glProgramUniformMatrix4x2fv");
        boom::glProgramUniformMatrix4x3dv = (boom::OpenGLProgramUniformMatrix4x3dvFn)wglGetProcAddress("glProgramUniformMatrix4x3dv");
        boom::glProgramUniformMatrix4x3fv = (boom::OpenGLProgramUniformMatrix4x3fvFn)wglGetProcAddress("glProgramUniformMatrix4x3fv");
        boom::glProvokingVertex = (boom::OpenGLProvokingVertexFn)wglGetProcAddress("glProvokingVertex");
        boom::glPushAttrib = (boom::OpenGLPushAttribFn)wglGetProcAddress("glPushAttrib");
        boom::glPushClientAttrib = (boom::OpenGLPushClientAttribFn)wglGetProcAddress("glPushClientAttrib");
        boom::glPushDebugGroup = (boom::OpenGLPushDebugGroupFn)wglGetProcAddress("glPushDebugGroup");
        boom::glPushMatrix = (boom::OpenGLPushMatrixFn)wglGetProcAddress("glPushMatrix");
        boom::glPushName = (boom::OpenGLPushNameFn)wglGetProcAddress("glPushName");
        boom::glQueryCounter = (boom::OpenGLQueryCounterFn)wglGetProcAddress("glQueryCounter");
        boom::glRasterPos2d = (boom::OpenGLRasterPos2dFn)wglGetProcAddress("glRasterPos2d");
        boom::glRasterPos2dv = (boom::OpenGLRasterPos2dvFn)wglGetProcAddress("glRasterPos2dv");
        boom::glRasterPos2f = (boom::OpenGLRasterPos2fFn)wglGetProcAddress("glRasterPos2f");
        boom::glRasterPos2fv = (boom::OpenGLRasterPos2fvFn)wglGetProcAddress("glRasterPos2fv");
        boom::glRasterPos2i = (boom::OpenGLRasterPos2iFn)wglGetProcAddress("glRasterPos2i");
        boom::glRasterPos2iv = (boom::OpenGLRasterPos2ivFn)wglGetProcAddress("glRasterPos2iv");
        boom::glRasterPos2s = (boom::OpenGLRasterPos2sFn)wglGetProcAddress("glRasterPos2s");
        boom::glRasterPos2sv = (boom::OpenGLRasterPos2svFn)wglGetProcAddress("glRasterPos2sv");
        boom::glRasterPos3d = (boom::OpenGLRasterPos3dFn)wglGetProcAddress("glRasterPos3d");
        boom::glRasterPos3dv = (boom::OpenGLRasterPos3dvFn)wglGetProcAddress("glRasterPos3dv");
        boom::glRasterPos3f = (boom::OpenGLRasterPos3fFn)wglGetProcAddress("glRasterPos3f");
        boom::glRasterPos3fv = (boom::OpenGLRasterPos3fvFn)wglGetProcAddress("glRasterPos3fv");
        boom::glRasterPos3i = (boom::OpenGLRasterPos3iFn)wglGetProcAddress("glRasterPos3i");
        boom::glRasterPos3iv = (boom::OpenGLRasterPos3ivFn)wglGetProcAddress("glRasterPos3iv");
        boom::glRasterPos3s = (boom::OpenGLRasterPos3sFn)wglGetProcAddress("glRasterPos3s");
        boom::glRasterPos3sv = (boom::OpenGLRasterPos3svFn)wglGetProcAddress("glRasterPos3sv");
        boom::glRasterPos4d = (boom::OpenGLRasterPos4dFn)wglGetProcAddress("glRasterPos4d");
        boom::glRasterPos4dv = (boom::OpenGLRasterPos4dvFn)wglGetProcAddress("glRasterPos4dv");
        boom::glRasterPos4f = (boom::OpenGLRasterPos4fFn)wglGetProcAddress("glRasterPos4f");
        boom::glRasterPos4fv = (boom::OpenGLRasterPos4fvFn)wglGetProcAddress("glRasterPos4fv");
        boom::glRasterPos4i = (boom::OpenGLRasterPos4iFn)wglGetProcAddress("glRasterPos4i");
        boom::glRasterPos4iv = (boom::OpenGLRasterPos4ivFn)wglGetProcAddress("glRasterPos4iv");
        boom::glRasterPos4s = (boom::OpenGLRasterPos4sFn)wglGetProcAddress("glRasterPos4s");
        boom::glRasterPos4sv = (boom::OpenGLRasterPos4svFn)wglGetProcAddress("glRasterPos4sv");
        boom::glReadBuffer = (boom::OpenGLReadBufferFn)wglGetProcAddress("glReadBuffer");
        boom::glReadPixels = (boom::OpenGLReadPixelsFn)wglGetProcAddress("glReadPixels");
        boom::glReadnPixels = (boom::OpenGLReadnPixelsFn)wglGetProcAddress("glReadnPixels");
        boom::glRectd = (boom::OpenGLRectdFn)wglGetProcAddress("glRectd");
        boom::glRectdv = (boom::OpenGLRectdvFn)wglGetProcAddress("glRectdv");
        boom::glRectf = (boom::OpenGLRectfFn)wglGetProcAddress("glRectf");
        boom::glRectfv = (boom::OpenGLRectfvFn)wglGetProcAddress("glRectfv");
        boom::glRecti = (boom::OpenGLRectiFn)wglGetProcAddress("glRecti");
        boom::glRectiv = (boom::OpenGLRectivFn)wglGetProcAddress("glRectiv");
        boom::glRects = (boom::OpenGLRectsFn)wglGetProcAddress("glRects");
        boom::glRectsv = (boom::OpenGLRectsvFn)wglGetProcAddress("glRectsv");
        boom::glReleaseShaderCompiler = (boom::OpenGLReleaseShaderCompilerFn)wglGetProcAddress("glReleaseShaderCompiler");
        boom::glRenderMode = (boom::OpenGLRenderModeFn)wglGetProcAddress("glRenderMode");
        boom::glRenderbufferStorage = (boom::OpenGLRenderbufferStorageFn)wglGetProcAddress("glRenderbufferStorage");
        boom::glRenderbufferStorageMultisample = (boom::OpenGLRenderbufferStorageMultisampleFn)wglGetProcAddress("glRenderbufferStorageMultisample");
        boom::glResumeTransformFeedback = (boom::OpenGLResumeTransformFeedbackFn)wglGetProcAddress("glResumeTransformFeedback");
        boom::glRotated = (boom::OpenGLRotatedFn)wglGetProcAddress("glRotated");
        boom::glRotatef = (boom::OpenGLRotatefFn)wglGetProcAddress("glRotatef");
        boom::glRotatex = (boom::OpenGLRotatexFn)wglGetProcAddress("glRotatex");
        boom::glSampleCoverage = (boom::OpenGLSampleCoverageFn)wglGetProcAddress("glSampleCoverage");
        boom::glSampleCoveragex = (boom::OpenGLSampleCoveragexFn)wglGetProcAddress("glSampleCoveragex");
        boom::glSampleMaski = (boom::OpenGLSampleMaskiFn)wglGetProcAddress("glSampleMaski");
        boom::glSamplerParameterIiv = (boom::OpenGLSamplerParameterIivFn)wglGetProcAddress("glSamplerParameterIiv");
        boom::glSamplerParameterIuiv = (boom::OpenGLSamplerParameterIuivFn)wglGetProcAddress("glSamplerParameterIuiv");
        boom::glSamplerParameterf = (boom::OpenGLSamplerParameterfFn)wglGetProcAddress("glSamplerParameterf");
        boom::glSamplerParameterfv = (boom::OpenGLSamplerParameterfvFn)wglGetProcAddress("glSamplerParameterfv");
        boom::glSamplerParameteri = (boom::OpenGLSamplerParameteriFn)wglGetProcAddress("glSamplerParameteri");
        boom::glSamplerParameteriv = (boom::OpenGLSamplerParameterivFn)wglGetProcAddress("glSamplerParameteriv");
        boom::glScaled = (boom::OpenGLScaledFn)wglGetProcAddress("glScaled");
        boom::glScalef = (boom::OpenGLScalefFn)wglGetProcAddress("glScalef");
        boom::glScalex = (boom::OpenGLScalexFn)wglGetProcAddress("glScalex");
        boom::glScissor = (boom::OpenGLScissorFn)wglGetProcAddress("glScissor");
        boom::glScissorArrayv = (boom::OpenGLScissorArrayvFn)wglGetProcAddress("glScissorArrayv");
        boom::glScissorIndexed = (boom::OpenGLScissorIndexedFn)wglGetProcAddress("glScissorIndexed");
        boom::glScissorIndexedv = (boom::OpenGLScissorIndexedvFn)wglGetProcAddress("glScissorIndexedv");
        boom::glSecondaryColor3b = (boom::OpenGLSecondaryColor3bFn)wglGetProcAddress("glSecondaryColor3b");
        boom::glSecondaryColor3bv = (boom::OpenGLSecondaryColor3bvFn)wglGetProcAddress("glSecondaryColor3bv");
        boom::glSecondaryColor3d = (boom::OpenGLSecondaryColor3dFn)wglGetProcAddress("glSecondaryColor3d");
        boom::glSecondaryColor3dv = (boom::OpenGLSecondaryColor3dvFn)wglGetProcAddress("glSecondaryColor3dv");
        boom::glSecondaryColor3f = (boom::OpenGLSecondaryColor3fFn)wglGetProcAddress("glSecondaryColor3f");
        boom::glSecondaryColor3fv = (boom::OpenGLSecondaryColor3fvFn)wglGetProcAddress("glSecondaryColor3fv");
        boom::glSecondaryColor3i = (boom::OpenGLSecondaryColor3iFn)wglGetProcAddress("glSecondaryColor3i");
        boom::glSecondaryColor3iv = (boom::OpenGLSecondaryColor3ivFn)wglGetProcAddress("glSecondaryColor3iv");
        boom::glSecondaryColor3s = (boom::OpenGLSecondaryColor3sFn)wglGetProcAddress("glSecondaryColor3s");
        boom::glSecondaryColor3sv = (boom::OpenGLSecondaryColor3svFn)wglGetProcAddress("glSecondaryColor3sv");
        boom::glSecondaryColor3ub = (boom::OpenGLSecondaryColor3ubFn)wglGetProcAddress("glSecondaryColor3ub");
        boom::glSecondaryColor3ubv = (boom::OpenGLSecondaryColor3ubvFn)wglGetProcAddress("glSecondaryColor3ubv");
        boom::glSecondaryColor3ui = (boom::OpenGLSecondaryColor3uiFn)wglGetProcAddress("glSecondaryColor3ui");
        boom::glSecondaryColor3uiv = (boom::OpenGLSecondaryColor3uivFn)wglGetProcAddress("glSecondaryColor3uiv");
        boom::glSecondaryColor3us = (boom::OpenGLSecondaryColor3usFn)wglGetProcAddress("glSecondaryColor3us");
        boom::glSecondaryColor3usv = (boom::OpenGLSecondaryColor3usvFn)wglGetProcAddress("glSecondaryColor3usv");
        boom::glSecondaryColorP3ui = (boom::OpenGLSecondaryColorP3uiFn)wglGetProcAddress("glSecondaryColorP3ui");
        boom::glSecondaryColorP3uiv = (boom::OpenGLSecondaryColorP3uivFn)wglGetProcAddress("glSecondaryColorP3uiv");
        boom::glSecondaryColorPointer = (boom::OpenGLSecondaryColorPointerFn)wglGetProcAddress("glSecondaryColorPointer");
        boom::glSelectBuffer = (boom::OpenGLSelectBufferFn)wglGetProcAddress("glSelectBuffer");
        boom::glShadeModel = (boom::OpenGLShadeModelFn)wglGetProcAddress("glShadeModel");
        boom::glShaderBinary = (boom::OpenGLShaderBinaryFn)wglGetProcAddress("glShaderBinary");
        boom::glShaderSource = (boom::OpenGLShaderSourceFn)wglGetProcAddress("glShaderSource");
        boom::glShaderStorageBlockBinding = (boom::OpenGLShaderStorageBlockBindingFn)wglGetProcAddress("glShaderStorageBlockBinding");
        boom::glSpecializeShader = (boom::OpenGLSpecializeShaderFn)wglGetProcAddress("glSpecializeShader");
        boom::glStencilFunc = (boom::OpenGLStencilFuncFn)wglGetProcAddress("glStencilFunc");
        boom::glStencilFuncSeparate = (boom::OpenGLStencilFuncSeparateFn)wglGetProcAddress("glStencilFuncSeparate");
        boom::glStencilMask = (boom::OpenGLStencilMaskFn)wglGetProcAddress("glStencilMask");
        boom::glStencilMaskSeparate = (boom::OpenGLStencilMaskSeparateFn)wglGetProcAddress("glStencilMaskSeparate");
        boom::glStencilOp = (boom::OpenGLStencilOpFn)wglGetProcAddress("glStencilOp");
        boom::glStencilOpSeparate = (boom::OpenGLStencilOpSeparateFn)wglGetProcAddress("glStencilOpSeparate");
        boom::glTexBuffer = (boom::OpenGLTexBufferFn)wglGetProcAddress("glTexBuffer");
        boom::glTexBufferRange = (boom::OpenGLTexBufferRangeFn)wglGetProcAddress("glTexBufferRange");
        boom::glTexCoord1d = (boom::OpenGLTexCoord1dFn)wglGetProcAddress("glTexCoord1d");
        boom::glTexCoord1dv = (boom::OpenGLTexCoord1dvFn)wglGetProcAddress("glTexCoord1dv");
        boom::glTexCoord1f = (boom::OpenGLTexCoord1fFn)wglGetProcAddress("glTexCoord1f");
        boom::glTexCoord1fv = (boom::OpenGLTexCoord1fvFn)wglGetProcAddress("glTexCoord1fv");
        boom::glTexCoord1i = (boom::OpenGLTexCoord1iFn)wglGetProcAddress("glTexCoord1i");
        boom::glTexCoord1iv = (boom::OpenGLTexCoord1ivFn)wglGetProcAddress("glTexCoord1iv");
        boom::glTexCoord1s = (boom::OpenGLTexCoord1sFn)wglGetProcAddress("glTexCoord1s");
        boom::glTexCoord1sv = (boom::OpenGLTexCoord1svFn)wglGetProcAddress("glTexCoord1sv");
        boom::glTexCoord2d = (boom::OpenGLTexCoord2dFn)wglGetProcAddress("glTexCoord2d");
        boom::glTexCoord2dv = (boom::OpenGLTexCoord2dvFn)wglGetProcAddress("glTexCoord2dv");
        boom::glTexCoord2f = (boom::OpenGLTexCoord2fFn)wglGetProcAddress("glTexCoord2f");
        boom::glTexCoord2fv = (boom::OpenGLTexCoord2fvFn)wglGetProcAddress("glTexCoord2fv");
        boom::glTexCoord2i = (boom::OpenGLTexCoord2iFn)wglGetProcAddress("glTexCoord2i");
        boom::glTexCoord2iv = (boom::OpenGLTexCoord2ivFn)wglGetProcAddress("glTexCoord2iv");
        boom::glTexCoord2s = (boom::OpenGLTexCoord2sFn)wglGetProcAddress("glTexCoord2s");
        boom::glTexCoord2sv = (boom::OpenGLTexCoord2svFn)wglGetProcAddress("glTexCoord2sv");
        boom::glTexCoord3d = (boom::OpenGLTexCoord3dFn)wglGetProcAddress("glTexCoord3d");
        boom::glTexCoord3dv = (boom::OpenGLTexCoord3dvFn)wglGetProcAddress("glTexCoord3dv");
        boom::glTexCoord3f = (boom::OpenGLTexCoord3fFn)wglGetProcAddress("glTexCoord3f");
        boom::glTexCoord3fv = (boom::OpenGLTexCoord3fvFn)wglGetProcAddress("glTexCoord3fv");
        boom::glTexCoord3i = (boom::OpenGLTexCoord3iFn)wglGetProcAddress("glTexCoord3i");
        boom::glTexCoord3iv = (boom::OpenGLTexCoord3ivFn)wglGetProcAddress("glTexCoord3iv");
        boom::glTexCoord3s = (boom::OpenGLTexCoord3sFn)wglGetProcAddress("glTexCoord3s");
        boom::glTexCoord3sv = (boom::OpenGLTexCoord3svFn)wglGetProcAddress("glTexCoord3sv");
        boom::glTexCoord4d = (boom::OpenGLTexCoord4dFn)wglGetProcAddress("glTexCoord4d");
        boom::glTexCoord4dv = (boom::OpenGLTexCoord4dvFn)wglGetProcAddress("glTexCoord4dv");
        boom::glTexCoord4f = (boom::OpenGLTexCoord4fFn)wglGetProcAddress("glTexCoord4f");
        boom::glTexCoord4fv = (boom::OpenGLTexCoord4fvFn)wglGetProcAddress("glTexCoord4fv");
        boom::glTexCoord4i = (boom::OpenGLTexCoord4iFn)wglGetProcAddress("glTexCoord4i");
        boom::glTexCoord4iv = (boom::OpenGLTexCoord4ivFn)wglGetProcAddress("glTexCoord4iv");
        boom::glTexCoord4s = (boom::OpenGLTexCoord4sFn)wglGetProcAddress("glTexCoord4s");
        boom::glTexCoord4sv = (boom::OpenGLTexCoord4svFn)wglGetProcAddress("glTexCoord4sv");
        boom::glTexCoordP1ui = (boom::OpenGLTexCoordP1uiFn)wglGetProcAddress("glTexCoordP1ui");
        boom::glTexCoordP1uiv = (boom::OpenGLTexCoordP1uivFn)wglGetProcAddress("glTexCoordP1uiv");
        boom::glTexCoordP2ui = (boom::OpenGLTexCoordP2uiFn)wglGetProcAddress("glTexCoordP2ui");
        boom::glTexCoordP2uiv = (boom::OpenGLTexCoordP2uivFn)wglGetProcAddress("glTexCoordP2uiv");
        boom::glTexCoordP3ui = (boom::OpenGLTexCoordP3uiFn)wglGetProcAddress("glTexCoordP3ui");
        boom::glTexCoordP3uiv = (boom::OpenGLTexCoordP3uivFn)wglGetProcAddress("glTexCoordP3uiv");
        boom::glTexCoordP4ui = (boom::OpenGLTexCoordP4uiFn)wglGetProcAddress("glTexCoordP4ui");
        boom::glTexCoordP4uiv = (boom::OpenGLTexCoordP4uivFn)wglGetProcAddress("glTexCoordP4uiv");
        boom::glTexCoordPointer = (boom::OpenGLTexCoordPointerFn)wglGetProcAddress("glTexCoordPointer");
        boom::glTexEnvf = (boom::OpenGLTexEnvfFn)wglGetProcAddress("glTexEnvf");
        boom::glTexEnvfv = (boom::OpenGLTexEnvfvFn)wglGetProcAddress("glTexEnvfv");
        boom::glTexEnvi = (boom::OpenGLTexEnviFn)wglGetProcAddress("glTexEnvi");
        boom::glTexEnviv = (boom::OpenGLTexEnvivFn)wglGetProcAddress("glTexEnviv");
        boom::glTexEnvx = (boom::OpenGLTexEnvxFn)wglGetProcAddress("glTexEnvx");
        boom::glTexEnvxv = (boom::OpenGLTexEnvxvFn)wglGetProcAddress("glTexEnvxv");
        boom::glTexGend = (boom::OpenGLTexGendFn)wglGetProcAddress("glTexGend");
        boom::glTexGendv = (boom::OpenGLTexGendvFn)wglGetProcAddress("glTexGendv");
        boom::glTexGenf = (boom::OpenGLTexGenfFn)wglGetProcAddress("glTexGenf");
        boom::glTexGenfv = (boom::OpenGLTexGenfvFn)wglGetProcAddress("glTexGenfv");
        boom::glTexGeni = (boom::OpenGLTexGeniFn)wglGetProcAddress("glTexGeni");
        boom::glTexGeniv = (boom::OpenGLTexGenivFn)wglGetProcAddress("glTexGeniv");
        boom::glTexImage1D = (boom::OpenGLTexImage1DFn)wglGetProcAddress("glTexImage1D");
        boom::glTexImage2D = (boom::OpenGLTexImage2DFn)wglGetProcAddress("glTexImage2D");
        boom::glTexImage2DMultisample = (boom::OpenGLTexImage2DMultisampleFn)wglGetProcAddress("glTexImage2DMultisample");
        boom::glTexImage3D = (boom::OpenGLTexImage3DFn)wglGetProcAddress("glTexImage3D");
        boom::glTexImage3DMultisample = (boom::OpenGLTexImage3DMultisampleFn)wglGetProcAddress("glTexImage3DMultisample");
        boom::glTexParameterIiv = (boom::OpenGLTexParameterIivFn)wglGetProcAddress("glTexParameterIiv");
        boom::glTexParameterIuiv = (boom::OpenGLTexParameterIuivFn)wglGetProcAddress("glTexParameterIuiv");
        boom::glTexParameterf = (boom::OpenGLTexParameterfFn)wglGetProcAddress("glTexParameterf");
        boom::glTexParameterfv = (boom::OpenGLTexParameterfvFn)wglGetProcAddress("glTexParameterfv");
        boom::glTexParameteri = (boom::OpenGLTexParameteriFn)wglGetProcAddress("glTexParameteri");
        boom::glTexParameteriv = (boom::OpenGLTexParameterivFn)wglGetProcAddress("glTexParameteriv");
        boom::glTexParameterx = (boom::OpenGLTexParameterxFn)wglGetProcAddress("glTexParameterx");
        boom::glTexParameterxv = (boom::OpenGLTexParameterxvFn)wglGetProcAddress("glTexParameterxv");
        boom::glTexStorage1D = (boom::OpenGLTexStorage1DFn)wglGetProcAddress("glTexStorage1D");
        boom::glTexStorage2D = (boom::OpenGLTexStorage2DFn)wglGetProcAddress("glTexStorage2D");
        boom::glTexStorage2DMultisample = (boom::OpenGLTexStorage2DMultisampleFn)wglGetProcAddress("glTexStorage2DMultisample");
        boom::glTexStorage3D = (boom::OpenGLTexStorage3DFn)wglGetProcAddress("glTexStorage3D");
        boom::glTexStorage3DMultisample = (boom::OpenGLTexStorage3DMultisampleFn)wglGetProcAddress("glTexStorage3DMultisample");
        boom::glTexSubImage1D = (boom::OpenGLTexSubImage1DFn)wglGetProcAddress("glTexSubImage1D");
        boom::glTexSubImage2D = (boom::OpenGLTexSubImage2DFn)wglGetProcAddress("glTexSubImage2D");
        boom::glTexSubImage3D = (boom::OpenGLTexSubImage3DFn)wglGetProcAddress("glTexSubImage3D");
        boom::glTextureBarrier = (boom::OpenGLTextureBarrierFn)wglGetProcAddress("glTextureBarrier");
        boom::glTextureBuffer = (boom::OpenGLTextureBufferFn)wglGetProcAddress("glTextureBuffer");
        boom::glTextureBufferRange = (boom::OpenGLTextureBufferRangeFn)wglGetProcAddress("glTextureBufferRange");
        boom::glTextureParameterIiv = (boom::OpenGLTextureParameterIivFn)wglGetProcAddress("glTextureParameterIiv");
        boom::glTextureParameterIuiv = (boom::OpenGLTextureParameterIuivFn)wglGetProcAddress("glTextureParameterIuiv");
        boom::glTextureParameterf = (boom::OpenGLTextureParameterfFn)wglGetProcAddress("glTextureParameterf");
        boom::glTextureParameterfv = (boom::OpenGLTextureParameterfvFn)wglGetProcAddress("glTextureParameterfv");
        boom::glTextureParameteri = (boom::OpenGLTextureParameteriFn)wglGetProcAddress("glTextureParameteri");
        boom::glTextureParameteriv = (boom::OpenGLTextureParameterivFn)wglGetProcAddress("glTextureParameteriv");
        boom::glTextureStorage1D = (boom::OpenGLTextureStorage1DFn)wglGetProcAddress("glTextureStorage1D");
        boom::glTextureStorage2D = (boom::OpenGLTextureStorage2DFn)wglGetProcAddress("glTextureStorage2D");
        boom::glTextureStorage2DMultisample = (boom::OpenGLTextureStorage2DMultisampleFn)wglGetProcAddress("glTextureStorage2DMultisample");
        boom::glTextureStorage3D = (boom::OpenGLTextureStorage3DFn)wglGetProcAddress("glTextureStorage3D");
        boom::glTextureStorage3DMultisample = (boom::OpenGLTextureStorage3DMultisampleFn)wglGetProcAddress("glTextureStorage3DMultisample");
        boom::glTextureSubImage1D = (boom::OpenGLTextureSubImage1DFn)wglGetProcAddress("glTextureSubImage1D");
        boom::glTextureSubImage2D = (boom::OpenGLTextureSubImage2DFn)wglGetProcAddress("glTextureSubImage2D");
        boom::glTextureSubImage3D = (boom::OpenGLTextureSubImage3DFn)wglGetProcAddress("glTextureSubImage3D");
        boom::glTextureView = (boom::OpenGLTextureViewFn)wglGetProcAddress("glTextureView");
        boom::glTransformFeedbackBufferBase = (boom::OpenGLTransformFeedbackBufferBaseFn)wglGetProcAddress("glTransformFeedbackBufferBase");
        boom::glTransformFeedbackBufferRange = (boom::OpenGLTransformFeedbackBufferRangeFn)wglGetProcAddress("glTransformFeedbackBufferRange");
        boom::glTransformFeedbackVaryings = (boom::OpenGLTransformFeedbackVaryingsFn)wglGetProcAddress("glTransformFeedbackVaryings");
        boom::glTranslated = (boom::OpenGLTranslatedFn)wglGetProcAddress("glTranslated");
        boom::glTranslatef = (boom::OpenGLTranslatefFn)wglGetProcAddress("glTranslatef");
        boom::glTranslatex = (boom::OpenGLTranslatexFn)wglGetProcAddress("glTranslatex");
        boom::glUniform1d = (boom::OpenGLUniform1dFn)wglGetProcAddress("glUniform1d");
        boom::glUniform1dv = (boom::OpenGLUniform1dvFn)wglGetProcAddress("glUniform1dv");
        boom::glUniform1f = (boom::OpenGLUniform1fFn)wglGetProcAddress("glUniform1f");
        boom::glUniform1fv = (boom::OpenGLUniform1fvFn)wglGetProcAddress("glUniform1fv");
        boom::glUniform1i = (boom::OpenGLUniform1iFn)wglGetProcAddress("glUniform1i");
        boom::glUniform1iv = (boom::OpenGLUniform1ivFn)wglGetProcAddress("glUniform1iv");
        boom::glUniform1ui = (boom::OpenGLUniform1uiFn)wglGetProcAddress("glUniform1ui");
        boom::glUniform1uiv = (boom::OpenGLUniform1uivFn)wglGetProcAddress("glUniform1uiv");
        boom::glUniform2d = (boom::OpenGLUniform2dFn)wglGetProcAddress("glUniform2d");
        boom::glUniform2dv = (boom::OpenGLUniform2dvFn)wglGetProcAddress("glUniform2dv");
        boom::glUniform2f = (boom::OpenGLUniform2fFn)wglGetProcAddress("glUniform2f");
        boom::glUniform2fv = (boom::OpenGLUniform2fvFn)wglGetProcAddress("glUniform2fv");
        boom::glUniform2i = (boom::OpenGLUniform2iFn)wglGetProcAddress("glUniform2i");
        boom::glUniform2iv = (boom::OpenGLUniform2ivFn)wglGetProcAddress("glUniform2iv");
        boom::glUniform2ui = (boom::OpenGLUniform2uiFn)wglGetProcAddress("glUniform2ui");
        boom::glUniform2uiv = (boom::OpenGLUniform2uivFn)wglGetProcAddress("glUniform2uiv");
        boom::glUniform3d = (boom::OpenGLUniform3dFn)wglGetProcAddress("glUniform3d");
        boom::glUniform3dv = (boom::OpenGLUniform3dvFn)wglGetProcAddress("glUniform3dv");
        boom::glUniform3f = (boom::OpenGLUniform3fFn)wglGetProcAddress("glUniform3f");
        boom::glUniform3fv = (boom::OpenGLUniform3fvFn)wglGetProcAddress("glUniform3fv");
        boom::glUniform3i = (boom::OpenGLUniform3iFn)wglGetProcAddress("glUniform3i");
        boom::glUniform3iv = (boom::OpenGLUniform3ivFn)wglGetProcAddress("glUniform3iv");
        boom::glUniform3ui = (boom::OpenGLUniform3uiFn)wglGetProcAddress("glUniform3ui");
        boom::glUniform3uiv = (boom::OpenGLUniform3uivFn)wglGetProcAddress("glUniform3uiv");
        boom::glUniform4d = (boom::OpenGLUniform4dFn)wglGetProcAddress("glUniform4d");
        boom::glUniform4dv = (boom::OpenGLUniform4dvFn)wglGetProcAddress("glUniform4dv");
        boom::glUniform4f = (boom::OpenGLUniform4fFn)wglGetProcAddress("glUniform4f");
        boom::glUniform4fv = (boom::OpenGLUniform4fvFn)wglGetProcAddress("glUniform4fv");
        boom::glUniform4i = (boom::OpenGLUniform4iFn)wglGetProcAddress("glUniform4i");
        boom::glUniform4iv = (boom::OpenGLUniform4ivFn)wglGetProcAddress("glUniform4iv");
        boom::glUniform4ui = (boom::OpenGLUniform4uiFn)wglGetProcAddress("glUniform4ui");
        boom::glUniform4uiv = (boom::OpenGLUniform4uivFn)wglGetProcAddress("glUniform4uiv");
        boom::glUniformBlockBinding = (boom::OpenGLUniformBlockBindingFn)wglGetProcAddress("glUniformBlockBinding");
        boom::glUniformMatrix2dv = (boom::OpenGLUniformMatrix2dvFn)wglGetProcAddress("glUniformMatrix2dv");
        boom::glUniformMatrix2fv = (boom::OpenGLUniformMatrix2fvFn)wglGetProcAddress("glUniformMatrix2fv");
        boom::glUniformMatrix2x3dv = (boom::OpenGLUniformMatrix2x3dvFn)wglGetProcAddress("glUniformMatrix2x3dv");
        boom::glUniformMatrix2x3fv = (boom::OpenGLUniformMatrix2x3fvFn)wglGetProcAddress("glUniformMatrix2x3fv");
        boom::glUniformMatrix2x4dv = (boom::OpenGLUniformMatrix2x4dvFn)wglGetProcAddress("glUniformMatrix2x4dv");
        boom::glUniformMatrix2x4fv = (boom::OpenGLUniformMatrix2x4fvFn)wglGetProcAddress("glUniformMatrix2x4fv");
        boom::glUniformMatrix3dv = (boom::OpenGLUniformMatrix3dvFn)wglGetProcAddress("glUniformMatrix3dv");
        boom::glUniformMatrix3fv = (boom::OpenGLUniformMatrix3fvFn)wglGetProcAddress("glUniformMatrix3fv");
        boom::glUniformMatrix3x2dv = (boom::OpenGLUniformMatrix3x2dvFn)wglGetProcAddress("glUniformMatrix3x2dv");
        boom::glUniformMatrix3x2fv = (boom::OpenGLUniformMatrix3x2fvFn)wglGetProcAddress("glUniformMatrix3x2fv");
        boom::glUniformMatrix3x4dv = (boom::OpenGLUniformMatrix3x4dvFn)wglGetProcAddress("glUniformMatrix3x4dv");
        boom::glUniformMatrix3x4fv = (boom::OpenGLUniformMatrix3x4fvFn)wglGetProcAddress("glUniformMatrix3x4fv");
        boom::glUniformMatrix4dv = (boom::OpenGLUniformMatrix4dvFn)wglGetProcAddress("glUniformMatrix4dv");
        boom::glUniformMatrix4fv = (boom::OpenGLUniformMatrix4fvFn)wglGetProcAddress("glUniformMatrix4fv");
        boom::glUniformMatrix4x2dv = (boom::OpenGLUniformMatrix4x2dvFn)wglGetProcAddress("glUniformMatrix4x2dv");
        boom::glUniformMatrix4x2fv = (boom::OpenGLUniformMatrix4x2fvFn)wglGetProcAddress("glUniformMatrix4x2fv");
        boom::glUniformMatrix4x3dv = (boom::OpenGLUniformMatrix4x3dvFn)wglGetProcAddress("glUniformMatrix4x3dv");
        boom::glUniformMatrix4x3fv = (boom::OpenGLUniformMatrix4x3fvFn)wglGetProcAddress("glUniformMatrix4x3fv");
        boom::glUniformSubroutinesuiv = (boom::OpenGLUniformSubroutinesuivFn)wglGetProcAddress("glUniformSubroutinesuiv");
        boom::glUnmapBuffer = (boom::OpenGLUnmapBufferFn)wglGetProcAddress("glUnmapBuffer");
        boom::glUnmapNamedBuffer = (boom::OpenGLUnmapNamedBufferFn)wglGetProcAddress("glUnmapNamedBuffer");
        boom::glUseProgram = (boom::OpenGLUseProgramFn)wglGetProcAddress("glUseProgram");
        boom::glUseProgramStages = (boom::OpenGLUseProgramStagesFn)wglGetProcAddress("glUseProgramStages");
        boom::glValidateProgram = (boom::OpenGLValidateProgramFn)wglGetProcAddress("glValidateProgram");
        boom::glValidateProgramPipeline = (boom::OpenGLValidateProgramPipelineFn)wglGetProcAddress("glValidateProgramPipeline");
        boom::glVertex2d = (boom::OpenGLVertex2dFn)wglGetProcAddress("glVertex2d");
        boom::glVertex2dv = (boom::OpenGLVertex2dvFn)wglGetProcAddress("glVertex2dv");
        boom::glVertex2f = (boom::OpenGLVertex2fFn)wglGetProcAddress("glVertex2f");
        boom::glVertex2fv = (boom::OpenGLVertex2fvFn)wglGetProcAddress("glVertex2fv");
        boom::glVertex2i = (boom::OpenGLVertex2iFn)wglGetProcAddress("glVertex2i");
        boom::glVertex2iv = (boom::OpenGLVertex2ivFn)wglGetProcAddress("glVertex2iv");
        boom::glVertex2s = (boom::OpenGLVertex2sFn)wglGetProcAddress("glVertex2s");
        boom::glVertex2sv = (boom::OpenGLVertex2svFn)wglGetProcAddress("glVertex2sv");
        boom::glVertex3d = (boom::OpenGLVertex3dFn)wglGetProcAddress("glVertex3d");
        boom::glVertex3dv = (boom::OpenGLVertex3dvFn)wglGetProcAddress("glVertex3dv");
        boom::glVertex3f = (boom::OpenGLVertex3fFn)wglGetProcAddress("glVertex3f");
        boom::glVertex3fv = (boom::OpenGLVertex3fvFn)wglGetProcAddress("glVertex3fv");
        boom::glVertex3i = (boom::OpenGLVertex3iFn)wglGetProcAddress("glVertex3i");
        boom::glVertex3iv = (boom::OpenGLVertex3ivFn)wglGetProcAddress("glVertex3iv");
        boom::glVertex3s = (boom::OpenGLVertex3sFn)wglGetProcAddress("glVertex3s");
        boom::glVertex3sv = (boom::OpenGLVertex3svFn)wglGetProcAddress("glVertex3sv");
        boom::glVertex4d = (boom::OpenGLVertex4dFn)wglGetProcAddress("glVertex4d");
        boom::glVertex4dv = (boom::OpenGLVertex4dvFn)wglGetProcAddress("glVertex4dv");
        boom::glVertex4f = (boom::OpenGLVertex4fFn)wglGetProcAddress("glVertex4f");
        boom::glVertex4fv = (boom::OpenGLVertex4fvFn)wglGetProcAddress("glVertex4fv");
        boom::glVertex4i = (boom::OpenGLVertex4iFn)wglGetProcAddress("glVertex4i");
        boom::glVertex4iv = (boom::OpenGLVertex4ivFn)wglGetProcAddress("glVertex4iv");
        boom::glVertex4s = (boom::OpenGLVertex4sFn)wglGetProcAddress("glVertex4s");
        boom::glVertex4sv = (boom::OpenGLVertex4svFn)wglGetProcAddress("glVertex4sv");
        boom::glVertexArrayAttribBinding = (boom::OpenGLVertexArrayAttribBindingFn)wglGetProcAddress("glVertexArrayAttribBinding");
        boom::glVertexArrayAttribFormat = (boom::OpenGLVertexArrayAttribFormatFn)wglGetProcAddress("glVertexArrayAttribFormat");
        boom::glVertexArrayAttribIFormat = (boom::OpenGLVertexArrayAttribIFormatFn)wglGetProcAddress("glVertexArrayAttribIFormat");
        boom::glVertexArrayAttribLFormat = (boom::OpenGLVertexArrayAttribLFormatFn)wglGetProcAddress("glVertexArrayAttribLFormat");
        boom::glVertexArrayBindingDivisor = (boom::OpenGLVertexArrayBindingDivisorFn)wglGetProcAddress("glVertexArrayBindingDivisor");
        boom::glVertexArrayElementBuffer = (boom::OpenGLVertexArrayElementBufferFn)wglGetProcAddress("glVertexArrayElementBuffer");
        boom::glVertexArrayVertexBuffer = (boom::OpenGLVertexArrayVertexBufferFn)wglGetProcAddress("glVertexArrayVertexBuffer");
        boom::glVertexArrayVertexBuffers = (boom::OpenGLVertexArrayVertexBuffersFn)wglGetProcAddress("glVertexArrayVertexBuffers");
        boom::glVertexAttrib1d = (boom::OpenGLVertexAttrib1dFn)wglGetProcAddress("glVertexAttrib1d");
        boom::glVertexAttrib1dv = (boom::OpenGLVertexAttrib1dvFn)wglGetProcAddress("glVertexAttrib1dv");
        boom::glVertexAttrib1f = (boom::OpenGLVertexAttrib1fFn)wglGetProcAddress("glVertexAttrib1f");
        boom::glVertexAttrib1fv = (boom::OpenGLVertexAttrib1fvFn)wglGetProcAddress("glVertexAttrib1fv");
        boom::glVertexAttrib1s = (boom::OpenGLVertexAttrib1sFn)wglGetProcAddress("glVertexAttrib1s");
        boom::glVertexAttrib1sv = (boom::OpenGLVertexAttrib1svFn)wglGetProcAddress("glVertexAttrib1sv");
        boom::glVertexAttrib2d = (boom::OpenGLVertexAttrib2dFn)wglGetProcAddress("glVertexAttrib2d");
        boom::glVertexAttrib2dv = (boom::OpenGLVertexAttrib2dvFn)wglGetProcAddress("glVertexAttrib2dv");
        boom::glVertexAttrib2f = (boom::OpenGLVertexAttrib2fFn)wglGetProcAddress("glVertexAttrib2f");
        boom::glVertexAttrib2fv = (boom::OpenGLVertexAttrib2fvFn)wglGetProcAddress("glVertexAttrib2fv");
        boom::glVertexAttrib2s = (boom::OpenGLVertexAttrib2sFn)wglGetProcAddress("glVertexAttrib2s");
        boom::glVertexAttrib2sv = (boom::OpenGLVertexAttrib2svFn)wglGetProcAddress("glVertexAttrib2sv");
        boom::glVertexAttrib3d = (boom::OpenGLVertexAttrib3dFn)wglGetProcAddress("glVertexAttrib3d");
        boom::glVertexAttrib3dv = (boom::OpenGLVertexAttrib3dvFn)wglGetProcAddress("glVertexAttrib3dv");
        boom::glVertexAttrib3f = (boom::OpenGLVertexAttrib3fFn)wglGetProcAddress("glVertexAttrib3f");
        boom::glVertexAttrib3fv = (boom::OpenGLVertexAttrib3fvFn)wglGetProcAddress("glVertexAttrib3fv");
        boom::glVertexAttrib3s = (boom::OpenGLVertexAttrib3sFn)wglGetProcAddress("glVertexAttrib3s");
        boom::glVertexAttrib3sv = (boom::OpenGLVertexAttrib3svFn)wglGetProcAddress("glVertexAttrib3sv");
        boom::glVertexAttrib4Nbv = (boom::OpenGLVertexAttrib4NbvFn)wglGetProcAddress("glVertexAttrib4Nbv");
        boom::glVertexAttrib4Niv = (boom::OpenGLVertexAttrib4NivFn)wglGetProcAddress("glVertexAttrib4Niv");
        boom::glVertexAttrib4Nsv = (boom::OpenGLVertexAttrib4NsvFn)wglGetProcAddress("glVertexAttrib4Nsv");
        boom::glVertexAttrib4Nub = (boom::OpenGLVertexAttrib4NubFn)wglGetProcAddress("glVertexAttrib4Nub");
        boom::glVertexAttrib4Nubv = (boom::OpenGLVertexAttrib4NubvFn)wglGetProcAddress("glVertexAttrib4Nubv");
        boom::glVertexAttrib4Nuiv = (boom::OpenGLVertexAttrib4NuivFn)wglGetProcAddress("glVertexAttrib4Nuiv");
        boom::glVertexAttrib4Nusv = (boom::OpenGLVertexAttrib4NusvFn)wglGetProcAddress("glVertexAttrib4Nusv");
        boom::glVertexAttrib4bv = (boom::OpenGLVertexAttrib4bvFn)wglGetProcAddress("glVertexAttrib4bv");
        boom::glVertexAttrib4d = (boom::OpenGLVertexAttrib4dFn)wglGetProcAddress("glVertexAttrib4d");
        boom::glVertexAttrib4dv = (boom::OpenGLVertexAttrib4dvFn)wglGetProcAddress("glVertexAttrib4dv");
        boom::glVertexAttrib4f = (boom::OpenGLVertexAttrib4fFn)wglGetProcAddress("glVertexAttrib4f");
        boom::glVertexAttrib4fv = (boom::OpenGLVertexAttrib4fvFn)wglGetProcAddress("glVertexAttrib4fv");
        boom::glVertexAttrib4iv = (boom::OpenGLVertexAttrib4ivFn)wglGetProcAddress("glVertexAttrib4iv");
        boom::glVertexAttrib4s = (boom::OpenGLVertexAttrib4sFn)wglGetProcAddress("glVertexAttrib4s");
        boom::glVertexAttrib4sv = (boom::OpenGLVertexAttrib4svFn)wglGetProcAddress("glVertexAttrib4sv");
        boom::glVertexAttrib4ubv = (boom::OpenGLVertexAttrib4ubvFn)wglGetProcAddress("glVertexAttrib4ubv");
        boom::glVertexAttrib4uiv = (boom::OpenGLVertexAttrib4uivFn)wglGetProcAddress("glVertexAttrib4uiv");
        boom::glVertexAttrib4usv = (boom::OpenGLVertexAttrib4usvFn)wglGetProcAddress("glVertexAttrib4usv");
        boom::glVertexAttribBinding = (boom::OpenGLVertexAttribBindingFn)wglGetProcAddress("glVertexAttribBinding");
        boom::glVertexAttribDivisor = (boom::OpenGLVertexAttribDivisorFn)wglGetProcAddress("glVertexAttribDivisor");
        boom::glVertexAttribFormat = (boom::OpenGLVertexAttribFormatFn)wglGetProcAddress("glVertexAttribFormat");
        boom::glVertexAttribI1i = (boom::OpenGLVertexAttribI1iFn)wglGetProcAddress("glVertexAttribI1i");
        boom::glVertexAttribI1iv = (boom::OpenGLVertexAttribI1ivFn)wglGetProcAddress("glVertexAttribI1iv");
        boom::glVertexAttribI1ui = (boom::OpenGLVertexAttribI1uiFn)wglGetProcAddress("glVertexAttribI1ui");
        boom::glVertexAttribI1uiv = (boom::OpenGLVertexAttribI1uivFn)wglGetProcAddress("glVertexAttribI1uiv");
        boom::glVertexAttribI2i = (boom::OpenGLVertexAttribI2iFn)wglGetProcAddress("glVertexAttribI2i");
        boom::glVertexAttribI2iv = (boom::OpenGLVertexAttribI2ivFn)wglGetProcAddress("glVertexAttribI2iv");
        boom::glVertexAttribI2ui = (boom::OpenGLVertexAttribI2uiFn)wglGetProcAddress("glVertexAttribI2ui");
        boom::glVertexAttribI2uiv = (boom::OpenGLVertexAttribI2uivFn)wglGetProcAddress("glVertexAttribI2uiv");
        boom::glVertexAttribI3i = (boom::OpenGLVertexAttribI3iFn)wglGetProcAddress("glVertexAttribI3i");
        boom::glVertexAttribI3iv = (boom::OpenGLVertexAttribI3ivFn)wglGetProcAddress("glVertexAttribI3iv");
        boom::glVertexAttribI3ui = (boom::OpenGLVertexAttribI3uiFn)wglGetProcAddress("glVertexAttribI3ui");
        boom::glVertexAttribI3uiv = (boom::OpenGLVertexAttribI3uivFn)wglGetProcAddress("glVertexAttribI3uiv");
        boom::glVertexAttribI4bv = (boom::OpenGLVertexAttribI4bvFn)wglGetProcAddress("glVertexAttribI4bv");
        boom::glVertexAttribI4i = (boom::OpenGLVertexAttribI4iFn)wglGetProcAddress("glVertexAttribI4i");
        boom::glVertexAttribI4iv = (boom::OpenGLVertexAttribI4ivFn)wglGetProcAddress("glVertexAttribI4iv");
        boom::glVertexAttribI4sv = (boom::OpenGLVertexAttribI4svFn)wglGetProcAddress("glVertexAttribI4sv");
        boom::glVertexAttribI4ubv = (boom::OpenGLVertexAttribI4ubvFn)wglGetProcAddress("glVertexAttribI4ubv");
        boom::glVertexAttribI4ui = (boom::OpenGLVertexAttribI4uiFn)wglGetProcAddress("glVertexAttribI4ui");
        boom::glVertexAttribI4uiv = (boom::OpenGLVertexAttribI4uivFn)wglGetProcAddress("glVertexAttribI4uiv");
        boom::glVertexAttribI4usv = (boom::OpenGLVertexAttribI4usvFn)wglGetProcAddress("glVertexAttribI4usv");
        boom::glVertexAttribIFormat = (boom::OpenGLVertexAttribIFormatFn)wglGetProcAddress("glVertexAttribIFormat");
        boom::glVertexAttribIPointer = (boom::OpenGLVertexAttribIPointerFn)wglGetProcAddress("glVertexAttribIPointer");
        boom::glVertexAttribL1d = (boom::OpenGLVertexAttribL1dFn)wglGetProcAddress("glVertexAttribL1d");
        boom::glVertexAttribL1dv = (boom::OpenGLVertexAttribL1dvFn)wglGetProcAddress("glVertexAttribL1dv");
        boom::glVertexAttribL2d = (boom::OpenGLVertexAttribL2dFn)wglGetProcAddress("glVertexAttribL2d");
        boom::glVertexAttribL2dv = (boom::OpenGLVertexAttribL2dvFn)wglGetProcAddress("glVertexAttribL2dv");
        boom::glVertexAttribL3d = (boom::OpenGLVertexAttribL3dFn)wglGetProcAddress("glVertexAttribL3d");
        boom::glVertexAttribL3dv = (boom::OpenGLVertexAttribL3dvFn)wglGetProcAddress("glVertexAttribL3dv");
        boom::glVertexAttribL4d = (boom::OpenGLVertexAttribL4dFn)wglGetProcAddress("glVertexAttribL4d");
        boom::glVertexAttribL4dv = (boom::OpenGLVertexAttribL4dvFn)wglGetProcAddress("glVertexAttribL4dv");
        boom::glVertexAttribLFormat = (boom::OpenGLVertexAttribLFormatFn)wglGetProcAddress("glVertexAttribLFormat");
        boom::glVertexAttribLPointer = (boom::OpenGLVertexAttribLPointerFn)wglGetProcAddress("glVertexAttribLPointer");
        boom::glVertexAttribP1ui = (boom::OpenGLVertexAttribP1uiFn)wglGetProcAddress("glVertexAttribP1ui");
        boom::glVertexAttribP1uiv = (boom::OpenGLVertexAttribP1uivFn)wglGetProcAddress("glVertexAttribP1uiv");
        boom::glVertexAttribP2ui = (boom::OpenGLVertexAttribP2uiFn)wglGetProcAddress("glVertexAttribP2ui");
        boom::glVertexAttribP2uiv = (boom::OpenGLVertexAttribP2uivFn)wglGetProcAddress("glVertexAttribP2uiv");
        boom::glVertexAttribP3ui = (boom::OpenGLVertexAttribP3uiFn)wglGetProcAddress("glVertexAttribP3ui");
        boom::glVertexAttribP3uiv = (boom::OpenGLVertexAttribP3uivFn)wglGetProcAddress("glVertexAttribP3uiv");
        boom::glVertexAttribP4ui = (boom::OpenGLVertexAttribP4uiFn)wglGetProcAddress("glVertexAttribP4ui");
        boom::glVertexAttribP4uiv = (boom::OpenGLVertexAttribP4uivFn)wglGetProcAddress("glVertexAttribP4uiv");
        boom::glVertexAttribPointer = (boom::OpenGLVertexAttribPointerFn)wglGetProcAddress("glVertexAttribPointer");
        boom::glVertexBindingDivisor = (boom::OpenGLVertexBindingDivisorFn)wglGetProcAddress("glVertexBindingDivisor");
        boom::glVertexP2ui = (boom::OpenGLVertexP2uiFn)wglGetProcAddress("glVertexP2ui");
        boom::glVertexP2uiv = (boom::OpenGLVertexP2uivFn)wglGetProcAddress("glVertexP2uiv");
        boom::glVertexP3ui = (boom::OpenGLVertexP3uiFn)wglGetProcAddress("glVertexP3ui");
        boom::glVertexP3uiv = (boom::OpenGLVertexP3uivFn)wglGetProcAddress("glVertexP3uiv");
        boom::glVertexP4ui = (boom::OpenGLVertexP4uiFn)wglGetProcAddress("glVertexP4ui");
        boom::glVertexP4uiv = (boom::OpenGLVertexP4uivFn)wglGetProcAddress("glVertexP4uiv");
        boom::glVertexPointer = (boom::OpenGLVertexPointerFn)wglGetProcAddress("glVertexPointer");
        boom::glViewport = (boom::OpenGLViewportFn)wglGetProcAddress("glViewport");
        boom::glViewportArrayv = (boom::OpenGLViewportArrayvFn)wglGetProcAddress("glViewportArrayv");
        boom::glViewportIndexedf = (boom::OpenGLViewportIndexedfFn)wglGetProcAddress("glViewportIndexedf");
        boom::glViewportIndexedfv = (boom::OpenGLViewportIndexedfvFn)wglGetProcAddress("glViewportIndexedfv");
        boom::glWaitSync = (boom::OpenGLWaitSyncFn)wglGetProcAddress("glWaitSync");
        boom::glWindowPos2d = (boom::OpenGLWindowPos2dFn)wglGetProcAddress("glWindowPos2d");
        boom::glWindowPos2dv = (boom::OpenGLWindowPos2dvFn)wglGetProcAddress("glWindowPos2dv");
        boom::glWindowPos2f = (boom::OpenGLWindowPos2fFn)wglGetProcAddress("glWindowPos2f");
        boom::glWindowPos2fv = (boom::OpenGLWindowPos2fvFn)wglGetProcAddress("glWindowPos2fv");
        boom::glWindowPos2i = (boom::OpenGLWindowPos2iFn)wglGetProcAddress("glWindowPos2i");
        boom::glWindowPos2iv = (boom::OpenGLWindowPos2ivFn)wglGetProcAddress("glWindowPos2iv");
        boom::glWindowPos2s = (boom::OpenGLWindowPos2sFn)wglGetProcAddress("glWindowPos2s");
        boom::glWindowPos2sv = (boom::OpenGLWindowPos2svFn)wglGetProcAddress("glWindowPos2sv");
        boom::glWindowPos3d = (boom::OpenGLWindowPos3dFn)wglGetProcAddress("glWindowPos3d");
        boom::glWindowPos3dv = (boom::OpenGLWindowPos3dvFn)wglGetProcAddress("glWindowPos3dv");
        boom::glWindowPos3f = (boom::OpenGLWindowPos3fFn)wglGetProcAddress("glWindowPos3f");
        boom::glWindowPos3fv = (boom::OpenGLWindowPos3fvFn)wglGetProcAddress("glWindowPos3fv");
        boom::glWindowPos3i = (boom::OpenGLWindowPos3iFn)wglGetProcAddress("glWindowPos3i");
        boom::glWindowPos3iv = (boom::OpenGLWindowPos3ivFn)wglGetProcAddress("glWindowPos3iv");
        boom::glWindowPos3s = (boom::OpenGLWindowPos3sFn)wglGetProcAddress("glWindowPos3s");
        boom::glWindowPos3sv = (boom::OpenGLWindowPos3svFn)wglGetProcAddress("glWindowPos3sv");
        bootstrapped = true;
    }
}

} /* namespace boom */