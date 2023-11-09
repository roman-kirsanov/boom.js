#pragma once

#include <Boom/OpenGL.hpp>
#include <Boom/View.hpp>

namespace boom {

class GraphicsView : public boom::View {
public:
    GraphicsView();
    boom::Emitter<std::shared_ptr<boom::GraphicsView>> onRender;
    std::shared_ptr<boom::OpenGL const> context() const;
    virtual ~GraphicsView();
protected:
    virtual void _onRender() {};
private:
    std::shared_ptr<boom::OpenGL> _context;
};

} /* namespace boom */