#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/App.hpp>

namespace boom {

boom::App* __current = nullptr;

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
    if (__current != nullptr) {
        boom::Abort("ERROR: boom::App::App() failed: Only one instance of boom::App is allowed");
    }
    __current = this;
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
    if (__current != nullptr) {
        return boom::GetShared<boom::App>(__current);
    } else {
        return nullptr;
    }
}

} /* namespace boom */
