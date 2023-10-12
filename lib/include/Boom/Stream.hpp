#pragma once

#include <expected>
#include <cinttypes>
#include <functional>
#include <Boom/Memory.hpp>
#include <Boom/Emitter.hpp>

namespace boom {

template<typename T>
using WriterOnWrite = std::function<void(std::vector<T> const&)>;

template<typename T>
using WriterOnClose = std::function<void()>;

template<typename T>
struct WriterOptions {
    boom::WriterOnWrite<T> onWrite;
    boom::WriterOnClose<T> onClose;
};

template<typename T>
class Writer : public boom::Shared {
public:
    Writer(boom::WriterOptions<T> const&);
    Writer(boom::WriterOptions<T> &&);
    bool isClosed() const;
    void write(std::vector<T> const&);
    void close();
    virtual ~Writer();
};

template<typename T>
using ReaderOnRead = std::function<std::vector<T>()>;

template<typename T>
using ReaderOnClose = std::function<void()>;

template<typename T>
struct ReaderOptions {
    boom::ReaderOnRead<T> onRead;
    boom::ReaderOnRead<T> onReadAll;
    boom::ReaderOnClose<T> onClose;
};

template<typename T>
class Reader : public boom::Shared {
public:
    Reader(boom::ReaderOptions<T> const&);
    Reader(boom::ReaderOptions<T> &&);
    bool isClosed() const;
    std::vector<T> readAll() const;
    std::tuple<std::vector<T>, bool> read() const;
    virtual ~Reader();
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
