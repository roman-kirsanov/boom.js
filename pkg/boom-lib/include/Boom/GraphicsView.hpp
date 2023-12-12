#pragma once

#include <Boom/Time.hpp>
#include <Boom/Timer.hpp>
#include <Boom/OpenGL.hpp>
#include <Boom/View.hpp>

namespace boom {

class GraphicsView;

using GraphicsViewRef = std::shared_ptr<boom::GraphicsView>;
using GraphicsViewCRef = std::shared_ptr<boom::GraphicsView const>;
using GraphicsViewWRef = std::weak_ptr<boom::GraphicsView>;
using GraphicsViewCWRef = std::weak_ptr<boom::GraphicsView const>;

class GraphicsView : public boom::View {
public:
    GraphicsView();
    boom::Emitter<boom::GraphicsViewRef> onRender;
    boom::OpenGLCRef context() const;
    virtual ~GraphicsView();
protected:
    virtual void _onReady() override;
    virtual void _onResize() override;
    virtual void _onRender() {};
private:
    boom::OpenGLRef _context;
    void _render();
};

} /* namespace boom */