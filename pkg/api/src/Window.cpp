#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/Window.hpp>

namespace boom::api {

void InitWindowAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitWindowAPI() failed: \"context\" cannot be nullptr");
    }

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

    static auto const ctor = [](boom::js::ScopeRef scope) {
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
        // payload->window->onRender([context=scope->context(), payload]() {
        //     for (auto& listener : payload->listeners["render"]) {
        //         listener->call(boom::js::Value::Undefined(context), {});
        //     }
        // });
        // payload->window->onMouseMove([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["mousemove"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mousemoveInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mousemoveInfo });
        //     }
        // });
        // payload->window->onMouseEnter([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["mouseenter"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseenterInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseenterInfo });
        //     }
        // });
        // payload->window->onMouseExit([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["mouseexit"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseexitInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseexitInfo });
        //     }
        // });
        // payload->window->onMouseWheel([context=scope->context(), payload](auto wheel, auto modifiers) {
        //     for (auto& listener : payload->listeners["mousewheel"]) {
        //         auto wheelValue = boom::js::Vec2ToValue(context, wheel);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mousewheelInfo = boom::js::Value::Object(context, {
        //             { "wheel", wheelValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mousewheelInfo });
        //     }
        // });
        // payload->window->onMouseClick([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["mouseclick"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseclickInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseclickInfo });
        //     }
        // });
        // payload->window->onLButtonDown([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["lbuttondown"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto lbuttondownInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { lbuttondownInfo });
        //     }
        // });
        // payload->window->onRButtonDown([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["rbuttondown"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto rbuttondownInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { rbuttondownInfo });
        //     }
        // });
        // payload->window->onLButtonUp([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["lbuttonup"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto lbuttonupInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { lbuttonupInfo });
        //     }
        // });
        // payload->window->onRButtonUp([context=scope->context(), payload](auto position, auto modifiers) {
        //     for (auto& listener : payload->listeners["rbuttonup"]) {
        //         auto positionValue = boom::js::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto rbuttonupInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { rbuttonupInfo });
        //     }
        // });
        // payload->window->onKeyDown([context=scope->context(), payload](auto key, auto modifiers, auto input) {
        //     for (auto& listener : payload->listeners["keydown"]) {
        //         auto keyValue = boom::js::KeyToValue(context, key);
        //         auto inputValue = boom::js::Value::String(context, input);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto keydownInfo = boom::js::Value::Object(context, {
        //             { "key", keyValue },
        //             { "input", inputValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { keydownInfo });
        //     }
        // });
        // payload->window->onKeyUp([context=scope->context(), payload](auto key, auto modifiers, auto input) {
        //     for (auto& listener : payload->listeners["keyup"]) {
        //         auto keyValue = boom::js::KeyToValue(context, key);
        //         auto inputValue = boom::js::Value::String(context, input);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto keyupInfo = boom::js::Value::Object(context, {
        //             { "key", keyValue },
        //             { "input", inputValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { keyupInfo });
        //     }
        // });
        scope->thisObject()->setPrivate(payload);
    };

    static auto const dtor = [](boom::js::ScopeRef scope) {
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
            // payload->window->onRender.clear();
            // payload->window->onMouseMove.clear();
            // payload->window->onMouseEnter.clear();
            // payload->window->onMouseExit.clear();
            // payload->window->onMouseWheel.clear();
            // payload->window->onMouseClick.clear();
            // payload->window->onLButtonDown.clear();
            // payload->window->onRButtonDown.clear();
            // payload->window->onLButtonUp.clear();
            // payload->window->onRButtonUp.clear();
            // payload->window->onKeyDown.clear();
            // payload->window->onKeyUp.clear();
        }
    };

    static auto const getPixelratio = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Vec2ToValue(scope->context(), payload->window->pixelratio());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window pixelratio");
        }
    };

    static auto const setViewport = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const viewport = [&]{
                try {
                    return boom::js::ValueToVec2(scope->context(), value);
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a Vec2");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                // payload->window->setViewport(viewport);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window viewport");
        }
    };

    static auto const getViewport = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Vec2ToValue(scope->context(), {} /* payload->window->viewport() */);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window viewport");
        }
    };

    static auto const setSize = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const size = [&]{
                try {
                    return boom::js::ValueToVec2(scope->context(), value);
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a Vec2");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setSize(size);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window size");
        }
    };

    static auto const getSize = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Vec2ToValue(scope->context(), payload->window->size());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window size");
        }
    };

    static auto const setVisible = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const visible = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setVisible(visible);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window visible");
        }
    };

    static auto const getVisible = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->visible());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window visible");
        }
    };

    static auto const setClosable = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const closable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setClosable(closable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window closable");
        }
    };

    static auto const getClosable = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->closable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window closable");
        }
    };

    static auto const setSizable = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const sizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setSizable(sizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window sizable");
        }
    };

    static auto const getSizable = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->sizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window sizable");
        }
    };

    static auto const setMaximizable = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const maximizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setMaximizable(maximizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximizable");
        }
    };

    static auto const getMaximizable = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->maximizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window maximizable");
        }
    };

    static auto const setMinimizable = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const minimizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setMinimizable(minimizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimizable");
        }
    };

    static auto const getMinimizable = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->minimizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window minimizable");
        }
    };

    static auto const setMaximized = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const maximized = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setMaximized(maximized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximized");
        }
    };

    static auto const getMaximized = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->maximized());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window maximized");
        }
    };

    static auto const setMinimized = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const minimized = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setMinimized(minimized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimized");
        }
    };

    static auto const getMinimized = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->minimized());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window minimized");
        }
    };

    static auto const setTopmost = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const topmost = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setTopmost(topmost);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window topmost");
        }
    };

    static auto const getTopmost = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->topmost());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window topmost");
        }
    };

    static auto const setTitle = [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const title = [&]{
                try {
                    return value->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->setTitle(title);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window title");
        }
    };

    static auto const getTitle = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                return boom::js::Value::String(scope->context(), payload->window->title());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window title");
        }
    };

    static auto const on = [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const func = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(WINDOW_EVENTS, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(WINDOW_EVENTS, ", "));
            }
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->listeners[event].push_back(func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    };

    static auto const off = [](boom::js::ScopeRef scope) {
        try {
            auto const event = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const func = [&]{
                try {
                    return scope->getArg(1)->functionValue();
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be a function");
                }
            }();
            if (boom::Includes(WINDOW_EVENTS, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(WINDOW_EVENTS, ", "));
            }
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                boom::Remove(payload->listeners[event], func);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    };

    static auto const center = [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<WindowPayload>()) {
                payload->window->center();
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to center a window");
        }
    };

    auto windowClass = boom::MakeShared<boom::js::Class>();
    windowClass->setConstructor(ctor);
    windowClass->setDestructor(dtor);
    windowClass->defineProperty("pixelratio", getPixelratio);
    windowClass->defineProperty("viewport", getViewport, setViewport);
    windowClass->defineProperty("size", getSize, setSize);
    windowClass->defineProperty("title", getTitle, setTitle);
    windowClass->defineProperty("visible", getVisible, setVisible);
    windowClass->defineProperty("closable", getClosable, setClosable);
    windowClass->defineProperty("sizable", getSizable, setSizable);
    windowClass->defineProperty("maximizable", getMaximizable, setMaximizable);
    windowClass->defineProperty("minimizable", getMinimizable, setMinimizable);
    windowClass->defineProperty("maximized", getMaximized, setMaximized);
    windowClass->defineProperty("minimized", getMinimized, setMinimized);
    windowClass->defineMethod("on", on);
    windowClass->defineMethod("off", off);
    windowClass->defineMethod("center", center);
    windowClass->install("Window", context);
}

} /* namespace boom::api */