#pragma once

#include <string>
#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Stream.hpp>

namespace boom {

struct FileOptions {
    bool read;
    bool write;
};

enum class FileSeek {
    Start,
    Current,
    End
};

class File final : public boom::Shared {
public:
    File(std::string const&, boom::FileOptions const& = { .read = true });
    bool exists() const;
    bool isFile() const;
    bool isDirectory() const;
    bool isSymlink() const;
    double createdAt() const;
    double modifiedAt() const;
    double accessedAt() const;
    std::size_t size() const;
    std::size_t position() const;
    std::size_t write(std::vector<std::uint8_t> const&);
    std::size_t read(std::vector<std::uint8_t>&);
    std::int64_t seek(std::int64_t, boom::FileSeek);
    void close();
    virtual ~File();
    static bool Exists(std::string const&);
    static bool IsFile(std::string const&);
    static bool IsDirectory(std::string const&);
    static bool IsSymlink(std::string const&);
    static void Write(std::string const&, std::vector<std::uint8_t> const&);
    static void Append(std::string const&, std::vector<std::uint8_t> const&);
    static void Remove(std::string const&);
    static std::vector<std::uint8_t> Read(std::string const&);
};

} /* namespace boom */
