#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/API/Utilities.hpp>

namespace boom::api {

void Subscribe(boom::js::ContextRef context, boom::js::ValueRef object, std::string const& event, boom::js::ValueRef callback) {
    if (context == nullptr) {
        boom::Abort("boom::api::Subscribe() failed: \"context\" cannot be nullptr");
    }
    if (object == nullptr) {
        boom::Abort("boom::api::Subscribe() failed: \"object\" cannot be nullptr");
    }
    if (callback == nullptr) {
        boom::Abort("boom::api::Subscribe() failed: \"callback\" cannot be nullptr");
    }
    if (object->isObject()) {
        auto listeners = object->getProperty("__" + event + "_listeners");
        if (listeners->isArray()) {
            auto push = listeners->getProperty("push");
            if (push->isFunction()) {
                push->call(listeners, { callback });
            } else {
                throw boom::Error("Listeners array has no \"push\" method");
            }
        } else {
            object->setProperty("__" + event + "_listeners", boom::js::Value::Array(context, { callback }));
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

void Unsubscribe(boom::js::ContextRef context, boom::js::ValueRef object, std::string const& event, boom::js::ValueRef callback) {
    if (context == nullptr) {
        boom::Abort("boom::api::Unsubscribe() failed: \"context\" cannot be nullptr");
    }
    if (object == nullptr) {
        boom::Abort("boom::api::Unsubscribe() failed: \"object\" cannot be nullptr");
    }
    if (callback == nullptr) {
        boom::Abort("boom::api::Unsubscribe() failed: \"callback\" cannot be nullptr");
    }
    if (object->isObject()) {
        auto listeners = object->getProperty("__" + event + "_listeners");
        if (listeners->isArray()) {
            auto array = listeners->arrayValue();
            auto pos = std::find(array.begin(), array.end(), callback);
            if (pos != array.end()) {
                array.erase(pos);
                object->setProperty("__" + event + "_listeners", boom::js::Value::Array(context, array));
            }
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

void Trigger(boom::js::ContextRef context, boom::js::ValueRef object, std::string const& event, std::vector<boom::js::ValueRef> const& args) {
    if (context == nullptr) {
        boom::Abort("boom::api::Trigger() failed: \"context\" cannot be nullptr");
    }
    if (object == nullptr) {
        boom::Abort("boom::api::Trigger() failed: \"object\" cannot be nullptr");
    }
    if (object->isObject()) {
        auto listeners = object->getProperty("__" + event + "_listeners");
        if (listeners->isArray()) {
            auto array = listeners->arrayValue();
            for (auto callback : array) {
                callback->call(boom::js::Value::Undefined(context), args);
            }
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

} /* namespace boom::api */