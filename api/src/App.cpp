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
        std::vector<boom::js::ValueRef> exitListeners;
        std::vector<boom::js::ValueRef> pollListeners;
        std::int64_t pollerSubscription;
    };

    auto ctor = [](boom::js::ScopeRef scope) {
        auto payload = boom::MakeShared<AppPayload>();
        payload->app = boom::MakeShared<boom::App>();
        payload->app->onExit([context=scope->context(), payload]() {
            for (auto& listener : payload->exitListeners) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->app->onPoll([context=scope->context(), payload]() {
            for (auto& listener : payload->pollListeners) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->pollerSubscription = boom::js::Poller::Default()->add([payload]() {
            payload->app->pollEvents();
        });
        scope->thisObject()->setPrivate(payload);
        scope->thisObject()->setFinalize([](auto, boom::js::ValueRef thisObject) {
            if (auto payload = thisObject->getPrivate<AppPayload>()) {
                boom::js::Poller::Default()->remove(payload->pollerSubscription);
                payload->app->onExit.clear();
                payload->app->onPoll.clear();
            }
        });
    };

    auto on = [](boom::js::ScopeRef scope) {
        auto const event = scope->getArg(0)->stringValue();
        auto const callback = scope->getArg(1)->functionValue();
        if (!event) {
            scope->setError("First argument must be a string");
            return;
        }
        if ((event != "exit")
        && (event != "poll")) {
            scope->setError("First argument must be one of: 'exit', 'poll'");
            return;
        }
        if (!callback) {
            scope->setError("Second argument must be a function");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            if (event == "exit") {
                payload->exitListeners.push_back(callback.value());
            } else if (event == "poll") {
                payload->pollListeners.push_back(callback.value());
            }
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto off = [](boom::js::ScopeRef scope) {
        auto const event = scope->getArg(0)->stringValue();
        auto const callback = scope->getArg(1)->functionValue();
        if (!event) {
            scope->setError("First argument must be a string");
            return;
        }
        if ((event != "exit")
        && (event != "poll")) {
            scope->setError("First argument must be one of: 'exit', 'poll'");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            if (event == "exit") {
                auto const pos = std::find(payload->exitListeners.begin(), payload->exitListeners.end(), callback);
                if (pos != payload->exitListeners.end()) {
                    payload->exitListeners.erase(pos);
                }
            } else if (event == "poll") {
                auto const pos = std::find(payload->pollListeners.begin(), payload->pollListeners.end(), callback);
                if (pos != payload->pollListeners.end()) {
                    payload->pollListeners.erase(pos);
                }
            }
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto setTitle = [](boom::js::ScopeRef scope) {
        auto const title = scope->getArg(0)->stringValue();
        if (!title) {
            scope->setError("First argument must be a string");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            payload->app->setTitle(title.value());
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto getTitle = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            scope->setResult(boom::js::Value::String(scope->context(), payload->app->title()));
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto exit = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            boom::js::Poller::Default()->remove(payload->pollerSubscription);
            payload->app->onExit.clear();
            payload->app->onPoll.clear();
        } else {
            scope->setError("Object is not an App");
        }
    };

    auto appProto = boom::js::Value::Object(context);
    appProto->setProperty("on", boom::js::Value::Function(context, on), { .readOnly = true }).value();
    appProto->setProperty("off", boom::js::Value::Function(context, off), { .readOnly = true }).value();
    appProto->setProperty("exit", boom::js::Value::Function(context, exit), { .readOnly = true }).value();
    appProto->defineProperty("title", getTitle, setTitle).value();

    auto appClass = boom::js::Value::Function(context, ctor);
    appClass->setProperty("prototype", appProto).value();

    context->globalThis()->setProperty("App", appClass).value();
}

} /* namespace boom::api */