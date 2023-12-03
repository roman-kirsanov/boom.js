#include <Cocoa/Cocoa.h>
#include <Boom/Window.hpp>

@interface __Window : NSWindow<NSWindowDelegate>

- (id)initWithIsPopup:(bool)isPopup
               onShow:(void(^)(void))onShow
               onHide:(void(^)(void))onHide
              onClose:(void(^)(void))onClose
           onMaximize:(void(^)(void))onMaximize
           onMinimize:(void(^)(void))onMinimize
         onDemaximize:(void(^)(void))onDemaximize
         onDeminimize:(void(^)(void))onDeminimize
               onSize:(void(^)(boom::Vec2))onSize
          onMouseMove:(void(^)(boom::Vec2, boom::KeyModifiers))onMouseMove
        onLButtonDown:(void(^)(boom::Vec2, boom::KeyModifiers))onLButtonDown
          onLButtonUp:(void(^)(boom::Vec2, boom::KeyModifiers))onLButtonUp
        onRButtonDown:(void(^)(boom::Vec2, boom::KeyModifiers))onRButtonDown
          onRButtonUp:(void(^)(boom::Vec2, boom::KeyModifiers))onRButtonUp
            onKeyDown:(void(^)(boom::Key, boom::KeyModifiers, char const*))onKeyDown
              onKeyUp:(void(^)(boom::Key, boom::KeyModifiers, char const*))onKeyUp
         onPixelRatio:(void(^)(double))onPixelratio;

@end

namespace boom {

struct __WindowImpl {
    __Window* window;
};

} /* namespace boom */
