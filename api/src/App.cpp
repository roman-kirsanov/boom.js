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

    static auto ctor = [](boom::js::ScopeRef scope) {
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
        scope->thisObject()->setFinalize([](boom::js::ScopeRef scope) {
            if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
                boom::js::Poller::Default()->remove(payload->pollerSubscription);
                payload->app->onExit.clear();
                payload->app->onPoll.clear();
            }
        });
    };

    static auto setTitle = [](boom::js::ScopeRef scope) {
        auto const titleArg = scope->getArg(0)->stringValue();
        if (!titleArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            payload->app->setTitle(titleArg.value());
        } else {
            scope->setError("Object is not an App");
        }
    };

    static auto getTitle = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            scope->setResult(boom::js::Value::String(scope->context(), payload->app->title()));
        } else {
            scope->setError("Object is not an App");
        }
    };

    static auto on = [](boom::js::ScopeRef scope) {
        auto const eventArg = scope->getArg(0)->stringValue();
        auto const funcArg = scope->getArg(1)->functionValue();
        if (!eventArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (boom::Includes(APP_EVENTS, eventArg.value()) == false) {
            scope->setError("First argument must be one of: ???");
            return;
        }
        if (!funcArg) {
            scope->setError("Second argument must be a function");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            payload->listeners[eventArg.value()].push_back(funcArg.value());
        } else {
            scope->setError("Object is not an App");
        }
    };

    static auto off = [](boom::js::ScopeRef scope) {
        auto const eventArg = scope->getArg(0)->stringValue();
        auto const funcArg = scope->getArg(1)->functionValue();
        if (!eventArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (boom::Includes(APP_EVENTS, eventArg.value()) == false) {
            scope->setError("First argument must be one of: ???");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            boom::Remove(payload->listeners[eventArg.value()], funcArg.value());
        } else {
            scope->setError("Object is not an App");
        }
    };

    static auto exit = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            boom::js::Poller::Default()->remove(payload->pollerSubscription);
            payload->app->onExit.clear();
            payload->app->onPoll.clear();
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto appProto = boom::js::Value::Object(context);
    appProto->defineProperty("title", getTitle, setTitle).value();
    appProto->setProperty("on", boom::js::Value::Function(context, on), { .readOnly = true }).value();
    appProto->setProperty("off", boom::js::Value::Function(context, off), { .readOnly = true }).value();
    appProto->setProperty("exit", boom::js::Value::Function(context, exit), { .readOnly = true }).value();

    auto appClass = boom::js::Value::Function(context, ctor);
    appClass->setProperty("prototype", appProto).value();

    context->globalThis()->setProperty("App", appClass).value();
}

} /* namespace boom::api */