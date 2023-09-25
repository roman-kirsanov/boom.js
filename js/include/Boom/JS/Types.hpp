#pragma once

#include <expected>
#include <functional>

namespace boom::js {

class Context;
class Value;
class Class;

using ContextRef = std::shared_ptr<boom::js::Context>;
using ValueRef = std::shared_ptr<boom::js::Value>;
using ClassRef = std::shared_ptr<boom::js::Class>;

using Function = std::function<
    std::expected<boom::js::ValueRef, boom::js::ValueRef>(
        boom::js::ContextRef,
        boom::js::ValueRef,
        std::vector<boom::js::ValueRef>
    )
>;

using FunctionResult = std::expected<boom::js::ValueRef, boom::js::ValueRef>;

} /* namespace boom::js */