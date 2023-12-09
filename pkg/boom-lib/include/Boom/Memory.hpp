#pragma once

#include <map>
#include <memory>
#include <cinttypes>
#include <algorithm>

namespace boom {

class Object;

template<typename T>
concept IsObject = std::is_base_of_v<boom::Object, T>;

template<typename T, typename... A>
std::shared_ptr<T> MakeShared(A &&... args);

template<typename T, typename B>
std::shared_ptr<T> GetShared(B* obj);

template<typename T, typename B>
std::shared_ptr<T const> GetShared(B const* obj);

template<typename T, typename B>
std::weak_ptr<T> GetWeak(B* obj);

template<typename T, typename B>
std::weak_ptr<T const> GetWeak(B const* obj);

class NoCopy {
public:
    NoCopy() = default;
    NoCopy(boom::NoCopy &&) = delete;
    NoCopy(boom::NoCopy const&) = delete;
    boom::NoCopy& operator=(boom::NoCopy &&) = delete;
    boom::NoCopy& operator=(boom::NoCopy const&) = delete;
};

enum ObjectValueRefType {
    Strong,
    Weak
};

struct ObjectValueOptions {
    std::optional<boom::ObjectValueRefType> refType;
};

class Object : public std::enable_shared_from_this<boom::Object> {
public:
    Object() = default;
    Object(boom::Object &&) = delete;
    Object(boom::Object const&) = delete;
    boom::Object& operator=(boom::Object &&) = delete;
    boom::Object& operator=(boom::Object const&) = delete;
    template<boom::IsObject T>
    std::shared_ptr<T> getValue(std::int64_t) const;
    template<boom::IsObject T>
    void setValue(std::int64_t, std::shared_ptr<T>, boom::ObjectValueOptions const& = {});
    void deleteValue(std::int64_t);
    virtual ~Object() = default;
protected:
    virtual void _onReady() {};
    template<typename T, typename... A>
    friend std::shared_ptr<T> MakeShared(A &&... args);
private:
    std::map<
        std::int64_t,
        std::tuple<
            std::shared_ptr<boom::Object>,
            std::weak_ptr<boom::Object>
        >
    > _values;
};

template<boom::IsObject T>
inline std::shared_ptr<T> Object::getValue(std::int64_t key) const {
    auto pair = _values.find(key);
    if (pair != _values.end()) {
        auto strptr = std::get<0>((*pair).second);
        auto weakptr = std::get<1>((*pair).second);
        if (strptr != nullptr) {
            return std::dynamic_pointer_cast<T>(strptr);
        } else if (auto strptr = weakptr.lock()) {
            return std::dynamic_pointer_cast<T>(strptr);
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}

template<boom::IsObject T>
inline void Object::setValue(std::int64_t key, std::shared_ptr<T> value, boom::ObjectValueOptions const& options) {
    if (options.refType.value_or(boom::ObjectValueRefType::Strong) == boom::ObjectValueRefType::Strong) {
        _values[key] = { value, std::weak_ptr<boom::Object>() };
    } else {
        _values[key] = { std::shared_ptr<boom::Object>(), value };
    }
}

inline void Object::deleteValue(std::int64_t key) {
    auto pos = _values.find(key);
    if (pos != _values.end()) {
        _values.erase(pos);
    }
}

template<typename T, typename... A>
inline std::shared_ptr<T> MakeShared(A &&... args) {
    std::shared_ptr<T> ptr = std::make_shared<T>(std::forward<A>(args)...);
    if constexpr (std::is_base_of_v<boom::Object, T>) {
        std::static_pointer_cast<boom::Object>(ptr)->_onReady();
    }
    return ptr;
}

template<typename T, typename B>
inline std::shared_ptr<T> GetShared(B* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Object, B>, "***");
    if (obj != nullptr) {
        return std::static_pointer_cast<T>(
            obj->shared_from_this()
        );
    } else {
        return nullptr;
    }
}

template<typename T, typename B>
inline std::shared_ptr<T const> GetShared(B const* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Object, B>, "***");
    if (obj != nullptr) {
        return std::static_pointer_cast<T const>(
            obj->shared_from_this()
        );
    } else {
        return nullptr;
    }
}

template<typename T, typename B>
inline std::weak_ptr<T> GetWeak(B* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Object, B>, "***");
    if (obj != nullptr) {
        return boom::GetShared<T, B>(obj);
    } else {
        return std::weak_ptr<T>{};
    }
}

template<typename T, typename B>
inline std::weak_ptr<T const> GetWeak(B const* obj) {
    static_assert(std::is_base_of_v<B, T>, "***");
    static_assert(std::is_base_of_v<boom::Object, B>, "***");
    if (obj != nullptr) {
        return boom::GetShared<T const, B>(obj);
    } else {
        return std::weak_ptr<T>{};
    }
}

} /* namespace boom */
