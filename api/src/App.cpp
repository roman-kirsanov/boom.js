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
    };

    auto ctor = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
        scope->thisObject()->setPrivate(payload);
        scope->thisObject()->setFinalize([](auto, boom::js::ValueRef thisObject) {
            if (auto payload = thisObject->getPrivate<AppPayload>()) {
                payload->app->onExit.clear();
                payload->app->onPoll.clear();
            }
        });
    });

    auto on = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });

    auto off = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });

    auto setTitle = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });

    auto getTitle = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            scope->setResult(boom::js::Value::String(scope->context(), payload->app->title()));
        } else {
            scope->setError("Object is not an App");
        }
    });

    auto exit = boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<AppPayload>()) {
            /// TODO: Unsubscribe from Poller
            ;
        } else {
            scope->setError("Object is not an App");
        }
    });

    auto proto = boom::js::Value::Object(context);
}

} /* namespace boom::api */