#include <vector>
#include <cassert>
#include <Boom.hpp>
#include <Boom/JS.hpp>
#include <Boom/API/Math.hpp>
#include <Boom/API/View.hpp>
#include <Boom/API/Input.hpp>
#include <Boom/API/Utilities.hpp>

namespace boom::api {

auto constexpr kViewAttachEvent = "attach";
auto constexpr kViewDetachEvent = "detach";
auto constexpr kViewResizeEvent = "resize";
auto constexpr kViewMouseMoveEvent = "mousemove";
auto constexpr kViewMouseEnterEvent = "mouseenter";
auto constexpr kViewMouseExitEvent = "mouseexit";
auto constexpr kViewMouseWheelEvent = "mousewheel";
auto constexpr kViewLButtonDownEvent = "lbuttondown";
auto constexpr kViewRButtonDownEvent = "rbuttondown";
auto constexpr kViewMButtonDownEvent = "mbuttondown";
auto constexpr kViewLButtonUpEvent = "lbuttonup";
auto constexpr kViewRButtonUpEvent = "rbuttonup";
auto constexpr kViewMButtonUpEvent = "mbuttonup";
auto constexpr kViewKeyDownEvent = "keydown";
auto constexpr kViewKeyUpEvent = "keyup";

static auto const kViewEventList = std::vector<std::string>({
    boom::api::kViewAttachEvent,      boom::api::kViewDetachEvent,      boom::api::kViewResizeEvent,
    boom::api::kViewMouseMoveEvent,   boom::api::kViewMouseEnterEvent,  boom::api::kViewMouseExitEvent,
    boom::api::kViewMouseWheelEvent,  boom::api::kViewLButtonDownEvent, boom::api::kViewRButtonDownEvent,
    boom::api::kViewMButtonDownEvent, boom::api::kViewLButtonUpEvent,   boom::api::kViewRButtonUpEvent,
    boom::api::kViewMButtonUpEvent,   boom::api::kViewKeyDownEvent,     boom::api::kViewKeyUpEvent
});

void InitViewAPI(boom::js::ContextRef context) {
    if (context == nullptr) {
        boom::Abort("boom::api::InitViewAPI() failed: \"context\" cannot be nullptr");
    }

    auto viewClass = boom::MakeShared<boom::js::Class>("View");

    viewClass->setConstructor([](boom::js::ScopeRef scope) {
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
            throw e.extend("Failed to construct a View");
        }
    });

    viewClass->setDestructor([](boom::js::ScopeRef scope) {
        if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
            view->deleteValue(boom::api::kViewValueKey);
        }
    });

    viewClass->defineProperty("children", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                return boom::js::Value::Array(
                    scope->context(),
                    boom::Map<boom::ViewRef, boom::js::ValueRef>(view->children(), [&](boom::ViewRef child) {
                        return child->getValue<boom::js::Value>(boom::api::kViewValueKey);
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
                return view->parent()->getValue<boom::js::Value>(boom::api::kViewValueKey);
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
                if (auto view = scope->getArg(0)->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("First argument must be a View");
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
                if (auto view = scope->getArg(0)->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("First argument must be a View");
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
                if (auto view = scope->getArg(0)->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("First argument must be a View");
                }
            }();
            auto const child2 = [&]{
                if (auto view = scope->getArg(1)->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("Second argument must be a View");
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
                if (auto view = scope->getArg(0)->getPrivate<boom::View>()) {
                    return view;
                } else {
                    throw boom::Error("First argument must be a View");
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

    viewClass->defineMethod("on", [](boom::js::ScopeRef scope) {
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
            if (boom::Includes(boom::api::kViewEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kViewEventList, ", "));
            }
            if (auto window = scope->thisObject()->getPrivate<boom::View>()) {
                boom::api::Subscribe(scope->thisObject(), event, callback);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to subscribe to an event");
        }
    });

    viewClass->defineMethod("off", [](boom::js::ScopeRef scope) {
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
            if (boom::Includes(boom::api::kViewEventList, event) == false) {
                throw boom::Error("First argument must be one of: " + boom::Join(boom::api::kViewEventList, ", "));
            }
            if (auto window = scope->thisObject()->getPrivate<boom::View>()) {
                boom::api::Unsubscribe(scope->thisObject(), event, callback);
                return boom::js::Value::Undefined(scope->context());
            } else {
                throw boom::Error("Object is not a View");
            }
        } catch (boom::Error& e) {
            throw e.extend("Failed to unsubscribe from an event");
        }
    });

    viewClass->defineMethod("_initPrivate", [](boom::js::ScopeRef scope) {
        try {
            auto view = boom::MakeShared<boom::View>();
            scope->thisObject()->unprotect();
            scope->thisObject()->setPrivate(view);
            view->setValue(boom::api::kViewValueKey, scope->thisObject());
            return boom::js::Value::Undefined(scope->context());
        } catch (boom::Error& e) {
            throw e.extend("Failed to init private");
        }
    });

    viewClass->defineMethod("_initListeners", [](boom::js::ScopeRef scope) {
        try {
            if (auto view = scope->thisObject()->getPrivate<boom::View>()) {
                view->onAttach([](boom::ViewRef view) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        boom::api::Trigger(value, "attach", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onDetach([](boom::ViewRef view) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        boom::api::Trigger(value, "detach", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onResize([](boom::ViewRef view) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        boom::api::Trigger(value, "resize", {});
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMouseMove([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMouseMoveEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMouseEnter([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMouseEnterEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMouseExit([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMouseExitEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMouseWheel([](boom::ViewRef view, boom::Vec2 wheel, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto wheelValue = boom::api::Vec2ToValue(value->context(), wheel);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "wheel", wheelValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMouseWheelEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onLButtonDown([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewLButtonDownEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onRButtonDown([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewRButtonDownEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMButtonDown([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMButtonDownEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onLButtonUp([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewLButtonUpEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onRButtonUp([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewRButtonUpEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onMButtonUp([](boom::ViewRef view, boom::Vec2 position, boom::KeyModifiers modifiers) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto positionValue = boom::api::Vec2ToValue(value->context(), position);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "position", positionValue },
                            { "modifiers", modifiersValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewMButtonUpEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onKeyDown([](boom::ViewRef view, boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto keyValue = boom::api::KeyToValue(value->context(), key);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto inputValue = boom::js::Value::String(value->context(), input);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "key", keyValue },
                            { "modifiers", modifiersValue },
                            { "input", inputValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewKeyDownEvent, { objectValue });
                        return true;
                    } else {
                        return false;
                    }
                });
                view->onKeyUp([](boom::ViewRef view, boom::Key key, boom::KeyModifiers modifiers, std::string const& input) {
                    if (auto value = view->getValue<boom::js::Value>(boom::api::kViewValueKey)) {
                        auto keyValue = boom::api::KeyToValue(value->context(), key);
                        auto modifiersValue = boom::api::KeyModifiersToValue(value->context(), modifiers);
                        auto inputValue = boom::js::Value::String(value->context(), input);
                        auto objectValue = boom::js::Value::Object(value->context(), {
                            { "key", keyValue },
                            { "modifiers", modifiersValue },
                            { "input", inputValue }
                        });
                        boom::api::Trigger(value, boom::api::kViewKeyUpEvent, { objectValue });
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

    viewClass->install(context);
}

} /* namespace boom::api */