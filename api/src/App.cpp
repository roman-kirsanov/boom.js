#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/App.hpp>

namespace boom::api {

void InitAppAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    struct AppPrivate : public boom::Shared {
        std::shared_ptr<boom::App> app;
        std::vector<boom::js::ValueRef> exitListeners;
        std::vector<boom::js::ValueRef> pollListeners;
    };

    auto ctor = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, auto) -> boom::js::Result {
        auto appPrivate = boom::MakeShared<AppPrivate>();
        appPrivate->app = boom::MakeShared<boom::App>();
        appPrivate->app->onExit([context, appPrivate]() {
            for (auto& listener : appPrivate->exitListeners) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        appPrivate->app->onPoll([context, appPrivate]() {
            for (auto& listener : appPrivate->pollListeners) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        thisObject->setPrivate(appPrivate);
        thisObject->setFinalize([](auto, boom::js::ValueRef thisObject) {
            if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
                appPrivate->app->onExit.clear();
                appPrivate->app->onPoll.clear();
            }
        });
        return boom::js::Value::Undefined(context);
    });

    auto on = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) -> boom::js::Result {
        if (arguments.size() != 2) {
            return std::unexpected(boom::js::Value::Error(context, "Wrong number of arguments"));
        }
        auto const event = arguments[0]->stringValue();
        auto const callback = arguments[1];
        if (!event) {
            return std::unexpected(boom::js::Value::Error(context, "First argument must be a string"));
        }
        if ((event != "exit")
        && (event != "poll")) {
            return std::unexpected(boom::js::Value::Error(context, "First argument must be one of: 'exit', 'poll'"));
        }
        if (!callback->isFunction()) {
            return std::unexpected(boom::js::Value::Error(context, "Second argument must be a function"));
        }
        if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
            if (event == "exit") {
                appPrivate->exitListeners.push_back(callback);
            } else if (event == "poll") {
                appPrivate->pollListeners.push_back(callback);
            }
            return boom::js::Value::Undefined(context);
        } else {
            return std::unexpected(boom::js::Value::Error(context, "Object is not an App"));
        }
    });

    auto off = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) -> boom::js::Result {
        if (arguments.size() != 2) {
            return std::unexpected(boom::js::Value::Error(context, "Wrong number of arguments"));
        }
        auto const event = arguments[0]->stringValue();
        auto const callback = arguments[1];
        if (!event) {
            return std::unexpected(boom::js::Value::Error(context, "First argument must be a string"));
        }
        if ((event != "exit")
        && (event != "poll")) {
            return std::unexpected(boom::js::Value::Error(context, "First argument must be one of: 'exit', 'poll'"));
        }
        if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
            if (event == "exit") {
                auto const pos = std::find(appPrivate->exitListeners.begin(), appPrivate->exitListeners.end(), callback);
                if (pos != appPrivate->exitListeners.end()) {
                    appPrivate->exitListeners.erase(pos);
                }
            } else if (event == "poll") {
                auto const pos = std::find(appPrivate->pollListeners.begin(), appPrivate->pollListeners.end(), callback);
                if (pos != appPrivate->pollListeners.end()) {
                    appPrivate->pollListeners.erase(pos);
                }
            }
            return boom::js::Value::Undefined(context);
        } else {
            return std::unexpected(boom::js::Value::Error(context, "Object is not an App"));
        }
    });

    auto setTitle = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) -> boom::js::Result {
        if (arguments.size() != 1) {
            return std::unexpected(boom::js::Value::Error(context, "Wrong number of arguments"));
        }
        auto const title = arguments[0]->stringValue();
        if (!title) {
            return std::unexpected(boom::js::Value::Error(context, "First argument must be a string"));
        }
        if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
            appPrivate->app->setTitle(title.value());
            return boom::js::Value::Undefined(context);
        } else {
            return std::unexpected(boom::js::Value::Error(context, "Object is not an App"));
        }
    });

    auto getTitle = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) -> boom::js::Result {
        if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
            return boom::js::Value::String(context, appPrivate->app->title());
        } else {
            return std::unexpected(boom::js::Value::Error(context, "Object is not an App"));
        }
    });

    auto exit = boom::js::Value::Function(context, [](boom::js::ContextRef context, boom::js::ValueRef thisObject, std::vector<boom::js::ValueRef> arguments) -> boom::js::Result {
        if (auto appPrivate = thisObject->getPrivate<AppPrivate>()) {
            /// TODO: Unsubscribe from Poller
            return boom::js::Value::Undefined(context);
        } else {
            return std::unexpected(boom::js::Value::Error(context, "Object is not an App"));
        }
    });

    auto proto = boom::js::Value::Object(context);
}

} /* namespace boom::api */