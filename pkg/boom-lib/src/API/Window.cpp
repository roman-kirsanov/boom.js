#include <map>
#include <string>
#include <vector>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/View.hpp>
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

    auto windowClass = boom::MakeShared<boom::js::Class>("Window");

    windowClass->setConstructor([](boom::js::ScopeRef scope) {
        try {
            auto initPrivate = scope->thisObject()->getProperty("_initPrivate");
            auto initListeners = scope->thisObject()->getProperty("_initListeners");
            if (initPrivate->isFunction()) {
                initPrivate->call(scope->thisObject(), {});
            } else {
                throw boom::Error("_initPrivate is not a function");
            }
            if (initListeners->isFunction()) {
                initListeners->call(scope->thisObject(), {});
            } else {
                throw boom::Error("_initListeners is not a function");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to construct a Window");
        }
    });

    windowClass->setDestructor([](boom::js::ScopeRef scope) {
        if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
            view->deleteValue(boom::api::kWindowValueKey);
        }
    });

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

    windowClass->defineProperty("view", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                if (auto view = window->view()) {
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
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->setView(view);
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
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                boom::api::Subscribe(scope->thisObject(), event, callback);
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
                boom::api::Unsubscribe(scope->thisObject(), event, callback);
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

    windowClass->defineMethod("_initPrivate", [](boom::js::ScopeRef scope) {
        try {
            auto window = boom::MakeShared<boom::Window>();
            scope->thisObject()->unprotect();
            scope->thisObject()->setPrivate(window);
            window->setValue(boom::api::kWindowValueKey, scope->thisObject());
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to init private");
        }
    });

    windowClass->defineMethod("_initListeners", [](boom::js::ScopeRef scope) {
        try {
            if (auto window = scope->thisObject()->getPrivate<boom::Window>()) {
                window->onShow([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "show", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onHide([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "hide", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onClose([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "close", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onResize([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "resize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onMaximize([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "maximize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onMinimize([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "minimize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onDemaximize([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "demaximize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onDeminimize([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "deminimize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                window->onPixelratio([](boom::WindowRef window) {
                    if (auto value = window->getValue<boom::js::Value>(boom::api::kWindowValueKey)) {
                        boom::api::Trigger(value, "pixelratio", {});
                        return true;
                    } else {
                        return false;
                    }
                });
            }
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to init listeners");
        }
    });

    windowClass->install(context);
}

} /* namespace boom::api */