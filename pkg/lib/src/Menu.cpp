#include <Boom/Menu.hpp>

namespace boom {

MenuItem::~MenuItem() {
    _implDone();
}

MenuItem::MenuItem()
    : boom::Object()
    , onClick()
    , _title()
    , _submenu()
    , _impl(nullptr)
    , _separator(false)
    , _disabled(false)
{
    _implInit();
}

std::string const& MenuItem::title() const {
    return _title;
}

boom::MenuRef MenuItem::submenu() const {
    return _submenu;
}

bool MenuItem::separator() const {
    return _separator;
}

bool MenuItem::disabled() const {
    return _disabled;
}

void MenuItem::setTitle(std::string const& title) {
    _title = title;
    _implSetTitle(title);
}

void MenuItem::setSubmenu(boom::MenuRef submenu) {
    _submenu = submenu;
    _implSetSubmenu(submenu);
}

void MenuItem::setSeparator(bool separator) {
    _separator = separator;
    _implSetSeparator(separator);
}

void MenuItem::setDisabled(bool disabled) {
    _disabled = disabled;
    _implSetDisabled(disabled);
}

void MenuItem::_click() {
    _onClick();
    onClick.emit(boom::GetShared<boom::MenuItem>(this));
}

Menu::~Menu() {
    _implDone();
}

Menu::Menu()
    : boom::Object()
    , onShow()
    , onHide()
    , _items()
    , _impl(nullptr)
{
    _implInit();
}

std::vector<boom::MenuItemRef> const& Menu::items() const {
    return _items;
}

void Menu::addItem(boom::MenuItemRef menuItem) {
    _items.push_back(menuItem);
    _implAddItem(menuItem);
}

void Menu::removeItem(boom::MenuItemRef menuItem) {
    auto pos = std::find(_items.begin(), _items.end(), menuItem);
    if (pos != _items.end()) {
        _items.erase(pos);
        _implRemoveItem(menuItem);
    }
}

void Menu::popup(boom::Vec2 point) const {
    _implPopup(point);
}

void Menu::_show() {
    _onShow();
    onShow.emit(boom::GetShared<boom::Menu>(this));
}

void Menu::_hide() {
    _onHide();
    onHide.emit(boom::GetShared<boom::Menu>(this));
}

} /* namespace boom */
