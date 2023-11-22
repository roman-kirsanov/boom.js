#include <Boom/App.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {
    if (auto app = boom::App::Default()) {
        app->onPoll.remove(_onPoll);
    }
}

GraphicsView::GraphicsView()
    : boom::View()
    , onRender()
    , _context(nullptr)
    , _onPoll(0) {}

void GraphicsView::_onReady() {
    _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
        .view = boom::GetShared<boom::GraphicsView>(this)
    });
    if (auto app = boom::App::Default()) {
        _onPoll = app->onPoll([
            viewWeak=boom::GetWeak<boom::GraphicsView>(this)
        ]() {
            if (auto view = viewWeak.lock()) {
                view->_render();
            }
        });
    }
}

void GraphicsView::_onResize() {
    _render();
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