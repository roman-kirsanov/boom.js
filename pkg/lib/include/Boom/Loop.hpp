#pragma once

#include <list>
#include <mutex>
#include <functional>
#include <Boom/Time.hpp>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>
#include <condition_variable>

namespace boom {

class Timer;

class Loop final : public boom::Shared {
public:
    Loop();
    boom::Emitter<> onLoop;
    std::shared_ptr<boom::Timer> after(double, std::function<void()> const&);
    std::shared_ptr<boom::Timer> every(double, std::function<void()> const&);
    void add(std::function<void()> const&);
    void run();
    void exit();
    virtual ~Loop();
    static std::shared_ptr<boom::Loop> Default();
private:
    bool _running;
    std::mutex _mutex;
    std::condition_variable _condvar;
    std::list<std::function<void()>> _queue;
};

} /* namespace boom */