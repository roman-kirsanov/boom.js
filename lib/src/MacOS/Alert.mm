#include <vector>
#include <functional>
#include <Cocoa/Cocoa.h>
#include <Boom/Alert.hpp>

namespace boom {

struct __AlertImpl {
    NSAlert* alert;
};

void Alert::_implInit() {
    _impl = new boom::__AlertImpl{
        .alert = [[NSAlert alloc] init]
    };
    [_impl->alert setIcon: [NSImage imageNamed: NSImageNameInfo]];
}

void Alert::_implDone() {
    delete _impl;
}

void Alert::_implSetType(boom::AlertType type) {
    if (type == boom::AlertType::Information) {
        [_impl->alert setIcon: [NSImage imageNamed: NSImageNameInfo]];
    } else if (type == boom::AlertType::Warning) {
        [_impl->alert setIcon: [NSImage imageNamed: NSImageNameCaution]];
    } else if (type == boom::AlertType::Error) {
        [_impl->alert setIcon: [NSImage imageNamed: NSImageNameCaution]];
    }
}

void Alert::_implSetTitle(std::string const& title) {
    [_impl->alert setInformativeText: [NSString stringWithCString: title.c_str() encoding: NSUTF8StringEncoding]];
}

void Alert::_implSetText(std::string const& text) {
    [_impl->alert setMessageText: [NSString stringWithCString: text.c_str() encoding: NSUTF8StringEncoding]];
}

void Alert::_implAddButton(std::string const& title, boom::AlertButtonType const& type) {
    auto button = [_impl->alert addButtonWithTitle: [NSString stringWithCString: title.c_str() encoding: NSUTF8StringEncoding]];
    if (type == boom::AlertButtonType::Default) {
        [button setKeyEquivalent: @"\r"];
    } else if (type == boom::AlertButtonType::Cancel) {
        [button setKeyEquivalent: @"\033"];
    } else {
        [button setKeyEquivalent: @""];
    }
}

int Alert::_implShow() {
    auto const result = [_impl->alert runModal];
    auto const index = (result - NSAlertFirstButtonReturn);
    return index;
}

} /* namespace boom */

