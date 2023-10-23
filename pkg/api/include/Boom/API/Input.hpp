#pragma once

#include <Boom/Input.hpp>
#include <Boom/JS.hpp>

namespace boom::js {

boom::js::ValueRef KeyToValue(boom::js::ContextRef, boom::Key);
boom::js::ValueRef KeyModifiersToValue(boom::js::ContextRef, boom::KeyModifiers);

} /* namespace boom::js */