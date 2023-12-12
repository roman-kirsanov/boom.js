#include <cassert>
#include <iostream>
#include <windows.h>
#include <GL/GL.h>
#include <Boom/OpenGL.hpp>
#include <Boom/Utilities.hpp>
#include "View.hpp"

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
        boom::Abort("RegisterClass() failed"); \
    } \
}

#define CreateWindowExE(...) [&]{ \
    auto __ret = CreateWindowExA(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("CreateWindowEx() failed"); \
    } \
    return __ret; \
}()

#define GetDCE(...) [&]{ \
    auto __ret = GetDC(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("GetDC() failed"); \
    } \
    return __ret; \
}()

#define ChoosePixelFormatE(...) [&]{ \
    auto __ret = ChoosePixelFormat(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("ChoosePixelFormat() failed"); \
    } \
    return __ret; \
}()

#define DescribePixelFormatE(...) { \
    if (!DescribePixelFormat(__VA_ARGS__)) { \
        boom::Abort("DescribePixelFormat() failed"); \
    } \
}

#define SetPixelFormatE(...) [&]{ \
    if (!SetPixelFormat(__VA_ARGS__)) { \
        boom::Abort("SetPixelFormat() failed"); \
    } \
}()

#define wglCreateContextE(...) [&]{ \
    auto __ret = wglCreateContext(__VA_ARGS__); \
    if (!__ret) { \
        boom::Abort("wglCreateContext() failed"); \
    } \
    return __ret; \
}()

#define wglMakeCurrentE(...) { \
    if (!wglMakeCurrent(__VA_ARGS__)) { \
        boom::Abort("wglMakeCurrent() failed"); \
    } \
}

#define wglDeleteContextE(...) { \
    if (!wglDeleteContext(__VA_ARGS__)) { \
        boom::Abort("wglDeleteContext() failed"); \
    } \
}

#define ReleaseDCE(...) { \
    if (!ReleaseDC(__VA_ARGS__)) { \
        boom::Abort("ReleaseDC() failed"); \
    } \
}

#define DestroyWindowE(...) { \
    if (!DestroyWindow(__VA_ARGS__)) { \
        boom::Abort("DestroyWindow() failed"); \
    } \
}

#define wglShareListsE(...) { \
    if (!wglShareLists(__VA_ARGS__)) { \
        boom::Abort("wglShareLists() failed"); \
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
        boom::Abort("boom::OpenGL::OpenGL() failed: Failed to obtain \"wglCreateContextAttribsARB\" function pointer");
    }
    if (boom::wglChoosePixelFormatARB == nullptr) {
        boom::Abort("boom::OpenGL::OpenGL() failed: Failed to obtain \"wglChoosePixelFormatARB\" function pointer");
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
        boom::Abort("boom::OpenGL::OpenGL() failed: wglChoosePixelFormatARB() failed");
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
        boom::Abort("boom::OpenGL::OpenGL() failed: wglCreateContextAttribsARB() failed");
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

} /* namespace boom */