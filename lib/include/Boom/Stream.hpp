#pragma once

#include <expected>
#include <cinttypes>
#include <functional>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

template<typename T>
class Stream final : boom::Shared {
public:
    Stream();
    boom::Emitter<> onClose;
    boom::Emitter<std::string const&> onError;
    boom::Emitter<std::vector<T> const&> onData;
    virtual ~Stream();
};

} /* namespace boom */
