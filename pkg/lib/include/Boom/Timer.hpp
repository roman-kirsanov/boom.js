#pragma once

#include <mutex>
#include <optional>
#include <functional>
#include <Boom/Memory.hpp>

namespace boom {

struct __TimerImpl;

class Timer;

using TimerRef = std::shared_ptr<boom::Timer>;
using TimerCRef = std::shared_ptr<boom::Timer const>;
using TimerWRef = std::weak_ptr<boom::Timer>;
using TimerCWRef = std::weak_ptr<boom::Timer const>;

struct TimerOptions {
    std::optional<double> interval;
    std::optional<bool> repeat;
};

class Timer final : public boom::Object {
public:
    Timer(std::function<void()> const&, boom::TimerOptions const& = {});
    void cancel();
    virtual ~Timer();
private:
    std::function<void()> _fn;
    double _interval;
    bool _repeat;
    boom::__TimerImpl* _impl;
    void _implInit();
    void _implDone();
    void _implCancel();
};

} /* namespace boom */