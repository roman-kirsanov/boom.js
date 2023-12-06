#include <Boom/Error.hpp>

namespace boom {

Error::Error(std::string const& message)
    : _message(message)
    , _data() {}

Error::Error(std::string const& message, std::map<std::string, std::shared_ptr<boom::Object>> const& data)
    : _message(message)
    , _data(data) {}

boom::Error& Error::extend(std::string const& message) {
    if (_message != "") {
        _message = (message + ": " + _message);
    } else {
        _message = message;
    }
    return *this;
}

boom::Error& Error::extend(std::string const& message, std::map<std::string, std::shared_ptr<boom::Object>> const& data) {
    if (_message != "") {
        _message = (message + ": " + _message);
    } else {
        _message = message;
    }
    for (auto& pair : data) {
        setData(pair.first, pair.second);
    }
    return *this;
}

std::shared_ptr<boom::Object> Error::_getData(std::string const& key) const {
    auto const pos = _data.find(key);
    if (pos != _data.end()) {
        return pos->second;
    } else {
        return nullptr;
    }
}

void Error::setData(std::string const& key, std::shared_ptr<boom::Object> value) {
    _data[key] = value;
}

char const* Error::what() const noexcept {
    return _message.c_str();
}

} /* namespace boom */