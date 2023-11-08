#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/App.hpp>

namespace boom::api {

void InitAppAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    struct AppPayload : public boom::Shared {
        std::shared_ptr<boom::App> app;
        std::map<std::string, std::vector<boom::js::ValueRef>> listeners;
        std::int64_t pollerSubscription;
    };

    static auto const APP_EVENTS = std::vector<std::string>({
        "exit", "poll"
    });

    static auto const ctor = [](boom::js::ScopeRef scope) {
        auto payload = boom::MakeShared<AppPayload>();
        payload->app = boom::MakeShared<boom::App>();
        payload->app->onExit([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["exit"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->app->onPoll([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["poll"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->pollerSubscription = boom::js::Poller::Default()->add([payload]() {
            payload->app->pollEvents();
        });
        scope->thisObject()->setPrivate(payload);
    };

    static auto const dtor = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            boom::js::Poller::Default()->remove(payload->pollerSubscription);
            payload->app->onExit.clear();
            payload->app->onPoll.clear();
        }
    };

    static auto const setTitle = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const title = [&]{
                try {
                    return value->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                payload->app->setTitle(title);
            } else {
                throw boom::Error("Object is not an App");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set app title");
        }
    };

    static auto const getTitle = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                return boom::js::Value::String(scope->context(), payload->app->title());
            } else {
                throw boom::Error("Object is not an App");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get app title");
        }
    };

    static auto const on = [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const func = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(APP_EVENTS, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(APP_EVENTS, ", "));
            }
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                payload->listeners[event].push_back(func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not an App");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    };

    static auto const off = [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const func = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(APP_EVENTS, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(APP_EVENTS, ", "));
            }
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                boom::Remove(payload->listeners[event], func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not an App");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    };

    static auto const exit = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                boom::js::Poller::Default()->remove(payload->pollerSubscription);
                payload->app->onExit.clear();
                payload->app->onPoll.clear();
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not an App");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to exit the app");
        }
    };

    auto appClass = boom::MakeShared<boom::js::Class>();
    appClass->setConstructor(ctor);
    appClass->setDestructor(dtor);
    appClass->defineProperty("title", getTitle, setTitle);
    appClass->defineMethod("on", on);
    appClass->defineMethod("off", off);
    appClass->defineMethod("exit", exit);
    appClass->install("App", context);
}

} /* namespace boom::api */