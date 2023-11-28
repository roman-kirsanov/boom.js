#pragma once

#include <Boom/Node.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

class ContentView;

using ContentViewRef = std::shared_ptr<boom::ContentView>;
using ContentViewCRef = std::shared_ptr<boom::ContentView const>;

class ContentView : public boom::GraphicsView {
public:
    ContentView();
    boom::Vec2 viewport() const;
    boom::Transform const& container() const;
    boom::SurfaceCRef surface() const;
    void setViewport(boom::Vec2);
    void addChild(boom::NodeRef);
    void removeChild(boom::NodeRef);
    void insertChild(boom::NodeRef, std::size_t);
    void replaceChild(boom::NodeRef, boom::NodeRef);
    virtual ~ContentView();
protected:
    virtual void _onRender() override;
    virtual void _onMouseWheel(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMouseMove(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onKeyDown(boom::Key, boom::KeyModifiers, std::string const&) override;
    virtual void _onKeyUp(boom::Key, boom::KeyModifiers, std::string const&) override;
private:
    std::vector<boom::NodeRef> _children;
    std::vector<boom::NodeRef> _hoverPath;
    std::vector<boom::NodeRef> _activePath;
    std::vector<std::function<void()>> _async;
    boom::ImageRef _texture;
    boom::SurfaceRef _surface;
    boom::Vec2 _viewport;
    boom::Transform _container;
    bool _propagation;
    boom::NodeRef _hitTest(boom::Vec2);
    boom::NodeRef _hitTestNode(boom::NodeRef, boom::Vec2);
    void _show();
    void _hide();
    void _close();
    void _resize(boom::Vec2);
    void _maximize();
    void _minimize();
    void _demaximize();
    void _deminimize();
    void _pixelratio(boom::Vec2);
    void _update();
};

} /* namespace boom */