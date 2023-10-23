#include <Boom/API/Input.hpp>

namespace boom::js {

boom::js::ValueRef KeyToValue(boom::js::ContextRef context, boom::Key key) {
    return boom::js::Value::String(context, boom::KeyName(key));
}

boom::js::ValueRef KeyModifiersToValue(boom::js::ContextRef context, boom::KeyModifiers modifiers) {
    return boom::js::Value::Object(context, {
        { "control", boom::js::Value::Boolean(context, modifiers.control) },
        { "shift", boom::js::Value::Boolean(context, modifiers.shift) },
        { "meta", boom::js::Value::Boolean(context, modifiers.meta) },
        { "alt", boom::js::Value::Boolean(context, modifiers.alt) }
    });
}

} /* namespace boom::js */