#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {}

GraphicsView::GraphicsView()
    : boom::View()
    , onRender()
    , _context(nullptr)
{
    // _impl->w
}

std::shared_ptr<boom::OpenGL const> GraphicsView::context() const {
    return _context;
}

} /* namespace boom */