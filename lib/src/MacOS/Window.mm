#include <map>
#include <iostream>
#include <cassert>
#include <functional>
#include <Cocoa/Cocoa.h>
#include <Carbon/Carbon.h>
#include "Window.hpp"

auto const __key_map = std::map<std::int32_t, boom::Key>({
    { kVK_ANSI_0, boom::Key::_0 },
    { kVK_ANSI_1, boom::Key::_1 },
    { kVK_ANSI_2, boom::Key::_2 },
    { kVK_ANSI_3, boom::Key::_3 },
    { kVK_ANSI_4, boom::Key::_4 },
    { kVK_ANSI_5, boom::Key::_5 },
    { kVK_ANSI_6, boom::Key::_6 },
    { kVK_ANSI_7, boom::Key::_7 },
    { kVK_ANSI_8, boom::Key::_8 },
    { kVK_ANSI_9, boom::Key::_9 },
    { kVK_ANSI_A, boom::Key::A },
    { kVK_ANSI_B, boom::Key::B },
    { kVK_ANSI_C, boom::Key::C },
    { kVK_ANSI_D, boom::Key::D },
    { kVK_ANSI_E, boom::Key::E },
    { kVK_ANSI_F, boom::Key::F },
    { kVK_ANSI_G, boom::Key::G },
    { kVK_ANSI_H, boom::Key::H },
    { kVK_ANSI_I, boom::Key::I },
    { kVK_ANSI_J, boom::Key::J },
    { kVK_ANSI_K, boom::Key::K },
    { kVK_ANSI_L, boom::Key::L },
    { kVK_ANSI_M, boom::Key::M },
    { kVK_ANSI_N, boom::Key::N },
    { kVK_ANSI_O, boom::Key::O },
    { kVK_ANSI_P, boom::Key::P },
    { kVK_ANSI_Q, boom::Key::Q },
    { kVK_ANSI_R, boom::Key::R },
    { kVK_ANSI_S, boom::Key::S },
    { kVK_ANSI_T, boom::Key::T },
    { kVK_ANSI_U, boom::Key::U },
    { kVK_ANSI_V, boom::Key::V },
    { kVK_ANSI_W, boom::Key::W },
    { kVK_ANSI_X, boom::Key::X },
    { kVK_ANSI_Y, boom::Key::Y },
    { kVK_ANSI_Z, boom::Key::Z },
    { kVK_F1, boom::Key::F1 },
    { kVK_F2, boom::Key::F2 },
    { kVK_F3, boom::Key::F3 },
    { kVK_F4, boom::Key::F4 },
    { kVK_F5, boom::Key::F5 },
    { kVK_F6, boom::Key::F6 },
    { kVK_F7, boom::Key::F7 },
    { kVK_F8, boom::Key::F8 },
    { kVK_F9, boom::Key::F9 },
    { kVK_F10, boom::Key::F10 },
    { kVK_F11, boom::Key::F11 },
    { kVK_F12, boom::Key::F12 },
    { kVK_F13, boom::Key::F13 },
    { kVK_F14, boom::Key::F14 },
    { kVK_F15, boom::Key::F15 },
    { kVK_F16, boom::Key::F16 },
    { kVK_F17, boom::Key::F17 },
    { kVK_F18, boom::Key::F18 },
    { kVK_F19, boom::Key::F19 },
    { kVK_F20, boom::Key::F20 },
    { kVK_Option, boom::Key::Alt },
    { kVK_DownArrow, boom::Key::ArrowDown },
    { kVK_LeftArrow, boom::Key::ArrowLeft },
    { kVK_RightArrow, boom::Key::ArrowRight },
    { kVK_UpArrow, boom::Key::ArrowUp },
    { kVK_ANSI_Backslash, boom::Key::Backslash },
    { kVK_ANSI_LeftBracket, boom::Key::BracketLeft },
    { kVK_ANSI_RightBracket, boom::Key::BracketRight },
    { kVK_CapsLock, boom::Key::Capslock },
    { kVK_ANSI_Comma, boom::Key::Comma },
    { kVK_Control, boom::Key::Control },
    { kVK_Delete, boom::Key::Backspace },
    { kVK_End, boom::Key::End },
    { kVK_ANSI_Equal, boom::Key::Equal },
    { kVK_Escape, boom::Key::Escape },
    { kVK_ForwardDelete, boom::Key::ForwardDelete },
    { kVK_Function, boom::Key::Function },
    { kVK_ANSI_Grave, boom::Key::Grave },
    { kVK_Help, boom::Key::Help },
    { kVK_Home, boom::Key::Home },
    { kVK_Command, boom::Key::Meta },
    { kVK_ANSI_Minus, boom::Key::Minus },
    { kVK_Mute, boom::Key::Mute },
    { kVK_PageDown, boom::Key::PageDown },
    { kVK_PageUp, boom::Key::PageUp },
    { kVK_ANSI_Period, boom::Key::Period },
    { kVK_ANSI_Quote, boom::Key::Quote },
    { kVK_Return, boom::Key::Return },
    { kVK_RightOption, boom::Key::RightAlt },
    { kVK_RightControl, boom::Key::RightControl },
    { kVK_RightShift, boom::Key::RightShift },
    { kVK_ANSI_Semicolon, boom::Key::Semicolon },
    { kVK_Shift, boom::Key::Shift },
    { kVK_ANSI_Slash, boom::Key::Slash },
    { kVK_Space, boom::Key::Space },
    { kVK_Tab, boom::Key::Tab },
    { kVK_VolumeDown, boom::Key::VolumeDown },
    { kVK_VolumeUp, boom::Key::VolumeUp },
    { kVK_ANSI_KeypadClear, boom::Key::KeypadClear },
    { kVK_ANSI_KeypadDecimal, boom::Key::KeypadDecimal },
    { kVK_ANSI_KeypadDivide, boom::Key::KeypadDivide },
    { kVK_ANSI_KeypadEnter, boom::Key::KeypadEnter },
    { kVK_ANSI_KeypadEquals, boom::Key::KeypadEqual },
    { kVK_ANSI_KeypadMinus, boom::Key::KeypadMinus },
    { kVK_ANSI_KeypadMultiply, boom::Key::KeypadMultiply },
    { kVK_ANSI_KeypadPlus, boom::Key::KeypadPlus },
    { kVK_ANSI_Keypad0, boom::Key::Keypad0 },
    { kVK_ANSI_Keypad1, boom::Key::Keypad1 },
    { kVK_ANSI_Keypad2, boom::Key::Keypad2 },
    { kVK_ANSI_Keypad3, boom::Key::Keypad3 },
    { kVK_ANSI_Keypad4, boom::Key::Keypad4 },
    { kVK_ANSI_Keypad5, boom::Key::Keypad5 },
    { kVK_ANSI_Keypad6, boom::Key::Keypad6 },
    { kVK_ANSI_Keypad7, boom::Key::Keypad7 },
    { kVK_ANSI_Keypad8, boom::Key::Keypad8 },
    { kVK_ANSI_Keypad9, boom::Key::Keypad9 }
});

boom::Key __key_convert(std::int32_t code) {
    if (__key_map.find(code) != __key_map.end()) {
        return __key_map.at(code);
    } else {
        return boom::Key::Unknown;
    }
}

@implementation __Window {
    void(^_onShow)(void);
    void(^_onHide)(void);
    void(^_onClose)(void);
    void(^_onMaximize)(void);
    void(^_onMinimize)(void);
    void(^_onDemaximize)(void);
    void(^_onDeminimize)(void);
    void(^_onSize)(boom::Vec2);
    void(^_onMouseMove)(boom::Vec2, boom::KeyModifiers);
    void(^_onLButtonDown)(boom::Vec2, boom::KeyModifiers);
    void(^_onLButtonUp)(boom::Vec2, boom::KeyModifiers);
    void(^_onRButtonDown)(boom::Vec2, boom::KeyModifiers);
    void(^_onRButtonUp)(boom::Vec2, boom::KeyModifiers);
    void(^_onKeyDown)(boom::Key, boom::KeyModifiers, char const*);
    void(^_onKeyUp)(boom::Key, boom::KeyModifiers, char const*);
    void(^_onPixelratio)(double);
}

- (id)initWithIsPopup:(bool)isPopup
               onShow:(void(^)(void))onShow
               onHide:(void(^)(void))onHide
              onClose:(void(^)(void))onClose
           onMaximize:(void(^)(void))onMaximize
           onMinimize:(void(^)(void))onMinimize
         onDemaximize:(void(^)(void))onDemaximize
         onDeminimize:(void(^)(void))onDeminimize
               onSize:(void(^)(boom::Vec2))onSize
          onMouseMove:(void(^)(boom::Vec2, boom::KeyModifiers))onMouseMove
        onLButtonDown:(void(^)(boom::Vec2, boom::KeyModifiers))onLButtonDown
          onLButtonUp:(void(^)(boom::Vec2, boom::KeyModifiers))onLButtonUp
        onRButtonDown:(void(^)(boom::Vec2, boom::KeyModifiers))onRButtonDown
          onRButtonUp:(void(^)(boom::Vec2, boom::KeyModifiers))onRButtonUp
            onKeyDown:(void(^)(boom::Key, boom::KeyModifiers, char const*))onKeyDown
              onKeyUp:(void(^)(boom::Key, boom::KeyModifiers, char const*))onKeyUp
         onPixelRatio:(void(^)(double))onPixelratio {
    self = [super init];
    if (isPopup) {
        [self setLevel: NSFloatingWindowLevel];
        [self setStyleMask: NSWindowStyleMaskBorderless];
        [self setBackgroundColor: [NSColor clearColor]];
        [self setHasShadow: YES];
        [self setOpaque: NO];
    } else {
        [self setStyleMask: NSWindowStyleMaskTitled];
    }
    if (self) {
        _onShow = onShow;
        _onHide = onHide;
        _onClose = onClose;
        _onMaximize = onMaximize;
        _onMinimize = onMinimize;
        _onDemaximize = onDemaximize;
        _onDeminimize = onDeminimize;
        _onSize = onSize;
        _onMouseMove = onMouseMove;
        _onLButtonDown = onLButtonDown;
        _onLButtonUp = onLButtonUp;
        _onRButtonDown = onRButtonDown;
        _onRButtonUp = onRButtonUp;
        _onKeyDown = onKeyDown;
        _onKeyUp = onKeyUp;
        _onPixelratio = onPixelratio;
        [self setDelegate: self];
    }
    return self;
}

- (void)mouseDown:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onLButtonDown({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)rightMouseDown:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onRButtonDown({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)otherMouseDown:(NSEvent*)event {
    /* */
}

- (void)mouseUp:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onLButtonUp({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)rightMouseUp:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onRButtonUp({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)otherMouseUp:(NSEvent*)event {
    /* */
}

- (void)mouseMoved:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onMouseMove({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)mouseDragged:(NSEvent*)event {
    NSPoint point = [event locationInWindow];
    self->_onMouseMove({
        static_cast<float>(point.x),
        static_cast<float>(self.contentView.frame.size.height - point.y)
    }, {
        .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
        .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
        .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
        .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption))
    });
}

- (void)scrollWheel:(NSEvent*)event {
    /* */
}

- (void)rightMouseDragged:(NSEvent*)event {
    /* */
}

- (void)otherMouseDragged:(NSEvent*)event {
    /* */
}

- (void)mouseEntered:(NSEvent*)event {
    /* */
}

- (void)mouseExited:(NSEvent*)event {
    /* */
}

- (void)keyDown:(NSEvent*)event {
    self->_onKeyDown(
        __key_convert(event.keyCode),
        { .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
          .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
          .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
          .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption)) },
        (event.characters != NULL)
            ? [event.characters cStringUsingEncoding: NSUTF8StringEncoding]
            : ""
    );
}

- (void)keyUp:(NSEvent*)event {
    self->_onKeyUp(
        __key_convert(event.keyCode),
        { .control = static_cast<bool>((event.modifierFlags & NSEventModifierFlagControl)),
          .shift = static_cast<bool>((event.modifierFlags & NSEventModifierFlagShift)),
          .meta = static_cast<bool>((event.modifierFlags & NSEventModifierFlagCommand)),
          .alt = static_cast<bool>((event.modifierFlags & NSEventModifierFlagOption)) },
        (event.characters != NULL)
            ? [event.characters cStringUsingEncoding: NSUTF8StringEncoding]
            : ""
    );
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    self->_onClose();
    return false;
}

- (void)windowWillClose:(NSWindow *)sender {
    self->_onHide();
}

- (void)windowDidResize:(NSNotification*)notification {
    self->_onSize({
        static_cast<float>(self.contentView.frame.size.width),
        static_cast<float>(self.contentView.frame.size.height)
    });
}

- (void)windowDidMiniaturize:(NSNotification*)notification {
    self->_onMinimize();
}

- (void)windowDidDeminiaturize:(NSNotification*)notification {
    self->_onDeminimize();
}

- (void)windowDidEnterFullScreen:(NSNotification*)notification {
    self->_onMaximize();
}

- (void)windowDidExitFullScreen:(NSNotification*)notification {
    self->_onDemaximize();
}

- (void)windowDidChangeBackingProperties:(NSNotification*)notification {
    self->_onPixelratio(self.backingScaleFactor);
    self->_onSize({
        static_cast<float>(self.contentView.frame.size.width),
        static_cast<float>(self.contentView.frame.size.height)
    });
}

@end

namespace boom {

void Window::_implDone() {
    [_impl->window setReleasedWhenClosed: NO];
    [_impl->window close];
    _impl->window = nil;
    delete _impl;
}

void Window::_implInit() {
    _impl = new __WindowImpl{ .window = nil };
    _impl->window = [[__Window alloc]
        initWithIsPopup: false
                 onShow: ^() { _show(); }
                 onHide: ^() { _hide(); }
                onClose: ^() { _close(); }
             onMaximize: ^() { _maximize(); }
             onMinimize: ^() { _minimize(); }
           onDemaximize: ^() { _demaximize(); }
           onDeminimize: ^() { _deminimize(); }
                 onSize: ^(boom::Vec2 size) { _resize(size); }
            onMouseMove: ^(boom::Vec2 point, boom::KeyModifiers mods) { _mouseMove(point, mods); }
          onLButtonDown: ^(boom::Vec2 point, boom::KeyModifiers mods) { _lButtonDown(point, mods); }
            onLButtonUp: ^(boom::Vec2 point, boom::KeyModifiers mods) { _lButtonUp(point, mods); }
          onRButtonDown: ^(boom::Vec2 point, boom::KeyModifiers mods) { _rButtonDown(point, mods); }
            onRButtonUp: ^(boom::Vec2 point, boom::KeyModifiers mods) { _rButtonUp(point, mods); }
              onKeyDown: ^(boom::Key key, boom::KeyModifiers mods, char const* input) { _keyDown(key, mods, std::string(input)); }
                onKeyUp: ^(boom::Key key, boom::KeyModifiers mods, char const* input) { _keyUp(key, mods, std::string(input)); }
           onPixelRatio: ^(double pixelratio) { _pixelratio({ static_cast<float>(pixelratio), static_cast<float>(pixelratio) }); }];
    [_impl->window setReleasedWhenClosed: NO];
    [_impl->window setAcceptsMouseMovedEvents: YES];
}

boom::Vec2 Window::_implPixelratio() const {
    return {
        static_cast<float>(_impl->window.backingScaleFactor),
        static_cast<float>(_impl->window.backingScaleFactor)
    };
}

boom::Vec2 Window::_implSize() const {
    return {
        static_cast<float>(_impl->window.contentView.frame.size.width),
        static_cast<float>(_impl->window.contentView.frame.size.height)
    };
}

bool Window::_implVisible() const {
    return _impl->window.visible;
}

bool Window::_implClosable() const {
    return (_impl->window.styleMask & NSWindowStyleMaskClosable);
}

bool Window::_implSizable() const {
    return (_impl->window.styleMask & NSWindowStyleMaskResizable);
}

bool Window::_implMaximizable() const {
    return (_impl->window.styleMask & NSWindowStyleMaskResizable);
}

bool Window::_implMinimizable() const {
    return (_impl->window.styleMask & NSWindowStyleMaskMiniaturizable);
}

bool Window::_implMaximized() const {
    return (_impl->window.styleMask & NSWindowStyleMaskFullScreen);
}

bool Window::_implMinimized() const {
    return _impl->window.miniaturized;
}

bool Window::_implTopmost() const {
    return (_impl->window.level == NSStatusWindowLevel);
}

void Window::_implCenter() const {
    [_impl->window center];
}

void Window::_implSetTitle(std::string const& title) {
    [_impl->window setTitle: [NSString stringWithUTF8String: title.c_str()]];
}

void Window::_implSetPosition(boom::Vec2 position) {
    ;
}

void Window::_implSetSize(boom::Vec2 size) {
    NSRect rect = _impl->window.frame;
    rect.size.width = size.width;
    rect.size.height = size.height + (_impl->window.frame.size.height
                                     - [_impl->window contentRectForFrameRect:
                                            _impl->window.frame].size.height);
    [_impl->window setFrame: rect display: YES];
}

void Window::_implSetVisible(bool visible) {
    if (visible) {
        if (!_impl->window.visible) {
            [_impl->window makeKeyAndOrderFront: nil];
            [_impl->window makeFirstResponder: _impl->window.contentView];
            _show();
        }
    } else {
        if (_impl->window.visible) {
            [_impl->window close];
            _hide();
        }
    }
}

void Window::_implSetClosable(bool closable) {
    if (closable != (bool)(_impl->window.styleMask & NSWindowStyleMaskClosable)) {
        if (closable) {
            _impl->window.styleMask |= NSWindowStyleMaskClosable;
        } else {
            _impl->window.styleMask &= ~NSWindowStyleMaskClosable;
        }
    }
}

void Window::_implSetSizable(bool sizable) {
    if (sizable != (bool)(_impl->window.styleMask & NSWindowStyleMaskResizable)) {
        if (sizable) {
            _impl->window.styleMask |= NSWindowStyleMaskResizable;
        } else {
            _impl->window.styleMask &= ~NSWindowStyleMaskResizable;
        }
    }
}

void Window::_implSetMaximizable(bool maximizable) {
    if (maximizable != (bool)(_impl->window.styleMask & NSWindowStyleMaskResizable)) {
        if (maximizable) {
            _impl->window.styleMask |= NSWindowStyleMaskResizable;
        } else {
            _impl->window.styleMask &= ~NSWindowStyleMaskResizable;
        }
    }
}

void Window::_implSetMinimizable(bool minimizable) {
    if (minimizable != (bool)(_impl->window.styleMask & NSWindowStyleMaskMiniaturizable)) {
        if (minimizable) {
            _impl->window.styleMask |= NSWindowStyleMaskMiniaturizable;
        } else {
            _impl->window.styleMask &= ~NSWindowStyleMaskMiniaturizable;
        }
    }
}

void Window::_implSetMaximized(bool maximized) {
    if (maximized != (bool)(_impl->window.styleMask & NSWindowStyleMaskFullScreen)) {
        [_impl->window toggleFullScreen: _impl->window];
    }
}

void Window::_implSetMinimized(bool minimized) {
    if (minimized != _impl->window.miniaturized) {
        if (minimized) {
            [_impl->window miniaturize: nil];
        } else {
            [_impl->window deminiaturize: nil];
        }
    }
}

void Window::_implSetTopmost(bool topmost) {
    [_impl->window setLevel: topmost ? NSStatusWindowLevel : NSNormalWindowLevel];
}

} /* namespace boom */
