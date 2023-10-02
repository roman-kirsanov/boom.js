#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/Window.hpp>

namespace boom::api {

void InitWindowAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    struct WindowPayload : public boom::Shared {
        std::shared_ptr<boom::Window> window;
        std::map<std::string, std::vector<boom::js::ValueRef>> listeners;
    };

    static auto const WINDOW_EVENTS = std::vector<std::string>({
        "show", "hide", "close", "resize", "maximize", "minimize",
        "demaximize", "deminimize", "pixelratio", "render", "mousemove",
        "mouseenter", "mouseexit", "mousewheel", "mouseclick", "lbuttondown",
        "rbuttondown", "lbuttonup", "rbuttonup", "keydown", "keyup"
    });

    static auto ctor = [](boom::js::ScopeRef scope) {
        auto payload = boom::MakeShared<WindowPayload>();
        payload->window = boom::MakeShared<boom::Window>();
        payload->window->onShow([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["show"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onHide([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["hide"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onClose([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["close"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onResize([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["resize"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onMaximize([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["maximize"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onMinimize([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["minimize"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onDemaximize([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["demaximize"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onDeminimize([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["deminimize"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onPixelratio([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["pixelratio"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onRender([context=scope->context(), payload]() {
            for (auto& listener : payload->listeners["render"]) {
                listener->call(boom::js::Value::Undefined(context), {});
            }
        });
        payload->window->onMouseMove([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["mousemove"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto mousemoveInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { mousemoveInfo });
            }
        });
        payload->window->onMouseEnter([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["mouseenter"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto mouseenterInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { mouseenterInfo });
            }
        });
        payload->window->onMouseExit([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["mouseexit"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto mouseexitInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { mouseexitInfo });
            }
        });
        payload->window->onMouseWheel([context=scope->context(), payload](auto wheel, auto modifiers) {
            for (auto& listener : payload->listeners["mousewheel"]) {
                auto wheelValue = boom::js::Vec2ToValue(context, wheel);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto mousewheelInfo = boom::js::Value::Object(context, {
                    { "wheel", wheelValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { mousewheelInfo });
            }
        });
        payload->window->onMouseClick([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["mouseclick"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto mouseclickInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { mouseclickInfo });
            }
        });
        payload->window->onLButtonDown([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["lbuttondown"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto lbuttondownInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { lbuttondownInfo });
            }
        });
        payload->window->onRButtonDown([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["rbuttondown"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto rbuttondownInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { rbuttondownInfo });
            }
        });
        payload->window->onLButtonUp([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["lbuttonup"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto lbuttonupInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { lbuttonupInfo });
            }
        });
        payload->window->onRButtonUp([context=scope->context(), payload](auto position, auto modifiers) {
            for (auto& listener : payload->listeners["rbuttonup"]) {
                auto positionValue = boom::js::Vec2ToValue(context, position);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto rbuttonupInfo = boom::js::Value::Object(context, {
                    { "position", positionValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { rbuttonupInfo });
            }
        });
        payload->window->onKeyDown([context=scope->context(), payload](auto key, auto modifiers, auto input) {
            for (auto& listener : payload->listeners["keydown"]) {
                auto keyValue = boom::js::KeyToValue(context, key);
                auto inputValue = boom::js::Value::String(context, input);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto keydownInfo = boom::js::Value::Object(context, {
                    { "key", keyValue },
                    { "input", inputValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { keydownInfo });
            }
        });
        payload->window->onKeyUp([context=scope->context(), payload](auto key, auto modifiers, auto input) {
            for (auto& listener : payload->listeners["keyup"]) {
                auto keyValue = boom::js::KeyToValue(context, key);
                auto inputValue = boom::js::Value::String(context, input);
                auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
                auto keyupInfo = boom::js::Value::Object(context, {
                    { "key", keyValue },
                    { "input", inputValue },
                    { "modifiers", modifiersValue }
                });
                listener->call(boom::js::Value::Undefined(context), { keyupInfo });
            }
        });
        scope->thisObject()->setPrivate(payload);
        scope->thisObject()->setFinalize([](boom::js::ScopeRef scope) {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->onShow.clear();
                payload->window->onHide.clear();
                payload->window->onClose.clear();
                payload->window->onResize.clear();
                payload->window->onMaximize.clear();
                payload->window->onMinimize.clear();
                payload->window->onDemaximize.clear();
                payload->window->onDeminimize.clear();
                payload->window->onPixelratio.clear();
                payload->window->onRender.clear();
                payload->window->onMouseMove.clear();
                payload->window->onMouseEnter.clear();
                payload->window->onMouseExit.clear();
                payload->window->onMouseWheel.clear();
                payload->window->onMouseClick.clear();
                payload->window->onLButtonDown.clear();
                payload->window->onRButtonDown.clear();
                payload->window->onLButtonUp.clear();
                payload->window->onRButtonUp.clear();
                payload->window->onKeyDown.clear();
                payload->window->onKeyUp.clear();
            }
        });
    };

    static auto getPixelratio = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Vec2ToValue(scope->context(), payload->window->pixelratio()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setViewport = [](boom::js::ScopeRef scope) {
        auto const viewportArg = boom::js::ValueToVec2(scope->context(), scope->getArg(0));
        if (!viewportArg) {
            scope->setError("First argument must be a Vec2");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setViewport(viewportArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getViewport = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Vec2ToValue(scope->context(), payload->window->viewport()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setSize = [](boom::js::ScopeRef scope) {
        auto const sizeArg = boom::js::ValueToVec2(scope->context(), scope->getArg(0));
        if (!sizeArg) {
            scope->setError("First argument must be a Vec2");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setSize(sizeArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getSize = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Vec2ToValue(scope->context(), payload->window->size()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setVisible = [](boom::js::ScopeRef scope) {
        auto const visibleArg = scope->getArg(0)->booleanValue();
        if (!visibleArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setVisible(visibleArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getVisible = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->visible()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setClosable = [](boom::js::ScopeRef scope) {
        auto const closableArg = scope->getArg(0)->booleanValue();
        if (!closableArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setClosable(closableArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getClosable = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->closable()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setSizable = [](boom::js::ScopeRef scope) {
        auto const sizableArg = scope->getArg(0)->booleanValue();
        if (!sizableArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setSizable(sizableArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getSizable = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->sizable()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setMaximizable = [](boom::js::ScopeRef scope) {
        auto const maximizableArg = scope->getArg(0)->booleanValue();
        if (!maximizableArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setMaximizable(maximizableArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getMaximizable = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->maximizable()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setMinimizable = [](boom::js::ScopeRef scope) {
        auto const minimizableArg = scope->getArg(0)->booleanValue();
        if (!minimizableArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setMinimizable(minimizableArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getMinimizable = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->minimizable()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setMaximized = [](boom::js::ScopeRef scope) {
        auto const maximizedArg = scope->getArg(0)->booleanValue();
        if (!maximizedArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setMaximized(maximizedArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getMaximized = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->maximized()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setMinimized = [](boom::js::ScopeRef scope) {
        auto const minimizedArg = scope->getArg(0)->booleanValue();
        if (!minimizedArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setMinimized(minimizedArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getMinimized = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->minimized()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setTopmost = [](boom::js::ScopeRef scope) {
        auto const topmostArg = scope->getArg(0)->booleanValue();
        if (!topmostArg) {
            scope->setError("First argument must be a boolean");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setTopmost(topmostArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getTopmost = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::Boolean(scope->context(), payload->window->topmost()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto setTitle = [](boom::js::ScopeRef scope) {
        auto const titleArg = scope->getArg(0)->stringValue();
        if (!titleArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->setTitle(titleArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto getTitle = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            scope->setResult(boom::js::Value::String(scope->context(), payload->window->title()));
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto on = [](boom::js::ScopeRef scope) {
        auto const eventArg = scope->getArg(0)->stringValue();
        auto const funcArg = scope->getArg(1)->functionValue();
        if (!eventArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (boom::Includes(WINDOW_EVENTS, eventArg.value()) == false) {
            scope->setError("First argument must be one of:????");
            return;
        }
        if (!funcArg) {
            scope->setError("Second argument must be a function");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->listeners[eventArg.value()].push_back(funcArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto off = [](boom::js::ScopeRef scope) {
        auto const eventArg = scope->getArg(0)->stringValue();
        auto const funcArg = scope->getArg(1)->functionValue();
        if (!eventArg) {
            scope->setError("First argument must be a string");
            return;
        }
        if (boom::Includes(WINDOW_EVENTS, eventArg.value()) == false) {
            scope->setError("First argument must be one of: ???");
            return;
        }
        if (!funcArg) {
            scope->setError("Second argument must be a function");
            return;
        }
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            boom::Remove(payload->listeners[eventArg.value()], funcArg.value());
        } else {
            scope->setError("Object is not a Window");
        }
    };

    static auto center = [](boom::js::ScopeRef scope) {
        if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
            payload->window->center();
        } else {
            scope->setError("Object is not a Window");
        }
    };

    auto windowProto = boom::js::Value::Object(context);
    windowProto->defineProperty("pixelratio", getPixelratio).value();
    windowProto->defineProperty("viewport", getViewport, setViewport).value();
    windowProto->defineProperty("size", getSize, setSize).value();
    windowProto->defineProperty("title", getTitle, setTitle).value();
    windowProto->defineProperty("visible", getVisible, setVisible).value();
    windowProto->defineProperty("closable", getClosable, setClosable).value();
    windowProto->defineProperty("sizable", getSizable, setSizable).value();
    windowProto->defineProperty("maximizable", getMaximizable, setMaximizable).value();
    windowProto->defineProperty("minimizable", getMinimizable, setMinimizable).value();
    windowProto->defineProperty("maximized", getMaximized, setMaximized).value();
    windowProto->defineProperty("minimized", getMinimized, setMinimized).value();
    windowProto->setProperty("on", boom::js::Value::Function(context, on), { .readOnly = true }).value();
    windowProto->setProperty("off", boom::js::Value::Function(context, off), { .readOnly = true }).value();
    windowProto->setProperty("center", boom::js::Value::Function(context, center), { .readOnly = true }).value();

    auto windowClass = boom::js::Value::Function(context, ctor);
    windowClass->setProperty("prototype", windowProto).value();

    context->globalThis()->setProperty("Window", windowClass).value();
}

} /* namespace boom::api */