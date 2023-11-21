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

std::int64_t RunLoop::once(boom::RunLoopTask const&, double) {
    return 0;
}

std::int64_t RunLoop::every(boom::RunLoopTask const&, double) {
    return 0;
}

} /* namespace boom */