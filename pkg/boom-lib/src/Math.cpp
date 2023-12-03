#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <Boom/Math.hpp>

namespace boom {

boom::Vec2 Vec2::operator+(boom::Vec2 const& vec2) const {
    return {
        (x + vec2.x),
        (y + vec2.y)
    };
}

boom::Vec2& Vec2::operator+=(boom::Vec2 const& vec2) {
    x += vec2.x;
    y += vec2.y;
    return *this;
}

boom::Vec2 Vec2::operator-(boom::Vec2 const& vec2) const {
    return {
        (x - vec2.x),
        (y - vec2.y)
    };
}

boom::Vec2& Vec2::operator-=(boom::Vec2 const& vec2) {
    x -= vec2.x;
    y -= vec2.y;
    return *this;
}

boom::Vec2 Vec2::operator*(boom::Vec2 const& vec2) const {
    return {
        (x * vec2.x),
        (y * vec2.y)
    };
}

boom::Vec2& Vec2::operator*=(boom::Vec2 const& vec2) {
    x *= vec2.x;
    y *= vec2.y;
    return *this;
}

boom::Vec2 Vec2::operator/(boom::Vec2 const& vec2) const {
    return {
        (x / vec2.x),
        (y / vec2.y)
    };
}

boom::Vec2& Vec2::operator/=(boom::Vec2 const& vec2) {
    x /= vec2.x;
    y /= vec2.y;
    return *this;
}

boom::Vec2 Vec2::operator+(float value) const {
    return {
        (x + value),
        (y + value)
    };
}

boom::Vec2& Vec2::operator+=(float value) {
    x += value;
    y += value;
    return *this;
}

boom::Vec2 Vec2::operator-(float value) const {
    return {
        (x - value),
        (y - value)
    };
}

boom::Vec2& Vec2::operator-=(float value) {
    x -= value;
    y -= value;
    return *this;
}

boom::Vec2 Vec2::operator*(float value) const {
    return {
        (x * value),
        (y * value)
    };
}

boom::Vec2& Vec2::operator*=(float value) {
    x *= value;
    y *= value;
    return *this;
}

boom::Vec2 Vec2::operator/(float value) const {
    return {
        (x / value),
        (y / value)
    };
}

boom::Vec2& Vec2::operator/=(float value) {
    x /= value;
    y /= value;
    return *this;
}

bool Vec2::operator==(boom::Vec2 const& vec2) const {
    return (x == vec2.x)
        && (y == vec2.y);
}

bool Vec2::operator!=(boom::Vec2 const& vec2) const {
    return !operator==(vec2);
}

boom::Vec2 Vec2::offset(boom::Vec2 vec2) const {
    return {
        (x + vec2.x),
        (y + vec2.y)
    };
}

boom::Vec2 Vec2::rotate(boom::Vec2 center, float angle) const {
    auto const rad = -(((float)M_PI / 180.0f) * angle);
    auto const co = std::cos(rad);
    auto const si = std::sin(rad);
    return {
        ((co * (x - center.x)) + (si * (y - center.y)) + center.x),
        ((co * (y - center.y)) - (si * (x - center.x)) + center.y)
    };
}

boom::Vec2 Vec2::lerp(boom::Vec2 destination, float t) const {
    return {
        boom::Lerp(x, destination.x, t),
        boom::Lerp(y, destination.y, t)
    };
}

float Vec2::angle(boom::Vec2 center) const {
    auto const dx = (x - center.x);
    auto const dy = (y - center.y);
    auto const an = ((atan2(dy, dx) * 180.0f) / (float)M_PI);
    return (an < 0 ? an + 360.0f : an);
}

bool Vec2::inRect(boom::Vec4 vec4) const {
    return (x >= vec4.x)
        && (y >= vec4.y)
        && (x < vec4.maxX())
        && (y < vec4.maxY());
}

bool Vec2::inTrian(boom::Vec2 vec2_1, boom::Vec2 vec2_2, boom::Vec2 vec2_3) const {
    auto const area = [](boom::Vec2 p1, boom::Vec2 p2, boom::Vec2 p3) {
        return 0.5f * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
    };
    auto const abc = area(vec2_1, vec2_2, vec2_3);
    auto const pab = area(*this, vec2_1, vec2_2);
    auto const pbc = area(*this, vec2_2, vec2_3);
    auto const pca = area(*this, vec2_3, vec2_1);
    auto const sum = (pab + pbc + pca);
    auto const tolerance = 0.000001f;
    return (std::abs(sum - abc) < tolerance);
}

Vec4::Vec4(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height) {}

Vec4::Vec4(boom::Vec2 origin, boom::Vec2 size)
    : x(origin.x), y(origin.y), width(size.width), height(size.height) {}

bool Vec4::operator==(boom::Vec4 const& vec4) const {
    return (x == vec4.x)
        && (y == vec4.y)
        && (width == vec4.width)
        && (height == vec4.height);
}

bool Vec4::operator!=(boom::Vec4 const& vec4) const {
    return !operator==(vec4);
}

float Vec4::maxX() const {
    return (x + width);
}

float Vec4::maxY() const {
    return (y + height);
}

boom::Vec2 Vec4::size() const {
    return { width, height };
}

boom::Vec2 Vec4::origin() const {
    return { x, y };
}

boom::Vec2 Vec4::center() const {
    return {
        (x + (width / 2.0f)),
        (y + (height / 2.0f))
    };
}

boom::Vec4 Vec4::zoom(boom::Vec2 zoom) const {
    return {
        (x - zoom.x),
        (y - zoom.y),
        (width + (zoom.x * 2.0f)),
        (height + (zoom.y * 2.0f))
    };
}

boom::Vec4 Vec4::offset(boom::Vec2 offset) const {
    return {
        (x + offset.x),
        (y + offset.y),
        width,
        height
    };
}

boom::Vec4 Vec4::intersect(boom::Vec4 vec4) const {
    auto const left = boom::Max(x, vec4.x);
    auto const right = boom::Min(x + width, vec4.x + vec4.width);
    auto const top = boom::Max(y, vec4.y);
    auto const bottom = boom::Min(y + height, vec4.y + vec4.height);
    if (left >= right || top >= bottom) {
        return { 0, 0, 0, 0 };
    } else {
        return { left, top, (right - left), (bottom - top) };
    }
}

std::vector<boom::Vec2> Vec4::vertices() const {
    return {
        origin(),
        { maxX(), y },
        { x, maxY() },
        { maxX(), y },
        { x, maxY() },
        { maxX(), maxY() }
    };
}

Transform::Transform()
    : data({
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    }) {}

Transform::Transform(
    float a, float b, float c, float d,
    float e, float f, float g, float h,
    float i, float j, float k, float l,
    float m, float n, float o, float p
) : data({
    a, b, c, d,
    e, f, g, h,
    i, j, k, l,
    m, n, o, p
}) {}

bool Transform::operator==(boom::Transform const& transform) const {
    return (data == transform.data);
}

bool Transform::operator!=(boom::Transform const& transform) const {
    return !operator==(transform);
}

boom::Transform Transform::operator*(boom::Transform const& transform) const {
    auto ret = boom::Transform();
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            ret.data[row * 4 + col] = (
                data[row * 4 + 0] * transform.data[0 * 4 + col] +
                data[row * 4 + 1] * transform.data[1 * 4 + col] +
                data[row * 4 + 2] * transform.data[2 * 4 + col] +
                data[row * 4 + 3] * transform.data[3 * 4 + col]
            );
        }
    }
    return ret;
}

float Lerp(float a, float b, float t) {
    return (a + (b - a) * t);
}

float Random() {
    static auto seeded = false;
    if (seeded == false) {
        seeded = true;
        srand(static_cast<unsigned>(time(nullptr)));
    }
    return ((float)rand() / (float)RAND_MAX);
}

boom::Transform Transform::ortho(boom::Vec2 size) const {
    auto const right = size.width;
    auto const top = size.height;
    auto const rl = (1.0f / right);
    auto const tb = (1.0f / top);
    auto const fn = (1.0f / (1.0f - (-1.0f)));

    // lower left projection...
    // auto const tran = boom::Transform{
    //     (2.0f * rl), 0.0f, 0.0f, 0.0f,
    //     0.0f,  (2.0f * tb), 0.0f, 0.0f,
    //     0.0f,  0.0f, (-2.0f * fn), 0.0f,
    //     -1.0f, -1.0f, (-(1.0f + (-1.0f)) * fn), 1.0f
    // };

    // upper left projection...
    auto const tran = boom::Transform{
        (2.0f * rl), 0.0f, 0.0f, 0.0f,
        0.0f, (-2.0f * tb), 0.0f, 0.0f,
        0.0f, 0.0f, (-2.0f * fn), 0.0f,
        -1.0f, 1.0f, (-(1.0f + (-1.0f)) * fn), 1.0f
    };
    return ((*this) * tran);
}

boom::Transform Transform::offset(boom::Vec2 offset) const {
    auto const tran = boom::Transform{
        1.0f,     0.0f,     0.0f, 0.0f,
        0.0f,     1.0f,     0.0f, 0.0f,
        0.0f,     0.0f,     1.0f, 0.0f,
        offset.x, offset.y, 0.0f, 1.0f
    };
    return ((*this) * tran);
}

boom::Transform Transform::scale(boom::Vec2 scale) const {
    auto const tran = boom::Transform{
        scale.x,0.0f,   0.0f, 0.0f,
        0.0f,   scale.y,0.0f, 0.0f,
        0.0f,   0.0f,   1.0f, 0.0f,
        0.0f,   0.0f,   0.0f, 1.0f
    };
    return ((*this) * tran);
}

boom::Transform Transform::rotate(float rotate) const {
    auto const rad = (rotate * M_PI / 180.0f);
    auto const cos = ::cosf(rad);
    auto const sin = ::sinf(rad);
    auto const tran = boom::Transform{
        cos,  sin,  0.0f, 0.0f,
        -sin, cos,  0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    return ((*this) * tran);
}

} /* namespace boom */
