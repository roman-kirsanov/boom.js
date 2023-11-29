#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/Application.hpp>

namespace boom {

Application::~Application() {
    _implDone();
}

Application::Application()
    : onExit()
    , onPoll()
    , _running(false)
    , _title("")
    , _mutex()
    , _async()
    , _impl(nullptr)
{
    _implInit();
}

std::string const& Application::title() const {
    return _title;
}

void Application::setTitle(std::string const& title) {
    _title = title;
    _implSetTitle(title);
}

void Application::async(std::function<void()> const& fn) {
    auto lock = std::unique_lock(_mutex);
    _async.push_back(fn);
    _implWakeUp();
}

void Application::exit() {
    _running = false;
}

void Application::run() {
    if (_running == false) {
        _running = true;
        for (;;) {
            _implPollEvents();
            _onPoll();
            onPoll.emit(boom::GetShared<boom::Application>(this));
            for (;;) {
                auto lock = std::unique_lock(_mutex);
                if (!_async.empty()) {
                    auto fn = _async.front();
                    _async.pop_front();
                    lock.unlock();
                    fn.operator()();
                } else {
                    break;
                }
            }
            if (_running == false) {
                break;
            }
        }
    }
}

boom::ApplicationRef Application::Default() {
    static auto app = boom::MakeShared<boom::Application>();
    return app;
}

} /* namespace boom */
