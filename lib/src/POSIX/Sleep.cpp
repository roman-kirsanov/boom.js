#ifdef __linux__
    #define _POSIX_C_SOURCE 200809L
#endif

#include <cmath>
#include <cstring>
#include <iostream>
#include <pthread.h>
#include <Boom/Utilities.hpp>
#include <Boom/Sleep.hpp>

#define nanospeep_E(a, b) { \
    int __err = nanosleep(a, b); \
    if (__err != 0) { \
        boom::Abort(std::string("ERROR: nanosleep() failed: ") + strerror(__err)); \
    } \
}

namespace boom {

void Sleep(double milliseconds) {
	if (milliseconds > 0) {
        struct timespec ts = {
#ifdef __linux__
            .tv_sec = static_cast<__time_t>(milliseconds / 1000),
#else
            .tv_sec = static_cast<__darwin_time_t>(milliseconds / 1000),
#endif
            .tv_nsec = static_cast<long>(fmod(milliseconds, 1000.0) * 1000000L)
        };
        nanospeep_E(&ts, NULL);
    }
}

} /* namespace boom */
