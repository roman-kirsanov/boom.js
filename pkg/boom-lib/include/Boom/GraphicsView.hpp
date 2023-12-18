#pragma once

#include <optional>
#include <Boom/Time.hpp>
#include <Boom/Timer.hpp>
#include <Boom/OpenGL.hpp>
#include <Boom/Surface.hpp>
#include <Boom/View.hpp>

namespace boom {

class GraphicsView;

using GraphicsViewRef = std::shared_ptr<boom::GraphicsView>;
using GraphicsViewCRef = std::shared_ptr<boom::GraphicsView const>;
using GraphicsViewWRef = std::weak_ptr<boom::GraphicsView>;
using GraphicsViewCWRef = std::weak_ptr<boom::GraphicsView const>;

struct GraphicsViewOptions {
    std::optional<boom::OpenGLVersion> version;
};

class GraphicsView : public boom::View {
public:
    GraphicsView(boom::GraphicsViewOptions const& = {});
    boom::Emitter<boom::GraphicsViewRef> onRender;
    boom::OpenGLCRef context() const;
    boom::SurfaceCRef surface() const;
    virtual ~GraphicsView();
protected:
    virtual void _onReady() override;
    virtual void _onResize() override;
    virtual void _onRender() {};
private:
    boom::OpenGLVersion _version;
    boom::SurfaceRef _surface;
    void _render();
};

} /* namespace boom */