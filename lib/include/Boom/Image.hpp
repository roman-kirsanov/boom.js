#pragma once

#include <memory>
#include <string>
#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Math.hpp>

namespace boom {

struct __ImageImpl;

class Surface;
class Paint;

enum class ImageFilter {
    Nearest,
    Linear
};

enum class ImagePosition {
    Start,
    Center,
    End,
    Stretch
};

struct ImageNPatch {
    float left;
    float top;
    float right;
    float bottom;
    bool operator==(boom::ImageNPatch const&) const;
    bool operator!=(boom::ImageNPatch const&) const;
};

class Image : public boom::Shared {
public:
    Image(boom::Vec2);
    Image(std::uint8_t const*, boom::Vec2);
    boom::Vec2 size() const;
    virtual ~Image();
    static std::expected<std::shared_ptr<boom::Image>, std::string> FromFile(std::string const&);
private:
    boom::Vec2 _size;
    boom::__ImageImpl* _impl;
    void _implInit(std::uint8_t const*, boom::Vec2);
    void _implDone();
    friend boom::Surface;
    friend boom::Paint;
};

} /* namespace boom */
