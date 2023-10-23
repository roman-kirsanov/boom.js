#include <Boom/JS/Poller.hpp>

namespace boom::js {

Poller::~Poller() {}

Poller::Poller()
    : _listeners() {}

std::int64_t Poller::add(std::function<void()> const& fn) {
    return _listeners(fn);
}
void Poller::remove(std::int64_t id) {
    _listeners.remove(id);
}

bool Poller::empty() const {
    return _listeners.listeners().empty();
}

void Poller::poll() {
    _listeners.emit();
}

void Poller::clear() {
    _listeners.clear();
}

boom::js::PollerRef Poller::Default() {
    static auto poller = boom::MakeShared<boom::js::Poller>();
    return poller;
}

} /* namespace boom::js */