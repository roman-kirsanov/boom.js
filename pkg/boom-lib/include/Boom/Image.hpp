#pragma once

#include <memory>
#include <string>
#include <cinttypes>
#include <Boom/Math.hpp>
#include <Boom/Memory.hpp>
#include <Boom/OpenGL.hpp>

namespace boom {

struct __ImageImpl;

class Surface;
class Paint;
class Image;

using ImageRef = std::shared_ptr<boom::Image>;
using ImageCRef = std::shared_ptr<boom::Image const>;
using ImageWRef = std::weak_ptr<boom::Image>;
using ImageCWRef = std::weak_ptr<boom::Image const>;

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

class Image : public boom::Object {
public:
    Image(boom::Vec2);
    Image(std::uint8_t const*, boom::Vec2);
    boom::Vec2 size() const;
    virtual ~Image();
    static boom::ImageRef FromFile(std::string const&);
private:
    boom::Vec2 _size;
    boom::OpenGLUInt _textureId;
    friend boom::Surface;
    friend boom::Paint;
};

} /* namespace boom */
