#include <Boom/App.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {
    if (auto app = boom::App::Current()) {
        app->onLoop.remove(_onLoop);
    }
}

GraphicsView::GraphicsView()
    : boom::View()
    , onRender()
    , _context(nullptr)
    , _onLoop(0) {}

void GraphicsView::_onReady() {
    _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
        .view = boom::GetShared<boom::GraphicsView>(this)
    });
    if (auto app = boom::App::Current()) {
        _onLoop = app->onLoop([
            viewWeak=boom::GetWeak<boom::GraphicsView>(this)
        ]() {
            if (auto view = viewWeak.lock()) {
                view->_render();
            }
        });
    }
}

std::shared_ptr<boom::OpenGL const> GraphicsView::context() const {
    return _context;
}

void GraphicsView::_render() {
    _context->bindFramebuffer(boom::kOpenGLFramebuffer, 0);
    _onRender();
    onRender.emit(boom::GetShared<boom::GraphicsView>(this));
    _context->swap();
}

} /* namespace boom */