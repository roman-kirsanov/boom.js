#pragma once

#include <string>
#include <Boom/Math.hpp>
#include <Boom/Input.hpp>
#include <Boom/Emitter.hpp>
#include <Boom/View.hpp>

namespace boom {

struct __WindowImpl;

class OpenGL;
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
    std::string const& title() const;
    boom::Vec2 pixelratio() const;
    boom::Vec2 position() const;
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
    void setView(std::shared_ptr<boom::View>);
    virtual ~Window();
protected:
    virtual void _onShow() {};
    virtual void _onHide() {};
    virtual void _onClose() {};
    virtual void _onResize() {};
    virtual void _onMaximize() {};
    virtual void _onMinimize() {};
    virtual void _onDemaximize() {};
    virtual void _onDeminimize() {};
    virtual void _onPixelratio() {};
private:
    std::string _title;
    boom::__WindowImpl* _impl;
    void _show();
    void _hide();
    void _close();
    void _resize(boom::Vec2);
    void _maximize();
    void _minimize();
    void _demaximize();
    void _deminimize();
    void _pixelratio(boom::Vec2);
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
};

} /* namespace boom */
