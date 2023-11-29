#include <string>
#include <vector>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/Window.hpp>
#include <Boom/API/Utilities.hpp>

namespace boom::api {

auto constexpr kWindowValueKey = 1;
auto constexpr kWindowShowEvent = "show";
auto constexpr kWindowHideEvent = "hide";
auto constexpr kWindowCloseEvent = "close";
auto constexpr kWindowResizeEvent = "resize";
auto constexpr kWindowMaximizeEvent = "maximize";
auto constexpr kWindowMinimizeEvent = "minimize";
auto constexpr kWindowDemaximizeEvent = "demaximize";
auto constexpr kWindowDeminimizeEvent = "deminimize";
auto constexpr kWindowPixelratioEvent = "pixelratio";

static auto const kWindowEventList = std::vector<std::string>({
    boom::api::kWindowShowEvent,       boom::api::kWindowHideEvent,
    boom::api::kWindowCloseEvent,      boom::api::kWindowResizeEvent,
    boom::api::kWindowMaximizeEvent,   boom::api::kWindowMinimizeEvent,
    boom::api::kWindowDemaximizeEvent, boom::api::kWindowDeminimizeEvent,
    boom::api::kWindowPixelratioEvent
});

void InitWindowAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitWindowAPI() failed: \"context\" cannot be nullptr");
    }

    auto windowClass = boom::MakeShared<boom::js::Class>();

    windowClass->setConstructor([](boom::js::ScopeRef scope) {
        auto window = boom::MakeShared<boom::Window>();
        scope->thisObject()->setPrivate(window);
        window->setValue(boom::api::kWindowValueKey, scope->thisObject());
        window->onShow([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowShowEvent, {});
            }
        });
        window->onHide([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowHideEvent, {});
            }
        });
        window->onClose([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowCloseEvent, {});
            }
        });
        window->onResize([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowResizeEvent, {});
            }
        });
        window->onMaximize([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowMaximizeEvent, {});
            }
        });
        window->onMinimize([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowMinimizeEvent, {});
            }
        });
        window->onDemaximize([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowDemaximizeEvent, {});
            }
        });
        window->onDeminimize([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowDeminimizeEvent, {});
            }
        });
        window->onPixelratio([context=scope->context()](boom::WindowRef window) {
            if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                boom::api::Trigger(context, value, boom::api::kWindowPixelratioEvent, {});
            }
        });

        // window->onRender([context=scope->context(), window]() {
        //     for (auto& listener : window->listeners["render"]) {
        //         listener->call(boom::js::Value::Undefined(context), {});
        //     }
        // });
        // window->onMouseMove([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["mousemove"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mousemoveInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mousemoveInfo });
        //     }
        // });
        // window->onMouseEnter([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["mouseenter"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseenterInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseenterInfo });
        //     }
        // });
        // window->onMouseExit([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["mouseexit"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseexitInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseexitInfo });
        //     }
        // });
        // window->onMouseWheel([context=scope->context(), window](auto wheel, auto modifiers) {
        //     for (auto& listener : window->listeners["mousewheel"]) {
        //         auto wheelValue = boom::api::Vec2ToValue(context, wheel);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mousewheelInfo = boom::js::Value::Object(context, {
        //             { "wheel", wheelValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mousewheelInfo });
        //     }
        // });
        // window->onMouseClick([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["mouseclick"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto mouseclickInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { mouseclickInfo });
        //     }
        // });
        // window->onLButtonDown([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["lbuttondown"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto lbuttondownInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { lbuttondownInfo });
        //     }
        // });
        // window->onRButtonDown([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["rbuttondown"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto rbuttondownInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { rbuttondownInfo });
        //     }
        // });
        // window->onLButtonUp([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["lbuttonup"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto lbuttonupInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { lbuttonupInfo });
        //     }
        // });
        // window->onRButtonUp([context=scope->context(), window](auto position, auto modifiers) {
        //     for (auto& listener : window->listeners["rbuttonup"]) {
        //         auto positionValue = boom::api::Vec2ToValue(context, position);
        //         auto modifiersValue = boom::js::KeyModifiersToValue(context, modifiers);
        //         auto rbuttonupInfo = boom::js::Value::Object(context, {
        //             { "position", positionValue },
        //             { "modifiers", modifiersValue }
        //         });
        //         listener->call(boom::js::Value::Undefined(context), { rbuttonupInfo });
        //     }
        // });
        // window->onKeyDown([context=scope->context(), window](auto key, auto modifiers, auto input) {
        //     for (auto& listener : window->listeners["keydown"]) {
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
        // window->onKeyUp([context=scope->context(), window](auto key, auto modifiers, auto input) {
        //     for (auto& listener : window->listeners["keyup"]) {
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
    });

    windowClass->setDestructor([](boom::js::ScopeRef scope) {});

    windowClass->defineProperty("pixelratio", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::api::Vec2ToValue(scope->context(), window->pixelratio());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window pixelratio");
        }
    });

    windowClass->defineProperty("size", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::api::Vec2ToValue(scope->context(), window->size());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window size");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const size = [&]{
                try {
                    return boom::api::ValueToVec2(scope->context(), value);
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a Vec2");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setSize(size);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window size");
        }
    });

    windowClass->defineProperty("title", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::String(scope->context(), window->title());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window title");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const title = [&]{
                try {
                    return value->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setTitle(title);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window title");
        }
    });

    windowClass->defineProperty("visible", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->visible());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window visible");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const visible = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setVisible(visible);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window visible");
        }
    });

    windowClass->defineProperty("closable", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->closable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window closable");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const closable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setClosable(closable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window closable");
        }
    });

    windowClass->defineProperty("sizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->sizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window sizable");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const sizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setSizable(sizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window sizable");
        }
    });

    windowClass->defineProperty("maximizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->maximizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window maximizable");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const maximizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setMaximizable(maximizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximizable");
        }
    });

    windowClass->defineProperty("minimizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->minimizable());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window minimizable");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const minimizable = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setMinimizable(minimizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimizable");
        }
    });

    windowClass->defineProperty("maximized", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->maximized());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window maximized");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const maximized = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setMaximized(maximized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximized");
        }
    });

    windowClass->defineProperty("minimized", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->minimized());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window minimized");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const minimized = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setMinimized(minimized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimized");
        }
    });

    windowClass->defineProperty("topmost", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                return boom::js::Value::Boolean(scope->context(), window->topmost());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window topmost");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const topmost = [&]{
                try {
                    return value->booleanValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a boolean");
                }
            }();
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setTopmost(topmost);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window topmost");
        }
    });

    windowClass->defineMethod("on", [](boom::js::ScopeRef scope) {
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
            if (boom::Includes(boom::api::kWindowEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kWindowEventList, ", "));
            }
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                boom::api::Subscribe(scope->context(), scope->thisObject(), event, callback);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    });

    windowClass->defineMethod("off", [](boom::js::ScopeRef scope) {
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
            if (boom::Includes(boom::api::kWindowEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kWindowEventList, ", "));
            }
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                boom::api::Unsubscribe(scope->context(), scope->thisObject(), event, callback);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    });

    windowClass->defineMethod("center", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->center();
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to center a window");
        }
    });

    windowClass->install("Window", context);
}

} /* namespace boom::api */