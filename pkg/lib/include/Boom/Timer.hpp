#pragma once

#include <optional>
#include <functional>
#include <Boom/Memory.hpp>

namespace boom {

struct __TimerImpl;

class Loop;

struct TimerOptions {
    std::optional<double> interval;
    std::optional<bool> repeat;
};

class Timer final : public boom::Shared {
public:
    Timer(std::function<void()> const&, boom::TimerOptions const&);
    Timer(std::shared_ptr<boom::Loop>, std::function<void()> const&, boom::TimerOptions const&);
    void cancel();
    virtual ~Timer();
private:
    std::shared_ptr<boom::Loop> _loop;
    std::function<void()> _fn;
    double _interval;
    bool _repeat;
    boom::__TimerImpl* _impl;
    void _implInit();
    void _implDone();
    void _implCancel();
#if _WIN32
    static void __stdcall _ImplTimerProc(std::uint32_t, std::uint32_t, std::uint64_t, std::uint64_t, std::uint64_t);
#endif
};

} /* namespace boom */