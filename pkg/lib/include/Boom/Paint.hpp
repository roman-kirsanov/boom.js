#pragma once

#include <vector>
#include <optional>
#include <Boom/Memory.hpp>
#include <Boom/Image.hpp>
#include <Boom/Color.hpp>
#include <Boom/Brush.hpp>
#include <Boom/Math.hpp>

namespace boom {

struct __PaintImpl;

class Surface;
class Image;
class Paint;

using PaintRef = std::shared_ptr<boom::Paint>;
using PaintCRef = std::shared_ptr<boom::Paint const>;
using PaintWRef = std::weak_ptr<boom::Paint>;
using PaintCWRef = std::weak_ptr<boom::Paint const>;

enum class StrokeCap {
    Butt,
    Square,
    Round
};

enum class StrokeJoint {
    Miter,
    Round,
    Bevel
};

class Paint : public boom::Shared {
public:
    Paint();
    bool blend() const;
    float opacity() const;
    std::optional<boom::Vec4> scissor() const;
    boom::Transform const& transform() const;
    boom::BrushCRef fillBrush() const;
    boom::BrushCRef strokeBrush() const;
    boom::StrokeJoint strokeJoint() const;
    boom::StrokeCap strokeCap() const;
    float strokeWidth() const;
    void setBlend(bool);
    void setOpacity(float);
    void setScissor(std::optional<boom::Vec4>);
    void setTransform(boom::Transform const&);
    void setFillBrush(boom::BrushCRef);
    void setStrokeBrush(boom::BrushCRef);
    void setStrokeJoint(boom::StrokeJoint);
    void setStrokeCap(boom::StrokeCap);
    void setStrokeWidth(float);
    void moveTo(boom::Vec2);
    void lineTo(boom::Vec2);
    void curveTo(boom::Vec2, boom::Vec2, boom::Vec2);
    void addRect(boom::Vec4);
    void addRect(boom::Vec4, float);
    void addRect(boom::Vec4, float, float, float, float);
    void addCircle(boom::Vec2, float);
    void addEllipse(boom::Vec4);
    void setRect(boom::Vec4);
    void setRect(boom::Vec4, float);
    void setRect(boom::Vec4, float, float, float, float);
    void setCircle(boom::Vec2, float);
    void setEllipse(boom::Vec4);
    void fill(boom::SurfaceCRef) const;
    void stroke(boom::SurfaceCRef) const;
    void close();
    void clear();
    virtual ~Paint();
private:
    std::vector<std::tuple<int, boom::Vec2, boom::Vec2, boom::Vec2>> _pathItems;
    std::vector<boom::Vec2> _strokeVertices;
    std::vector<boom::Vec2> _fillVertices;
    std::optional<boom::Vec4> _scissor;
    boom::Transform _transform;
    float _opacity;
    bool _blend;
    boom::BrushCRef _fillBrush;
    boom::BrushCRef _strokeBrush;
    boom::StrokeJoint _strokeJoint;
    boom::StrokeCap _strokeCap;
    float _strokeWidth;
    bool _fillNeedsVertices;
    bool _fillNeedsBuffers;
    bool _strokeNeedsVertices;
    bool _strokeNeedsBuffers;
    int _fillBrushVersion;
    int _strokeBrushVersion;
    boom::__PaintImpl* _impl;
    void _render(
        boom::SurfaceCRef,
        boom::BrushCRef,
        std::vector<boom::Vec2> const&
    ) const;
    void _implInit();
    void _implDone();
    void _implRender(
        boom::SurfaceCRef,
        boom::BrushCRef,
        std::vector<boom::Vec2> const&
    ) const;
    friend boom::Surface;
};

} /* namespace boom */
