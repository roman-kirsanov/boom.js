#pragma once

#include <memory>
#include <algorithm>

namespace boom {

class NoCopy {
public:
    NoCopy() = default;
    NoCopy(boom::NoCopy &&) = delete;
    NoCopy(boom::NoCopy const&) = delete;
    boom::NoCopy& operator=(boom::NoCopy &&) = delete;
    boom::NoCopy& operator=(boom::NoCopy const&) = delete;
};

class Shared : public std::enable_shared_from_this<boom::Shared> {
public:
    Shared() = default;
    Shared(boom::Shared &&) = delete;
    Shared(boom::Shared const&) = delete;
    boom::Shared& operator=(boom::Shared &&) = delete;
    boom::Shared& operator=(boom::Shared const&) = delete;
    virtual ~Shared() = default;
protected:
    virtual void _onReady() {};
    template<typename T, typename... A>
    friend std::shared_ptr<T> MakeShared(A &&... args);
};

template<int N>
struct Tag {
    constexpr Tag(char const (&)[N]);
    constexpr operator char const*() const;
    char value[N];
};

template<typename T, typename... A>
std::shared_ptr<T> MakeShared(A &&... args) {
    std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<A>(args)...);
    if constexpr (std::is_base_of_v<boom::Shared, T>) {
        std::static_pointer_cast<boom::Shared>(ptr)->_onReady();
    }
    return ptr;
}

template<typename T, typename B>
std::shared_ptr<T> GetShared(B* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Shared, B>, "***");
    if (obj != nullptr) {
        return std::static_pointer_cast<T>(
            obj->shared_from_this()
        );
    } else {
        return nullptr;
    }
}

template<typename T, typename B>
std::shared_ptr<T const> GetShared(B const* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Shared, B>, "***");
    if (obj != nullptr) {
        return std::static_pointer_cast<T const>(
            obj->shared_from_this()
        );
    } else {
        return nullptr;
    }
}

template<typename T, typename B>
std::weak_ptr<T> GetWeak(B* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Shared, B>, "***");
    if (obj != nullptr) {
        return boom::GetShared<T, B>(obj);
    } else {
        return std::weak_ptr<T>{};
    }
}

template<typename T, typename B>
std::weak_ptr<T const> GetWeak(B const* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Shared, B>, "***");
    if (obj != nullptr) {
        return boom::GetShared<T const, B>(obj);
    } else {
        return std::weak_ptr<T>{};
    }
}

template<int N>
inline constexpr Tag<N>::Tag(char const (&className)[N]) {
    std::copy(className, className + N, value);
}

template<int N>
inline constexpr Tag<N>::operator char const*() const {
    return value;
}

template<typename T>
T* Alloc(std::size_t size) {
    return static_cast<T*>(calloc(size, sizeof(T)));
}

template<typename T>
void Free(T* data) {
    if (data != nullptr) {
        ::free(data);
    }
}

} /* namespace boom */
