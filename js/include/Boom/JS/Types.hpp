#pragma once

#include <expected>
#include <functional>

namespace boom::js {

class Poller;
class Context;
class Scope;
class Value;

using PollerRef = std::shared_ptr<boom::js::Poller>;
using ContextRef = std::shared_ptr<boom::js::Context>;
using ScopeRef = std::shared_ptr<boom::js::Scope>;
using ValueRef = std::shared_ptr<boom::js::Value>;

using Finalizer = std::function<void(boom::js::ContextRef, boom::js::ValueRef)>;
using Function = std::function<void(boom::js::ScopeRef)>;

} /* namespace boom::js */