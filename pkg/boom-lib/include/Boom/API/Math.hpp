#pragma once

#include <Boom/Math.hpp>
#include <Boom/JS.hpp>

namespace boom::api {

boom::js::ValueRef Vec2ToValue(boom::js::ContextRef, boom::Vec2);
boom::js::ValueRef Vec4ToValue(boom::js::ContextRef, boom::Vec4);

boom::Vec2 ValueToVec2(boom::js::ContextRef, boom::js::ValueRef);
boom::Vec4 ValueToVec4(boom::js::ContextRef, boom::js::ValueRef);

} /* namespace boom::api */