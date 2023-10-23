#pragma once

#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>
#include <Boom/JS/Types.hpp>

namespace boom::js {

class Poller final : public boom::Shared {
public:
    Poller();
    std::int64_t add(std::function<void()> const&);
    void remove(std::int64_t);
    bool empty() const;
    void poll();
    void clear();
    virtual ~Poller();
    static boom::js::PollerRef Default();
private:
    boom::Emitter<> _listeners;
};

} /* namespace boom::js */