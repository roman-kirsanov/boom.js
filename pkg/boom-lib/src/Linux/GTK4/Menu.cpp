#include <cassert>
#include <functional>
#include <Boom/Menu.hpp>

namespace boom {

struct __MenuItemImpl {
    ;
};

struct __MenuImpl {
    ;
};

void MenuItem::_implInit() {
    _impl = new boom::__MenuItemImpl{};
    ;
}

void MenuItem::_implDone() {
    ;
    delete _impl;
}

void MenuItem::_implSetTitle(std::string const& title) {
    if (_separator == false) {
        ;
    }
}

void MenuItem::_implSetSubmenu(std::shared_ptr<boom::Menu> submenu) {
    if (_separator == false) {
        if (submenu != nullptr) {
            ;
        } else {
            ;
        }
    }
}

void MenuItem::_implSetSeparator(bool separator) {
    if (separator) {
        ;
    } else {
        ;
        if (_submenu) {
            ;
        }
    }
}

void MenuItem::_implSetDisabled(bool disabled) {
    if (_separator == false) {
        ;
    }
}

void Menu::_implInit() {
    _impl = new boom::__MenuImpl{};
    ;
}

void Menu::_implDone() {
    ;
    delete _impl;
}

void Menu::_implAddItem(std::shared_ptr<boom::MenuItem> menuItem) {
    assert(menuItem != nullptr);
    ;
}

void Menu::_implRemoveItem(std::shared_ptr<boom::MenuItem> menuItem) {
    assert(menuItem != nullptr);
    ;
}

void Menu::_implPopup(boom::Vec2 point) const {
    ;
}

} /* namespace boom */
