#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
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
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get view children");
        }
    });

    viewClass->defineProperty("parent", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                return view->parent()->getValue<boom::js::Value>(boom::api::kViewJSValueKey);
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get view parent");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const parent = [&]{
                try {
                    return value->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("Value must be a View");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->setParent(parent);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set view parent");
        }
    });

    viewClass->defineProperty("position", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                return boom::api::Vec2ToValue(scope->context(), view->position());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get view position");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const position = [&]() {
                try {
                    return boom::api::ValueToVec2(scope->context(), value);
                } catch (boom::Error& e) {
                    throw e.extend("Value must be a Vec2");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->setPosition(position);
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set view position");
        }
    });

    viewClass->defineProperty("size", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                return boom::api::Vec2ToValue(scope->context(), view->size());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get view size");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const size = [&]() {
                try {
                    return boom::api::ValueToVec2(scope->context(), value);
                } catch (boom::Error& e) {
                    throw e.extend("Value must be a Vec2");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->setSize(size);
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set view size");
        }
    });

    viewClass->defineMethod("removeFromParent", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->removeFromParent();
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to remove view from its parent");
        }
    });

    viewClass->defineMethod("addChild", [](boom::js::ScopeRef scope) {
        try {
            auto const child = [&]{
                try {
                    return scope->getArg(0)->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a View");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->addChild(child);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to add view child");
        }
    });

    viewClass->defineMethod("removeChild", [](boom::js::ScopeRef scope) {
        try {
            auto const child = [&]{
                try {
                    return scope->getArg(0)->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a View");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->removeChild(child);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to remove view child");
        }
    });

    viewClass->defineMethod("replaceChild", [](boom::js::ScopeRef scope) {
        try {
            auto const child1 = [&]{
                try {
                    return scope->getArg(0)->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a View");
                }
            }();
            auto const child2 = [&]{
                try {
                    return scope->getArg(1)->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a View");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->replaceChild(child1, child2);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to replace view child");
        }
    });

    viewClass->defineMethod("insertChild", [](boom::js::ScopeRef scope) {
        try {
            auto const child = [&]{
                try {
                    return scope->getArg(0)->getPrivate<boom::View>();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a View");
                }
            }();
            auto const index = [&]{
                try {
                    return scope->getArg(1)->numberValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a number");
                }
            }();
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->insertChild(child, static_cast<std::size_t>(index));
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to insert view child");
        }
    });

    viewClass->install("View", context);
}

} /* namespace boom::api */