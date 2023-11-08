#pragma once

#include <memory>
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

using Constructor = std::function<void(boom::js::ScopeRef)>;
using Destructor = std::function<void(boom::js::ScopeRef)>;
using Function = std::function<boom::js::ValueRef(boom::js::ScopeRef)>;
using Getter = std::function<boom::js::ValueRef(boom::js::ScopeRef)>;
using Setter = std::function<void(boom::js::ScopeRef, boom::js::ValueRef)>;

} /* namespace boom::js */