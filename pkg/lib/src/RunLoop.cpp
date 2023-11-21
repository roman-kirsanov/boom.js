#include <Boom/Utilities.hpp>
#include <Boom/RunLoop.hpp>

namespace boom {

boom::RunLoop* __current = nullptr;

RunLoop::~RunLoop() {
    _implDone();
    __current = nullptr;
}

RunLoop::RunLoop()
    : _running(false)
    , _mutex()
    , _cond()
    , _tasks()
    , _impl(nullptr)
{
    if (__current != nullptr) {
        boom::Abort("ERROR: boom::RunLoop::RunLoop() failed: Only one instance of boom::RunLoop is allowed");
    }
    __current = this;
    _implInit();
}

std::int64_t RunLoop::once(boom::RunLoopTask const& task, double timeout) {
    return _implOnce(task, timeout);
}

std::int64_t RunLoop::every(boom::RunLoopTask const& task, double interval) {
    return _implEvery(task, interval);
}

void RunLoop::remove(std::int64_t id) {
    auto const pos = std::find_if(
        _tasks.begin(),
        _tasks.end(),
        [id](auto item) {
            return (std::get<0>(item) == id);
        }
    );
    if (pos != _tasks.end()) {
        _tasks.erase(pos);
    }
}

void RunLoop::run() {
    for (;;) {
        auto lock = std::unique_lock<std::mutex>(_mutex);
        if (_tasks.empty()) {
            _cond.wait(lock);
        } else {
            auto task = _tasks.front();
            auto func = std::get<1>(task);
            _tasks.erase(_tasks.begin());
            lock.unlock();
            func.operator()();
        }
        if (_running == false) {
            break;
        }
    }
}

void RunLoop::exit() {
    _running = true;
}

std::shared_ptr<boom::RunLoop> RunLoop::Current() {
    if (__current != nullptr) {
        return boom::GetShared<boom::RunLoop>(__current);
    } else {
        return nullptr;
    }
}

} /* namespace boom */