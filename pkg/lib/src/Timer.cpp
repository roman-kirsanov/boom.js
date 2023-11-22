#include <Boom/Utilities.hpp>
#include <Boom/Loop.hpp>
#include <Boom/Timer.hpp>

namespace boom {

Timer::~Timer() {
    cancel();
    _implDone();
}

Timer::Timer(std::function<void()> const& fn, boom::TimerOptions const& options)
    : _loop(boom::Loop::Default())
    , _fn(fn)
    , _interval(options.interval.value_or(1000.0))
    , _repeat(options.repeat.value_or(false))
    , _impl(nullptr)
{
    _implInit();
}

Timer::Timer(std::shared_ptr<boom::Loop> loop, std::function<void()> const& fn, boom::TimerOptions const& options)
    : _loop(loop)
    , _fn(fn)
    , _interval(options.interval.value_or(1000.0))
    , _repeat(options.repeat.value_or(false))
    , _impl(nullptr)
{
    if (loop == nullptr) {
        boom::Abort("ERROR: boom::Timer::Timer() failed: \"loop\" cannot be nullptr");
    }
    _implInit();
}

void Timer::cancel() {
    _implCancel();
}

} /* namespace boom */