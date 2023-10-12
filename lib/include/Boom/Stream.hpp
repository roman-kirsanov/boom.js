#pragma once

#include <expected>
#include <cinttypes>
#include <functional>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

template<typename T>
class Writer : public boom::Shared {
public:
    Writer();
    bool isClosed() const;
    void write(std::vector<T> const&);
    void close();
    virtual ~Writer();
protected:
    virtual void _onWrite(std::vector<T> const&) {};
    virtual void _onClose() {};
};

template<typename T>
class Reader : public boom::Shared {
public:
    Reader();
    bool isClosed() const;
    std::vector<T> readAll() const;
    std::tuple<std::vector<T>, bool> read() const;
    virtual ~Reader();
protected:
    virtual std::vector<T> _onReadAll() const { return {}; }
    virtual std::tuple<std::vector<T>, bool> _onRead() const { return { {}, true }; }
    virtual void _onClose() {};
};

template<typename T>
class Stream final : boom::Shared {
public:
    Stream();
    boom::Emitter<> onClose;
    boom::Emitter<std::string const&> onError;
    boom::Emitter<std::vector<T> const&> onData;
    std::shared_ptr<boom::Reader<T>> reader() const;
    std::shared_ptr<boom::Writer<T>> writer();
    virtual ~Stream();
};

} /* namespace boom */
