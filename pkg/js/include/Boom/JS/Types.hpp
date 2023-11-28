#pragma once

#include <memory>
#include <expected>
#include <functional>

namespace boom::js {

class Context;
class Scope;
class Value;

using ContextRef = std::shared_ptr<boom::js::Context>;
using ContextCRef = std::shared_ptr<boom::js::Context const>;
using ScopeRef = std::shared_ptr<boom::js::Scope>;
using ScopeCRef = std::shared_ptr<boom::js::Scope const>;
using ValueRef = std::shared_ptr<boom::js::Value>;
using ValueCRef = std::shared_ptr<boom::js::Value const>;
using ContextWRef = std::weak_ptr<boom::js::Context>;
using ContextCWRef = std::weak_ptr<boom::js::Context const>;
using ScopeWRef = std::weak_ptr<boom::js::Scope>;
using ScopeCWRef = std::weak_ptr<boom::js::Scope const>;
using ValueWRef = std::weak_ptr<boom::js::Value>;
using ValueCWRef = std::weak_ptr<boom::js::Value const>;

using Constructor = std::function<void(boom::js::ScopeRef)>;
using Destructor = std::function<void(boom::js::ScopeRef)>;
using Function = std::function<boom::js::ValueRef(boom::js::ScopeRef)>;
using Getter = std::function<boom::js::ValueRef(boom::js::ScopeRef)>;
using Setter = std::function<void(boom::js::ScopeRef, boom::js::ValueRef)>;

} /* namespace boom::js */