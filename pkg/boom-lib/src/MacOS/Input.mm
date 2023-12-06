#include <map>
#include <CoreGraphics/CoreGraphics.h>
#include <Boom/Input.hpp>

namespace boom {

boom::Vec2 MousePosition() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint point = CGEventGetLocation(event);
    return {
        static_cast<float>(point.x),
        static_cast<float>(point.y)
    };
}

} /* namespace boom */
