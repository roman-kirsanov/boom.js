#include <Boom.hpp>

namespace app {

class Header final : public boom::GraphicsView {
protected:
    virtual void _onRender() override;
};

} /* namespace app */