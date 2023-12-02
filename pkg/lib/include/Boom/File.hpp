#pragma once

#include <span>
#include <string>
#include <fstream>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

class File;

using FileRef = std::shared_ptr<boom::File>;
using FileCRef = std::shared_ptr<boom::File const>;
using FileWRef = std::weak_ptr<boom::File>;
using FileCWRef = std::weak_ptr<boom::File const>;

struct FileInfo {
    bool exists;
    bool isFile;
    bool isSymlink;
    bool isDirectory;
    double createdAt;
    double modifiedAt;
    double accessedAt;
    std::size_t size;
};

struct FileMode {
    bool read;
    bool write;
    bool trunc;
};

enum class FileSeek {
    Start,
    Current,
    End
};

class File final : public boom::Object {
public:
    File(std::string const&, boom::FileMode const& = {});
    std::size_t position();
    std::size_t read(boom::BufferRef);
    void write(boom::BufferCRef);
    void write(std::string const&);
    void seek(std::int64_t, boom::FileSeek);
    void close();
    virtual ~File();
    static boom::BufferRef Read(std::string const&);
    static void Write(std::string const&, boom::BufferCRef);
    static void Write(std::string const&, std::string const&);
    static void Append(std::string const&, boom::BufferCRef);
    static void Append(std::string const&, std::string const&);
    static bool Exists(std::string const&);
    static bool IsFile(std::string const&);
    static bool IsDirectory(std::string const&);
    static bool IsSymlink(std::string const&);
    static boom::FileInfo Info(std::string const&);
private:
    std::fstream _stream;
};

} /* namespace boom */
