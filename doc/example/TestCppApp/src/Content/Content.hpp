#include <Boom.hpp>

namespace app {

class Content final : public boom::GraphicsView {
protected:
    virtual void _onReady() override;
    virtual void _onRender() override;
    virtual void _onMouseMove(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMouseEnter(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMouseExit(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMButtonDown(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onLButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onRButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onMButtonUp(boom::Vec2, boom::KeyModifiers) override;
    virtual void _onKeyDown(boom::Key, boom::KeyModifiers, std::string const&) override;
    virtual void _onKeyUp(boom::Key, boom::KeyModifiers, std::string const&) override;
protected:
    boom::Vec2 _position;
};

} /* namespace app */