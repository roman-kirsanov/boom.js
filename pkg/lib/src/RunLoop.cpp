#include <Boom/Utilities.hpp>
#include <Boom/RunLoop.hpp>

namespace boom {

std::shared_ptr<boom::RunLoop> __current = nullptr;

RunLoop::~RunLoop() {
    _implDone();
    __current = nullptr;
}

RunLoop::RunLoop()
    : _running(false)
    , _mutex()
    , _cond()
    , _callbaks()
    , _impl(nullptr)
{
    _implInit();
}

std::shared_ptr<boom::RunLoopCallback> RunLoop::once(std::function<void()> const& func, double timeout) {
    auto callback = boom::MakeShared<boom::RunLoopCallback>(func);
    _callbaks.push_back(callback);
    _implSchedule(callback, timeout, false);
}

std::shared_ptr<boom::RunLoopCallback> RunLoop::every(std::function<void()> const& func, double interval) {
    auto callback = boom::MakeShared<boom::RunLoopCallback>(func);
    _callbaks.push_back(callback);
    _implSchedule(callback, interval, true);
}

void RunLoop::run() {
    for (;;) {
        auto lock = std::unique_lock<std::mutex>(_mutex);
        auto pos = std::find_if(
            _callbaks.begin(),
            _callbaks.end(),
            [](auto item) {
                return (item->state() == boom::RunLoopCallbackState::Ready);
            }
        );
        if (pos == _callbaks.end()) {
            _cond.wait(lock);
        } else {
            auto cb = *pos;
            if (!cb->_repeat) {
                _callbaks.erase(pos);
            }
            lock.unlock();
            cb->_func.operator()();
            cb->_state = (
                (cb->_repeat)
                    ? boom::RunLoopCallbackState::Pending
                    : boom::RunLoopCallbackState::Executed
            );
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
    return __current;
}

void RunLoop::_onReady() {
    if (__current != nullptr) {
        boom::Abort("ERROR: boom::RunLoop::_onReady() failed: Only one instance of boom::RunLoop is allowed");
    }
    __current = boom::GetShared<boom::RunLoop>(this);
}

} /* namespace boom */