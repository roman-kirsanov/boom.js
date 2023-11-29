#pragma once

#include <Boom/JS/Value.hpp>

namespace boom::api {

void Subscribe(boom::js::ContextRef, boom::js::ValueRef, std::string const&, boom::js::ValueRef);
void Unsubscribe(boom::js::ContextRef, boom::js::ValueRef, std::string const&, boom::js::ValueRef);
void Trigger(boom::js::ContextRef, boom::js::ValueRef, std::string const&, std::vector<boom::js::ValueRef> const&);

} /* namespace boom::api */