#ifdef __linux__
#define _POSIX_C_SOURCE 200809L
#endif

#include <cmath>
#include <ctime>
#include <iostream>
#include <cstring>
#include <sys/time.h>
#include <Boom/Time.hpp>

#define gettimeofday_E(a, b) { \
    int __err = gettimeofday(a, b); \
    if (__err != 0) { \
        std::cerr << "ERROR: gettimeofday() failed: " << strerror(__err) << std::endl; \
        ::exit(-1); \
    } \
}

namespace boom {

double Time() {
    struct timeval tv = {};
    gettimeofday_E(&tv, nullptr);
    return (tv.tv_sec * 1000.0)
           + (tv.tv_usec / 1000.0);
}

double TimeLocal() {
    struct timeval tv = {};
    struct tm utc = {};
    struct tm loc = {};
    gettimeofday_E(&tv, nullptr);
    localtime_r(&tv.tv_sec, &loc);
    gmtime_r(&tv.tv_sec, &utc);
    return (tv.tv_sec * 1000.0)
           + (tv.tv_usec / 1000.0)
           + (((loc.tm_sec * 1000.0) + (loc.tm_min * 60000.0) + (loc.tm_hour * 3600000.0))
              - ((utc.tm_sec * 1000.0) + (utc.tm_min * 60000.0) + (utc.tm_hour * 3600000.0)));
}

} /* namespace boom */
