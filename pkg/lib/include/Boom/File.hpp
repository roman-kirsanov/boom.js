#pragma once

#include <span>
#include <string>
#include <fstream>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

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

class File final : public boom::Shared {
public:
    File(std::string const&, boom::FileMode const& = {});
    std::size_t position();
    std::size_t read(std::shared_ptr<boom::Buffer>);
    void write(std::shared_ptr<boom::Buffer const>);
    void write(std::string const&);
    void seek(std::int64_t, boom::FileSeek);
    void close();
    virtual ~File();
    static std::shared_ptr<boom::Buffer> Read(std::string const&);
    static void Write(std::string const&, std::shared_ptr<boom::Buffer const>);
    static void Write(std::string const&, std::string const&);
    static void Append(std::string const&, std::shared_ptr<boom::Buffer const>);
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
