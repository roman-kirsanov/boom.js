#pragma once

#include <mutex>
#include <cinttypes>
#include <functional>
#include <condition_variable>
#include <Boom/Memory.hpp>

namespace boom {

struct __RunLoopImpl;

class RunLoop;

enum class RunLoopCallbackState {
    Pending,
    Ready,
    Executed,
    Cancelled
};

class RunLoopCallback final : public boom::Shared {
public:
    RunLoopCallback(std::function<void()> const&, bool);
    boom::RunLoopCallbackState state() const;
    void cancel();
    virtual ~RunLoopCallback();
private:
    boom::RunLoopCallbackState _state;
    std::function<void()> _func;
    bool _cancelled;
    bool _repeat;
    friend boom::RunLoop;
};

class RunLoop final : public boom::Shared {
public:
    RunLoop();
    std::shared_ptr<boom::RunLoopCallback> once(std::function<void()> const&, double = 0.0);
    std::shared_ptr<boom::RunLoopCallback> every(std::function<void()> const&, double);
    void run();
    void exit();
    virtual ~RunLoop();
    static std::shared_ptr<boom::RunLoop> Current();
protected:
    virtual void _onReady() override;
private:
    bool _running;
    std::mutex _mutex;
    std::condition_variable _cond;
    std::vector<std::shared_ptr<boom::RunLoopCallback>> _callbaks;
    boom::__RunLoopImpl* _impl;
    void _implInit();
    void _implDone();
    void _implSchedule(std::shared_ptr<boom::RunLoopCallback>, double, bool);
};

} /* namespace boom */