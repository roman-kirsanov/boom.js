#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/View.hpp>

namespace boom::api {

auto constexpr kViewJSValueKey = 1;

void InitViewAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitViewAPI() failed: \"context\" cannot be nullptr");
    }

    auto viewClass = boom::MakeShared<boom::js::Class>();
    viewClass->setConstructor([](boom::js::ScopeRef scope) {
        auto view = boom::MakeShared<boom::View>();
        scope->thisObject()->setPrivate(view);
        view->setValue(
            boom::api::kViewJSValueKey,
            scope->thisObject(),
            { .refType = boom::StoreValueRefType::Weak }
        );
    });
    viewClass->setDestructor([](boom::js::ScopeRef scope) {
        if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
            ;
        }
    });
    viewClass->defineProperty("children", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                return boom::js::Value::Array(
                    scope->context(),
                    boom::Map<boom::ViewRef, boom::js::ValueRef>(view->children(), [&](boom::ViewRef child) {
                        return child->getValue<boom::js::Value>(boom::api::kViewJSValueKey);
                    })
                );
            } else {
                throw boom::Error("Object is not a view");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get view children");
        }
    });

    // auto applicationClass = boom::MakeShared<boom::js::Class>();
    // applicationClass->setConstructor(ctor);
    // applicationClass->setDestructor(dtor);
    // applicationClass->defineProperty("title", getTitle, setTitle);
    // applicationClass->defineMethod("on", on);
    // applicationClass->defineMethod("off", off);
    // applicationClass->defineMethod("exit", exit);
    // applicationClass->install("View", context);
    // context->evaluate("globalThis.application = new View()");
}

} /* namespace boom::api */