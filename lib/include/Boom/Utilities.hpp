#pragma once

#include <map>
#include <vector>
#include <string>
#include <functional>

namespace boom {

std::vector<std::string> ParseArgs(char const**, int);
std::map<std::string, std::string> ParseEnvs(char const**);

template<typename T>
std::int64_t IndexOf(std::vector<T> const&, T const&);

template<typename T>
bool Includes(std::vector<T> const&, T const&);

template<typename T>
bool Remove(std::vector<T>&, T const&);

template<typename T>
void ForEach(std::vector<T> const&, std::function<void(T const&)> const&);

template<typename T>
void ForEach(std::vector<T> const&, std::function<void(T const&, std::size_t)> const&);

template<typename T1, typename T2>
std::vector<T2> Map(std::vector<T1> const&, std::function<T2(T1 const&)> const&);

template<typename T1, typename T2>
std::vector<T2> Map(std::vector<T1> const&, std::function<T2(T1 const&, std::size_t)> const&);

template<typename T>
std::string Join(std::vector<T> const&, std::string const&);

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
    auto index = boom::IndexOf(vector, item);
    if (index > -1) {
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

} /* namespace boom */