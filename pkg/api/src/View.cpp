#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/View.hpp>

namespace boom::api {

class View final : public boom::View {
public:
    View();
    boom::js::ValueRef value() const;
    void setValue(boom::js::ValueRef);
    virtual ~View();
private:
    boom::js::ValueWRef _value;
};

View::View()
    : _value() {}

View::~View() {}

boom::js::ValueRef View::value() const {
    return _value.lock();
}

void View::setValue(boom::js::ValueRef value) {
    _value = value;
}

void InitViewAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitViewAPI() failed: \"context\" cannot be nullptr");
    }

    auto viewClass = boom::MakeShared<boom::js::Class>();
    viewClass->setConstructor([](boom::js::ScopeRef scope) {
        auto view = boom::MakeShared<boom::api::View>();
        view->setValue(scope->thisObject());
        scope->thisObject()->setPrivate(view);
        ;
    });
    viewClass->setDestructor([](boom::js::ScopeRef scope) {
        if (auto view = scope->thisObject()->getPrivate<boom::api::View>()) {
            ;
        }
    });
    viewClass->defineProperty("children", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::api::View>()) {
                return boom::js::Value::Array(
                    scope->context(),
                    boom::Map<boom::ViewRef, boom::js::ValueRef>(view->children(), [&](auto child) {
                        if (auto view = std::dynamic_pointer_cast<boom::api::View>(child)) {
                            return view->value();
                        } else {
                            throw boom::Error("Child is not an object");
                        }
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