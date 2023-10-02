#include <map>
#include <CoreGraphics/CoreGraphics.h>
#include <Boom/Input.hpp>

namespace boom {

std::string const& KeyName(boom::Key key) {
    static auto const UNKNOWN = std::string("Unknown");
    static auto const MAPPING = std::map<boom::Key, std::string>({
        { boom::Key::Unknown, "Unknown" },
        { boom::Key::_0, "_0" },
        { boom::Key::_1, "_1" },
        { boom::Key::_2, "_2" },
        { boom::Key::_3, "_3" },
        { boom::Key::_4, "_4" },
        { boom::Key::_5, "_5" },
        { boom::Key::_6, "_6" },
        { boom::Key::_7, "_7" },
        { boom::Key::_8, "_8" },
        { boom::Key::_9, "_9" },
        { boom::Key::A, "A" },
        { boom::Key::B, "B" },
        { boom::Key::C, "C" },
        { boom::Key::D, "D" },
        { boom::Key::E, "E" },
        { boom::Key::F, "F" },
        { boom::Key::G, "G" },
        { boom::Key::H, "H" },
        { boom::Key::I, "I" },
        { boom::Key::J, "J" },
        { boom::Key::K, "K" },
        { boom::Key::L, "L" },
        { boom::Key::M, "M" },
        { boom::Key::N, "N" },
        { boom::Key::O, "O" },
        { boom::Key::P, "P" },
        { boom::Key::Q, "Q" },
        { boom::Key::R, "R" },
        { boom::Key::S, "S" },
        { boom::Key::T, "T" },
        { boom::Key::U, "U" },
        { boom::Key::V, "V" },
        { boom::Key::W, "W" },
        { boom::Key::X, "X" },
        { boom::Key::Y, "Y" },
        { boom::Key::Z, "Z" },
        { boom::Key::F1, "F1" },
        { boom::Key::F2, "F2" },
        { boom::Key::F3, "F3" },
        { boom::Key::F4, "F4" },
        { boom::Key::F5, "F5" },
        { boom::Key::F6, "F6" },
        { boom::Key::F7, "F7" },
        { boom::Key::F8, "F8" },
        { boom::Key::F9, "F9" },
        { boom::Key::F10, "F10" },
        { boom::Key::F11, "F11" },
        { boom::Key::F12, "F12" },
        { boom::Key::F13, "F13" },
        { boom::Key::F14, "F14" },
        { boom::Key::F15, "F15" },
        { boom::Key::F16, "F16" },
        { boom::Key::F17, "F17" },
        { boom::Key::F18, "F18" },
        { boom::Key::F19, "F19" },
        { boom::Key::F20, "F20" },
        { boom::Key::Alt, "Alt" },
        { boom::Key::ArrowDown, "ArrowDown" },
        { boom::Key::ArrowLeft, "ArrowLeft" },
        { boom::Key::ArrowRight, "ArrowRight" },
        { boom::Key::ArrowUp, "ArrowUp" },
        { boom::Key::Backslash, "Backslash" },
        { boom::Key::Backspace, "Backspace" },
        { boom::Key::BracketLeft, "BracketLeft" },
        { boom::Key::BracketRight, "BracketRight" },
        { boom::Key::Capslock, "Capslock" },
        { boom::Key::Comma, "Comma" },
        { boom::Key::Control, "Control" },
        { boom::Key::End, "End" },
        { boom::Key::Equal, "Equal" },
        { boom::Key::Escape, "Escape" },
        { boom::Key::ForwardDelete, "ForwardDelete" },
        { boom::Key::Function, "Function" },
        { boom::Key::Grave, "Grave" },
        { boom::Key::Help, "Help" },
        { boom::Key::Home, "Home" },
        { boom::Key::Meta, "Meta" },
        { boom::Key::Minus, "Minus" },
        { boom::Key::Mute, "Mute" },
        { boom::Key::PageDown, "PageDown" },
        { boom::Key::PageUp, "PageUp" },
        { boom::Key::Period, "Period" },
        { boom::Key::Quote, "Quote" },
        { boom::Key::Return, "Return" },
        { boom::Key::RightAlt, "RightAlt" },
        { boom::Key::RightControl, "RightControl" },
        { boom::Key::RightShift, "RightShift" },
        { boom::Key::Semicolon, "Semicolon" },
        { boom::Key::Shift, "Shift" },
        { boom::Key::Slash, "Slash" },
        { boom::Key::Space, "Space" },
        { boom::Key::Tab, "Tab" },
        { boom::Key::VolumeDown, "VolumeDown" },
        { boom::Key::VolumeUp, "VolumeUp" },
        { boom::Key::KeypadClear, "KeypadClear" },
        { boom::Key::KeypadDecimal, "KeypadDecimal" },
        { boom::Key::KeypadDivide, "KeypadDivide" },
        { boom::Key::KeypadEnter, "KeypadEnter" },
        { boom::Key::KeypadEqual, "KeypadEqual" },
        { boom::Key::KeypadMinus, "KeypadMinus" },
        { boom::Key::KeypadMultiply, "KeypadMultiply" },
        { boom::Key::KeypadPlus, "KeypadPlus" },
        { boom::Key::Keypad0, "Keypad0" },
        { boom::Key::Keypad1, "Keypad1" },
        { boom::Key::Keypad2, "Keypad2" },
        { boom::Key::Keypad3, "Keypad3" },
        { boom::Key::Keypad4, "Keypad4" },
        { boom::Key::Keypad5, "Keypad5" },
        { boom::Key::Keypad6, "Keypad6" },
        { boom::Key::Keypad7, "Keypad7" },
        { boom::Key::Keypad8, "Keypad8" },
        { boom::Key::Keypad9, "Keypad9" }
    });
    auto pos = MAPPING.find(key);
    if (pos != MAPPING.end()) {
        return pos->second;
    } else {
        return UNKNOWN;
    }

}

boom::Vec2 MousePosition() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint point = CGEventGetLocation(event);
    return {
        static_cast<float>(point.x),
        static_cast<float>(point.y)
    };
}

} /* namespace boom */
