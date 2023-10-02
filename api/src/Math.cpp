#include <iostream>
#include <Boom/API/Math.hpp>

namespace boom::js {

boom::js::ValueRef Vec2ToValue(boom::js::ContextRef context, boom::Vec2 vec2) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Vec2ToValue() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return boom::js::Value::Array(context, {
        boom::js::Value::Number(context, vec2.x),
        boom::js::Value::Number(context, vec2.y)
    });
}

boom::js::ValueRef Vec4ToValue(boom::js::ContextRef context, boom::Vec4 vec4) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::Vec4ToValue() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return boom::js::Value::Array(context, {
        boom::js::Value::Number(context, vec4.x),
        boom::js::Value::Number(context, vec4.y),
        boom::js::Value::Number(context, vec4.width),
        boom::js::Value::Number(context, vec4.height)
    });
}

std::expected<boom::Vec2, boom::js::ValueRef> ValueToVec2(boom::js::ContextRef context, boom::js::ValueRef value) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::ValueToVec2() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    if (value == nullptr) {
        std::cerr << "ERROR: boom::js::ValueToVec2() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto const array = value->arrayValue();
    if (!array) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec2"));
    }
    if (array.value().size() != 2) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec2"));
    }
    auto const x = array.value()[0]->numberValue();
    auto const y = array.value()[1]->numberValue();
    if (!x) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec2"));
    }
    if (!y) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec2"));
    }
    return boom::Vec2{
        static_cast<float>(x.value()),
        static_cast<float>(y.value())
    };
}

std::expected<boom::Vec4, boom::js::ValueRef> ValueToVec4(boom::js::ContextRef context, boom::js::ValueRef value) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::js::ValueToVec4() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    if (value == nullptr) {
        std::cerr << "ERROR: boom::js::ValueToVec4() failed: \"value\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    auto const array = value->arrayValue();
    if (!array) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    if (array.value().size() != 4) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    auto const x = array.value()[0]->numberValue();
    auto const y = array.value()[1]->numberValue();
    auto const width = array.value()[2]->numberValue();
    auto const height = array.value()[3]->numberValue();
    if (!x) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    if (!y) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    if (!width) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    if (!height) {
        return std::unexpected(boom::js::Value::Error(context, "Value is not a Vec4"));
    }
    return boom::Vec4{
        static_cast<float>(x.value()),
        static_cast<float>(y.value()),
        static_cast<float>(width.value()),
        static_cast<float>(height.value())
    };
}

} /* namespace boom::js */