#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/App.hpp>

namespace boom {

App::~App() {
    _implDone();
}

App::App()
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

std::string const& App::title() const {
    return _title;
}

void App::setTitle(std::string const& title) {
    _title = title;
    _implSetTitle(title);
}

void App::async(std::function<void()> const& fn) {
    auto lock = std::unique_lock(_mutex);
    _async.push_back(fn);
    _implWakeUp();
}

void App::exit() {
    _running = false;
}

void App::run() {
    if (_running == false) {
        _running = true;
        for (;;) {
            _implPollEvents();
            _onPoll();
            onPoll.emit();
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

std::shared_ptr<boom::App> App::Default() {
    static auto app = boom::MakeShared<boom::App>();
    return app;
}

} /* namespace boom */
