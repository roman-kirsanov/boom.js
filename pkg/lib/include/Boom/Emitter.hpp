#pragma once

#include <vector>
#include <cinttypes>
#include <functional>

namespace boom {

std::int64_t __EmitterNextId();

template<typename... A>
using EmitterHandler = std::function<void(A...)>;

template<typename... A>
struct EmitterListener {
    boom::EmitterHandler<A...> fn;
    std::int64_t id;
    bool once;
};

template<typename... A>
class Emitter {
public:
    Emitter();
    Emitter(boom::Emitter<A...> const&) : _emitting(false) {};
    Emitter(boom::Emitter<A...> &&) : _emitting(false) {};
    boom::Emitter<A...>& operator=(boom::Emitter<A...> const&) {};
    boom::Emitter<A...>& operator=(boom::Emitter<A...> &&) {};
    std::int64_t operator()(boom::EmitterHandler<A...> const&);
    std::int64_t once(boom::EmitterHandler<A...> const&);
    std::vector<boom::EmitterListener<A...>> const& listeners() const;
    bool emitting() const;
    void remove(std::int64_t);
    void emit(A...);
    void clear();
    virtual ~Emitter() {}
private:
    bool _emitting;
    std::vector<boom::EmitterListener<A...>> _listeners;
};

template<typename... A>
inline Emitter<A...>::Emitter()
    : _emitting(false)
    , _listeners() {}

template<typename... A>
inline std::int64_t Emitter<A...>::operator()(boom::EmitterHandler<A...> const& fn) {
    auto const id = __EmitterNextId();
    _listeners.push_back({ fn, id, false });
    return id;
}

template<typename... A>
inline std::int64_t Emitter<A...>::once(boom::EmitterHandler<A...> const& fn) {
    auto const id = __EmitterNextId();
    _listeners.push_back({ fn, id, true });
    return id;
}

template<typename... A>
inline std::vector<boom::EmitterListener<A...>> const& Emitter<A...>::listeners() const {
    return _listeners;
}

template<typename... A>
inline bool Emitter<A...>::emitting() const {
    return _emitting;
}

template<typename... A>
inline void Emitter<A...>::remove(std::int64_t id) {
    auto const it = (
        std::find_if(
            _listeners.begin(),
            _listeners.end(),
            [&](auto const& listener) { return (listener.id == id); }
        )
    );
    if (it != _listeners.end()) {
        _listeners.erase(it);
    }
}

template<typename... A>
inline void Emitter<A...>::emit(A... args) {
    if (_emitting == false) {
        _emitting = true;
        for (auto const& listener : _listeners) {
            listener.fn(args...);
        }
        _emitting = false;
        _listeners.erase(
            std::remove_if(
                _listeners.begin(),
                _listeners.end(),
                [](auto const& listener) { return listener.once; }
            ),
            _listeners.end()
        );
    }
}

template<typename... A>
inline void Emitter<A...>::clear() {
    _listeners.clear();
}

} /* namespace boom */
