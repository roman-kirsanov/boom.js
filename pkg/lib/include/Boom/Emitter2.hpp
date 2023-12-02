#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include <functional>

namespace boom {

template<typename... A>
class Subscription;

template<typename... A>
using SubscriptionRef = std::shared_ptr<Subscription<A...>>;

template<typename... A>
using Emitter2Callback = std::function<bool(A...)>;

template<typename... A>
class Subscription {
public:
    Subscription(boom::Emitter2Callback<A...> const&);
    void invoke(A...);
    void cancel();
    bool cancelled() const;
private:
    boom::Emitter2Callback<A...> _callback;
    bool _cancelled;
};

template<typename... A>
class Emitter2 final {
public:
    Emitter2();
    Emitter2(boom::Emitter2<A...> const&);
    Emitter2(boom::Emitter2<A...> &&);
    boom::Emitter2<A...>& operator=(boom::Emitter2<A...> const&);
    boom::Emitter2<A...>& operator=(boom::Emitter2<A...> &&);
    template<typename F>
    typename std::enable_if_t<std::is_same_v<std::invoke_result_t<F, A...>, void>, boom::SubscriptionRef<A...>> operator()(F const&);
    template<typename F>
    typename std::enable_if_t<std::is_same_v<std::invoke_result_t<F, A...>, bool>, boom::SubscriptionRef<A...>> operator()(F const&);
    boom::SubscriptionRef<A...> once(boom::Emitter2Callback<A...> const&);
    void emit(A...);
    void clear();
    ~Emitter2();
private:
    bool _emitting;
    std::vector<boom::SubscriptionRef<A...>> _subscriptions;
};

template<typename... A>
inline Subscription<A...>::Subscription(boom::Emitter2Callback<A...> const& callback)
    : _callback(callback)
    , _cancelled(false) {}

template<typename... A>
inline void Subscription<A...>::invoke(A... args) {
    if (_cancelled == false) {
        if (_callback(std::forward<A...>(args)...) == false) {
            _cancelled = true;
        }
    }
}

template<typename... A>
inline void Subscription<A...>::cancel() {
    _cancelled = true;
}

template<typename... A>
inline bool Subscription<A...>::cancelled() const {
    return _cancelled;
}

template<typename... A>
inline Emitter2<A...>::~Emitter2() {}

template<typename... A>
inline Emitter2<A...>::Emitter2()
    : _emitting(false)
    , _subscriptions() {}

template<typename... A>
inline Emitter2<A...>::Emitter2(boom::Emitter2<A...> const&) {}

template<typename... A>
inline Emitter2<A...>::Emitter2(boom::Emitter2<A...> &&) {}

template<typename... A>
inline boom::Emitter2<A...>& Emitter2<A...>::operator=(boom::Emitter2<A...> const&) {
    return *this;
}

template<typename... A>
inline boom::Emitter2<A...>& Emitter2<A...>::operator=(boom::Emitter2<A...> &&) {
    return *this;
}

template<typename... A>
template<typename F>
inline typename std::enable_if_t<std::is_same_v<std::invoke_result_t<F, A...>, void>, boom::SubscriptionRef<A...>> Emitter2<A...>::operator()(F const& callback) {
    auto subscription = std::make_shared<boom::Subscription<A...>>([callback](A... args) {
        callback(args...);
        return true;
    });
    _subscriptions.push_back(subscription);
    return subscription;
}

template<typename... A>
template<typename F>
inline typename std::enable_if_t<std::is_same_v<std::invoke_result_t<F, A...>, bool>, boom::SubscriptionRef<A...>> Emitter2<A...>::operator()(F const& callback) {
    auto subscription = std::make_shared<boom::Subscription<A...>>(callback);
    _subscriptions.push_back(subscription);
    return subscription;
}

template<typename... A>
inline boom::SubscriptionRef<A...> Emitter2<A...>::once(boom::Emitter2Callback<A...> const& callback) {
    auto subscription = std::make_shared<boom::Subscription<A...>>([callback](A... args) {
        callback(args...);
        return false;
    });
    _subscriptions.push_back(subscription);
    return subscription;
}

template<typename... A>
inline void Emitter2<A...>::emit(A... args) {
    if (_emitting == false) {
        _emitting = true;
        try {
            for (auto subscription : _subscriptions) {
                subscription->invoke(std::forward<A...>(args)...);
            }
            auto from = std::remove_if(
                _subscriptions.begin(),
                _subscriptions.end(),
                [](auto item) { return (item->cancelled() == true); }
            );
            if (from != _subscriptions.end()) {
                _subscriptions.erase(from, _subscriptions.end());
            }
            _emitting = false;
        } catch (...) {
            _emitting = false;
            throw;
        }
    }
}

template<typename... A>
inline void Emitter2<A...>::clear() {

}

} /* namespace boom */