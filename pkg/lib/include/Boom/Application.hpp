#pragma once

#include <list>
#include <mutex>
#include <memory>
#include <string>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

struct __AppImpl;

class Timer;
class Window;
class Application;

using ApplicationRef = std::shared_ptr<boom::Application>;
using ApplicationCRef = std::shared_ptr<boom::Application const>;

class Application : public boom::Shared {
public:
    Application();
    boom::Emitter<> onExit;
    boom::Emitter<> onPoll;
    std::string const& title() const;
    void setTitle(std::string const&);
    void async(std::function<void()> const&);
    void exit();
    void run();
    virtual ~Application();
    static std::shared_ptr<boom::Application> Default();
protected:
    virtual void _onExit() {};
    virtual void _onPoll() {};
private:
    bool _running;
    std::string _title;
    std::mutex _mutex;
    std::list<std::function<void()>> _async;
    boom::__AppImpl* _impl;
    void _implInit();
    void _implDone();
    void _implSetTitle(std::string const&);
    void _implPollEvents();
    void _implWakeUp();
    friend boom::Window;
    friend boom::Timer;
};

} /* namespace boom */
