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

std::shared_ptr<boom::App> App::Default() {
    static auto app = boom::MakeShared<boom::App>();
    return app;
}

} /* namespace boom */
