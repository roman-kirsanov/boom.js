#pragma once

#include <span>
#include <string>
#include <expected>
#include <cinttypes>
#include <Boom/Memory.hpp>
#include <Boom/Buffer.hpp>

namespace boom {

struct __FileImpl;

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
    std::expected<void, std::string> write(std::string const&);
    std::expected<void, std::string> write(std::shared_ptr<boom::Buffer const>);
    std::expected<std::size_t, std::string> read(std::shared_ptr<boom::Buffer>);
    void seek(std::int64_t, boom::FileSeek);
    void close();
    virtual ~File();
private:
    boom::__FileImpl* _impl;
    void _implInit(std::string const&, boom::FileOptions const&);
    void _implDone();
    bool _implExists() const;
    bool _implIsFile() const;
    bool _implIsDirectory() const;
    bool _implIsSymlink() const;
    bool _implCreatedAt() const;
    bool _implModifiedAt() const;
    bool _implAccessedAt() const;
    std::size_t _implSize() const;
    std::size_t _implPosition() const;
    std::expected<void, std::string> _implWrite(std::string const&);
    std::expected<void, std::string> _implWrite(std::shared_ptr<boom::Buffer const>);
    std::expected<std::size_t, std::string> _implRead(std::shared_ptr<boom::Buffer>);
    void _implSeek(std::int64_t, boom::FileSeek);
    void _implClose();
};

bool FileExists(std::string const&);
bool FileIsFile(std::string const&);
bool FileIsDirectory(std::string const&);
bool FileIsSymlink(std::string const&);
void FileWrite(std::string const&, std::string const&);
void FileWrite(std::string const&, std::shared_ptr<boom::Buffer const>);
void FileAppend(std::string const&, std::shared_ptr<boom::Buffer const>);
void FileAppend(std::string const&, std::string const&);
void FileRemove(std::string const&);
std::expected<std::shared_ptr<boom::Buffer>, std::string> FileRead(std::string const&);

} /* namespace boom */
