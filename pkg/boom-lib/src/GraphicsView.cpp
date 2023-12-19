#include <iostream>
#include <Boom/Application.hpp>
#include <Boom/GraphicsView.hpp>

namespace boom {

GraphicsView::~GraphicsView() {}

GraphicsView::GraphicsView(boom::GraphicsViewOptions const& options)
    : boom::View()
    , onRender()
    , _version(options.version.value_or(boom::OpenGLVersion::CompatibilityProfile_32))
    , _surface(nullptr) {}

boom::OpenGLCRef GraphicsView::context() const {
    return _surface->context();
}

boom::SurfaceCRef GraphicsView::surface() const {
    return _surface;
}

void GraphicsView::_onReady() {
    _surface = boom::MakeShared<boom::Surface>(boom::SurfaceOptions{
        .type = boom::SurfaceType::View,
        .view = boom::GetShared<boom::GraphicsView>(this),
        .version = _version
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

void GraphicsView::_render() {
    _surface->current();
    _onRender();
    onRender.emit(boom::GetShared<boom::GraphicsView>(this));
    _surface->flush();
    _surface->swap();
}

} /* namespace boom */