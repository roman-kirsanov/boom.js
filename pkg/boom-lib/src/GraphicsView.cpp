#include <iostream>
#include <Boom/Application.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {}

GraphicsView::GraphicsView()
    : boom::View()
    , onRender()
    , _context(nullptr) {}

void GraphicsView::_onReady() {
    _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
        .view = boom::GetShared<boom::GraphicsView>(this)
    });
    boom::Application::Default()->onPoll([
        viewWeak=boom::GetWeak<boom::GraphicsView>(this)
    ](auto) {
        if (auto view = viewWeak.lock()) {
            view->_render();
            return true;
        } else {
            return false;
        }
    });
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