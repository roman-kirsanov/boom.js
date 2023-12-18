#pragma once

#include <map>
#include <vector>
#include <string>
#include <cinttypes>
#include <functional>

namespace boom {

template<int N>
struct Tag {
    constexpr Tag(char const (&)[N]);
    constexpr operator char const*() const;
    char value[N];
};

[[noreturn]] void Abort(std::string const&);
void Warning(std::string const&);

template<typename T>
T* Alloc(std::size_t size);

template<typename T>
void Free(T* data);

std::vector<std::string> ParseArgs(char const**, int);
std::map<std::string, std::string> ParseEnvs(char const**);

template<typename T>
std::int64_t IndexOf(std::vector<T> const&, T const&);

template<typename T>
bool Includes(std::vector<T> const&, T const&);

template<typename T>
bool Remove(std::vector<T>&, T const&);

template<typename T>
bool RemoveIndex(std::vector<T>&, std::int64_t);

template<typename T>
void ForEach(std::vector<T> const&, std::function<void(T const&)> const&);

template<typename T>
void ForEach(std::vector<T> const&, std::function<void(T const&, std::size_t)> const&);

template<typename T1, typename T2>
std::vector<T2> Map(std::vector<T1> const&, std::function<T2(T1 const&)> const&);

template<typename T1, typename T2>
std::vector<T2> Map(std::vector<T1> const&, std::function<T2(T1 const&, std::size_t)> const&);

template<typename T>
T Clamp(T, T, T);

template<typename T>
std::string Join(std::vector<T> const&, std::string const&);

template<typename T>
std::vector<T> Concat(std::vector<T> const&, std::vector<T> const&);

template<typename T>
std::vector<T> Slice(std::vector<T> const&, std::int64_t);

template<typename T>
std::vector<T> Slice(std::vector<T> const&, std::int64_t, std::int64_t);

template<typename T>
T const& ItemOr(std::vector<T> const&, std::int64_t, T const&);

template<int N>
inline constexpr Tag<N>::Tag(char const (&className)[N]) {
    std::copy(className, className + N, value);
}

template<int N>
inline constexpr Tag<N>::operator char const*() const {
    return value;
}

template<typename T>
inline T* Alloc(std::size_t size) {
    return static_cast<T*>(calloc(size, sizeof(T)));
}

template<typename T>
inline void Free(T* data) {
    if (data != nullptr) {
        ::free(data);
    }
}

template<typename T>
inline std::int64_t IndexOf(std::vector<T> const& vector, T const& item) {
    for (std::size_t i = 0; i < vector.size(); i++) {
        if (vector[i] == item) {
            return static_cast<std::int64_t>(i);
        }
    }
    return -1;
}

template<typename T>
inline bool Includes(std::vector<T> const& vector, T const& item) {
    return (boom::IndexOf(vector, item) > -1);
}

template<typename T>
inline bool Remove(std::vector<T>& vector, T const& item) {
    auto const index = boom::IndexOf(vector, item);
    if (index > -1) {
        vector.erase(vector.begin() + index);
        return true;
    } else {
        return false;
    }
}

template<typename T>
bool RemoveIndex(std::vector<T>& vector, std::int64_t index) {
    if ((index >= 0) && (index < vector.size())) {
        vector.erase(vector.begin() + index);
        return true;
    } else {
        return false;
    }
}

template<typename T>
inline void ForEach(std::vector<T> const& vector, std::function<void(T const&)> const& fn) {
    for (std::size_t i = 0; i < vector.size(); i++) {
        fn(vector[i]);
    }
}

template<typename T>
inline void ForEach(std::vector<T> const& vector, std::function<void(T const&, std::size_t)> const& fn) {
    for (std::size_t i = 0; i < vector.size(); i++) {
        fn(vector[i], i);
    }
}

template<typename T1, typename T2>
inline std::vector<T2> Map(std::vector<T1> const& vector, std::function<T2(T1 const&)> const& fn) {
    auto ret = std::vector<T2>();
    ret.reserve(vector.size());
    for (std::size_t i = 0; i < vector.size(); i++) {
        ret.push_back(fn(vector[i]));
    }
    return ret;
}

template<typename T1, typename T2>
inline std::vector<T2> Map(std::vector<T1> const& vector, std::function<T2(T1 const&, std::size_t)> const& fn) {
    auto ret = std::vector<T2>();
    ret.reserve(vector.size());
    for (std::size_t i = 0; i < vector.size(); i++) {
        ret.push_back(fn(vector[i], i));
    }
    return ret;
}

template<typename T>
inline T Clamp(T value, T min, T max) {
    if (value < min) return min;
    else if (value > max) return max;
    else return value;
}

template<typename T>
inline std::string Join(std::vector<T> const& vector, std::string const& separator) {
    auto ret = std::string();
    if (vector.size() > 1) {
        ret = std::to_string(vector[0]);
        for (std::size_t i = 1; i < vector.size(); i++) {
            ret += separator;
            ret += std::to_string(vector[i]);
        }
    } else if (vector.size() == 1) {
        ret = std::to_string(vector[0]);
    }
    return ret;
}

template<>
inline std::string Join<std::string>(std::vector<std::string> const& vector, std::string const& separator) {
    auto ret = std::string();
    if (vector.size() > 1) {
        ret = vector[0];
        for (std::size_t i = 1; i < vector.size(); i++) {
            ret += separator;
            ret += vector[i];
        }
    } else if (vector.size() == 1) {
        ret = vector[0];
    }
    return ret;
}

template<typename T>
inline std::vector<T> Concat(std::vector<T> const& vector1, std::vector<T> const& vector2) {
    auto ret = std::vector<T>();
    ret.insert(ret.end(), vector1.begin(), vector1.end());
    ret.insert(ret.end(), vector2.begin(), vector2.end());
    return ret;
}

template<typename T>
inline std::vector<T> Slice(std::vector<T> const& vector, std::int64_t start) {
    if (start >= 0) {
        return std::vector<T>(
            (vector.begin() + boom::Clamp<std::int64_t>(start, 0, vector.size())),
            vector.end()
        );
    } else {
        return std::vector<T>(
            (vector.end() - boom::Clamp<std::int64_t>((start * -1), 0, vector.size())),
            vector.end()
        );
    }
}

template<typename T>
inline std::vector<T> Slice(std::vector<T> const& vector, std::int64_t start, std::int64_t end) {
    auto const startIndex = boom::Clamp<std::int64_t>(((start >= 0) ? start : (vector.size() + start)), 0, vector.size());
    auto const endIndex = boom::Clamp<std::int64_t>(((end >= 0) ? end : (vector.size() + end)), startIndex, vector.size());
    return std::vector<T>(
        (vector.begin() + startIndex),
        (vector.begin() + endIndex)
    );
}

template<typename T>
inline T const& ItemOr(std::vector<T> const& vector, std::int64_t index, T const& fallback) {
    if ((index >= 0)
    && (index < vector.size())) {
        return vector[index];
    } else {
        return fallback;
    }
}

std::vector<std::string> Split(std::string const&, std::string const&);

} /* namespace boom */