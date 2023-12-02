#pragma once

#include <map>
#include <string>
#include <exception>
#include <Boom/Memory.hpp>

namespace boom {

class Error : public std::exception {
public:
    Error(std::string const&);
    Error(std::string const&, std::map<std::string, std::shared_ptr<boom::Object>> const&);
    boom::Error& extend(std::string const&);
    boom::Error& extend(std::string const&, std::map<std::string, std::shared_ptr<boom::Object>> const&);
    template<typename T>
    std::shared_ptr<T> data(std::string const&) const;
    void setData(std::string const&, std::shared_ptr<boom::Object>);
    virtual char const* what() const noexcept override;
private:
    std::string _message;
    std::map<std::string, std::shared_ptr<boom::Object>> _data;
    std::shared_ptr<boom::Object> _getData(std::string const&) const;
};

template<typename T>
std::shared_ptr<T> Error::data(std::string const& key) const {
    if (auto value = _getData(key)) {
        return std::dynamic_pointer_cast<T>(value);
    } else {
        return nullptr;
    }
}

} /* namespace boom */