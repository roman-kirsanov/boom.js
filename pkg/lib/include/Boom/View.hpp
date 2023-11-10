#pragma once

#include <string>
#include <vector>
#include <Boom/Math.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>
#include <Boom/Input.hpp>

namespace boom {

struct __ViewImpl;

class Window;
class OpenGL;

class View : public boom::Shared {
public:
    View();
    boom::Emitter<std::shared_ptr<boom::View>> onAttach;
    boom::Emitter<std::shared_ptr<boom::View>> onDetach;
    boom::Emitter<std::shared_ptr<boom::View>> onResize;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onMouseMove;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onMouseEnter;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onMouseExit;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onMouseWheel;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onMouseClick;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onLButtonDown;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onRButtonDown;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onLButtonUp;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Vec2, boom::KeyModifiers> onRButtonUp;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Key, boom::KeyModifiers, std::string const&> onKeyDown;
    boom::Emitter<std::shared_ptr<boom::View>, boom::Key, boom::KeyModifiers, std::string const&> onKeyUp;
    std::vector<std::shared_ptr<boom::View>> const& children() const;
    std::shared_ptr<boom::View> parent() const;
    boom::Vec2 position() const;
    boom::Vec2 size() const;
    void removeFromParent();
    void addChild(std::shared_ptr<boom::View>);
    void removeChild(std::shared_ptr<boom::View>);
    void replaceChild(std::shared_ptr<boom::View>, std::shared_ptr<boom::View>);
    void insertChild(std::shared_ptr<boom::View>, std::size_t);
    void setParent(std::shared_ptr<boom::View>);
    void setPosition(boom::Vec2);
    void setSize(boom::Vec2);
    virtual ~View();
protected:
    virtual void _onAttach() {};
    virtual void _onDetach() {};
    virtual void _onResize() {};
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
    bool _attaching;
    bool _detaching;
    bool _resizing;
    bool _windowView;
    std::shared_ptr<boom::View> _parent;
    std::vector<std::shared_ptr<boom::View>> _children;
    boom::__ViewImpl* _impl;
    void _attach();
    void _detach();
    void _resize();
    boom::Vec2 _implPosition() const;
    boom::Vec2 _implSize() const;
    void _implAddChild(std::shared_ptr<boom::View>);
    void _implRemoveChild(std::shared_ptr<boom::View>);
    void _implReplaceChild(std::shared_ptr<boom::View>, std::shared_ptr<boom::View>);
    void _implInsertChild(std::shared_ptr<boom::View>, std::size_t);
    void _implSetPosition(boom::Vec2);
    void _implSetSize(boom::Vec2);
    void _implInit();
    void _implDone();
#ifdef _WIN32
    static std::intptr_t _ImplViewProc(void*, std::uint32_t, std::uintptr_t, std::intptr_t);
#endif
    friend boom::OpenGL;
    friend boom::Window;
};

} /* namespace boom */