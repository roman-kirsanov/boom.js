#include <map>
#include <string>
#include <vector>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/View.hpp>
#include <Boom/API/Window.hpp>

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

struct WindowPayload : public boom::Shared {
    boom::WindowRef window;
    std::map<
        std::string,
        std::vector<boom::js::ValueRef>
    > listeners;
};

void InitWindowAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitWindowAPI() failed: \"context\" cannot be nullptr");
    }

    auto windowClass = boom::MakeShared<boom::js::Class>("Window");

    windowClass->setConstructor([](boom::js::ScopeRef scope) {
        auto payload = boom::MakeShared<boom::api::WindowPayload>();

        payload->window = boom::MakeShared<boom::Window>();
        payload->window->onShow([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowShowEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onHide([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowHideEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onClose([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowCloseEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onResize([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowResizeEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onMaximize([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowMaximizeEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onMinimize([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowMinimizeEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onDemaximize([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowDemaximizeEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onDeminimize([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowDeminimizeEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });
        payload->window->onPixelratio([
            contextWeak=std::weak_ptr<boom::js::Context>(scope->context()),
            payloadWeak=std::weak_ptr<boom::api::WindowPayload>(payload)
        ](boom::WindowRef window) {
            auto context = contextWeak.lock();
            auto payload = payloadWeak.lock();
            if (context && payload) {
                for (auto callback : payload->listeners[boom::api::kWindowPixelratioEvent]) {
                    if (callback->isFunction()) {
                        callback->call(boom::js::Value::Undefined(context), {});
                    }
                }
                return true;
            } else {
                return false;
            }
        });

        scope->thisObject()->setPrivate(payload);

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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::api::Vec2ToValue(scope->context(), payload->window->pixelratio());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window pixelratio");
        }
    });

    windowClass->defineProperty("size", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::api::Vec2ToValue(scope->context(), payload->window->size());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setSize(size);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window size");
        }
    });

    windowClass->defineProperty("title", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::String(scope->context(), payload->window->title());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setTitle(title);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window title");
        }
    });

    windowClass->defineProperty("visible", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->visible());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setVisible(visible);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window visible");
        }
    });

    windowClass->defineProperty("closable", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->closable());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setClosable(closable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window closable");
        }
    });

    windowClass->defineProperty("sizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->sizable());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setSizable(sizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window sizable");
        }
    });

    windowClass->defineProperty("maximizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->maximizable());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setMaximizable(maximizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximizable");
        }
    });

    windowClass->defineProperty("minimizable", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->minimizable());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setMinimizable(minimizable);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimizable");
        }
    });

    windowClass->defineProperty("maximized", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->maximized());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setMaximized(maximized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window maximized");
        }
    });

    windowClass->defineProperty("minimized", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->minimized());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setMinimized(minimized);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window minimized");
        }
    });

    windowClass->defineProperty("topmost", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                return boom::js::Value::Boolean(scope->context(), payload->window->topmost());
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setTopmost(topmost);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window topmost");
        }
    });

    windowClass->defineProperty("view", [](boom::js::ScopeRef scope) {
        try {
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                if (auto view = payload->window->view()) {
                    return view->getValue<boom::js::Value>(boom::api::kViewValueKey);
                } else {
                    return boom::js::Value::Undefined(scope->context());
                }
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to get window view");
        }
    }, [](boom::js::ScopeRef scope, boom::js::ValueRef value) {
        try {
            auto const view = [&]{
                if (auto view = value->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("First argument must be a View");
                }
            }();
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->setView(view);
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to set window view");
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->listeners[event].push_back(callback);
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                boom::Remove(payload->listeners[event], callback);
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
            if (auto payload = scope->thisObject()->getPrivate<boom::api::WindowPayload>()) {
                payload->window->center();
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a Window");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to center a window");
        }
    });

    windowClass->install(context);
}

} /* namespace boom::api */