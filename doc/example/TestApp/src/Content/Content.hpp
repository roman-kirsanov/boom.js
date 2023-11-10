#include <Boom.hpp>

namespace app {

class Content final : public boom::GraphicsView {
protected:
    virtual void _onRender() override;
};

} /* namespace app */