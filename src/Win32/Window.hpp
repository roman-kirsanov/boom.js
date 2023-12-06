#include <windows.h>
#include <Boom/Window.hpp>

namespace boom {

struct __WindowImpl {
    HWND window;
    bool maximized;
    bool minimized;
};

} /* namespace boom */
