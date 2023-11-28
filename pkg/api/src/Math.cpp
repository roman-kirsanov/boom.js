#include <iostream>
#include <Boom/Utilities.hpp>
#include <Boom/API/Math.hpp>

namespace boom::api {

boom::js::ValueRef Vec2ToValue(boom::js::ContextRef context, boom::Vec2 vec2) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::api::Vec2ToValue() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return boom::js::Value::Array(context, {
        boom::js::Value::Number(context, vec2.x),
        boom::js::Value::Number(context, vec2.y)
    });
}

boom::js::ValueRef Vec4ToValue(boom::js::ContextRef context, boom::Vec4 vec4) {
    if (context == nullptr) {
        std::cerr << "ERROR: boom::api::Vec4ToValue() failed: \"context\" cannot be nullptr" << std::endl;
        std::exit(-1);
    }
    return boom::js::Value::Array(context, {
        boom::js::Value::Number(context, vec4.x),
        boom::js::Value::Number(context, vec4.y),
        boom::js::Value::Number(context, vec4.width),
        boom::js::Value::Number(context, vec4.height)
    });
}

boom::Vec2 ValueToVec2(boom::js::ContextRef context, boom::js::ValueRef value) {
    if (context == nullptr) {
        boom::Abort("boom::api::ValueToVec2() failed: \"context\" cannot be nullptr");
    }
    if (value == nullptr) {
        boom::Abort("boom::api::ValueToVec2() failed: \"value\" cannot be nullptr");
    }
    try {
        auto const array = value->arrayValue();
        if (array.size() != 2) {
            throw boom::Error("Array must be of length 2");
        }
        if (array[0]->isNumber() == false) {
            throw boom::Error("First element must be of type number");
        }
        if (array[1]->isNumber() == false) {
            throw boom::Error("Second element must be of type number");
        }
        return boom::Vec2{
            static_cast<float>(array[0]->numberValue()),
            static_cast<float>(array[1]->numberValue())
        };
    } catch (boom::Error& e) {
        throw e.extend("Value is not a Vec2");
    }
}

boom::Vec4 ValueToVec4(boom::js::ContextRef context, boom::js::ValueRef value) {
    if (context == nullptr) {
        boom::Abort("boom::api::ValueToVec4() failed: \"context\" cannot be nullptr");
    }
    if (value == nullptr) {
        boom::Abort("boom::api::ValueToVec4() failed: \"value\" cannot be nullptr");
    }
    try {
        auto const array = value->arrayValue();
        if (array.size() != 4) {
            throw boom::Error("Array must be of length 4");
        }
        if (array[0]->isNumber() == false) {
            throw boom::Error("First element must be of type number");
        }
        if (array[1]->isNumber() == false) {
            throw boom::Error("Second element must be of type number");
        }
        if (array[2]->isNumber() == false) {
            throw boom::Error("Third element must be of type number");
        }
        if (array[3]->isNumber() == false) {
            throw boom::Error("Fourth element must be of type number");
        }
        return boom::Vec4{
            static_cast<float>(array[0]->numberValue()),
            static_cast<float>(array[1]->numberValue()),
            static_cast<float>(array[2]->numberValue()),
            static_cast<float>(array[3]->numberValue())
        };
    } catch (boom::Error& e) {
        throw e.extend("Value is not a Vec4");
    }
}

} /* namespace boom::api */