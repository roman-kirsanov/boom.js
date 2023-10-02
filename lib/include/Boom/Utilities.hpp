#pragma once

#include <map>
#include <vector>
#include <string>

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
std::int64_t IndexOf(std::vector<T> const& vector, T const& item) {
    for (std::size_t i = 0; i < vector.size(); i++) {
        if (vector[i] == item) {
            return static_cast<std::int64_t>(i);
        }
    }
    return -1;
}

template<typename T>
bool Includes(std::vector<T> const& vector, T const& item) {
    return (boom::IndexOf(vector, item) > -1);
}

template<typename T>
bool Remove(std::vector<T>& vector, T const& item) {
    auto index = boom::IndexOf(vector, item);
    if (index > -1) {
        vector.erase(vector.begin() + index);
        return true;
    } else {
        return false;
    }
}

} /* namespace boom */