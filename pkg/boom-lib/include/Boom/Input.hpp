#pragma once

#include <string>
#include <Boom/Math.hpp>

namespace boom {

enum class Key {
    Unknown,
    _0,
    _1,
    _2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    Alt,
    ArrowDown,
    ArrowLeft,
    ArrowRight,
    ArrowUp,
    Backslash,
    Backspace,
    BracketLeft,
    BracketRight,
    Capslock,
    Comma,
    Control,
    End,
    Equal,
    Escape,
    ForwardDelete,
    Function,
    Grave,
    Help,
    Home,
    Meta,
    Minus,
    Mute,
    PageDown,
    PageUp,
    Period,
    Quote,
    Return,
    RightAlt,
    RightControl,
    RightShift,
    Semicolon,
    Shift,
    Slash,
    Space,
    Tab,
    VolumeDown,
    VolumeUp,
    KeypadClear,
    KeypadDecimal,
    KeypadDivide,
    KeypadEnter,
    KeypadEqual,
    KeypadMinus,
    KeypadMultiply,
    KeypadPlus,
    Keypad0,
    Keypad1,
    Keypad2,
    Keypad3,
    Keypad4,
    Keypad5,
    Keypad6,
    Keypad7,
    Keypad8,
    Keypad9
};

struct KeyModifiers {
    bool control;
    bool shift;
    bool meta;
    bool alt;
};

std::string const& KeyName(boom::Key);

boom::Vec2 MousePosition();

} /* namespace boom */
