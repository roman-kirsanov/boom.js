#include <Boom/Application.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {}

GraphicsView::GraphicsView()
    : boom::View()
    , onRender()
    , _context(nullptr)
    , _timer(nullptr) {}

void GraphicsView::_onReady() {
    _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
        .view = boom::GetShared<boom::GraphicsView>(this)
    });
    _timer = boom::MakeShared<boom::Timer>(
        [viewWeak=boom::GetWeak<boom::GraphicsView>(this)]() {
            if (auto view = viewWeak.lock()) {
                view->_render();
            }
        },
        boom::TimerOptions{
            .interval = 16.667_ms,
            .repeat = true
        }
    );
}

void GraphicsView::_onResize() {
    _render();
}

boom::OpenGLCRef GraphicsView::context() const {
    return _context;
}

void GraphicsView::_render() {
    _context->bindFramebuffer(boom::kOpenGLFramebuffer, 0);
    _onRender();
    onRender.emit(boom::GetShared<boom::GraphicsView>(this));
    _context->swap();
}

} /* namespace boom */