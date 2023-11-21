#pragma once

#include <cinttypes>
#include <functional>
#include <Boom/Memory.hpp>

namespace boom {

struct __RunLoopImpl;

using RunLoopTask = std::function<void()>;

class RunLoop final : public boom::Shared {
public:
    RunLoop();
    std::int64_t once(boom::RunLoopTask const&, double = 0.0);
    std::int64_t every(boom::RunLoopTask const&, double);
    void remove(std::int64_t);
    void run();
    void exit();
    virtual ~RunLoop();
    static std::shared_ptr<boom::RunLoop> Current();
private:
    boom::__RunLoopImpl* _impl;
    void _implInit();
    void _implDone();
    void _implRun();
    void _implExit();
    void _implRemove(std::int64_t);
    std::int64_t _implOnce(boom::RunLoopTask const&, double);
    std::int64_t _implEvery(boom::RunLoopTask const&, double);
};

} /* namespace boom */