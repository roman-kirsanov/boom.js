#pragma once

#include <mutex>
#include <cinttypes>
#include <functional>
#include <condition_variable>
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
    bool _running;
    std::mutex _mutex;
    std::condition_variable _cond;
    std::vector<std::tuple<std::int64_t, boom::RunLoopTask>> _tasks;
    boom::__RunLoopImpl* _impl;
    void _implInit();
    void _implDone();
    std::int64_t _implOnce(boom::RunLoopTask const&, double);
    std::int64_t _implEvery(boom::RunLoopTask const&, double);
};

} /* namespace boom */