#pragma once

#include <Boom/Node.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

class ContentView : public boom::GraphicsView {
public:
    ContentView();
    boom::Vec2 viewport() const;
    boom::Transform const& container() const;
    std::shared_ptr<boom::Surface const> surface() const;
    void setViewport(boom::Vec2);
    void addChild(std::shared_ptr<boom::Node>);
    void removeChild(std::shared_ptr<boom::Node>);
    void insertChild(std::shared_ptr<boom::Node>, std::size_t);
    void replaceChild(std::shared_ptr<boom::Node>, std::shared_ptr<boom::Node>);
    virtual ~ContentView();
protected:
    virtual void _onRender() override;
    virtual void _onMouseWheel(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMouseMove(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onKeyDown(boom::Key, boom::KeyModifiers, std::string const&);
    virtual void _onKeyUp(boom::Key, boom::KeyModifiers, std::string const&);
private:
    std::vector<std::shared_ptr<boom::Node>> _children;
    std::vector<std::shared_ptr<boom::Node>> _hoverPath;
    std::vector<std::shared_ptr<boom::Node>> _activePath;
    std::vector<std::function<void()>> _async;
    std::shared_ptr<boom::Image> _texture;
    std::shared_ptr<boom::Surface> _surface;
    boom::Vec2 _viewport;
    boom::Transform _container;
    bool _propagation;
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
    void _update();
};

} /* namespace boom */