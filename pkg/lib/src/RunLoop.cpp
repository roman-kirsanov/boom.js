#include <Boom/Utilities.hpp>
#include <Boom/RunLoop.hpp>

namespace boom {

boom::RunLoop* __current = nullptr;

RunLoop::~RunLoop() {
    _implDone();
    __current = nullptr;
}

RunLoop::RunLoop()
    : _impl(nullptr)
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
    _implRemove(id);
}

void RunLoop::run() {
    _implRun();
}

void RunLoop::exit() {
    _implExit();
}

std::shared_ptr<boom::RunLoop> RunLoop::Current() {
    if (__current != nullptr) {
        return boom::GetShared<boom::RunLoop>(__current);
    } else {
        return nullptr;
    }
}

} /* namespace boom */