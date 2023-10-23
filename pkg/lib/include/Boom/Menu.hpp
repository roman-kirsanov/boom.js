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

class MenuItem final : public boom::Shared {
public:
    MenuItem();
    boom::Emitter<> onClick;
    std::string const& title() const;
    std::shared_ptr<boom::Menu> submenu() const;
    bool separator() const;
    bool disabled() const;
    void setTitle(std::string const&);
    void setSubmenu(std::shared_ptr<boom::Menu>);
    void setSeparator(bool);
    void setDisabled(bool);
    virtual ~MenuItem();
protected:
    virtual void _onClick() {};
private:
    std::string _title;
    std::shared_ptr<boom::Menu> _submenu;
    boom::__MenuItemImpl* _impl;
    bool _separator;
    bool _disabled;
    void _emitClick();
    void _implInit();
    void _implDone();
    void _implSetTitle(std::string const&);
    void _implSetSubmenu(std::shared_ptr<boom::Menu>);
    void _implSetSeparator(bool);
    void _implSetDisabled(bool);
    friend boom::Menu;
};

class Menu final : public boom::Shared {
public:
    Menu();
    boom::Emitter<> onShow;
    boom::Emitter<> onHide;
    std::vector<std::shared_ptr<boom::MenuItem>> const& items() const;
    void addItem(std::shared_ptr<boom::MenuItem>);
    void removeItem(std::shared_ptr<boom::MenuItem>);
    void popup(boom::Vec2) const;
    virtual ~Menu();
protected:
    virtual void _onShow() {};
    virtual void _onHide() {};
private:
    std::vector<std::shared_ptr<boom::MenuItem>> _items;
    boom::__MenuImpl* _impl;
    void _show();
    void _hide();
    void _implInit();
    void _implDone();
    void _implAddItem(std::shared_ptr<boom::MenuItem>);
    void _implRemoveItem(std::shared_ptr<boom::MenuItem>);
    void _implPopup(boom::Vec2) const;
    friend boom::MenuItem;
};

} /* namespace boom */
