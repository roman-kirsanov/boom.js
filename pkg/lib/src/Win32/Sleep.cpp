#include <windows.h>
#include <Boom/Sleep.hpp>

namespace boom {

void Sleep(double milliseconds) {
    ::Sleep(static_cast<DWORD>(milliseconds));
}

} /* namespace boom */
