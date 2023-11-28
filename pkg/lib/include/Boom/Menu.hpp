#pragma once

#include <string>
#include <vector>
#include <Boom/Math.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

struct __MenuItemImpl;
struct __MenuImpl;

class Menu;
class MenuItem;

using MenuRef = std::shared_ptr<boom::Menu>;
using MenuCRef = std::shared_ptr<boom::Menu const>;
using MenuItemRef = std::shared_ptr<boom::MenuItem>;
using MenuItemCRef = std::shared_ptr<boom::MenuItem const>;
using MenuWRef = std::weak_ptr<boom::Menu>;
using MenuCWRef = std::weak_ptr<boom::Menu const>;
using MenuWItemRef = std::weak_ptr<boom::MenuItem>;
using MenuWItemCRef = std::weak_ptr<boom::MenuItem const>;

class MenuItem final : public boom::Shared {
public:
    MenuItem();
    boom::Emitter<> onClick;
    std::string const& title() const;
    boom::MenuRef submenu() const;
    bool separator() const;
    bool disabled() const;
    void setTitle(std::string const&);
    void setSubmenu(boom::MenuRef);
    void setSeparator(bool);
    void setDisabled(bool);
    virtual ~MenuItem();
protected:
    virtual void _onClick() {};
private:
    std::string _title;
    boom::MenuRef _submenu;
    boom::__MenuItemImpl* _impl;
    bool _separator;
    bool _disabled;
    void _emitClick();
    void _implInit();
    void _implDone();
    void _implSetTitle(std::string const&);
    void _implSetSubmenu(boom::MenuRef);
    void _implSetSeparator(bool);
    void _implSetDisabled(bool);
    friend boom::Menu;
};

class Menu final : public boom::Shared {
public:
    Menu();
    boom::Emitter<> onShow;
    boom::Emitter<> onHide;
    std::vector<boom::MenuItemRef> const& items() const;
    void addItem(boom::MenuItemRef);
    void removeItem(boom::MenuItemRef);
    void popup(boom::Vec2) const;
    virtual ~Menu();
protected:
    virtual void _onShow() {};
    virtual void _onHide() {};
private:
    std::vector<boom::MenuItemRef> _items;
    boom::__MenuImpl* _impl;
    void _show();
    void _hide();
    void _implInit();
    void _implDone();
    void _implAddItem(boom::MenuItemRef);
    void _implRemoveItem(boom::MenuItemRef);
    void _implPopup(boom::Vec2) const;
    friend boom::MenuItem;
};

} /* namespace boom */
