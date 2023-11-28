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
class View;

using ViewRef = std::shared_ptr<boom::View>;
using ViewCRef = std::shared_ptr<boom::View const>;

class View : public boom::Shared {
public:
    View();
    boom::Emitter<boom::ViewRef> onAttach;
    boom::Emitter<boom::ViewRef> onDetach;
    boom::Emitter<boom::ViewRef> onResize;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onMouseMove;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onMouseEnter;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onMouseExit;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onMouseWheel;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onMouseClick;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onLButtonDown;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onRButtonDown;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onLButtonUp;
    boom::Emitter<boom::ViewRef, boom::Vec2, boom::KeyModifiers> onRButtonUp;
    boom::Emitter<boom::ViewRef, boom::Key, boom::KeyModifiers, std::string const&> onKeyDown;
    boom::Emitter<boom::ViewRef, boom::Key, boom::KeyModifiers, std::string const&> onKeyUp;
    std::vector<boom::ViewRef> const& children() const;
    boom::ViewRef parent() const;
    boom::Vec2 position() const;
    boom::Vec2 size() const;
    void removeFromParent();
    void addChild(boom::ViewRef);
    void removeChild(boom::ViewRef);
    void replaceChild(boom::ViewRef, boom::ViewRef);
    void insertChild(boom::ViewRef, std::size_t);
    void setParent(boom::ViewRef);
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
    boom::ViewRef _parent;
    std::vector<boom::ViewRef> _children;
    boom::__ViewImpl* _impl;
    void _attach();
    void _detach();
    void _resize();
    boom::Vec2 _implPosition() const;
    boom::Vec2 _implSize() const;
    void _implAddChild(boom::ViewRef);
    void _implRemoveChild(boom::ViewRef);
    void _implReplaceChild(boom::ViewRef, boom::ViewRef);
    void _implInsertChild(boom::ViewRef, std::size_t);
    void _implSetPosition(boom::Vec2);
    void _implSetSize(boom::Vec2);
    void _implInit();
    void _implDone();
#ifdef _WIN32
    static std::intptr_t __stdcall _ImplViewProc(void*, std::uint32_t, std::uintptr_t, std::intptr_t);
#endif
    friend boom::OpenGL;
    friend boom::Window;
};

} /* namespace boom */