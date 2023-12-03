#include <windows.h>
#include <Boom/Utilities.hpp>
#include <Boom/Time.hpp>

#define UNIX_TIME_START 116444736000000000ULL

namespace boom {

double Time() {
    auto fileTime = FILETIME{};
    GetSystemTimeAsFileTime(&fileTime);
    auto uint64Time = ULARGE_INTEGER{
        .LowPart = fileTime.dwLowDateTime,
        .HighPart = fileTime.dwHighDateTime
    };
    return (uint64Time.QuadPart - UNIX_TIME_START) / 10000.0;
}

double TimeLocal() {
    auto localFileTime = FILETIME{};
    auto localSystemTime = SYSTEMTIME{};
    GetLocalTime(&localSystemTime);
    SystemTimeToFileTime(&localSystemTime, &localFileTime);
    auto localUint64Time = ULARGE_INTEGER{
        .LowPart = localFileTime.dwLowDateTime,
        .HighPart = localFileTime.dwHighDateTime
    };
    return (localUint64Time.QuadPart - UNIX_TIME_START) / 10000.0;
}

} /* namespace boom */
