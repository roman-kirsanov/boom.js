#include <iostream>
#include <Boom/Application.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {}

GraphicsView::GraphicsView(boom::GraphicsViewOptions const& options)
    : boom::View()
    , onRender()
    , _openGLVersion(options.openGLVersion.value_or(boom::OpenGLVersion::CompatibilityProfile_32))
    , _context(nullptr) {}

void GraphicsView::_onReady() {
    _context = boom::MakeShared<boom::OpenGL>(boom::OpenGLOptions{
        .view = boom::GetShared<boom::GraphicsView>(this),
        .version = _openGLVersion
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
    _context->viewport(0, 0, size().width, size().height);
    _onRender();
    onRender.emit(boom::GetShared<boom::GraphicsView>(this));
    _context->flush();
    _context->swap();
}

} /* namespace boom */