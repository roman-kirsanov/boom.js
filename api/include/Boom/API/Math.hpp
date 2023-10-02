#pragma once

#include <expected>
#include <Boom/Math.hpp>
#include <Boom/JS.hpp>

namespace boom::js {

boom::js::ValueRef Vec2ToValue(boom::js::ContextRef, boom::Vec2);
boom::js::ValueRef Vec4ToValue(boom::js::ContextRef, boom::Vec4);

std::expected<boom::Vec2, boom::js::ValueRef> ValueToVec2(boom::js::ContextRef, boom::js::ValueRef);
std::expected<boom::Vec4, boom::js::ValueRef> ValueToVec4(boom::js::ContextRef, boom::js::ValueRef);

} /* namespace boom::js */