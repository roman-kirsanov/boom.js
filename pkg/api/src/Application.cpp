#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Utilities.hpp>
#include <Boom/API/Application.hpp>

namespace boom::api {

auto constexpr kApplicationValueKey = 1;
auto constexpr kApplicationExitEvent = "exit";
auto constexpr kApplicationPollEvent = "poll";

static auto kApplicationEventList = std::vector<std::string>({
    boom::api::kApplicationExitEvent,
    boom::api::kApplicationPollEvent
});

void InitApplicationAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitApplicationAPI() failed: \"context\" cannot be nullptr");
    }

    auto application = boom::js::Value::Object(context);

    auto onExitId = boom::Application::Default()->onExit([
        application=std::weak_ptr<boom::js::Value>(application),
        context=std::weak_ptr<boom::js::Context>(context)
    ](auto) {
        auto app = application.lock();
        auto ctx = context.lock();
        if (app && ctx) {
            boom::api::Trigger(ctx, app, boom::api::kApplicationExitEvent, {});
        }
    });

    auto onPollId = boom::Application::Default()->onPoll([
        application=std::weak_ptr<boom::js::Value>(application),
        context=std::weak_ptr<boom::js::Context>(context)
    ](auto) {
        auto app = application.lock();
        auto ctx = context.lock();
        if (app && ctx) {
            boom::api::Trigger(ctx, app, boom::api::kApplicationPollEvent, {});
        }
    });

    application->setDestructor([onExitId, onPollId](boom::js::ScopeRef scope) {
        boom::Application::Default()->onExit.remove(onExitId);
        boom::Application::Default()->onPoll.remove(onPollId);
    });

    application->defineProperty("title", [](boom::js::ScopeRef scope) {
        try {
            return boom::js::Value::String(scope->context(), boom::Application::Default()->title());
        } catch (boom::Error& e) {
            throw e.extend("Failed to get application title");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const title = [&]{
                try {
                    return value->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("Title must be a string");
                }
            }();
            boom::Application::Default()->setTitle(title);
        } catch (boom::Error& e) {
            throw e.extend("Failed to set application title");
        }
    });

    application->defineMethod("on", [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const callback = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(boom::api::kApplicationEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kApplicationEventList, ", "));
            }
            boom::api::Subscribe(scope->context(), scope->thisObject(), event, callback);
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    });

    application->defineMethod("off", [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const callback = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(boom::api::kApplicationEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kApplicationEventList, ", "));
            }
            boom::api::Unsubscribe(scope->context(), scope->thisObject(), event, callback);
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    });

    application->defineMethod("exit", [](boom::js::ScopeRef scope) {
        try {
            boom::Application::Default()->exit();
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to exit the application");
        }
    });

    context->globalThis()->setProperty("application", application);
}

} /* namespace boom::api */