#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Application.hpp>

namespace boom::api {

void InitApplicationAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitApplicationAPI() failed: \"context\" cannot be nullptr");
    }

    struct ApplicationPayload : public boom::Shared {
        std::map<std::string, std::vector<boom::js::ValueRef>> listeners;
        std::int64_t exitSubscription;
        std::int64_t pollSubscription;
    };

    static auto const APP_EVENTS = std::vector<std::string>({
        "exit", "poll"
    });

    static auto const ctor = [](boom::js::ScopeRef scope) {
        auto payload = boom::MakeShared<ApplicationPayload>();
        payload->exitSubscription = boom::Application::Default()->onExit([context=scope->context(), payload](auto) {
            for (auto& listener : payload->listeners["exit"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->pollSubscription = boom::Application::Default()->onPoll([context=scope->context(), payload](auto) {
            for (auto& listener : payload->listeners["poll"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        scope->thisObject()->setPrivate(payload);
    };

    static auto const dtor = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<ApplicationPayload>()) {
            boom::Application::Default()->onExit.remove(payload->exitSubscription);
            boom::Application::Default()->onPoll.remove(payload->pollSubscription);
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
            boom::Application::Default()->setTitle(title);
        } catch (boom::Error& e) {
            throw e.extend("Failed to set application title");
        }
    };

    static auto const getTitle = [](boom::js::ScopeRef scope) {
        try {
            return boom::js::Value::String(scope->context(), boom::Application::Default()->title());
        } catch (boom::Error& e) {
            throw e.extend("Failed to get application title");
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
            if (auto payload = scope->thisObject()->getPrivate<ApplicationPayload>()) {
                payload->listeners[event].push_back(func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not an Application");
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
            if (auto payload = scope->thisObject()->getPrivate<ApplicationPayload>()) {
                boom::Remove(payload->listeners[event], func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not an Application");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    };

    static auto const exit = [](boom::js::ScopeRef scope) {
        try {
            boom::Application::Default()->exit();
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to exit the application");
        }
    };

    auto applicationClass = boom::MakeShared<boom::js::Class>("Application");
    applicationClass->setConstructor(ctor);
    applicationClass->setDestructor(dtor);
    applicationClass->defineProperty("title", getTitle, setTitle);
    applicationClass->defineMethod("on", on);
    applicationClass->defineMethod("off", off);
    applicationClass->defineMethod("exit", exit);
    applicationClass->install(context);
    context->evaluate("globalThis.application = new Application()");
}

} /* namespace boom::api */