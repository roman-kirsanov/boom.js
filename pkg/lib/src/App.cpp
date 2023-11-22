#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/App.hpp>

namespace boom {

std::shared_ptr<boom::App> __current = nullptr;

App::~App() {
    _implDone();
    __current = nullptr;
}

App::App()
    : onExit()
    , onPoll()
    , _title("")
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

void App::pollEvents(double timeout) {
    _implPollEvents(timeout);
    _onPoll();
    onPoll.emit();
}

std::shared_ptr<boom::App> App::Current() {
    return __current;
}

void App::_onReady() {
    if (__current != nullptr) {
        boom::Abort("ERROR: boom::App::_onReady() failed: Only one instance of boom::App is allowed");
    }
    __current = boom::GetShared<boom::App>(this);
}

} /* namespace boom */
