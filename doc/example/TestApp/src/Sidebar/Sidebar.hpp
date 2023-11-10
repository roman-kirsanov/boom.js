#include <Boom.hpp>

namespace app {

class Sidebar final : public boom::GraphicsView {
protected:
    virtual void _onRender() override;
};

} /* namespace app */