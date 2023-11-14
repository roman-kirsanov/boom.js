#pragma once

#include <memory>
#include <string>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

struct __AppImpl;

class Window;

class App : public boom::Shared {
public:
    App();
    boom::Emitter<> onExit;
    boom::Emitter<> onLoop;
    std::string const& title() const;
    void setTitle(std::string const&);
    void run();
    void exit();
    virtual ~App();
    static std::shared_ptr<boom::App> Current();
protected:
    virtual void _onExit() {};
    virtual void _onLoop() {};
private:
    bool _running;
    std::string _title;
    boom::__AppImpl* _impl;
    void _implInit();
    void _implDone();
    void _implSetTitle(std::string const&);
    void _implPollEvents(double);
    friend boom::Window;
};

} /* namespace boom */
