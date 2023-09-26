#pragma once

#include <expected>
#include <functional>

namespace boom::js {

class Context;
class Value;

using ContextRef = std::shared_ptr<boom::js::Context>;
using ValueRef = std::shared_ptr<boom::js::Value>;

using Initializer = std::function<void(boom::js::ContextRef, boom::js::ValueRef)>;
using Finalizer = std::function<void(boom::js::ContextRef, boom::js::ValueRef)>;
using Result = std::expected<boom::js::ValueRef, boom::js::ValueRef>;
using Function = std::function<
    boom::js::Result(
        boom::js::ContextRef,
        boom::js::ValueRef,
        std::vector<boom::js::ValueRef>
    )
>;

} /* namespace boom::js */