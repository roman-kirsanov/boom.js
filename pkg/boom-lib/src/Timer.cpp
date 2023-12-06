#include <Boom/Utilities.hpp>
#include <Boom/Timer.hpp>

namespace boom {

Timer::~Timer() {
    _implDone();
}

Timer::Timer(std::function<void()> const& fn, boom::TimerOptions const& options)
    : _fn(fn)
    , _interval(options.interval.value_or(1000.0))
    , _repeat(options.repeat.value_or(true))
    , _impl(nullptr)
{
    _implInit();
}

void Timer::cancel() {
    _implCancel();
}

} /* namespace boom */