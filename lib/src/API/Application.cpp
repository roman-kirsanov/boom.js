#include <map>
#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
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

    auto listeners = std::make_shared<std::map<std::string, std::vector<boom::js::ValueRef>>>();
    auto application = boom::js::Value::Object(context);

    boom::Application::Default()->onExit([contextWeak=std::weak_ptr<boom::js::Context>(context), listeners](auto) {
        if (auto context = contextWeak.lock()) {
            for (auto callback : (*listeners)[boom::api::kApplicationExitEvent]) {
                if (callback->isFunction()) {
                    callback->call(boom::js::Value::Undefined(context), {});
                }
            }
            return true;
        } else {
            return false;
        }
    });

    boom::Application::Default()->onPoll([contextWeak=std::weak_ptr<boom::js::Context>(context), listeners](auto) {
        if (auto context = contextWeak.lock()) {
            for (auto callback : (*listeners)[boom::api::kApplicationPollEvent]) {
                if (callback->isFunction()) {
                    callback->call(boom::js::Value::Undefined(context), {});
                }
            }
            return true;
        } else {
            return false;
        }
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

    application->defineMethod("on", [listeners](boom::js::ScopeRef scope) {
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
            (*listeners)[event].push_back(callback);
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    });

    application->defineMethod("off", [listeners](boom::js::ScopeRef scope) {
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
            boom::Remove((*listeners)[event], callback);
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