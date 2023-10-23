#include <functional>
#include <Cocoa/Cocoa.h>
#include <Boom/Menu.hpp>

using NSMenuItemOnClickHandler = std::function<void()>;

@interface __MenuItem : NSMenuItem

- (id)init;
- (void)setOnClick:(NSMenuItemOnClickHandler)handler;

@end

@implementation __MenuItem {
    NSMenuItemOnClickHandler _onClick;
}

- (id)init {
    self = [super init];
    if (self) {
        _onClick = [](){};
        [self setTarget: self];
        [self setAction: @selector(onClick)];
    }
    return self;
}

- (void)onClick {
    _onClick();
}

- (void)setOnClick: (NSMenuItemOnClickHandler)handler {
    _onClick = handler;
}

@end

namespace boom {

struct __MenuItemImpl {
    __MenuItem* menuItem;
};

struct __MenuImpl {
    NSMenu* menu;
};

void MenuItem::_implInit() {
    _impl = new boom::__MenuItemImpl{
        .menuItem = nil
    };
    _impl->menuItem = [[__MenuItem alloc] init];
    [_impl->menuItem setOnClick: [this]() { _emitClick(); }];
}

void MenuItem::_implDone() {
    _impl->menuItem = nil;
    delete _impl;
}

void MenuItem::_implSetTitle(std::string const& title) {
    if (_separator == false) {
        [_impl->menuItem setTitle: [NSString stringWithUTF8String: title.c_str()]];
    }
}

void MenuItem::_implSetSubmenu(std::shared_ptr<boom::Menu> submenu) {
    if (_separator == false) {
        if (submenu != nullptr) {
            [_impl->menuItem setSubmenu: submenu->_impl->menu];
        } else {
            [_impl->menuItem setSubmenu: nil];
        }
    }
}

void MenuItem::_implSetSeparator(bool separator) {

    // TODO: if item is about to recreate but it's already attached to a menu - handle it!

    if (separator) {
        _impl->menuItem = nil;
        _impl->menuItem = (__MenuItem*)[NSMenuItem separatorItem];
    } else {
        _impl->menuItem = nil;
        _impl->menuItem = [[__MenuItem alloc] init];
        [_impl->menuItem setTitle: [NSString stringWithUTF8String: _title.c_str()]];
        [_impl->menuItem setOnClick: [this](){ _emitClick(); }];
        if (_submenu) {
            [_impl->menuItem setSubmenu: _submenu->_impl->menu];
        }
    }
}

void MenuItem::_implSetDisabled(bool disabled) {
    if (_separator == false) {
        [_impl->menuItem setEnabled: !disabled];
    }
}

void Menu::_implInit() {
    _impl = new boom::__MenuImpl{
        .menu = nil
    };
    _impl->menu = [[NSMenu alloc] init];
}

void Menu::_implDone() {
    _impl->menu = nil;
    delete _impl;
}

void Menu::_implAddItem(std::shared_ptr<boom::MenuItem> menuItem) {
    assert(menuItem != nullptr);
    [_impl->menu addItem: menuItem->_impl->menuItem];
}

void Menu::_implRemoveItem(std::shared_ptr<boom::MenuItem> menuItem) {
    assert(menuItem != nullptr);
    [_impl->menu removeItem: menuItem->_impl->menuItem];
}

void Menu::_implPopup(boom::Vec2 point) const {
    NSScreen* screen = [[NSApplication sharedApplication] keyWindow].screen;
    if (screen) {
        NSPoint position = {
            .x = point.x,
            .y = (screen.frame.size.height - point.y)
        };
        [_impl->menu popUpMenuPositioningItem: nil atLocation: position inView: nil];
    }
}

} /* namespace boom */
