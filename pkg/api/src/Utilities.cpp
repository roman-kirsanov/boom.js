#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/API/Utilities.hpp>

namespace boom::api {

void Subscribe(boom::js::ValueRef object, std::string const& event, boom::js::ValueRef callback) {
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
            object->setProperty("__" + event + "_listeners", boom::js::Value::Array(object->context(), { callback }));
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

void Unsubscribe(boom::js::ValueRef object, std::string const& event, boom::js::ValueRef callback) {
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
                object->setProperty("__" + event + "_listeners", boom::js::Value::Array(object->context(), array));
            }
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

void Trigger(boom::js::ValueRef object, std::string const& event, std::vector<boom::js::ValueRef> const& args) {
    if (object == nullptr) {
        boom::Abort("boom::api::Trigger() failed: \"object\" cannot be nullptr");
    }
    if (object->isObject()) {
        auto listeners = object->getProperty("__" + event + "_listeners");
        if (listeners->isArray()) {
            auto array = listeners->arrayValue();
            for (auto callback : array) {
                try {
                    callback->call(boom::js::Value::Undefined(object->context()), args);
                } catch (boom::Error& e) {
                    if (auto error = e.data<boom::js::Value>("jsError")) {
                        std::cerr << "ERROR: " << boom::js::ExtractErrorMessage(error) << std::endl;
                        std::cerr << boom::js::ExtractErrorStack(error) << std::endl;
                    } else {
                        std::cerr << "ERROR: " << e.what() << std::endl;
                    }
                }
            }
        }
    } else {
        throw boom::Error("Value is not an object");
    }
}

} /* namespace boom::api */