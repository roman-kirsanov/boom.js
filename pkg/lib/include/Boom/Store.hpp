#pragma once

#include <map>
#include <tuple>
#include <optional>
#include <Boom/Memory.hpp>

namespace boom {

enum StoreValueRefType {
    Strong,
    Weak
};

class StoreValueOptions {
    std::optional<boom::StoreValueRefType> refType;
};

class Store {
public:
    Store();
    template<boom::SharedObject T>
    std::shared_ptr<T> getValue(std::int64_t) const;
    template<boom::SharedObject T>
    void setValue(std::int64_t, std::shared_ptr<T>, boom::StoreValueOptions const& = {});
private:
    std::map<
        std::int64_t,
        std::tuple<
            std::shared_ptr<boom::Shared>,
            std::weak_ptr<boom::Shared>
        >
    > _values;
};

template<boom::SharedObject T>
inline std::shared_ptr<T> Store::getValue(std::int64_t key) const {
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

template<boom::SharedObject T>
inline void Store::setValue(std::int64_t key, std::shared_ptr<T> value, boom::StoreValueOptions const& options) {
    if (options.refType.value_or(boom::StoreValueRefType::Strong) == boom::StoreValueRefType::Strong) {
        _values[key] = { value, nullptr };
    } else {
        _values[key] = { nullptr, value };
    }
}

} /* namespace boom */