#include <cmath>
#include <cassert>
#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/Surface.hpp>
#include <Boom/Paint.hpp>

#define PATH_ITEM_TYPE_MOVE_TO  0
#define PATH_ITEM_TYPE_LINE_TO  1
#define PATH_ITEM_TYPE_CURVE_TO 2
#define PATH_ITEM_TYPE_CLOSE    3

namespace boom {

enum class __Orien {
    Colinear,
    Right,
    Left
};

static __Orien __orienPolygon(std::vector<boom::Vec2> const& polygon) {
    auto sum = 0.0;
    auto p1 = polygon.back();
    for (auto const& p2 : polygon) {
        sum += ((p2.x - p1.x) * (p2.y + p1.y));
        p1 = p2;
    }
    return ((sum > 0.0) ? __Orien::Right : __Orien::Left);
}

static __Orien __orienPoints(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3) {
    auto const val = ((p2.y - p1.y) * (p3.x - p2.x)
                    - (p2.x - p1.x) * (p3.y - p2.y));
    return (
        (val == 0.0f) ? __Orien::Colinear :
        (val > 0.0f) ? __Orien::Right :
                      __Orien::Left
    );
}

static void __earcut(std::vector<boom::Vec2> const& src, std::vector<boom::Vec2>& dst) {
    if (src.size() < 3) {
        return;
    } else if (src.size() == 3) {
        dst.push_back(src[0]);
        dst.push_back(src[1]);
        dst.push_back(src[2]);
    } else {
        auto const porien = boom::__orienPolygon(src);
        auto temp = std::vector<boom::Vec2>(src);
        auto offset = 0lu;
        while ((temp.size() - offset) > 2) {
            auto const p1 = temp[0 + offset];
            auto const p2 = temp[1 + offset];
            auto const p3 = temp[2 + offset];
            auto const torien = boom::__orienPoints(p1, p2, p3);
            if (torien == porien) {
                auto confl = false;
                for (std::size_t i = 0; i < temp.size(); i++) {
                    if (temp[i] == p1 || temp[i] == p2 || temp[i] == p3) {
                        continue;
                    }
                    if (temp[i].inTrian(p1, p2, p3)) {
                        confl = true;
                        break;
                    }
                }
                if (!confl) {
                    dst.push_back(p1);
                    dst.push_back(p2);
                    dst.push_back(p3);
                    temp.erase(temp.begin() + offset + 1);
                    offset = 0;
                } else {
                    offset += 1;
                }
            } else if (torien == __Orien::Colinear) {
                temp.erase(temp.begin() + offset);
                offset = 0;
            } else {
                offset += 1;
            }
        }
    }
}

static void __quad(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3, boom::Vec2 p4, std::vector<boom::Vec2>& dst) {
    dst.push_back(p1);
    dst.push_back(p2);
    dst.push_back(p3);
    dst.push_back(p3);
    dst.push_back(p4);
    dst.push_back(p1);
}

static void __round(boom::Vec2 center, float radius, float from, float to, std::vector<boom::Vec2>& dst) {
    //// TODO: find a better way to calculate the number of segments for better balance performance/quality...
    auto const deg1 = ((to + 360.0f) - from);
    auto const deg2 = ((deg1 > 360.0f) ? (deg1 - 360.0f) : deg1);
    auto const num = (int)ceilf(deg2 / (180.0f / radius));
    auto const step = (deg2 / num);
    auto p1 = (
        center
            .offset({ radius, 0.0f })
            .rotate(center, from)
    );
    dst.reserve(static_cast<int>(dst.size()) + (num * 3));
    for (int i = 0; i < num; i++) {
        auto const p2 = p1.rotate(center, step);
        dst.push_back(center);
        dst.push_back(p1);
        dst.push_back(p2);
        p1 = p2;
    }
}

static float __flatness(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3, boom::Vec2 p4) {
    auto ux = ((3.0f * p2.x) - (2.0f * p1.x) - p4.x); ux *= ux;
    auto uy = ((3.0f * p2.y) - (2.0f * p1.y) - p4.y); uy *= uy;
    auto vx = ((3.0f * p3.x) - (2.0f * p4.x) - p1.x); vx *= vx;
    auto vy = ((3.0f * p3.y) - (2.0f * p4.y) - p1.y); vy *= vy;
    if (ux < vx) ux = vx;
    if (uy < vy) uy = vy;
    return (ux + uy);
}

static void __curve(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3, boom::Vec2 p4, float fidelity, std::vector<boom::Vec2>& dst) {
    auto const tolerance = (1.0f - fidelity) + 0.001f;
    if (boom::__flatness(p1, p2, p3, p4) < tolerance) {
        dst.push_back(p4);
    } else {
        auto const t = 0.5f;
        auto const q1 = p1.lerp(p2, t);
        auto const q2 = p2.lerp(p3, t);
        auto const q3 = p3.lerp(p4, t);
        auto const r1 = q1.lerp(q2, t);
        auto const r2 = q2.lerp(q3, t);
        auto const pt = r1.lerp(r2, t);
        boom::__curve(p1, q1, r1, pt, fidelity, dst);
        boom::__curve(pt, r2, q3, p4, fidelity, dst);
    }
}

static void __polygonize(std::vector<std::tuple<int, boom::Vec2, boom::Vec2, boom::Vec2>> const& items, std::vector<std::vector<boom::Vec2>>& dst) {
    for (auto const& item : items) {
        if (std::get<0>(item) == PATH_ITEM_TYPE_MOVE_TO) {
            dst.push_back(std::vector<boom::Vec2>());
            dst.back().push_back(std::get<1>(item));
        } else if (std::get<0>(item) == PATH_ITEM_TYPE_LINE_TO) {
            assert(dst.size() > 0);
            assert(dst.back().size() > 0);
            dst.back().push_back(std::get<1>(item));
        } else if (std::get<0>(item) == PATH_ITEM_TYPE_CURVE_TO) {
            assert(dst.size() > 0);
            assert(dst.back().size() > 0);
            boom::__curve(
                dst.back()[dst.back().size() - 1],
                std::get<1>(item),
                std::get<2>(item),
                std::get<3>(item),
                0.1,
                dst.back()
            );
        } else if (std::get<0>(item) == PATH_ITEM_TYPE_CLOSE) {
            assert(dst.size() > 0);
            assert(dst.back().size() > 0);
            dst.back().push_back(dst.back()[0]);
        }
    }
}

static std::optional<boom::Vec2> __lineIntersect(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3, boom::Vec2 p4) {
    auto const x1 = p1.x;
    auto const y1 = p1.y;
    auto const x2 = p2.x;
    auto const y2 = p2.y;
    auto const x3 = p3.x;
    auto const y3 = p3.y;
    auto const x4 = p4.x;
    auto const y4 = p4.y;
    auto const denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    if (std::abs(denom) < 0.000001) {
        return std::nullopt;
    }
    auto const ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    auto const ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;
    if (ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1) {
        return boom::Vec2{
            (x1 + ua * (x2 - x1)),
            (y1 + ua * (y2 - y1))
        };
    } else {
        return std::nullopt;
    }
}

static std::optional<boom::Vec2> __vecIntersect(boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3, boom::Vec2 p4) {
    auto const x1 = p1.x;
    auto const y1 = p1.y;
    auto const x2 = p2.x;
    auto const y2 = p2.y;
    auto const x3 = p3.x;
    auto const y3 = p3.y;
    auto const x4 = p4.x;
    auto const y4 = p4.y;
    auto const denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    if (std::abs(denom) < 0.000001) {
        return std::nullopt;
    }
    auto const ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    return boom::Vec2{
        (x1 + ua * (x2 - x1)),
        (y1 + ua * (y2 - y1))
    };
}

Paint::~Paint() {
    _implDone();
}

Paint::Paint()
    : _pathItems()
    , _strokeVertices()
    , _fillVertices()
    , _scissor(std::nullopt)
    , _transform()
    , _opacity(1.0f)
    , _blend(true)
    , _fillBrush(nullptr)
    , _strokeBrush(nullptr)
    , _strokeJoint(boom::StrokeJoint::Round)
    , _strokeCap(boom::StrokeCap::Round)
    , _strokeWidth(1.0f)
    , _fillNeedsVertices(false)
    , _fillNeedsBuffers(false)
    , _strokeNeedsVertices(false)
    , _strokeNeedsBuffers(false)
    , _fillBrushVersion(0)
    , _strokeBrushVersion(0)
    , _impl(nullptr)
{
    _implInit();
}

float Paint::opacity() const {
    return _opacity;
}

bool Paint::blend() const {
    return _blend;
}

std::optional<boom::Vec4> Paint::scissor() const {
    return _scissor;
}

boom::Transform const& Paint::transform() const {
    return _transform;
}

std::shared_ptr<boom::Brush const> Paint::fillBrush() const {
    return _fillBrush;
}

std::shared_ptr<boom::Brush const> Paint::strokeBrush() const {
    return _strokeBrush;
}

boom::StrokeJoint Paint::strokeJoint() const {
    return _strokeJoint;
}

boom::StrokeCap Paint::strokeCap() const {
    return _strokeCap;
}

float Paint::strokeWidth() const {
    return _strokeWidth;
}

void Paint::setOpacity(float opacity) {
    if (_opacity != opacity) {
        _opacity = opacity;
    }
}

void Paint::setBlend(bool blend) {
    if (_blend != blend) {
        _blend = blend;
    }
}

void Paint::setScissor(std::optional<boom::Vec4> scissor) {
    if (_scissor != scissor) {
        _scissor = scissor;
    }
}

void Paint::setTransform(boom::Transform const& transform) {
    if (_transform != transform) {
        _transform = transform;
    }
}

void Paint::setFillBrush(std::shared_ptr<boom::Brush const> fillBrush) {
    if (_fillBrush != fillBrush) {
        _fillBrush = fillBrush;
        _fillNeedsBuffers = true;
    }
}

void Paint::setStrokeBrush(std::shared_ptr<boom::Brush const> strokeBrush) {
    if (_strokeBrush != strokeBrush) {
        _strokeBrush = strokeBrush;
        _strokeNeedsBuffers = true;
    }
}

void Paint::setStrokeJoint(boom::StrokeJoint strokeJoint) {
    if (_strokeJoint != strokeJoint) {
        _strokeJoint = strokeJoint;
        _strokeNeedsVertices = true;
        _strokeNeedsBuffers = true;
    }
}

void Paint::setStrokeCap(boom::StrokeCap strokeCap) {
    if (_strokeCap != strokeCap) {
        _strokeCap = strokeCap;
        _strokeNeedsVertices = true;
        _strokeNeedsBuffers = true;
    }
}

void Paint::setStrokeWidth(float strokeWidth) {
    if (_strokeWidth != strokeWidth) {
        _strokeWidth = strokeWidth;
        _strokeNeedsVertices = true;
        _strokeNeedsBuffers = true;
    }
}

void Paint::moveTo(boom::Vec2 point) {
    if (_pathItems.empty()) {
        _pathItems.push_back({ PATH_ITEM_TYPE_MOVE_TO, point, {}, {} });
    } else {
        if (std::get<0>(_pathItems.back()) == PATH_ITEM_TYPE_MOVE_TO) {
            std::get<1>(_pathItems.back()) = point;
        } else {
            _pathItems.push_back({ PATH_ITEM_TYPE_MOVE_TO, point, {}, {} });
        }
    }
    _strokeNeedsVertices = true;
    _strokeNeedsBuffers = true;
    _fillNeedsVertices = true;
    _fillNeedsBuffers = true;
}

void Paint::lineTo(boom::Vec2 point) {
    if (_pathItems.empty()) {
        _pathItems.push_back({ PATH_ITEM_TYPE_MOVE_TO, { 0.0f, 0.0f }, {}, {} });
    }
    _pathItems.push_back({ PATH_ITEM_TYPE_LINE_TO, point, {}, {} });
    _strokeNeedsVertices = true;
    _strokeNeedsBuffers = true;
    _fillNeedsVertices = true;
    _fillNeedsBuffers = true;
}

void Paint::curveTo(boom::Vec2 point1, boom::Vec2 point2, boom::Vec2 point3) {
    if (_pathItems.empty()) {
        _pathItems.push_back({ PATH_ITEM_TYPE_MOVE_TO, { 0.0f, 0.0f }, {}, {} });
    }
    _pathItems.push_back({ PATH_ITEM_TYPE_CURVE_TO, point1, point2, point3 });
    _strokeNeedsVertices = true;
    _strokeNeedsBuffers = true;
    _fillNeedsVertices = true;
    _fillNeedsBuffers = true;
}

void Paint::addRect(boom::Vec4 rect, float corner1, float corner2, float corner3, float corner4) {
    close();
    auto const max_x = rect.maxX();
    auto const max_y = rect.maxY();
    auto const half_me = (boom::Min(rect.width, rect.height) / 2.0f);
    corner1 = boom::Min(corner1, half_me);
    corner2 = boom::Min(corner2, half_me);
    corner3 = boom::Min(corner3, half_me);
    corner4 = boom::Min(corner4, half_me);
    if (corner1 > 0.0f) {
        auto const half1 = (corner1 / 2.0f);
        moveTo({ (rect.x + corner1), rect.y });
        curveTo(
            { (rect.x + half1), rect.y },
            { rect.x, (rect.y + half1) },
            { rect.x, (rect.y + corner1) }
        );
    } else {
        moveTo(rect.origin());
    }
    if (corner2 > 0.0f) {
        auto const half2 = (corner2 / 2.0f);
        lineTo({ rect.x, (max_y - corner2) });
        curveTo(
            { rect.x, (max_y - half2) },
            { (rect.x + half2), max_y },
            { (rect.x + corner2), max_y }
        );
    } else {
        lineTo({ rect.x, max_y });
    }
    if (corner3 > 0.0f) {
        auto const half3 = (corner3 / 2.0f);
        lineTo({ (max_x - corner3), max_y });
        curveTo(
            { (max_x - half3), max_y },
            { max_x, (max_y - half3) },
            { max_x, (max_y - corner3) }
        );
    } else {
        lineTo({ max_x, max_y });
    }
    if (corner4 > 0.0f) {
        auto const half4 = (corner4 / 2.0f);
        lineTo({ max_x, (rect.y + corner4) });
        curveTo(
            { max_x, (rect.y + half4) },
            { (max_x - half4), rect.y },
            { (max_x - corner4), rect.y }
        );
    } else {
        lineTo({ max_x, rect.y });
    }
    close();
}

void Paint::addRect(boom::Vec4 rect, float radius) {
    Paint::addRect(rect, radius, radius, radius, radius);
}

void Paint::addRect(boom::Vec4 rect) {
    Paint::addRect(rect, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Paint::addCircle(boom::Vec2 center, float radius) {
    close();
    if (radius > 0.0f) {
        auto const half = (radius / 2.0f);
        moveTo({ (center.x + radius), center.y });
        curveTo(
            { (center.x + radius), (center.y + half) },
            { (center.x + half), (center.y + radius) },
            { center.x, (center.y + radius) }
        );
        curveTo(
            { (center.x - half), (center.y + radius) },
            { (center.x - radius), (center.y + half) },
            { (center.x - radius), center.y }
        );
        curveTo(
            { (center.x - radius), (center.y - half) },
            { (center.x - half), (center.y - radius) },
            { center.x, (center.y - radius) }
        );
        curveTo(
            { (center.x + half), (center.y - radius) },
            { (center.x + radius), (center.y - half) },
            { (center.x + radius), center.y }
        );
        close();
    }
}

void Paint::addEllipse(boom::Vec4 rect) {
    ;
}

void Paint::setRect(boom::Vec4 rect) {
    clear();
    addRect(rect);
}

void Paint::setRect(boom::Vec4 rect, float radius) {
    clear();
    addRect(rect, radius);
}

void Paint::setRect(boom::Vec4 rect, float corner1, float corner2, float corner3, float corner4) {
    clear();
    addRect(rect, corner1, corner2, corner3, corner4);
}

void Paint::setCircle(boom::Vec2 center, float radius) {
    clear();
    addCircle(center, radius);
}

void Paint::setEllipse(boom::Vec4 rect) {
    clear();
    addEllipse(rect);
}

void Paint::close() {
    if (!_pathItems.empty()) {
        if ((std::get<0>(_pathItems.back()) != PATH_ITEM_TYPE_CLOSE)
        && (std::get<0>(_pathItems.back()) != PATH_ITEM_TYPE_MOVE_TO)) {
            _pathItems.push_back({ PATH_ITEM_TYPE_CLOSE, {}, {}, {} });
            _strokeNeedsVertices = true;
            _strokeNeedsBuffers = true;
            _fillNeedsVertices = true;
            _fillNeedsBuffers = true;
        }
    }
}

void Paint::clear() {
    _pathItems.clear();
    _strokeNeedsVertices = true;
    _strokeNeedsBuffers = true;
    _fillNeedsVertices = true;
    _fillNeedsBuffers = true;
}

void Paint::fill(std::shared_ptr<boom::Surface const> surface) const {
    if (surface == nullptr) {
        boom::Abort("ERROR: boom::Paint::fill() failed: \"surface\" cannot be nullptr");
    }
    if (_fillBrush == nullptr) {
        return;
    }
    if (_fillBrush->version() != _fillBrushVersion) {
        const_cast<boom::Paint*>(this)->_fillBrushVersion = _fillBrush->version();
        const_cast<boom::Paint*>(this)->_fillNeedsBuffers = true;
    }
    if (_fillNeedsVertices) {
        auto vecs = std::vector<boom::Vec2>();
        auto parts = std::vector<std::vector<boom::Vec2>>();
        boom::__polygonize(_pathItems, parts);
        for (auto const& part : parts) {
            boom::__earcut(part, vecs);
        }
        const_cast<boom::Paint*>(this)->_fillNeedsVertices = false;
        const_cast<boom::Paint*>(this)->_fillVertices = std::move(vecs);
    }
    _render(surface, _fillBrush, _fillVertices);
    const_cast<boom::Paint*>(this)->_fillNeedsVertices = false;
    const_cast<boom::Paint*>(this)->_fillNeedsBuffers = false;
}

void Paint::stroke(std::shared_ptr<boom::Surface const> surface) const {
    if (surface == nullptr) {
        boom::Abort("ERROR: boom::Paint::stroke() failed: \"surface\" cannot be nullptr");
    }
    if (_strokeBrush == nullptr) {
        return;
    }
    if (_strokeBrush->version() != _strokeBrushVersion) {
        const_cast<boom::Paint*>(this)->_strokeBrushVersion = _strokeBrush->version();
        const_cast<boom::Paint*>(this)->_strokeNeedsBuffers = true;
    }
    if (_strokeNeedsVertices) {
        /*
              point1 ------ ... ------ point4
                |                        |
            vec.point1 ---- ... --- vec.point2
                |                        |
              point2 ------ ... ------ point3
        */
        struct __Segment {
            struct {
                boom::Vec2 point1;
                boom::Vec2 point2;
            } vec;
            boom::Vec2 point1;
            boom::Vec2 point2;
            boom::Vec2 point3;
            boom::Vec2 point4;
        };
        auto half = (_strokeWidth / 2.0f);
        auto vecs = std::vector<boom::Vec2>();
        auto parts = std::vector<std::vector<boom::Vec2>>();
        boom::__polygonize(_pathItems, parts);
        for (auto const& part : parts) {
            if (part.size() > 1) {
                auto segs = std::vector<__Segment>();
                segs.reserve(part.size() - 1);
                for (std::size_t i = 1; i < part.size(); i++) {
                    auto const fpt = part[i - 1];
                    auto const tpt = part[i];
                    auto const fsp = fpt.offset({ half, 0.0f });
                    auto const tsp = tpt.offset({ half, 0.0f });
                    auto const ang = tpt.angle(fpt);
                    segs.push_back({
                        { fpt, tpt },
                        fsp.rotate(fpt, ang + 90.0f),
                        fsp.rotate(fpt, ang + 90.0f + 180.0f),
                        tsp.rotate(tpt, ang + 90.0f + 180.0f),
                        tsp.rotate(tpt, ang + 90.0f)
                    });
                }
                if (_strokeJoint == boom::StrokeJoint::Miter) {
                    for (std::size_t i = 0; i < segs.size(); i++) {
                        auto& curr = segs[i];
                        auto& prev = (i > 0) ? segs[i - 1] : segs.back();
                        if (auto const p1_4 = boom::__lineIntersect(prev.point1, prev.point4, curr.point1, curr.point4)) {
                            prev.point4 = p1_4.value();
                            curr.point1 = p1_4.value();
                            if (auto const p2_3 = boom::__vecIntersect(prev.point2, prev.point3, curr.point2, curr.point3)) {
                                prev.point3 = p2_3.value();
                                curr.point2 = p2_3.value();
                            }
                        } else if (auto const p2_3 = boom::__lineIntersect(prev.point2, prev.point3, curr.point2, curr.point3)) {
                            prev.point3 = p2_3.value();
                            curr.point2 = p2_3.value();
                            if (auto const p1_4 = boom::__vecIntersect(prev.point1, prev.point4, curr.point1, curr.point4)) {
                                prev.point4 = p1_4.value();
                                curr.point1 = p1_4.value();
                            }
                        }
                    }
                } else {
                    for (std::size_t i = 0; i < segs.size(); i++) {
                        auto& curr = segs[i];
                        auto& prev = (i > 0) ? segs[i - 1] : segs.back();
                        if (auto const p1_4 = boom::__lineIntersect(prev.point1, prev.point4, curr.point1, curr.point4)) {
                            prev.point4 = p1_4.value();
                            curr.point1 = p1_4.value();
                            if (_strokeJoint == boom::StrokeJoint::Bevel) {
                                vecs.push_back(curr.vec.point1);
                                vecs.push_back(curr.point2);
                                vecs.push_back(prev.point3);
                            } else if (_strokeJoint == boom::StrokeJoint::Round) {
                                auto const ang1 = prev.point3.angle(curr.vec.point1);
                                auto const ang2 = curr.point2.angle(curr.vec.point1);
                                boom::__round(curr.vec.point1, half, ang1, ang2, vecs);
                            }
                        } else if (auto const p2_3 = __lineIntersect(prev.point2, prev.point3, curr.point2, curr.point3)) {
                            prev.point3 = p2_3.value();
                            curr.point2 = p2_3.value();
                            if (_strokeJoint == boom::StrokeJoint::Bevel) {
                                vecs.push_back(curr.vec.point1);
                                vecs.push_back(curr.point1);
                                vecs.push_back(prev.point4);
                            } else if (_strokeJoint == boom::StrokeJoint::Round) {
                                auto const ang1 = prev.point4.angle(curr.vec.point1);
                                auto const ang2 = curr.point1.angle(curr.vec.point1);
                                boom::__round(curr.vec.point1, half, ang2, ang1, vecs);
                            }
                        }
                    }
                }
                for (auto const& seg : segs) {
                    boom::__quad(seg.point1, seg.vec.point1, seg.vec.point2, seg.point4, vecs);
                    boom::__quad(seg.vec.point1, seg.point2, seg.point3, seg.vec.point2, vecs);
                }
            }
        }
        const_cast<boom::Paint*>(this)->_strokeNeedsVertices = false;
        const_cast<boom::Paint*>(this)->_strokeVertices = std::move(vecs);
    }
    _render(surface, _strokeBrush, _strokeVertices);
    const_cast<boom::Paint*>(this)->_strokeNeedsVertices = false;
    const_cast<boom::Paint*>(this)->_strokeNeedsBuffers = false;
}

void Paint::_render(
    std::shared_ptr<boom::Surface const> surface,
    std::shared_ptr<boom::Brush const> brush,
    std::vector<boom::Vec2> const& vertices
) const {
    assert(surface != nullptr);
    assert(brush != nullptr);
    if (vertices.size() == 0) {
        return;
    }
    if ((vertices.size() % 3) != 0) {
        boom::Abort("ERROR: boom::Paint::_render() failed: Wrong number of vertices, found " + std::to_string(vertices.size()));
    }
    _implRender(surface, brush, vertices);
}

} /* namespace boom */
