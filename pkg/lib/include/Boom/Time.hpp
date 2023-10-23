#pragma once

constexpr double operator ""_ms(long double ms) { return ms; };
constexpr double operator ""_sec(long double sec) { return (sec * 1000.0); };
constexpr double operator ""_min(long double min) { return (min * 1000.0 * 60.0); };
constexpr double operator ""_ms(unsigned long long ms) { return ms; };
constexpr double operator ""_sec(unsigned long long sec) { return (sec * 1000.0); };
constexpr double operator ""_min(unsigned long long min) { return (min * 1000.0 * 60.0); };

namespace boom {

double Time();
double TimeLocal();

} /* namespace Boom */
