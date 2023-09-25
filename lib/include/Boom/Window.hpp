#pragma once

#include <string>
#include <Boom/Node.hpp>
#include <Boom/Math.hpp>
#include <Boom/Input.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

struct __WindowImpl;

class Surface;

class Window final : public boom::Shared {
public:
    Window();
    boom::Emitter<> onShow;
    boom::Emitter<> onHide;
    boom::Emitter<> onClose;
    boom::Emitter<> onResize;
    boom::Emitter<> onMaximize;
    boom::Emitter<> onMinimize;
    boom::Emitter<> onDemaximize;
    boom::Emitter<> onDeminimize;
    boom::Emitter<> onPixelratio;
    boom::Emitter<> onRender;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseMove;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseEnter;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseExit;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseWheel;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onMouseClick;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onLButtonDown;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onRButtonDown;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onLButtonUp;
    boom::Emitter<boom::Vec2, boom::KeyModifiers> onRButtonUp;
    boom::Emitter<boom::Key, boom::KeyModifiers, std::string const&> onKeyDown;
    boom::Emitter<boom::Key, boom::KeyModifiers, std::string const&> onKeyUp;
    std::shared_ptr<boom::Surface const> surface() const;
    boom::Transform const& container() const;
    std::string const& title() const;
    boom::Vec2 pixelratio() const;
    boom::Vec2 viewport() const;
    boom::Vec2 size() const;
    bool visible() const;
    bool closable() const;
    bool sizable() const;
    bool maximizable() const;
    bool minimizable() const;
    bool maximized() const;
    bool minimized() const;
    bool topmost() const;
    void center() const;
    void setPosition(boom::Vec2);
    void setViewport(boom::Vec2);
    void setSize(boom::Vec2);
    void setTitle(std::string const&);
    void setVisible(bool);
    void setClosable(bool);
    void setSizable(bool);
    void setMaximizable(bool);
    void setMinimizable(bool);
    void setMaximized(bool);
    void setMinimized(bool);
    void setTopmost(bool);
    void addChild(std::shared_ptr<boom::Node>);
    void removeChild(std::shared_ptr<boom::Node>);
    void insertChild(std::shared_ptr<boom::Node>, std::size_t);
    void replaceChild(std::shared_ptr<boom::Node>, std::shared_ptr<boom::Node>);
    virtual ~Window();
protected:
    virtual void _onReady() override;
    virtual void _onShow() {};
    virtual void _onHide() {};
    virtual void _onClose() {};
    virtual void _onResize() {};
    virtual void _onMaximize() {};
    virtual void _onMinimize() {};
    virtual void _onDemaximize() {};
    virtual void _onDeminimize() {};
    virtual void _onPixelratio() {};
    virtual void _onRender() {};
    virtual void _onMouseMove(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseEnter(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseExit(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseWheel(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onMouseClick(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onLButtonDown(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onRButtonDown(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onLButtonUp(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onRButtonUp(boom::Vec2, boom::KeyModifiers) {};
    virtual void _onKeyDown(boom::Key, boom::KeyModifiers, std::string const&) {};
    virtual void _onKeyUp(boom::Key, boom::KeyModifiers, std::string const&) {};
private:
    std::string _title;
    std::int64_t _subscr;
    std::shared_ptr<boom::Surface> _surface;
    std::shared_ptr<boom::ImageBrush> _brush;
    std::shared_ptr<boom::Paint> _paint;
    std::vector<std::shared_ptr<boom::Node>> _children;
    std::vector<std::shared_ptr<boom::Node>> _hoverPath;
    std::vector<std::shared_ptr<boom::Node>> _activePath;
    std::vector<std::function<void()>> _async;
    std::shared_ptr<boom::Image> _viewportTexture;
    std::shared_ptr<boom::Surface> _viewportSurface;
    boom::Vec2 _viewport;
    boom::Transform _container;
    bool _propagation;
    boom::__WindowImpl* _impl;
    std::shared_ptr<boom::Node> _hitTest(boom::Vec2);
    std::shared_ptr<boom::Node> _hitTestNode(std::shared_ptr<boom::Node>, boom::Vec2);
    void _show();
    void _hide();
    void _close();
    void _resize(boom::Vec2);
    void _maximize();
    void _minimize();
    void _demaximize();
    void _deminimize();
    void _pixelratio(boom::Vec2);
    void _mouseWheel(boom::Vec2, boom::KeyModifiers);
    void _mouseMove(boom::Vec2, boom::KeyModifiers);
    void _lButtonDown(boom::Vec2, boom::KeyModifiers);
    void _rButtonDown(boom::Vec2, boom::KeyModifiers);
    void _lButtonUp(boom::Vec2, boom::KeyModifiers);
    void _rButtonUp(boom::Vec2, boom::KeyModifiers);
    void _keyDown(boom::Key, boom::KeyModifiers, std::string const&);
    void _keyUp(boom::Key, boom::KeyModifiers, std::string const&);
    void _update();
    void _render();
    void _implInit();
    void _implDone();
    boom::Vec2 _implPixelratio() const;
    boom::Vec2 _implSize() const;
    bool _implVisible() const;
    bool _implClosable() const;
    bool _implSizable() const;
    bool _implMaximizable() const;
    bool _implMinimizable() const;
    bool _implMaximized() const;
    bool _implMinimized() const;
    bool _implTopmost() const;
    void _implCenter() const;
    void _implSetPosition(boom::Vec2);
    void _implSetSize(boom::Vec2);
    void _implSetTitle(std::string const&);
    void _implSetVisible(bool);
    void _implSetClosable(bool);
    void _implSetSizable(bool);
    void _implSetMaximizable(bool);
    void _implSetMinimizable(bool);
    void _implSetMaximized(bool);
    void _implSetMinimized(bool);
    void _implSetTopmost(bool);
    friend boom::Surface;
};

} /* namespace boom */
