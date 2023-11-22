#include <Boom/RunLoop.hpp>

namespace boom {

struct __RunLoopImpl {

};

void RunLoop::_implInit() {
    _impl = new boom::__RunLoopImpl{};
}

void RunLoop::_implDone() {
    delete _impl;
}

void RunLoop::_implSchedule(std::shared_ptr<boom::RunLoopCallback> callback, double timeout, bool repeat) {
    ;
}

} /* namespace boom */