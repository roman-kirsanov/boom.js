#include <Boom/Loop.hpp>
#include <Boom/Timer.hpp>

namespace boom {

Loop::~Loop() {}

Loop::Loop()
    : onLoop()
    , _running(false)
    , _mutex()
    , _condvar()
    , _queue() {}

std::shared_ptr<boom::Timer> Loop::after(double timeout, std::function<void()> const& fn) {
    return boom::MakeShared<boom::Timer>(boom::GetShared<boom::Loop>(this), fn, boom::TimerOptions{ .interval = timeout });
}

std::shared_ptr<boom::Timer> Loop::every(double interval, std::function<void()> const& fn) {
    return boom::MakeShared<boom::Timer>(boom::GetShared<boom::Loop>(this), fn, boom::TimerOptions{ .interval = interval, .repeat = true });
}

void Loop::add(std::function<void()> const& fn) {
    _mutex.lock();
    _queue.push_back(fn);
    _mutex.unlock();
    _condvar.notify_one();
}

void Loop::run() {
    _running = true;
    for (;;) {
        onLoop.emit();
        auto lock = std::unique_lock(_mutex);
        if (_queue.empty()) {
            // _condvar.wait(lock);
            _condvar.wait_for(lock, std::chrono::milliseconds(1));
        } else {
            auto fn = _queue.front();
            _queue.pop_front();
            lock.unlock();
            fn.operator()();
        }
        if (_running == false) {
            break;
        }
    }
}

void Loop::exit() {
    _running = true;
}

std::shared_ptr<boom::Loop> Loop::Default() {
    static auto loop = boom::MakeShared<boom::Loop>();
    return loop;
}

} /* namespace boom */