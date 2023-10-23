#pragma once

#include <array>
#include <vector>
#include <type_traits>

namespace boom {

struct Vec4;

struct Vec2 {
    union {
        float x;
        float width;
    };
    union {
        float y;
        float height;
    };
    boom::Vec2 operator+(boom::Vec2 const&) const;
    boom::Vec2& operator+=(boom::Vec2 const&);
    boom::Vec2 operator-(boom::Vec2 const&) const;
    boom::Vec2& operator-=(boom::Vec2 const&);
    boom::Vec2 operator*(boom::Vec2 const&) const;
    boom::Vec2& operator*=(boom::Vec2 const&);
    boom::Vec2 operator/(boom::Vec2 const&) const;
    boom::Vec2& operator/=(boom::Vec2 const&);
    boom::Vec2 operator+(float) const;
    boom::Vec2& operator+=(float);
    boom::Vec2 operator-(float) const;
    boom::Vec2& operator-=(float);
    boom::Vec2 operator*(float) const;
    boom::Vec2& operator*=(float);
    boom::Vec2 operator/(float) const;
    boom::Vec2& operator/=(float);
    bool operator==(boom::Vec2 const&) const;
    bool operator!=(boom::Vec2 const&) const;
    boom::Vec2 offset(boom::Vec2) const;
    boom::Vec2 rotate(boom::Vec2, float) const;
    boom::Vec2 lerp(boom::Vec2, float) const;
    float angle(boom::Vec2) const;
    bool inRect(boom::Vec4) const;
    bool inTrian(boom::Vec2, boom::Vec2, boom::Vec2) const;
};

struct Vec4 {
    union {
        float x;
        float red;
    };
    union {
        float y;
        float green;
    };
    union {
        float width;
        float blue;
    };
    union {
        float height;
        float alpha;
    };
    Vec4(float, float, float, float);
    Vec4(boom::Vec2, boom::Vec2);
    bool operator==(boom::Vec4 const&) const;
    bool operator!=(boom::Vec4 const&) const;
    float maxX() const;
    float maxY() const;
    boom::Vec2 size() const;
    boom::Vec2 origin() const;
    boom::Vec2 center() const;
    boom::Vec4 zoom(boom::Vec2) const;
    boom::Vec4 offset(boom::Vec2) const;
    boom::Vec4 intersect(boom::Vec4) const;
    std::vector<boom::Vec2> vertices() const;
};

struct Transform {
    std::array<float, 16> data;
    Transform();
    Transform(
        float, float, float, float,
        float, float, float, float,
        float, float, float, float,
        float, float, float, float
    );
    bool operator==(boom::Transform const&) const;
    bool operator!=(boom::Transform const&) const;
    boom::Transform operator*(boom::Transform const&) const;
    boom::Transform ortho(boom::Vec2) const;
    boom::Transform offset(boom::Vec2) const;
    boom::Transform scale(boom::Vec2) const;
    boom::Transform rotate(float) const;
};

float Lerp(float, float, float);
float Random();

template<typename T>
T Random(T min, T max);

template<typename T1, typename... T2>
T1 Max(T1, T2...);

template<typename T1, typename... T2>
T1 Min(T1, T2...);

template<typename T>
inline T Random(T min, T max) {
    static_assert(std::is_integral_v<T>, "***");
    double const mind = min;
    double const maxd = max;
    double const span = (maxd - mind + 0.99999);
    return (min + static_cast<T>(span * Random()));
}

template<typename T1, typename... T2>
inline T1 Max(T1 value, T2... rest) {
    static_assert(((std::is_same_v<T1, std::decay_t<T2>>) && ...), "***");
    T1 max_ = value;
    ((max_ = rest > max_ ? rest : max_), ...);
    return max_;
}

template<typename T1, typename... T2>
inline T1 Min(T1 value, T2... rest) {
    static_assert(((std::is_same_v<T1, std::decay_t<T2>>) && ...), "***");
    T1 min_ = value;
    ((min_ = rest < min_ ? rest : min_), ...);
    return min_;
}

} /* namespace boom */
